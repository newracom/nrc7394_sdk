/*
	nrc_fota_rootd.c

	Linux/OpenWRT "Root" helper for NRC multi-role TFOTA:
	- Listens for directory REGISTER from relays (UDP 60000)
	- Loads target firmware metadata from a version.json
	- If update is needed, pushes firmware to the relay's TFOTA TCP server (60010)

	Build (OpenWRT):
		opkg update
		opkg install libjson-c libjson-c-dev
		gcc -Wall -Wextra -O2 -o nrc_fota_rootd nrc_fota_rootd_pthread.c -ljson-c -pthread

	Run:
		./nrc_fota_rootd -j /tmp/version.json -F /tmp/firmware_dir -v

	Reload version.json (and re-stat firmware) without restart:
		kill -HUP $(pidof nrc_fota_rootd)

	Notes:
	- Wire protocol structs mirror hvac_wifi_comm/multi_role_proto.h
	- Reference firmware uses host endianness (little-endian) for fields inside payload.
	- ipv4_addr inside REGISTER is NBO (network byte order) per the firmware.
*/

#define _GNU_SOURCE

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <pthread.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>

#include <json-c/json.h>

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))
#endif

/* ---- Protocol (from multi_role_proto.h) ---- */

#define NRC_APP_NAME_MAX	16

#define NRC_FOTA_CTRL_PORT	60000	/* UDP directory */
#define NRC_FOTA_DATA_PORT	60010	/* TCP firmware */

#define NRC_MAGIC_DIR		0x4E524344	/* 'NRCD' */
#define NRC_MAGIC_FOTA		0x4E524346	/* 'NRCF' */

typedef enum {
	NRC_DIR_MSG_REGISTER = 1,
	NRC_DIR_MSG_STATUS,
	NRC_DIR_MSG_GET_LIST,
	NRC_DIR_MSG_LIST_RESP,
	NRC_DIR_MSG_ACK,
	NRC_DIR_MSG_HEARTBEAT
} nrc_dir_msg_type_t;

typedef enum {
	NRC_FOTA_MSG_START = 1,
	NRC_FOTA_MSG_CHUNK,
	NRC_FOTA_MSG_END,
	NRC_FOTA_MSG_REBOOT,
	NRC_FOTA_MSG_ACK
} nrc_fota_msg_type_t;

typedef enum {
	NRC_FOTA_STATUS_IDLE = 0,
	NRC_FOTA_STATUS_IN_PROGRESS,
	NRC_FOTA_STATUS_READY_TO_REBOOT,
	NRC_FOTA_STATUS_REBOOTING,
	NRC_FOTA_STATUS_DONE,
	NRC_FOTA_STATUS_FAILED
} nrc_fota_status_t;

typedef struct __attribute__((packed)) {
	uint32_t	magic;
	uint16_t	type;
	uint16_t	len;
	uint32_t	seq;
} nrc_dir_hdr_t;

typedef struct __attribute__((packed)) {
	nrc_dir_hdr_t	hdr;
	uint32_t	node_id;
	uint8_t		mac[6];
	uint8_t		parent_mac[6];
	uint8_t		role;
	uint8_t		hop;
	uint16_t	rsvd0;
	uint32_t	ipv4_addr;			/* NBO */
	uint32_t	fw_ver_packed;			/* app-defined packed ver */
	char		app_name[NRC_APP_NAME_MAX];
} nrc_dir_register_t;

typedef struct __attribute__((packed)) {
	nrc_dir_hdr_t	hdr;
	uint16_t	acked_type;
	uint16_t	code;
	uint32_t	dir_version;
	uint32_t	node_id;
	uint8_t		mac[6];
	uint8_t		rsvd0[2];
} nrc_dir_ack_t;

typedef struct __attribute__((packed)) {
	uint32_t	magic;
	uint16_t	type;
	uint16_t	len;
	uint32_t	seq;
	uint32_t	session_id;
} nrc_fota_hdr_t;

typedef struct __attribute__((packed)) {
	nrc_fota_hdr_t	hdr;
	uint32_t	fw_ver_packed;
	uint32_t	fw_len;
	uint32_t	fw_crc;
	uint32_t	chunk_size;
	char		target_app_name[NRC_APP_NAME_MAX];
} nrc_fota_start_t;

typedef struct __attribute__((packed)) {
	nrc_fota_hdr_t	hdr;
	uint32_t	offset;
	uint16_t	payload_len;
	uint16_t	rsvd0;
	uint8_t		payload[];
} nrc_fota_chunk_t;

typedef struct __attribute__((packed)) {
	nrc_fota_hdr_t	hdr;
	uint32_t	written;
	uint32_t	next_offset;
	uint8_t		progress_percent;
	uint8_t		status;
	uint16_t	rsvd0;
} nrc_fota_ack_t;

/* ---- Roles (from multi_role_config.h) ---- */

typedef enum {
	ROLE_UNDEFINED = -1,
	ROLE_SOFTAP,
	ROLE_STATION,
	ROLE_RELAY
} system_role_t;

