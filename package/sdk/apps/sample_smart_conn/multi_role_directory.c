/* multi_role_directory.c
 *
 * Root-side directory + TFOTA manager
 *
 * Key behaviors:
 * - Directory uses UDP REGISTER/STATUS only (TCP list optional via DIR_ENABLE_TCP)
 * - TFOTA manager:
 *     - does NOT continuously compute CRC over the SF_FOTA image
 *     - only runs when it detects a *root firmware version change* vs NVS-stored version
 *     - reads fw_len/fw_crc from SF_FW_INFO
 *     - updates relays one at a time, closest hop first
 *     - marks rollout complete by updating NVS version only when all known relays match target
 */

#include "multi_role_directory.h"
#include "nrc_sdk.h"

#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

#include "lwip/sockets.h"
#include "lwip/inet.h"

#include "api_system.h"
#include "nvs.h"
#include "app_feature_cfg.h"
#include "system_sflash_.h" /* SF_FW_INFO */

extern nvs_handle_t nvs_handle;

/* ---------------- Options ---------------- */
#ifndef DIR_DEBUG
#define DIR_DEBUG 1
#endif

#ifndef DIR_ENABLE_TCP
#define DIR_ENABLE_TCP 0	/* set 1 if host TCP list query needed */
#endif

#ifndef TFOTA_MANAGER_ENABLE
#define TFOTA_MANAGER_ENABLE 1
#endif

#ifndef TFOTA_MANAGER_POLL_MS
#define TFOTA_MANAGER_POLL_MS 5000
#endif

#ifndef TFOTA_MANAGER_STARTUP_DELAY_MS
#define TFOTA_MANAGER_STARTUP_DELAY_MS 180000
#endif

#ifndef TFOTA_MANAGER_TIMEOUT_MS
#define TFOTA_MANAGER_TIMEOUT_MS 180000	/* 3 minutes per node before giving up */
#endif



/* If a node reports IN_PROGRESS but we stop receiving STATUS/progress updates,
 * treat it as stuck and force it to FAILED so the manager can retry.
 */
#ifndef TFOTA_STUCK_NO_STATUS_MS
/*
 * Be conservative on lossy links.
 *
 * We only want to declare "stuck" when the transfer is truly dead.
 * On multi-hop/poor wireless, progress can pause for tens of seconds.
 */
#define TFOTA_STUCK_NO_STATUS_MS     30000   /* 30s without any STATUS => assume dead */
#endif

#ifndef TFOTA_STUCK_NO_PROGRESS_MS
#define TFOTA_STUCK_NO_PROGRESS_MS   60000   /* 60s without prog/status change => assume dead */
#endif

#ifndef TFOTA_STUCK_BACKOFF_MS
#define TFOTA_STUCK_BACKOFF_MS       2000    /* small backoff before retrying */
#endif

#ifndef DIR_REGISTER_LOG_INTERVAL_MS
#define DIR_REGISTER_LOG_INTERVAL_MS 5000    /* print REGISTER at most every 5s per node (unless changed) */
#endif

#ifndef DIR_OFFLINE_TIMEOUT_MS
#define DIR_OFFLINE_TIMEOUT_MS 30000	/* if no update for 30s -> treat offline */
#endif

/* NVS key for "last rollout completed" version (packed) */
#ifndef TFOTA_NVS_KEY_VER
#define TFOTA_NVS_KEY_VER "rollout_ver"
#endif

/* ---------------- Directory state ---------------- */
static nrc_node_directory_t g_dir;
static SemaphoreHandle_t g_dir_lock;

static const uint8_t ZERO_MAC[6] = {0,};

/* ---------------- Directory log ---------------- */
#define DIR_LOG(fmt, ...) printf("[DIR] " fmt, ##__VA_ARGS__)

#define U8(v)  ((unsigned)(v))
#define U16(v) ((unsigned)(v))

static const char *dir_role_str(uint8_t role)
{
	switch (role) {
	case ROLE_SOFTAP:  return "ROOT";
	case ROLE_RELAY:   return "RELAY";
	case ROLE_STATION: return "STA";
	default:           return "UNK";
	}
}

static const char *dir_fota_status_str(uint8_t st)
{
	switch (st) {
	case NRC_FOTA_STATUS_IDLE:            return "IDLE";
	case NRC_FOTA_STATUS_IN_PROGRESS:     return "INPROG";
	case NRC_FOTA_STATUS_READY_TO_REBOOT: return "READY";
	case NRC_FOTA_STATUS_REBOOTING:       return "REBOOT";
	case NRC_FOTA_STATUS_DONE:            return "DONE";
	case NRC_FOTA_STATUS_FAILED:          return "FAIL";
	default:                              return "UNK";
	}
}

