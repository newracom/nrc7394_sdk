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

#include "nrc_sdk.h"

#define TEST_COUNT 10
#define TEST_INTERVAL 1000 /* msec */

#if defined(NRC7394)
#define PWM_GPIO0 GPIO_06
#define PWM_GPIO1 GPIO_07
#define PWM_GPIO2 GPIO_10
#define PWM_GPIO3 GPIO_11
#else
/* For nrc7292 */
#define PWM_GPIO0 GPIO_08
#define PWM_GPIO1 GPIO_09
#define PWM_GPIO2 GPIO_10
#define PWM_GPIO3 GPIO_11
#endif

/******************************************************************************
 * FunctionName : run_sample_pwm
 * Description  : sample test for pwm
 * Parameters   : count(test count), interval(test interval)
 * Returns      : 0 or -1 (0: success, -1: fail)
 *******************************************************************************/
 #if defined(NRC7292)
nrc_err_t run_sample_pwm(int count, int interval)
{
	int i = 0;

	nrc_usr_print("[%s] Sample App for PWM API \n",__func__);

	nrc_pwm_hw_init(PWM_CH0, PWM_GPIO0, 0);
	nrc_pwm_hw_init(PWM_CH1, PWM_GPIO1, 0);
	nrc_pwm_hw_init(PWM_CH2, PWM_GPIO2, 0);
	nrc_pwm_hw_init(PWM_CH3, PWM_GPIO3, 0);

	nrc_pwm_set_config(PWM_CH0, 0xF0000000, 0x0, 0x0, 0x0);
	nrc_pwm_set_config(PWM_CH1, 0xFFFF0000, 0x0, 0x0, 0x0);
	nrc_pwm_set_config(PWM_CH2, 0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x0);
	nrc_pwm_set_config(PWM_CH3, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);

	nrc_pwm_set_enable(PWM_CH0, 1);
	nrc_pwm_set_enable(PWM_CH1, 1);
	nrc_pwm_set_enable(PWM_CH2, 1);
	nrc_pwm_set_enable(PWM_CH3, 1);

	_delay_ms(5000);

	uint32_t a, b, c, d;

	c = 0xFFFFFFFF;
	d = 0x000FFFFF;
	for (a = 0; a < 5; a++) {
		nrc_pwm_set_config(PWM_CH0, c << a, c << a, c << a, c << a);
		nrc_pwm_set_config(PWM_CH1, a, a, a, a);
		nrc_pwm_set_config(PWM_CH2, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
		nrc_pwm_set_config(PWM_CH3, d >> a, d >> (a * 2), d >> (a * 3), d >> (a * 4));
		_delay_ms(1000);
		nrc_pwm_set_config(PWM_CH0, 0x0, 0x0, 0x0, 0x0);
		nrc_pwm_set_config(PWM_CH1, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
		nrc_pwm_set_config(PWM_CH2, 0x0, 0x0, 0x0, 0x0);
		nrc_pwm_set_config(PWM_CH3, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
		_delay_ms(1000);
	}

	for(i=0;i<count; i++)
	{
		nrc_usr_print("[%s] Print GPIO_%02d\n",__func__, PWM_GPIO0);
		nrc_pwm_set_config(PWM_CH0, 0, 0, 0, 0);
		nrc_pwm_set_config(PWM_CH1, 0, 0, 0, 0);
		nrc_pwm_set_config(PWM_CH2, 0, 0, 0, 0);
		nrc_pwm_set_config(PWM_CH3, 0, 0, 0, 0);
		_delay_ms(500);

		a = 1;
		b = c = d = 0;
		while (a != 0xFFFFFFFF)
		{
			nrc_usr_print("[%s] Print GPIO_%02d\n",__func__, PWM_GPIO0);
			nrc_pwm_set_config(PWM_CH0, a, 0, 0, 0);
			a = (a << 1) | 0x1;
			_delay_ms(50);
		}
		b = 1;
		while (b != 0xFFFFFFFF)
		{
			nrc_usr_print("[%s] Print GPIO_%02d\n",__func__, PWM_GPIO1);
			nrc_pwm_set_config(PWM_CH1, 0, b, 0, 0);
			b = (b << 1) | 0x1;
			_delay_ms(50);
		}
		c = 1;
		while (c != 0xFFFFFFFF)
		{
			nrc_usr_print("[%s] Print GPIO_%02d\n",__func__, PWM_GPIO2);
			nrc_pwm_set_config(PWM_CH2, 0, 0, c, 0);
			c = (c << 1) | 0x1;
			_delay_ms(50);
		}
		d = 1;
		while (d != 0xFFFFFFFF)
		{
			nrc_usr_print("[%s] Print GPIO_%02d\n",__func__, PWM_GPIO3);
			nrc_pwm_set_config(PWM_CH3, 0, 0, 0, d);
			d = (d << 1) | 0x1;
			_delay_ms(50);
		}

		_delay_ms(1000);
		nrc_pwm_set_config(PWM_CH0, 0, 0, 0, 0);
		nrc_pwm_set_config(PWM_CH1, 0, 0, 0, 0);
		nrc_pwm_set_config(PWM_CH2, 0, 0, 0, 0);
		nrc_pwm_set_config(PWM_CH3, 0, 0, 0, 0);
		_delay_ms(500);
		nrc_pwm_set_config(PWM_CH0, a, b, c, d);
		nrc_pwm_set_config(PWM_CH1, a, b, c, d);
		nrc_pwm_set_config(PWM_CH2, a, b, c, d);
		nrc_pwm_set_config(PWM_CH3, a, b, c, d);
		_delay_ms(500);

		while (a != 0x0)
		{
			nrc_usr_print("[%s] Print GPIO_%02d\n",__func__, PWM_GPIO0);
			nrc_pwm_set_config(PWM_CH0, a, 0, 0, 0);
			a = a >> 1;
			_delay_ms(50);
		}
		while (b != 0x0)
		{
			nrc_usr_print("[%s] Print GPIO_%02d\n",__func__, PWM_GPIO1);
			nrc_pwm_set_config(PWM_CH1, 0, b, 0, 0);
			b = b >> 1;
			_delay_ms(50);
		}
		while (c != 0x0)
		{
			nrc_usr_print("[%s] Print GPIO_%02d\n",__func__, PWM_GPIO2);
			nrc_pwm_set_config(PWM_CH2, 0, 0, c, 0);
			c = c >> 1;
			_delay_ms(50);
		}
		while (d != 0x0)
		{
			nrc_usr_print("[%s] Print GPIO_%02d\n",__func__, PWM_GPIO3);
			nrc_pwm_set_config(PWM_CH3, 0, 0, 0, d);
			d = d >> 1;
			_delay_ms(50);
		}
		_delay_ms(interval);
	}

	nrc_usr_print("[%s] exit \n",__func__);
	return NRC_SUCCESS;
}
#else

#define PWM_SAMPLE_MODE_PHASE 1
#define BASE_CLK_HZ 32000000

static void pwm_regout_demo(void)
{
	nrc_pwm_cfg_t cfg_ch0, cfg_ch1, cfg_ch2, cfg_ch3;

	nrc_usr_print("[%s]\n",__func__);

	/* CH0 */
	memset(&cfg_ch0, 0, sizeof(cfg_ch0));
	cfg_ch0.ch = PWM_CH0;
	cfg_ch0.gpio_num = PWM_GPIO0;
	cfg_ch0.mode = NRC_PWM_MODE_REGOUT;
	cfg_ch0.clk_div = NRC_PWM_CLK_DIV_2;
	cfg_ch0.inversion = false;
	cfg_ch0.trigger = true;
	cfg_ch0.u.regout.p0 = 0xffFF0000;
	nrc_pwm_configure(&cfg_ch0, false);
	nrc_pwm_set_enable_ex(PWM_CH0, true, false);

	/* CH1 */
	memset(&cfg_ch1, 0, sizeof(cfg_ch1));
	cfg_ch1.ch = PWM_CH1;
	cfg_ch1.gpio_num = PWM_GPIO1;
	cfg_ch1.mode = NRC_PWM_MODE_REGOUT;
	cfg_ch1.clk_div = NRC_PWM_CLK_DIV_2;
	cfg_ch1.inversion = false;
	cfg_ch1.trigger = true;
	cfg_ch1.u.regout.p0 = 0xa55aa55a;
	nrc_pwm_configure(&cfg_ch1, false);
	nrc_pwm_set_enable_ex(PWM_CH1, true, false);

	/* CH2 */
	memset(&cfg_ch2, 0, sizeof(cfg_ch2));
	cfg_ch2.ch = PWM_CH2;
	cfg_ch2.gpio_num = PWM_GPIO2;
	cfg_ch2.mode = NRC_PWM_MODE_REGOUT2;
	cfg_ch2.clk_div = NRC_PWM_CLK_DIV_2;
	cfg_ch2.inversion = false;
	cfg_ch2.trigger = true;
	cfg_ch2.u.regout.p0 = 0xffFF0000;
	cfg_ch2.u.regout.p1 = 0xa55aa55a;
	cfg_ch2.u.regout.p2 = 0x0f0f0f0f;
	cfg_ch2.u.regout.p3 = 0xf0f0f0f0;
	nrc_pwm_configure(&cfg_ch2, false);
	nrc_pwm_set_enable_ex(PWM_CH2, true, false);

	/* CH3 */
	memset(&cfg_ch3, 0, sizeof(cfg_ch3));
	cfg_ch3.ch = PWM_CH3;
	cfg_ch3.gpio_num = PWM_GPIO3;
	cfg_ch3.mode = NRC_PWM_MODE_REGOUT2;
	cfg_ch3.clk_div = NRC_PWM_CLK_DIV_2;
	cfg_ch3.inversion = false;
	cfg_ch3.trigger = true;
	cfg_ch3.u.regout.p0 = 0xa55aa55a;
	cfg_ch3.u.regout.p1 = 0xffFF0000;
	cfg_ch3.u.regout.p2 = 0xf0f0f0f0;
	cfg_ch3.u.regout.p3 = 0x0f0f0f0f;
	nrc_pwm_configure(&cfg_ch3, false);
	nrc_pwm_set_enable_ex(PWM_CH3, true, false);

	/* Apply */
	nrc_pwm_apply(PWM_CH0);
	nrc_pwm_apply(PWM_CH1);
	nrc_pwm_apply(PWM_CH2);
	nrc_pwm_apply(PWM_CH3);

	while (1) {
		_delay_ms(1000);
	}
}

static bool pwm_phase_demo(void)
{
	nrc_pwm_cfg_t cfg_ch0, cfg_ch1, cfg_ch2, cfg_ch3;
	uint32_t duty, freq;

	nrc_usr_print("[%s]\n",__func__);

	/* CH0 */
	const uint32_t target_hz_ch0 =  4000000;
	memset(&cfg_ch0, 0, sizeof(cfg_ch0));
	cfg_ch0.ch = PWM_CH0;
	cfg_ch0.gpio_num = PWM_GPIO0;
	cfg_ch0.mode = NRC_PWM_MODE_PHASE;
	cfg_ch0.clk_div = NRC_PWM_CLK_DIV_2;
	cfg_ch0.inversion = false;
	cfg_ch0.trigger = true;

	if (nrc_pwm_calc_freq_duty(BASE_CLK_HZ, cfg_ch0.clk_div ,target_hz_ch0, 25, &freq, &duty) == NRC_SUCCESS) {
		cfg_ch0.u.phase.frequency0 = freq;
		cfg_ch0.u.phase.duty0 = (uint8_t)duty;
	} else {
		nrc_usr_print("[%s] Check the availabe parameters for PWM CH%d\n",__func__, cfg_ch0.ch);
		return false;
	}

	/* (optional) deterministic: clear segment1 */
	cfg_ch0.u.phase.duty1 = 0;
	cfg_ch0.u.phase.frequency1 = 0;
	nrc_pwm_configure(&cfg_ch0, false);
	nrc_pwm_set_enable_ex(PWM_CH0, true, false);

	/* CH1 */
	const uint32_t target_hz_ch1 =  8000000;
	memset(&cfg_ch1, 0, sizeof(cfg_ch1));
	cfg_ch1.ch = PWM_CH1;
	cfg_ch1.gpio_num = PWM_GPIO1;
	cfg_ch1.mode = NRC_PWM_MODE_PHASE;
	cfg_ch1.clk_div = NRC_PWM_CLK_DIV_2;
	cfg_ch1.inversion = false;
	cfg_ch1.trigger = true;
	if (nrc_pwm_calc_freq_duty(BASE_CLK_HZ, cfg_ch1.clk_div ,target_hz_ch1, 50, &freq, &duty) == NRC_SUCCESS) {
		cfg_ch1.u.phase.frequency0 = freq;
		cfg_ch1.u.phase.duty0 = (uint8_t)duty;
	} else {
		nrc_usr_print("[%s] Check the availabe parameters for PWM CH%d\n",__func__, cfg_ch1.ch);
		return false;
	}

	/* (optional) deterministic: clear segment1 */
	cfg_ch1.u.phase.duty1 = 0;
	cfg_ch1.u.phase.frequency1 = 0;
	nrc_pwm_configure(&cfg_ch1, false);
	nrc_pwm_set_enable_ex(PWM_CH1, true, false);

	/* CH2 (PHASE2: duty0/frequency0 + duty1/frequency1) */
	const uint32_t target_hz_ch2 =  4000000;
	memset(&cfg_ch2, 0, sizeof(cfg_ch2));
	cfg_ch2.ch = PWM_CH2;
	cfg_ch2.gpio_num = PWM_GPIO2;
	cfg_ch2.mode = NRC_PWM_MODE_PHASE2;
	cfg_ch2.clk_div = NRC_PWM_CLK_DIV_2;
	cfg_ch2.inversion = false;
	cfg_ch2.trigger = true;
	if (nrc_pwm_calc_freq_duty(BASE_CLK_HZ, cfg_ch2.clk_div ,target_hz_ch2, 50, &freq, &duty) == NRC_SUCCESS) {
		cfg_ch2.u.phase.frequency0 = freq;
		cfg_ch2.u.phase.duty0 = (uint8_t)duty;
	} else {
		nrc_usr_print("[%s] Check the availabe parameters for PWM CH%d\n",__func__, cfg_ch2.ch);
		return false;
	}

	if (nrc_pwm_calc_freq_duty(BASE_CLK_HZ, cfg_ch2.clk_div ,target_hz_ch2, 25, &freq, &duty) == NRC_SUCCESS) {
		cfg_ch2.u.phase.frequency1 = freq;
		cfg_ch2.u.phase.duty1 = (uint8_t)duty;
	} else {
		nrc_usr_print("[%s] Check the availabe parameters for PWM CH%d\n",__func__, cfg_ch2.ch);
		return false;
	}

	nrc_pwm_configure(&cfg_ch2, false);
	nrc_pwm_set_enable_ex(PWM_CH2, true, false);

	/* CH3 (PHASE2) */
	const uint32_t target_hz_ch3 =  2000000;
	memset(&cfg_ch3, 0, sizeof(cfg_ch3));
	cfg_ch3.ch = PWM_CH3;
	cfg_ch3.gpio_num = PWM_GPIO3;
	cfg_ch3.mode = NRC_PWM_MODE_PHASE2;
	cfg_ch3.clk_div = NRC_PWM_CLK_DIV_2;
	cfg_ch3.inversion = false;
	cfg_ch3.trigger = true;


	if (nrc_pwm_calc_freq_duty(BASE_CLK_HZ, cfg_ch3.clk_div ,target_hz_ch3, 75, &freq, &duty) == NRC_SUCCESS) {
		cfg_ch3.u.phase.frequency0 = freq;
		cfg_ch3.u.phase.duty0 = (uint8_t)duty;
	} else {
		nrc_usr_print("[%s] Check the availabe parameters for PWM CH%d\n",__func__, cfg_ch3.ch);
		return false;
	}

	if (nrc_pwm_calc_freq_duty(BASE_CLK_HZ, cfg_ch3.clk_div ,target_hz_ch3, 25, &freq, &duty) == NRC_SUCCESS) {
		cfg_ch3.u.phase.frequency1 = freq;
		cfg_ch3.u.phase.duty1 = (uint8_t)duty;
	} else {
		nrc_usr_print("[%s] Check the availabe parameters for PWM CH%d\n",__func__, cfg_ch3.ch);
		return false;
	}

	nrc_pwm_configure(&cfg_ch3, false);
	nrc_pwm_set_enable_ex(PWM_CH3, true, false);

	/* Apply */
	nrc_pwm_apply(PWM_CH0);
	nrc_pwm_apply(PWM_CH1);
	nrc_pwm_apply(PWM_CH2);
	nrc_pwm_apply(PWM_CH3);

	/* Keep initial waveform as-is */
	while (1) {
		_delay_ms(1000);
	}
	return true;
}

#endif

/******************************************************************************
 * FunctionName : user_init
 * Description  : Start Code for User Application, Initialize User function
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void user_init(void)
{
	//Enable Console for Debugging
	nrc_uart_console_enable(true);
#if defined(NRC7292)
	run_sample_pwm(TEST_COUNT, TEST_INTERVAL);
#else
#if PWM_SAMPLE_MODE_PHASE
	pwm_phase_demo();
#else
	pwm_regout_demo();
#endif
#endif
}
