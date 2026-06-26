/*
 * MIT License
 *
 * Copyright (c) 2022 Newracom, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#ifndef __NRC_API_PWM_H__
#define __NRC_API_PWM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------------------------------------------------
 * Platform capability
 * -------------------------------------------------------------------------- */
#if defined(NRC7292)
#define NRC_PWM_MAX_CHANNELS   4
#else
#define NRC_PWM_MAX_CHANNELS   8
#endif

#define NRC_PWM_CH_IS_VALID(ch)   ((uint32_t)(ch) < (uint32_t)NRC_PWM_MAX_CHANNELS)

/** @brief channel number of PWM */
typedef enum {
	PWM_CH0,        /**< PWM channel 0 */
	PWM_CH1,        /**< PWM channel 1 */
	PWM_CH2,        /**< PWM channel 2 */
	PWM_CH3,        /**< PWM channel 3 */
#if !defined( NRC7292 )
	PWM_CH4,        /**< PWM channel 4 */
	PWM_CH5,        /**< PWM channel 5 */
	PWM_CH6,        /**< PWM channel 6 */
	PWM_CH7,        /**< PWM channel 7 */
#endif
}PWM_CH;

/**
 * @brief PWM operating mode
 */
typedef enum {
	NRC_PWM_MODE_PHASE   = 0,  /**< PHASE mode: single-segment PWM (duty0 / frequency0) */
	NRC_PWM_MODE_PHASE2  = 1,  /**< PHASE2 mode: dual-segment PWM (duty0/frequency0 + duty1/frequency1)*/
	NRC_PWM_MODE_REGOUT  = 2,  /**< REGOUT mode: single register pattern output (pattern0 only) */
	NRC_PWM_MODE_REGOUT2 = 3,  /**< REGOUT2 mode: multi-register pattern output (pattern0 ~ pattern3, total 128-bit) */
} nrc_pwm_mode_t;

/** @brief PWM clock divider */
typedef enum {
	NRC_PWM_CLK_DIV_2  = 0,   /**< Divide input clock by 2  */
	NRC_PWM_CLK_DIV_4  = 1,   /**< Divide input clock by 4  */
	NRC_PWM_CLK_DIV_8  = 2,   /**< Divide input clock by 8  */
	NRC_PWM_CLK_DIV_16 = 3,   /**< Divide input clock by 16 */
} nrc_pwm_clk_div_t;

/**
 * @brief Phase mode configuration
 */
typedef struct {
	uint32_t duty0;
	uint32_t frequency0;
	uint32_t duty1;
	uint32_t frequency1;
} nrc_pwm_phase_cfg_t;

/**
 * @brief Register output configuration (128-bit)
 */
typedef struct {
	uint32_t p0;
	uint32_t p1;
	uint32_t p2;
	uint32_t p3;
} nrc_pwm_regout_cfg_t;

/**
 * @brief Unified PWM configuration
 */
typedef struct {

	uint8_t ch;
	uint8_t gpio_num;
	nrc_pwm_clk_div_t clk_div;    /* Clock divider */
	bool inversion;    /* Inversion option */
	bool trigger;    /* Enable trigger */

	nrc_pwm_mode_t mode;

	union {
		nrc_pwm_phase_cfg_t  phase;
		nrc_pwm_regout_cfg_t regout;
	} u;

} nrc_pwm_cfg_t;

/*
 * PWM Timing Model
 *
 *	Timing basis:
 *		One tick = one counter clock cycle
 *
 *		counter_clk = base_clk_hz / (2^(clk_div + 1))
 *
 *	Parameter constraints:
 *		freq >= 2
 *		duty >= 1
 *
 *	Output interpretation:
 *
 *		if (inversion == false)
 *			LOW  ticks = duty
 *			HIGH ticks = freq - duty
 *
 *		if (inversion == true)
 *			HIGH ticks = duty
 *			LOW  ticks = freq - duty
 *
 *	|<------------- freq (total ticks) -------------->|
 *
 *	inversion = false (default)
 *
 *	+----+----+----+----+----+----+----+----+----+----+
 *	| L  | L  | L  | L  | H  | H  | H  | H  | H  | H  |
 *	+----+----+----+----+----+----+----+----+----+----+
 *	  <------ duty ------> <------- HIGH region ------>
 *
 *	Actual output frequency:
 *		actual_hz = counter_clk / freq
 */


/**********************************************
 * @fn nrc_err_t nrc_pwm_calc_freq_duty(uint32_t base_clk_hz,
 *                                     uint8_t clk_div,
 *                                     uint32_t target_hz,
 *                                     uint32_t target_duty_percent,
 *                                     uint32_t *out_frequency,
 *                                     uint32_t *out_duty)
 *
 * @brief Calculate PWM frequency and duty ticks
 *        from target frequency and duty percentage
 *
 * @param base_clk_hz: Base clock frequency (Hz)
 *
 * @param clk_div: Clock divider selector (0..3 => /2, /4, /8, /16)
 *
 * @param target_hz: Requested PWM frequency (Hz)
 *
 * @param target_duty_percent: Requested duty percentage
 *
 * @param out_frequency: Output PWM period (ticks)
 *
 * @param out_duty: Output duty (ticks)
 *
 * @return If success, then NRC_SUCCESS.
 *         Otherwise, NRC_FAIL is returned.
 *
 * @note Frequency and duty are calculated using rounding.
 *       Exact target values may not be achievable due to
 *       tick quantization.
 ***********************************************/
