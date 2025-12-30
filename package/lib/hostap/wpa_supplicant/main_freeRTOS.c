/*
 * WPA Supplicant / Example program entrypoint
 * Copyright (c) 2003-2005, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#include "includes.h"
#include "common.h"
#include "wpa_supplicant_i.h"
#include "FreeRTOS.h"
#include "system_common.h"
#include "lmac_common.h"
#include "driver_nrc.h"
#include "driver_nrc_scan.h"
#include "wpa_debug.h"
#include "ctrl_iface_freeRTOS.h"
#include "config.h"
#include "eap_peer/eap_i.h"
#include "system_recovery.h"
#include "system_modem_api.h"
#include "hostapd.h"
#include "wpa_auth.h"
#include "wpa_auth_i.h"
#include "sta_info.h"
#include "ap_drv_ops.h"
#include "ieee802_11.h"
#include "pmksa_cache_auth.h"
#include "scan.h"
#include "bss.h"
#include "dpp.h"
#include "dpp_i.h"
#include "wpa.h"
#include "wpa_i.h"
#include "pmksa_cache.h"
#include "nrc_ps_api.h"

#define IFNAME_PREFIX "wlan"
struct wpa_global *global = NULL;

static inline void wpas_set_blob(struct wpa_supplicant *wpa_s, const char *name, const char *data)
{
	struct wpa_config_blob *blob = os_zalloc(sizeof(struct wpa_config_blob));
	blob->name = os_strdup(name);
	blob->data = (u8 *)os_strdup(data);
	blob->len = os_strlen(data) + 1;
	blob->next = wpa_s->conf->blobs;
	wpa_s->conf->blobs = blob;
}

char * wpas_config_get(int vif_id, const char *name)
{
	struct wpa_supplicant *wpa_s = wpas_iface_init(vif_id);
	if (!wpa_s) {
		return NULL;
	}

	struct wpa_ssid *ssid = wpa_config_get_network(wpa_s->conf, 0);
	/* Caution: some returned memory must be freed by you */
	return wpa_config_get(ssid, name);
}

int wpas_config_set(int vif_id, const char *name, char *value)
{
	struct wpa_supplicant *wpa_s = wpas_iface_init(vif_id);
	if (!wpa_s) {
		return -1;
	}

	struct wpa_ssid *ssid = wpa_config_get_network(wpa_s->conf, 0);
	return wpa_config_set(ssid, name, value, 0);
}

int wpas_config_global_get(int vif_id, const char *name, char *buf, size_t buflen)
{
	struct wpa_supplicant *wpa_s = wpas_iface_init(vif_id);
	if (!wpa_s) {
		return -1;
	}

	return wpa_config_get_value(name, wpa_s->conf, buf, buflen);
}

#define MAX_CONFIG_LINE_SIZE 512
int wpas_config_global_set(int vif_id, const char *name, char *value)
{
	struct wpa_supplicant *wpa_s = wpas_iface_init(vif_id);
	if (!wpa_s) {
		return -1;
	}

	char config_line[MAX_CONFIG_LINE_SIZE];
	os_snprintf(config_line, sizeof(config_line), "%s=%s", name, value);

	return wpa_config_process_global(wpa_s->conf, config_line, 0);
}

#if defined(INCLUDE_SOFT_AP)
int wpas_ap_remove_sta(int vif_id, uint16_t aid)
{
#if defined(INCLUDE_FAST_CONNECT)
	if (!system_modem_api_get_fc()) {
		return -1;
	}
#endif /* INCLUDE_FAST_CONNECT */

	if (system_recovery_wifi_ap_get_in_recovery()) {
		return -1;
	}

	if (system_recovery_wifi_ap_free_sta(aid) > 0) {
#if defined(INCLUDE_FAST_CONNECT)
		/* Clear retention for bridged & unassociated STA */
		if (system_recovery_wifi_ap_get_num_sta() == 0 &&
			system_recovery_wifi_ap_get_active_bridgeif(vif_id) == VIF_MAX) {
			system_modem_api_remove_fc_sta();
		}

		if (system_modem_api_write_fc_ap(false)) {
			wpa_printf(MSG_INFO, "%d WPA STA[%d] retention cleared",
				vif_id, aid);
			return 0;
		} else {
			wpa_printf(MSG_ERROR, "%d Failed to clear WPA STA[%d]",
				vif_id, aid);
			return -1;
		}
#else
		return 0;
#endif /* INCLUDE_FAST_CONNECT */
	} else {
		wpa_printf(MSG_ERROR, "%d Failed to remove STA[%d]", vif_id, aid);
		return -1;
	}
}

int wpas_ap_update_sta(int vif_id, const uint8_t *addr)
{
	struct wpa_supplicant *wpa_s = wpas_iface_init(vif_id);
	struct hostapd_data *hapd = NULL;
	struct sta_info *sta = NULL;
	recovery_sta_config_t *config;
	int config_size = sizeof(recovery_sta_config_t);

#if defined(INCLUDE_FAST_CONNECT)
	if (!system_modem_api_get_fc()) {
		return -1;
	}
#endif /* INCLUDE_FAST_CONNECT */

	if (system_recovery_wifi_ap_get_in_recovery()) {
		return -1;
	}

	if (!wpa_s || !wpa_s->ap_iface) {
		wpa_printf(MSG_ERROR, "%d No AP interface", vif_id);
		return -1;
	}

	hapd = wpa_s->ap_iface->bss[0];
	if (!hapd) {
		wpa_printf(MSG_ERROR, "%d No hostapd data", vif_id);
		return -1;
	}

	sta = ap_get_sta(hapd, addr);
	if (sta == NULL || sta->aid <= 0) {
		return wpas_ap_remove_sta(vif_id, sta->aid);
	}

	/* Fill STA info */
	config = system_recovery_wifi_ap_alloc_sta(sta->aid, addr);
	if (!config) {
		wpa_printf(MSG_ERROR, "%d Failed to allocate STA["MACSTR"]",
			vif_id, MAC2STR(addr));
		return -1;
	}

	if (sta->wpa_sm) {
		os_memcpy(config->kck, sta->wpa_sm->PTK.kck, sizeof(config->kck));
		os_memcpy(config->kek, sta->wpa_sm->PTK.kek, sizeof(config->kek));
		os_memcpy(config->tk, sta->wpa_sm->PTK.tk, sizeof(config->tk));

#if defined(PMKSA_CACHE_RECOVERY)
		struct rsn_pmksa_cache_entry *pmksa =
			wpa_auth_pmksa_get(hapd->wpa_auth, sta->addr, NULL);
		if (pmksa) {
			os_memcpy(config->pmk, pmksa->pmk, sizeof(config->pmk));
			os_memcpy(config->pmkid, pmksa->pmkid, sizeof(config->pmkid));
		}
#endif /* PMKSA_CACHE_RECOVERY */

#if defined(GTK_REKEY_RECOVERY)
		os_memcpy(config->replay_counter, sta->wpa_sm->key_replay[0].counter,
			sizeof(config->replay_counter));
#endif /* GTK_REKEY_RECOVERY */
	}

	STAINFO *sta_info = get_stainfo_by_aid(vif_id, sta->aid);
	if (sta_info) {
		memcpy(&config->s1g_capability, &sta_info->m_s1g, sizeof(S1G_CAPA));
	}

#if defined(INCLUDE_FAST_CONNECT)
	/* Save retention for bridged & unassociated STA */
	if (system_recovery_wifi_ap_get_num_sta() == 1 &&
		system_recovery_wifi_ap_get_active_bridgeif(vif_id) == VIF_MAX) {
		system_modem_api_write_fc_sta(false);
	}

	if (!system_modem_api_write_fc_ap(false)) {
		wpa_printf(MSG_ERROR, "%d Failed to flash STA["MACSTR"]",
			vif_id, MAC2STR(addr));
		return -1;
	}
#endif

	wpa_printf(MSG_INFO, "%d WPA STA["MACSTR"] retention updated(%dB)",
		vif_id, MAC2STR(addr), config_size);
	return config_size;
}

