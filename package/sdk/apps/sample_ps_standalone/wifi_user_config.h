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

#define NRC_WIFI_LISTEN_INTERVAL_DEFAULT 1000

/*
 * Power-save mode used by this sample.
 *   0: NON-TIM deep sleep. Wake by RTC/GPIO after the configured sleep time.
 *   1: TIM deep sleep. Wake for AP TIM indication, or by optional timeout.
 *
 * These defaults can still be overridden from NVS using:
 *   nvs set_u8 ps_mode <0|1>
 *   nvs set_u32 ps_sleep <sleep_ms>
 */
#define NRC_WIFI_PS_MODE_DEFAULT 1

#if (NRC_WIFI_PS_MODE_DEFAULT == 1)
/*
 * TIM mode defaults:
 * - ps_idle is the idle time before entering dynamic power save.
 * - ps_sleep 0 means no user timeout; wake only for TIM traffic indication.
 */
#define NRC_WIFI_PS_IDLE_TIMEOUT_DEFAULT 100
#define NRC_WIFI_PS_SLEEP_TIME_DEFAULT 0
#else
/*
 * NON-TIM mode defaults:
 * - nrc_ps_deep_sleep() requires ps_sleep >= 1000 ms.
 * - Do not set ps_sleep to 0. The modem PS layer treats
 *   nontim_sleep_ms == 0 as TIM mode.
 */
#define NRC_WIFI_PS_IDLE_TIMEOUT_DEFAULT 100
#define NRC_WIFI_PS_SLEEP_TIME_DEFAULT 60000
#endif
#endif // __WIFI_USER_CONFIG_H__ //
