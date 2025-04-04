#if !defined(__NRC_CONFIG_H__)
#define __NRC_CONFIG_H__

#define SF_SECTOR_SIZE            4096

/* sysconfig BEGIN */
#define SYSCONFIG_SECTOR_SIZE               4096
#define SYSCONFIG_PRE_USER_FACTORY_SIZE      256
#define SYSCONFIG_USER_FACTORY_SIZE          512
#define SYSCONFIG_SIZE                       768

typedef enum {
	CONFIG_IN_FLASH,
	CONFIG_IN_EEPROM,
} config_location_t;

//1 Byte
typedef struct {
	uint8_t cfo_cal   : 1; //1: pass, 0: fail
	uint8_t da_cal    : 1;
	uint8_t txpwr_cal : 1;
	uint8_t rssi_cal  : 1;
	uint8_t iq_cal    : 1;
	uint8_t reserved  : 1;
	uint8_t tx_test   : 1;
	uint8_t rx_test   : 1;
} sf_sys_config_trx_pass_fail_t;

//4 Bytes
typedef struct {
	uint32_t type     : 16;
	uint32_t reserved : 16;
} sf_sys_config_chip_type_t;

//4 Bytes
typedef struct {
	uint32_t type     : 16;
	uint32_t reserved : 16;
} sf_sys_config_module_type_t;

// 4 Bytes
typedef struct {
	union {
		struct {
			uint32_t txpwr_boosting_valid       :  1;
			uint32_t fem_polarity_valid         :  1;
			uint32_t external_pa_exists         :  1;
			uint32_t max_txgain_valid           :  1;
			uint32_t max_txpwr_valid            :  1;
			uint32_t auxadc_temp_override_valid :  1;
			uint32_t unused                     :  1;
			uint32_t rx_cal_default_override    :  1;
			uint32_t gp17_tx_on_monitoring      :  1;
			uint32_t reserved1                  :  7;
			uint32_t sxtal_32k_flag             :  2; //0: Unknown, 1: okay, 2: not okay
			uint32_t reserved2                  : 14;
		};
		uint32_t word;
	};
} sf_sys_config_module_feature_t;

// 1 Byte
typedef struct {
	uint8_t tmx_gmrc : 2;
	uint8_t reserved : 6;
} sf_sys_config_txpwr_boosting_t;

// 4 Bytes
typedef struct {
	union {
		struct {
			uint32_t pa_en_valid         : 1;
			uint32_t pa_en_always_on     : 1;
			uint32_t pa_en_pin           : 6;

			uint32_t ant_sel_valid       : 1; //TRX Switch
			uint32_t ant_sel_reserved    : 1;
			uint32_t ant_sel_pin         : 6; //TRX Switch

			uint32_t power_down_valid    : 1;
			uint32_t power_down_data     : 1;
			uint32_t power_down_pin      : 6;

			uint32_t reserved         : 8;
		};
		uint32_t word;
	};
} sf_sys_config_gpio_index_map_t;

// 4 Bytes
typedef struct {
	uint16_t valid          : 1;
	uint16_t polarity       : 1;
	uint16_t pin            : 6;
	uint16_t channel_set_id : 8;
	char     country_code[2];
} sf_sys_config_gpio_band_select_t;

//768 Bytes (256 + 512)
typedef struct {
	uint32_t                         version; /* sys_config structure version*/
	char                             mac_addr0[6]; /*mac address for interface 0*/
	char                             mac_addr1[6]; /*mac address for interface 1*/
	uint8_t                          cal_use; /*enable/disable the usage of calibration data*/
	sf_sys_config_trx_pass_fail_t    trx_pass_fail;
	uint16_t                         hw_version; /* HW Version */
	uint32_t                         auxadc_temp_override;
	uint32_t                         reserved1; /* Previously rf_pllldo12_tr struct */
	sf_sys_config_chip_type_t        chip_type; /* NRC7394 module name - TBD */
	sf_sys_config_module_type_t      module_type;
	sf_sys_config_module_feature_t   module_feature;
	sf_sys_config_txpwr_boosting_t   txpwr_boosting;
	uint8_t                          max_txgain; /* NRC7394 max txgain */
	uint8_t                          max_txpwr; /* NRC7394 max txpwr */
	uint8_t                          fem_polarity;
	sf_sys_config_gpio_index_map_t   gpio_index_map;
	char                             serial_number[32];
	char                             mfgt_version[32];
	sf_sys_config_gpio_band_select_t gpio_band_select;
	uint8_t                          reserved2[140];
	char                             user_factory[SYSCONFIG_USER_FACTORY_SIZE];
} sf_sys_config_t;
/* sysconfig END */


