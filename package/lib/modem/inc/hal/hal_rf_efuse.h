#ifndef __NRC_RF_EFUSE_H__
#define __NRC_RF_EFUSE_H__
#include "hal_efuse.h"

#if !defined(NRC7394)
void __csp_efuse_Initialize(void);
st_efuse_t* __csp_efuse_get_data();
void hal_modem_find_txpwr_optimal_gains(int16_t txpwr, uint8_t *optimal_txgain, uint16_t *optimal_dig_lpf_gain);
uint8_t hal_rf_convert_txpwr(uint8_t txpwr, uint16_t *lpf_gain);
void temp_sensor_init();
#endif


#if 0
bool hal_rf_efuse_process();
int hal_rf_efuse_get_version();
bool hal_rf_efuse_get_pllldo12_tr(uint32_t *value);
int hal_rf_efuse_get_version();
#endif
#endif// __NRC_RF_EFUSE_H__
