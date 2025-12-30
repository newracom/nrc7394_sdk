#ifndef CTRL_IFACE_FREERTOS_H
#define CTRL_IFACE_FREERTOS_H
#include "driver.h"

typedef struct
{
	int len;
	char *msg;
} ctrl_iface_resp_t;

typedef struct
{
	uint8_t security;
	uint8_t akm;
	uint8_t eap_type;
	uint8_t scan_mode;
	uint8_t sae_pwe;
	uint16_t channel;
	uint16_t nons1g_freq;
	uint32_t ip_addr;
	uint32_t net_mask:31;
	uint32_t ip_mode:1;
	uint32_t gw_addr;
#if !defined(NRC7292)
	uint8_t  dhcp_setting[52 + 4]; /* sizeof(struct dhcp) + sizeof(dhcp_event_handler_t) */
	uint32_t dhcp_renew:1;
	uint32_t reserved0:31;
#endif
#if defined(CONFIG_DPP)
	uint8_t dpp_configurator_id;
	uint8_t dpp_pfs;
	uint8_t dpp_akm;
	uint8_t *dpp_connector;
	uint8_t *dpp_net_access_key;
	uint8_t dpp_net_access_key_len;
	uint32_t dpp_net_access_key_expiry;
	uint8_t *dpp_csign;
	uint8_t dpp_csign_len;
	uint8_t *dpp_ppkey;
	uint8_t dpp_ppkey_len;
	uint8_t *dpp_pmkid;
	uint8_t *dpp_pmk;
	uint8_t dpp_pmk_len;
#endif
	const char *country;
	const char *ssid;
	const char *bssid;
	const char *password;
	const char *pmk;
#if defined(EAPOL_8021X_RETENTION)
	const char *identity;
	const char *private_key_password;
	const char *eap_ca_cert;
	const char *eap_client_cert;
	const char *eap_private_key;
#endif
} ctrl_iface_recovery_t;

int ctrl_iface_receive(int vif_id, char *cmd);
int wpa_cmd_receive(int vif_id, int argc, char *argv[]);
struct wpa_global * wpas_global_init(void);
struct wpa_supplicant * wpas_iface_init(int vif_id);
int wpas_iface_deinit(int vif_id);
bool wpas_recovery(int vif_id, ctrl_iface_recovery_t *config, void (*set_network_id)(int vif_id, int net_id));
char * wpas_config_get(int vif_id, const char *name);
int wpas_config_set(int vif_id, const char *name, char *value);
int wpas_config_global_get(int vif_id, const char *name, char *buf, size_t buflen);
int wpas_config_global_set(int vif_id, const char *name, char *value);
int wpas_get_scan_selected_result(int vif_id, struct wpa_scan_res **scan_res, void **selected_ssid);
void nrc_ps_get_rconf(ctrl_iface_recovery_t *config);
int wpas_nrc_get_sae_state(struct wpa_supplicant *wpa_s);
#if defined(INCLUDE_SOFT_AP)
struct hostapd_iface * wpas_nrc_get_ap_iface(struct wpa_supplicant *wpa_s);
int wpas_ap_remove_sta(int vif_id, uint16_t aid);
int wpas_ap_update_sta(int vif_id, const uint8_t *addr);
int wpas_ap_retent(int vif_id);
bool wpas_ap_recovery(int vif_id, void (*set_network_id)(int vif_id, int net_id));
#else
static inline struct hostapd_iface * wpas_nrc_get_ap_iface(struct wpa_supplicant *wpa_s){return NULL;};
static inline int wpas_ap_remove_sta(int vif_id, uint16_t aid) {return 0;};
static inline int wpas_ap_update_sta(int vif_id, const uint8_t *addr){return 0;};
static inline int wpas_ap_retent(int vif_id) {return 0;};
static inline bool wpas_ap_recovery(int vif_id, void (*set_network_id)(int vif_id, int net_id)) {return false;};
#endif
int wpas_get_current_network(int vif_id);
int wpas_dpp_backup_connector(int vif_id);

ctrl_iface_resp_t *ctrl_iface_receive_response(int vif_id, const char *fmt, ...);
bool CTRL_IFACE_RESP_OK (ctrl_iface_resp_t *resp);
bool CTRL_IFACE_RESP_MSG (ctrl_iface_resp_t *resp);
void CTRL_IFACE_RESP_FREE (ctrl_iface_resp_t *resp);

#endif /* CTRL_IFACE_FREERTOS_H */