/* rfcal BEGIN */
#define RF_CAL_SIGNATURE ('r' | 'f' << 8)
#define RF_CAL_MAIN_HEADER_CURRENT_VER 1
#define RF_CAL_DATA_CURRENT_VER        1
#define RF_CAL_TXPWR_LUT_LENGTH_A      64
#define RF_CAL_TXPWR_LUT_LENGTH_B      64
#define RF_CAL_CHANNEL_INFO_LUT_LENGTH 16
#define RF_CAL_SLOT_HEADER_SIZE        16
#define RF_CAL_SECTOR_SIZE             4096
#define RF_CAL_MAX_SIZE_WITHOUT_SLOT   (RF_CAL_SECTOR_SIZE - RF_CAL_SLOT_HEADER_SIZE)
#define RF_CAL_MAX_INT32_BUF_SIZE      16
#define RF_CAL_MAX_DATA_COUNT          8
#define RF_CAL_MAIN_HEADER_SIZE        8
#define RF_CAL_DATA_SIZE               512

#define RF_CAL_ENCODE_BW(x) (__builtin_ctz(x))
#define RF_CAL_DECODE_BW(x) (1 << x)

#define RF_CAL_TXGAIN_TXPWR_KEY_VALUE_PER_LINE 8
#define RF_CAL_FREQ_OFFSET_KEY_VALUE_PER_LINE  4

// EEPROM
#define EEPROM_SLOT_INFO_SIZE                12
#define EEPROM_SYSCONFIG_ADDR                0x0
#define EEPROM_SYSCONFIG_SIZE                SYSCONFIG_SIZE
#define EEPROM_SYSCONFIG_SECTOR_SIZE         EEPROM_SLOT_INFO_SIZE + EEPROM_SYSCONFIG_SIZE
#define EEPROM_RF_CAL_ADDR                   0x0320
#define EEPROM_RF_CAL_MAX_DATA_COUNT         5
#define EEPROM_RF_CAL_MAX_DATA_SIZE          RF_CAL_MAIN_HEADER_SIZE + (EEPROM_RF_CAL_MAX_DATA_COUNT*RF_CAL_DATA_SIZE)
#define EEPROM_RF_CAL_SECTOR_SIZE            EEPROM_SLOT_INFO_SIZE + EEPROM_RF_CAL_MAX_DATA_SIZE
/////////////////
// MAIN HEADER //
/////////////////

// 8 Bytes
typedef struct {
	uint32_t signature  : 16; // 'r', 'f'
	uint32_t version    : 16; // 1
	uint32_t length     : 16;
	uint32_t data_count :  8;
	uint32_t reserved   :  8;
} rf_cal_main_header_t;

/////////////
// FREQ/BW //
/////////////

#define RF_CAL_BW1M 0
#define RF_CAL_BW2M 1
#define RF_CAL_BW4M 2
#define RF_CAL_BW8M 3

// 4 Bytes
typedef struct {
	uint32_t rx_bw_1m : 4;
	uint32_t prim_1m  : 4;
	uint32_t rx_bw_2m : 4;
	uint32_t prim_2m  : 4;
	uint32_t rx_bw_4m : 4;
	uint32_t prim_4m  : 4;
	uint32_t rx_bw_8m : 4;
	uint32_t prim_8m  : 4;
} rf_cal_op_tx_bw_t;

/////////////////
// DATA HEADER //
/////////////////

// 8 Bytes
typedef struct {
	uint64_t         ref_freq       : 14;
	uint64_t         ref_bw         :  2; //RF_CAL_BWxM
	uint64_t         ref_txgain     :  6;
	uint64_t         reserved       :  2;
	uint64_t         txgain_min     :  6;
	uint64_t         txgain_max     :  6;
	uint64_t         row_valid_1m   :  1;
	uint64_t         row_end_1m     :  6; //Exclusive end: row_count(1m)
	uint64_t         row_valid_2m   :  1;
	uint64_t         row_end_2m     :  6; //Exclusive end: row_count(1m) + row_count(2m)
	uint64_t         row_valid_4m   :  1;
	uint64_t         row_end_4m     :  6; //Exclusive end: row_count(1m) + row_count(2m) + row_count(4m)
	uint64_t         row_valid_8m   :  1;
	uint64_t         row_end_8m     :  6; //Exclusive end: row_count(1m) + row_count(2m) + row_count(4m) + row_count(8m)
} rf_cal_txpwr_cal_info_t;

