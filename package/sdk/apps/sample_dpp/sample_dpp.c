/*
 * MIT License
 *
 * Copyright (c) 2025 Newracom, Inc.
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

#include "nrc_sdk.h"
#include "wifi_config_setup.h"
#include "wifi_connect_common.h"

/******************************************************************************
 * FunctionName : run_sample_dpp
 * Description  : sample test for DPP connection
 * Parameters   : WIFI_CONFIG
 * Returns      : 0 or -1 (0: success, -1: fail)
 *******************************************************************************/
nrc_err_t run_sample_dpp(WIFI_CONFIG *param)
{
	int ap = (param->device_mode == WIFI_MODE_AP);
	int i = 0;

	nrc_usr_print("[%s] Sample App for DPP \n", __func__);
	if (param->security_mode != WIFI_SEC_DPP) {
		nrc_usr_print("security_mode is invalid(%d)\n", param->security_mode);
		return NRC_FAIL;
	}

	if (ap) {
		/* See 6.2.2 of Wi-Fi Easy Connect Specification v3.0 */
		if (param->channel == 0) {
			param->channel = 9205;
			param->nons1g_freq = STAGetNonS1GFreq(param->channel);
		}
		nrc_usr_print(" - mode : AP\n");
		nrc_usr_print(" - channel : %d\n", param->channel);
	} else {
		nrc_usr_print(" - mode : STA\n");
	}
	nrc_usr_print(" - country: %s\n", param->country);
	nrc_usr_print(" - ssid : %s\n", param->ssid);
	nrc_usr_print(" - DPP role: %s\n", param->dpp_configurator? "configurator" : "enrollee");

	/* set initial wifi configuration */
	while(1){
		if (wifi_init(param) == WIFI_SUCCESS) {
			nrc_usr_print ("[%s] wifi_init Success\n", __func__);
			break;
		} else {
			nrc_usr_print ("[%s] wifi_init Failed\n", __func__);
			_delay_ms(1000);
		}
	}

	if (ap) {
		/* create AP */
		if (wifi_start_softap(param) != WIFI_SUCCESS) {
			nrc_usr_print ("[%s] Fail to start softap\n", __func__);
			return NRC_FAIL;
		}

		if (param->dhcp_server == 1) {
			nrc_usr_print("[%s] Trying to start DHCP Server\n",	__func__);
			if(nrc_wifi_softap_start_dhcp_server(0) != WIFI_SUCCESS) {
				nrc_usr_print("[%s] Fail to start dhcp server\n", __func__);
				return NRC_FAIL;
			}
		} else if (nrc_wifi_softap_set_ip(0, (char *)&param->static_ip, (char *)&param->netmask, (char *)&param->gateway) != WIFI_SUCCESS) {
			nrc_usr_print("[%s] Fail set AP's IP\n", __func__);
			return NRC_FAIL;
		}

		/* Push button every 110sec */
		while (1) {
			if (nrc_wifi_dpp_push_button(0, param->dpp_configurator) == WIFI_SUCCESS) {
				nrc_usr_print ("[%s] Wait for Peer...\n", __func__);
				_delay_ms(110000); // 110sec
				/* Check if AP Enrollee is connected */
				if (nrc_wifi_softap_get_sta_num(0) > 0 && param->dpp_configurator == 0) {
					break;
				}
			} else {
				nrc_usr_print ("[%s] Fail to push button\n", __func__);
				return NRC_FAIL;
			}
		}
	} else {
		/* Ready to push button */
		if (wifi_connect(param) != WIFI_SUCCESS) {
			nrc_usr_print ("[%s] Fail for connection %s\n", __func__, param->ssid);
			return NRC_FAIL;
		}

		/* Push button every 110sec */
		while (1) {
			if (param->dpp_configurator || nrc_wifi_get_state(0) != WIFI_STATE_CONNECTED) {
				if (nrc_wifi_dpp_push_button(0, param->dpp_configurator) == WIFI_SUCCESS) {
					nrc_usr_print ("[%s] Wait for Peer...\n", __func__);
				} else {
					nrc_usr_print ("[%s] Fail to push button\n", __func__);
					return NRC_FAIL;
				}
			}

			if (nrc_wifi_get_state(0) == WIFI_STATE_CONNECTED)
				_delay_ms(110000); // 110sec
		}
	}

	nrc_usr_print("[%s] End of run_sample_dpp\n", __func__);

	return NRC_SUCCESS;
}

/******************************************************************************
 * FunctionName : user_init
 * Description  : Start Code for User Application, Initialize User function
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
WIFI_CONFIG wifi_config;
WIFI_CONFIG* param = &wifi_config;

void user_init(void)
{
	memset(param, 0x0, WIFI_CONFIG_SIZE);
	nrc_usr_print("[%s] \n", __func__);

	nrc_wifi_set_config(param);

	run_sample_dpp(param);
}
