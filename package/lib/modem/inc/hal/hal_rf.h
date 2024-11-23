#ifndef __NRC_RF_H__
#define __NRC_RF_H__

#define SIZE_OF_TX_PWR_TBL	64
#define SIZE_OF_FREQ_DELTA_TBL	64
#define TX_POWER_MIN		0
#define TX_POWER_MAX		63

#define RegLPF_GAIN (*((volatile uint32_t *)(0x4008A018)))
#define RF_REG_BASE_START 0x4004F000
#define RF_REG_SIZE 4
#define PMS_REG_MAX 0x0b
#define RF_REG_PLL_DCXO 0x0A
#define RF_REG_MAX 0x7F

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

void rf_init_dump(void);

void nrf_reg_init(void);
void nrf_filter_bw(uint32_t bw);
void nrf_pms_spi_write(uint32_t addr, uint32_t wdata);
uint32_t nrf_pms_spi_read(uint32_t addr);
void nrf_spi_write(uint32_t addr, uint32_t wdata);
uint32_t nrf_spi_read(uint32_t addr);
void nrf_cfo_cal(double cfo_ppm, uint32_t *cfo_reg);

void hal_rf_pll_frequency(uint32_t channel_freq);
void hal_rf_update_txpwr(void);
uint8_t hal_rf_set_txpwr(uint8_t txpwr);
uint8_t hal_rf_get_txpwr(void);
uint8_t hal_rf_recover_txpwr(uint8_t txpwr);

#if defined(INCLUDE_RF_DEBUG)
//TBD will be removed

// RF PMS Register Address
#define PMS_REG_BGR_LDO 0x00
#define PMS_REG_IBIAS 0x01
#define PMS_REG_VSLREF 0x02
#define PMS_REG_SLLDO 0x03
#define PMS_REG_BUCK_CLK 0x04
#define PMS_REG_VBUCK 0x05
#define PMS_REG_TP_ENSL_LPOCAL 0x06
#define PMS_REG_TP_LPO16M_TSTEN 0x07
#define PMS_REG_TP_IBIAS_VREF 0x08
#define PMS_REG_TP_FLAG_SSPWM 0x09
#define PMS_REG_TP_FLAG_LPOCLK 0x0a
#define PMS_REG_TP_PWM_SLDUTY 0x0b

// RF Register Address
#define RF_REG_AFE_CLK_INVERSE 0x00
#define RF_REG_RXRF_BWC_TP_SWC 0x01
#define RF_REG_LNA_LDO_IBC 0x02
#define RF_REG_RX_GAC_BWC 0x03
#define RF_REG_RXLPF_BWC 0x04
#define RF_REG_TX_GAC 0x05
#define RF_REG_TX_IBC 0x06
#define RF_REG_TXRF_BWC 0x07
#define RF_REG_TX_CAP_MSB_OFFSET 0x07 // NRC7292
#define RF_REG_PLL_TP 0x08
#define RF_REG_PLL_LDO 0x09

