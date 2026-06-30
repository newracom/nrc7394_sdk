/* multi_role_tfota_client.c (Root side) */

#include "multi_role_proto.h"
#include "app_feature_cfg.h"
#include "nrc_sdk.h"
#include "lwip/sockets.h"
#include "lwip/inet.h"
#include "lwip/errno.h"
#include "lwip/tcp.h" /* TCP_NODELAY */
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

#ifndef TFOTA_CHUNK_MAX
#define TFOTA_CHUNK_MAX 1024
#endif

/*
 * When the relay’s RX loop is busy (flash writes, status reporting, etc.),
 * lwIP can run out of TCP send buffers/pbufs and send() can return -1 with
 * errno=ENOMEM (ERR_MEM) instead of blocking. Treat this as a transient
 * condition and retry a few times with a short backoff.
 */
#ifndef TFOTA_SEND_RETRY_DELAY_MS
#define TFOTA_SEND_RETRY_DELAY_MS 10
#endif

#ifndef TFOTA_SEND_RETRY_MAX_MS
#define TFOTA_SEND_RETRY_MAX_MS 5000
#endif

/* Optional pacing between chunks (helps very slow flash writers) */
#ifndef TFOTA_SEND_THROTTLE_MS
#define TFOTA_SEND_THROTTLE_MS 0
#endif

/* Stop-and-wait application ACK on top of TCP. */
#ifndef TFOTA_USE_APP_ACK
#define TFOTA_USE_APP_ACK 1
#endif

#ifndef TFOTA_ACK_TIMEOUT_MS
#define TFOTA_ACK_TIMEOUT_MS 30000
#endif

/* Total time budget for waiting an ACK for a given phase (START/CHUNK/END).
 * On jittery multi-hop links, it is common to see long gaps. We prefer to
 * tolerate those rather than aborting too early.
 */
#ifndef TFOTA_ACK_TOTAL_TIMEOUT_MS
#define TFOTA_ACK_TOTAL_TIMEOUT_MS 120000
#endif

/* Retry policy when an ACK is missed.
 * START must NOT be resent (it triggers erase/start on relay).
 * CHUNK/END are idempotent and may be resent.
 */
#ifndef TFOTA_ACK_RETRY_DELAY_MS
#define TFOTA_ACK_RETRY_DELAY_MS 200
#endif

#ifndef TFOTA_CHUNK_ACK_RETRY_MAX
#define TFOTA_CHUNK_ACK_RETRY_MAX 2
#endif

#ifndef TFOTA_END_ACK_RETRY_MAX
#define TFOTA_END_ACK_RETRY_MAX 2
#endif

#ifndef TFOTA_ACK_RCV_POLL_MS
#define TFOTA_ACK_RCV_POLL_MS 200
#endif

/* from util_fota.c */
extern int util_fota_read(uint32_t src, uint8_t *dst, uint32_t len);

/* Optional debug */
#ifndef TFOTA_DEBUG
#define TFOTA_DEBUG 0
#endif

#if TFOTA_DEBUG
#define TFOTA_LOG(fmt, ...) printf("[TFOTA] " fmt, ##__VA_ARGS__)
#else
#define TFOTA_LOG(fmt, ...) do {} while (0)
#endif

static uint32_t tfota_now_ms(void)
{
	return (uint32_t)(xTaskGetTickCount() * portTICK_PERIOD_MS);
}

static int send_all(int sock, const void *buf, int len)
{
	const uint8_t *p = (const uint8_t *)buf;
	uint32_t waited_ms = 0;

	while (len > 0) {
		int n = send(sock, p, len, 0);
		if (n < 0) {
			if (errno == ENOMEM || errno == EWOULDBLOCK || errno == EAGAIN) {
				if (waited_ms >= TFOTA_SEND_RETRY_MAX_MS) {
					TFOTA_LOG("send_all: retry timeout (errno=%d)\n", errno);
					return -1;
				}
				_delay_ms(TFOTA_SEND_RETRY_DELAY_MS);
				waited_ms += TFOTA_SEND_RETRY_DELAY_MS;
				continue;
			}
			TFOTA_LOG("send_all: send failed errno=%d\n", errno);
			return -1;
		}
		if (n == 0) {
			TFOTA_LOG("send_all: send returned 0\n");
			return -1;
		}
		p += n;
		len -= n;
		waited_ms = 0;
	}
	return 0;
}

