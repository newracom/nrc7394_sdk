#include "nrc_sdk.h"
#include "nrc_lwip.h"
#include "api_uart_dma.h"
#include "lwip/sockets.h"
#include "lwip/etharp.h"
#include "lfs_port.h"

#include "multi_role_config.h"

#include "multi_role_util.h"
#include "multi_role_stats.h"

#include "multi_role_ps.h"
#include "multi_role_bfota.h"
#include "multi_role_status.h"

#ifdef SUPPORT_TCP_FOTA
#include "multi_role_directory.h"
#include "multi_role_tfota_server.h"
#include "multi_role_register.h"
#endif

#include "multi_role_iperf.h"
#include "wifi_provision.h"
#include "nrc_ps_api.h"

#include "api_bcast_fota.h"
#include "sample_smart_conn_version.h"
#include "nvs.h"
#include "nvs_config.h"
#include "wifi_config.h"
#include "app_debug.h"
#ifdef SUPPORT_TCP_CLI
#include "tcp_cli.h"
#endif /* SUPPORT_TCP_CLI */

#include "epd_status_display.h"
#include "link_status.h"
#include "app_feature_cfg.h"

/* nvs value to control */
nvs_handle_t nvs_handle = 0;

#if defined(MAX_ADDRESSED_DEVICES)
uint8_t max_addressed_devices = MAX_ADDRESSED_DEVICES; /* maximum number of devices addressed */
#else
#error "MAX_ADDRESSED_DEVICES is not defined."
#endif

uint8_t recovery_on = 1; /* 0: auto recovery off, 1: auto recovery on */
uint8_t test_on = 0; /* to enable test data pumping on(1)/off(0), default off */
uint8_t report_on = 0; /* to enable reporting on(1)/ off(0), default off */
uint8_t sleep_on = 0; /* to enable sleep mode on(1)/ off(0), default off */
uint8_t unicast_on = 1; /* whether to send unicast (1) or broadcast (0) msg, default off */
uint8_t loop_on = 1; /* to enable loopback check on(1)/ off(0), default on */

uint8_t uart_on = 1; /* to enable UART connection on(1)/off(0), default on */
uint16_t broadcast_collecting_time = 500; /* collecting time for broadcast packet (ms)*/
uint16_t broadcast_collecting_time_addressing = 10; /* collecting time for broadcast packet (ms)*/

uint8_t loopback_retry_max = 1;
uint16_t loopback_timeout_ms = 500;
uint16_t loopback_timeout_ms_ap = 100;

uint16_t uart_if_check = 1; /* uart interface check */
uint8_t uart_normal_start = 0; /* to check uart interface is normal normal(1) / abnormal(0), default abnormal */

static uint8_t iperf_on = 1; /* to enable iperf function on(1)/off(0), default on */
static uint8_t relay_signal = 0; /* to enable snr/rssi in relay on(1)/ off(0) */
static uint8_t home_mode = 0; /* to enable home mode (AP - 4 STA) */
static uint32_t idle_timeout = IDLE_TIMEOUT_TO_PS; /* UART input idle timeout before sleep mode (unit:ms)*/


void handle_wakeup_reason(nvs_handle_t nvs_handle)
{
	uint8_t boot;
	if (nrc_ps_wakeup_reason(&boot) == NRC_FAIL) {
		app_log(DEBUG_LEVEL_ALWAYS, NULL, "[%s] Boot reason retrieval failed.\n", __func__);
		return;
	}

	switch(boot) {
		case NRC_WAKEUP_REASON_COLDBOOT:
			app_log(DEBUG_LEVEL_ALWAYS, NULL, "** [%s] COLDBOOT\n", __func__);
#ifdef SUPPORT_EPAPER
//			if (!nrc_wifi_get_recovered_by_fast_connect(0) &&
//				!nrc_wifi_get_recovered_by_fast_connect(1))
				update_home_mode_display(nvs_handle);
#endif
			break;
		case NRC_WAKEUP_REASON_RTC:
			app_log(DEBUG_LEVEL_ALWAYS, NULL, "** [%s] Awaken for RTC **\n", __func__);
			break;
		case NRC_WAKEUP_REASON_TIM:
			app_log(DEBUG_LEVEL_ALWAYS, NULL, "** [%s] Awaken for data received **\n", __func__);
			break;
		case NRC_WAKEUP_REASON_GPIO:
			app_log(DEBUG_LEVEL_ALWAYS, NULL, "[%s] ** Awaken by GPIO **\n", __func__);
			break;
		case NRC_WAKEUP_REASON_TIM_TIMER:
			app_log(DEBUG_LEVEL_ALWAYS, NULL, "** [%s] TIM TIMER **\n", __func__);
			break;
		default:
			app_log(DEBUG_LEVEL_ALWAYS, NULL, "** [%s] WAKEUP REASON NOT_SUPPORTED.\n", __func__);
	}
}

void user_init(void)
{
	system_role_t role = ROLE_UNDEFINED;

	system_time_reset();

	sample_smart_conn_set_app_version();

	nrc_uart_console_enable(true);
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "[ %s v%d.%d.%d ]\n", nrc_get_app_name(),
		SAMPLE_SMART_CONN_MAJOR, SAMPLE_SMART_CONN_MINOR, SAMPLE_SMART_CONN_PATCH);

	start_link_status_update();

#ifdef SUPPORT_LFS
	if (lfs_port_init() != 0) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "LittleFS init failed\n");
		return;
	}
