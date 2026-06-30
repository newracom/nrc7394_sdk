#include "nrc_sdk.h"

#include "wifi_config_setup.h"
#include "wifi_connect_common.h"
#include "wifi_config.h"
#include "nrc_lwip.h"
#include "nrc_eth_if.h"
#include "lwip/dhcp.h"
#include "netif/bridgeif.h"
#include "app_debug.h"
#include "wifi_relay_service.h"
#include "nvs.h"

extern struct netif br_netif;
extern nvs_handle_t nvs_handle;

#define WIFI_CONNECT_RETRY_COUNT 10
#define WIFI_CONNECT_RETRY_DELAY_MS 500

nrc_err_t relay_start_softap(WIFI_CONFIG *param)
{
	if (nrc_wifi_get_state(AP_INTERFACE) >= WIFI_STATE_SOFTAP_START) {
		app_log(DEBUG_LEVEL_ALWAYS, NULL, "[%s] Relay AP already started\n", __func__);
		return WIFI_SUCCESS;
	}

	app_log(DEBUG_LEVEL_ALWAYS, NULL, "[%s] Trying to start Soft AP (SSID:%s, S1G_CH:%d , BW:%d)\n", \
			 __func__, (char *)param->ssid,  (int)param->channel,  (int)param->bw);

	if (nrc_wifi_add_network(AP_INTERFACE) < 0) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "[%s] Fail to init \n", __func__);
		return WIFI_FAIL_INIT;
	}

	if(nrc_wifi_softap_set_conf(AP_INTERFACE, (char *)param->ssid, (int)param->channel, (int)param->bw,
			(int)param->security_mode, (char *)param->password, (int)param->sae_pwe) != WIFI_SUCCESS) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "[%s] Fail to set sotftap config\n", __func__);
		return WIFI_FAIL;
	}

	if(param->bss_max_idle > 0) {
		uint32_t disassociate_timeout = 0;
		disassociate_timeout = (param->bss_max_idle*param->bss_retry_cnt);
		app_log(DEBUG_LEVEL_ALWAYS, NULL, "[%s] bss max idle : %d [sec]\n", __func__, param->bss_max_idle);
		app_log(DEBUG_LEVEL_ALWAYS, NULL, "[%s] bss max idle count : %d\n", __func__, param->bss_retry_cnt);
		app_log(DEBUG_LEVEL_ALWAYS, NULL, "[%s] Disassociate Timeout : %d [sec]\n", __func__, disassociate_timeout);
		nrc_wifi_softap_set_bss_max_idle(AP_INTERFACE, param->bss_max_idle, param->bss_retry_cnt);
	}

	if(nrc_wifi_set_rate_control(AP_INTERFACE, (bool)param->rc) != WIFI_SUCCESS) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "[%s] Fail to set rate control\n", __func__);
		return WIFI_FAIL;
	}

	if(nrc_wifi_set_mcs (param->mcs) != WIFI_SUCCESS) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "[%s] Fail to set mcs\n", __func__);
		return WIFI_FAIL;
	}

	if(nrc_wifi_set_cca_threshold(AP_INTERFACE, param->cca_thres) != WIFI_SUCCESS) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "[%s] Fail to set cca threshold\n", __func__);
		return WIFI_FAIL;
	}

	if(nrc_wifi_softap_set_ignore_broadcast_ssid(AP_INTERFACE, param->ignore_broadcast_ssid) != WIFI_SUCCESS) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "[%s] Fail to set hidden ssid\n", __func__);
		return WIFI_FAIL;
	}

	if(nrc_wifi_softap_set_max_num_sta(AP_INTERFACE, param->max_num_sta) != WIFI_SUCCESS) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "[%s] Fail to set max_num_sta\n", __func__);
		return WIFI_FAIL;
	}

	if(nrc_wifi_softap_set_beacon_interval(AP_INTERFACE,  param->bcn_interval) != WIFI_SUCCESS) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "[%s] Fail to set bcn_interval %d\n", __func__, param->bcn_interval);
		return WIFI_FAIL;
	}

	if(nrc_wifi_softap_start(AP_INTERFACE) != WIFI_SUCCESS) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "[%s] Fail to start sotftap\n", __func__);
		return WIFI_FAIL_SOFTAP;
	}
	return WIFI_SUCCESS;
}

static int scan_ap_count = 0;
void relay_set_scan_ap_count(uint8_t count)
{
	scan_ap_count = count;
}

