#include "nrc_sdk.h"
#include "nrc_lwip.h"
#include "nvs.h"
#include "nvs_config.h"
#include "wifi_user_config.h"
#include "wifi_config_setup.h"
#include "wifi_connect_common.h"
#include "wifi_relay_service.h"
#include "epd_status_display.h"
#ifdef SMART_CONNECTION_ENABLE
#include "api_smart_conn.h"
#endif /* SMART_CONNECTION_ENABLE */

#include "multi_role_config.h"

#ifdef SUPPORT_TCP_CLI
#include "tcp_cli.h"
#endif /* SUPPORT_TCP_CLI */
#include "app_debug.h"

static system_role_t system_type = ROLE_UNDEFINED;

static WIFI_CONFIG wifi_config;

static uint16_t provisioned = 0;

#ifndef BEACON_LOSS_DETECTION_COUNT
#define BEACON_LOSS_DETECTION_COUNT 15
#endif

#ifndef SC_SCAN_INTERVAL
#define SC_SCAN_INTERVAL 20
#endif

#ifndef SC_SCAN_DURATION
#define SC_SCAN_DURATION (SC_SCAN_INTERVAL /5)
#endif

static nrc_err_t start_softap(nvs_handle_t nvs_handle)
{
	/* start softAP */
	nrc_wifi_set_use_4address(true);

	do {
		if (wifi_init(&wifi_config) == WIFI_SUCCESS) {
			break;
		} else {
			_delay_ms(1000);
		}
	} while (1);

	if (nrc_wifi_get_recovered_by_fast_connect(0)) {
		app_log(DEBUG_LEVEL_ALWAYS, NULL, "SoftAP recovered by fast connect\n");
		return NRC_SUCCESS;
	}

	if (wifi_start_softap(&wifi_config) != WIFI_SUCCESS) {
		return NRC_FAIL;
	}

	if (nrc_wifi_softap_set_short_beacon(0, false) != WIFI_SUCCESS){
		return NRC_FAIL;
	}

	if (nrc_wifi_softap_set_ip(0, wifi_config.static_ip, wifi_config.netmask, wifi_config.gateway) != WIFI_SUCCESS) {
		return NRC_FAIL;
	}

	if (wifi_config.dhcp_server) {
		if (nrc_wifi_softap_start_dhcp_server(0) != WIFI_SUCCESS) {
			return NRC_FAIL;
		}
	}

	return NRC_SUCCESS;
}