static void dir_mac_to_str(const uint8_t mac[6], char out[18])
{
	snprintf(out, 18, "%02x:%02x:%02x:%02x:%02x:%02x",
		 mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

static void dir_ip_to_str_nbo(uint32_t ip_nbo, char out[16])
{
	const uint8_t *p = (const uint8_t *)&ip_nbo;
	snprintf(out, 16, "%u.%u.%u.%u", U8(p[0]), U8(p[1]), U8(p[2]), U8(p[3]));
}

static void __attribute__((unused)) dir_print_mac(const char *tag, const uint8_t mac[6])
{
	DIR_LOG("%s %02x:%02x:%02x:%02x:%02x:%02x\n",
		tag,
		mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

static void dir_print_ip_nbo(const char *tag, uint32_t ip_nbo)
{
	const uint8_t *p = (const uint8_t *)&ip_nbo;
	DIR_LOG("%s %u.%u.%u.%u\n", tag, U8(p[0]), U8(p[1]), U8(p[2]), U8(p[3]));
}

void dir_dump_node(const nrc_node_record_t *n, const char *prefix)
{
	if (!n || !n->valid)
		return;

	char macs[18], pmacs[18], ips[16];
	dir_mac_to_str(n->mac, macs);
	dir_mac_to_str(n->parent_mac, pmacs);
	dir_ip_to_str_nbo(n->ipv4_addr, ips);

	DIR_LOG("%s%s hop=%u online=%u ip=%s mac=%s parent=%s app='%s' fw=0x%08" PRIx32 " fota=%s(%u) prog=%u\n",
		(prefix ? prefix : ""),
		dir_role_str(n->role),
		U8(n->hop),
		U8(n->online ? 1 : 0),
		ips, macs, pmacs,
		n->app_name,
		n->fw_ver_packed,
		dir_fota_status_str(n->fota_status),
		U8(n->fota_status),
		U8(n->progress_percent));
}

static uint32_t dir_now_ms(void)
{
	return (uint32_t)(xTaskGetTickCount() * portTICK_PERIOD_MS);
}



static void dir_tfota_maybe_fix_stuck_inprog(nrc_node_record_t *n, uint32_t now_ms)
{
	if (!n || !n->valid)
		return;

	/* Only relevant for nodes that appear alive */
	if (!n->online)
		return;

	if (n->fota_status != NRC_FOTA_STATUS_IN_PROGRESS)
		return;

	/* If we haven't received a STATUS in a long time, assume the TCP session died. */
	if (n->last_status_ms == 0)
		return;

	uint32_t since_status = now_ms - n->last_status_ms;
	uint32_t since_change = (n->last_fota_change_ms) ? (now_ms - n->last_fota_change_ms) : since_status;

	/*
	 * Avoid false positives on poor links.
	 *
	 * We only declare "stuck" when BOTH:
	 *  - STATUS has been silent for a while (no liveness), and
	 *  - progress/status change has been frozen for longer (no forward progress).
	 */
	if (since_status < TFOTA_STUCK_NO_STATUS_MS)
		return;

	if (since_change < TFOTA_STUCK_NO_PROGRESS_MS)
		return;

	DIR_LOG("TFOTA stuck: mac=%02x:%02x:%02x:%02x:%02x:%02x prog=%u -> FAIL (no_status=%ums no_change=%ums)\n",
		n->mac[0], n->mac[1], n->mac[2], n->mac[3], n->mac[4], n->mac[5],
		U8(n->progress_percent), (unsigned)since_status, (unsigned)since_change);

	n->fota_status = NRC_FOTA_STATUS_FAILED;
	n->progress_percent = 0;
	n->last_session_id = 0;
	n->last_fota_change_ms = now_ms;
	n->tfota_backoff_until_ms = now_ms + TFOTA_STUCK_BACKOFF_MS;

	/* bump version so host sees it */
	g_dir.dir_version++;
	g_dir.last_update_ms = now_ms;
}

/* Directory liveness tuning
 * - dir_refresh_ms: how often nodes re-REGISTER (node-side setting, but stored in NVS)
 * - dir_offline_ms: how long root should wait before marking a node offline
 */
static uint32_t dir_get_refresh_ms(void)
{
	return app_dir_refresh_ms();
}

static uint32_t dir_get_offline_timeout_ms_unprov(void)
{
	return app_dir_offline_ms_unprov();
}

static uint32_t dir_get_offline_timeout_ms_prov(void)
{
	return app_dir_offline_ms_prov();
}

static uint32_t dir_get_offline_timeout_ms(void)
{
	if (wifi_is_provisioned())
		return dir_get_offline_timeout_ms_prov();
	return dir_get_offline_timeout_ms_unprov();
}

/* TFOTA guardrails: don't immediately re-push to a node that just rebooted or
 * recently changed FW state. This helps avoid "update again right after reboot"
 * loops when the directory momentarily has stale fw/status information.
 */
#ifndef TFOTA_NODE_STABLE_MS
#define TFOTA_NODE_STABLE_MS          8000   /* wait after REGISTER before pushing */
#endif

#ifndef TFOTA_FW_CHANGE_GRACE_MS
#define TFOTA_FW_CHANGE_GRACE_MS      15000  /* wait after fw_ver change before pushing */
#endif

#ifndef TFOTA_NODE_BACKOFF_MS
#define TFOTA_NODE_BACKOFF_MS         20000  /* per-node backoff after a TFOTA failure */
#endif

#ifndef TFOTA_POST_UPDATE_GRACE_MS
#define TFOTA_POST_UPDATE_GRACE_MS    45000  /* grace after READY_TO_REBOOT/REBOOTING */
#endif

static int find_by_mac(const uint8_t mac[6])
{
	for (int i = 0; i < NRC_MAX_NODES; i++) {
		if (g_dir.nodes[i].valid &&
		    memcmp(g_dir.nodes[i].mac, mac, 6) == 0) {
			return i;
		}
	}
	return -1;
}

static bool dir_tfota_can_start_locked(int idx, uint32_t now_ms)
{
	if (idx < 0 || idx >= NRC_MAX_NODES)
		return false;

	nrc_node_record_t *n = &g_dir.nodes[idx];
	if (!n->valid || !n->online)
		return false;
	if (n->last_register_ms == 0)
		return false;

	/* Let the node settle after boot/association */
	if (n->last_register_ms && (now_ms - n->last_register_ms) < TFOTA_NODE_STABLE_MS)
		return false;

	/* Grace period right after we observe fw version change */
	if (n->last_fw_change_ms && (now_ms - n->last_fw_change_ms) < TFOTA_FW_CHANGE_GRACE_MS)
		return false;

	/* Backoff window after failures */
	if (n->tfota_backoff_until_ms && (int32_t)(now_ms - n->tfota_backoff_until_ms) < 0)
		return false;

	/* If the node reports it is mid-TFOTA or rebooting, do not start a new one */
	if (n->fota_status == NRC_FOTA_STATUS_IN_PROGRESS ||
	    n->fota_status == NRC_FOTA_STATUS_READY_TO_REBOOT ||
	    n->fota_status == NRC_FOTA_STATUS_REBOOTING) {
		return false;
	}

	return true;
}

static bool dir_tfota_can_start(const uint8_t mac[6], uint32_t now_ms)
{
	if (!mac || !g_dir_lock)
		return false;

	bool ok = false;
	if (xSemaphoreTake(g_dir_lock, pdMS_TO_TICKS(50)) == pdTRUE) {
		int idx = find_by_mac(mac);
		ok = dir_tfota_can_start_locked(idx, now_ms);
		xSemaphoreGive(g_dir_lock);
	}
	return ok;
}

static void dir_tfota_set_backoff(const uint8_t mac[6], uint32_t until_ms)
{
	if (!mac || !g_dir_lock)
		return;

	if (xSemaphoreTake(g_dir_lock, pdMS_TO_TICKS(50)) == pdTRUE) {
		int idx = find_by_mac(mac);
		if (idx >= 0) {
			g_dir.nodes[idx].tfota_backoff_until_ms = until_ms;
		}
		xSemaphoreGive(g_dir_lock);
	}
}

static int alloc_slot(void)
{
	for (int i = 0; i < NRC_MAX_NODES; i++) {
		if (!g_dir.nodes[i].valid) {
			memset(&g_dir.nodes[i], 0, sizeof(g_dir.nodes[i]));
			g_dir.nodes[i].valid = true;
			if (g_dir.count < NRC_MAX_NODES)
				g_dir.count++;

			DIR_LOG("alloc_slot(): idx=%d count=%u\n", i, U16(g_dir.count));
			return i;
		}
	}
	DIR_LOG("alloc_slot(): FAILED (directory full)\n");
	return -1;
}

/* ---------------- Public API ---------------- */

void directory_init(system_role_t role)
{
	/* Root only */
	if (role != ROLE_SOFTAP)
		return;

	memset(&g_dir, 0, sizeof(g_dir));
	if (!g_dir_lock)
		g_dir_lock = xSemaphoreCreateMutex();

	DIR_LOG("directory_init(): root enabled, max=%d\n", NRC_MAX_NODES);
}

void directory_on_keepalive(const uint8_t mac[6], uint32_t ipv4_addr_nbo)
{
	if (!g_dir_lock || !mac)
		return;

	xSemaphoreTake(g_dir_lock, portMAX_DELAY);

	int idx = find_by_mac(mac);
	if (idx < 0)
		idx = alloc_slot();
	if (idx < 0) {
		xSemaphoreGive(g_dir_lock);
		return;
	}

	nrc_node_record_t *n = &g_dir.nodes[idx];
	/* If we learned about a node only via keepalive (no REGISTER yet),
	 * don't let the default role=0 (ROLE_SOFTAP) hide it from counters.
	 */
	if (n->node_id == 0 && n->role == ROLE_SOFTAP) {
		n->role = ROLE_RELAY;
		n->hop = 0xFF;
	}
	memcpy(n->mac, mac, 6);
	if (ipv4_addr_nbo)
		n->ipv4_addr = ipv4_addr_nbo;
	n->last_seen_ms = dir_now_ms();
	n->online = true;

	g_dir.dir_version++;
	g_dir.last_update_ms = n->last_seen_ms;

	xSemaphoreGive(g_dir_lock);
}

void directory_on_heartbeat(const nrc_dir_heartbeat_t *hb)
{
	if (!hb || !g_dir_lock)
		return;

	const uint32_t now = dir_now_ms();

	xSemaphoreTake(g_dir_lock, portMAX_DELAY);

	int idx = find_by_mac(hb->mac);
	if (idx < 0)
		idx = alloc_slot();
	if (idx < 0) {
		xSemaphoreGive(g_dir_lock);
		return;
	}

	nrc_node_record_t *n = &g_dir.nodes[idx];
	bool bump_ver = false;

	/* If we learned about a node only via heartbeat (no REGISTER yet),
	 * don't let the default role=0 (ROLE_SOFTAP) hide it from counters.
	 */
	if (n->node_id == 0 && n->role == ROLE_SOFTAP) {
		n->role = ROLE_RELAY;
		n->hop = 0xFF;
		bump_ver = true;
	}

	if (memcmp(n->mac, hb->mac, 6) != 0) {
		memcpy(n->mac, hb->mac, 6);
		bump_ver = true;
	}

	if (hb->ipv4_addr && n->ipv4_addr != hb->ipv4_addr) {
		n->ipv4_addr = hb->ipv4_addr;
		bump_ver = true;
	}

	if (!n->online) {
		n->online = true;
		bump_ver = true;
	}

	n->last_seen_ms = now;

	/* Don't keep DONE sticky forever. After a short grace period,
	 * transition DONE -> IDLE so the directory reflects steady-state.
	 * (We keep DONE briefly so a human can see completion.)
	 */
	if (n->fota_status == NRC_FOTA_STATUS_DONE) {
		if (n->last_fw_change_ms != 0 && (now - n->last_fw_change_ms) > 5000) {
			n->fota_status = NRC_FOTA_STATUS_IDLE;
			n->progress_percent = 0;
			n->last_session_id = 0;
			bump_ver = true;
		}
	}

	/* If the node looks stuck in IN_PROGRESS, force it to FAIL so manager can retry. */
	dir_tfota_maybe_fix_stuck_inprog(n, now);

	if (bump_ver) {
		g_dir.dir_version++;
		g_dir.last_update_ms = now;
	}

	xSemaphoreGive(g_dir_lock);
}

void directory_on_register(const nrc_dir_register_t *reg)
{
	if (!reg || !g_dir_lock)
		return;

	const uint32_t now = dir_now_ms();

	xSemaphoreTake(g_dir_lock, portMAX_DELAY);

	int idx = find_by_mac(reg->mac);
	if (idx < 0)
		idx = alloc_slot();

	if (idx >= 0) {
		nrc_node_record_t *n = &g_dir.nodes[idx];
		const uint32_t old_fw = n->fw_ver_packed;
		char old_app[NRC_APP_NAME_MAX];
		const uint8_t old_fota = n->fota_status;
		const uint8_t old_prog = n->progress_percent;
		const uint32_t old_sess = n->last_session_id;

		memcpy(old_app, n->app_name, sizeof(old_app));

		n->node_id = reg->node_id;
		memcpy(n->mac, reg->mac, 6);
		memcpy(n->parent_mac, reg->parent_mac, 6);

		n->role = reg->role;
		n->hop = reg->hop;

		n->ipv4_addr = reg->ipv4_addr;

		/* Authoritative "post-boot" version from REGISTER */
		n->fw_ver_packed = reg->fw_ver_packed;
		/* Best-effort app name (used to gate TFOTA to matching applications). */
		memset(n->app_name, 0, sizeof(n->app_name));
		if (reg->app_name[0]) {
			strncpy(n->app_name, reg->app_name, sizeof(n->app_name) - 1);
			n->app_name[sizeof(n->app_name) - 1] = '\0';
		}
		if (old_fw != 0 && old_fw != n->fw_ver_packed)
			n->last_fw_change_ms = now;
		else if (old_fw == 0)
			n->last_fw_change_ms = now;

		/* REGISTER after a reboot is our best signal that the node is back up.
		 * If we previously saw READY/REBOOT, translate the transient state into
		 * a terminal result so Root doesn't show "stuck REBOOT" forever.
		 */
		if (old_fota == NRC_FOTA_STATUS_READY_TO_REBOOT ||
		    old_fota == NRC_FOTA_STATUS_REBOOTING) {
			if (old_fw != 0 && old_fw != n->fw_ver_packed) {
				/* Running FW changed => update completed */
				n->fota_status = NRC_FOTA_STATUS_DONE;
				n->progress_percent = 100;
				n->last_session_id = 0;
			} else {
				/* FW did not change (or unknown) => treat as failure */
				n->fota_status = NRC_FOTA_STATUS_FAILED;
				n->progress_percent = 0;
				n->last_session_id = 0;
			}
		}

		n->last_seen_ms = now;
		n->last_register_ms = now;
		n->online = true;

		/* If the node looks stuck in IN_PROGRESS, force it to FAIL so manager can retry. */
		dir_tfota_maybe_fix_stuck_inprog(n, now);

		/* Only bump dir_version if something meaningful changed. */
		bool changed = false;
		if (old_fw != n->fw_ver_packed)
			changed = true;
		if (memcmp(old_app, n->app_name, sizeof(old_app)) != 0)
			changed = true;
		if (old_fota != n->fota_status || old_prog != n->progress_percent || old_sess != n->last_session_id)
			changed = true;

		if (changed) {
			g_dir.dir_version++;
			g_dir.last_update_ms = n->last_seen_ms;
		}

#if DIR_DEBUG
		/* Reduce console spam: print REGISTER only when changed or once per interval */
		if (changed || (n->last_log_ms == 0) || (now - n->last_log_ms) >= DIR_REGISTER_LOG_INTERVAL_MS) {
			char pfx[64];
			snprintf(pfx, sizeof(pfx), "REGISTER idx=%d ver=%" PRIu32 " ", idx, g_dir.dir_version);
			dir_dump_node(n, pfx);
			n->last_log_ms = now;
		}
#endif
	}

	xSemaphoreGive(g_dir_lock);
}

void directory_on_status(const nrc_dir_status_t *st)
{
	if (!st || !g_dir_lock)
		return;

	xSemaphoreTake(g_dir_lock, portMAX_DELAY);

	int idx = find_by_mac(st->mac);
	if (idx < 0)
		idx = alloc_slot();

	if (idx >= 0) {
		nrc_node_record_t *n = &g_dir.nodes[idx];
		const uint32_t now = dir_now_ms();
		const uint8_t old_fota = n->fota_status;
		const uint8_t old_prog = n->progress_percent;
		const bool old_online = n->online;
		const uint32_t old_sess = n->last_session_id;

		n->node_id = st->node_id;
		memcpy(n->mac, st->mac, 6);

		n->last_session_id = st->session_id;
		n->fota_status = st->fota_status;
		n->progress_percent = st->progress_percent;

		/* Track status cadence and progress changes (for stuck-IN_PROGRESS detection) */
		n->last_status_ms = now;
		if (old_fota != n->fota_status || old_prog != n->progress_percent || old_sess != n->last_session_id)
			n->last_fota_change_ms = now;
		n->last_fota_status_seen = n->fota_status;
		n->last_fota_prog_seen = n->progress_percent;


		/* NOTE:
		 * We intentionally do NOT overwrite fw_ver_packed from STATUS.
		 * REGISTER after reboot is authoritative for "new running version".
		 */

		n->last_seen_ms = now;
		n->online = true;

		bool changed = false;
		if (old_fota != n->fota_status || old_prog != n->progress_percent || old_sess != n->last_session_id)
			changed = true;
		if (!old_online && n->online)
			changed = true;
		if (changed) {
			g_dir.dir_version++;
			g_dir.last_update_ms = n->last_seen_ms;
		}

		/* Reduce console spam: print only when meaningful fields change */
		if (changed) {
			char pfx[64];
			snprintf(pfx, sizeof(pfx), "STATUS idx=%d ver=%" PRIu32 " ", idx, g_dir.dir_version);
			dir_dump_node(n, pfx);
		}
	}

	xSemaphoreGive(g_dir_lock);
}

void directory_recompute_hops(void)
{
	if (!g_dir_lock)
		return;

	xSemaphoreTake(g_dir_lock, portMAX_DELAY);

	DIR_LOG("recompute_hops(): start\n");

	for (int i = 0; i < NRC_MAX_NODES; i++) {
		if (!g_dir.nodes[i].valid)
			continue;

		if (g_dir.nodes[i].role == ROLE_SOFTAP ||
		    memcmp(g_dir.nodes[i].parent_mac, ZERO_MAC, 6) == 0) {
			g_dir.nodes[i].hop = 0;
		}
	}

	for (int pass = 0; pass < NRC_MAX_NODES; pass++) {
		bool changed = false;

		for (int i = 0; i < NRC_MAX_NODES; i++) {
			if (!g_dir.nodes[i].valid)
				continue;

			for (int p = 0; p < NRC_MAX_NODES; p++) {
				if (!g_dir.nodes[p].valid)
					continue;

				if (memcmp(g_dir.nodes[i].parent_mac, g_dir.nodes[p].mac, 6) == 0) {
					uint8_t nd = (uint8_t)(g_dir.nodes[p].hop + 1);
					if (g_dir.nodes[i].hop != nd) {
						DIR_LOG("  pass=%d idx=%d hop %u -> %u\n",
							pass, i, U8(g_dir.nodes[i].hop), U8(nd));
						g_dir.nodes[i].hop = nd;
						changed = true;
					}
					break;
				}
			}
		}

		if (!changed) {
			DIR_LOG("recompute_hops(): converged at pass=%d\n", pass);
			break;
		}
	}

	g_dir.dir_version++;
	g_dir.last_update_ms = dir_now_ms();

	DIR_LOG("recompute_hops(): done dir_ver=%" PRIu32 "\n", g_dir.dir_version);

	xSemaphoreGive(g_dir_lock);
}

int directory_get_list(nrc_dir_node_info_t *out, int max, uint32_t *dir_version_out)
{
	if (!out || max <= 0 || !g_dir_lock)
		return 0;

	int count = 0;
	uint32_t now = dir_now_ms();
	
	xSemaphoreTake(g_dir_lock, portMAX_DELAY);

	for (int i = 0; i < NRC_MAX_NODES && count < max; i++) {
		nrc_node_record_t *n = &g_dir.nodes[i];
		if (!n->valid)
			continue;

		/* Compute "effective" online with staleness */
		bool online = n->online;
		if (online && (now - n->last_seen_ms) > dir_get_offline_timeout_ms())
			online = false;

		nrc_dir_node_info_t *o = &out[count++];

		memset(o, 0, sizeof(*o));
		o->node_id = n->node_id;

		memcpy(o->mac, n->mac, 6);
		memcpy(o->parent_mac, n->parent_mac, 6);

		o->role = n->role;
		o->hop = n->hop;
		o->online = online ? 1 : 0;

		o->ipv4_addr = n->ipv4_addr;
		o->fw_ver_packed = n->fw_ver_packed;
		memset(o->app_name, 0, sizeof(o->app_name));
		if (n->app_name[0]) {
			strncpy(o->app_name, n->app_name, sizeof(o->app_name) - 1);
			o->app_name[sizeof(o->app_name) - 1] = '\0';
		}
		o->session_id = n->last_session_id;
		o->fota_status = n->fota_status;
		o->progress_percent = n->progress_percent;
	}

	if (dir_version_out)
		*dir_version_out = g_dir.dir_version;

	xSemaphoreGive(g_dir_lock);
	return count;
}

/* ---------------- Convenience helpers (root-side) ---------------- */

static bool dir_node_online_locked(const nrc_node_record_t *n, uint32_t now_ms)
{
	if (!n || !n->valid)
		return false;
	if (!n->online)
		return false;
	if ((now_ms - n->last_seen_ms) > dir_get_offline_timeout_ms())
		return false;
	return true;
}

int directory_get_active_count(void)
{
	if (!g_dir_lock)
		return 0;

	uint32_t now = dir_now_ms();
	int cnt = 0;

	xSemaphoreTake(g_dir_lock, portMAX_DELAY);
	for (int i = 0; i < NRC_MAX_NODES; i++) {
		nrc_node_record_t *n = &g_dir.nodes[i];
		if (!dir_node_online_locked(n, now))
			continue;
		if (n->role == ROLE_SOFTAP)
			continue;
		cnt++;
	}
	xSemaphoreGive(g_dir_lock);
	return cnt;
}

static int dir_count_flag(uint8_t flag)
{
	if (!g_dir_lock)
		return 0;
	uint32_t now = dir_now_ms();
	int cnt = 0;
	xSemaphoreTake(g_dir_lock, portMAX_DELAY);
	for (int i = 0; i < NRC_MAX_NODES; i++) {
		nrc_node_record_t *n = &g_dir.nodes[i];
		if (!dir_node_online_locked(n, now))
			continue;
		if (n->role == ROLE_SOFTAP)
			continue;
		if (n->prov_flags & flag)
			cnt++;
	}
	xSemaphoreGive(g_dir_lock);
	return cnt;
}

int directory_get_config_updated_count(void)
{
	return dir_count_flag(DIR_PROV_FLAG_CONFIG_UPDATED);
}

int directory_get_reboot_ack_count(void)
{
	return dir_count_flag(DIR_PROV_FLAG_REBOOT_ACK);
}

int directory_get_factoryreset_ack_count(void)
{
	return dir_count_flag(DIR_PROV_FLAG_FACTORYRESET_ACK);
}

static int dir_find_or_alloc_locked(const uint8_t mac[6])
{
	int idx = find_by_mac(mac);
	if (idx < 0)
		idx = alloc_slot();
	return idx;
}

static void dir_set_flag_locked(const uint8_t mac[6], uint8_t flag, bool on)
{
	if (!mac)
		return;
	int idx = dir_find_or_alloc_locked(mac);
	if (idx < 0)
		return;
	nrc_node_record_t *n = &g_dir.nodes[idx];
	memcpy(n->mac, mac, 6);
	if (on)
		n->prov_flags |= flag;
	else
		n->prov_flags &= (uint8_t)~flag;
	g_dir.dir_version++;
	g_dir.last_update_ms = dir_now_ms();
}

static bool dir_get_flag_locked(const uint8_t mac[6], uint8_t flag)
{
	int idx = find_by_mac(mac);
	if (idx < 0)
		return false;
	return (g_dir.nodes[idx].prov_flags & flag) ? true : false;
}

bool directory_is_config_updated(const uint8_t mac[6])
{
	bool v = false;
	if (!g_dir_lock || !mac)
		return false;
	xSemaphoreTake(g_dir_lock, portMAX_DELAY);
	v = dir_get_flag_locked(mac, DIR_PROV_FLAG_CONFIG_UPDATED);
	xSemaphoreGive(g_dir_lock);
	return v;
}

bool directory_is_reboot_acked(const uint8_t mac[6])
{
	bool v = false;
	if (!g_dir_lock || !mac)
		return false;
	xSemaphoreTake(g_dir_lock, portMAX_DELAY);
	v = dir_get_flag_locked(mac, DIR_PROV_FLAG_REBOOT_ACK);
	xSemaphoreGive(g_dir_lock);
	return v;
}

bool directory_is_factoryreset_acked(const uint8_t mac[6])
{
	bool v = false;
	if (!g_dir_lock || !mac)
		return false;
	xSemaphoreTake(g_dir_lock, portMAX_DELAY);
	v = dir_get_flag_locked(mac, DIR_PROV_FLAG_FACTORYRESET_ACK);
	xSemaphoreGive(g_dir_lock);
	return v;
}

void directory_mark_config_updated(const uint8_t mac[6], bool on)
{
	if (!g_dir_lock || !mac)
		return;
	xSemaphoreTake(g_dir_lock, portMAX_DELAY);
	dir_set_flag_locked(mac, DIR_PROV_FLAG_CONFIG_UPDATED, on);
	xSemaphoreGive(g_dir_lock);
}

void directory_mark_reboot_ack(const uint8_t mac[6], bool on)
{
	if (!g_dir_lock || !mac)
		return;
	xSemaphoreTake(g_dir_lock, portMAX_DELAY);
	dir_set_flag_locked(mac, DIR_PROV_FLAG_REBOOT_ACK, on);
	xSemaphoreGive(g_dir_lock);
}

void directory_mark_factoryreset_ack(const uint8_t mac[6], bool on)
{
	if (!g_dir_lock || !mac)
		return;
	xSemaphoreTake(g_dir_lock, portMAX_DELAY);
	dir_set_flag_locked(mac, DIR_PROV_FLAG_FACTORYRESET_ACK, on);
	xSemaphoreGive(g_dir_lock);
}

void directory_clear_prov_flags_all(uint8_t mask)
{
	if (!g_dir_lock || mask == 0)
		return;
	xSemaphoreTake(g_dir_lock, portMAX_DELAY);
	for (int i = 0; i < NRC_MAX_NODES; i++) {
		if (!g_dir.nodes[i].valid)
			continue;
		g_dir.nodes[i].prov_flags &= (uint8_t)~mask;
	}
	g_dir.dir_version++;
	g_dir.last_update_ms = dir_now_ms();
	xSemaphoreGive(g_dir_lock);
}

/* ---------------- Root servers ---------------- */

static void directory_udp_task(void *arg)
{
	(void)arg;

	int s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)
		vTaskDelete(NULL);

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(app_tfota_ctrl_port());
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		close(s);
		vTaskDelete(NULL);
	}

	uint8_t buf[256];

	DIR_LOG("UDP server start (port=%u)\n", (unsigned)app_tfota_ctrl_port());

	while (1) {
		struct sockaddr_in from;
		socklen_t fl = sizeof(from);

		int r = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *)&from, &fl);
		if (r < (int)sizeof(nrc_dir_hdr_t))
			continue;

		nrc_dir_hdr_t *hdr = (nrc_dir_hdr_t *)buf;
		if (hdr->magic != NRC_MAGIC_DIR)
			continue;

		if (hdr->type == NRC_DIR_MSG_REGISTER) {
			if (r >= (int)sizeof(nrc_dir_register_t)) {
				nrc_dir_register_t *reg = (nrc_dir_register_t *)buf;
				directory_on_register(reg);

				/* Reliability: ACK REGISTER so the node can retry on loss */
				nrc_dir_ack_t ack;
				memset(&ack, 0, sizeof(ack));
				ack.hdr.magic = NRC_MAGIC_DIR;
				ack.hdr.type  = NRC_DIR_MSG_ACK;
				ack.hdr.len   = sizeof(ack);
				ack.hdr.seq   = reg->hdr.seq;
				ack.acked_type = NRC_DIR_MSG_REGISTER;
				ack.code = 0;
				ack.dir_version = g_dir.dir_version;
				ack.node_id = reg->node_id;
				memcpy(ack.mac, reg->mac, 6);
				sendto(s, &ack, sizeof(ack), 0, (struct sockaddr *)&from, fl);
			}
		} else if (hdr->type == NRC_DIR_MSG_STATUS) {
			if (r >= (int)sizeof(nrc_dir_status_t))
				directory_on_status((nrc_dir_status_t *)buf);
		} else if (hdr->type == NRC_DIR_MSG_HEARTBEAT) {
			if (r >= (int)sizeof(nrc_dir_heartbeat_t)) {
				nrc_dir_heartbeat_t *hb = (nrc_dir_heartbeat_t *)buf;
				directory_on_heartbeat(hb);

				/* Reliability: ACK HEARTBEAT so the node can detect Root reachability.
				 * This mirrors the legacy keepalive echo/ACK behavior.
				 */
				nrc_dir_ack_t ack;
				memset(&ack, 0, sizeof(ack));
				ack.hdr.magic = NRC_MAGIC_DIR;
				ack.hdr.type  = NRC_DIR_MSG_ACK;
				ack.hdr.len   = sizeof(ack);
				ack.hdr.seq   = hb->hdr.seq;
				ack.acked_type = NRC_DIR_MSG_HEARTBEAT;
				ack.code = 0;
				ack.dir_version = g_dir.dir_version;
				ack.node_id = 0; /* optional; node may validate by MAC+SEQ only */
				memcpy(ack.mac, hb->mac, 6);
				sendto(s, &ack, sizeof(ack), 0, (struct sockaddr *)&from, fl);
			}
		}
	}
}