uint8_t relay_get_scan_ap_count(void)
{
	return scan_ap_count;
}

nrc_err_t relay_connect_to_ap(WIFI_CONFIG* param)
{
	int i = 0;
	int retry = 0;
	int dhcp_server = 0;
	int ap_found = 0;

	dhcp_server = param->dhcp_server;

	if (nrc_wifi_get_recovered_by_fast_connect(STA_INTERFACE)) {
		goto connected;
	}

	if (wifi_init_with_vif(STA_INTERFACE, param)!= WIFI_SUCCESS) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "[%s] Fail for wifi_init_with_vif\n", __func__);
		return NRC_FAIL;
	}

	netif_set_default(nrc_netif[STA_INTERFACE]);

#if 1
	do {
		SCAN_RESULTS results;
		uint8_t sta_count = 0;
		nrc_usr_print("%s: ssid=%s\n", __func__, param->ssid);
		relay_set_scan_ap_count(0);

		if (nrc_wifi_scan_ssid(STA_INTERFACE, (char*)param->ssid) == WIFI_SUCCESS) {
			if (nrc_wifi_scan_results(STA_INTERFACE, &results)== WIFI_SUCCESS) {
				/* Find the ssid in scan results */
				app_log(DEBUG_LEVEL_INFO, NULL, "[%s] Looking for '%s'\n", __func__, param->ssid);
				app_log(DEBUG_LEVEL_INFO, NULL, "SCAN_RESULT :  bssid / frequency / signal level / flags / ssid\n");
				for(int i = 0; i < results.n_result ; i++) {
					app_log(DEBUG_LEVEL_ALWAYS, NULL, "[%d] %s\t%s\t%s\t%s\t%s\n",
								  (i+1), 	(char*)results.result[i].bssid,
								  (char*)results.result[i].freq, (char*)results.result[i].sig_level,
								  (char*)results.result[i].flags, (char*)results.result[i].ssid);
					if((strcmp((char*)param->ssid, (char*)results.result[i].ssid)== 0)
					   && (results.result[i].security == param->security_mode)){
						sta_count++;
						app_log(DEBUG_LEVEL_INFO, NULL, "[%s] %s is found \n", __func__, param->ssid);
						ap_found = 1;
					}
				}
				relay_set_scan_ap_count(sta_count);
				if(ap_found)
					break;
			} else {
				return NRC_FAIL;
			}
			_delay_ms(1000);
		}
		if (ap_found) {
			break;
		}
	} while (1);
#endif

	/* Try to connect */
	for (retry = 0; retry < WIFI_CONNECT_RETRY_COUNT; retry++) {
		tWIFI_STATUS ret = wifi_connect_with_vif(STA_INTERFACE, param);

		if (ret == WIFI_SUCCESS) {
			app_log(DEBUG_LEVEL_ALWAYS, NULL,
				"Connected to AP - %s.\n", param->ssid);
			break;
		}

		app_log(DEBUG_LEVEL_ALWAYS, NULL,
			"wifi_connect_with_vif() failed (ret=%d), retry=%d/%d\n",
			ret, retry + 1, WIFI_CONNECT_RETRY_COUNT);

		vTaskDelay(pdMS_TO_TICKS(WIFI_CONNECT_RETRY_DELAY_MS));
	}

	if (retry >= WIFI_CONNECT_RETRY_COUNT) {
		app_log(DEBUG_LEVEL_ALWAYS, NULL, "Remove FC & nrc_sw_reset\n");
		nrc_wifi_set_fast_connect(false);
		nrc_sw_reset();
		return NRC_FAIL;
	}