static int wpas_ap_sta_recovery(int vif_id, struct hostapd_data *hapd,
				void *sta_config, uint16_t auth_alg)
{
	int ret = -1;
	struct sta_info *sta = NULL;
	struct wpa_state_machine *sm = NULL;
	struct ieee80211_ht_capabilities ht_cap;
	recovery_sta_config_t *config = (recovery_sta_config_t *) sta_config;

	if (!config || config->aid == 0) {
		return -1;
	}

	if (!hapd) {
		wpa_printf(MSG_ERROR, "%d No hostapd data", vif_id);
		return -1;
	}

	/* Add STA */
	sta = ap_sta_add(hapd, config->addr);
	if (sta == NULL)
		return -1;

	/* Add authenticated STA in driver */
	if (ap_sta_re_add(hapd, sta) < 0) {
		ap_free_sta(hapd, sta);
		return -1;
	}

	/* Set associated STA in driver */
	sta->flags |= WLAN_STA_AUTH;
	sta->aid = config->aid;
	if (sta->flags & WLAN_STA_HT)
		hostapd_get_ht_capab(hapd, sta->ht_capabilities, &ht_cap);

	if (hostapd_sta_add(hapd, sta->addr, sta->aid, sta->capability,
			    sta->supported_rates, sta->supported_rates_len,
			    sta->listen_interval,
			    sta->flags & WLAN_STA_HT ? &ht_cap : NULL,
			    NULL, NULL, 0, NULL,
			    sta->flags | WLAN_STA_ASSOC, sta->qosinfo,
			    sta->vht_opmode, sta->p2p_ie ? 1 : 0,
			    1)) {
		goto sta_add_fail;
	}

	sta->added_unassoc = 0;
	sta->flags |= WLAN_STA_ASSOC;
	ap_sta_set_authorized(hapd, sta, 1);

	sta->auth_alg = auth_alg;
	if (hapd->wpa_auth) {
		/* Initialize WPA state machine */
		if (!sta->wpa_sm) {
			sta->wpa_sm = wpa_auth_sta_init(hapd->wpa_auth, sta->addr, NULL);
			if (!sta->wpa_sm) {
				sta->added_unassoc = 1;
				goto sta_add_fail;
			}
		}

		/* Set pairwise key */
		sm = sta->wpa_sm;
		wpa_auth_set_auth_alg(sm, sta->auth_alg);
		os_memcpy(sm->PTK.kck, config->kck, sizeof(config->kck));
		os_memcpy(sm->PTK.kek, config->kek, sizeof(config->kek));
		os_memcpy(sm->PTK.tk, config->tk, sizeof(config->tk));
		sm->PTK.kck_len = sizeof(config->kck);
		sm->PTK.kek_len = sizeof(config->kek);
		sm->PTK.tk_len = sizeof(config->tk);
		sm->pmk_len = 32;
		sm->wpa_key_mgmt = hapd->wpa_auth->conf.wpa_key_mgmt;
		if (hapd->wpa_auth->conf.ieee80211w != NO_MGMT_FRAME_PROTECTION) {
			sm->mgmt_frame_prot = 1;
		}
		sm->wpa = WPA_VERSION_WPA2;
		sm->pairwise = WPA_CIPHER_CCMP;
		sm->wpa_ptk_state = WPA_PTK_PTKINITNEGOTIATING;
		sm->AuthenticationRequest = false;
		sm->ReAuthenticationRequest = false;
		sm->EAPOLKeyReceived = true;
		sm->EAPOLKeyRequest = false;
		sm->EAPOLKeyPairwise = true;
		sm->MICVerified = true;
		sm->Pair = true;
		sm->PTK_valid = true;
		wpa_auth_sm_notify(sm);

#if defined(PMKSA_CACHE_RECOVERY)
		/* Add PMKSA cache entry */
		uint32_t *pmkid_word = (uint32_t *) config->pmkid;
		if (*pmkid_word != 0) {
			os_memcpy(sm->PMK, config->pmk, sizeof(config->pmk));
			if (wpa_auth_pmksa_add2(hapd->wpa_auth, sta->addr,
				config->pmk, sizeof(config->pmk), config->pmkid,
				0, hapd->wpa_auth->conf.wpa_key_mgmt) < 0) {
				wpa_printf(MSG_INFO, "%d Fail to recover PMKSA cache ["MACSTR"]",
					vif_id, MAC2STR(sta->addr));
			}
		}
#endif /* PMKSA_CACHE_RECOVERY */

#if defined(GTK_REKEY_RECOVERY)
		/* Recover replay counter */
		os_memcpy(sm->key_replay[0].counter, config->replay_counter,
			sizeof(config->replay_counter));
		wpa_hexdump(MSG_DEBUG, "Replay Counter recovered",
			sm->key_replay[0].counter, WPA_REPLAY_COUNTER_LEN);
#endif /* GTK_REKEY_RECOVERY */
	}

	/* Set AID bitmap */
	int bitmap_index = (config->aid - 1) / 32;
	int bit_index = (config->aid - 1) % 32;
	hapd->sta_aid[bitmap_index] |= BIT(bit_index);

	STAINFO *sta_info = get_stainfo_by_aid(vif_id, sta->aid);
	if (sta_info) {
		memcpy(&sta_info->m_s1g, &config->s1g_capability, sizeof(S1G_CAPA));
	}

	extern bool nrc_route_set_use_4addr_by_aid(int vif_id, uint16_t aid, bool use_4addr);
	nrc_route_set_use_4addr_by_aid(vif_id, sta->aid, config->use_4addr);

	wpa_printf(MSG_INFO, "%d WPA STA["MACSTR"] recovered",
		vif_id, MAC2STR(sta->addr));
	ret = 0;

sta_add_fail:
	if (sta->added_unassoc) {
		wpa_printf(MSG_ERROR, "%d Failed to add recovered STA["MACSTR"]",
			vif_id, MAC2STR(config->addr));
		hostapd_drv_sta_remove(hapd, sta->addr);
		sta->added_unassoc = 0;
		ap_free_sta(hapd, sta);
	}

	return ret;
}

