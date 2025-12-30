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
#define TEST_INTERVAL 2000 /* msec */

/******************************************************************************
 * FunctionName : run_sample_adc
 * Description  : sample test for adc
 * Parameters   : count(test count), interval(test interval)
 * Returns      : 0 or -1 (0: success, -1: fail)
 *******************************************************************************/
nrc_err_t run_sample_adc(int count, int interval)
{
	nrc_usr_print("[%s] Sample App for ADC API \n", __func__);
#ifdef NRC7394
	nrc_adc_set_gpio(ADC0, GPIO_17);
	nrc_adc_set_gpio(ADC1, GPIO_18);
#endif
	nrc_adc_init(true);
	_delay_ms(100);

	for(int i=0; i<count; i++) {
		nrc_usr_print("[%s] ", __func__);

#ifdef NRC7292
		nrc_usr_print("ADC1=%03d   ", nrc_adc_get_data(ADC1));
		nrc_usr_print("ADC2=%03d   ", nrc_adc_get_data(ADC2));
		nrc_usr_print("ADC3=%03d   ", nrc_adc_get_data(ADC3));
#else
		nrc_usr_print("ADC0=%03d   ", nrc_adc_get_data(ADC0));
		nrc_usr_print("ADC1=%03d   ", nrc_adc_get_data(ADC1));
#endif
		nrc_usr_print("\n");
		_delay_ms(interval);
	}
	nrc_usr_print("[%s] exit \n",__func__);
	return NRC_SUCCESS;
}

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

	run_sample_adc(TEST_COUNT, TEST_INTERVAL);
}
