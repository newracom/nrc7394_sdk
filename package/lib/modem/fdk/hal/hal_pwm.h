#ifndef __HAL_PWM_H__
#define __HAL_PWM_H__
#include <stdint.h>
#include <stdbool.h>
#include "drv_pwm.h"

#ifndef HAL_PWM_MAX_CH
#define HAL_PWM_MAX_CH	4
#endif

/* ---------------- valid_mask bits ---------------- */
/* Common */
#define HAL_PWM_F_GPIO			(1u << 0)
#define HAL_PWM_F_CLKDIV		(1u << 1)
#define HAL_PWM_F_INVERSION		(1u << 2)
#define HAL_PWM_F_MODE			(1u << 3)
#define HAL_PWM_F_LOOP			(1u << 4)
#define HAL_PWM_F_TRIGGER		(1u << 5)
#define HAL_PWM_F_ENABLE		(1u << 6)

/* Phase partial updates */
#define HAL_PWM_F_DUTY0			(1u << 7)
#define HAL_PWM_F_FREQUENCY0		(1u << 8)
#define HAL_PWM_F_DUTY1			(1u << 9)
#define HAL_PWM_F_FREQUENCY1		(1u << 10)

/* Register-out partial updates */
#define HAL_PWM_F_PATTERN0		(1u << 11)
#define HAL_PWM_F_PATTERN1		(1u << 12)
#define HAL_PWM_F_PATTERN2		(1u << 13)
#define HAL_PWM_F_PATTERN3		(1u << 14)

typedef struct {

	uint32_t valid_mask;

	/* Common */
	uint16_t gpio;
	uint32_t clk_div;
	uint32_t inversion;
	uint32_t mode;
	uint32_t loop;
	uint32_t trigger;
	uint8_t  enable;

	union {

		/* Phase mode */
		struct {
			uint32_t duty0;
			uint32_t frequency0;
			uint32_t duty1;
			uint32_t frequency1;
		} phase;

		/* Register out mode */
		struct {
			uint32_t pattern0;
			uint32_t pattern1;
			uint32_t pattern2;
			uint32_t pattern3;
		} regout;

	} u;
} hal_pwm_ch_cfg_t;

#ifdef __cplusplus
extern "C" {
#endif

void hal_pwm_init(void);
void hal_pwm_deinit(void);

int hal_pwm_reset(void);
int hal_pwm_apply(uint8_t ch);

/* Per-channel configure (recommended usage) */
int hal_pwm_configure_channel(uint8_t ch, const hal_pwm_ch_cfg_t *cfg, bool apply_now);

#ifdef __cplusplus
}
#endif


#endif /*__HAL_PWM_H__*/
