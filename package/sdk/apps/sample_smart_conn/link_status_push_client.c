/*
 * udp_json_push_client_task.c
 *
 * FreeRTOS + lwIP sockets UDP client:
 * - every 30 seconds, build JSON and sendto(server_ip:port)
 *
 * JSON includes:
 * - mac, parent_mac, hop, rssi, snr
 */

#include "link_status_push_client.h"
#include "link_status.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "nrc_types.h"

#include "FreeRTOS.h"
#include "task.h"

#include "lwip/sockets.h"
#include "lwip/inet.h"
#include "lwip/ip_addr.h"
#include "api_smart_conn.h"
#include "api_system.h"

#ifdef USE_NANOPB
#include "pb_encode.h"
#include "link_status.pb.h"
#endif

#ifdef USE_NANOPB
#define UDP_STATUS_FMT_STR  "PB"
#else
#define UDP_STATUS_FMT_STR  "JSON"
#endif

/* -------------------- Configuration -------------------- */
#define UDP_STATUS_SERVER_IP_STR        "192.168.200.1"
#define UDP_STATUS_SERVER_PORT          5000
#define UDP_STATUS_PERIOD_MS            (10 * 1000)
#define UDP_STATUS_SEND_TIMEOUT_MS      2000
#define UDP_STATUS_MAX_LEN              1024
#define UDP_STATUS_MAX_CANDIDATES		10
#define UDP_STATUS_MAX_BLACKLIST		10

/* -------------------- Helpers -------------------- */
static void set_send_timeout_ms(int fd, int timeout_ms)
{
	struct timeval tv;
	tv.tv_sec = timeout_ms / 1000;
	tv.tv_usec = (timeout_ms % 1000) * 1000;
	(void)setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
}

#ifdef USE_NANOPB
static void copy_mac_to_pbbytes(pb_bytes_array_t *dst, size_t dst_max, const uint8_t mac[6])
{
	if (!dst || dst_max < 6) {
		return;
	}

	dst->size = 6;
	memcpy(dst->bytes, mac, 6);
}

static int build_linkstatus_pb(const link_status_t *st,
				uint8_t *out, size_t out_sz,
				uint32_t *out_len)
{
	smartconn_LinkStatus msg = smartconn_LinkStatus_init_zero;
	VERSION_T *ver = nrc_get_app_version();

	smart_connection_neighbor_info_t neigh[UDP_STATUS_MAX_CANDIDATES];
	smart_connection_blacklist_info_t bl[UDP_STATUS_MAX_BLACKLIST];
	int neigh_cnt, bl_cnt;

	neigh_cnt = smart_connection_get_neighbor_list(neigh, UDP_STATUS_MAX_CANDIDATES);
	if (neigh_cnt < 0) neigh_cnt = 0;
	if (neigh_cnt > UDP_STATUS_MAX_CANDIDATES) neigh_cnt = UDP_STATUS_MAX_CANDIDATES;

	bl_cnt = smart_connection_get_blacklist(bl, UDP_STATUS_MAX_BLACKLIST);
	if (bl_cnt < 0) bl_cnt = 0;
	if (bl_cnt > UDP_STATUS_MAX_BLACKLIST) bl_cnt = UDP_STATUS_MAX_BLACKLIST;

	/* mac (required) */
	copy_mac_to_pbbytes((pb_bytes_array_t *)&msg.mac, sizeof(msg.mac.bytes), st->mac);

	/* parent_mac (optional) */
	msg.has_parent_mac = (st->parent_valid != 0);
	if (msg.has_parent_mac) {
		copy_mac_to_pbbytes((pb_bytes_array_t *)&msg.parent_mac,
					sizeof(msg.parent_mac.bytes), st->parent_mac);
	}

	msg.hop = (int32_t)st->hop;
	msg.rssi = (int32_t)st->rssi;

	/* app version  */
	msg.has_ver = true;
	msg.ver.major = (uint32_t)ver->major;
	msg.ver.minor = (uint32_t)ver->minor;
	msg.ver.patch = (uint32_t)ver->patch;

	/* candidates */
	msg.candidates_count = 0;
	for (int i = 0; i < neigh_cnt && msg.candidates_count < UDP_STATUS_MAX_CANDIDATES; i++) {
		smartconn_Candidate *c = &msg.candidates[msg.candidates_count];

		copy_mac_to_pbbytes((pb_bytes_array_t *)&c->bssid, sizeof(c->bssid.bytes), neigh[i].bssid);
		c->rssi = (int32_t)neigh[i].rssi;
		c->hop = (int32_t)neigh[i].current_hop;

		msg.candidates_count++;
	}

	/* blacklist */
	msg.blacklist_count = 0;
	for (int i = 0; i < bl_cnt && msg.blacklist_count < UDP_STATUS_MAX_BLACKLIST; i++) {
		smartconn_BlackItem *b = &msg.blacklist[msg.blacklist_count];

		copy_mac_to_pbbytes((pb_bytes_array_t *)&b->bssid, sizeof(b->bssid.bytes), bl[i].bssid);

		msg.blacklist_count++;
	}

	pb_ostream_t os = pb_ostream_from_buffer(out, out_sz);
	if (!pb_encode(&os, smartconn_LinkStatus_fields, &msg)) {
		printf("pb_encode failed: %s\n", PB_GET_ERROR(&os));
		return -1;
	}

	*out_len = (uint32_t)os.bytes_written;
	return 0;
}
#else // not USE_NANOPB
/* Append formatted text safely into JSON buffer */
static int json_append(char *out, size_t out_sz, size_t *off,
					   const char *fmt, ...)
{
	va_list ap;
	int n;

	if (*off >= out_sz)
		return -1;

	va_start(ap, fmt);
	n = vsnprintf(out + *off, out_sz - *off, fmt, ap);
	va_end(ap);

	if (n < 0 || (size_t)n >= (out_sz - *off))
		return -1;

	*off += (size_t)n;
	return 0;
}