int wpas_ap_retent(int vif_id)
{
	struct wpa_supplicant *wpa_s = wpas_iface_init(vif_id);
	struct hostapd_data *hapd = NULL;
	struct wpa_group *group = NULL;
	struct wpa_ssid *ssid = NULL;
	recovery_wpa_config_t *config = system_recovery_wifi_ap_get_wpa();
	int config_size = sizeof(recovery_wpa_config_t);

#if defined(INCLUDE_FAST_CONNECT)
	if (!system_modem_api_get_fc()) {
		return -1;
	}
#endif /* INCLUDE_FAST_CONNECT */

	if (system_recovery_wifi_ap_get_in_recovery()) {
		return -1;
	}

	if (!config) {
		return -1;
	}

	if (!wpa_s || !wpa_s->conf || !wpa_s->ap_iface) {
		wpa_printf(MSG_ERROR, "%d No AP interface", vif_id);
		return -1;
	}

	hapd = wpa_s->ap_iface->bss[0];
	if (!hapd) {
		wpa_printf(MSG_ERROR, "%d No hostapd data", vif_id);
		return -1;
	}

	ssid = wpa_config_get_network(wpa_s->conf, vif_id);
	if (!ssid || ssid->mode != WPAS_MODE_AP) {
		wpa_printf(MSG_ERROR, "%d No AP network", vif_id);
		return -1;
	}

	/* Fill AP info */
	os_memset(config, 0, config_size);
	os_memcpy(config->bssid, hapd->own_addr, ETH_ALEN);
	config->key_mgmt = ssid->key_mgmt;
	config->sae_pwe = wpa_s->conf->sae_pwe;
	config->max_num_sta = wpa_s->conf->max_num_sta;
	config->ignore_broadcast_ssid = ssid->ignore_broadcast_ssid;
	config->nons1g_freq = ssid->frequency;

	if (ssid->dtim_period) {
		config->dtim_period = ssid->dtim_period;
	} else {
		config->dtim_period = wpa_s->conf->dtim_period;
	}

	if (ssid->beacon_int) {
		config->beacon_int = ssid->beacon_int;
	} else {
		config->beacon_int = wpa_s->conf->beacon_int;
	}

	if (wpa_s->conf->country[0] && wpa_s->conf->country[1]) {
		os_strlcpy(config->country, wpa_s->conf->country, sizeof(config->country));
	} else {
		os_strlcpy(config->country, (char *) lmac_get_country(vif_id), sizeof(config->country));
	}

	os_strlcpy((char *) config->ssid, (char *) ssid->ssid, sizeof(config->ssid));

	if (config->key_mgmt != WPA_KEY_MGMT_NONE) {
		if (config->key_mgmt == WPA_KEY_MGMT_SAE) {
			os_strlcpy(config->password, ssid->sae_password, sizeof(config->password));
		} else {
			os_strlcpy(config->password, ssid->passphrase, sizeof(config->password));
		}

		if (hapd->wpa_auth) {
			group = hapd->wpa_auth->group;
			if (!group) {
				wpa_printf(MSG_ERROR, "%d No wpa group", vif_id);
				return -1;
			}
			os_memcpy(config->group_counter, group->Counter, sizeof(config->group_counter));
			os_memcpy(config->gtk, group->GTK, sizeof(config->gtk));
			os_memcpy(config->gmk, group->GMK, sizeof(config->gmk));
		}
	}

#if defined(INCLUDE_FAST_CONNECT)
	if (!system_modem_api_write_fc_ap(false)) {
		wpa_printf(MSG_ERROR, "%d Failed to flash AP", vif_id);
		return -1;
	}
#endif

	wpa_printf(MSG_INFO, "%d WPA AP retented(%dB)", vif_id, config_size);
	return config_size;
}