connected:
#ifndef BRIDGE_STATIC_IP_BY_RELAY_NUMBER
	if (param->network_mode == WIFI_NETWORK_MODE_BRIDGE) {
		int ip_get_retry_cnt = 0;
		struct netif *interface = nrc_netif_get_by_idx(BRIDGE_INTERFACE);
		if (ip4_addr_isany(netif_ip4_addr(interface))) {
			bridgeif_add_port(&br_netif, nrc_netif[STA_INTERFACE]);
			if (param->ip_mode !=  WIFI_STATIC_IP) {
				wifi_bridge_dhcpc_start();
			} else {
				char ip_str[16] = {0};
				size_t length;
				if (param->ip_mode == WIFI_STATIC_IP) {
					app_log(DEBUG_LEVEL_ALWAYS, NULL, "[%s:%d] set static ip addr\n", __func__,__LINE__);
					length = MAX_STATIC_IP_LENGTH + 1;
					if (nvs_get_str(nvs_handle, NVS_BRIDGE_IP, ip_str, &length) == NVS_OK) {
						strcpy(param->static_ip, ip_str);
					}
					length = MAX_STATIC_IP_LENGTH + 1;
					if (nvs_get_str(nvs_handle, NVS_BRIDGE_NETMASK, ip_str, &length) == NVS_OK) {
						strcpy(param->netmask, ip_str);
					}
					length = MAX_STATIC_IP_LENGTH + 1;
					if (nvs_get_str(nvs_handle, NVS_BRIDGE_GATEWAY, ip_str, &length) == NVS_OK) {
						strcpy(param->gateway, ip_str);
					}
					nrc_bridge_set_ip(param->static_ip,
									  param->netmask,
									  param->gateway);
				}
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

		return WIFI_SUCCESS;
	}
#endif

	return NRC_SUCCESS;
}

nrc_err_t nrc_add_bridge()
{
	if (netif_is_up(&br_netif)) {
		app_log(DEBUG_LEVEL_ALWAYS, NULL, "bridge interface already exists.\n");
		return NRC_SUCCESS;
	}

	if (!setup_wifi_bridge_interface()) {
		return NRC_FAIL;
	}

	/*
	 * This is already performed in setup_wifi_bridge_interface.
	 * Why do we need this again?
	 * For Relay Recovery, bridge address will be invalid if we set it again.
	 * - In setup_wifi_bridge_interface, bridge mac is based on netif 0 mac.
	 *   but here, bridge mac is based on netif 1 (STA_INTERFACE).
	 */
#if 0
	/* set MAC address for the bridge interface as station interface MAC address */
	/* Set third octet to be one added to third octet of station interface. */
	memcpy(br_netif.hwaddr, nrc_netif[STA_INTERFACE]->hwaddr, 6);
	if (br_netif.hwaddr[3] < 0xff) {
		br_netif.hwaddr[3]++;
		/* Check if br_netif HW mac with AP interface and if they are the same */
		if (memcmp(br_netif.hwaddr, nrc_netif[AP_INTERFACE]->hwaddr, 6) == 0) {
			br_netif.hwaddr[3]++;
		}
	} else {
		br_netif.hwaddr[3] = 0;
	}
#endif
	return NRC_SUCCESS;
}

nrc_err_t nrc_add_bridge_interfaces()
{
	if (!netif_is_up(&br_netif)) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "bridge interface does not exist.\n");
		return NRC_FAIL;
	}

	/* Add Soft AP interface to the bridge */
	/* Station interface will be added when it is associated with AP */
	bridgeif_add_port(&br_netif, nrc_netif[AP_INTERFACE]);

	return NRC_SUCCESS;
}

nrc_err_t nrc_bridge_dhcpc_start()
{
	if (!netif_is_up(&br_netif)) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "bridge interface does not exist.\n");
		return NRC_FAIL;
	}

	if (dhcp_start(&br_netif)) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "DHCP client on bridge interface failed.\n");
		return NRC_FAIL;
	}

	return NRC_SUCCESS;
}

nrc_err_t nrc_bridge_set_ip(char *ipaddr, char *netmask, char *gateway)
{
	if (IP_IS_V4(&addr)) {
		ip4_addr_t ip_addr, netmask_addr, gw_addr;
		ip4addr_aton(ipaddr, &ip_addr);

		if (gateway == NULL) {
			/* Set GW */
			IP4_ADDR(&gw_addr, ip4_addr1_16(&ip_addr), ip4_addr2_16(&ip_addr), ip4_addr3_16(&ip_addr), 1);
		} else {
			ip4addr_aton(gateway, &gw_addr);
		}

		if (netmask == NULL) {
			/* Set Netmask */
			IP4_ADDR(&netmask_addr, 255, 255, 255, 0);
		} else {
			ip4addr_aton(netmask, &netmask_addr);
		}

		netif_set_addr(&br_netif, &ip_addr, &netmask_addr, &gw_addr);
	}
#if LWIP_IPV6
	else {
		int8_t index = 0;
		/* Set static ipv6 address to available slot in netif */
		if (netif_add_ip6_address(&br_netif, &addr.u_addr.ip6, &index) != ERR_OK) {
			return NRC_FAIL;
		}

		netif_ip6_addr_set_state(&br_netif, index, IP6_ADDR_PREFERRED);
	}
#endif
	return NRC_SUCCESS;
}