#if DIR_ENABLE_TCP
static void directory_tcp_task(void *arg)
{
	(void)arg;

	int s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0)
		vTaskDelete(NULL);

	int opt = 1;
	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(app_tfota_ctrl_port());
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		close(s);
		vTaskDelete(NULL);
	}

	listen(s, 2);

	DIR_LOG("TCP server start (port=%u)\n", (unsigned)app_tfota_ctrl_port());

	while (1) {
		int c = accept(s, NULL, NULL);
		if (c < 0)
			continue;

		while (1) {
			nrc_dir_hdr_t hdr;
			int r = recv(c, &hdr, sizeof(hdr), MSG_WAITALL);
			if (r != (int)sizeof(hdr))
				break;

			if (hdr.magic != NRC_MAGIC_DIR || hdr.len < sizeof(hdr))
				break;

			if (hdr.type == NRC_DIR_MSG_GET_LIST) {
				nrc_dir_get_list_t req;
				memcpy(&req.hdr, &hdr, sizeof(hdr));

				if (hdr.len != sizeof(req))
					break;

				r = recv(c, ((uint8_t *)&req) + sizeof(hdr),
					 sizeof(req) - sizeof(hdr), MSG_WAITALL);
				if (r != (int)(sizeof(req) - sizeof(hdr)))
					break;

				uint16_t max = req.max_nodes ? req.max_nodes : NRC_MAX_NODES;
				if (max > NRC_MAX_NODES)
					max = NRC_MAX_NODES;

				nrc_dir_node_info_t *nodes = (nrc_dir_node_info_t *)pvPortMalloc(sizeof(nrc_dir_node_info_t) * max);
				uint32_t dir_ver = 0;
				int count = 0;
				if (nodes)
					count = directory_get_list(nodes, max, &dir_ver);

				uint16_t payload_len = (uint16_t)(count * sizeof(nrc_dir_node_info_t));
				uint16_t resp_len = (uint16_t)(sizeof(nrc_dir_list_resp_t) + payload_len);

				uint8_t *resp_buf = (uint8_t *)pvPortMalloc(resp_len);
				if (!resp_buf) {
					if (nodes)
						vPortFree(nodes);
					break;
				}

				nrc_dir_list_resp_t *resp = (nrc_dir_list_resp_t *)resp_buf;
				memset(resp, 0, resp_len);

				resp->hdr.magic = NRC_MAGIC_DIR;
				resp->hdr.type = NRC_DIR_MSG_LIST_RESP;
				resp->hdr.len = resp_len;
				resp->hdr.seq = hdr.seq;

				resp->count = (uint16_t)count;
				resp->dir_version = dir_ver;

				if (payload_len && nodes)
					memcpy(resp->payload, nodes, payload_len);

				send(c, resp_buf, resp_len, 0);
				if (nodes)
					vPortFree(nodes);
				vPortFree(resp_buf);
			} else {
				break;
			}
		}

		close(c);
	}
}
#endif /* DIR_ENABLE_TCP */