#endif

	/* Open NVS handle to read configuration data */
	if (nvs_open(NVS_DEFAULT_NAMESPACE, NVS_READWRITE, &nvs_handle) != NVS_OK) {;
		app_log(DEBUG_LEVEL_ERROR, NULL, "Make sure NVS is enabled.\n");
		return;
	}

	nvs_get_u8(nvs_handle, "max_device", &max_addressed_devices);
	nvs_get_u8(nvs_handle, "debug_level", &g_debug_level);
	nvs_get_u8(nvs_handle, "recovery_on", &recovery_on);
	nvs_get_u8(nvs_handle, "loop_on", &loop_on);
	nvs_get_u8(nvs_handle, "test_on", &test_on);
	nvs_get_u8(nvs_handle, "uart_on", &uart_on);
	nvs_get_u8(nvs_handle, "iperf_on", &iperf_on);
	nvs_get_u8(nvs_handle, "unicast_on", &unicast_on);
	nvs_get_u8(nvs_handle, "hex_mode", &g_hex_mode);
	nvs_get_u8(nvs_handle, "loop_retry", &loopback_retry_max);
	nvs_get_u16(nvs_handle, "loop_timeout", &loopback_timeout_ms);
	nvs_get_u16(nvs_handle, "loop_timeout_ap", &loopback_timeout_ms_ap);
	nvs_get_u16(nvs_handle, "bc_collect", &broadcast_collecting_time);
	nvs_get_u16(nvs_handle, "bc_collect_addr", &broadcast_collecting_time_addressing);
	nvs_get_u16(nvs_handle, "uart_if_check", &uart_if_check);

#if defined(DISABLE_AUTO_RECOVERY)
	recovery_on = 0;
#endif
#if defined(DISABLE_UART_LOOPBACK)
	loop_on = 0;
#endif
#if defined(FEATURE_EXTENDER)
	uart_if_check = 0;
#endif

	set_debug_level(g_debug_level);

	/*
	 * Feature/runtime overrides (compile-time gate + NVS override).
	 * Must be initialized early so other modules can consume current values.
	 */
	app_feature_cfg_init(nvs_handle);

	handle_wakeup_reason(nvs_handle);
	multi_role_config_init(nvs_handle);
	role = get_system_role(nvs_handle);

	/* Start softap, station or relay depends on the system setting. */
	if (multi_role_system_init(nvs_handle) == NRC_FAIL) {
		nvs_close(nvs_handle);
		return;
	}

	/* station status check */
	init_status_check(role);
/*
	if (!wifi_is_provisioned()) {
		switch (role) {
		case ROLE_SOFTAP:
#ifndef TEST_LFS_SMARTCONN
			xTaskCreate(ap_config_msg_task, "ap config msg", 1024, NULL, USER_APP_TASK_PRIORITY, NULL);
			break;
#endif
		case ROLE_RELAY:
		case ROLE_STATION:
			xTaskCreate(sta_config_msg_task, "sta config msg", 1024, NULL, USER_APP_TASK_PRIORITY, NULL);
			break;
		default:
			break;
		}
	} else {
		if (role == ROLE_RELAY || role == ROLE_STATION) {
			// Need to handle factory reset message
			xTaskCreate(sta_config_msg_task, "sta config msg", 1024, NULL, USER_APP_TASK_PRIORITY, NULL);
		}
	}
*/
#ifdef BCMC_COLLISION_AWARE_ENABLE
	/* Update Minimum contention window size (CWMin)  */
	uint16_t  cw_min = 1023;
	nvs_get_u16(nvs_handle, "cw_min", (uint16_t *) &cw_min);
	nrc_wifi_set_bcmc_collision_aware(true, cw_min);
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "cw_min : %d\n", cw_min);
#endif /* BCMC_COLLISION_AWARE_ENABLE */

#ifdef IDLE_POWER_SAVE_ENABLE
	nvs_get_u8(nvs_handle, "sleep_on", &sleep_on);
	if (role == ROLE_STATION && sleep_on) {
		nvs_get_u32(nvs_handle, "idle_timeout", (uint32_t *) &idle_timeout);
		init_idle_timer(idle_timeout);
		start_idle_timer();
	}
#endif

#ifdef SUPPORT_BCAST_FOTA
	/* Must initialize at the end, so that the wifi connection is ready. */
	init_broadcast_fota();
#endif // SUPPORT_BCAST_FOTA

#ifdef SUPPORT_TCP_CLI
	tcp_cli_init();
#endif /* SUPPORT_TCP_CLI */

	if (iperf_on) {
		start_iperf_server();
	}

	device_ready(role);

#ifdef SUPPORT_TCP_FOTA
	if (app_feature_tfota_enabled()) {
		if (role == ROLE_SOFTAP) {
			start_directory_server(role);
		}

		/*
		 * Only roles that *receive* firmware need the TCP FOTA server.
		 * The SOFTAP node is the TFOTA client (pusher), so skip the server there.
		 */
		if (role != ROLE_SOFTAP) {
			start_tfota_server();
		}
	} else {
		app_log(DEBUG_LEVEL_ALWAYS, NULL, "[FEATURE] tfota_on=0, skipping TCP FOTA start\n");
	}
#endif

#ifdef ENABLE_TASK_KEEPALIVE
	// if (wifi_is_provisioned()) 
	{
		switch (role) {
			case ROLE_SOFTAP:
				start_keepalive_server_task();
				break;
			case ROLE_RELAY:
			case ROLE_STATION:
#ifndef FEATURE_EXTENDER
				start_keepalive_task();
#endif
				break;
			default:
				break;
		}
	}
#endif

#if defined(TEST_PACKET_COUNT)
	packet_count_init();
#endif
}
