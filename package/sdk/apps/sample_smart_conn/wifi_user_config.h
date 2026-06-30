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

#ifndef __WIFI_USER_CONFIG_H__
#define __WIFI_USER_CONFIG_H__

/**
 * User configurations for Wi-Fi settings can be added here. These definitions will
 * override the default values found in 'wifi_common/wifi_config.h'.
 *
 * The NVS (non-volatile storage) can also be used to override the configuration values
 * dynamically. See 'wifi_common/nvs_config.h' to find the keys that can be used to configure
 * the device using NVS.
 *
 * By defining these user configurations here, specific Wi-Fi settings such as the SSID,
 * password, security type, IP address, and other parameters can be customized for a
 * particular use case or application.
*/

// Defines for wifi_config_setup
#define COUNTRY_CODE "US"
#define NRC_WIFI_CHANNEL 9225

#define STR_SSID "HalowNRC"

//#define NRC_WIFI_SECURE  WIFI_SEC_WPA3_SAE
//#define NRC_WIFI_PASSWORD  "12345678"

#define TX_POWER 14		//14 dBm
#define TX_POWER_TYPE 1	// 0 - auto, 1 - limit, 2 - fixed power

//#define NRC_WIFI_RATE_CONTROL 0	//rate controll off
//#define NRC_WIFI_MCS_DEFAULT 10	//mcs 10

//#define NRC_WIFI_IP_MODE	WIFI_STATIC_IP
#define	NRC_STATIC_IP "192.168.200.1"
#define NRC_NETMASK "255.255.255.0"
#define NRC_GATEWAY "192.168.200.1"

#define	NRC_SOFTAP_IP NRC_STATIC_IP

//#define NRC_WIFI_AUTH_CONTROL WIFI_ENABLE_AUTH_CONTROL
#define NRC_WIFI_SCAN_MODE WIFI_SCAN_MODE_PASSIVE

#define NRC_WIFI_BCN_INTERVAL 2000

#define NRC_WIFI_PS_MODE_DEFAULT 0
#define NRC_WIFI_PS_IDLE_TIMEOUT_DEFAULT 100
#define NRC_WIFI_PS_SLEEP_TIME_DEFAULT 0xFFFFFFFF

// Defines for application
#define DHCPC_TIMEOUT 60 // (unit:sec) Timeout in sec for IP to be assigned using DHCP client.
#define DEFAULT_BAUD_RATE 9600
#define BCAST_SERVER_URL "192.168.200.1"

#define IDLE_TIMEOUT_TO_PS (10*60*1000) // 10 minutes (unit:ms)

#define NRC_WIFI_LISTEN_INTERVAL_DEFAULT 0	//

#define NRC_WIFI_SCAN_PERIOD 110 // (unit:ms) Scan period(dwell time)

#define NRC_WIFI_CCA_THRES_DEFAULT -65

#define BEACON_LOSS_DETECTION_COUNT 15

#define SC_SCAN_INTERVAL 5

#endif // __WIFI_USER_CONFIG_H__ //