#define RF_REG_PLL_MMD_SDM 0x0B
#define RF_REG_PLL_SDM_JK 0x0C
#define RF_REG_PLL_SDM_L 0x0D
#define RF_REG_PLL_PFD_CP 0x0E
#define RF_REG_PLL_CP_IBLE 0x0F
#define RF_REG_PLL_LF_R2 0x10
#define RF_REG_XO_BG_CTRL_OFFSET 0x11
#define RF_REG_PLL_LF_C2C3C4 0x12
#define RF_REG_PLL_VCOTP 0x13
#define RF_REG_TSEN_VBATCHK 0x14
#define RF_REG_RF_LDO_BGR 0x15
#define RF_REG_RF_MONITOR 0x16
#define RF_REG_CAL_AFEMODE 0x17
#define RF_REG_CAL_READ_TXLPF 0x18
#define RF_REG_CAL_VCO 0x19
#define RF_REG_CAL_READ_VCO_TXLPF_ADC 0x1A
#define RF_REG_CAL_TXLPF_ENANA_BWC 0x1B
#define RF_REG_CAL_TXLPF_ENDIG 0x1C
#define RF_REG_CAL_ADC 0x1D
#define RF_REG_CAL_ADC_WI_11 0x1E
#define RF_REG_CAL_ADC_WI_10 0x1F
#define RF_REG_CAL_ADC_WI_09 0x20
#define RF_REG_CAL_ADC_WI_08 0x21
#define RF_REG_CAL_ADC_WI_07 0x22
#define RF_REG_CAL_ADC_WI_06 0x23
#define RF_REG_CAL_ADC_WI_05 0x24
#define RF_REG_CAL_ADC_WI_04 0x25
#define RF_REG_CAL_ADC_WI_03 0x26
#define RF_REG_CAL_ADC_WI_02 0x27
#define RF_REG_CAL_ADC_WI_01_00 0x28
#define RF_REG_CAL_ADC_WQ_11 0x29
#define RF_REG_CAL_ADC_WQ_10 0x2A
#define RF_REG_CAL_ADC_WQ_09 0x2B
#define RF_REG_CAL_ADC_WQ_08 0x2C
#define RF_REG_CAL_ADC_WQ_07 0x2D
#define RF_REG_CAL_ADC_WQ_06 0x2E
#define RF_REG_CAL_ADC_WQ_05 0x2F
#define RF_REG_CAL_ADC_WQ_04 0x30
#define RF_REG_CAL_ADC_WQ_03 0x31
#define RF_REG_CAL_ADC_WQ_02 0x32
#define RF_REG_CAL_ADC_WQ_01_00 0x33
#define RF_REG_CAL_ADC_PARAM 0x34
#define RF_REG_CAL_TX_LOIMG 0x35
#define RF_REG_CAL_TSSI 0x36
#define RF_REG_CAL_RXLPF 0x37
#define RF_REG_CAL_READ_RXLPF 0x38
#define RF_REG_CAL_DOC_PARAM 0x39
#define RF_REG_RXHP_PARAM 0x3A
#define RF_REG_CAL_DOC_SET 0x3B
#define RF_REG_DOC_TEST 0x3C
#define RF_REG_DOC_LUT_MANUAL 0x3D
#define RF_REG_CAL_READ_DOC 0x3E
#define RF_REG_CAL_RXIMG 0x3F
#define RF_REG_CAL_DOC_RXGAIN00 0x40
#define RF_REG_CAL_DOC_RXGAIN02 0x41
#define RF_REG_CAL_DOC_RXGAIN04 0x42
#define RF_REG_CAL_DOC_RXGAIN06 0x43
#define RF_REG_CAL_DOC_RXGAIN08 0x44
#define RF_REG_CAL_DOC_RXGAIN10 0x45
#define RF_REG_CAL_DOC_RXGAIN12 0x46
#define RF_REG_CAL_DOC_RXGAIN14 0x47
#define RF_REG_CAL_DOC_RXGAIN16 0x48
#define RF_REG_CAL_DOC_RXGAIN18 0x49
#define RF_REG_CAL_DOC_RXGAIN20 0x4A
#define RF_REG_CAL_DOC_RXGAIN22 0x4B
#define RF_REG_CAL_DOC_RXGAIN24 0x4C
#define RF_REG_CAL_DOC_RXGAIN26 0x4D
#define RF_REG_CAL_DOC_RXGAIN28 0x4E
#define RF_REG_CAL_DOC_RXGAIN30 0x4F
#define RF_REG_CAL_DOC_RXGAIN32 0x50
#define RF_REG_CAL_DOC_RXGAIN34 0x51
#define RF_REG_CAL_DOC_RXGAIN36 0x52
#define RF_REG_CAL_DOC_RXGAIN38 0x53
#define RF_REG_CAL_DOC_RXGAIN40 0x54
#define RF_REG_CAL_DOC_RXGAIN42 0x55
#define RF_REG_CAL_DOC_RXGAIN44 0x56
#define RF_REG_CAL_DOC_RXGAIN46 0x57
#define RF_REG_CAL_DOC_RXGAIN48 0x58
#define RF_REG_CAL_DOC_RXGAIN50 0x59
#define RF_REG_CAL_DOC_RXGAIN52 0x5A
#define RF_REG_CAL_DOC_RXGAIN54 0x5B
#define RF_REG_CAL_DOC_RXGAIN56 0x5C
#define RF_REG_CAL_DOC_RXGAIN58 0x5D
#define RF_REG_CAL_DOC_RXGAIN60 0x5E
#define RF_REG_CAL_DOC_RXGAIN62 0x5F
#define RF_REG_CAL_DOC_DACCODE00 0x60
#define RF_REG_CAL_DOC_DACCODE02 0x61
#define RF_REG_CAL_DOC_DACCODE04 0x62
#define RF_REG_CAL_DOC_DACCODE06 0x63
#define RF_REG_CAL_DOC_DACCODE08 0x64
#define RF_REG_CAL_DOC_DACCODE10 0x65
#define RF_REG_CAL_DOC_DACCODE12 0x66
#define RF_REG_CAL_DOC_DACCODE14 0x67
#define RF_REG_CAL_DOC_DACCODE16 0x68
#define RF_REG_CAL_DOC_DACCODE18 0x69
#define RF_REG_CAL_DOC_DACCODE20 0x6A
#define RF_REG_CAL_DOC_DACCODE22 0x6B
#define RF_REG_CAL_DOC_DACCODE24 0x6C
#define RF_REG_CAL_DOC_DACCODE26 0x6D
#define RF_REG_CAL_DOC_DACCODE28 0x6E
#define RF_REG_CAL_DOC_DACCODE30 0x6F
#define RF_REG_CAL_DOC_DACCODE32 0x70
#define RF_REG_CAL_DOC_DACCODE34 0x71
#define RF_REG_CAL_DOC_DACCODE36 0x72
#define RF_REG_CAL_DOC_DACCODE38 0x73
#define RF_REG_CAL_DOC_DACCODE40 0x74
#define RF_REG_CAL_DOC_DACCODE42 0x75
#define RF_REG_CAL_DOC_DACCODE44 0x76
#define RF_REG_CAL_DOC_DACCODE46 0x77
#define RF_REG_CAL_DOC_DACCODE48 0x78
#define RF_REG_CAL_DOC_DACCODE50 0x79
#define RF_REG_CAL_DOC_DACCODE52 0x7A
#define RF_REG_CAL_DOC_DACCODE54 0x7B
#define RF_REG_CAL_DOC_DACCODE56 0x7C
#define RF_REG_CAL_DOC_DACCODE58 0x7D
#define RF_REG_CAL_DOC_DACCODE60 0x7E
#define RF_REG_CAL_DOC_DACCODE62 0x7F

