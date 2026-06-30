/* multi_role_tfota_server.c
 *
 * TFOTA TCP server running on RELAY.
 *
 * Debug/robustness notes:
 * - Do NOT assume recv(MSG_WAITALL) returns the full requested length in lwIP.
 *   It can legally return short reads. Always loop until you've assembled
 *   the required bytes (recv_exact()).
 * - Only trust errno when recv() returns < 0.
 * - Log only interesting cases (failures, split reads, slow flash writes),
 *   to avoid flooding the console.
 */

#include "multi_role_tfota_server.h"
#include "multi_role_register.h"
#include "nrc_sdk.h"
#include "app_feature_cfg.h"

#include "lwip/sockets.h"
#include "lwip/inet.h"
#include "lwip/tcp.h"   /* TCP_NODELAY */
#include "lwip/errno.h" /* errno */

#include <string.h>
#include <inttypes.h>
#include <stdbool.h>

#define TFOTA_CHUNK_MAX     1024

#ifndef TFOTA_SRV_DEBUG
#define TFOTA_SRV_DEBUG     1
#endif

#if TFOTA_SRV_DEBUG
#define TFOTA_LOG(fmt, ...) printf("[TFOTA_SRV] " fmt, ##__VA_ARGS__)
#else
#define TFOTA_LOG(fmt, ...) do {} while (0)
#endif

/*
 * IMPORTANT: In this sample, we write each received chunk directly to flash
 * and also report status to the root.
 *
 * Flash writes and very frequent status reporting can stall the RX loop,
 * which reduces TCP ACK pace and can cause the sender (root) to time out or
 * hit lwIP ERR_MEM/ENOMEM.
 *
 * Two pragmatic mitigations:
 *  - Throttle status reporting (big win)
 *  - Yield briefly after a flash write (optional)
 */
#ifndef TFOTA_STATUS_MIN_INTERVAL_MS
#define TFOTA_STATUS_MIN_INTERVAL_MS  1000  /* don't spam UDP status faster than this */
#endif

#ifndef TFOTA_STATUS_PCT_STEP
#define TFOTA_STATUS_PCT_STEP         1     /* report when progress advances by at least this */
#endif

#ifndef TFOTA_FLASH_WRITE_YIELD_MS
#define TFOTA_FLASH_WRITE_YIELD_MS    0     /* set to 1..5ms if flash driver blocks CPU for long */
#endif

/*
 * TFOTA robustness on multi-hop / jittery links
 * -------------------------------------------
 * lwIP can return EAGAIN/EWOULDBLOCK either because SO_RCVTIMEO fired or
 * because the task was delayed and no data is immediately available.
 *
 * The old behavior treated ~10s of no-data as a hard failure. On HaLow
 * multi-hop paths, it's common to see gaps >10s between TCP payload bursts.
 *
 * New behavior:
 *   - Use a short per-recv timeout to wake periodically (SO_RCVTIMEO)
 *   - Abort only after a longer overall "no progress" window
 */
#ifndef TFOTA_TCP_RCVTIMEO_MS
#define TFOTA_TCP_RCVTIMEO_MS         2000   /* per recv() wake-up */
#endif

#ifndef TFOTA_NO_PROGRESS_MS
#define TFOTA_NO_PROGRESS_MS          60000  /* abort only after this long with no RX progress */
#endif

#ifndef TFOTA_RECV_EAGAIN_DELAY_MS
#define TFOTA_RECV_EAGAIN_DELAY_MS    10
#endif

/* Log "split recv" only if a payload required multiple recv() calls */
#ifndef TFOTA_LOG_SPLIT_RECV
#define TFOTA_LOG_SPLIT_RECV          0
#endif

/* Log slow flash operations */
#ifndef TFOTA_LOG_SLOW_FLASH_MS
#define TFOTA_LOG_SLOW_FLASH_MS       20
#endif

static uint32_t g_session;
static uint32_t g_fw_len;
static uint32_t g_fw_crc;
static uint32_t g_written;

static uint32_t g_new_fw_ver;
static uint32_t g_chunk_size;

static uint32_t g_last_report_ms;
static uint8_t  g_last_report_pct;
static nrc_fota_status_t g_last_report_state;

/* Current TCP connection from root (valid only while a session is active). */
static int g_client_sock = -1;

/* Optional weak hooks from register.c */
extern uint32_t tfota_get_root_ip_nbo(void);
extern int      tfota_get_self_mac(uint8_t mac[6]);

/* ---------------- helpers ---------------- */

