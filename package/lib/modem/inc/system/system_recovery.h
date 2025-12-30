#ifndef SYSTEM_RECOVERY_H
#define SYSTEM_RECOVERY_H
#include "umac_info.h"

#define MAX_RECOVERY_STA	MAX_STA
#define PMKSA_CACHE_RECOVERY
#define GTK_REKEY_RECOVERY

typedef struct
{
	char country[3];
	char password[64];
	uint8_t sae_pwe;
	uint8_t max_num_sta;
	uint8_t ignore_broadcast_ssid;
	uint8_t dtim_period;
	uint8_t bssid[6];
	uint8_t ssid[32];
	uint8_t group_counter[32];
	uint8_t gtk[16];
	uint8_t gmk[32];
	uint16_t auth_alg;
	uint16_t nons1g_freq;
	uint16_t beacon_int;
	uint32_t key_mgmt;
} __attribute__((packed)) recovery_wpa_config_t;

typedef struct {
	uint8_t ndp_preq     : 1;
	uint8_t rate_control : 1;
	uint8_t auth_control : 1;
	uint8_t use_4addr    : 1;
	uint8_t short_beacon : 1;
	uint8_t reserved     : 1;
	uint8_t gi           : 2;
	uint8_t txpwr        : 6;
	uint8_t txpwr_type   : 2;
	uint8_t mcs          : 4;
	uint8_t reserved2    : 4;
	int8_t cca_threshold;
	uint8_t auth_ctrl_slot;
	uint8_t auth_ctrl_min;
	uint8_t auth_ctrl_max;
	uint8_t auth_ctrl_scale;
	uint16_t bss_max_idle_period;
	uint16_t bss_max_idle_retry;
	uint16_t lbt_cs_time;
	uint32_t lbt_pause_time;
	uint32_t lbt_resume_time;
	uint16_t duty_margin;
	uint32_t duty_window;
	uint32_t duty_max_token;
} __attribute__((packed)) recovery_mac_config_t;

typedef struct
{
	uint8_t use_4addr    : 1;
	uint8_t reserved     : 7;
	uint8_t addr[6];
	uint8_t kck[16];
	uint8_t kek[16];
	uint8_t tk[16];
#ifdef PMKSA_CACHE_RECOVERY
	uint8_t pmkid[16];
	uint8_t pmk[32];
#endif /* PMKSA_CACHE_RECOVERY */
#ifdef GTK_REKEY_RECOVERY
	uint8_t replay_counter[8];
#endif /* GTK_REKEY_RECOVERY */
	uint16_t aid;
	S1G_CAPA s1g_capability;
} __attribute__((packed)) recovery_sta_config_t;

typedef struct
{
	uint8_t valid        : 1;
	uint8_t fast_connect : 1;
	uint8_t vif_id       : 2;
	uint8_t in_recovery  : 1;
	uint8_t bridge       : 2;
	uint8_t reserved     : 1;
	uint8_t num_sta;
	recovery_wpa_config_t wpa;
	recovery_mac_config_t mac;
	recovery_sta_config_t sta[MAX_RECOVERY_STA];
} __attribute__((packed)) ap_recovery_t;

typedef struct {
	uint8_t net_id       : 2;
	uint8_t reserved     : 6;
	uint16_t aid;
	uint8_t mac[6];
	uint32_t ipaddr;
} __attribute__((packed)) recovery_peer_config_t;

typedef struct {
	uint8_t valid        : 1;
	uint8_t dhcps        : 1;
	uint8_t in_recovery  : 1;
	uint8_t net_id       : 2;
	uint8_t reserved     : 3;
	uint32_t ip_addr;
	uint32_t netmask;
	uint32_t gw;
	uint32_t lease_time;
	recovery_peer_config_t peer[MAX_RECOVERY_STA];
} __attribute__((packed)) ip_recovery_t;


ap_recovery_t *system_recovery_wifi_ap_get(void);
bool system_recovery_wifi_ap_is_valid(void);
void system_recovery_wifi_ap_set_valid(bool valid);
bool system_recovery_wifi_ap_get_in_recovery(void);
void system_recovery_wifi_ap_set_in_recovery(bool in_recovery);
void system_recovery_wifi_ap_init(void);
void system_recovery_wifi_ap_set_vif_id(int vif_id);
recovery_sta_config_t *system_recovery_wifi_ap_get_sta(int i);
recovery_sta_config_t *system_recovery_wifi_ap_set_replay_counter(
	const uint8_t *addr, uint8_t *replay_counter);
int system_recovery_wifi_ap_update_4addr(uint16_t aid, bool use_4addr);
recovery_sta_config_t *system_recovery_wifi_ap_alloc_sta(
	uint16_t aid, const uint8_t *addr);
int system_recovery_wifi_ap_free_sta(uint16_t aid);
int system_recovery_wifi_ap_get_num_sta(void);
recovery_wpa_config_t *system_recovery_wifi_ap_get_wpa(void);
recovery_mac_config_t *system_recovery_wifi_ap_get_mac(void);
void system_recovery_wifi_ap_set_bridge(int vif_id);
bool system_recovery_wifi_ap_get_bridge(int vif_id);
int system_recovery_wifi_ap_get_active_bridgeif(int vif_id);
void system_recovery_wifi_ap_print(ap_recovery_t *ap_recovery);

ip_recovery_t *system_recovery_wifi_ip_get(void);
bool system_recovery_wifi_ip_is_valid(void);
bool system_recovery_wifi_ip_get_in_recovery(void);
void system_recovery_wifi_ip_set_in_recovery(bool in_recovery);
void system_recovery_wifi_ip_init(void);
recovery_peer_config_t *system_recovery_wifi_ip_get_peer(int i);
recovery_peer_config_t *system_recovery_wifi_ip_alloc_peer(
	int net_id, uint8_t *mac, uint32_t ipaddr);
int system_recovery_wifi_ip_free_peer(uint32_t ipaddr);
recovery_peer_config_t *system_recovery_wifi_ip_alloc_route(int net_id, uint8_t *mac);
int system_recovery_wifi_ip_free_route(int net_id, uint8_t *mac, uint16_t aid);
void system_recovery_wifi_ip_print(ip_recovery_t *ip_recovery);

#endif // SYSTEM_RECOVERY_H