// 4 Bytes
typedef struct {
	union {
		struct {
			uint32_t  cfo_cal_valid          :  1; //0
			uint32_t  da_cal_valid           :  1; //1
			uint32_t  txpwr_cal_valid        :  1; //2
			uint32_t  rssi_cal_valid         :  1; //3
			uint32_t  iq_cal_valid           :  1; //4
			uint32_t  reserved_cal_valid     :  3;

			uint32_t  lpf_gain_comp_valid    :  1; //8
			uint32_t  temperature_comp_valid :  1; //9
			uint32_t  reserved               : 22;
		};
		uint32_t word;
	};
} rf_cal_field_valid_t;

// 20 Bytes
typedef struct {
	uint16_t                segment_valid : 8;
	uint16_t                id            : 8;
	char                    country_code[2];
	rf_cal_op_tx_bw_t       op_tx_bw;
	rf_cal_txpwr_cal_info_t txpwr_cal_info;
	rf_cal_field_valid_t    field_valid;
} rf_cal_data_header_t;

///////////////
// DATA BODY //
///////////////

// 4 Bytes
typedef struct {
	uint32_t pll_dcxo :  8;
	uint32_t reserved : 24;
} rf_cal_cfo_cal_value_t;

// 4 Bytes
typedef struct {
        int8_t  image_q_offset;
        int8_t  reserved1;
        int8_t  reserved2;
        int8_t  reserved3;
} rf_cal_iq_cal_value_t;

// 4 Bytes
typedef struct {
	uint32_t padr_ibc :  4;
	uint32_t da_con   :  3;
	uint32_t reserved : 25;
} rf_cal_da_cal_value_t;

// 4 Bytes
typedef struct {
	int16_t  txpwr_offset;
	uint16_t freq : 14;
	uint16_t bw   :  2;
} rf_cal_freq_bw_to_txpwr_offset_t;

// 320 Bytes (2 x 64 + 4 x 48)
typedef struct {
	int16_t                          lut_txgain_to_txpwr        [RF_CAL_TXPWR_LUT_LENGTH_A];
	rf_cal_freq_bw_to_txpwr_offset_t lut_freq_bw_to_txpwr_offset[RF_CAL_TXPWR_LUT_LENGTH_B];
} rf_cal_txpwr_cal_value_t;

// 4 Bytes
typedef struct {
	uint32_t base_rssi_1m : 8;
	uint32_t base_rssi_2m : 8;
	uint32_t base_rssi_4m : 8;
	uint32_t base_rssi_8m : 8;
} rf_cal_rssi_cal_value_t;

// 8 Bytes
typedef struct {
	int32_t bw_txpwr_offset_1m : 16;
	int32_t bw_txpwr_offset_2m : 16;
	int32_t bw_txpwr_offset_4m : 16;
	int32_t bw_txpwr_offset_8m : 16;
} rf_cal_bw_txpwr_offset_t;

// 4 Bytes
typedef struct {
	int32_t lna_offset :  8;
	int32_t reserved   : 24;
} rf_cal_lna_offset_t;

// 24 Bytes
typedef struct {
	uint8_t  type;                    // Polynomial: 1
	uint8_t  subtype;                 // N=0~3: Nth order polynomial
	uint8_t  negative_base_two_power; // Negative base 2 power
	uint8_t  reserved;
	int16_t  input_min;
	int16_t  input_max;
	int32_t  coefficients[4];
} rf_cal_interpolator_t;

// 12 Bytes
typedef struct {
	uint32_t start_freq_1m : 16;
	uint32_t start_freq_2m : 16;
	uint32_t start_freq_4m : 16;
	uint32_t start_freq_8m : 16;
	uint32_t index_1m      :  8;
	uint32_t index_2m      :  8;
	uint32_t index_4m      :  8;
	uint32_t index_8m      :  8;
} rf_cal_s1g_global_op_t;

// 488 Bytes
typedef struct {
	rf_cal_cfo_cal_value_t          cfo_cal;
	rf_cal_da_cal_value_t           da_cal;
	rf_cal_txpwr_cal_value_t        txpwr_cal;
	rf_cal_rssi_cal_value_t         rssi_cal;
	rf_cal_bw_txpwr_offset_t        bw_txpwr_offset;
	rf_cal_lna_offset_t             lna_offset;
	rf_cal_iq_cal_value_t           iq_cal;
	uint32_t                        reserved1;
	rf_cal_interpolator_t           lpf_gain_comp;
	rf_cal_interpolator_t           temperature_comp;
	rf_cal_s1g_global_op_t          s1g_global_op;
	uint32_t                        reserved2[3];
} rf_cal_data_body_t;

