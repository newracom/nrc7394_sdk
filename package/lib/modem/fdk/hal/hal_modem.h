#ifndef __NRC_MODEM_H__
#define __NRC_MODEM_H__

#undef MAX_MCS

#if !defined(EXCLUDE_FDK_MAC)
#include "drv_mac_common.h"
#include "drv_efuse.h"
#include "drv_pmsspi.h"
#define MAX_MCS 10
#else
#include "hal_efuse.h"
#include "hal_pmsspi.h"
#include "system_efuse.h"
#include "system_pmsspi.h"
#define MAX_MCS 11
#endif

#include "drv_phy_common.h"

#if defined(NRC7292RFE)
#include "drv_rf_nrc7292rfe.h"
#define drv_rf_set_boosting(A)
#define drv_rf_singen_off()
#define drv_rf_singen_on(A) 1
#else
#include "drv_rf_common.h"
#endif


typedef enum {
    MCS0,MCS1,MCS2,MCS3,MCS4,MCS5,MCS6,MCS7,MCS8,MCS9,MCS10
} mcs_t;

typedef enum {
    FIXED   = 0,
    AUTO    = 1 
} txpower_mode_t;

typedef enum {
    TX = 0,
    RX = 1
} switch_direction_t;

typedef struct {
    uint8_t txgain_index;
    uint8_t digital_gain;
} txpower_value_t;

typedef struct {
    txpower_mode_t mode;
    txpower_value_t fixed_txpower;
    txpower_value_t auto_txpower[MAX_MCS];
    int16_t temp_power_offset;
} hal_modem_txpower_t;

typedef struct {
    // prim_position : 0 (lower) , 1(upper)
    int32_t txiq_param0 , txiq_param1;
    int32_t txlo_param0 , txlo_param1;
    int32_t rximg_param0 , rximg_param1;
    bool    txiq_cal_valid;
    double cfo_ppm;
    uint32_t freq;
    bw_t bw;
    uint8_t prim_1m_loc;
    hal_modem_txpower_t txpower;
    uint8_t rxgain;
    uint8_t txgain;
} hal_modem_info_t;

typedef struct {
    hal_modem_info_t    hal_modem_info;
    drv_rf_info_t       drv_rf_info;
    drv_phy_info_t      drv_phy_info;
#if !defined(EXCLUDE_FDK_MAC)
    drv_mac_info_t      drv_mac_info;
#endif
	st_efuse_t          drv_efuse_info;
} hal_modem_ret_info_t;

// HAL API
#if defined(UCODE)
void            hal_modem_init_ucode();
#endif
void            hal_modem_init(bool recovery);
void            hal_modem_restore_default_rf_cal_hw_values();
void            hal_modem_show();
void            hal_modem_set_freq_bw_prim(uint32_t freq , bw_t bw , uint8_t loc);

#if !defined(EXCLUDE_FDK_MAC)
send_result_t   hal_modem_send_buffer(uint8_t *buffer , uint32_t size , ac_t ac , bool sync_flag);
#endif
uint16_t        hal_modem_convert_auxadc_raw_to_mv(uint32_t a_raw);
uint8_t         hal_modem_get_compensated_rxgain(uint8_t rxgain);
void            hal_modem_apply_rf_cal_data();
int16_t         hal_modem_temp_sensor_get_temp_celcius(void);
int16_t         hal_modem_temp_sensor_get_power_offset(bool recovery);
void            hal_modem_find_txpwr_optimal_gains(int16_t txpwr, uint8_t *optimal_txgain, uint16_t *optimal_dig_lpf_gain , bool doppler, int16_t temp_power_offset);
#if !defined(EXCLUDE_FDK_MAC)
uint8_t hal_modem_set_txpwr(int16_t txpwr);
#else
uint8_t hal_modem_set_txpwr(int16_t txpwr, int16_t temp_power_offset);
#endif

void            hal_modem_set_rxgain(uint8_t rxgain, bool recovery);
void            hal_modem_cfo_ppm(double cfo_ppm);
hal_modem_ret_info_t*   hal_modem_get_ret_info();

// Local Function
static void modem_info_init();
static void modem_trx_cal();
static void modem_adjust_modem_param();
static void modem_apply_rf_cal_data();
static void modem_system_init();
static void modem_retention_init();
static void modem_recover_modem_param();
static void modem_set_txiq_cal_param();
static void modem_efuse_init();
static void modem_temp_sensor_init();
#endif// __NRC_RF_H__