static nrc_err_t start_station(nvs_handle_t nvs_handle)
{
	int ip_get_retry_cnt = 0;
	int ap_found = 0;
	uint8_t boot;
	struct netif *interface = nrc_netif_get_by_idx(0);

	/* start station */
	/* set initial wifi configuration */
	if (wifi_init(&wifi_config) != WIFI_SUCCESS) {
		return NRC_FAIL;
	}

	/* 255 : about 25 sec (beacon interval * BEACON_LOSS_DETECTION_COUNT) */
	nrc_wifi_set_beacon_loss_detection(WLAN0_INTERFACE, true, BEACON_LOSS_DETECTION_COUNT);

	do {
		//no need to do scan to find AP after STA is recovered by fast connect or power save
		if (nrc_wifi_get_recovered_by_fast_connect(0) ||
			((nrc_ps_wakeup_reason(&boot) == NRC_SUCCESS) &&
			(boot == NRC_WAKEUP_REASON_RTC || boot == NRC_WAKEUP_REASON_TIM ||
			NRC_WAKEUP_REASON_GPIO ||NRC_WAKEUP_REASON_TIM_TIMER ))) {
			break;
		}

		SCAN_RESULTS results;
		if (nrc_wifi_scan(0) == WIFI_SUCCESS) {
			if (nrc_wifi_scan_results(0, &results)== WIFI_SUCCESS) {
				/* Find the ssid in scan results */
				app_log(DEBUG_LEVEL_ALWAYS, NULL, "SCAN_RESULT :  bssid / frequency / signal level / flags / ssid\n");
				for(int i = 0; i < results.n_result ; i++) {
					app_log(DEBUG_LEVEL_ALWAYS, NULL, "[%d] %s\t%s\t%s\t%s\t%s\n",
								  (i+1), 	(char*)results.result[i].bssid,
								  (char*)results.result[i].freq, (char*)results.result[i].sig_level,
								  (char*)results.result[i].flags, (char*)results.result[i].ssid);
					if((strcmp((char*)wifi_config.ssid, (char*)results.result[i].ssid)== 0)
					   && (results.result[i].security == wifi_config.security_mode)){
						app_log(DEBUG_LEVEL_ALWAYS, NULL, "[%s] %s is found \n", __func__, wifi_config.ssid);
						ap_found = 1;
						break;
					}
				}
			} else {
				return NRC_FAIL;
			}
			_delay_ms(1000);
		}
		if (ap_found) {
			break;
		}
	} while (1);

	do {
		if (wifi_connect(&wifi_config) == WIFI_SUCCESS) {
			app_log(DEBUG_LEVEL_ALWAYS, NULL, "Connected to AP - %s.\n", wifi_config.ssid);
			break;
		} else {
			app_log(DEBUG_LEVEL_ALWAYS, NULL, "Failed to connect to %s\n", wifi_config.ssid);
		}
	} while (1);

	if (nrc_wifi_get_recovered_by_fast_connect(STA_INTERFACE) && ip4_addr_isany(netif_ip4_addr(interface))) {
		if (wifi_config.ip_mode !=  WIFI_STATIC_IP) {
			wifi_station_dhcpc_start(STA_INTERFACE);
		}
	}

	do {
		_delay_ms(1000);

		if (!ip4_addr_isany(netif_ip4_addr(interface))) {
			app_log(DEBUG_LEVEL_ALWAYS, NULL, "[%s] IP Address: %s\n", __func__, ip4addr_ntoa(netif_ip4_addr(interface)));
			break;
		}

		if(++ip_get_retry_cnt > DHCPC_TIMEOUT) {
			app_log(DEBUG_LEVEL_ALWAYS, NULL, "[%s] nrc_sw_reset : %d\n", __func__, ip_get_retry_cnt);
			nrc_wifi_set_fast_connect(false);
			nrc_sw_reset();
		}
	} while (1);

	if (nrc_wifi_get_recovered_by_fast_connect(0) &&
		!((nrc_ps_wakeup_reason(&boot) == NRC_SUCCESS) &&
		(boot == NRC_WAKEUP_REASON_RTC || boot == NRC_WAKEUP_REASON_TIM ||
		NRC_WAKEUP_REASON_GPIO || NRC_WAKEUP_REASON_TIM_TIMER))) {
		app_log(DEBUG_LEVEL_ALWAYS, NULL, "Station recovered by fast connect\n");
	}

	return NRC_SUCCESS;
}

void get_relay_ssid(nvs_handle_t nvs_handle, char* relay_ssid_buf, size_t relay_ssid_buf_size)
{
	size_t length = relay_ssid_buf_size;
	if (nvs_get_str(nvs_handle, NVS_RELAY_SSID, relay_ssid_buf, &length) != NVS_OK) {
	}
}

#ifdef BRIDGE_STATIC_IP_BY_RELAY_NUMBER
void configure_static_bridge_ip_by_relay_ssid(char *ssid)
{
	uint8_t number = 0;
	const char *prefix = "relay";

	if (strncmp(ssid, prefix, strlen(prefix)) == 0) {
		number = (uint8_t)atoi(ssid + strlen(prefix));
	}

	char br_ipaddr[16], br_netmask[16], br_gateway[16];
	snprintf(br_ipaddr, sizeof(br_ipaddr), "192.168.200.%d", number);
	snprintf(br_netmask, sizeof(br_netmask), "255.255.255.0");
	snprintf(br_gateway, sizeof(br_gateway), "192.168.200.70");

	app_log(DEBUG_LEVEL_ALWAYS, NULL, "relay ssid : %s\n", ssid);
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "Setting bridge IP: %s, Netmask: %s, Gateway: %s\n",
				br_ipaddr, br_netmask, br_gateway);

	nrc_bridge_set_ip(br_ipaddr, br_netmask, br_gateway);
}
#endif