bool wpas_ap_recovery(int vif_id, void (*set_network_id)(int vif_id, int net_id))
{
	struct wpa_supplicant *wpa_s = NULL;
	struct hostapd_data *hapd = NULL;
	struct wpa_group *group = NULL;
	struct wpa_ssid *ssid = NULL;
	uint16_t auth_alg = WLAN_AUTH_OPEN;
	recovery_wpa_config_t *config = system_recovery_wifi_ap_get_wpa();

#if defined(INCLUDE_FAST_CONNECT)
	if (!system_modem_api_get_recovered_by_fc(vif_id)) {
		return -1;
	}
#endif /* INCLUDE_FAST_CONNECT */

	if (!system_recovery_wifi_ap_is_valid()) {
		return -1;
	}

	if (!config) {
		wpa_printf(MSG_ERROR, "%d No AP config", vif_id);
		return false;
	}

	/* Get interface */
	wpa_s = wpas_iface_init(vif_id);
	if (!wpa_s || !wpa_s->conf) {
		wpa_printf(MSG_ERROR, "%d No wpa config", vif_id);
		return false;
	}

	/* Add network */
	ssid = wpa_supplicant_add_network(wpa_s);
	if (!ssid) {
		wpa_printf(MSG_ERROR, "%d Failed to add network", vif_id);
		return false;
	}

	/* Set network id */
	if (set_network_id) {
		set_network_id(vif_id, ssid->id);
	}

	/* Set country */
	wpa_s->conf->country[0] = config->country[0];
	wpa_s->conf->country[1] = config->country[1];
	wpa_s->conf->changed_parameters |= CFG_CHANGED_COUNTRY;
	wpa_supplicant_update_config(wpa_s);

	/* Set mode */
	ssid->mode = WPAS_MODE_AP;

	/* Set ssid */
	ssid->ssid_len = os_strlen((const char *)config->ssid);
	ssid->ssid = (u8 *) os_zalloc(ssid->ssid_len + 1);
	os_strlcpy((char *)ssid->ssid, (const char *)config->ssid, ssid->ssid_len + 1);
	ssid->scan_ssid = 1;

	/* Set frequency */
	ssid->frequency = config->nons1g_freq;

	/* Set security */
	ssid->key_mgmt = config->key_mgmt;
	if (config->key_mgmt == WPA_KEY_MGMT_NONE) {
		ssid->ieee80211w = NO_MGMT_FRAME_PROTECTION;
	} else {
		ssid->pairwise_cipher = WPA_CIPHER_CCMP;
		ssid->group_cipher = WPA_CIPHER_CCMP;
		ssid->proto = WPA_PROTO_RSN;
		if (config->key_mgmt == WPA_KEY_MGMT_PSK) {
			ssid->ieee80211w = NO_MGMT_FRAME_PROTECTION;
			ssid->passphrase = os_strdup((const char *)config->password);
			wpa_config_update_psk(ssid);
		} else if (config->key_mgmt == WPA_KEY_MGMT_SAE) {
			ssid->ieee80211w = MGMT_FRAME_PROTECTION_REQUIRED;
			ssid->sae_password = os_strdup((const char *)config->password);
			wpa_s->conf->sae_pwe = config->sae_pwe;
			auth_alg = WLAN_AUTH_SAE;
		} else if (config->key_mgmt == WPA_KEY_MGMT_OWE) {
			ssid->ieee80211w = MGMT_FRAME_PROTECTION_REQUIRED;
		} else if (config->key_mgmt == WPA_KEY_MGMT_DPP) {
			ssid->ieee80211w = MGMT_FRAME_PROTECTION_REQUIRED;
		} else {
			wpa_printf(MSG_ERROR, "%d key_mgmt(%d) not supported",
				vif_id, config->key_mgmt);
			wpa_supplicant_remove_network(wpa_s, ssid->id);
			return -1;
		}
	}

	/* Set ignore_broadcast_ssid */
	ssid->ignore_broadcast_ssid = config->ignore_broadcast_ssid;

	/* Set DTIM period */
	ssid->dtim_period = config->dtim_period;

	/* Set MAX STA */
	wpa_s->conf->max_num_sta = config->max_num_sta;

	/* Set Beacon Interval */
	wpa_s->conf->beacon_int = config->beacon_int;

	/* Enable network */
	wpa_supplicant_enable_network(wpa_s, ssid);

	if (!wpa_s->ap_iface) {
		wpa_printf(MSG_ERROR, "%d No AP interface", vif_id);
		wpa_supplicant_remove_network(wpa_s, ssid->id);
		return false;
	}

	hapd = wpa_s->ap_iface->bss[0];
	if (!hapd) {
		wpa_printf(MSG_ERROR, "%d No hostapd data", vif_id);
		wpa_supplicant_remove_network(wpa_s, ssid->id);
		return false;
	}

	/* Set Group Key */
	if (hapd->wpa_auth) {
		group = hapd->wpa_auth->group;
		if (!group) {
			wpa_printf(MSG_ERROR, "%d No wpa group", vif_id);
			wpa_supplicant_remove_network(wpa_s, ssid->id);
			return false;
		}

		group->GTK_len = wpa_cipher_key_len(WPA_CIPHER_CCMP);
		os_memcpy(group->Counter, config->group_counter, sizeof(config->group_counter));
		os_memcpy(group->GTK, config->gtk, sizeof(config->gtk));
		os_memcpy(group->GMK, config->gmk, sizeof(config->gmk));
		wpa_auth_reconfig_group_keys(hapd->wpa_auth);
		group->first_sta_seen = true;

#if !defined(GTK_REKEY_RECOVERY)
		/* Disable GTK rekey
		 * Replay Counter is 8 Bytes per STA. */
		hapd->wpa_auth->conf.wpa_group_rekey = 0;
		hapd->wpa_auth->group = NULL;
		wpa_auth_rekey_gtk(hapd->wpa_auth);
		hapd->wpa_auth->group = group;
#endif /* GTK_REKEY_RECOVERY */

		APINFO *ap_info = get_apinfo_by_vifid(vif_id);
		if (ap_info) {
			ap_info->m_security.security = (config->key_mgmt != WPA_KEY_MGMT_NONE);
		}
	}
	wpa_printf(MSG_INFO, "%d WPA AP recovered", vif_id);

	/* Add STAs */
	for (int i = 0; i < MAX_RECOVERY_STA; i++) {
		wpas_ap_sta_recovery(vif_id, hapd,
			system_recovery_wifi_ap_get_sta(i), auth_alg);
	}

	return true;
}
#endif

int wpas_get_scan_selected_result(int vif_id, struct wpa_scan_res **scan_res,
											void **selected_ssid)
{
	struct wpa_supplicant *wpa_s = wpas_iface_init(vif_id);
	if (!wpa_s) {
		return -1;
	}

	struct nrc_wpa_if *intf = wpa_driver_get_interface(vif_id);
	if (!intf || !intf->scan) {
		return -1;
	}
	intf->scan->keep_scan_results = true;
	if (wpa_supplicant_update_scan_results(wpa_s) < 0) {
		intf->scan->keep_scan_results = false;
		return -1;
	}
	intf->scan->keep_scan_results = false;

	struct wpa_ssid *ssid = NULL;
	struct wpa_bss *bss = wpa_supplicant_pick_network(wpa_s, &ssid);
	if (!bss || !ssid) {
		wpa_bss_flush(wpa_s);
		return -1;
	}
	struct wpa_scan_res *res = os_zalloc(sizeof(**scan_res) + bss->ie_len + bss->beacon_ie_len);
	res->flags = bss->flags;
	os_memcpy(res->bssid, bss->bssid, ETH_ALEN);
	res->freq = bss->freq;
	res->beacon_int = bss->beacon_int;
	res->caps = bss->caps;
	res->qual = bss->qual;
	res->noise = bss->noise;
	res->level = bss->level;
	res->tsf = bss->tsf;
	res->est_throughput = bss->est_throughput;
	res->snr = bss->snr;
	res->ie_len = bss->ie_len;
	res->beacon_ie_len = bss->beacon_ie_len;
	os_memcpy( res + 1, bss->ies, res->ie_len + res->beacon_ie_len);
	wpa_bss_flush(wpa_s);
	*scan_res = res;
	*selected_ssid = ssid;
	return 0;
}