/* Convert MAC address to string */
static void mac_to_str(const uint8_t mac[6], char out[18])
{
	snprintf(out, 18, "%02X:%02X:%02X:%02X:%02X:%02X",
			 mac[0], mac[1], mac[2],
			 mac[3], mac[4], mac[5]);
}

/*
 * Build telemetry JSON
 * - Mandatory fields: mac, parent_mac, hop, rssi, snr
 * - Optional fields: candidates[], blacklist[]
 *   (included only if non-empty)
 */
static int build_linkstatus_json(const link_status_t *st,
					  char *out,
					  size_t out_sz,
					  uint32_t *out_len)
{
	char mac[18];
	char parent_mac[18];
	VERSION_T* ver = nrc_get_app_version();

	smart_connection_neighbor_info_t neigh[UDP_STATUS_MAX_CANDIDATES];
	smart_connection_blacklist_info_t bl[UDP_STATUS_MAX_BLACKLIST];

	int neigh_cnt;
	int bl_cnt;

	size_t off = 0;
	bool need_comma = false;

	mac_to_str(st->mac, mac);
	mac_to_str(st->parent_mac, parent_mac);

	neigh_cnt = smart_connection_get_neighbor_list(neigh, UDP_STATUS_MAX_CANDIDATES);
	if (neigh_cnt < 0)
		neigh_cnt = 0;
	if (neigh_cnt > UDP_STATUS_MAX_CANDIDATES)
		neigh_cnt = UDP_STATUS_MAX_CANDIDATES;

	bl_cnt = smart_connection_get_blacklist(bl, UDP_STATUS_MAX_BLACKLIST);
	if (bl_cnt < 0)
		bl_cnt = 0;
	if (bl_cnt > UDP_STATUS_MAX_BLACKLIST)
		bl_cnt = UDP_STATUS_MAX_BLACKLIST;

#define APPEND_FIELD(fmt, ...)										 \
	do {															 \
		if (need_comma) {											 \
			if (json_append(out, out_sz, &off, ",") != 0)			 \
				return -1;											 \
		}															 \
		if (json_append(out, out_sz, &off, fmt, ##__VA_ARGS__) != 0) \
			return -1;												 \
		need_comma = true;											 \
	} while (0)

	/* Start JSON object */
	if (json_append(out, out_sz, &off, "{") != 0)
		return -1;

	/* Mandatory fields */
	APPEND_FIELD("\"mac\":\"%s\"", mac);
	APPEND_FIELD("\"parent_mac\":\"%s\"", parent_mac);
	APPEND_FIELD("\"hop\":%d", (int)st->hop);
	APPEND_FIELD("\"rssi\":%d", (int)st->rssi);
	APPEND_FIELD("\"ver\":\"%u.%u.%u\"", ver->major, ver->minor, ver->patch);

	/* Optional: candidate AP list */
	if (neigh_cnt > 0) {
		if (json_append(out, out_sz, &off, ",\"candidates\":[") != 0)
			return -1;

		for (int i = 0; i < neigh_cnt; i++) {
			char bssid[18];

			mac_to_str(neigh[i].bssid, bssid);

			if (json_append(out, out_sz, &off,
							"%s{\"bssid\":\"%s\",\"rssi\":%d,\"hop\":%d}",
							(i == 0) ? "" : ",",
							bssid,
							(int)neigh[i].rssi,
							(int)neigh[i].current_hop) != 0)
				return -1;
		}

		if (json_append(out, out_sz, &off, "]") != 0)
			return -1;
	}

	/* Optional: blacklist */
	if (bl_cnt > 0) {
		if (json_append(out, out_sz, &off, ",\"blacklist\":[") != 0)
			return -1;

		for (int i = 0; i < bl_cnt; i++) {
			char bssid[18];

			mac_to_str(bl[i].bssid, bssid);

			if (json_append(out, out_sz, &off,
							"%s{\"bssid\":\"%s\"}",
							(i == 0) ? "" : ",",
							bssid) != 0)
				return -1;
		}

		if (json_append(out, out_sz, &off, "]") != 0)
			return -1;
	}

	/* End JSON object */
	if (json_append(out, out_sz, &off, "}") != 0)
		return -1;

#undef APPEND_FIELD

	*out_len = (uint32_t)off;
	return 0;
}
#endif // USE_NANOPB

static int build_linkstatus_payload(const link_status_t *st,
					uint8_t *out, size_t out_sz,
					uint32_t *out_len)
{
#ifdef USE_NANOPB
	return build_linkstatus_pb(st, out, out_sz, out_len);
#else
	return build_linkstatus_json(st, (char *)out, out_sz, out_len);
#endif
}

/* -------------------- UDP Push Task -------------------- */
static void udp_status_push_client_task(void *arg)
{
	(void)arg;

	printf("[UDP] status push client start (%s)\n", UDP_STATUS_FMT_STR);

	int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (fd < 0) {
		printf("[UDP][ERROR] socket() failed\n");
		vTaskDelete(NULL);
		return;
	}

	set_send_timeout_ms(fd, UDP_STATUS_SEND_TIMEOUT_MS);

	struct sockaddr_in srv;
	memset(&srv, 0, sizeof(srv));
	srv.sin_family = AF_INET;
	srv.sin_port = htons(UDP_STATUS_SERVER_PORT);

#if LWIP_IPV4
	if (inet_aton(UDP_STATUS_SERVER_IP_STR, &srv.sin_addr) == 0) {
		srv.sin_addr.s_addr = ipaddr_addr(UDP_STATUS_SERVER_IP_STR);
		if (srv.sin_addr.s_addr == IPADDR_NONE) {
			printf("[UDP][ERROR] invalid server IP: %s\n", UDP_STATUS_SERVER_IP_STR);
			close(fd);
			vTaskDelete(NULL);
			return;
		}
	}
#else
	srv.sin_addr.s_addr = ipaddr_addr(UDP_STATUS_SERVER_IP_STR);
#endif

	for (;;) {
		link_status_t st;
		uint8_t payload[UDP_STATUS_MAX_LEN];
		uint32_t payload_len = 0;

		if (!link_status_get(&st)) {
			printf("[UDP][WARN] link_status_get() failed\n");
			vTaskDelay(pdMS_TO_TICKS(UDP_STATUS_PERIOD_MS));
			continue;
		}

		if (st.connected == WIFI_STATE_CONNECTED) {
			if (build_linkstatus_payload(&st, payload, sizeof(payload), &payload_len) != 0) {
				printf("[UDP][WARN] build_linkstatus_payload() failed (%s)\n", UDP_STATUS_FMT_STR);
				vTaskDelay(pdMS_TO_TICKS(UDP_STATUS_PERIOD_MS));
				continue;
			}

			int n = sendto(fd, payload, (int)payload_len, 0,
					(struct sockaddr *)&srv, sizeof(srv));

			if (n == (int)payload_len) {
				printf("[UDP] sent %d bytes (%s) to %s:%d\n",
					n, UDP_STATUS_FMT_STR,
					UDP_STATUS_SERVER_IP_STR, UDP_STATUS_SERVER_PORT);
			} else {
				printf("[UDP][WARN] sendto() failed (n=%d, errno=%d)\n", n, errno);
			}
		}

		vTaskDelay(pdMS_TO_TICKS(UDP_STATUS_PERIOD_MS));
	}
}

/* -------------------- Start API -------------------- */
void link_status_push_client_start(void)
{
	if (xTaskCreate(udp_status_push_client_task,
					"udp_status_push_client",
					1024,
					NULL,
					USER_APP_TASK_PRIORITY,
					NULL) != pdPASS) {
		printf("Failed to create udp_status_push_client_task\n");
	}
}

