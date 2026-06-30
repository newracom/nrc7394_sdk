#ifndef __APP_FEATURE_CFG_H__
#define __APP_FEATURE_CFG_H__

#include <stdint.h>
#include <stdbool.h>

#include "nvs.h"

/*
 * Runtime Feature Configuration (compile-time + NVS override)
 *
 * "Feature" in this app means:
 *  - Compile-time switch that enables the runtime-config logic.
 *  - If enabled, values in NVS (if present) override the defaults.
 *
 * Keys (NVS_DEFAULT_NAMESPACE):
 *   feat_cfg_on        (u8)   : 0/1, master switch for applying overrides (default: 1)
 *   tfota_on            (u8)   : 0/1, runtime enable TCP FOTA behaviors (default: 1)
 *   tfota_root_ip       (str)  : dotted IPv4 for Root FOTA server (default: NRC_SOFTAP_IP)
 *   tfota_ctrl_port     (u16)  : directory/control UDP/TCP port (default: NRC_FOTA_CTRL_PORT)
 *   tfota_data_port     (u16)  : firmware transfer TCP port (default: NRC_FOTA_DATA_PORT)
 *
 *   Directory / REGISTER / HEARTBEAT timing ("periodic reporting" in your request):
 *   dir_refresh_ms      (u32)  : re-REGISTER interval (ms) (default: 30000)
 *   dir_hb_ms           (u32)  : HEARTBEAT interval before provisioned (ms) (default: 2000)
 *   dir_hb_ms_pr        (u32)  : HEARTBEAT interval after provisioned (ms)  (default: 15000)
 *   dir_off_ms          (u32)  : Root offline timeout before provisioned (ms) (default: 10000)
 *   dir_off_ms_pr       (u32)  : Root offline timeout after provisioned (ms)  (default: 60000)
 *
 * Notes:
 *  - If feat_cfg_on == 0, all overrides are ignored.
 */

/* Compile-time gate (set -DFEATURE_RUNTIME_CFG=0 to disable). */
#ifndef FEATURE_RUNTIME_CFG
#define FEATURE_RUNTIME_CFG 1
#endif

void app_feature_cfg_init(nvs_handle_t h);

bool app_feature_overrides_enabled(void);
bool app_feature_tfota_enabled(void);

/* TFOTA "server" here means the Root directory server (IP/port). */
uint32_t app_tfota_root_ip_nbo(void);
uint16_t app_tfota_ctrl_port(void);
uint16_t app_tfota_data_port(void);

/* Directory timing (REGISTER / HEARTBEAT / offline detection) */
uint32_t app_dir_refresh_ms(void);
uint32_t app_dir_hb_ms_unprov(void);
uint32_t app_dir_hb_ms_prov(void);
uint32_t app_dir_offline_ms_unprov(void);
uint32_t app_dir_offline_ms_prov(void);

/* For logging/diagnostics */
void app_feature_cfg_dump(void);

#endif /* __APP_FEATURE_CFG_H__ */
