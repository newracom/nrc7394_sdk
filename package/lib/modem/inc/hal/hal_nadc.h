#ifndef __HAL_NADC_NRC7392_H__
#define __HAL_NADC_NRC7392_H__

#include "system.h"

enum {
	ADC_CH_0 = 0,
	ADC_CH_1,
	ADC_CH_2,
	ADC_CH_3,
};

enum {
	ADC_NO_AVRG = 0,
	ADC_2_AVRG,
	ADC_4_AVRG,
	ADC_8_AVRG,
	ADC_16_AVRG,
};

typedef union {
	struct {
		uint32_t sw_en 		: 1;
		uint32_t sel		: 2;
		uint32_t reserved1   : 1;
		uint32_t adc_en   : 1;
		uint32_t reserved2   : 3;
		uint32_t avrg_sel   : 3;
		uint32_t reserved3   : 20;
		uint32_t clk_inv   : 1;
	} bit;
	uint32_t word;
} adc_ctrl_t;


typedef union {
	struct {
		uint32_t ch0 			: 9;
		uint32_t ch0_valid		: 1;
		uint32_t reserved1   	: 6;
		uint32_t ch1 			: 9;
		uint32_t ch1_valid		: 1;
		uint32_t reserved2   	: 6;
	} bit;
	uint32_t word;
} adc_data_t;


typedef struct {
	volatile adc_ctrl_t 						ctrl;
	volatile adc_data_t 						data01;
	volatile adc_data_t 						data23;
} adc_controller_t;

void nrc_nadc_init(void);
void nrc_nadc_deinit(void);

void nrc_nadc_clk_inversion(bool enable);
void nrc_nadc_avrg_sel(uint8_t id);
void nrc_nadc_sel(uint32_t id);
void nrc_nadc_enable(bool enable);

/* Auxiliary ADC Enable
  ADC should be enabled more than 30usec in advance
  before conversion starting with SWEN bit
*/
void nrc_nadc_aux_adc_enable(bool enable);


bool nrc_nadc_ch_valid(uint32_t id);
uint16_t nrc_nadc_data(uint32_t id);
uint16_t nrc_nadc_valid_with_data(uint32_t id);
bool nrc_nadc_valid(uint16_t value);
void nrc_nadc_show(void);
void nrc_nadc_test(void);

#define ADC_VALID(x) ((x & BIT10)? true: false)
#define ADC_VALUE(x) (x & 0x3FF)

#endif //__HAL_NADC_NRC7392_H__