#include "nrc_sdk.h"
#include "lwip/sockets.h"
#include "multi_role_config.h"

#include "wifi_provision.h"
#include "nrc_udp_comm.h"
#include "app_debug.h"
#include "api_smart_conn.h"
#include "nvs.h"
#include "drv_rtc.h"

#ifdef SUPPORT_TCP_FOTA
#include "multi_role_register.h"
#include "multi_role_directory.h"
#endif

extern nvs_handle_t nvs_handle;
extern uint8_t recovery_on;
extern uint8_t unicast_on;
extern uint64_t uart_last_time;
extern uint8_t uart_normal_start;

static bool g_device_ready = false;

void device_ready (system_role_t role)
{
	const char *str_role[] =
	{
		[ROLE_SOFTAP] = "SOFTAP",
		[ROLE_STATION] = "STA",
		[ROLE_RELAY] = "RELAY"
	};

	g_device_ready = true;

	_delay_ms(100);
	nrc_usr_print("!!!!!! Device Ready : %s !!!!!!\n", str_role[role]);
}

///////////////////////for auto recovery - request by SS

#define	RECOVER_CONNECT_TIMEOUT		60 	// 1 min

static void send_keepalive (void)
{
	char data[2] = { 0x32, 0x34 };
	uint32_t ip_softap = get_softap_ip();
	uint16_t port = get_system_config()->remote_port;
	char ip[IP4ADDR_STRLEN_MAX];
	bool unicast = true;

	if (unicast_on && ip4addr_ntoa((ip4_addr_t *)&ip_softap))
		strcpy(ip, ip4addr_ntoa((ip4_addr_t *)&ip_softap));
	else
	{
		unicast = false;
		strcpy(ip, "255.255.255.255");
	}

	app_log(DEBUG_LEVEL_INFO, NULL, "[%s] ip=%s port=%u\n", __func__, ip, port);

	sendto_network(ip, port, data, sizeof(data), unicast);
}

static void status_check_task(void *pvParameters)
{
	system_role_t role  = (system_role_t)pvParameters;
	bool provisioned = wifi_is_provisioned();
	uint8_t vif_id = (role == ROLE_RELAY) ? 1 : 0;
	uint8_t timer_cnt = 0;

#if defined(KEEPALIVE_INTERVAL)
	uint16_t ka_interval = KEEPALIVE_INTERVAL;
#else
	uint16_t ka_interval = 0;
#endif

#ifdef SUPPORT_TCP_FOTA
	uint32_t reg_tick = 0;
#endif

	nvs_get_u16(nvs_handle, "ka_interval", &ka_interval);

	app_log(DEBUG_LEVEL_INFO, NULL, "[%s] role=%d provisioned=%d ka_interval=%u\n",
			__func__, role, provisioned, ka_interval);

	while(1) {
		if(nrc_wifi_get_state(vif_id) != WIFI_STATE_CONNECTED || get_current_hop() == -1) {
			app_log(DEBUG_LEVEL_ALWAYS, NULL, "[STA] state : %s, current hop : %d\n", nrc_wifi_get_state(vif_id) == WIFI_STATE_CONNECTED? "connected":"disconnected", get_current_hop());
			if (timer_cnt == 0) {
				app_log(DEBUG_LEVEL_ALWAYS, NULL, "[STA] Disonnected, provisioned=%d\n", provisioned);
			}

			timer_cnt++;

			if (recovery_on) {
				if (timer_cnt > RECOVER_CONNECT_TIMEOUT) {
					app_log(DEBUG_LEVEL_ALWAYS, NULL, "[STA] Connection Timeout (%u), Reboot ...\n",
							RECOVER_CONNECT_TIMEOUT);

					_delay_ms(1000);
					nrc_sw_reset();
				}
			}
		} else {

#ifdef SUPPORT_TCP_FOTA
			reg_tick++;
			if (reg_tick >= 60) {
				reg_tick = 0;
				tfota_try_register_later();
			}
#endif
		}

		_delay_ms(1000);
	}
}

#define MAX_CHILD_NODES 16

static void print_mac(const uint8_t *mac) {
	CPA("%02X:%02X:%02X:%02X:%02X:%02X\n",
		mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

void child_status_check_task(void *pvParameters)
{
	bool provisioned = wifi_is_provisioned();
	uint8_t bssid_list[MAX_CHILD_NODES][6];
	uint16_t count = 0;
	uint16_t last_count = 0;
	const uint8_t vif_id = 0;
	const uint32_t check_time = 1000;
	system_role_t *role  = pvParameters;

	while (1) {
		device_list_check_active(&count);

		if (count != last_count) {
			if (provisioned)
			{
				uint16_t max_count = wifi_get_provisioned_count();
				app_log(DEBUG_LEVEL_ALWAYS, NULL, "%s: Number of active children (%u/%u)\n",
						__func__, count, max_count);

			}
			else
			{
				app_log(DEBUG_LEVEL_ALWAYS, NULL, "%s: Number of connected children (%u)\n",
						__func__, count);

			}

			last_count = count;
		}

		if (recovery_on && provisioned) {

		}

		_delay_ms(check_time);
	}
}

void init_status_check(system_role_t role)
{
	init_device_list(role);

	if(role == ROLE_STATION || role == ROLE_RELAY)
		xTaskCreate(status_check_task, "Status Check Task", configMINIMAL_STACK_SIZE, (void *)role, USER_APP_TASK_PRIORITY, NULL);

	if(role == ROLE_SOFTAP)
		xTaskCreate(child_status_check_task, "child_status_check_task", 2048, NULL, USER_APP_TASK_PRIORITY, NULL);
}

