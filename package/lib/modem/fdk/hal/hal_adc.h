#ifndef __HAL_ADC_H__
#define __HAL_ADC_H__
#include <stdint.h>
#include <stdbool.h>
#include "drv_adc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HAL_ADC_DRV_CH0			0
#define HAL_ADC_DRV_CH1			1
#define HAL_ADC_DRV_CH2			2
#define HAL_ADC_DRV_CH3			3
#define HAL_ADC_DRV_CH_NUM   	4

// ---- Public API ----
void hal_adc_init(void);
void hal_adc_deinit(void);
int hal_adc_channel_enable(uint8_t ch, bool en);
void hal_adc_enable(bool en);
int hal_adc_set_gpio(uint8_t ch, uint16_t pin);
uint16_t hal_adc_read_raw(uint8_t ch);
void hal_adc_background_update(void);

#ifdef __cplusplus
}
#endif


#endif /*__HAL_ADC_H__*/