int wpas_get_current_network(int vif_id)
{
	struct wpa_supplicant *wpa_s = wpas_iface_init(vif_id);
	if (!wpa_s) {
		return -1;
	}

	if (wpa_s->current_ssid)
		return wpa_s->current_ssid->id;
	else
		return -1;
}

#if defined(CONFIG_DPP)
struct supp_rsn_pmksa_cache_entry {
	struct rsn_pmksa_cache_entry *next;
	u8 pmkid[PMKID_LEN];
	u8 pmk[PMK_LEN_MAX];
	size_t pmk_len;
	os_time_t expiration;
	int akmp;
	u8 aa[ETH_ALEN];

	u8 fils_cache_id[2];
	unsigned int fils_cache_id_set:1;
	unsigned int dpp_pfs:1;

	os_time_t reauth_time;

	void *network_ctx;
	int opportunistic;
	bool external;
};

int wpas_dpp_backup_connector(int vif_id)
{
	struct wpa_supplicant *wpa_s = wpas_iface_init(vif_id);
	struct wpa_ssid *ssid = NULL;
	struct dpp_configurator *conf = NULL;
	struct ret_dppinfo *dpp_retention = &nrc_ps_get_retention_info()->dpp_info;
	uint32_t len = 0;
	uint32_t hex_len = 0;
	char hex[512];

	if (!wpa_s || !wpa_s->dpp) {
		return -1;
	}

	ssid = wpa_s->current_ssid;
	if (!ssid) {
		return -1;
	}

	/* Backup NetAccessKey */
	len = ssid->dpp_netaccesskey_len;
	if (ssid->dpp_netaccesskey && len <= sizeof(dpp_retention->net_access_key)) {
		os_memcpy(dpp_retention->net_access_key, ssid->dpp_netaccesskey, len);
		dpp_retention->net_access_key_len = len;
		dpp_retention->net_access_key_expiry = ssid->dpp_netaccesskey_expiry;
		if (len > 0) {
			hex_len = 2 * len + 1;
			os_memset(hex, 0, sizeof(hex));
			wpa_snprintf_hex(hex, hex_len, dpp_retention->net_access_key, len);
			wpa_msg(wpa_s, MSG_DEBUG, DPP_EVENT_NET_ACCESS_KEY "%s %lu",
				hex, dpp_retention->net_access_key_expiry);
		}
	} else {
		return -1;
	}

	/* Backup Connector */
	len = os_strlen(ssid->dpp_connector) + 1;
	if (ssid->dpp_connector && len <= sizeof(dpp_retention->connector)) {
		os_strlcpy((char *)dpp_retention->connector, ssid->dpp_connector, len);
		wpa_msg(wpa_s, MSG_DEBUG, DPP_EVENT_CONNECTOR "%s", dpp_retention->connector);
	}

	/* Backup CSign Public Key */
	len = ssid->dpp_csign_len;
	if (ssid->dpp_csign && len <= sizeof(dpp_retention->csign)) {
		os_memcpy(dpp_retention->csign, ssid->dpp_csign, len);
		dpp_retention->csign_len = len;
		if (len > 0) {
			hex_len = 2 * len + 1;
			os_memset(hex, 0, sizeof(hex));
			wpa_snprintf_hex(hex, hex_len, dpp_retention->csign, len);
			wpa_msg(wpa_s, MSG_DEBUG, DPP_EVENT_C_SIGN_KEY "(PUB) %s", hex);
		}
	}

	/* Backup PPKey Public Key */
	len = ssid->dpp_pp_key_len;
	if (ssid->dpp_pp_key && len <= sizeof(dpp_retention->ppkey)) {
		os_memcpy(dpp_retention->ppkey, ssid->dpp_pp_key, len);
		dpp_retention->ppkey_len = len;
		if (len > 0) {
			hex_len = 2 * len + 1;
			os_memset(hex, 0, sizeof(hex));
			wpa_snprintf_hex(hex, hex_len, dpp_retention->ppkey, len);
			wpa_msg(wpa_s, MSG_DEBUG, DPP_EVENT_PP_KEY "(PUB) %s", hex);
		}
	}

	/* Backup AKM */
	if (ssid->key_mgmt & WPA_KEY_MGMT_DPP) {
		if (ssid->key_mgmt & WPA_KEY_MGMT_SAE) {
			if (ssid->key_mgmt & WPA_KEY_MGMT_PSK) {
				dpp_retention->akm = DPP_AKM_PSK_SAE_DPP;
			} else {
				dpp_retention->akm = DPP_AKM_SAE_DPP;
			}
		} else {
			dpp_retention->akm = DPP_AKM_DPP;
		}
	} else if (ssid->key_mgmt & WPA_KEY_MGMT_SAE) {
		if (ssid->key_mgmt & WPA_KEY_MGMT_PSK) {
			dpp_retention->akm = DPP_AKM_PSK_SAE;
		} else {
			dpp_retention->akm = DPP_AKM_SAE;
		}
	} else if (ssid->key_mgmt & WPA_KEY_MGMT_PSK) {
		dpp_retention->akm = DPP_AKM_PSK;
	}

	/* Backup PFS */
	if (wpa_s->wpa && wpa_s->wpa->cur_pmksa) {
		struct supp_rsn_pmksa_cache_entry *pmksa =
			(struct supp_rsn_pmksa_cache_entry *) wpa_s->wpa->cur_pmksa;
		dpp_retention->pfs = pmksa->dpp_pfs;
	}

	/* Backup Configurator */
	dl_list_for_each(conf, &wpa_s->dpp->configurator,
					struct dpp_configurator, list) {
		struct wpabuf *buf = NULL;
		if (conf->id == 0) {
			continue;
		}

		/* Find matching CSign key */
		buf = crypto_ec_key_get_subject_public_key(conf->csign);
		if (buf) {
			if (os_memcmp(ssid->dpp_csign, wpabuf_head(buf), wpabuf_len(buf)) != 0) {
				wpabuf_free(buf);
				continue;
			}
			wpabuf_free(buf);
			/* Backup CSign Keypair */
			buf = crypto_ec_key_get_ecprivate_key(conf->csign, true);
			if (buf) {
				os_memcpy(dpp_retention->csign, wpabuf_head(buf), wpabuf_len(buf));
				dpp_retention->csign_len = wpabuf_len(buf);
				if (dpp_retention->csign_len > 0) {
					hex_len = 2 * wpabuf_len(buf) + 1;
					os_memset(hex, 0, sizeof(hex));
					wpa_snprintf_hex(hex, hex_len, wpabuf_head(buf), wpabuf_len(buf));
					wpa_msg(wpa_s, MSG_DEBUG, DPP_EVENT_C_SIGN_KEY "%s", hex);
				}
				wpabuf_free(buf);
			}
		} else {
			continue;
		}

		/* Backup PPKey Keypair */
		buf = crypto_ec_key_get_ecprivate_key(conf->pp_key, true);
		if (buf) {
			os_memcpy(dpp_retention->ppkey, wpabuf_head(buf), wpabuf_len(buf));
			dpp_retention->ppkey_len = wpabuf_len(buf);
			dpp_retention->configurator_id = conf->id;
			if (dpp_retention->ppkey_len > 0) {
				hex_len = 2 * wpabuf_len(buf) + 1;
				os_memset(hex, 0, sizeof(hex));
				wpa_snprintf_hex(hex, hex_len, wpabuf_head(buf), wpabuf_len(buf));
				wpa_msg(wpa_s, MSG_DEBUG, DPP_EVENT_PP_KEY "%s", hex);
			}
			wpabuf_free(buf);
			break;
		} else {
			continue;
		}
	}

	wpa_printf(MSG_DEBUG, "%s: DPP Connector backup done", __func__);
	return 0;
}