/* ---------------- Root TFOTA manager ---------------- */
#if TFOTA_MANAGER_ENABLE

/* Your SF_FW_INFO format (len/crc). */
typedef struct __attribute__((packed)) {
	uint32_t fw_length;
	uint32_t crc;
	uint32_t ready;
} fota_info_flash_t;

/* Provided by your Root-side TFOTA sender (matches your wire format) */
extern int tfota_push_to_relay(uint32_t relay_ip_nbo,
			       uint32_t fw_ver_packed,
			       uint32_t fw_len,
			       uint32_t fw_crc);

/* Low-level SF read (should already be declared by your SDK headers) */
extern uint32_t nrc_sf_read(uint32_t address, uint8_t *buffer, size_t size);

/* ---- NVS helpers ---- */

static uint32_t tfota_root_get_nvs_fw_ver(void)
{
	nvs_handle_t h;
	uint32_t ver = 0;

	if (nvs_open(NVS_DEFAULT_NAMESPACE, NVS_READWRITE, &h) != NVS_OK)
		return 0;

	if (nvs_get_u32(h, TFOTA_NVS_KEY_VER, &ver) != NVS_OK)
		ver = 0;

	nvs_close(h);
	return ver;
}

static void tfota_root_set_nvs_fw_ver(uint32_t ver)
{
	nvs_handle_t h;

	if (nvs_open(NVS_DEFAULT_NAMESPACE, NVS_READWRITE, &h) != NVS_OK)
		return;

	(void)nvs_set_u32(h, TFOTA_NVS_KEY_VER, ver);
	(void)nvs_commit(h);
	nvs_close(h);
}