static nrc_err_t start_relay(nvs_handle_t nvs_handle)
{
	/* start relay */

	/* set network_mode to bridge */
	wifi_config.network_mode = WIFI_NETWORK_MODE_BRIDGE;

	/* 255 : about 25 sec (beacon interval * BEACON_LOSS_DETECTION_COUNT) */
	nrc_wifi_set_beacon_loss_detection(WLAN1_INTERFACE, true, BEACON_LOSS_DETECTION_COUNT);

	/* prepare bridge interface */
	if (nrc_add_bridge() != NRC_SUCCESS) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "[%s] Bridge interface bring up failed.\n", __func__);
		return NRC_FAIL;
	}

	if (relay_connect_to_ap(&wifi_config) == NRC_FAIL) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "[%s] Connection to %s failed.\n",
					  __func__,
					  wifi_config.ssid);
		return NRC_FAIL;
	}

	/* add softap interface to the bridge */
	if (nrc_add_bridge_interfaces() != NRC_SUCCESS) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "[%s] Adding wlan0/wlan1 to br interface failed.\n", __func__);
		return NRC_FAIL;
	}

	uint16_t s1g_freq = 0;
	if (nrc_wifi_get_channel_freq(STA_INTERFACE, &s1g_freq) != WIFI_SUCCESS) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "[%s] Failed to retrieve channg186el frequency...\n", __func__);
		return NRC_FAIL;
	}

	/* check if relay ssid exists in NVS */
	/* If relay ssid is in NVS, use it */
	if (provisioned) {
		char relay_ssid[64] = {0};
		get_relay_ssid(nvs_handle, relay_ssid, sizeof(relay_ssid));
		strcpy((char *) wifi_config.ssid, relay_ssid);
		app_log(DEBUG_LEVEL_ALWAYS, NULL, "relay ssid : %s\n", wifi_config.ssid);
	}
	wifi_config.channel = s1g_freq;

	if (relay_start_softap(&wifi_config) == NRC_FAIL) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "[%s] Soft AP with ssid %s failed.\n",
					  __func__,
					  wifi_config.ssid);
		return NRC_FAIL;
	}


	if (nrc_wifi_softap_set_short_beacon(0, false) != WIFI_SUCCESS){
		return NRC_FAIL;
	}

	while (nrc_wifi_get_state(1) != WIFI_STATE_CONNECTED) {
		_delay_ms(1000);
	}

	if (nrc_wifi_get_recovered_by_fast_connect(AP_INTERFACE) &&
		nrc_wifi_get_recovered_by_fast_connect(STA_INTERFACE)) {
		app_log(DEBUG_LEVEL_ALWAYS, NULL, "Relay recovered by fast connect\n");
	}

	return NRC_SUCCESS;
}

WIFI_CONFIG *get_system_config()
{
	return &wifi_config;
}

system_role_t get_system_role(nvs_handle_t nvs_handle)
{
	if (system_type == ROLE_SOFTAP || system_type == ROLE_STATION || system_type == ROLE_RELAY) {
		return system_type;
	}

	char system_role[16] = {0};
	size_t length = sizeof(system_role);

	if (nvs_get_str(nvs_handle, "system_role", system_role, &length) != NVS_OK) {
		/* Default system role is "ROLE_RELAY" */
		system_type = ROLE_RELAY;
	} else {
		if (!strcmp(system_role, "softap")) {
			system_type = ROLE_SOFTAP;
		} else if (!strcmp(system_role, "station")) {
			system_type = ROLE_STATION;
		} else if (!strcmp(system_role, "relay")) {
			system_type = ROLE_RELAY;
		} else {
			system_type = ROLE_UNDEFINED;
		}
	}

	return system_type;
}