// 448 Biytes
typedef struct {
	rf_cal_data_header_t header;
	rf_cal_data_body_t   body;
} rf_cal_data_t;

typedef struct {
	char buf[RF_CAL_MAX_SIZE_WITHOUT_SLOT];
} rf_cal_block_t;

typedef bool (*rf_cal_data_header_filter_func) (rf_cal_data_header_t*);

/* rfcal END */
/* nrc_config API */
#define API

typedef struct {
	sf_sys_config_t sysconfig;
	rf_cal_data_t  rf_cal_data;
} nrc_config_info_t;

extern nrc_config_info_t *nrc_config_info;

#define SYSCONFIG    nrc_config_info->sysconfig
#define RF_CAL_DATA  nrc_config_info->rf_cal_data
//#define RF_CAL_BLOCK nrc_config_info->rf_cal_block

void API	nrc_config_init();
void API        nrc_config_enable_sjit_workaround();

void API 	nrc_config_sysconfig_print(sf_sys_config_t *sysconfig, bool hex);
void API 	nrc_config_sysconfig_user_factory_print(sf_sys_config_t *sysconfig, bool hex);

void API 	nrc_config_rf_cal_print_data(rf_cal_data_t *data, int indent_level, bool hex);
bool API 	nrc_config_rf_cal_print_block(rf_cal_block_t *block, bool hex);

bool 		nrc_config_rf_cal_main_header_load(rf_cal_main_header_t *main_header_buf);
bool 		nrc_config_rf_cal_main_header_print(rf_cal_main_header_t *main_header, bool hex);
bool 		nrc_config_rf_cal_signature_valid(rf_cal_main_header_t *main_header);
bool		nrc_config_rf_cal_version_supported(rf_cal_main_header_t *main_header);
bool 		nrc_config_rf_cal_data_segment_valid(rf_cal_data_header_t *data_header);
bool 		nrc_config_rf_cal_evaluate_interpolator(rf_cal_interpolator_t *interpolator, int16_t input, int32_t *output, bool bounded);

uint8_t         nrc_config_rf_cal_get_s1g_channel_index(rf_cal_data_t *rf_cal_data, uint16_t freq, uint8_t bw);

void API 	nrc_config_set_config_location(config_location_t input);
uint8_t API     nrc_config_get_config_location(void);
void API 	nrc_config_erase_sysconfig(void);
void API 	nrc_config_commit_sysconfig(void);
void API 	nrc_config_erase_sysconfig_user_factory(void);
void API 	nrc_config_load_sysconfig_block(uint8_t* sysconfig_block);
void API 	nrc_config_load_sysconfig(void);
bool API 	nrc_config_rf_cal_select_first_filtered_data(rf_cal_data_header_filter_func data_header_filter);
void API 	nrc_config_rf_cal_select_first_valid_data();
bool API 	nrc_config_rf_cal_select_data_by_country_code(char *country_code, uint8_t id);

void API 	nrc_config_load_rf_cal_block(uint8_t* rf_cal_block_data);
void API 	nrc_config_erase_rf_cal_block(void);
void API 	nrc_config_commit_rf_cal_block(uint8_t* rf_cal_block_data);

uint8_t API     nrc_config_rf_cal_get_preferred_worldwide_index(char *country_code, uint8_t id);
bool API nrc_config_rf_cal_get_preferred_country(char *cc);
uint16_t API     nrc_config_get_hw_version(void);
bool API 	nrc_config_get_macaddr(uint8_t *macaddr, uint8_t vif_id);
bool API 	nrc_config_set_macaddr(uint8_t *macaddr, uint8_t vif_id);

extern bool sysconfig_valid;
extern bool rf_cal_valid;

#define ALL_CC_ID 0xFF

typedef struct {
	char     cc[2];
	uint8_t  id;
	uint8_t  reserved;
} cc_id_t;

static const cc_id_t ww7_cc_ids[] =
{
	{"CN",   ALL_CC_ID},
	{{0, 0}, 0, 0} //END MARKER
};

static const cc_id_t ww8_cc_ids[] =
{
	{"EU",   ALL_CC_ID},
	{"SG",   8},
	{"TW",   1},
	{{0, 0}, 0, 0} //END MARKER
};

static const cc_id_t ww9_cc_ids[] =
{
	{"US",   ALL_CC_ID},
	{"JP",   ALL_CC_ID},
	{"KR",   ALL_CC_ID},
	{"SG",   9},
	{"AU",   ALL_CC_ID},
	{"NZ",   ALL_CC_ID},
	{"TW",   9},
	{{0, 0}, 0, 0} //END MARKER
};

#endif /* __NRC_CONFIG_H__ */