struct wpa_ssid * wpas_dpp_restore_connector(struct wpa_supplicant *wpa_s, struct wpa_ssid *ssid, ctrl_iface_recovery_t *config)
{
	char *csign = NULL, *ppkey = NULL;
	char cmd[MAX_CONFIG_LINE_SIZE];
	uint32_t csign_len, ppkey_len;

	if (!wpa_s->dpp) {
		wpa_printf(MSG_DEBUG, "%s: DPP not initialized", __func__);
		goto fail;
	}

	if (config->dpp_net_access_key_len == 0 ||
	    config->dpp_ppkey_len == 0 ||
	    config->dpp_csign_len == 0) {
		wpa_printf(MSG_DEBUG, "%s: DPP Connector retention is empty", __func__);
		goto fail;
	}

	/* Restore Connector */
	ssid->dpp_connector = os_strdup((const char *)config->dpp_connector);
	if (!ssid->dpp_connector) {
		wpa_printf(MSG_ERROR, "%s: Failed to allocate DPP Connector", __func__);
		goto fail;
	}

	/* Restore NetAccessKey */
	ssid->dpp_netaccesskey = os_malloc(config->dpp_net_access_key_len);
	if (!ssid->dpp_netaccesskey) {
		wpa_printf(MSG_ERROR, "%s: Failed to allocate DPP Net Access Key", __func__);
		goto fail;
	}
	os_memcpy(ssid->dpp_netaccesskey, config->dpp_net_access_key,
		  config->dpp_net_access_key_len);
	ssid->dpp_netaccesskey_len = config->dpp_net_access_key_len;
	ssid->dpp_netaccesskey_expiry = config->dpp_net_access_key_expiry;

	/* Restore AKM */
	ssid->key_mgmt = 0;
	ssid->proto = WPA_PROTO_RSN;
	switch (config->dpp_akm) {
	case DPP_AKM_PSK_SAE_DPP:
		ssid->key_mgmt |= WPA_KEY_MGMT_PSK;
		wpa_config_update_psk(ssid);
	case DPP_AKM_SAE_DPP:
		ssid->key_mgmt |= WPA_KEY_MGMT_SAE;
		ssid->sae_password = os_strdup((const char *)config->password);
		if (config->sae_pwe > 0) {
			wpa_s->conf->sae_pwe = 3;
		}
	case DPP_AKM_DPP:
		ssid->key_mgmt |= WPA_KEY_MGMT_DPP;
		ssid->ieee80211w = MGMT_FRAME_PROTECTION_REQUIRED;
		break;
	case DPP_AKM_PSK_SAE:
		ssid->key_mgmt |= WPA_KEY_MGMT_PSK;
		wpa_config_update_psk(ssid);
	case DPP_AKM_SAE:
		ssid->key_mgmt |= WPA_KEY_MGMT_SAE;
		ssid->ieee80211w = MGMT_FRAME_PROTECTION_REQUIRED;
		ssid->sae_password = os_strdup((const char *)config->password);
		if (config->sae_pwe > 0) {
			wpa_s->conf->sae_pwe = 3;
		}
		break;
	case DPP_AKM_PSK:
		ssid->key_mgmt |= WPA_KEY_MGMT_PSK;
		ssid->ieee80211w = NO_MGMT_FRAME_PROTECTION;
		wpa_config_update_psk(ssid);
		break;
	default:
		wpa_printf(MSG_ERROR, "%s: Unsupported DPP AKM %d", __func__, config->akm);
		goto fail;
	}