/* ---- version.json meta ---- */

typedef struct {
	char	version_str[32];	/* "1.1.0" */
	uint32_t	version_packed;	/* major<<24|minor<<16|patch<<8 */
	uint32_t	crc32;
	int	force;
	char	fw_name[256];
	char	app_name[64];		/* optional; empty means "don't enforce" */
	char	fw_path[512];		/* resolved full path */
	uint32_t	fw_len;
	uint32_t	chunk_size;
} fota_meta_t;

/* ---- globals ---- */

static volatile sig_atomic_t g_reload = 0;
static int g_verbose = 0;
static char g_version_json_path[512];
static char g_firmware_dir[512];

static pthread_mutex_t g_meta_lock = PTHREAD_MUTEX_INITIALIZER;
static fota_meta_t g_meta;

/* ---- util ---- */

static uint64_t now_ms(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (uint64_t)ts.tv_sec * 1000ULL + (uint64_t)ts.tv_nsec / 1000000ULL;
}

static void logi(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vsyslog(LOG_INFO, fmt, ap);
	va_end(ap);

	if (g_verbose) {
		va_start(ap, fmt);
		vfprintf(stderr, fmt, ap);
		fprintf(stderr, "\n");
		va_end(ap);
	}
}

static void loge(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vsyslog(LOG_ERR, fmt, ap);
	va_end(ap);

	if (g_verbose) {
		va_start(ap, fmt);
		vfprintf(stderr, fmt, ap);
		fprintf(stderr, "\n");
		va_end(ap);
	}
}

static void on_sighup(int sig)
{
	(void)sig;
	g_reload = 1;
}

