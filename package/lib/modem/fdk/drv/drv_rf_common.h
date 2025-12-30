#ifndef __DRV_RF_H__
#define __DRV_RF_H__

#include "system.h"
#include "drv_rf.h"

#if !defined(EXCLUDE_FDK_MAC)
#include "drv_mac_common.h"
#endif

#if defined(MFGT)
#define DBG_NON_MFGT
#else
#define DBG_NON_MFGT DBG
#endif

#define DOC_CODE_NUM    32
typedef enum {
    CAL_TX_LO,
    CAL_TX_IQ,
    CAL_RX_IMG,
    CAL_DONE
} cal_mode_t;

typedef struct {
    uint32_t 	rf_pll_freq;
#if defined(NRC5291) || defined(NRC5292) || defined(NRC5293)
	uint32_t 	sbr_pll_freq;
#endif
    uint32_t 	doc_code[DOC_CODE_NUM];
    bw_t     	rf_rx_filter_bw , rf_tx_filter_bw;
    uint8_t  	rf_pll_init_trim_code;
	bool		valid;
} drv_rf_info_t;
extern drv_rf_info_t* drv_rf_info;

// RF API /////////////////////////////////////////////
void drv_rf_init(bool recovery);
void drv_rf_set_bw(bw_t bw);
void drv_rf_cal_init(bool recovery);
void drv_rf_adjust_pll_reg8(bw_t bw);
void drv_rf_set_frequency(uint32_t freq);
uint32_t drv_rf_get_frequency();
void drv_rf_set_rx_filter(bw_t bw);
void drv_rf_set_tx_filter(bw_t bw);
void drv_rf_loopback_rx_mode(bool enable);
void drv_rf_loopback_tx_mode(bool enable);
uint8_t drv_rf_get_txcal_tlpf_gac(void);
uint8_t drv_rf_get_txcal_tx_lo_tlpf(void);
void drv_rf_set_txcal_tlpf_gac(uint8_t value);
void drv_rf_cfo_ppm(double cfo_ppm);
void drv_rf_show();
////////////////////////////////////////////////////////

// __WEAK //////
void drv_rf_set_sbr_frequency(uint32_t freq);
void drv_rf_sbrmode(bool);
void drv_rf_sbr_pll_cal();
void drv_rf_set_boosting(uint8_t tmx_gmrc);
void drv_rf_cal_rf_setting(cal_mode_t mode);
////////////////

void drv_rf_tx_lpf_cal();
void drv_rf_rx_lpf_cal();
void drv_rf_dcoc_cal(bool recovery);
void drv_rf_reg_init(bool recovery);

bool drv_rf_singen_on(int8_t freq_100khz);
void drv_rf_singen_off();

void rf_delay_us(uint32_t us);
void drv_rf_trx_cal(cal_mode_t mode , bool dac_swap , int32_t *param0 , int32_t *param1 , bool debug);
void drv_rf_set_cal_param(cal_mode_t mode , int32_t param0 , int32_t param1);
void drv_rf_get_cal_param(cal_mode_t mode , int32_t *param0 , int32_t *param1);
void drv_rf_cal_phy_setting(cal_mode_t mode , bool dac_swap);
uint64_t drv_rf_cal_measure_point(cal_mode_t mode , int32_t param0 , int32_t param1 , uint32_t loop);

#define CHECK_FLAG_TIMEOUT(FLAG , TIMEOUT_US)  \
	{\
		uint32_t now = NOW;\
		volatile bool result = true;\
		while(!(result = FLAG) && (NOW - now) < TIMEOUT_US );\
		if(result) break;\
	}

#define CHECK_FLAG(FLAG) while(!FLAG);

/*
#define WRITE_REG_BEGIN(BLOCK,REG) {\
			BLOCK ##_ REG reg = BLOCK->REG.b;\
			BLOCK ##_ REG *addr = &BLOCK->REG.w;
#define WRITE_REG_END() *addr = reg; }
*/


#endif// __DRV_RF_H__