#if TFOTA_USE_APP_ACK
static void tfota_dump_ack(const nrc_fota_ack_t *ack, const char *tag)
{
	if (!ack)
		return;

	TFOTA_LOG("%s ACK: magic=0x%08" PRIx32 " type=%u len=%u seq=%" PRIu32
		  " sess=0x%08" PRIx32 " written=%" PRIu32 " next=%" PRIu32
		  " prog=%u status=%u\n",
		  tag,
		  ack->hdr.magic,
		  (unsigned)ack->hdr.type,
		  (unsigned)ack->hdr.len,
		  ack->hdr.seq,
		  ack->hdr.session_id,
		  ack->written,
		  ack->next_offset,
		  (unsigned)ack->progress_percent,
		  (unsigned)ack->status);
}

/*
 * Read exactly N bytes without relying on MSG_WAITALL.
 * Uses SO_RCVTIMEO polling and a total deadline.
 */
static int recv_exact_deadline(int sock, void *buf, int len, int deadline_ms)
{
	uint8_t *p = (uint8_t *)buf;
	int left = len;

	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = TFOTA_ACK_RCV_POLL_MS * 1000;
	setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

	uint32_t start = tfota_now_ms();
	int calls = 0;

	while (left > 0) {
		int n = recv(sock, p, left, 0);
		calls++;

		if (n > 0) {
			p += n;
			left -= n;
			continue;
		}

		if (n == 0) {
			TFOTA_LOG("recv_exact: peer closed (got=%d/%d)\n", len - left, len);
			return -1;
		}

		/* n < 0 */
		if (errno == EWOULDBLOCK || errno == EAGAIN) {
			if ((int)(tfota_now_ms() - start) >= deadline_ms) {
				TFOTA_LOG("recv_exact: timeout (got=%d/%d, calls=%d)\n",
					  len - left, len, calls);
				return -1;
			}
			continue;
		}

		TFOTA_LOG("recv_exact: recv error errno=%d (got=%d/%d)\n",
			  errno, len - left, len);
		return -1;
	}

#if TFOTA_DEBUG
	if (calls > 1)
		TFOTA_LOG("recv_exact: assembled %d bytes in %d recv calls\n", len, calls);
#endif
	return 0;
}