nrc_err_t nrc_pwm_calc_freq_duty(uint32_t base_clk_hz,
	uint8_t clk_div,
	uint32_t target_hz,
	uint32_t target_duty_percent,
	uint32_t *out_frequency,
	uint32_t *out_duty);


/**********************************************
 * @fn nrc_err_t nrc_pwm_configure(const nrc_pwm_cfg_t *cfg, bool apply_now)
 *
 * @brief Initialize PWM channel with unified configuration
 *        (supports both PHASE and REGOUT modes)
 *
 * @param cfg: Pointer to PWM configuration structure
 *
 * @param apply_now: Apply configuration immediately if true
 *
 * @return If success, then NRC_SUCCESS.
 *         Otherwise, NRC_FAIL is returned.
 ***********************************************/
nrc_err_t nrc_pwm_configure(const nrc_pwm_cfg_t *cfg, bool apply_now);


/**********************************************
 * @fn nrc_err_t nrc_pwm_set_enable_ex(uint8_t ch, bool enable, bool apply_now)
 *
 * @brief Enable / disable PWM channel (extended API)
 *
 * @param ch: PWM channel
 *
 * @param enable: true(enable) or false(disable)
 *
 * @param apply_now: Apply configuration immediately if true
 *
 * @return If success, then NRC_SUCCESS.
 *         Otherwise, NRC_FAIL is returned.
 ***********************************************/
nrc_err_t nrc_pwm_set_enable_ex(uint8_t ch, bool enable, bool apply_now);


/**********************************************
 * @fn nrc_err_t nrc_pwm_apply(uint8_t ch)
 *
 * @brief Apply pending PWM configuration for the specified channel.
 *		  Use this API to start multiple PWM channels at the same time
 *		  by calling nrc_pwm_configure(..., false) / nrc_pwm_set_enable_ex(..., false)
 *		  first, and then applying them together.
 *
 * @param ch: PWM channel
 *
 * @return If success, then NRC_SUCCESS.
 *		   Otherwise, NRC_FAIL is returned.
 ***********************************************/
nrc_err_t nrc_pwm_apply(uint8_t ch);


/* --------------------------------------------------------------------------
 * Legacy API
 *
 * [NOTE]
 * On NRC7394, this legacy PWM API is deprecated and will be removed
 * in a future release. New designs should use the unified PWM API
 * (nrc_pwm_configure / nrc_pwm_set_enable_ex / nrc_pwm_apply) instead.
 *
 * -------------------------------------------------------------------------- */

/**********************************************
 * @fn nrc_err_t nrc_pwm_hw_init(uint8_t ch, uint8_t gpio_num, uint8_t use_high_clk)
 *
 * @brief Initialize PWM controller
 *
 * @param ch: PWM channel
 *
 * @param gpio_num: GPIO number assigned for PWM
 *
 * @param use_high_clk: If 0, then the pulse duration for 1-bit in each pattern is about 20.8us.
 *                        Otherwise, about 10.4us.
 *
 * @return If success, then NRC_SUCCESS. Otherwise, NRC_FAIL is returned.
 ***********************************************/
nrc_err_t nrc_pwm_hw_init(uint8_t ch, uint8_t gpio_num, uint8_t use_high_clk);


/**********************************************
 * @fn nrc_err_t nrc_pwm_set_config(uint8_t ch, uint32_t pattern1,
 *         uint32_t pattern2,    uint32_t pattern3, uint32_t pattern4)
 *
 * @brief Set configuration parameters of PWM.
 *         one duty cycle consists of 4 pulse patterns(total 128-bit).
 *         it starts with the MSB of pattern1 and ends with the LSB of pattern4.
 *
 * @param ch: PWM channel
 *
 * @param pattern1: 1st pulse pattern
 *
 * @param pattern2: 2nd pulse pattern
 *
 * @param pattern3: 3rd pulse pattern
 *
 * @param pattern4: 4th pulse pattern
 *
 * @return If success, then NRC_SUCCESS. Otherwise, NRC_FAIL is returned.
 ***********************************************/
nrc_err_t nrc_pwm_set_config(uint8_t ch, uint32_t pattern1,\
      uint32_t pattern2, uint32_t pattern3, uint32_t pattern4);


/**********************************************
 * @fn nrc_err_t nrc_pwm_set_enable(uint32_t ch, bool enable)
 *
 * @brief Enable / disable the PWM.
 *
 * @param ch: PWM channel
 *
 * @param enable: true(enable) or false(disable)
 *
 * @return If success, then NRC_SUCCESS. Otherwise, NRC_FAIL is returned.
 ***********************************************/
nrc_err_t nrc_pwm_set_enable(uint32_t ch, bool enable);

#ifdef __cplusplus
}
#endif

#endif //__NRC_API_PWM_H__