static uint32_t tfota_now_ms(void)
{
	return (uint32_t)(xTaskGetTickCount() * portTICK_PERIOD_MS);
}

static void tfota_print_ip_port(const char *prefix, uint32_t ip_nbo, uint16_t port_nbo)
{
	const uint8_t *p = (const uint8_t *)&ip_nbo;
	TFOTA_LOG("%s %u.%u.%u.%u:%u\n",
		  prefix,
		  (unsigned)p[0], (unsigned)p[1], (unsigned)p[2], (unsigned)p[3],
		  (unsigned)ntohs(port_nbo));
}

static const char *tfota_type_str(uint16_t t)
{
	switch (t) {
	case NRC_FOTA_MSG_START:  return "START";
	case NRC_FOTA_MSG_CHUNK:  return "CHUNK";
	case NRC_FOTA_MSG_END:    return "END";
	case NRC_FOTA_MSG_REBOOT: return "REBOOT";
	case NRC_FOTA_MSG_ACK:    return "ACK";
	default:                  return "UNK";
	}
}

/* Looping recv: assemble exactly len bytes unless connection closes or error occurs. */
static int recv_exact(int sock, void *buf, int len, const char *tag, uint32_t sess)
{
	uint8_t *p = (uint8_t *)buf;
	int got = 0;
	int calls = 0;
	uint32_t t0 = tfota_now_ms();
	uint32_t last_progress_ms = t0;

	while (got < len) {
		int r = recv(sock, p + got, len - got, 0);
		calls++;

		if (r > 0) {
			got += r;
			last_progress_ms = tfota_now_ms();
			continue;
		}

		if (r == 0) {
			TFOTA_LOG("recv_exact(%s): peer closed (sess=0x%08" PRIx32 " got=%d/%d)\n",
				  tag, sess, got, len);
			return -1;
		}

		/* r < 0 */
		if (errno == EAGAIN || errno == EWOULDBLOCK) {
			uint32_t now = tfota_now_ms();

			/* Only fail after a long overall no-progress window. */
			if ((now - last_progress_ms) < TFOTA_NO_PROGRESS_MS) {
				_delay_ms(TFOTA_RECV_EAGAIN_DELAY_MS);
				continue;
			}

			TFOTA_LOG("recv_exact(%s): timeout errno=%d (sess=0x%08" PRIx32
				" got=%d/%d idle=%ums total=%ums)\n",
				tag, errno, sess, got, len,
				(unsigned)(now - last_progress_ms),
				(unsigned)(now - t0));
			errno = ETIMEDOUT;
			return -1;
		}

		TFOTA_LOG("recv_exact(%s): error r=%d errno=%d (sess=0x%08" PRIx32 " got=%d/%d)\n",
			  tag, r, errno, sess, got, len);
		return -1;
	}

#if TFOTA_LOG_SPLIT_RECV
	if (calls > 1) {
		TFOTA_LOG("recv_exact: assembled %d bytes in %d recv calls (tag=%s, dt=%ums)\n",
			  len, calls, tag, (unsigned)(tfota_now_ms() - t0));
	}
#endif

	return got;
}

/* ---------------- status reporting ---------------- */

/*
 * Some deployments want to avoid sending DIR STATUS packets during TFOTA.
 * We keep the internal state/progress tracking (used by REGISTER and logs),
 * but optionally suppress UDP status reports to the root.
 *
 *  - TFOTA_SEND_DIR_STATUS=0 : do NOT send DIR STATUS packets (default)
 *  - TFOTA_SEND_DIR_STATUS=1 : send DIR STATUS packets (legacy behavior)
 */
#ifndef TFOTA_SEND_DIR_STATUS
#define TFOTA_SEND_DIR_STATUS 1
#endif

static void tfota_report(nrc_fota_status_t st, uint8_t progress, uint32_t new_fw_ver)
{
	/* Always keep the local state up-to-date (REGISTER uses these). */
	g_last_report_state = st;
	g_last_report_pct = progress;
	g_last_report_ms = tfota_now_ms();

#if !TFOTA_SEND_DIR_STATUS
	(void)new_fw_ver;
	return;
#endif

	uint32_t root_ip = tfota_get_root_ip_nbo();
	if (!root_ip)
		return;

	uint8_t self_mac[6];
	if (tfota_get_self_mac(self_mac) < 0)
		return;

	uint32_t node_id = make_node_id_from_mac(self_mac);

	/* Root matches by MAC; node_id is nice-to-have. */
	send_status_to_root(root_ip, self_mac, node_id, g_session, st, progress, new_fw_ver);
}

