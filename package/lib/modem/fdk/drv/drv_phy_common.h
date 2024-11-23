#ifndef __DRV_PHY_COMMON_H__
#define __DRV_PHY_COMMON_H__
#include "system.h"
#if defined(NRC7292RFE)
#include "drv_trx_gain_table_nrc7292rfe.h"
#else
#include "drv_trx_gain_table.h"
#endif
#include "drv_phy.h"

#if defined(NRC7394)
    #define PHY_SINGEN_RF_CTL_CONFIG 0xdd
#else
    #define PHY_SINGEN_RF_CTL_CONFIG 0x6d
#endif

typedef struct {
	uint16_t rxgain;
} drv_phy_info_t;

extern drv_phy_info_t *drv_phy_info;
#if defined(UCODE)
void drv_phy_reg_init_ucode();
#endif
void drv_phy_init();
void drv_phy_reg_init();
void drv_phy_set_op_bw(bw_t bw);
bw_t  drv_phy_get_op_bw();
void drv_phy_set_prim_1m_loc(uint8_t loc);
uint8_t drv_phy_get_prim_1m_loc();
void drv_phy_set_rx_initial_gain(uint8_t rxgain);
void drv_phy_set_tx_gain(uint8_t txgain);
void drv_phy_set_dig_lpf_gain(uint16_t lpf_gain);
void drv_phy_enable();
void drv_phy_disable();
void drv_phy_rx_rst();
void drv_phy_set_cfo2sfo(uint32_t freq , bw_t bw);

bool drv_phy_singen_on(uint8_t freq_100khz);
void drv_phy_singen_off();

void drv_phy_get_current_snr( uint32_t *snr0 , uint32_t *snr1 , uint32_t *snr2 , uint32_t *snr3 , uint32_t *signal , uint32_t *noise);
double drv_phy_vector_cfo_to_ppm(uint32_t vector_cfo);

void drv_phy_set_rxcal_param(uint32_t param0 , uint32_t param1);

void drv_phy_show(bool rst);

void drv_phy_rxgain_lut_write();
void drv_phy_rxgain_lut_write_sunmi();
void drv_phy_txgain_lut_write();
void drv_phy_rxgain_sbr_lut_write();

uint8_t drv_phy_get_rx_initial_gain();

typedef enum {
	TXGAIN_FIXED = 0,
	TXGAIN_AUTO = 1
} txgain_mode_t;

#define CHECK_FLAG_TIMEOUT(FLAG , TIMEOUT_US)  \
	{\
		uint32_t now = NOW;\
		volatile bool result = true;\
		while(!(result = FLAG) && (NOW - now) < TIMEOUT_US );\
		if(result) break;\
	}

#define CHECK_FLAG(FLAG) while(!FLAG);


#define WRITE_REG_BEGIN(BLOCK,REG) {\
			BLOCK ##_ REG reg = BLOCK->REG.b;\
			BLOCK ##_ REG *addr = &BLOCK->REG.w;
#define WRITE_REG_END() *addr = reg; }

#endif// __DRV_PHY_COMMON_H__