	/* Restore CSign/PPKey */
	if (config->dpp_configurator_id > 0) {
		/* Add Configurator */
		csign_len = 2 * config->dpp_csign_len + 1;
		csign = os_malloc(csign_len);
		if (!csign) {
			wpa_printf(MSG_ERROR, "%s: Failed to allocate DPP C-sign", __func__);
			goto fail;
		}
		wpa_snprintf_hex(csign, csign_len,
				config->dpp_csign, config->dpp_csign_len);
		ppkey_len = 2 * config->dpp_ppkey_len + 1;
		ppkey = os_malloc(ppkey_len);
		if (!ppkey) {
			wpa_printf(MSG_ERROR, "%s: Failed to allocate DPP PPKey", __func__);
			goto fail;
		}
		wpa_snprintf_hex(ppkey, ppkey_len,
				config->dpp_ppkey, config->dpp_ppkey_len);

		os_snprintf(cmd, MAX_CONFIG_LINE_SIZE, " key=%s ppkey=%s",
				csign, ppkey);

		int id = dpp_configurator_add(wpa_s->dpp, cmd);
		if (id < 0) {
			wpa_printf(MSG_ERROR, "%s: Failed to add DPP Configurator", __func__);
			goto fail;
		}
		os_free(csign); csign = NULL;
		os_free(ppkey); ppkey = NULL;

		/* Get Configurator */
		struct dpp_configurator *conf = NULL;
		dl_list_for_each(conf, &wpa_s->dpp->configurator, struct dpp_configurator, list) {
			if (conf->id == id)
				break;
		}
		if (!conf) {
			wpa_printf(MSG_ERROR, "%s: Failed to get DPP Configurator", __func__);
			goto fail;
		}

		/* Restore CSign Public Key */
		struct wpabuf *buf = NULL;
		buf = crypto_ec_key_get_subject_public_key(conf->csign);
		if (!buf) {
			wpa_printf(MSG_ERROR, "%s: Failed to get DPP C-sign", __func__);
			goto fail;
		}
		ssid->dpp_csign = os_malloc(wpabuf_len(buf));
		if (!ssid->dpp_csign) {
			wpa_printf(MSG_ERROR, "%s: Failed to allocate DPP C-sign", __func__);
			goto fail;
		}
		os_memcpy(ssid->dpp_csign, wpabuf_head(buf), wpabuf_len(buf));
		ssid->dpp_csign_len = wpabuf_len(buf);
		wpabuf_free(buf);

		/* Restore PPKey Public Key */
		buf = crypto_ec_key_get_subject_public_key(conf->pp_key);
		if (!buf) {
			wpa_printf(MSG_ERROR, "%s: Failed to get DPP PPKey", __func__);
			goto fail;
		}
		ssid->dpp_pp_key = os_malloc(wpabuf_len(buf));
		if (!ssid->dpp_pp_key) {
			wpa_printf(MSG_ERROR, "%s: Failed to allocate DPP PPKey", __func__);
			goto fail;
		}
		os_memcpy(ssid->dpp_pp_key, wpabuf_head(buf), wpabuf_len(buf));
		ssid->dpp_pp_key_len = wpabuf_len(buf);
		wpabuf_free(buf);
	} else {
		/* Restore CSign Public Key */
		ssid->dpp_csign = os_malloc(config->dpp_csign_len);
		if (!ssid->dpp_csign) {
			wpa_printf(MSG_ERROR, "%s: Failed to allocate DPP C-sign", __func__);
			goto fail;
		}
		os_memcpy(ssid->dpp_csign, config->dpp_csign, config->dpp_csign_len);
		ssid->dpp_csign_len = config->dpp_csign_len;

		/* Restore PPKey Public Key */
		ssid->dpp_pp_key = os_malloc(config->dpp_ppkey_len);
		if (!ssid->dpp_pp_key) {
			wpa_printf(MSG_ERROR, "%s: Failed to allocate DPP PPKey", __func__);
			goto fail;
		}
		os_memcpy(ssid->dpp_pp_key, config->dpp_ppkey, config->dpp_ppkey_len);
		ssid->dpp_pp_key_len = config->dpp_ppkey_len;
	}

	return ssid;

fail:
	if (csign) {
		os_free(csign);
	}
	if (ppkey) {
		os_free(ppkey);
	}

	return NULL;
}
#endif