/* Read and validate one FOTA ACK message (header-first parsing). */
static int wait_fota_ack(int sock, uint32_t session_id, uint32_t expected_written, int ack_timeout_ms)
{
	uint32_t start = tfota_now_ms();
	int deadline_ms = ack_timeout_ms;

	/* 1) Read header */
	nrc_fota_hdr_t hdr;
	memset(&hdr, 0, sizeof(hdr));

	if (recv_exact_deadline(sock, &hdr, (int)sizeof(hdr), deadline_ms) < 0) {
		TFOTA_LOG("wait_fota_ack: timeout/short HDR (sess=0x%08" PRIx32 " expect=%" PRIu32 ")\n",
			  session_id, expected_written);
		return -1;
	}

	/* Remaining time */
	{
		int used = (int)(tfota_now_ms() - start);
		if (used >= deadline_ms) {
			TFOTA_LOG("wait_fota_ack: deadline exceeded after HDR\n");
			return -1;
		}
		deadline_ms -= used;
	}

	/* Basic header checks */
	if (hdr.magic != NRC_MAGIC_FOTA || hdr.type != NRC_FOTA_MSG_ACK) {
		nrc_fota_ack_t tmp;
		memset(&tmp, 0, sizeof(tmp));
		memcpy(&tmp.hdr, &hdr, sizeof(hdr));
		tfota_dump_ack(&tmp, "BAD_HDR");
		return -1;
	}

	if (hdr.len != (uint16_t)sizeof(nrc_fota_ack_t)) {
		TFOTA_LOG("BAD_LEN: hdr.len=%u expected=%u\n",
			  (unsigned)hdr.len, (unsigned)sizeof(nrc_fota_ack_t));
		return -1;
	}

	if (hdr.session_id != session_id) {
		TFOTA_LOG("BAD_SESS: rx=0x%08" PRIx32 " expected=0x%08" PRIx32 "\n",
			  hdr.session_id, session_id);
		return -1;
	}

	/* 2) Read remainder of ACK */
	nrc_fota_ack_t ack;
	memset(&ack, 0, sizeof(ack));
	memcpy(&ack.hdr, &hdr, sizeof(hdr));

	int remain = (int)sizeof(ack) - (int)sizeof(hdr);
	if (recv_exact_deadline(sock, ((uint8_t *)&ack) + sizeof(hdr), remain, deadline_ms) < 0) {
		TFOTA_LOG("wait_fota_ack: timeout/short PAYLOAD (sess=0x%08" PRIx32 ")\n", session_id);
		return -1;
	}

	/* If server reports failure, stop immediately. */
	if (ack.status == (uint8_t)NRC_FOTA_STATUS_FAILED) {
		tfota_dump_ack(&ack, "FAIL");
		return -1;
	}

	/* written must be >= what we expect (allow coalescing). */
	if (ack.written < expected_written) {
		tfota_dump_ack(&ack, "BEHIND");
		return -1;
	}

	return 0;
}
#endif /* TFOTA_USE_APP_ACK */

#if TFOTA_USE_APP_ACK
/* Wait for an ACK with a total budget, without resending anything. */
static int wait_fota_ack_total(int sock, uint32_t session_id, uint32_t expected_written, int total_timeout_ms)
{
	uint32_t t0 = tfota_now_ms();
	while ((int)(tfota_now_ms() - t0) < total_timeout_ms) {
		int left = total_timeout_ms - (int)(tfota_now_ms() - t0);
		int slice = TFOTA_ACK_TIMEOUT_MS;
		if (slice > left)
			slice = left;

		if (wait_fota_ack(sock, session_id, expected_written, slice) == 0)
			return 0;

		/* Brief pause before trying again, in case the relay is busy. */
		_delay_ms(TFOTA_ACK_RETRY_DELAY_MS);
	}
	return -1;
}
#endif

static uint32_t make_session_id(void)
{
	uint32_t t = (uint32_t)xTaskGetTickCount();
	return (t ^ (t << 16) ^ 0xA5A55A5A);
}