/* ---- Version packing ---- */

static uint32_t tfota_pack_ver(const VERSION_T *v)
{
	if (!v)
		return 0;

	return ((uint32_t)v->major << 24) |
	       ((uint32_t)v->minor << 16) |
	       ((uint32_t)v->patch <<  8);
}

static uint32_t tfota_root_get_running_fw_ver(void)
{
	return tfota_pack_ver(nrc_get_app_version());
}

/* ---- SF_FW_INFO helpers ---- */

static bool tfota_root_read_fota_info(fota_info_flash_t *out)
{
	if (!out)
		return false;

	memset(out, 0, sizeof(*out));
	nrc_sf_read(SF_FW_INFO, (uint8_t *)out, sizeof(*out));

	/* Basic validity checks for len/crc */
	if (!out->fw_length || out->fw_length == 0xFFFFFFFF)
		return false;
	if (!out->crc || out->crc == 0xFFFFFFFF)
		return false;

	/* Optional size guard if you have util_fota_get_max_fw_size() available */
#ifdef util_fota_get_max_fw_size
	if (out->fw_length > util_fota_get_max_fw_size())
		return false;
#endif

	return true;
}

/* ---- Sorting ---- */

static inline uint8_t dir_norm_hop(uint8_t hop)
{
	return (hop == 255) ? 0 : hop;
}

