/*
 * MIT License
 *
 * Copyright (c) 2024 Newracom, Inc.
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

static spi_device_t sensor_spi;

/* Note spi_isr_handler should handle input and output as fast as SPI tx/rx operates. */
static void spi_isr_handler(int vector)
{
	uint8_t data = 0;

	/* loop back received data */
	nrc_spi_slave_read(&data);
	nrc_spi_slave_write(data);
}

/******************************************************************************
 * FunctionName : run_sample_spi
 * Description  : sample test for spi
 * Parameters   : count(test count), interval(test interval)
 * Returns      : 0 or -1 (0: success, -1: fail)
 *******************************************************************************/
nrc_err_t run_sample_spi_slave(void)
{
	nrc_usr_print("[%s] Sample App for SPI SLAVE \n",__func__);

	/* Set sensor   spi */
	sensor_spi.pin_miso = 29;
	sensor_spi.pin_mosi = 6;
	sensor_spi.pin_cs = 28;
	sensor_spi.pin_sclk = 7;

	sensor_spi.frame_bits = SPI_BIT8;
	sensor_spi.mode = SPI_MODE3; /* Only SPI_MODE3 is supported */
	sensor_spi.controller = SPI_CONTROLLER_SPI0;
	sensor_spi.irq_save_flag = 0;
	sensor_spi.isr_handler = spi_isr_handler;

	nrc_spi_slave_init(&sensor_spi);

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

	run_sample_spi_slave();
}