system_role_t get_system_type()
{
	return system_type;
}

void multi_role_help(void)
{
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "Invalid system role stored. Resetting configuration.\n");
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "Please Set using below commands.\n");
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "\nFor SoftAP\n");
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "nvs set system_role softap\n");
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "Optional: (if not set WIFI_CONFIG will be used. check nvs_config.h/wifi_user_config.h)\n");
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "\tnvs set ssid <SoftAP SSID>\n");
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "\tnvs set_u8 wifi_security <security> (0: open, 1: wpa2psk, 2: wpa3owe, 3: wpa3sae)\n");
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "\tnvs set wifi_password <password> (For wpa2psk and wpa3sae)\n");
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "\tnvs set_u16 wifi_channel <s1g channel>\n");
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "\tnvs set wlan0_ip <IPv4 Address>\n");
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "\tnvs set wlan0_netmask <IPv4 Netmask>\n");
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "\tnvs set wlan0_gateway <IPv4 Gateway>\n");
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "\nFor Station\n");
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "nvs set system_role station\n");
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "Optional: (if not set WIFI_CONFIG will be used. check nvs_config.h/wifi_user_config.h)\n");
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "\tnvs set ssid <AP SSID>\n");
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "\tnvs set_u8 wifi_security <security> (0: open, 1: wpa2psk, 2: wpa3owe, 3: wpa3sae)\n");
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "\tnvs set wifi_password <password> (For wpa2psk and wpa3sae)\n");
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "\nFor Relay\n");
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "nvs set system_role relay\n");
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "Optional: (if not set WIFI_CONFIG will be used. check nvs_config.h/wifi_user_config.h)\n");
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "\tnvs set relay_ssid <Relay SSID>\n");
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "\tnvs set ssid <AP SSID>\n");
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "\tnvs set_u8 wifi_security <security> (0: open, 1: wpa2psk, 2: wpa3owe, 3: wpa3sae)\n");
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "\tnvs set wifi_password <password> (For wpa2psk and wpa3sae)\n");
}

void multi_role_config_init(nvs_handle_t nvs_handle)
{
	memset(&wifi_config, 0, WIFI_CONFIG_SIZE);
	nrc_wifi_set_config(&wifi_config);

	wifi_get_provisioned(nvs_handle, &provisioned);
	/* If not provisioned, set default SSID/PASSWORD */
	if (provisioned == 0) {
	}

	if (1) {
		const char *str_security[] = { "open", "wpa2-psk", "wpa3-owe", "wpa3-sae" };

		nrc_usr_print("[ %s ]\n", __func__);
		nrc_usr_print(" ssid : %s\n", wifi_config.ssid);
		nrc_usr_print(" security : %s\n", str_security[wifi_config.security_mode]);
		nrc_usr_print(" password : %s\n", wifi_config.password);
	}
}

