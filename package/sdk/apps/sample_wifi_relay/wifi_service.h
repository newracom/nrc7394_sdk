#ifndef __WIFI_SERVICE_H__
#define __WIFI_SERVICE_H__

#include "nrc_sdk.h"
#include "wifi_config.h"

#define AP_INTERFACE 0
#define STA_INTERFACE 1

nrc_err_t relay_start_softap(WIFI_CONFIG *param);
nrc_err_t relay_connect_to_ap(WIFI_CONFIG *param);

nrc_err_t nrc_add_bridge();
nrc_err_t nrc_add_bridge_interfaces();
nrc_err_t nrc_bridge_dhcpc_start();
nrc_err_t nrc_bridge_set_ip(char *ipaddr, char *netmask, char *gateway);
#endif
