/* multi_role_register.c */

#include "nrc_sdk.h"
#include "multi_role_register.h"
#include "nrc_sdk.h"
#include "lwip/sockets.h"
#include "lwip/inet.h"
#include "lwip/netif.h"
#include "wifi_user_config.h"
#include "api_smart_conn.h"
#include "sample_smart_conn_version.h"
#include "nvs.h"
#include "app_feature_cfg.h"
#include <string.h>

/* --------------------------------------------------------------------------
 * REGISTER reliability notes
 *
 * With "fast connect", a relay can remain Wi-Fi associated even if the Root
 * (SoftAP) reboots. In that case the relay may try to REGISTER before the
 * Root's directory UDP server is bound/ready. To handle this without adding
 * continuous background traffic, we:
 *
 *  - Use ACK + retry + exponential backoff for REGISTER.
 *  - Keep a small background task that will re-REGISTER periodically. If the
 *    Root rebooted and lost its directory, this repopulates it automatically.
 */

#ifndef TFOTA_REG_ACK_TIMEOUT_MS
#define TFOTA_REG_ACK_TIMEOUT_MS     400
#endif

#ifndef TFOTA_REG_MIN_BACKOFF_MS
#define TFOTA_REG_MIN_BACKOFF_MS     200
#endif

#ifndef TFOTA_REG_BURST_WINDOW_MS
#define TFOTA_REG_BURST_WINDOW_MS    30000   /* try for ~30s, then pause */
#endif

#ifndef TFOTA_REG_BURST_ATTEMPTS
#define TFOTA_REG_BURST_ATTEMPTS     6
#endif

#ifndef TFOTA_REG_MAX_BACKOFF_MS
#define TFOTA_REG_MAX_BACKOFF_MS     10000
#endif

/* After a successful REGISTER, re-REGISTER at this interval to repopulate
 * Root's directory after Root reboot ("fast connect" may not trigger a
 * disconnect event on the relay).
 */
#ifndef TFOTA_REG_REFRESH_MS
#define TFOTA_REG_REFRESH_MS         60000   /* re-register every 60s */
#endif

extern nvs_handle_t nvs_handle;

/* If a burst attempt fails (Root not ready), wait this long before trying
 * another burst. This prevents 64 relays from spamming during Root boot.
 */
#ifndef TFOTA_REG_RETRY_FAIL_MS
#define TFOTA_REG_RETRY_FAIL_MS      5000
#endif

static SemaphoreHandle_t g_reg_lock;
static bool g_reg_inflight;

static uint32_t reg_now_ms(void)
{
	return (uint32_t)(xTaskGetTickCount() * portTICK_PERIOD_MS);
}

extern struct netif *nrc_netif[];
extern struct netif br_netif;

uint32_t tfota_get_root_ip_nbo(void)
{
	return app_tfota_root_ip_nbo();
}

int tfota_get_self_mac(uint8_t mac[6])
{
	system_role_t role = get_system_type();
	struct netif *n = NULL;

	if (role == ROLE_SOFTAP) {
		n = nrc_netif[0];
	} else if (role == ROLE_RELAY) {
		n = &br_netif;
	} else if (role == ROLE_STATION) {
		n = nrc_netif[0];
	}

	if (n && n->hwaddr_len >= 6) {
		memcpy(mac, n->hwaddr, 6);
		return 0;
	}

	return -1;
}

static int tfota_get_parent_mac(uint8_t mac[6])
{
	AP_INFO info;
	tWIFI_STATUS st;

	if (!mac)
		return -1;

	memset(mac, 0, 6);
	memset(&info, 0, sizeof(info));

	st = nrc_wifi_get_ap_info(1, &info);
	if (st != WIFI_SUCCESS)
		return -1;

	if (info.bssid[0] == 0 && info.bssid[1] == 0 && info.bssid[2] == 0 &&
		info.bssid[3] == 0 && info.bssid[4] == 0 && info.bssid[5] == 0) {
		return -1;
	}

	memcpy(mac, info.bssid, 6);
	return 0;
}

static inline uint32_t ver_pack_u32(const version_t *v)
{
	if (!v) return 0;
	return ((uint32_t)v->major << 24) |
	       ((uint32_t)v->minor << 16) |
	       ((uint32_t)v->patch <<  8);
	/* low 8 bits reserved for future */
}