static void tfota_report_throttled(nrc_fota_status_t st, uint8_t progress, uint32_t new_fw_ver)
{
	/* Always report terminal states immediately */
	if (st != NRC_FOTA_STATUS_IN_PROGRESS) {
		g_last_report_state = st;
		g_last_report_pct = progress;
		g_last_report_ms = tfota_now_ms();
		tfota_report(st, progress, new_fw_ver);
		return;
	}

	uint32_t now = tfota_now_ms();
	bool send_it = false;

	if (g_last_report_state != st) {
		send_it = true;
	} else if (progress >= 100) {
		send_it = true;
	} else if ((uint8_t)(progress - g_last_report_pct) >= TFOTA_STATUS_PCT_STEP) {
		send_it = true;
	} else if ((now - g_last_report_ms) >= TFOTA_STATUS_MIN_INTERVAL_MS) {
		send_it = true;
	}

	if (!send_it)
		return;

	g_last_report_state = st;
	g_last_report_pct = progress;
	g_last_report_ms = now;
	tfota_report(st, progress, new_fw_ver);
}

/* ---------------- TFOTA ACK (app-level) ---------------- */

static int send_all_retry(int sock, const void *buf, int len)
{
	const uint8_t *p = (const uint8_t *)buf;
	uint32_t waited_ms = 0;

	while (len > 0) {
		int n = send(sock, p, len, 0);
		if (n < 0) {
			if (errno == ENOMEM || errno == EWOULDBLOCK || errno == EAGAIN) {
				if (waited_ms >= 2000) /* cap retry window */
					return -1;
				_delay_ms(10);
				waited_ms += 10;
				continue;
			}
			return -1;
		}
		if (n == 0)
			return -1;
		p += n;
		len -= n;
		waited_ms = 0;
	}
	return 0;
}

static int tfota_send_ack(int sock, uint32_t session_id, uint32_t written,
			  nrc_fota_status_t st, uint8_t progress)
{
	nrc_fota_ack_t ack;
	memset(&ack, 0, sizeof(ack));
	ack.hdr.magic = NRC_MAGIC_FOTA;
	ack.hdr.type = NRC_FOTA_MSG_ACK;
	ack.hdr.len = (uint16_t)sizeof(ack);
	ack.hdr.seq = 0;
	ack.hdr.session_id = session_id;

	ack.written = written;
	ack.next_offset = written;
	ack.progress_percent = progress;
	ack.status = (uint8_t)st;

	if (send_all_retry(sock, &ack, (int)sizeof(ack)) < 0) {
		TFOTA_LOG("send_all(ACK) failed errno=%d sess=0x%08" PRIx32 " written=%" PRIu32 "\n",
			  errno, session_id, written);
		return -1;
	}
	return 0;
}

/* ---------------- message handlers ---------------- */

static void tfota_handle_start(const nrc_fota_start_t *st)
{
	/* Safety: accept START only if app name matches (when provided). */
	const char *my_app = (const char *)nrc_get_app_name();
	if (!my_app)
		my_app = "";
	if (st->target_app_name[0]) {
		if (strncmp(st->target_app_name, my_app, NRC_APP_NAME_MAX) != 0) {
			TFOTA_LOG("RX START rejected: target_app='%s' my_app='%s'\n",
				 st->target_app_name, my_app);

			/* Report FAILED so Root can retry/skip cleanly. */
			g_session = st->hdr.session_id;
			g_written = 0;
			g_fw_len = st->fw_len;
			g_fw_crc = st->fw_crc;
			tfota_report_throttled(NRC_FOTA_STATUS_FAILED, 0, 0);
			if (g_client_sock >= 0)
				tfota_send_ack(g_client_sock, g_session, 0, NRC_FOTA_STATUS_FAILED, 0);

			if (g_client_sock >= 0) {
				close(g_client_sock);
				g_client_sock = -1;
			}
			g_session = 0;
			return;
		}
	}

	g_session = st->hdr.session_id;
	g_new_fw_ver = st->fw_ver_packed;
	g_fw_len = st->fw_len;
	g_fw_crc = st->fw_crc;

	g_chunk_size = st->chunk_size;
	if (g_chunk_size == 0 || g_chunk_size > TFOTA_CHUNK_MAX)
		g_chunk_size = TFOTA_CHUNK_MAX;

	g_written = 0;
	g_last_report_ms = 0;
	g_last_report_pct = 0;
	g_last_report_state = NRC_FOTA_STATUS_IDLE;

	TFOTA_LOG("RX START sess=0x%08" PRIx32 " ver=0x%08" PRIx32 " len=%" PRIu32 " crc=0x%08" PRIx32 " chunk=%" PRIu32 " app='%s'\n",
		  g_session, g_new_fw_ver, g_fw_len, g_fw_crc, g_chunk_size,
		  st->target_app_name);

	uint32_t t0 = tfota_now_ms();
	nrc_fota_erase();
	uint32_t dt = tfota_now_ms() - t0;
	TFOTA_LOG("flash erase done in %u ms\n", (unsigned)dt);

	tfota_report_throttled(NRC_FOTA_STATUS_IN_PROGRESS, 0, 0);
	if (g_client_sock >= 0)
		tfota_send_ack(g_client_sock, g_session, g_written, NRC_FOTA_STATUS_IN_PROGRESS, 0);
}

