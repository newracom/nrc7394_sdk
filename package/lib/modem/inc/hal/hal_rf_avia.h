#ifndef __NRC_RF_AVIA_H__
#define __NRC_RF_AVIA_H__

#define SIZE_OF_TX_PWR_TBL      64
#define SIZE_OF_FREQ_DELTA_TBL  64

#define RegLPF_GAIN (*((volatile uint32_t *)(0x4008A018)))

typedef struct {
	uint8_t valid;
	uint8_t nv_version;
    uint8_t country[2]; /* two ASCII characters */
    /*
     * phy txgain index from 1 to 30.
     * the values of the array were multiplied by 100 to avoid the usage of float type.
     */
    int16_t tx_pwr_tbl[SIZE_OF_TX_PWR_TBL];
    /*
     * Delta power of center frequency table of 1Mhz bw for the configured conuntry code.
     * the values of the array were multiplied by 100 to avoid the usage of float type.
     */
    int16_t freq_delta_tbl[SIZE_OF_FREQ_DELTA_TBL];
} TX_PWR_CAL_PARAM;

void hal_rf_init();
void nrf_reg_init();
void rf_init_dump();
bool nrf_channel_test(uint32_t channel_freq);
bool nrf_channel(uint32_t channel_freq);
bool nrf_channel_idx(uint8_t ch_index);
bool nrf_channel_fine(uint32_t channel_freq);
void nrf_filter_bw(uint32_t bw);
void nrf_self_trx_cal();
void nrf_self_rxdc_cal();
void nrf_self_txlo_cal();
void nrf_spi_write(uint32_t addr, uint32_t wdata);
void nrf_pms_spi_write(uint32_t addr, uint32_t wdata);
uint32_t nrf_channel_freq_find(uint32_t ch_idx);
uint32_t nrf_spi_read(uint32_t addr);
uint32_t nrf_pms_spi_read(uint32_t addr);
uint32_t nrf_pll_lock_flag();
void nrf_loiqcal_loopback(uint32_t cal_mode);
void nrf_cfo_cal(double cfo_ppm, uint32_t *cfo_reg);
void nrf_reg_ram_lut_wr(uint32_t cmd_num);
void nrf_rffe_config(uint8_t rffe);
void nrf_dcoc_config(uint8_t mode);

void init_sfi();
void load_cal_info();
void store_cal_info();
void clear_cal_info();
void update_cal_info_valid(uint8_t valid);
void update_cal_info_nv_version(uint8_t version);
void update_cal_info_tx_pwr_cal(uint8_t index, int8_t value);
void update_cal_info_rx_rssi_cal(uint8_t index, int8_t value);
void show_cal_info();
void hal_rf_pll_frequency(uint32_t channel_freq );
uint8_t hal_rf_set_txpwr(uint8_t txpwr);
uint8_t     hal_rf_get_txpwr(void);
uint8_t hal_rf_set_txpwr(uint8_t txpwr);
#endif// __NRC_RF_AVIA_H__