bool wpas_recovery(int vif_id, ctrl_iface_recovery_t *config, void (*set_network_id)(int vif_id, int net_id))
{
	struct wpa_supplicant *wpa_s = NULL;
	struct wpa_ssid *ssid = NULL;

	if (!config) {
		return false;
	}

	/* Get interface */
	wpa_s = wpas_iface_init(vif_id);
	if (!wpa_s) {
		return false;
	}

	/* Add network */
	ssid = wpa_supplicant_add_network(wpa_s);
	if (!ssid) {
		wpa_printf(MSG_ERROR, "Failed to add network(%d)", vif_id);
		return false;
	}

	/* Set network id */
	if (set_network_id) {
		set_network_id(vif_id, ssid->id);
	}

	/* Set country */
	wpa_s->conf->country[0] = config->country[0];
	wpa_s->conf->country[1] = config->country[1];
	wpa_s->conf->changed_parameters |= CFG_CHANGED_COUNTRY;
	wpa_supplicant_update_config(wpa_s);

	/* Set passive scan */
	if (config->scan_mode == 1) {
		wpa_s->conf->passive_scan = 1;
	}

	/* Set mode */
	ssid->mode = WPAS_MODE_INFRA;
	wpa_s->driver->set_device_mode(wpa_s->drv_priv, ssid->mode);

	/* Set ssid */
	if (ssid->ssid) {
		os_free(ssid->ssid);
	}
	ssid->ssid_len = os_strlen((const char *)config->ssid);
	ssid->ssid = (u8 *) os_zalloc(ssid->ssid_len + 1);
	os_strlcpy((char *)ssid->ssid, (const char *)config->ssid, ssid->ssid_len + 1);
	ssid->scan_ssid = 1;

	/* Set bssid */
	memcpy(ssid->bssid, config->bssid, sizeof(ssid->bssid));

	/* Set frequency */
	ssid->frequency = config->nons1g_freq;

	/* Set security */
	if (config->security == WPA_KEY_MGMT_NONE) {
		ssid->key_mgmt = WPA_KEY_MGMT_NONE;
		ssid->ieee80211w = NO_MGMT_FRAME_PROTECTION;
	} else {
		switch(config->akm) {
		case 2:  // RSN_AUTH_KEY_MGMT_PSK_OVER_802_1X
			if (config->eap_type == 0) {
				ssid->key_mgmt = WPA_KEY_MGMT_PSK;
				ssid->ieee80211w = NO_MGMT_FRAME_PROTECTION;
				ssid->proto = WPA_PROTO_RSN;
				wpa_config_update_psk(ssid);
				/* WPA2-PSK passphrase can't be recovered due to lack of retention.
				 * ssid->passphrase = os_strdup((const char *)config->passphrase) */
			}
#if defined(IEEE8021X_EAPOL) && defined(EAPOL_8021X_RETENTION) // for future use
			else {
				ssid->key_mgmt = WPA_KEY_MGMT_IEEE8021X;
				ssid->eap.identity = (u8 *)os_strdup((const char *)config->identity);
				ssid->eap.password = (u8 *)os_strdup((const char *)config->password);
				ssid->eap.password_len = os_strlen((const char *)config->password);
				ssid->eap.flags &= ~EAP_CONFIG_FLAGS_PASSWORD_NTHASH;
				ssid->eap.flags &= ~EAP_CONFIG_FLAGS_EXT_PASSWORD;
			}
			switch (config->eap_type) {
				case 1: // WIFI_EAP_TLS
					ssid->eap.eap_methods = os_zalloc(sizeof(struct eap_method_type));
					ssid->eap.eap_methods->method = EAP_TYPE_TLS;
					ssid->eap.eap_methods->vendor = EAP_VENDOR_IETF;
					ssid->eap.cert.ca_cert = os_strdup("\"blob://ca_cert\"");
					ssid->eap.cert.client_cert = os_strdup("\"blob://client_cert\"");
					ssid->eap.cert.private_key = os_strdup("\"blob://private_key\"");
					ssid->eap.cert.private_key_passwd = os_strdup((const char *)config->private_key_password);
					wpas_set_blob(wpa_s, "ca_cert", config->eap_ca_cert);
					wpas_set_blob(wpa_s, "client_cert", config->eap_client_cert);
					wpas_set_blob(wpa_s, "private_key", config->eap_private_key);
					break;
				case 3: //WIFI_EAP_PEAP
					ssid->eap.eap_methods = os_zalloc(sizeof(struct eap_method_type));
					ssid->eap.eap_methods->method = EAP_TYPE_PEAP;
					ssid->eap.eap_methods->vendor = EAP_VENDOR_IETF;
					ssid->eap.phase1 = os_strdup("\"peapver=0\"");
					ssid->eap.phase2 = os_strdup("\"MSCHAPV2\"");
					break;
				case 2: // WIFI_EAP_TTLS
					ssid->eap.eap_methods = os_zalloc(sizeof(struct eap_method_type));
					ssid->eap.eap_methods->method = EAP_TYPE_TTLS;
					ssid->eap.eap_methods->vendor = EAP_VENDOR_IETF;
					ssid->eap.phase2 = os_strdup("\"MSCHAPV2\"");
					break;
				default:
					goto recovery_fail;
			}
#else
			else {
				goto recovery_fail;
			}
#endif /* IEEE8021X_EAPOL && EAPOL_8021X_RETENTION */
			break;
#if defined(CONFIG_SAE)
		case 8:  // RSN_AUTH_KEY_MGMT_SAE
			ssid->key_mgmt = WPA_KEY_MGMT_SAE;
			ssid->ieee80211w = MGMT_FRAME_PROTECTION_REQUIRED;
			ssid->proto = WPA_PROTO_RSN;
			ssid->sae_password = os_strdup((const char *)config->password);
			if (config->sae_pwe > 0) {
				/* SAE: Special test mode (Use hunting-and-pecking loop)
				 * hash-to-element makes PT in recovery process but takes
				 * long time. Use test mode in recovery process and recover
				 * sae_pwe option in port authorization. (wpa_ps_hook_handle_port)
				 * https://w1.fi/cgit/hostap/commit/?id=641d79f165750f3c6af5f9565ff317f14fffa114
				 */
				wpa_s->conf->sae_pwe = 3;
			}
			break;
#endif
#if defined(CONFIG_OWE)
		case 18: // RSN_AUTH_KEY_MGMT_OWE
			ssid->key_mgmt = WPA_KEY_MGMT_OWE;
			ssid->ieee80211w = MGMT_FRAME_PROTECTION_REQUIRED;
			ssid->proto = WPA_PROTO_RSN;
			break;
#endif
#if defined(CONFIG_DPP)
		case 22: // RSN_AUTH_KEY_MGMT_DPP
			wpa_s->wpa->network_ctx = wpas_dpp_restore_connector(wpa_s, ssid, config);
			wpa_sm_pmksa_cache_add(wpa_s->wpa, config->dpp_pmk,
				config->dpp_pmk_len, config->dpp_pmkid, (const u8 *)config->bssid, NULL);
			struct supp_rsn_pmksa_cache_entry *pmksa =
				(struct supp_rsn_pmksa_cache_entry *) wpa_s->wpa->cur_pmksa;
			pmksa->dpp_pfs = config->dpp_pfs;
			break;
#endif
		default:
			goto recovery_fail;
		}
	}

	/* Enable network */
	wpa_supplicant_enable_network(wpa_s, ssid);

	return true;

recovery_fail:

	/* Remove network */
	wpa_supplicant_remove_network(wpa_s, ssid->id);

	return false;
}

struct wpa_supplicant * wpas_iface_init(int vif_id)
{
	char ifname[6];
	struct wpa_supplicant *wpa_s = NULL;
	struct wpa_interface iface;

	if (!global) {
		global = wpas_global_init();
		if (!global) {
			return NULL;
		}
	}

	snprintf(ifname, sizeof(ifname), IFNAME_PREFIX"%d", vif_id);
	wpa_s = wpa_supplicant_get_iface(global, ifname);
	if (wpa_s) {
		return wpa_s;
	}

	memset(&iface, 0, sizeof(struct wpa_interface));
	iface.confname = iface.ifname = ifname;
	wpa_s = wpa_supplicant_add_iface(global, &iface, NULL);
	if (!wpa_s) {
		wpa_printf(MSG_ERROR, "Failed to add iface(%d)", vif_id);
		return NULL;
	}

	return wpa_s;
}

int wpas_iface_deinit(int vif_id)
{
	char ifname[6];
	struct wpa_supplicant *wpa_s = NULL;

	if (!global) {
		return -1;
	}

	snprintf(ifname, sizeof(ifname), IFNAME_PREFIX"%d", vif_id);
	wpa_s = wpa_supplicant_get_iface(global, ifname);
	if (!wpa_s) {
		return -1;
	}

	return wpa_supplicant_remove_iface(global, wpa_s, 0);
}

struct wpa_global * wpas_global_init(void)
{
	struct wpa_params params;

	if (global) {
		return global;
	}

	memset(&params, 0, sizeof(params));
	params.wpa_debug_level = wpa_debug_level;
	params.wpa_debug_show_keys = wpa_debug_show_keys;
	params.wpa_debug_timestamp = wpa_debug_timestamp;

	global = wpa_supplicant_init(&params);

	if (!global) {
		wpa_printf(MSG_ERROR, "Failed to init wpa_supplicant");
		return NULL;
	}

	return global;
}

void wpas_task_main(void *pvParams)
{
	global = wpas_global_init();
	if (!global) {
		return;
	}

	wpas_iface_init(0);

#if !defined(NRC7291_SDK_DUAL_CM3) && !defined(NRC7292_SDK_DUAL_CM3)
	lmac_start();
#endif

	wpa_supplicant_run(global);
	wpa_supplicant_deinit(global);
}