static inline void ver_unpack_u32(uint32_t packed, version_t *out)
{
	if (!out) return;
	out->major = (packed >> 24) & 0xFF;
	out->minor = (packed >> 16) & 0xFF;
	out->patch = (packed >>  8) & 0xFF;
}

static inline int ver_cmp(const version_t *a, const version_t *b)
{
	uint32_t pa = ver_pack_u32(a);
	uint32_t pb = ver_pack_u32(b);
	if (pa < pb) return -1;
	if (pa > pb) return  1;
	return 0;
}

uint32_t tfota_get_fw_version_packed(void)
{
	const VERSION_T *v = nrc_get_app_version();   /* same as version_t */
	return ver_pack_u32((const version_t *)v);
}

static uint32_t tfota_get_ipv4_addr_nbo(void)
{
	system_role_t role = get_system_type();

	if (role == ROLE_SOFTAP) {
		return nrc_netif[0]->ip_addr.addr;
	} else if (role == ROLE_RELAY) {
		return br_netif.ip_addr.addr;
	} else if (role == ROLE_STATION) {
		return nrc_netif[0]->ip_addr.addr;
	} else {
		if (netif_default) {
			return netif_default->ip_addr.addr;
		}
	}

	return 0;
}

static bool tfota_network_is_up(void)
{
	uint32_t ip = tfota_get_ipv4_addr_nbo();
	return (ip != 0);
}

/* -------- Helpers -------- */

uint32_t make_node_id_from_mac(const uint8_t mac[6])
{
	uint32_t v = 0;
	for (int i = 0; i < 6; i++)
		v = (v << 5) ^ (v >> 27) ^ mac[i];
	return v ? v : 1;
}

int send_register_to_root(uint32_t root_ip_nbo,
						  const uint8_t self_mac[6],
						  const uint8_t parent_mac[6],
						  system_role_t role,
						  uint8_t hop,
						  uint32_t fw_ver_packed)
{
	if (!root_ip_nbo || !self_mac)
		return -1;

	int s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)
		return -1;

	/* Wait for ACK to make REGISTER reliable.
	 *
	 * IMPORTANT: After a Root reboot, it can take several seconds (or longer)
	 * before the Root's UDP directory server is bound and ready to reply.
	 * So we keep retrying for a while with exponential backoff.
	 */
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = TFOTA_REG_ACK_TIMEOUT_MS * 1000; /* e.g., 400ms */
	setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

	struct sockaddr_in to;
	memset(&to, 0, sizeof(to));
	to.sin_family = AF_INET;
	to.sin_port = htons(app_tfota_ctrl_port());
	to.sin_addr.s_addr = root_ip_nbo;

	uint32_t node_id = make_node_id_from_mac(self_mac);
	uint32_t seq_base = (uint32_t)xTaskGetTickCount();
	int backoff_ms = TFOTA_REG_MIN_BACKOFF_MS;
	uint32_t start_ms = (uint32_t)(xTaskGetTickCount() * portTICK_PERIOD_MS);

	for (int attempt = 0; ; attempt++) {
		uint32_t now_ms = (uint32_t)(xTaskGetTickCount() * portTICK_PERIOD_MS);
		if ((now_ms - start_ms) > TFOTA_REG_BURST_WINDOW_MS) {
			/* Give control back to the caller (register_task) so it can
			 * back off further and also re-check role / network state.
			 */
			break;
		}

		nrc_dir_register_t reg;
		memset(&reg, 0, sizeof(reg));

		reg.hdr.magic = NRC_MAGIC_DIR;
		reg.hdr.type = NRC_DIR_MSG_REGISTER;
		reg.hdr.len = sizeof(reg);
		reg.hdr.seq = seq_base + (uint32_t)attempt;

		reg.node_id = node_id;
		memcpy(reg.mac, self_mac, 6);
		if (parent_mac)
			memcpy(reg.parent_mac, parent_mac, 6);
		reg.role = role;
		reg.hop = hop;
		reg.ipv4_addr = tfota_get_ipv4_addr_nbo();
		reg.fw_ver_packed = fw_ver_packed;
		/* app name (null-terminated). */
		{
			const char *nm = (const char *)nrc_get_app_name();
			memset(reg.app_name, 0, sizeof(reg.app_name));
			if (nm && nm[0]) {
				strncpy(reg.app_name, nm, sizeof(reg.app_name) - 1);
				reg.app_name[sizeof(reg.app_name) - 1] = '\0';
			}
		}

		(void)sendto(s, &reg, sizeof(reg), 0, (struct sockaddr *)&to, sizeof(to));

		/* Wait ACK */
		nrc_dir_ack_t ack;
		struct sockaddr_in from;
		socklen_t fl = sizeof(from);
		int r = recvfrom(s, &ack, sizeof(ack), 0, (struct sockaddr *)&from, &fl);
		if (r == (int)sizeof(ack) &&
			ack.hdr.magic == NRC_MAGIC_DIR &&
			ack.hdr.type == NRC_DIR_MSG_ACK &&
			ack.hdr.seq == reg.hdr.seq &&
			ack.acked_type == NRC_DIR_MSG_REGISTER &&
			memcmp(ack.mac, self_mac, 6) == 0 &&
			ack.node_id == node_id &&
			ack.code == 0) {
			close(s);
			return 0;
		}

		/* Exponential backoff with small deterministic jitter */
		int jitter = (int)((seq_base >> (attempt & 0xF)) & 0x3F); /* 0..63ms */
		_delay_ms((uint32_t)(backoff_ms + jitter));
		if (backoff_ms < TFOTA_REG_MAX_BACKOFF_MS)
			backoff_ms *= 2;
		if (backoff_ms > TFOTA_REG_MAX_BACKOFF_MS)
			backoff_ms = TFOTA_REG_MAX_BACKOFF_MS;
	}

	close(s);
	return -1;
}