// HAL Functions
void hal_rf_init(void);
void hal_rf_pll_legacy_index(uint8_t index);
void hal_rf_pll_ch_index(uint8_t index);
void hal_rf_cal();
uint8_t* hal_rf_get_country(void);

// Cal Functions
bool nrf_tx_lpf_cal();
bool nrf_rx_lpf_cal();
bool nrf_dcoc_cal();
void nrf_self_trx_cal(uint8_t mode);
void nrf_loiqcal_loopback(uint32_t cal_mode);
void nrf_loopback_tx_mode(bool enable);
void nrf_loopback_rx_mode(bool enable);

// Internal Functions
void rf_init_dump_ucode(void);
bool nrf_channel_test(uint32_t channel_freq);
bool nrf_channel(uint32_t channel_freq);
bool nrf_channel_idx(uint8_t ch_index);
bool nrf_channel_fine(uint32_t channel_freq);
uint32_t nrf_channel_freq_find(uint32_t ch_idx);
uint8_t nrf_pll_lock_flag(void);
void nrf_loiqcal_loopback(uint32_t cal_mode);
void nrf_reg_ram_lut_wr(uint32_t cmd_num);
void nrf_rffe_config(uint8_t rffe);
void nrf_dcoc_config(uint8_t mode);

void load_cal_info(void);
void store_cal_info(void);
void clear_cal_info(void);
void update_cal_info_valid(uint8_t valid);
void update_cal_info_nv_version(uint8_t version);
void update_cal_info_tx_pwr_tbl(uint8_t index, int16_t value);
void update_cal_info_freq_pwr_delta_tbl(uint8_t index, int16_t value);
void update_cal_info_country(uint8_t* code);
void show_cal_info(void);
uint8_t hal_get_rf_cal_use(void);
TX_PWR_CAL_PARAM* get_tx_pwr_cal(void);
#endif //#if defined(INCLUDE_RF_DEBUG)
#endif// __NRC_RF_H__
