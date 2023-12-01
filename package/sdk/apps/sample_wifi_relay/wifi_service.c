#include "nrc_sdk.h"

#include "wifi_config_setup.h"
#include "wifi_connect_common.h"
#include "wifi_config.h"
#include "nrc_lwip.h"
#include "nrc_eth_if.h"
#include "lwip/netif.h"
#include "lwip/dhcp.h"
#include "netif/bridgeif.h"

#include "wifi_service.h"

extern struct netif* nrc_netif[MAX_IF];
extern struct netif br_netif;

nrc_err_t relay_start_softap(WIFI_CONFIG *param)
{
	nrc_usr_print("[%s] Trying to start Soft AP (SSID:%s, S1G_CH:%d , BW:%d)\n", \
			 __func__, (char *)param->ssid,  (int)param->channel,  (int)param->bw);

	if (nrc_wifi_add_network(AP_INTERFACE) < 0) {
		nrc_usr_print("[%s] Fail to init \n", __func__);
		return WIFI_FAIL_INIT;
	}

	if(nrc_wifi_softap_set_conf(AP_INTERFACE, (char *)param->ssid, (int)param->channel, (int)param->bw,
			(int)param->security_mode, (char *)param->password) != WIFI_SUCCESS) {
		nrc_usr_print("[%s] Fail to set sotftap config\n", __func__);
		return WIFI_FAIL;
	}

	if(param->bss_max_idle > 0) {
		uint32_t disassociate_timeout = 0;
		disassociate_timeout = (param->bss_max_idle*param->bss_retry_cnt);
		nrc_usr_print("[%s] bss max idle : %d [sec]\n", __func__, param->bss_max_idle);
		nrc_usr_print("[%s] bss max idle count : %d\n", __func__, param->bss_retry_cnt);
		nrc_usr_print("[%s] Disassociate Timeout : %d [sec]\n", __func__, disassociate_timeout);
		nrc_wifi_softap_set_bss_max_idle(AP_INTERFACE, param->bss_max_idle, param->bss_retry_cnt);
	}

	if(nrc_wifi_set_rate_control(AP_INTERFACE, (bool)param->rc) != WIFI_SUCCESS) {
		nrc_usr_print("[%s] Fail to set rate control\n", __func__);
		return WIFI_FAIL;
	}

	if(nrc_wifi_set_mcs (param->mcs) != WIFI_SUCCESS) {
		nrc_usr_print("[%s] Fail to set mcs\n", __func__);
		return WIFI_FAIL;
	}

	if(nrc_wifi_set_cca_threshold(AP_INTERFACE, param->cca_thres) != WIFI_SUCCESS) {
		nrc_usr_print("[%s] Fail to set cca threshold\n", __func__);
		return WIFI_FAIL;
	}

	if(nrc_wifi_softap_set_ignore_broadcast_ssid(AP_INTERFACE, param->ignore_broadcast_ssid) != WIFI_SUCCESS) {
		nrc_usr_print("[%s] Fail to set hidden ssid\n", __func__);
		return WIFI_FAIL;
	}

	if(nrc_wifi_softap_set_max_num_sta(AP_INTERFACE, param->max_num_sta) != WIFI_SUCCESS) {
		nrc_usr_print("[%s] Fail to set max_num_sta\n", __func__);
		return WIFI_FAIL;
	}

	if(nrc_wifi_softap_start(AP_INTERFACE) != WIFI_SUCCESS) {
		nrc_usr_print("[%s] Fail to start sotftap\n", __func__);
		return WIFI_FAIL_SOFTAP;
	}
	return WIFI_SUCCESS;
}

nrc_err_t relay_connect_to_ap(WIFI_CONFIG* param)
{
	int i = 0;
	int count = 0;
	int dhcp_server = 0;

	count = 10;
	dhcp_server = param->dhcp_server;

	if (wifi_init_with_vif(STA_INTERFACE, param)!= WIFI_SUCCESS) {
		nrc_usr_print ("[%s] ASSERT! Fail for init\n", __func__);
		return NRC_FAIL;
	}

	netif_set_default(nrc_netif[STA_INTERFACE]);

	/* Try to connect */
	if (wifi_connect_with_vif(STA_INTERFACE, param)!= WIFI_SUCCESS) {
		nrc_usr_print ("[%s] Pairing to AP failed. (results:%d)\n", __func__);
		return NRC_FAIL;
	}

	if (param->network_mode == WIFI_NETWORK_MODE_BRIDGE) {
		/* ignore wifi state for bridge mode */
		return WIFI_SUCCESS;
	}
#if 0
	/* check if IP is ready */
	while(1) {
		if (nrc_addr_get_state(0) == NET_ADDR_SET) {
			nrc_usr_print("[%s] IP ...\n",__func__);
			break;
		} else {
			nrc_usr_print("[%s] IP Address setting State : %d != NET_ADDR_SET(%d) yet...\n",
						  __func__, nrc_addr_get_state(0), NET_ADDR_SET);
		}
		_delay_ms(1000);
	}
#endif
	return NRC_SUCCESS;
}

nrc_err_t nrc_add_bridge()
{
	if (netif_is_up(&br_netif)) {
		nrc_usr_print("bridge interface already exists.\n");
		return NRC_FAIL;
	}

	if (!setup_wifi_bridge_interface()) {
		return NRC_FAIL;
	}

	return NRC_SUCCESS;
}

nrc_err_t nrc_add_bridge_interfaces()
{
	if (!netif_is_up(&br_netif)) {
		nrc_usr_print("bridge interface does not exist.\n");
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
		nrc_usr_print("bridge interface does not exist.\n");
		return NRC_FAIL;
	}

	if (dhcp_start(&br_netif)) {
		nrc_usr_print("DHCP client on bridge interface failed.\n");
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