static void mac_to_str(const uint8_t mac[6], char out[18])
{
	snprintf(out, 18, "%02X:%02X:%02X:%02X:%02X:%02X",
		mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

static int parse_u8(const char *s, int *out)
{
	char *end = NULL;
	long v = strtol(s, &end, 10);
	if (!s || s[0] == '\0' || (end && *end != '\0'))
		return -1;
	if (v < 0 || v > 255)
		return -1;
	*out = (int)v;
	return 0;
}

static uint32_t pack_ver_str(const char *ver_str)
{
	/* "M.m.p" -> (M<<24)|(m<<16)|(p<<8) */
	int m = 0, n = 0, p = 0;
	if (!ver_str || !ver_str[0])
		return 0;

	char tmp[64];
	snprintf(tmp, sizeof(tmp), "%s", ver_str);

	char *save = NULL;
	char *tok = strtok_r(tmp, ".", &save);
	if (tok && parse_u8(tok, &m) == 0) {
		tok = strtok_r(NULL, ".", &save);
		if (tok) parse_u8(tok, &n);
		tok = strtok_r(NULL, ".", &save);
		if (tok) parse_u8(tok, &p);
	}

	return ((uint32_t)m << 24) | ((uint32_t)n << 16) | ((uint32_t)p << 8);
}

/* ---- CRC32 (standard Ethernet/ZIP) ---- */

static uint32_t crc32_table[256];
static int crc32_init_done = 0;

static void crc32_init(void)
{
	for (uint32_t i = 0; i < 256; i++) {
		uint32_t c = i;
		for (int j = 0; j < 8; j++)
			c = (c & 1) ? (0xEDB88320U ^ (c >> 1)) : (c >> 1);
		crc32_table[i] = c;
	}
	crc32_init_done = 1;
}

static uint32_t crc32_file(const char *path, uint32_t *len_out)
{
	if (!crc32_init_done)
		crc32_init();

	int fd = open(path, O_RDONLY);
	if (fd < 0)
		return 0;

	uint8_t buf[4096];
	ssize_t n;
	uint32_t crc = 0xFFFFFFFFU;
	uint32_t total = 0;

	while ((n = read(fd, buf, sizeof(buf))) > 0) {
		total += (uint32_t)n;
		for (ssize_t i = 0; i < n; i++)
			crc = crc32_table[(crc ^ buf[i]) & 0xFF] ^ (crc >> 8);
	}

	close(fd);

	if (len_out)
		*len_out = total;

	return crc ^ 0xFFFFFFFFU;
}

static int parse_hex_u32(const char *hex, uint32_t *out)
{
	if (!hex || !out)
		return -1;
	char *end = NULL;
	unsigned long v = strtoul(hex, &end, 16);
	if (hex[0] == '\0' || (end && *end != '\0'))
		return -1;
	*out = (uint32_t)v;
	return 0;
}

static void dirname_of(const char *path, char out[512])
{
	/* simple, no libgen */
	snprintf(out, 512, "%s", path ? path : "");
	char *slash = strrchr(out, '/');
	if (slash)
		*slash = '\0';
	else
		snprintf(out, 512, ".");
}

static int join_path(char *out, size_t out_sz, const char *dir, const char *name)
{
	if (!out || out_sz == 0 || !name)
		return -EINVAL;
	if (!dir || !dir[0]) {
		int req = snprintf(NULL, 0, "%s", name);
		if (req < 0) return -EINVAL;
		if ((size_t)req >= out_sz) return -ENAMETOOLONG;
		snprintf(out, out_sz, "%s", name);
		return 0;
	}

	int need_slash = (dir[strlen(dir) - 1] != '/');
	int req = snprintf(NULL, 0, need_slash ? "%s/%s" : "%s%s", dir, name);
	if (req < 0) return -EINVAL;
	if ((size_t)req >= out_sz) return -ENAMETOOLONG;
	snprintf(out, out_sz, need_slash ? "%s/%s" : "%s%s", dir, name);
	return 0;
}

/* ---- version.json loader ---- */

static int load_version_json(const char *path, const char *fw_dir_override, fota_meta_t *out)
{
	if (!path || !out)
		return -1;

	FILE *fp = fopen(path, "rb");
	if (!fp) {
		loge("Failed to open %s (%s)", path, strerror(errno));
		return -1;
	}

	fseek(fp, 0, SEEK_END);
	long sz = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	if (sz <= 0 || sz > 64 * 1024) {
		fclose(fp);
		loge("Invalid version.json size: %ld", sz);
		return -1;
	}

	char *buf = (char *)calloc(1, (size_t)sz + 1);
	if (!buf) {
		fclose(fp);
		loge("OOM reading version.json");
		return -1;
	}

	if (fread(buf, 1, (size_t)sz, fp) != (size_t)sz) {
		free(buf);
		fclose(fp);
		loge("Failed to read version.json");
		return -1;
	}
	fclose(fp);

	struct json_object *root = json_tokener_parse(buf);
	free(buf);
	if (!root) {
		loge("JSON parse failed: %s", path);
		return -1;
	}

	memset(out, 0, sizeof(*out));
	out->chunk_size = 1024;

	struct json_object *jv = NULL, *jc = NULL, *jf = NULL, *jn = NULL, *ja = NULL, *jcs = NULL;

	if (json_object_object_get_ex(root, "version", &jv) && json_object_is_type(jv, json_type_string))
		snprintf(out->version_str, sizeof(out->version_str), "%s", json_object_get_string(jv));
	else
		snprintf(out->version_str, sizeof(out->version_str), "0.0.0");

	out->version_packed = pack_ver_str(out->version_str);

	if (json_object_object_get_ex(root, "crc", &jc) && json_object_is_type(jc, json_type_string)) {
		const char *s = json_object_get_string(jc);
		if (parse_hex_u32(s, &out->crc32) != 0)
			out->crc32 = 0;
	}

	out->force = 0;
	if (json_object_object_get_ex(root, "force", &jf)) {
		if (json_object_is_type(jf, json_type_string)) {
			const char *s = json_object_get_string(jf);
			out->force = (s && atoi(s) != 0) ? 1 : 0;
		} else if (json_object_is_type(jf, json_type_int)) {
			out->force = (json_object_get_int(jf) != 0) ? 1 : 0;
		}
	}

	if (json_object_object_get_ex(root, "fw_name", &jn) && json_object_is_type(jn, json_type_string))
		snprintf(out->fw_name, sizeof(out->fw_name), "%s", json_object_get_string(jn));

	if (json_object_object_get_ex(root, "app_name", &ja) && json_object_is_type(ja, json_type_string))
		snprintf(out->app_name, sizeof(out->app_name), "%s", json_object_get_string(ja));

	if (json_object_object_get_ex(root, "chunk_size", &jcs)) {
		if (json_object_is_type(jcs, json_type_int)) {
			int cs = json_object_get_int(jcs);
			if (cs > 0 && cs <= 1024)
				out->chunk_size = (uint32_t)cs;
		}
	}

	json_object_put(root);

	char fwdir[512];
	if (fw_dir_override && fw_dir_override[0])
		snprintf(fwdir, sizeof(fwdir), "%s", fw_dir_override);
	else
		dirname_of(path, fwdir);

	if (join_path(out->fw_path, sizeof(out->fw_path), fwdir, out->fw_name) != 0) {
		loge("Firmware path too long: dir='%s' name='%s'", fwdir, out->fw_name);
		return -1;
	}

	out->fw_len = 0;
	uint32_t calc_crc = crc32_file(out->fw_path, &out->fw_len);
	if (calc_crc == 0 || out->fw_len == 0) {
		loge("Firmware file not readable: %s", out->fw_path);
		return -1;
	}

	if (out->crc32 == 0) {
		out->crc32 = calc_crc;
	} else if (out->crc32 != calc_crc) {
		loge("WARNING: version.json crc(0x%08" PRIx32 ") != file crc(0x%08" PRIx32 ") for %s",
			out->crc32, calc_crc, out->fw_path);
		out->crc32 = calc_crc;
	}

	logi("Loaded version.json: ver=%s packed=0x%08" PRIx32 " force=%d fw=%s len=%" PRIu32 " crc=0x%08" PRIx32 " app='%s' chunk=%" PRIu32,
		out->version_str, out->version_packed, out->force, out->fw_path,
		out->fw_len, out->crc32, out->app_name, out->chunk_size);

	return 0;
}

/* ---- TCP helpers ---- */

static int send_all(int sock, const void *buf, int len)
{
	const uint8_t *p = (const uint8_t *)buf;
	while (len > 0) {
		int n = send(sock, p, len, 0);
		if (n > 0) {
			p += n;
			len -= n;
			continue;
		}
		if (n < 0) {
			if (errno == EINTR)
				continue;
			if (errno == EAGAIN || errno == EWOULDBLOCK) {
				usleep(10 * 1000);
				continue;
			}
			return -1;
		}
		return -1;
	}
	return 0;
}

static int recv_exact_deadline(int sock, void *buf, int len, int deadline_ms)
{
	uint8_t *p = (uint8_t *)buf;
	int left = len;

	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 200 * 1000;
	setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

	uint64_t start = now_ms();
	while (left > 0) {
		int n = recv(sock, p, left, 0);
		if (n > 0) {
			p += n;
			left -= n;
			continue;
		}
		if (n == 0)
			return -1;
		if (errno == EAGAIN || errno == EWOULDBLOCK) {
			if ((int)(now_ms() - start) >= deadline_ms)
				return -1;
			continue;
		}
		if (errno == EINTR)
			continue;
		return -1;
	}
	return 0;
}

static int wait_fota_ack(int sock, uint32_t session_id, uint32_t expected_written)
{
	int deadline_ms = 30000;
	nrc_fota_hdr_t hdr;
	memset(&hdr, 0, sizeof(hdr));

	if (recv_exact_deadline(sock, &hdr, (int)sizeof(hdr), deadline_ms) < 0)
		return -1;

	if (hdr.magic != NRC_MAGIC_FOTA || hdr.type != NRC_FOTA_MSG_ACK)
		return -1;
	if (hdr.len != (uint16_t)sizeof(nrc_fota_ack_t))
		return -1;
	if (hdr.session_id != session_id)
		return -1;

	nrc_fota_ack_t ack;
	memset(&ack, 0, sizeof(ack));
	memcpy(&ack.hdr, &hdr, sizeof(hdr));

	int remain = (int)sizeof(ack) - (int)sizeof(hdr);
	if (recv_exact_deadline(sock, ((uint8_t *)&ack) + sizeof(hdr), remain, deadline_ms) < 0)
		return -1;

	if (ack.status == (uint8_t)NRC_FOTA_STATUS_FAILED)
		return -1;
	if (ack.written < expected_written)
		return -1;

	return 0;
}

static int g_data_port = NRC_FOTA_DATA_PORT; /* TCP firmware port */

static uint32_t make_session_id(void)
{
	uint32_t t = (uint32_t)now_ms();
	return (t ^ (t << 16) ^ 0xA5A55A5A);
}

static int tfota_push_file(uint32_t relay_ip_nbo, const fota_meta_t *m, const char node_app[NRC_APP_NAME_MAX])
{
	if (!relay_ip_nbo || !m || !m->fw_path[0] || !m->fw_len || !m->crc32)
		return -1;

	int fd = open(m->fw_path, O_RDONLY);
	if (fd < 0) {
		loge("open fw failed: %s (%s)", m->fw_path, strerror(errno));
		return -1;
	}

	uint32_t session_id = make_session_id();
	uint32_t seq = 1;

	int s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		close(fd);
		return -1;
	}

	/* socket tuning */
	{
		int v;
		v = 1;
		setsockopt(s, IPPROTO_TCP, TCP_NODELAY, &v, sizeof(v));
		v = 64 * 1024;
		setsockopt(s, SOL_SOCKET, SO_SNDBUF, &v, sizeof(v));
		v = 64 * 1024;
		setsockopt(s, SOL_SOCKET, SO_RCVBUF, &v, sizeof(v));
	}

	struct sockaddr_in to;
	memset(&to, 0, sizeof(to));
	to.sin_family = AF_INET;
	to.sin_port = htons((uint16_t)g_data_port);
	to.sin_addr.s_addr = relay_ip_nbo;

	if (connect(s, (struct sockaddr *)&to, sizeof(to)) < 0) {
		loge("[TFOTA_CLI] connect failed (%s)", strerror(errno));
		close(s);
		close(fd);
		return -1;
	}

	/* START */
	nrc_fota_start_t st;
	memset(&st, 0, sizeof(st));
	st.hdr.magic = NRC_MAGIC_FOTA;
	st.hdr.type = NRC_FOTA_MSG_START;
	st.hdr.len = (uint16_t)sizeof(st);
	st.hdr.seq = seq++;
	st.hdr.session_id = session_id;
	st.fw_ver_packed = m->version_packed;
	st.fw_len = m->fw_len;
	st.fw_crc = m->crc32;
	st.chunk_size = m->chunk_size;
	/* If version.json didn't provide app_name, mirror node's app name to keep logs/behavior consistent */
	if (m->app_name[0]) {
		snprintf(st.target_app_name, NRC_APP_NAME_MAX, "%.*s", NRC_APP_NAME_MAX - 1, m->app_name);
	} else if (node_app && node_app[0]) {
		snprintf(st.target_app_name, NRC_APP_NAME_MAX, "%.*s", NRC_APP_NAME_MAX - 1, node_app);
	}

	logi("[TFOTA_CLI] START sess=0x%08" PRIx32 " ver=0x%08" PRIx32 " len=%" PRIu32 " crc=0x%08" PRIx32 " chunk=%" PRIu32 " app='%s'",
		session_id, st.fw_ver_packed, st.fw_len, st.fw_crc, st.chunk_size, st.target_app_name);

	if (send_all(s, &st, (int)sizeof(st)) < 0)
		goto fail;
	if (wait_fota_ack(s, session_id, 0) < 0)
		goto fail;

	/* CHUNKS */
	uint32_t chunk = m->chunk_size;
	if (chunk == 0 || chunk > 1024)
		chunk = 1024;

	uint8_t *pkt = (uint8_t *)malloc(sizeof(nrc_fota_chunk_t) + chunk);
	if (!pkt)
		goto fail;

	for (uint32_t off = 0; off < m->fw_len; off += chunk) {
		uint32_t n = m->fw_len - off;
		if (n > chunk)
			n = chunk;

		nrc_fota_chunk_t *ch = (nrc_fota_chunk_t *)pkt;
		memset(ch, 0, sizeof(*ch));
		ch->hdr.magic = NRC_MAGIC_FOTA;
		ch->hdr.type = NRC_FOTA_MSG_CHUNK;
		ch->hdr.seq = seq++;
		ch->hdr.session_id = session_id;
		ch->offset = off;
		ch->payload_len = (uint16_t)n;
		ch->hdr.len = (uint16_t)(sizeof(nrc_fota_chunk_t) + n);

		ssize_t r = pread(fd, ch->payload, n, off);
		if (r != (ssize_t)n) {
			loge("[TFOTA_CLI] pread failed off=%" PRIu32 " n=%" PRIu32 " r=%zd (%s)", off, n, r, strerror(errno));
			free(pkt);
			goto fail;
		}

		if (send_all(s, pkt, (int)ch->hdr.len) < 0) {
			loge("[TFOTA_CLI] send chunk failed off=%" PRIu32 " (%s)", off, strerror(errno));
			free(pkt);
			goto fail;
		}

		if (wait_fota_ack(s, session_id, off + n) < 0) {
			loge("[TFOTA_CLI] ACK timeout/invalid off=%" PRIu32, off);
			free(pkt);
			goto fail;
		}
	}

	free(pkt);

	/* END */
	nrc_fota_hdr_t end;
	memset(&end, 0, sizeof(end));
	end.magic = NRC_MAGIC_FOTA;
	end.type = NRC_FOTA_MSG_END;
	end.len = (uint16_t)sizeof(end);
	end.seq = seq++;
	end.session_id = session_id;

	if (send_all(s, &end, (int)sizeof(end)) < 0)
		goto fail;
	if (wait_fota_ack(s, session_id, m->fw_len) < 0)
		goto fail;

	/* REBOOT */
	nrc_fota_hdr_t rb;
	memset(&rb, 0, sizeof(rb));
	rb.magic = NRC_MAGIC_FOTA;
	rb.type = NRC_FOTA_MSG_REBOOT;
	rb.len = (uint16_t)sizeof(rb);
	rb.seq = seq++;
	rb.session_id = session_id;

	if (send_all(s, &rb, (int)sizeof(rb)) < 0)
		goto fail;

	logi("[TFOTA_CLI] done (sent reboot) sess=0x%08" PRIx32, session_id);
	close(s);
	close(fd);
	return 0;

fail:
	loge("[TFOTA_CLI] failed (sess=0x%08" PRIx32 ")", session_id);
	close(s);
	close(fd);
	return -1;
}

/* ---- directory ACK ---- */

static int send_dir_ack(int udp_sock, const struct sockaddr_in *to, socklen_t tolen,
			const nrc_dir_register_t *reg)
{
	nrc_dir_ack_t ack;
	memset(&ack, 0, sizeof(ack));
	ack.hdr.magic = NRC_MAGIC_DIR;
	ack.hdr.type = NRC_DIR_MSG_ACK;
	ack.hdr.len = (uint16_t)sizeof(ack);
	ack.hdr.seq = reg->hdr.seq;
	ack.acked_type = NRC_DIR_MSG_REGISTER;
	ack.code = 0;
	ack.dir_version = 0;
	ack.node_id = reg->node_id;
	memcpy(ack.mac, reg->mac, 6);

	int rc = sendto(udp_sock, &ack, sizeof(ack), 0, (const struct sockaddr *)to, tolen);
	return (rc == (int)sizeof(ack)) ? 0 : -1;
}

/* ---- relay state (thread-safe) ---- */

typedef struct {
	uint8_t	mac[6];
	int	valid;
	int	inflight;
	uint32_t	backoff_ms;
	uint32_t	last_attempt_ms;
	uint32_t	suppress_until_ms;
	uint32_t	last_target_ver;
} relay_state_t;

#define RELAY_STATE_MAX 64
static relay_state_t g_relays[RELAY_STATE_MAX];
static pthread_mutex_t g_relays_lock = PTHREAD_MUTEX_INITIALIZER;

static relay_state_t *relay_state_get_locked(const uint8_t mac[6])
{
	for (int i = 0; i < RELAY_STATE_MAX; i++) {
		if (g_relays[i].valid && memcmp(g_relays[i].mac, mac, 6) == 0)
			return &g_relays[i];
	}
	for (int i = 0; i < RELAY_STATE_MAX; i++) {
		if (!g_relays[i].valid) {
			g_relays[i].valid = 1;
			memcpy(g_relays[i].mac, mac, 6);
			g_relays[i].inflight = 0;
			g_relays[i].backoff_ms = 5000;
			g_relays[i].last_attempt_ms = 0;
			g_relays[i].suppress_until_ms = 0;
			g_relays[i].last_target_ver = 0;
			return &g_relays[i];
		}
	}
	return NULL;
}

static bool app_name_match_ok(const char *target_app, const char node_app[NRC_APP_NAME_MAX])
{
	if (!target_app || !target_app[0])
		return true;
	if (!node_app || !node_app[0])
		return false;
	return (strncmp(target_app, node_app, NRC_APP_NAME_MAX) == 0);
}

/*
	Update decision:
	- User requested: "Do not worry about version # checking".
	- So we just update if node version != target version, or force=1.
*/
static bool need_update_simple(const fota_meta_t *m, const nrc_dir_register_t *reg)
{
	if (!m || !reg)
		return false;
	if (m->force)
		return true;
	return (reg->fw_ver_packed != m->version_packed);
}

/* ---- event queue ---- */

typedef struct reg_event {
	nrc_dir_register_t reg;
	struct sockaddr_in from;
	socklen_t fromlen;
	uint64_t recv_ms;
	struct reg_event *next;
} reg_event_t;

static pthread_mutex_t g_q_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t g_q_cond = PTHREAD_COND_INITIALIZER;
static reg_event_t *g_q_head = NULL;
static reg_event_t *g_q_tail = NULL;
static int g_q_len = 0;
static int g_q_max = 256;
static int g_stop = 0;

static void queue_push(reg_event_t *ev)
{
	pthread_mutex_lock(&g_q_lock);
	if (g_stop) {
		pthread_mutex_unlock(&g_q_lock);
		free(ev);
		return;
	}
	if (g_q_len >= g_q_max) {
		/* drop oldest to keep listener responsive */
		reg_event_t *old = g_q_head;
		if (old) {
			g_q_head = old->next;
			if (!g_q_head)
				g_q_tail = NULL;
			free(old);
			g_q_len--;
		}
	}
	ev->next = NULL;
	if (!g_q_tail) {
		g_q_head = g_q_tail = ev;
	} else {
		g_q_tail->next = ev;
		g_q_tail = ev;
	}
	g_q_len++;
	pthread_cond_signal(&g_q_cond);
	pthread_mutex_unlock(&g_q_lock);
}

static reg_event_t *queue_pop(void)
{
	pthread_mutex_lock(&g_q_lock);
	while (!g_stop && !g_q_head)
		pthread_cond_wait(&g_q_cond, &g_q_lock);

	reg_event_t *ev = NULL;
	if (g_q_head) {
		ev = g_q_head;
		g_q_head = ev->next;
		if (!g_q_head)
			g_q_tail = NULL;
		ev->next = NULL;
		g_q_len--;
	}
	pthread_mutex_unlock(&g_q_lock);
	return ev;
}

/* ---- threads ---- */

typedef struct {
	int udp_sock;
} listener_arg_t;

static void maybe_reload_meta(void)
{
	if (!g_reload)
		return;
	g_reload = 0;
	fota_meta_t tmp;
	if (load_version_json(g_version_json_path, g_firmware_dir, &tmp) == 0) {
		pthread_mutex_lock(&g_meta_lock);
		g_meta = tmp;
		pthread_mutex_unlock(&g_meta_lock);
		logi("Reloaded version.json");
	} else {
		loge("Reload failed; keeping previous metadata");
	}
}

static void *listener_thread(void *arg)
{
	listener_arg_t *la = (listener_arg_t *)arg;
	uint8_t buf[2048];

	for (;;) {
		if (g_stop)
			break;

		maybe_reload_meta();

		struct sockaddr_in from;
		socklen_t fromlen = sizeof(from);
		ssize_t n = recvfrom(la->udp_sock, buf, sizeof(buf), 0, (struct sockaddr *)&from, &fromlen);
		if (n < 0) {
			if (errno == EINTR)
				continue;
			loge("recvfrom failed (%s)", strerror(errno));
			continue;
		}
		if ((size_t)n < sizeof(nrc_dir_hdr_t))
			continue;

		nrc_dir_hdr_t *hdr = (nrc_dir_hdr_t *)buf;
		if (hdr->magic != NRC_MAGIC_DIR)
			continue;
		if (hdr->type != NRC_DIR_MSG_REGISTER)
			continue;
		if (hdr->len != sizeof(nrc_dir_register_t))
			continue;
		if ((size_t)n < sizeof(nrc_dir_register_t))
			continue;

		nrc_dir_register_t reg;
		memcpy(&reg, buf, sizeof(reg));

		/* ACK quickly (echo seq) */
		(void)send_dir_ack(la->udp_sock, &from, fromlen, &reg);

		char macs[18];
		mac_to_str(reg.mac, macs);
		struct in_addr ina;
		ina.s_addr = reg.ipv4_addr;
		char app[NRC_APP_NAME_MAX + 1];
		memset(app, 0, sizeof(app));
		memcpy(app, reg.app_name, NRC_APP_NAME_MAX);

		logi("[DIR] REGISTER from %s:%u mac=%s role=%u hop=%u fw=0x%08" PRIx32 " app='%s'",
			inet_ntoa(ina), ntohs(from.sin_port), macs, reg.role, reg.hop, reg.fw_ver_packed, app);

		reg_event_t *ev = (reg_event_t *)calloc(1, sizeof(*ev));
		if (!ev)
			continue;
		ev->reg = reg;
		ev->from = from;
		ev->fromlen = fromlen;
		ev->recv_ms = now_ms();
		queue_push(ev);
	}

	return NULL;
}

static void *worker_thread(void *arg)
{
	(void)arg;
	for (;;) {
		if (g_stop)
			break;
		reg_event_t *ev = queue_pop();
		if (!ev)
			continue;

		nrc_dir_register_t *reg = &ev->reg;

		/* Only push to relays */
		if (reg->role != (uint8_t)ROLE_RELAY) {
			free(ev);
			continue;
		}

		/* Snapshot meta */
		fota_meta_t meta;
		pthread_mutex_lock(&g_meta_lock);
		meta = g_meta;
		pthread_mutex_unlock(&g_meta_lock);

		if (!app_name_match_ok(meta.app_name, reg->app_name)) {
			char macs[18];
			mac_to_str(reg->mac, macs);
			char node_app[NRC_APP_NAME_MAX + 1];
			memset(node_app, 0, sizeof(node_app));
			memcpy(node_app, reg->app_name, NRC_APP_NAME_MAX);
			loge("Skip TFOTA for %s: app mismatch (target='%s' node='%s')", macs, meta.app_name, node_app);
			free(ev);
			continue;
		}

		if (!need_update_simple(&meta, reg)) {
			free(ev);
			continue;
		}

		char macs[18];
		mac_to_str(reg->mac, macs);
		struct in_addr ina;
		ina.s_addr = reg->ipv4_addr;
		char ipbuf[64];
		snprintf(ipbuf, sizeof(ipbuf), "%s", inet_ntoa(ina));

		/* Per-relay gating */
		bool do_fota = false;
		pthread_mutex_lock(&g_relays_lock);
		relay_state_t *st = relay_state_get_locked(reg->mac);
		uint64_t now = now_ms();
		if (!st) {
			pthread_mutex_unlock(&g_relays_lock);
			loge("No relay_state slot; skipping %s", macs);
			free(ev);
			continue;
		}

		if (st->inflight) {
			pthread_mutex_unlock(&g_relays_lock);
			/* Another TFOTA already running for this MAC */
			free(ev);
			continue;
		}

		/* Suppress repeated STARTs after successful TFOTA to avoid queued REGISTER duplicates */
		if (st->suppress_until_ms && (uint32_t)now < st->suppress_until_ms && st->last_target_ver == meta.version_packed) {
			uint32_t left = st->suppress_until_ms - (uint32_t)now;
			pthread_mutex_unlock(&g_relays_lock);
			logi("TFOTA suppress for %s (waiting reboot/new version, %u ms left)", macs, left);
			free(ev);
			continue;
		}

		/* Backoff */
		if (st->last_attempt_ms != 0) {
			uint32_t elapsed = (uint32_t)now - st->last_attempt_ms;
			if (elapsed < st->backoff_ms) {
				uint32_t left = st->backoff_ms - elapsed;
				pthread_mutex_unlock(&g_relays_lock);
				logi("Backoff active for %s (next in %u ms)", macs, left);
				free(ev);
				continue;
			}
		}

		st->inflight = 1;
		st->last_attempt_ms = (uint32_t)now;
		do_fota = true;
		pthread_mutex_unlock(&g_relays_lock);

		if (!do_fota) {
			free(ev);
			continue;
		}

		char node_app[NRC_APP_NAME_MAX + 1];
		memset(node_app, 0, sizeof(node_app));
		memcpy(node_app, reg->app_name, NRC_APP_NAME_MAX);

		logi("[TFOTA_CLI] required for %s (%s): node_ver=0x%08" PRIx32 " target=0x%08" PRIx32 " force=%d",
			macs, ipbuf, reg->fw_ver_packed, meta.version_packed, meta.force);

		int rc = tfota_push_file(reg->ipv4_addr, &meta, node_app);

		pthread_mutex_lock(&g_relays_lock);
		st = relay_state_get_locked(reg->mac);
		if (st) {
			st->inflight = 0;
			st->last_attempt_ms = (uint32_t)now_ms();
			if (rc == 0) {
				st->backoff_ms = 5000;
				st->last_target_ver = meta.version_packed;
				st->suppress_until_ms = st->last_attempt_ms + 180000; /* 180s */
			} else {
				/* exponential backoff up to 5 minutes */
				uint32_t b = st->backoff_ms ? st->backoff_ms : 5000;
				b = b * 2;
				if (b > 300000)
					b = 300000;
				st->backoff_ms = b;
			}
		}
		pthread_mutex_unlock(&g_relays_lock);

		free(ev);
	}
	return NULL;
}

/* ---- main ---- */

static void usage(const char *prog)
{
	fprintf(stderr,
		"Usage: %s -j /tmp/version.json [-F firmware_dir] [-b bind_ip] [-p ctrl_port] [-P data_port] [-v]\n"
		"\n"
		"  -j <path>   version.json path\n"
		"  -F <dir>    firmware directory (default: same dir as version.json)\n"
		"  -b <ip>     bind ip (default 0.0.0.0)\n"
		"  -p <port>   directory UDP port (default %d)\n"
		"  -P <port>   TFOTA TCP data port (default %d)\n"
		"  -v          verbose stderr\n",
		prog, NRC_FOTA_CTRL_PORT, NRC_FOTA_DATA_PORT);
}

int main(int argc, char **argv)
{
	int port = NRC_FOTA_CTRL_PORT;
	char bind_ip[64] = "0.0.0.0";

	memset(g_version_json_path, 0, sizeof(g_version_json_path));
	memset(g_firmware_dir, 0, sizeof(g_firmware_dir));
	memset(&g_meta, 0, sizeof(g_meta));

	int opt;
	while ((opt = getopt(argc, argv, "j:F:b:p:P:vh")) != -1) {
		switch (opt) {
		case 'j':
			snprintf(g_version_json_path, sizeof(g_version_json_path), "%s", optarg);
			break;
		case 'F':
			snprintf(g_firmware_dir, sizeof(g_firmware_dir), "%s", optarg);
			break;
		case 'b':
			snprintf(bind_ip, sizeof(bind_ip), "%s", optarg);
			break;
		case 'p':
			port = atoi(optarg);
			break;
		case 'P':
			g_data_port = atoi(optarg);
			break;
		case 'v':
			g_verbose = 1;
			break;
		case 'h':
		default:
			usage(argv[0]);
			return 1;
		}
	}

	if (g_data_port <= 0 || g_data_port > 65535) {
		fprintf(stderr, "Invalid data port: %d\n", g_data_port);
		return 1;
	}

	openlog("nrc_fota_rootd", LOG_PID | LOG_NDELAY, LOG_DAEMON);
	signal(SIGHUP, on_sighup);

	if (!g_version_json_path[0]) {
		usage(argv[0]);
		return 1;
	}

	fota_meta_t tmp;
	if (load_version_json(g_version_json_path, g_firmware_dir, &tmp) != 0)
		return 1;
	pthread_mutex_lock(&g_meta_lock);
	g_meta = tmp;
	pthread_mutex_unlock(&g_meta_lock);

	int udp = socket(AF_INET, SOCK_DGRAM, 0);
	if (udp < 0) {
		loge("socket udp failed (%s)", strerror(errno));
		return 1;
	}

	int one = 1;
	setsockopt(udp, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons((uint16_t)port);
	if (inet_aton(bind_ip, &addr.sin_addr) == 0) {
		loge("Invalid bind ip: %s", bind_ip);
		close(udp);
		return 1;
	}

	if (bind(udp, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		loge("bind %s:%d failed (%s)", bind_ip, port, strerror(errno));
		close(udp);
		return 1;
	}

	logi("Listening directory UDP on %s:%d", bind_ip, port);

	listener_arg_t la;
	la.udp_sock = udp;

	pthread_t th_listener;
	pthread_t th_worker;

	if (pthread_create(&th_listener, NULL, listener_thread, &la) != 0) {
		loge("pthread_create(listener) failed");
		close(udp);
		return 1;
	}
	if (pthread_create(&th_worker, NULL, worker_thread, NULL) != 0) {
		loge("pthread_create(worker) failed");
		g_stop = 1;
		pthread_cond_broadcast(&g_q_cond);
		pthread_join(th_listener, NULL);
		close(udp);
		return 1;
	}

	/* Run forever */
	for (;;) {
		pause();
	}

	/* not reached */
	g_stop = 1;
	pthread_cond_broadcast(&g_q_cond);
	pthread_join(th_listener, NULL);
	pthread_join(th_worker, NULL);
	close(udp);
	closelog();
	return 0;
}