int tfota_push_to_relay(uint32_t relay_ip_nbo,
			uint32_t fw_ver_packed,
			uint32_t fw_len,
			uint32_t fw_crc)
{
	if (!relay_ip_nbo || !fw_len || !fw_crc) {
		TFOTA_LOG("invalid args: ip=0x%08" PRIx32 " len=%" PRIu32 " crc=0x%08" PRIx32 "\n",
			  relay_ip_nbo, fw_len, fw_crc);
		return -1;
	}

	uint32_t session_id = make_session_id();
	uint32_t seq = 1;
	uint32_t chunk_size = TFOTA_CHUNK_MAX;

	int s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0)
		return -1;

	/* Best-effort: enlarge buffers and disable Nagle */
	{
		int v;

		v = 1;
		setsockopt(s, IPPROTO_TCP, TCP_NODELAY, &v, sizeof(v));

		v = 16 * 1024;
		setsockopt(s, SOL_SOCKET, SO_SNDBUF, &v, sizeof(v));

		v = 16 * 1024;
		setsockopt(s, SOL_SOCKET, SO_RCVBUF, &v, sizeof(v));
	}

	struct sockaddr_in to;
	memset(&to, 0, sizeof(to));
	to.sin_family = AF_INET;
	to.sin_port = htons(app_tfota_data_port());
	to.sin_addr.s_addr = relay_ip_nbo;

	TFOTA_LOG("connect relay ip=0x%08" PRIx32 " port=%u\n",
		  relay_ip_nbo, (unsigned)app_tfota_data_port());

	if (connect(s, (struct sockaddr *)&to, sizeof(to)) < 0) {
		TFOTA_LOG("connect failed errno=%d\n", errno);
		close(s);
		return -1;
	}

	/* ---------------- START ---------------- */
	nrc_fota_start_t st;
	memset(&st, 0, sizeof(st));
	st.hdr.magic = NRC_MAGIC_FOTA;
	st.hdr.type = NRC_FOTA_MSG_START;
	st.hdr.len = (uint16_t)sizeof(st);
	st.hdr.seq = seq++;
	st.hdr.session_id = session_id;

	st.fw_ver_packed = fw_ver_packed;
	st.fw_len = fw_len;
	st.fw_crc = fw_crc;
	st.chunk_size = chunk_size;
	{
		const char *nm = (const char *)nrc_get_app_name();
		memset(st.target_app_name, 0, sizeof(st.target_app_name));
		if (nm && nm[0]) {
			strncpy(st.target_app_name, nm, sizeof(st.target_app_name) - 1);
			st.target_app_name[sizeof(st.target_app_name) - 1] = '\0';
		}
	}

	TFOTA_LOG("START sess=0x%08" PRIx32 " ver=0x%08" PRIx32 " len=%" PRIu32
		  " crc=0x%08" PRIx32 " chunk=%" PRIu32 " app='%s'\n",
		  session_id, fw_ver_packed, fw_len, fw_crc, chunk_size,
		  st.target_app_name);

	if (send_all(s, &st, (int)sizeof(st)) < 0)
		goto fail;

#if TFOTA_USE_APP_ACK
	/* START must not be resent (it triggers erase/start on relay).
	 * Just wait longer on poor links.
	 */
	if (wait_fota_ack(s, session_id, 0, TFOTA_ACK_TOTAL_TIMEOUT_MS) < 0) {
		TFOTA_LOG("START ACK timeout/invalid\n");
		goto fail;
	}
