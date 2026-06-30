#ifndef __WIFI_SERVICE_H__
#define __WIFI_SERVICE_H__

#include "nrc_sdk.h"
#include "wifi_config.h"
#include "wifi_config_setup.h"

/* user can override SSID for relay AP using below NVS key */
#define NVS_RELAY_SSID "relay_ssid"
/* user can override bridge ip/netmask/gateway using below NVS keys if static ip is used */
#define NVS_BRIDGE_IP "br_ip"
#define NVS_BRIDGE_NETMASK "br_netmask"
#define NVS_BRIDGE_GATEWAY "br_gateway"

#define AP_INTERFACE 0
#define STA_INTERFACE 1

nrc_err_t relay_start_softap(WIFI_CONFIG *param);
nrc_err_t relay_connect_to_ap(WIFI_CONFIG *param);
uint8_t relay_get_scan_ap_count(void);

nrc_err_t nrc_add_bridge();
nrc_err_t nrc_add_bridge_interfaces();
nrc_err_t nrc_bridge_dhcpc_start();
nrc_err_t nrc_bridge_set_ip(char *ipaddr, char *netmask, char *gateway);
#endif
