#include "nrc_sdk.h"
#include "nrc_lwip.h"
#include "wifi_config.h"
#include "multi_role_config.h"
#include "app_debug.h"

#ifdef IDLE_POWER_SAVE_ENABLE

#define WAKEUP_GPIO_PIN GPIO_13

static TimerHandle_t timeout_timer;

static bool wait_for_ip(void) {
	uint8_t retry_cnt = 0;
	struct netif *interface = nrc_netif_get_by_idx(WLAN0_INTERFACE);

	while (ip4_addr_isany(netif_ip4_addr(interface))) {
		_delay_ms(200);

		if (++retry_cnt > 200) {
			app_log(DEBUG_LEVEL_ALWAYS, NULL, "[%s] Exceeded retry limit (200), entering deep sleep for 5000ms.\n", __func__);
			nrc_ps_sleep_alone(5000);
			retry_cnt = 0;
		}
	}
	_delay_ms(1000);
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "IP address : %s\n", ip4addr_ntoa(netif_ip4_addr(interface)));
	return true;
}

static bool _ready_ip_address(void)
{
	if (nrc_addr_get_state(0) == NET_ADDR_SET &&
		nrc_wifi_get_state(0) == WIFI_STATE_CONNECTED) {
		return true;
	} else {
		return false;
	}
}

static void run_power_save(void)
{
	uint32_t wakeup_source = 0;
	WIFI_CONFIG *param = get_system_config();
	uint32_t gpio_direction = 0xFFF7FDC7;

	uint8_t ps_mode = param->ps_mode;
	uint32_t ps_idle_timeout_ms = param->ps_idle;
	uint32_t ps_sleep_time_ms = param->ps_sleep;

check_again:
	if(wait_for_ip() == false){
		nrc_ps_sleep_alone(5000);
	}

#if defined(WAKEUP_GPIO_PIN)
	gpio_direction &= ~(1 << WAKEUP_GPIO_PIN);
	nrc_ps_set_gpio_wakeup_pin(false, WAKEUP_GPIO_PIN, false);
	wakeup_source |= WAKEUP_SOURCE_GPIO;
#endif /* defined(WAKEUP_GPIO_PIN) */

	wakeup_source |= WAKEUP_SOURCE_RTC;
	nrc_ps_set_wakeup_source(wakeup_source);

	app_log(DEBUG_LEVEL_ALWAYS, NULL, "ps gpio_direction: 0x%08X\n", gpio_direction);
	nrc_ps_set_gpio_direction(gpio_direction);
	nrc_ps_set_gpio_out(0x0);
	nrc_ps_set_gpio_pullup(0x0);

	app_log(DEBUG_LEVEL_ALWAYS, NULL, "[%s] ps_mode(%s) idle_time(%d ms) sleep_time(%u ms)\n",
		__func__, (ps_mode == 1) ? "TIM" : "NON-TIM", ps_idle_timeout_ms, ps_sleep_time_ms);

	while (1) {
		if(ps_mode){
			if (nrc_ps_wifi_tim_deep_sleep(ps_idle_timeout_ms, ps_sleep_time_ms) == NRC_SUCCESS) {
				if (_ready_ip_address()) {
					app_log(DEBUG_LEVEL_ALWAYS, NULL, "[%s] IP is ready\n",__func__);
					break;
				}
			} else {
				app_log(DEBUG_LEVEL_ALWAYS, NULL, "[%s] fail to set sleep (wifi_state:%d, ip_state:%d)\n",
					__func__, nrc_wifi_get_state(0), nrc_addr_get_state(0));
				goto check_again;
			}
		} else {
			//bypass timing constraints (listen interval and/or bss max idle)
			nrc_ps_bypass_constraints(true);
			if (nrc_ps_deep_sleep(ps_sleep_time_ms) == NRC_SUCCESS) {
				if (_ready_ip_address()) {
					app_log(DEBUG_LEVEL_ALWAYS, NULL, "[%s] IP is ready\n",__func__);
					break;
				}
			} else {
				app_log(DEBUG_LEVEL_ALWAYS, NULL, "[%s] fail to set sleep (wifi_state:%d, ip_state:%d)\n",
					__func__, nrc_wifi_get_state(0), nrc_addr_get_state(0));
				goto check_again;
			}
		}
	}

	_delay_ms(1000);
	if(wait_for_ip() == false){
		nrc_ps_sleep_alone(5000);
	}
}

static void idle_timeout_callback(TimerHandle_t xTimer)
{
	run_power_save();
}

void reset_idle_timer(void)
{
	if (xTimerReset(timeout_timer, 0) != pdPASS) {
		app_log(DEBUG_LEVEL_ALWAYS, NULL, "[ERROR] Failed to reset timer!\n");
	}
	//app_log(DEBUG_LEVEL_ALWAYS, NULL, "reset_idle_timer\n");
}

void init_idle_timer(uint32_t idle_timeout)
{
	timeout_timer = xTimerCreate("TimeoutTimer", idle_timeout, pdFALSE, NULL, idle_timeout_callback);
	if (timeout_timer == NULL) {
		app_log(DEBUG_LEVEL_ALWAYS, NULL, "[ERROR] Failed to create timer!\n");
	}
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "init_idle_timer %d ms\n", idle_timeout);
}

void start_idle_timer(void)
{
	xTimerStart(timeout_timer, 0);
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "start_idle_timer\n");
}

#endif /* IDLE_POWER_SAVE_ENABLE */
