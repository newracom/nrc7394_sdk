/*
 * MIT License
 *
 * Copyright (c) 2023 Newracom, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "wifi_config_setup.h"
#include "nrc_sdk.h"
#include "wifi_connect_common.h"

#include "wifi_service.h"
#include "nvs.h"

#define RELAY_SSID "relay"

/* user can override SSID for relay AP using below NVS key */
#define NVS_RELAY_SSID "relay_ssid"
/* user can override bridge ip/netmask/gateway using below NVS keys if static ip is used */
#define NVS_BRIDGE_IP "br_ip"
#define NVS_BRIDGE_NETMASK "br_netmask"
#define NVS_BRIDGE_GATEWAY "br_gateway"

//#define FEATURE_UART_TCP_CLIENT

#ifdef FEATURE_UART_TCP_CLIENT
void uart_tcp_client_init(char *remote_addr, uint16_t remote_port);
#endif

void user_init(void)
{
	WIFI_CONFIG wifi_config;

	/* prepare bridge interface */
	if (nrc_add_bridge() != NRC_SUCCESS) {
		nrc_usr_print("[%s] Bridge interface bring up failed.\n", __func__);
		return;
	}

	/* add softap interface to the bridge */
	if (nrc_add_bridge_interfaces() != NRC_SUCCESS) {
		nrc_usr_print("[%s] Adding wlan0/wlan1 to br interface failed.\n", __func__);
		return;
	}

	memset(&wifi_config, 0, WIFI_CONFIG_SIZE);

	nrc_wifi_set_config(&wifi_config);

	/* set network_mode to bridge */
	wifi_config.network_mode = WIFI_NETWORK_MODE_BRIDGE;

	/* save wifi_config in NVS */
	nrc_save_wifi_config(&wifi_config, 0);

	if (relay_connect_to_ap(&wifi_config) == NRC_FAIL) {
		nrc_usr_print("[%s] Connection to %s failed.\n",
					  __func__,
					  wifi_config.ssid);
		return;
	}

	uint16_t s1g_freq = 0;
	if (nrc_wifi_get_channel_freq(STA_INTERFACE, &s1g_freq) != WIFI_SUCCESS) {
		A("[%s] Failed to retrieve frequench...\n", __func__);
		return;
	}

	nvs_handle_t nvs_handle = 0;
	char relay_ssid[MAX_SSID_LENGTH + 1] = {0, };
	size_t length = MAX_SSID_LENGTH + 1;

	if (nvs_open(NVS_DEFAULT_NAMESPACE, NVS_READWRITE, &nvs_handle) != NVS_OK) {
		A("[%s] error opening NVS...\n", __func__);
		return;
	}

	/* check if relay ssid exists in NVS */
	/* If relay ssid is in NVS, use it */
	if (nvs_get_str(nvs_handle, NVS_RELAY_SSID, relay_ssid, &length) != NVS_OK) {
		/* if not, use default relay ssid and save it to nvs */
		strcpy(relay_ssid, RELAY_SSID);
		if (nvs_set_str(nvs_handle, NVS_RELAY_SSID, relay_ssid) != NVS_OK) {
			A("[%s] error saving relay SSID to NVS...\n");
		}
	}

	strcpy((char *) wifi_config.ssid, relay_ssid);
	wifi_config.channel = s1g_freq;

	if (relay_start_softap(&wifi_config) == NRC_FAIL) {
		nrc_usr_print("[%s] Soft AP with ssid %s failed.\n",
					  __func__,
					  wifi_config.ssid);
		return;
	}

	while (nrc_wifi_get_state(1) != WIFI_STATE_CONNECTED) {
		_delay_ms(1000);
	}

	if (nrc_wifi_get_state(1) == WIFI_STATE_CONNECTED) {
		if (wifi_config.ip_mode == WIFI_DYNAMIC_IP) {
			nrc_bridge_dhcpc_start();
		} else {
			char ip_str[MAX_STATIC_IP_LENGTH+1];
			length = MAX_STATIC_IP_LENGTH + 1;
			if (nvs_get_str(nvs_handle, NVS_BRIDGE_IP, ip_str, &length) == NVS_OK) {
				strcpy(wifi_config.static_ip, ip_str);
			}
			length = MAX_STATIC_IP_LENGTH + 1;
			if (nvs_get_str(nvs_handle, NVS_BRIDGE_NETMASK, ip_str, &length) == NVS_OK) {
				strcpy(wifi_config.netmask, ip_str);
			}
			length = MAX_STATIC_IP_LENGTH + 1;
			if (nvs_get_str(nvs_handle, NVS_BRIDGE_GATEWAY, ip_str, &length) == NVS_OK) {
				strcpy(wifi_config.gateway, ip_str);
			}
			nrc_bridge_set_ip(wifi_config.static_ip,
							  wifi_config.netmask,
							  wifi_config.gateway);
		}
	}
#ifdef FEATURE_UART_TCP_CLIENT
	uart_tcp_client_init(wifi_config.remote_addr, wifi_config.remote_port);
#endif
}