static void tfota_handle_chunk(const nrc_fota_chunk_t *ch)
{
	if (ch->hdr.session_id != g_session) {
		TFOTA_LOG("drop CHUNK: session mismatch rx=0x%08" PRIx32 " cur=0x%08" PRIx32 "\n",
			  ch->hdr.session_id, g_session);
		return;
	}

	if (ch->payload_len == 0) {
		TFOTA_LOG("drop CHUNK: payload_len=0\n");
		return;
	}

	if (ch->payload_len > g_chunk_size) {
		TFOTA_LOG("drop CHUNK: payload_len=%u > chunk_size=%" PRIu32 "\n",
			  (unsigned)ch->payload_len, g_chunk_size);
		return;
	}

	/* With stop-and-wait client, expect strictly sequential offsets. */
	if (ch->offset != g_written) {
		TFOTA_LOG("CHUNK out-of-order sess=0x%08" PRIx32 " rx_off=%" PRIu32 " expected=%" PRIu32 " n=%u\n",
			  ch->hdr.session_id, ch->offset, g_written, (unsigned)ch->payload_len);

		/* Re-ACK current state so client can re-send the expected chunk. */
		uint8_t pct = (g_fw_len) ? (uint8_t)((g_written * 100ULL) / g_fw_len) : 0;
		if (pct > 100) pct = 100;
		if (g_client_sock >= 0)
			tfota_send_ack(g_client_sock, g_session, g_written, NRC_FOTA_STATUS_IN_PROGRESS, pct);
		return;
	}

	uint32_t t0 = tfota_now_ms();
	nrc_fota_write(ch->offset, (uint8_t *)ch->payload, ch->payload_len);
	uint32_t dt = tfota_now_ms() - t0;

	if (dt >= TFOTA_LOG_SLOW_FLASH_MS) {
		TFOTA_LOG("flash write slow off=%" PRIu32 " n=%u dt=%u ms\n",
			  ch->offset, (unsigned)ch->payload_len, (unsigned)dt);
	}

	if (TFOTA_FLASH_WRITE_YIELD_MS)
		_delay_ms(TFOTA_FLASH_WRITE_YIELD_MS);

	uint32_t end = ch->offset + ch->payload_len;
	if (end > g_written)
		g_written = end;

	uint8_t pct = (g_fw_len) ? (uint8_t)((g_written * 100ULL) / g_fw_len) : 0;
	if (pct > 100) pct = 100;

	tfota_report_throttled(NRC_FOTA_STATUS_IN_PROGRESS, pct, 0);
	if (g_client_sock >= 0)
		tfota_send_ack(g_client_sock, g_session, g_written, NRC_FOTA_STATUS_IN_PROGRESS, pct);
}

static void tfota_handle_end(const nrc_fota_hdr_t *hdr)
{
	if (hdr->session_id != g_session) {
		TFOTA_LOG("drop END: session mismatch rx=0x%08" PRIx32 " cur=0x%08" PRIx32 "\n",
			  hdr->session_id, g_session);
		return;
	}

	TFOTA_LOG("RX END sess=0x%08" PRIx32 " written=%" PRIu32 "/%" PRIu32 "\n",
		  g_session, g_written, g_fw_len);

	if (g_written < g_fw_len) {
		TFOTA_LOG("END FAIL: incomplete written=%" PRIu32 " fw_len=%" PRIu32 "\n", g_written, g_fw_len);
		tfota_report(NRC_FOTA_STATUS_FAILED, 0, 0);
		if (g_client_sock >= 0)
			tfota_send_ack(g_client_sock, g_session, g_written, NRC_FOTA_STATUS_FAILED, 0);
		return;
	}

	nrc_fota_set_info(g_fw_len, g_fw_crc);

	TFOTA_LOG("READY_TO_REBOOT sess=0x%08" PRIx32 " len=%" PRIu32 " crc=0x%08" PRIx32 "\n",
		  g_session, g_fw_len, g_fw_crc);

	tfota_report(NRC_FOTA_STATUS_READY_TO_REBOOT, 100, 0);
	if (g_client_sock >= 0)
		tfota_send_ack(g_client_sock, g_session, g_written, NRC_FOTA_STATUS_READY_TO_REBOOT, 100);
}