#endif

	/* ---------------- CHUNKS ---------------- */
	static uint8_t pktbuf[sizeof(nrc_fota_chunk_t) + TFOTA_CHUNK_MAX];

	for (uint32_t off = 0; off < fw_len; off += chunk_size) {
		uint32_t n = fw_len - off;
		if (n > chunk_size)
			n = chunk_size;

		nrc_fota_chunk_t *ch = (nrc_fota_chunk_t *)pktbuf;

		memset(ch, 0, sizeof(nrc_fota_chunk_t));
		ch->hdr.magic = NRC_MAGIC_FOTA;
		ch->hdr.type = NRC_FOTA_MSG_CHUNK;
		/* Keep seq stable for retransmits of the same chunk. */
		uint32_t chunk_seq = seq++;
		ch->hdr.seq = chunk_seq;
		ch->hdr.session_id = session_id;

		ch->offset = off;
		ch->payload_len = (uint16_t)n;
		ch->hdr.len = (uint16_t)(sizeof(nrc_fota_chunk_t) + n);

		/* Read directly into the packet payload buffer (saves RAM). */
		if (util_fota_read(off, ch->payload, n) < 0) {
			TFOTA_LOG("util_fota_read failed off=%" PRIu32 " n=%" PRIu32 "\n", off, n);
			goto fail;
		}

		/* Send + wait ACK with limited retransmits on missed ACK.
		 * This is crucial for lossy/jittery multi-hop wireless.
		 */
		uint32_t phase_start = tfota_now_ms();
		int retries = 0;
		while (1) {
			if (send_all(s, pktbuf, (int)ch->hdr.len) < 0) {
				TFOTA_LOG("send chunk failed off=%" PRIu32 " n=%" PRIu32 " errno=%d\n",
					  off, n, errno);
				goto fail;
			}

#if TFOTA_USE_APP_ACK
			int remaining = (int)TFOTA_ACK_TOTAL_TIMEOUT_MS - (int)(tfota_now_ms() - phase_start);
			if (remaining <= 0)
				remaining = TFOTA_ACK_TIMEOUT_MS;
			if (remaining > TFOTA_ACK_TIMEOUT_MS)
				remaining = TFOTA_ACK_TIMEOUT_MS;

			if (wait_fota_ack(s, session_id, off + n, remaining) == 0)
				break;

			retries++;
			if (retries > TFOTA_CHUNK_ACK_RETRY_MAX ||
			    (tfota_now_ms() - phase_start) >= TFOTA_ACK_TOTAL_TIMEOUT_MS) {
				TFOTA_LOG("ACK timeout/invalid off=%" PRIu32 " n=%" PRIu32 " (retries=%d)\n",
					  off, n, retries);
				goto fail;
			}
			_delay_ms(TFOTA_ACK_RETRY_DELAY_MS);
			/* retransmit same chunk with same seq */
#else
			break;
#endif
		}

		if (TFOTA_SEND_THROTTLE_MS)
			_delay_ms(TFOTA_SEND_THROTTLE_MS);
	}

	/* ---------------- END ---------------- */
	nrc_fota_hdr_t end;
	memset(&end, 0, sizeof(end));
	end.magic = NRC_MAGIC_FOTA;
	end.type = NRC_FOTA_MSG_END;
	end.len = (uint16_t)sizeof(end);
	end.seq = seq++;
	end.session_id = session_id;

	TFOTA_LOG("END sess=0x%08" PRIx32 "\n", session_id);

	/* END is idempotent; allow a couple retransmits if ACK is missed. */
	{
		uint32_t phase_start = tfota_now_ms();
		int retries = 0;
		while (1) {
			if (send_all(s, &end, (int)sizeof(end)) < 0)
				goto fail;

#if TFOTA_USE_APP_ACK
			int remaining = (int)TFOTA_ACK_TOTAL_TIMEOUT_MS - (int)(tfota_now_ms() - phase_start);
			if (remaining <= 0)
				remaining = TFOTA_ACK_TIMEOUT_MS;
			if (remaining > TFOTA_ACK_TIMEOUT_MS)
				remaining = TFOTA_ACK_TIMEOUT_MS;

			if (wait_fota_ack(s, session_id, fw_len, remaining) == 0)
				break;

			retries++;
			if (retries > TFOTA_END_ACK_RETRY_MAX ||
			    (tfota_now_ms() - phase_start) >= TFOTA_ACK_TOTAL_TIMEOUT_MS) {
				TFOTA_LOG("END ACK timeout/invalid (retries=%d)\n", retries);
				goto fail;
			}
			_delay_ms(TFOTA_ACK_RETRY_DELAY_MS);
#else
			break;
#endif
		}
	}

	/* ---------------- REBOOT ---------------- */
	nrc_fota_hdr_t rb;
	memset(&rb, 0, sizeof(rb));
	rb.magic = NRC_MAGIC_FOTA;
	rb.type = NRC_FOTA_MSG_REBOOT;
	rb.len = (uint16_t)sizeof(rb);
	rb.seq = seq++;
	rb.session_id = session_id;

	TFOTA_LOG("REBOOT sess=0x%08" PRIx32 "\n", session_id);

	if (send_all(s, &rb, (int)sizeof(rb)) < 0)
		goto fail;

	close(s);
	return 0;

fail:
	close(s);
	return -1;
}
