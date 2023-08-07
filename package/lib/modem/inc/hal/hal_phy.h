#ifndef __NRC_PHY_H__
#define __NRC_PHY_H__

/* CCA Threshold init : -75 dBm */
//#define CCA_THRESHOLD_REG2_INIT_VALUE	0x0000b5b8
//#define CCA_THRESHOLD_REG3_INIT_VALUE	0xb5b5b8b8

/* 10212021 CCA-ED Threshold : - 85dBm regardless of BW */
/* CCA-ED: -85dBm */
#define CCA_THRESHOLD_REG2_KR_VALUE	0x0000abab
#define CCA_THRESHOLD_REG3_KR_VALUE	0xabababab

void hal_phy_init();
void phy_op_bw(uint32_t bw);
void phy_set_primary_1m_loc(uint8_t loc);
void phy_nrf_txgain_control(uint32_t nrf_txgain);
uint32_t phy_get_txgain();
void phy_nrf_rxgain_control(uint32_t nrf_rxgain);
uint32_t phy_get_rxgain();
void phy_nrf_txgain_lut_write(uint32_t ram_type);
void phy_nrf_rxgain_lut_write(uint32_t ram_type);

/* TBD no functions */
void phy_set_cfo2sfo_factor(uint32_t channel_freq, uint32_t op_mode);

#if defined(INCLUDE_PHY_DEBUG)
void mdelay(uint32_t delay);
void phy_state_print();
void phy_dfe_status_counter();
void phy_dfe_status_counter_rst();
void phy_enable();
void phy_disable();
void phy_sw_reset();
void phy_romgen_enable(uint32_t format, uint32_t count);
void phy_romgen_disable();
void phy_adc_iq_swap();
void phy_dac_iq_swap();
void phy_adc_iq_noswap();
void phy_dac_iq_noswap();
void phy_adc_twos();
void phy_dac_twos();
void phy_configure_txfifo_af_lvl(uint32_t txfifo_af_level);
void phy_configure_bssid(uint32_t bssid_0, uint32_t bssid_1, uint32_t bssid_2, uint32_t bssid_3, uint32_t bssid_4);
void phy_ignore_bssid_check();
void phy_ignore_ul_ind_bit_check();
void phy_enable_ul_ind_bit_check();
void phy_ignore_rsrvd_bit_check();
void phy_enable_rsrvd_bit_check();
void phy_rfloiq_cal(uint32_t cal_mode, uint32_t cal_range, uint32_t cal_step, uint32_t cal_search);
void phy_loiqcal_settings(uint32_t cal_mode);
void phy_rfloiq_calparam_search(uint32_t cal_mode, uint32_t cal_range, uint32_t cal_step, uint32_t cal_search);
void hal_phy_set_bssid(bool enable, int index, int value);
void phy_nrf_singen_on(uint32_t freq);
void phy_nrf_singen_off();
#endif /* INCLUDE_PHY_DEBUG */

#endif //__NRC_PHY_H__