static void tfota_handle_reboot(const nrc_fota_hdr_t *hdr)
{
	if (hdr->session_id != g_session) {
		TFOTA_LOG("drop REBOOT: session mismatch rx=0x%08" PRIx32 " cur=0x%08" PRIx32 "\n",
			  hdr->session_id, g_session);
		return;
	}

	TFOTA_LOG("RX REBOOT sess=0x%08" PRIx32 "\n", g_session);

	tfota_report(NRC_FOTA_STATUS_REBOOTING, 100, 0);

	TFOTA_LOG("REBOOT sess=0x%08" PRIx32 "\n", g_session);
	nrc_fota_update_done();

	while (1);
}

static void tfota_report_failed_if_needed(const char *reason)
{
	/* Only meaningful after START. */
	if (g_session == 0 || g_fw_len == 0)
		return;

	/* If we've already reached a terminal state, don't override it. */
	if (g_last_report_state == NRC_FOTA_STATUS_READY_TO_REBOOT ||
	    g_last_report_state == NRC_FOTA_STATUS_REBOOTING ||
	    g_last_report_state == NRC_FOTA_STATUS_FAILED) {
		return;
	}

	uint8_t pct = (g_fw_len) ? (uint8_t)((g_written * 100ULL) / g_fw_len) : 0;
	if (pct > 100) pct = 100;

	TFOTA_LOG("ABORT %s (sess=0x%08" PRIx32 " written=%" PRIu32 "/%" PRIu32 ")\n",
			reason ? reason : "", g_session, g_written, g_fw_len);

	/* Report FAILED so Root can retry. */
	g_last_report_state = NRC_FOTA_STATUS_FAILED;
	g_last_report_pct = pct;
	g_last_report_ms = tfota_now_ms();
	tfota_report(NRC_FOTA_STATUS_FAILED, pct, 0);

	/* Clear local state so REGISTER/telemetry won't look like we're still busy. */
	g_session = 0;
	g_fw_len = 0;
	g_fw_crc = 0;
	g_written = 0;
	g_last_report_state = NRC_FOTA_STATUS_IDLE;
	g_last_report_pct = 0;
	g_last_report_ms = tfota_now_ms();
}

/* ---------------- server task ---------------- */