nrc_err_t multi_role_system_init(nvs_handle_t nvs_handle)
{
	enum system_role role = get_system_role(nvs_handle);
	int vif_id = 0;
	char ssid[32 + 1];
	char relay_ssid[32 + 1];
#ifdef SMART_CONNECTION_ENABLE
	smart_connection_param_t smart_connection = {
		.vif = 0,
		.ip_idx = 0,
		.role = SC_ROLE_UNDEFINED,
		.scan_interval = SC_SCAN_INTERVAL,
		.scan_duration = SC_SCAN_DURATION,
		.roam_conn_timeout = 0,
		.sig_margin = 10,
		.sig_min = -60,
		.vendor_oui = 0x123456,
		.vendor_subcmd = 0
	};
#endif /* SMART_CONNECTION_ENABLE */

	/* Default role is relay */
	if (role == ROLE_UNDEFINED) {
		nvs_set_str(nvs_handle, "system_role", "relay");
		system_type = role = ROLE_RELAY;
	}
	memset(ssid, 0x0, sizeof(ssid));
	memcpy(ssid, wifi_config.ssid, sizeof(ssid));

	switch(role) {
		case ROLE_SOFTAP:
			app_log(DEBUG_LEVEL_ALWAYS, NULL, "SoftAP:\r\n");
			start_softap(nvs_handle);
#ifdef SUPPORT_EPAPER
			//if (!nrc_wifi_get_recovered_by_fast_connect(vif_id)) {
				nrc_display_state(true,  "softap" ,0 , ssid, NULL);
			//}
#endif
#ifdef SMART_CONNECTION_ENABLE
			smart_connection.vif = 0;
			smart_connection.role = SC_ROLE_ROOT;
			if (start_smart_connection(&smart_connection) != NRC_SUCCESS) {
				app_log(DEBUG_LEVEL_ALWAYS, NULL, "Failed to start SmartConn\n");
			}
#endif /* SMART_CONNECTION_ENABLE */
			return NRC_SUCCESS;
		case ROLE_STATION:
			app_log(DEBUG_LEVEL_ALWAYS, NULL, "Station:\r\n");
			start_station(nvs_handle);
			#ifdef SUPPORT_TCP_CLI
			tcp_cli_init();
			#endif /* SUPPORT_TCP_CLI */
#ifdef SUPPORT_EPAPER
			if (!nrc_wifi_get_recovered_by_fast_connect(vif_id)) {
				nrc_display_state(true,  "station", 0, ssid, NULL);
			}
#endif
#ifdef SMART_CONNECTION_ENABLE
			smart_connection.vif = 0;
			smart_connection.role = SC_ROLE_ROAMER;
			if (start_smart_connection(&smart_connection) != NRC_SUCCESS) {
				app_log(DEBUG_LEVEL_ALWAYS, NULL, "Failed to start SmartConn\n");
			}
#endif /* SMART_CONNECTION_ENABLE */
			return NRC_SUCCESS;
		case ROLE_RELAY:
			app_log(DEBUG_LEVEL_ALWAYS, NULL, "Relay:\r\n");
			start_relay(nvs_handle);
			#ifdef SUPPORT_TCP_CLI
			tcp_cli_init();
			#endif /* SUPPORT_TCP_CLI */
			memset(relay_ssid, 0x0, sizeof(relay_ssid));
			memcpy(relay_ssid, wifi_config.ssid, sizeof(relay_ssid));
#ifdef SUPPORT_EPAPER
			//if (!(nrc_wifi_get_recovered_by_fast_connect(0) &&
			//	nrc_wifi_get_recovered_by_fast_connect(1))) {
				nrc_display_state(true,  "relay", 0, ssid, relay_ssid);
			//}
#endif
#ifdef SMART_CONNECTION_ENABLE
			smart_connection.vif = 1;
			smart_connection.ip_idx = BRIDGE_INTERFACE;
			smart_connection.role = SC_ROLE_ROAMER;
			if (start_smart_connection(&smart_connection) != NRC_SUCCESS) {
				app_log(DEBUG_LEVEL_ALWAYS, NULL, "Failed to start SmartConn\n");
			}
#endif /* SMART_CONNECTION_ENABLE */
			return NRC_SUCCESS;
		default:
			multi_role_help();
			//nrc_epd_update_black_full_screen("[Setting]");
			return NRC_FAIL;
		}
}

bool wifi_is_provisioned(void)
{
	return !!provisioned;
}

void wifi_set_provisioned(nvs_handle_t nvs_handle, uint16_t count)
{
	nvs_set_u16(nvs_handle, "provisioned", count);
	provisioned = count;
}

void wifi_get_provisioned(nvs_handle_t nvs_handle, uint16_t *count)
{
	nvs_get_u16(nvs_handle, "provisioned", count);
}

uint16_t wifi_get_provisioned_count(void)
{
	return provisioned;
}
