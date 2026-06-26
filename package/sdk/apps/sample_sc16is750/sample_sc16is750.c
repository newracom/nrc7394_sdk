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
#include "sc16is750.h"

i2c_device_t *dev_i2c = NULL;
spi_device_t *dev_spi = NULL;
SC16IS750_t *sc16is750 = NULL;

#define SC16IS750_I2C
//#define SC16IS750_SPI

#define SC16IS750_I2C_SCL 7
#define SC16IS750_I2C_SDA 6
#define SC16IS750_I2C_CLOCK 100000
#define SC16IS750_I2C_CLOCK_SOURCE 0 /* 0:clock controller, 1:PCLK */
#define SC16IS750_BAUD_RATE 115200
#define SC16IS750_I2C_ADDRESS 0x4d

#define SC16IS750_SPI_MISO 12
#define SC16IS750_SPI_MOSI 13
#define SC16IS750_SPI_CS 14
#define SC16IS750_SPI_CLK 17
#define SC16IS750_SPI_CLOCK 400000

//#define SC16IS750_GPIO_TEST_ENABLE 1
#define SC16IS750_GPIO_TEST_PIN 0

#ifdef SC16IS750_GPIO_TEST_ENABLE
static void SC16IS750_GPIO_TEST(void)
{
	nrc_usr_print("SC16IS750_GPIO_TEST\n");
	int gpio = SC16IS750_GPIO_TEST_PIN;
	SC16IS750_pinMode(sc16is750, gpio, OUTPUT);
	while (1) {
		SC16IS750_digitalWrite(sc16is750, gpio, 1);
		_delay_ms(1000);
		SC16IS750_digitalWrite(sc16is750, gpio, 0);
		_delay_ms(1000);
	}
}
#else
static void SC16IS750_UART_TEST(void)
{
	nrc_usr_print("SC16IS750_UART_TEST\n");

	char buffer_A[64] = {0};
	int index_A = 0;
	char buffer_B[64] = {0};
	int index_B = 0;

	char c;
	while(1) {
		if (SC16IS750_available(sc16is750, SC16IS750_CHANNEL_A)) {
			c = SC16IS750_read(sc16is750, SC16IS750_CHANNEL_A);
			if (c < 0x20) {
				nrc_usr_print("c_A= (0x%02x)\n",c);
			} else {
				nrc_usr_print("c_A=%c(0x%02x)\n",c,c);
			}
			if (c == 0x0d) {

			} else if (c == 0x0a) {
				nrc_usr_print("[CH_A:%s]\n",buffer_A);
				index_A = 0;
				buffer_A[0] = 0;
			} else {
				if (index_A < sizeof(buffer_A)-1) {
					buffer_A[index_A++] = c;
					buffer_A[index_A] = 0;
				}
			}
		} // end CHANNEL_A

		if (SC16IS750_available(sc16is750, SC16IS750_CHANNEL_B)) {
			c = SC16IS750_read(sc16is750, SC16IS750_CHANNEL_B);
			if (c < 0x20) {
				nrc_usr_print("c_B= (0x%02x)\n",c);
			} else {
				nrc_usr_print("c_B=%c(0x%02x)\n",c,c);
			}
			if (c == 0x0d) {

			} else if (c == 0x0a) {
				nrc_usr_print("[CH_B:%s]\n",buffer_B);
				index_B = 0;
				buffer_B[0] = 0;
			} else {
				if (index_B < sizeof(buffer_B)-1) {
					buffer_B[index_B++] = c;
					buffer_B[index_B] = 0;
				}
			}
		} // end CHANNEL_B
	} // end while
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
	uint8_t address = 0;
	nrc_uart_console_enable(true);

	sc16is750 = pvPortMalloc(sizeof(SC16IS750_t));
	memset(sc16is750, 0x0, sizeof(SC16IS750_t));

#ifdef SC16IS750_I2C
	dev_i2c = pvPortMalloc(sizeof(i2c_device_t));
	memset(dev_i2c, 0x0, sizeof(i2c_device_t));
	dev_i2c->pin_sda = SC16IS750_I2C_SDA;
	dev_i2c->pin_scl = SC16IS750_I2C_SCL;
	dev_i2c->clock_source = SC16IS750_I2C_CLOCK_SOURCE;
	dev_i2c->controller = I2C_MASTER_0;
	dev_i2c->clock = SC16IS750_I2C_CLOCK;
	dev_i2c->width = I2C_8BIT;
	sc16is750->protocol = SC16IS750_PROTOCOL_I2C;
	address = SC16IS750_I2C_ADDRESS;
#elif defined(SC16IS750_SPI)
	dev_spi = pvPortMalloc(sizeof(spi_device_t));
	memset(dev_spi, 0x0, sizeof(spi_device_t));
	dev_spi->pin_miso = SC16IS750_SPI_MISO;
	dev_spi->pin_mosi = SC16IS750_SPI_MOSI;
	dev_spi->pin_cs =SC16IS750_SPI_CS;
	dev_spi->pin_sclk = SC16IS750_SPI_CLK;
	dev_spi->frame_bits = SPI_BIT8;
	dev_spi->clock = SC16IS750_SPI_CLOCK;
	dev_spi->mode = SPI_MODE0;
	dev_spi->controller = SPI_CONTROLLER_SPI0;
	dev_spi->irq_save_flag = 0;
	dev_spi->isr_handler = NULL;
	sc16is750->protocol = SC16IS750_PROTOCOL_SPI;
	address = SC16IS750_SPI_CS;
#endif
	sc16is750->i2c = dev_i2c;
	sc16is750->spi = dev_spi;

	SC16IS750_init(sc16is750 ,sc16is750->protocol, address, SC16IS750_DUAL_CHANNEL);

	SC16IS750_begin(sc16is750 ,SC16IS750_BAUD_RATE, SC16IS750_BAUD_RATE, SC16IS750_CRYSTCAL_FREQ);
	if (SC16IS750_ping(sc16is750)!=1) {
		nrc_usr_print("device not found\n");
	} else {
		nrc_usr_print("device found\n");
	}

#ifdef SC16IS750_GPIO_TEST_ENABLE
	SC16IS750_GPIO_TEST();
#else
	SC16IS750_UART_TEST();
#endif
}