static void tfota_server_task(void *arg)
{
	(void)arg;

	int s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0)
		vTaskDelete(NULL);

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(app_tfota_data_port());
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		TFOTA_LOG("bind failed errno=%d\n", errno);
		close(s);
		vTaskDelete(NULL);
	}

	if (listen(s, 4) < 0) {
		TFOTA_LOG("listen failed errno=%d\n", errno);
		close(s);
		vTaskDelete(NULL);
	}

	TFOTA_LOG("listening on TCP port=%u\n", (unsigned)app_tfota_data_port());

	while (1) {
		struct sockaddr_in peer;
		socklen_t pl = sizeof(peer);
		memset(&peer, 0, sizeof(peer));

		int c = accept(s, (struct sockaddr *)&peer, &pl);
		if (c < 0)
			continue;

		tfota_print_ip_port("accept from", peer.sin_addr.s_addr, peer.sin_port);

		/* Help lwIP keep the pipe moving */
		{
			int one = 1;
			setsockopt(c, IPPROTO_TCP, TCP_NODELAY, &one, sizeof(one));

			/* Best-effort: not all lwIP configs honor these */
			int rcv = 16 * 1024;
			int snd = 16 * 1024;
			setsockopt(c, SOL_SOCKET, SO_RCVBUF, &rcv, sizeof(rcv));
			setsockopt(c, SOL_SOCKET, SO_SNDBUF, &snd, sizeof(snd));

			struct timeval tv;
			tv.tv_sec = TFOTA_TCP_RCVTIMEO_MS / 1000;
			tv.tv_usec = (TFOTA_TCP_RCVTIMEO_MS % 1000) * 1000;
			setsockopt(c, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
		}

		g_client_sock = c;
		g_session = 0;
		g_written = 0;
		g_fw_len = 0;
		g_fw_crc = 0;

		while (1) {
			nrc_fota_hdr_t hdr;

			int r = recv_exact(c, &hdr, (int)sizeof(hdr), "HDR", g_session);
			if (r != (int)sizeof(hdr)) {
				TFOTA_LOG("recv(HDR) failed r=%d errno=%d (sess=0x%08" PRIx32 ")\n",
					  r, errno, g_session);
				break;
			}

			if (hdr.magic != NRC_MAGIC_FOTA || hdr.len < sizeof(hdr)) {
				TFOTA_LOG("bad hdr: magic=0x%08" PRIx32 " type=%u(%s) len=%u sess=0x%08" PRIx32 "\n",
					  hdr.magic, (unsigned)hdr.type, tfota_type_str(hdr.type),
					  (unsigned)hdr.len, hdr.session_id);
				break;
			}

			if (hdr.type == NRC_FOTA_MSG_START) {
				nrc_fota_start_t st;
				memcpy(&st.hdr, &hdr, sizeof(hdr));

				int remain = (int)sizeof(st) - (int)sizeof(hdr);
				r = recv_exact(c, ((uint8_t *)&st) + sizeof(hdr), remain, "START_PAYLOAD", hdr.session_id);
				if (r != remain) {
					TFOTA_LOG("recv(START) failed r=%d/%d errno=%d\n", r, remain, errno);
					break;
				}

				tfota_handle_start(&st);

			} else if (hdr.type == NRC_FOTA_MSG_CHUNK) {
				if (hdr.len > (sizeof(nrc_fota_chunk_t) + TFOTA_CHUNK_MAX)) {
					TFOTA_LOG("bad CHUNK len=%u > %u\n",
						  (unsigned)hdr.len, (unsigned)(sizeof(nrc_fota_chunk_t) + TFOTA_CHUNK_MAX));
					break;
				}

				uint8_t buf[sizeof(nrc_fota_chunk_t) + TFOTA_CHUNK_MAX];
				nrc_fota_chunk_t *ch = (nrc_fota_chunk_t *)buf;

				memcpy(&ch->hdr, &hdr, sizeof(hdr));
				int remain = (int)hdr.len - (int)sizeof(hdr);
				if (remain < 8) {
					TFOTA_LOG("bad CHUNK remain=%d (len=%u)\n", remain, (unsigned)hdr.len);
					break;
				}

				r = recv_exact(c, buf + sizeof(hdr), remain, "CHUNK_PAYLOAD", hdr.session_id);
				if (r != remain) {
					TFOTA_LOG("recv(CHUNK) failed r=%d/%d errno=%d (sess=0x%08" PRIx32 ")\n",
						  r, remain, errno, hdr.session_id);
					break;
				}

				/* basic trace for first chunk and every 256KB */
				if (ch->offset == 0 || (ch->offset % (256 * 1024)) == 0) {
					TFOTA_LOG("RX CHUNK sess=0x%08" PRIx32 " off=%" PRIu32 " n=%u (hdr.len=%u)\n",
						  ch->hdr.session_id, ch->offset, (unsigned)ch->payload_len, (unsigned)hdr.len);
				}

				tfota_handle_chunk(ch);

			} else if (hdr.type == NRC_FOTA_MSG_END) {
				tfota_handle_end(&hdr);

			} else if (hdr.type == NRC_FOTA_MSG_REBOOT) {
				tfota_handle_reboot(&hdr);

			} else {
				TFOTA_LOG("unknown msg type=%u len=%u sess=0x%08" PRIx32 "\n",
					  (unsigned)hdr.type, (unsigned)hdr.len, hdr.session_id);
				break;
			}
		}

		TFOTA_LOG("close connection (sess=0x%08" PRIx32 " written=%" PRIu32 "/%" PRIu32 ")\n",
			  g_session, g_written, g_fw_len);

		/* If we drop the TCP connection mid-transfer, make it explicit.
		 * Otherwise Root will keep seeing IN_PROGRESS and never retry.
		 */
		tfota_report_failed_if_needed("tcp disconnected");

		g_client_sock = -1;
		close(c);
	}
}

void start_tfota_server(void)
{
	xTaskCreate(tfota_server_task,
		    "tfota_srv",
		    4096,
		    NULL,
		    tskIDLE_PRIORITY + 2,
		    NULL);
}