int send_status_to_root(uint32_t root_ip_nbo,
			const uint8_t self_mac[6],
			uint32_t node_id,
			uint32_t session_id,
			nrc_fota_status_t status,
			uint8_t progress_percent,
			uint32_t fw_ver_packed)
{
	if (!root_ip_nbo || !self_mac)
		return -1;

	int s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)
		return -1;

	struct sockaddr_in to;
	memset(&to, 0, sizeof(to));
	to.sin_family = AF_INET;
	to.sin_port = htons(app_tfota_ctrl_port());
	to.sin_addr.s_addr = root_ip_nbo;

	nrc_dir_status_t st;
	memset(&st, 0, sizeof(st));

	st.hdr.magic = NRC_MAGIC_DIR;
	st.hdr.type = NRC_DIR_MSG_STATUS;
	st.hdr.len = sizeof(st);
	st.hdr.seq = 1;

	st.node_id = node_id;
	memcpy(st.mac, self_mac, 6);

	st.session_id = session_id;
	st.fota_status = (uint8_t)status;
	st.progress_percent = progress_percent;
	st.fw_ver_packed = fw_ver_packed;

	sendto(s, &st, sizeof(st), 0, (struct sockaddr *)&to, sizeof(to));
	close(s);
	return 0;
}

int send_heartbeat_to_root(uint32_t root_ip_nbo, const uint8_t self_mac[6])
{
	if (!root_ip_nbo || !self_mac)
		return -1;

#ifndef DIR_HB_ACK_WAIT_MS
#define DIR_HB_ACK_WAIT_MS 800
#endif

#ifndef DIR_HB_ACK_RETRY_MAX
#define DIR_HB_ACK_RETRY_MAX 1
#endif

	int s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)
		return -1;

	/* Wait for ACK from Root so the node can detect Root reachability.
	 * Use a short timeout; overall detection is handled by the caller.
	 */
	struct timeval tv;
	tv.tv_sec = DIR_HB_ACK_WAIT_MS / 1000;
	tv.tv_usec = (DIR_HB_ACK_WAIT_MS % 1000) * 1000;
	setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

	struct sockaddr_in to;
	memset(&to, 0, sizeof(to));
	to.sin_family = AF_INET;
	to.sin_port = htons(app_tfota_ctrl_port());
	to.sin_addr.s_addr = root_ip_nbo;

	nrc_dir_heartbeat_t hb;
	memset(&hb, 0, sizeof(hb));

	hb.hdr.magic = NRC_MAGIC_DIR;
	hb.hdr.type  = NRC_DIR_MSG_HEARTBEAT;
	hb.hdr.len   = sizeof(hb);
	hb.hdr.seq   = (uint32_t)xTaskGetTickCount();

	memcpy(hb.mac, self_mac, 6);
	hb.ipv4_addr = tfota_get_ipv4_addr_nbo();
	hb.uptime_ms = (uint32_t)(xTaskGetTickCount() * portTICK_PERIOD_MS);

	for (int attempt = 0; attempt <= DIR_HB_ACK_RETRY_MAX; attempt++) {
		(void)sendto(s, &hb, sizeof(hb), 0, (struct sockaddr *)&to, sizeof(to));

		nrc_dir_ack_t ack;
		struct sockaddr_in from;
		socklen_t fl = sizeof(from);
		int r = recvfrom(s, &ack, sizeof(ack), 0, (struct sockaddr *)&from, &fl);
		if (r == (int)sizeof(ack) &&
			ack.hdr.magic == NRC_MAGIC_DIR &&
			ack.hdr.type == NRC_DIR_MSG_ACK &&
			ack.acked_type == NRC_DIR_MSG_HEARTBEAT &&
			memcmp(ack.mac, self_mac, 6) == 0 &&
			ack.code == 0) {
			close(s);
			return 0;
		}
		/* retry once if desired */
	}

	close(s);
	return -1;
}