static inline int dir_role_pri(uint8_t role)
{
#if TFOTA_MANAGER_LEAF_FIRST
	if (role == ROLE_STATION)
		return 0; /* leaf first */
	if (role == ROLE_RELAY)
		return 1;
	return 2;
#else
	(void) role;
	return 0;
#endif
}

static int cmp_hop_then_mac(const void *a, const void *b)
{
	const nrc_dir_node_info_t *na = (const nrc_dir_node_info_t *) a;
	const nrc_dir_node_info_t *nb = (const nrc_dir_node_info_t *) b;

#if TFOTA_MANAGER_LEAF_FIRST
	int pra = dir_role_pri(na->role);
	int prb = dir_role_pri(nb->role);
	if (pra != prb)
		return pra - prb;

	int ha = (int) dir_norm_hop(na->hop);
	int hb = (int) dir_norm_hop(nb->hop);
	if (ha != hb)
		return hb - ha; /* hop DESC: farthest first */
#else
	int ha = (int) dir_norm_hop(na->hop);
	int hb = (int) dir_norm_hop(nb->hop);
	if (ha != hb)
		return ha - hb; /* hop ASC: closest first */
#endif

	return memcmp(na->mac, nb->mac, sizeof(na->mac));
}

/* ---- Rollout completion check ----
 * We treat rollout complete only when all known RELAY records match target.
 * (Safe: keeps rollout "pending" until stragglers reconnect and REGISTER.)
 */
