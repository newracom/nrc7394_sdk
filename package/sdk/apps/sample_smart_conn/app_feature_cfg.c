#include "app_feature_cfg.h"

#include "wifi_user_config.h" /* NRC_SOFTAP_IP, REPORT_DURATION */
#include "multi_role_proto.h" /* default ports */
#include "app_debug.h"

#include "lwip/inet.h"
#include <string.h>
#include <inttypes.h>

typedef struct {
	bool	inited;
	bool	overrides_on; /* feat_cfg_on */
	bool	tfota_on;     /* tfota_on */

	uint32_t root_ip_nbo;
	uint16_t ctrl_port;
	uint16_t data_port;

	uint32_t report_period_ms;

	/* Directory timing (REGISTER / HEARTBEAT / offline detection) */
	uint32_t dir_refresh_ms;
	uint32_t dir_hb_ms_unprov;
	uint32_t dir_hb_ms_prov;
	uint32_t dir_offline_ms_unprov;
	uint32_t dir_offline_ms_prov;
} app_feature_cfg_t;

static app_feature_cfg_t g_cfg;

/*
 * NVS key names MUST be <= 15 characters (16 bytes including NUL).
 * Keep these consistent across apps (hvac_wifi_comm, sample_smart_conn, future apps).
 */
#define KEY_FEAT_CFG_ON       "feat_cfg_on"      /* u8 */
#define KEY_TFOTA_ON          "tfota_on"         /* u8 */
#define KEY_TFOTA_ROOT_IP     "tfota_root_ip"    /* str */
#define KEY_TFOTA_CTRL_PORT   "tfota_ctrl_port"  /* u16 */
#define KEY_TFOTA_DATA_PORT   "tfota_data_port"  /* u16 */

#define KEY_DIR_REFRESH_MS    "dir_refresh_ms"   /* u32 */
#define KEY_DIR_HB_MS         "dir_hb_ms"        /* u32 */
#define KEY_DIR_HB_MS_PR      "dir_hb_ms_pr"     /* u32 */
#define KEY_DIR_OFF_MS        "dir_off_ms"       /* u32 */
#define KEY_DIR_OFF_MS_PR     "dir_off_ms_pr"    /* u32 */

static uint32_t default_root_ip_nbo(void)
{
	/* inet_addr() returns NBO. */
	return inet_addr(NRC_SOFTAP_IP);
}

static uint16_t sanitize_port_u16(uint16_t v, uint16_t dflt)
{
	if (v == 0)
		return dflt;
	return v;
}

static uint32_t sanitize_period_ms(uint32_t v, uint32_t dflt)
{
	/* Avoid 0, and avoid absurdly small values that could spam logs */
	if (v < 1000)
		return dflt;
	return v;
}

static uint32_t clamp_u32(uint32_t v, uint32_t minv, uint32_t maxv)
{
	if (v < minv) return minv;
	if (v > maxv) return maxv;
	return v;
}

void app_feature_cfg_init(nvs_handle_t h)
{
	memset(&g_cfg, 0, sizeof(g_cfg));
	g_cfg.inited = true;

	/* Defaults */
	g_cfg.overrides_on = true;
	g_cfg.tfota_on = true;
	g_cfg.root_ip_nbo = default_root_ip_nbo();
	g_cfg.ctrl_port = NRC_FOTA_CTRL_PORT;
	g_cfg.data_port = NRC_FOTA_DATA_PORT;

	/* Directory defaults (match existing directory behavior) */
	g_cfg.dir_refresh_ms = 30000;
	g_cfg.dir_hb_ms_unprov = 2000;
	g_cfg.dir_hb_ms_prov = 15000;
	g_cfg.dir_offline_ms_unprov = 10000;
	g_cfg.dir_offline_ms_prov = 60000;

#if FEATURE_RUNTIME_CFG
	if (h) {
		uint8_t u8;
		uint16_t u16;
		uint32_t u32;
		uint16_t ka_interval = 0;
		uint16_t ka_interval_pr = 15;
		bool has_dir_hb_ms = false;
		bool has_dir_hb_ms_pr = false;
		char ipstr[32];
		size_t iplen = sizeof(ipstr);

		/* Master switch */
		if (nvs_get_u8(h, KEY_FEAT_CFG_ON, &u8) == NVS_OK)
			g_cfg.overrides_on = (u8 != 0);

		if (g_cfg.overrides_on) {
			if (nvs_get_u8(h, KEY_TFOTA_ON, &u8) == NVS_OK)
				g_cfg.tfota_on = (u8 != 0);

			if (nvs_get_str(h, KEY_TFOTA_ROOT_IP, ipstr, &iplen) == NVS_OK) {
				uint32_t ip = inet_addr(ipstr);
				if (ip != IPADDR_NONE)
					g_cfg.root_ip_nbo = ip;
			}

			if (nvs_get_u16(h, KEY_TFOTA_CTRL_PORT, &u16) == NVS_OK)
				g_cfg.ctrl_port = sanitize_port_u16(u16, NRC_FOTA_CTRL_PORT);
			if (nvs_get_u16(h, KEY_TFOTA_DATA_PORT, &u16) == NVS_OK)
				g_cfg.data_port = sanitize_port_u16(u16, NRC_FOTA_DATA_PORT);

			/* Directory timing overrides ("periodic reporting" for directory) */
			if (nvs_get_u32(h, KEY_DIR_REFRESH_MS, &u32) == NVS_OK && u32 > 0)
				g_cfg.dir_refresh_ms = clamp_u32(u32, 2000, 600000);
			if (nvs_get_u32(h, KEY_DIR_HB_MS, &u32) == NVS_OK && u32 > 0) {
				g_cfg.dir_hb_ms_unprov = clamp_u32(u32, 500, 5000);
				has_dir_hb_ms = true;
			}
			if (nvs_get_u32(h, KEY_DIR_HB_MS_PR, &u32) == NVS_OK && u32 > 0) {
				g_cfg.dir_hb_ms_prov = clamp_u32(u32, 1000, 60000);
				has_dir_hb_ms_pr = true;
			}
			/* offline timeout: prefer short keys; accept legacy long keys if present */
			if (nvs_get_u32(h, KEY_DIR_OFF_MS, &u32) == NVS_OK && u32 > 0)
				g_cfg.dir_offline_ms_unprov = clamp_u32(u32, 3000, 600000);
			else if (nvs_get_u32(h, "dir_offline_ms", &u32) == NVS_OK && u32 > 0)
				g_cfg.dir_offline_ms_unprov = clamp_u32(u32, 3000, 600000);
			if (nvs_get_u32(h, KEY_DIR_OFF_MS_PR, &u32) == NVS_OK && u32 > 0)
				g_cfg.dir_offline_ms_prov = clamp_u32(u32, 10000, 3600000);
			else if (nvs_get_u32(h, "dir_offline_ms_pr", &u32) == NVS_OK && u32 > 0)
				g_cfg.dir_offline_ms_prov = clamp_u32(u32, 10000, 3600000);

			/* Backward compatible fallback: if dir_hb_ms* are not set, reuse legacy keepalive cadence. */
			(void)nvs_get_u16(h, "ka_interval", &ka_interval);
			(void)nvs_get_u16(h, "ka_interval_pr", &ka_interval_pr);
			if (!has_dir_hb_ms && ka_interval > 0)
				g_cfg.dir_hb_ms_unprov = clamp_u32((uint32_t)ka_interval * 1000U, 500, 5000);
			if (!has_dir_hb_ms_pr && ka_interval_pr > 0)
				g_cfg.dir_hb_ms_prov = clamp_u32((uint32_t)ka_interval_pr * 1000U, 1000, 60000);
		}
	}
#endif

	app_feature_cfg_dump();
}

