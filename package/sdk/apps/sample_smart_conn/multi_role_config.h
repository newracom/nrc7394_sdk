#ifndef __MULTI_ROLE_CONFIG_H__
#define __MULTI_ROLE_CONFIG_H__

#include "nvs.h"
#include "wifi_config_setup.h"

typedef enum system_role {
	ROLE_UNDEFINED = -1,
	ROLE_SOFTAP,
	ROLE_STATION,
	ROLE_RELAY
} system_role_t;

WIFI_CONFIG *get_system_config();
nrc_err_t multi_role_system_init(nvs_handle_t nvs_handle);
/* Retrieve system role from nvs */
system_role_t get_system_role(nvs_handle_t nvs_handle);
/* Retrieve system role saved in memory. */
system_role_t get_system_type();
void multi_role_config_init(nvs_handle_t nvs_handle);
void get_relay_ssid(nvs_handle_t nvs_handle, char* relay_ssid_buf, size_t relay_ssid_buf_size);
bool wifi_is_provisioned();
void wifi_set_provisioned(nvs_handle_t nvs_handle, uint16_t count);
void wifi_get_provisioned(nvs_handle_t nvs_handle, uint16_t *count);
uint16_t wifi_get_provisioned_count(void);

#endif /* __MULTI_ROLE_CONFIG_H__ */