static bool tfota_rollout_complete(const nrc_dir_node_info_t *nodes, int n, uint32_t target_ver)
{
	for (int i = 0; i < n; i++) {
		if (nodes[i].role != ROLE_RELAY && nodes[i].role != ROLE_STATION)
			continue;

		/* fw_ver_packed==0 means "unknown" -> treat as not complete */
		if (nodes[i].fw_ver_packed != target_ver)
			return false;
	}
	return true;
}

/* ---- Log rate limiter for repeated invalid states ---- */
static bool should_log_every(uint32_t *last_ms, uint32_t period_ms)
{
	uint32_t now = dir_now_ms();
	if (*last_ms == 0 || (now - *last_ms) >= period_ms) {
		*last_ms = now;
		return true;
	}
	return false;
}

static uint32_t nrc_get_time_ms(void)
{
	return (uint32_t)(xTaskGetTickCount() * portTICK_PERIOD_MS);
}

static void tfota_manager_task(void *arg)
{
	(void)arg;

	uint8_t updating_mac[6] = {0,};
	uint32_t updating_start_ms = 0;
	bool updating = false;

	/* Log suppression timers */
	uint32_t last_bad_info_log_ms = 0;

	uint32_t boot_ms = nrc_get_time_ms();

	/* Rollout state:
	 * - stored_ver: last version we consider "completed rollout"
	 * - target_ver: current running version (what relays should get)
	 */
	while (1) {
		uint32_t now_ms = nrc_get_time_ms();
		if ((uint32_t)(now_ms - boot_ms) < TFOTA_MANAGER_STARTUP_DELAY_MS) {
			_delay_ms(500);
			continue;
		}

		uint32_t running_ver = tfota_root_get_running_fw_ver();
		if (!running_ver) {
			_delay_ms(TFOTA_MANAGER_POLL_MS);
			continue;
		}

		uint32_t stored_ver = tfota_root_get_nvs_fw_ver();
		if (stored_ver == 0) {
			/* First boot / uninitialized: record current version.
			 * NOTE: we still keep enforcing updates for late/joining relays based on
			 * the staged image (SF_FW_INFO) below, so do NOT early-return here.
			 */
			tfota_root_set_nvs_fw_ver(running_ver);
			stored_ver = running_ver;
		}

		/* Need staged image metadata from SF_FW_INFO */
		fota_info_flash_t fi;
		if (!tfota_root_read_fota_info(&fi)) {
			if (should_log_every(&last_bad_info_log_ms, 60000)) {
				DIR_LOG("[TFOTA] SF_FW_INFO invalid (len/crc) @0x%08x\n", (unsigned)SF_FW_INFO);
			}
			_delay_ms(TFOTA_MANAGER_POLL_MS);
			continue;
		}

		/* The version we want relays to run.
		 *
		 * NOTE: SF_FW_INFO (fota_info_flash_t) only carries length/crc in
		 * this project, so we cannot derive a "staged image" version from it.
		 * Therefore, use the root's running version (which you can also persist
		 * in NVS as app_version).
		 */
		uint32_t target_ver = running_ver;
		/* Note: even if stored_ver == target_ver (no root firmware change),
		 * we still want to heal/update "straggler" relays that come online later
		 * with an older version.
		 */

		uint32_t fw_len = fi.fw_length;
		uint32_t fw_crc = fi.crc;

		/* Snapshot directory */
		nrc_dir_node_info_t *nodes = (nrc_dir_node_info_t *)pvPortMalloc(sizeof(nrc_dir_node_info_t) * NRC_MAX_NODES);
		uint32_t dir_ver = 0;
		if (!nodes) {
			_delay_ms(TFOTA_MANAGER_POLL_MS);
			continue;
		}
		int n = directory_get_list(nodes, NRC_MAX_NODES, &dir_ver);
		if (n <= 0) {
			vPortFree(nodes);
			_delay_ms(TFOTA_MANAGER_POLL_MS);
			continue;
		}

		/* Sort by hop so we update closer relays first */
		for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n; j++) {
				if (cmp_hop_then_mac(&nodes[i], &nodes[j]) > 0) {
					nrc_dir_node_info_t tmp = nodes[i];
					nodes[i] = nodes[j];
					nodes[j] = tmp;
				}
			}
		}

		uint32_t now = dir_now_ms();
		const char *target_app = (const char *)nrc_get_app_name();
		if (!target_app)
			target_app = "";

		/* If we're updating someone, wait until:
		 * - they re-register with new fw_ver_packed, OR
		 * - timeout, OR
		 * - failure reported
		 */
		if (updating) {
			bool found = false;
			for (int i = 0; i < n; i++) {
				if (memcmp(nodes[i].mac, updating_mac, 6) == 0) {
					found = true;

					if (nodes[i].fw_ver_packed == target_ver) {
						DIR_LOG("[TFOTA] DONE mac=%02x:%02x:%02x:%02x:%02x:%02x\n",
							updating_mac[0], updating_mac[1], updating_mac[2],
							updating_mac[3], updating_mac[4], updating_mac[5]);
						updating = false;
						memset(updating_mac, 0, sizeof(updating_mac));
						break;
					}

					/* The node finished flashing and is about to reboot. Give it some grace
					 * time to restart and re-REGISTER before we ever consider pushing again.
					 */
					if (nodes[i].fota_status == NRC_FOTA_STATUS_READY_TO_REBOOT ||
						nodes[i].fota_status == NRC_FOTA_STATUS_REBOOTING) {
						DIR_LOG("[TFOTA] POST-UPDATE mac=%02x:%02x:%02x:%02x:%02x:%02x status=%u\n",
							updating_mac[0], updating_mac[1], updating_mac[2],
							updating_mac[3], updating_mac[4], updating_mac[5],
							nodes[i].fota_status);
						dir_tfota_set_backoff(updating_mac, now + TFOTA_POST_UPDATE_GRACE_MS);
						updating = false;
						memset(updating_mac, 0, sizeof(updating_mac));
						break;
					}

					if (nodes[i].fota_status == NRC_FOTA_STATUS_FAILED) {
						DIR_LOG("[TFOTA] FAIL mac=%02x:%02x:%02x:%02x:%02x:%02x\n",
							updating_mac[0], updating_mac[1], updating_mac[2],
							updating_mac[3], updating_mac[4], updating_mac[5]);
						dir_tfota_set_backoff(updating_mac, now + TFOTA_NODE_BACKOFF_MS);
						updating = false;
						memset(updating_mac, 0, sizeof(updating_mac));
						break;
					}
				}
			}

			if (updating && (!found || (now - updating_start_ms) > TFOTA_MANAGER_TIMEOUT_MS)) {
				DIR_LOG("[TFOTA] TIMEOUT mac=%02x:%02x:%02x:%02x:%02x:%02x\n",
					updating_mac[0], updating_mac[1], updating_mac[2],
					updating_mac[3], updating_mac[4], updating_mac[5]);
				dir_tfota_set_backoff(updating_mac, now + TFOTA_NODE_BACKOFF_MS);
				updating = false;
				memset(updating_mac, 0, sizeof(updating_mac));
			}

			vPortFree(nodes);
			_delay_ms(TFOTA_MANAGER_POLL_MS);
			continue;
		}

			/* If rollout appears complete, commit NVS only when it changes.
			 * (Avoid NVS wear + log spam while maintaining "target" for next boot.)
			 */
			if (tfota_rollout_complete(nodes, n, target_ver)) {
				if (stored_ver != target_ver) {
					DIR_LOG("[TFOTA] rollout complete: stored=0x%08" PRIx32 " -> target=0x%08" PRIx32 "\n",
						stored_ver, target_ver);
					tfota_root_set_nvs_fw_ver(target_ver);
					stored_ver = target_ver;
				}
				vPortFree(nodes);
				_delay_ms(TFOTA_MANAGER_POLL_MS);
				continue;
			}

		/* Find first outdated ONLINE relay and start update */
		for (int i = 0; i < n; i++) {
			if (!nodes[i].online)
				continue;
			if (nodes[i].role != ROLE_RELAY && nodes[i].role != ROLE_STATION)
				continue;
			/* Gate TFOTA by app name to avoid pushing the wrong image. */
			if (!nodes[i].app_name[0])
				continue;
			if (strncmp(nodes[i].app_name, target_app, NRC_APP_NAME_MAX) != 0)
				continue;
			if (nodes[i].ipv4_addr == 0)
				continue;

			if (nodes[i].fw_ver_packed == target_ver)
				continue;

			/* Extra guardrails: wait for REGISTER settle time and per-node backoff */
			if (!dir_tfota_can_start(nodes[i].mac, now))
				continue;

			DIR_LOG("[TFOTA] START mac=%02x:%02x:%02x:%02x:%02x:%02x ip=%u.%u.%u.%u hop=%u cur=0x%08" PRIx32 " tgt=0x%08" PRIx32 " len=%" PRIu32 " crc=0x%08" PRIx32 "\n",
				nodes[i].mac[0], nodes[i].mac[1], nodes[i].mac[2],
				nodes[i].mac[3], nodes[i].mac[4], nodes[i].mac[5],
				((uint8_t *)&nodes[i].ipv4_addr)[0], ((uint8_t *)&nodes[i].ipv4_addr)[1],
				((uint8_t *)&nodes[i].ipv4_addr)[2], ((uint8_t *)&nodes[i].ipv4_addr)[3],
				U8(nodes[i].hop),
				nodes[i].fw_ver_packed, target_ver,
				fw_len, fw_crc);

			if (tfota_push_to_relay(nodes[i].ipv4_addr, target_ver, fw_len, fw_crc) == 0) {
				memcpy(updating_mac, nodes[i].mac, 6);
				updating_start_ms = now;
				updating = true;
			} else {
				DIR_LOG("[TFOTA] push failed (connect/send)\n");
				dir_tfota_set_backoff(nodes[i].mac, now + TFOTA_NODE_BACKOFF_MS);
			}
			break; /* one at a time */
		}

		vPortFree(nodes);
		_delay_ms(TFOTA_MANAGER_POLL_MS);
	}
}
#endif /* TFOTA_MANAGER_ENABLE */

void start_directory_server(system_role_t role)
{
	if (role != ROLE_SOFTAP)
		return;

	directory_init(role);

	DIR_LOG("Creating directory tasks (udp%s)...\n",
		DIR_ENABLE_TCP ? "/tcp" : "");

	xTaskCreate(directory_udp_task, "dir_udp", 2048, NULL,
		    tskIDLE_PRIORITY + 2, NULL);

#if DIR_ENABLE_TCP
	xTaskCreate(directory_tcp_task, "dir_tcp", 3072, NULL,
		    tskIDLE_PRIORITY + 2, NULL);
#endif

#if TFOTA_MANAGER_ENABLE
	xTaskCreate(tfota_manager_task, "tfota_mgr", 4096, NULL,
		    tskIDLE_PRIORITY + 2, NULL);
#endif
}

nrc_node_directory_t *directory_get_dir(void)
{
	return &g_dir;
}