bool app_feature_overrides_enabled(void)
{
#if FEATURE_RUNTIME_CFG
	return g_cfg.inited ? g_cfg.overrides_on : true;
#else
	return false;
#endif
}

bool app_feature_tfota_enabled(void)
{
	if (!g_cfg.inited)
		return true;
	return g_cfg.tfota_on;
}

uint32_t app_tfota_root_ip_nbo(void)
{
	return g_cfg.inited ? g_cfg.root_ip_nbo : default_root_ip_nbo();
}

uint16_t app_tfota_ctrl_port(void)
{
	return g_cfg.inited ? g_cfg.ctrl_port : NRC_FOTA_CTRL_PORT;
}

uint16_t app_tfota_data_port(void)
{
	return g_cfg.inited ? g_cfg.data_port : NRC_FOTA_DATA_PORT;
}

uint32_t app_dir_refresh_ms(void)
{
	return g_cfg.inited ? g_cfg.dir_refresh_ms : 30000;
}

uint32_t app_dir_hb_ms_unprov(void)
{
	return g_cfg.inited ? g_cfg.dir_hb_ms_unprov : 2000;
}

uint32_t app_dir_hb_ms_prov(void)
{
	return g_cfg.inited ? g_cfg.dir_hb_ms_prov : 15000;
}

uint32_t app_dir_offline_ms_unprov(void)
{
	return g_cfg.inited ? g_cfg.dir_offline_ms_unprov : 10000;
}

uint32_t app_dir_offline_ms_prov(void)
{
	return g_cfg.inited ? g_cfg.dir_offline_ms_prov : 60000;
}

static void ip_to_str(uint32_t ip_nbo, char out[16])
{
	/* inet_ntoa expects struct in_addr */
	struct in_addr a;
	a.s_addr = ip_nbo;
	const char *s = inet_ntoa(a);
	if (s)
		strncpy(out, s, 16);
	else
		strncpy(out, "0.0.0.0", 16);
	out[15] = '\0';
}

void app_feature_cfg_dump(void)
{
	char ip[16];
	ip_to_str(g_cfg.root_ip_nbo, ip);

#if FEATURE_RUNTIME_CFG
	app_log(DEBUG_LEVEL_ALWAYS, NULL,
		"[FEATURE] runtime_cfg=%u overrides_on=%u tfota_on=%u root_ip=%s ctrl_port=%u data_port=%u"
		" dir_refresh_ms=%" PRIu32 " dir_hb_ms=%" PRIu32 " dir_hb_ms_pr=%" PRIu32
		" dir_off_ms=%" PRIu32 " dir_off_ms_pr=%" PRIu32 "\n",
		(unsigned)FEATURE_RUNTIME_CFG,
		(unsigned)g_cfg.overrides_on,
		(unsigned)g_cfg.tfota_on,
		ip,
		(unsigned)g_cfg.ctrl_port,
		(unsigned)g_cfg.data_port,
		g_cfg.dir_refresh_ms,
		g_cfg.dir_hb_ms_unprov,
		g_cfg.dir_hb_ms_prov,
		g_cfg.dir_offline_ms_unprov,
		g_cfg.dir_offline_ms_prov);
#else
	app_log(DEBUG_LEVEL_ALWAYS, NULL,
		"[FEATURE] runtime_cfg=0 (compile-time disabled) using defaults root_ip=%s ctrl_port=%u data_port=%u" PRIu32 "\n",
		ip,
		(unsigned)NRC_FOTA_CTRL_PORT,
		(unsigned)NRC_FOTA_DATA_PORT);
#endif
}