/* -------- Deferred register task -------- */

static void register_task(void *arg)
{
	/* Keep a single background task alive that:
	 *  - waits for IP,
	 *  - bursts REGISTER retries until ACK,
	 *  - periodically re-REGISTER to recover Root directory after Root reboot.
	 */
	int backoff_refresh_ms = (int)TFOTA_REG_REFRESH_MS;
	uint32_t seed = (uint32_t)xTaskGetTickCount();

	while (1) {
		/* If role changed away from relay/sta, stop */
		system_role_t role = get_system_type();
		if (role == ROLE_SOFTAP)
			break;

		/* Directory REGISTER refresh cadence is configurable (NVS read once at boot). */
		backoff_refresh_ms = (int)app_dir_refresh_ms();

		/* Wait until IP is ready */
		if (!tfota_network_is_up()) {
			_delay_ms(200);
			continue;
		}

		uint32_t root_ip = tfota_get_root_ip_nbo();
		if (!root_ip) {
			_delay_ms(500);
			continue;
		}

		uint8_t self_mac[6];
		uint8_t parent_mac[6];
		if (tfota_get_self_mac(self_mac) < 0) {
			_delay_ms(1000);
			continue;
		}
		if (tfota_get_parent_mac(parent_mac) < 0)
			memset(parent_mac, 0, 6);

		int8_t h = get_current_hop();
		uint8_t hop = (h < 0) ? 0xFF : (uint8_t)h;
		uint32_t fw = tfota_get_fw_version_packed();

		int rc = send_register_to_root(root_ip, self_mac, parent_mac, role, hop, fw);
		if (rc == 0) {
			/* Small stable jitter so 64 relays don't align */
			int jitter = (int)((seed ^ make_node_id_from_mac(self_mac)) & 0x3FF); /* 0..1023ms */
			_delay_ms((uint32_t)(backoff_refresh_ms + jitter));
			continue;
		}

		/* Root not ready yet (or packet loss). Wait and try another burst. */
		_delay_ms(TFOTA_REG_RETRY_FAIL_MS);
	}

	/* mark inflight=false */
	if (!g_reg_lock)
		g_reg_lock = xSemaphoreCreateMutex();
	if (g_reg_lock) {
		xSemaphoreTake(g_reg_lock, portMAX_DELAY);
		g_reg_inflight = false;
		xSemaphoreGive(g_reg_lock);
	}

	vTaskDelete(NULL);
}

void tfota_try_register_later(void)
{
	if (!app_feature_tfota_enabled())
		return;
	if (!g_reg_lock)
		g_reg_lock = xSemaphoreCreateMutex();
	if (g_reg_lock) {
		xSemaphoreTake(g_reg_lock, portMAX_DELAY);
		if (g_reg_inflight) {
			xSemaphoreGive(g_reg_lock);
			return;
		}
		g_reg_inflight = true;
		xSemaphoreGive(g_reg_lock);
	}

	if (xTaskCreate(register_task, "tfota_reg", 2048, NULL,
			   tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
		if (g_reg_lock) {
			xSemaphoreTake(g_reg_lock, portMAX_DELAY);
			g_reg_inflight = false;
			xSemaphoreGive(g_reg_lock);
		}
	}
}
