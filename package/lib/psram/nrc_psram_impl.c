/*
 * MIT License
 *
 * Copyright (c) 2021 Newracom, Inc.
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
#include "nrc_dma.h"
#include "nrc_psram_impl.h"

#define PSRAM_SPI_MISO GPIO_12
#define PSRAM_SPI_MOSI GPIO_13
#define PSRAM_SPI_CS   GPIO_14
#define PSRAM_SPI_SCLK GPIO_15

#define PSRAM_SPI_SCLK_SPEED 16000000

#define SPI_XFER_SIZE  8
#define MAX_DMA_DESC_SIZE ((PSRAM_PAGE_SIZE / SPI_XFER_SIZE) + 1)

#define DMA_TX_CHANNEL 4
#define DMA_RX_CHANNEL 5

dma_peri_t spi_tx_peri;
dma_peri_t spi_rx_peri;

dma_desc_t tx_desc[MAX_DMA_DESC_SIZE];
dma_desc_t rx_desc[MAX_DMA_DESC_SIZE];

static uint8_t emptybuffer[MAX_DMA_DESC_SIZE] = {0};

static SemaphoreHandle_t tx_sem;
static SemaphoreHandle_t rx_sem;

spi_device_t spi_dma;

static void print_buffer(uint8_t *buffer, uint32_t size)
{
	int i = 0;
	hal_uart_printf(("\n"));
	hal_uart_printf(("   0        1        2        3        4        5        6        7        8        9       10       11       12       13       14       15    \n"));
	hal_uart_printf(("-----------------------------------------------------------------------------------------------------------------------------------------------\n"));
	for (i = 0; i < size; i++) {
		hal_uart_printf("0x%02x (%c) ", buffer[i],
					  ((buffer[i] >= 32) && (buffer[i] <= 126))? buffer[i] : 0x20);
		if ((i % 16) == 15) {
			hal_uart_printf(("\n"));
		}
	}
	hal_uart_printf(("\n\n"));
}

static void spi_tx_dma_inttc_isr (int channel)
{
    BaseType_t	xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(tx_sem, &xHigherPriorityTaskWoken);
//	system_printf("[%s] xHigherPriorityTaskWoken (%d).\n\n",__func__, xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken == pdTRUE)
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

static void spi_tx_dma_interr_isr (int channel)
{
    BaseType_t	xHigherPriorityTaskWoken = pdFALSE;
//	system_printf("[%s] spi_tx_dma_interr_isr(%d) failed.\n\n",__func__, channel);
    xSemaphoreGiveFromISR(tx_sem, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken == pdTRUE)
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

static void spi_rx_dma_inttc_isr (int channel)
{
    BaseType_t	xHigherPriorityTaskWoken = pdFALSE;
//	system_printf("[%s] spi_rx_dma_inttc_isr(%d).\n\n",__func__, channel);
    xSemaphoreGiveFromISR(rx_sem, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken == pdTRUE)
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

static void spi_rx_dma_interr_isr (int channel)
{
    BaseType_t	xHigherPriorityTaskWoken = pdFALSE;
//	system_printf("[%s] spi_rx_dma_interr_isr(%d) failed.\n\n",__func__, channel);
    xSemaphoreGiveFromISR(rx_sem, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken == pdTRUE)
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

static void init_dma_desc(bool tx)
{
    dma_peri_t *peri;
    dma_desc_t *desc = NULL;
    int i = 0;

//	system_printf("[%s] for %s.\n",__func__, tx? "TX": "RX");
    if (tx) {
        peri = &spi_tx_peri;
        desc = tx_desc;
    } else {
        peri = &spi_rx_peri;
        desc = rx_desc;
    }

    for (i = 0; i < MAX_DMA_DESC_SIZE; i++) {
        if (tx) {
            nrc_dma_desc_init(&desc[i], 0, spi_tx_peri.Addr, SPI_XFER_SIZE);
            nrc_dma_desc_set_addr_inc(&desc[i], true, false);
            nrc_dma_desc_set_ahb_master(&desc[i], NRC_DMA_AHB_M1, NRC_DMA_AHB_M2);
        } else {
            nrc_dma_desc_init(&desc[i], spi_rx_peri.Addr, 0, SPI_XFER_SIZE);
            nrc_dma_desc_set_addr_inc(&desc[i], false, true);
            nrc_dma_desc_set_ahb_master(&desc[i], NRC_DMA_AHB_M2, NRC_DMA_AHB_M1);
        }
        nrc_dma_desc_set_width(&desc[i], NRC_DMA_WIDTH_8, NRC_DMA_WIDTH_8);
        nrc_dma_desc_set_bsize(&desc[i], NRC_DMA_BSIZE_1, NRC_DMA_BSIZE_1);
        nrc_dma_desc_set_inttc(&desc[i], false);

        nrc_dma_desc_set_protection(&desc[i], false, false, false);
        if (i >= 1)
            nrc_dma_desc_link(desc + i - 1, desc + i);
    }
//	system_printf("[%s] returns for %s.\n",__func__, tx? "TX": "RX");
}

static void prepare_dma_desc(bool tx, uint32_t addr, uint32_t size)
{
    dma_peri_t *peri;
    int i = 0;

    dma_desc_t *desc = NULL;
    int n_desc = 0;
    int remainder = size % SPI_XFER_SIZE;

//	system_printf("[%s] for %s.\n",__func__, tx? "TX": "RX");
    if (tx) {
        peri = &spi_tx_peri;
        desc = tx_desc;
    } else {
        peri = &spi_rx_peri;
        desc = rx_desc;
    }

    if (remainder) {
        n_desc = (size / SPI_XFER_SIZE) + 1;
    } else {
        n_desc = size / SPI_XFER_SIZE;
    }

    for (i = 0; i < n_desc; i++) {
        int xfer_size = 0;
        if (remainder) {
            if (i == n_desc - 1) {
                xfer_size = remainder;
            } else {
                xfer_size = SPI_XFER_SIZE;
            }
        } else {
            xfer_size = SPI_XFER_SIZE;
        }

        if (tx) {
            nrc_dma_desc_set_addr(&desc[i], addr + (i * SPI_XFER_SIZE), spi_tx_peri.Addr);
        } else {
            nrc_dma_desc_set_addr(&desc[i], spi_rx_peri.Addr, addr + (i * SPI_XFER_SIZE));
        }
        nrc_dma_desc_set_size(&desc[i], xfer_size);
        desc[i].Next = 0;
        if (i >= 1)
            nrc_dma_desc_link(desc + i - 1, desc + i);
    }
    nrc_dma_desc_set_inttc(&desc[i - 1], true);
}

static int spi_tx_dma_init()
{
    if (nrc_dma_peri_init(&spi_tx_peri, NRC_DMA_PERI_SSP0_TX, SSP0_BASE_ADDR + 8, false, false) != 0) {
        system_printf("[%s] nrc_dma_peri_init() failed.\n",__func__);
        return -1;
    }

    if ( nrc_dma_config_m2p(DMA_TX_CHANNEL, &spi_tx_peri, spi_tx_dma_inttc_isr, spi_tx_dma_interr_isr) != 0) {
        system_printf("[%s] nrc_dma_config_m2p() failed.\n",__func__);
        return -1;
    }

    init_dma_desc(true);

    return 0;
}

static int spi_rx_dma_init()
{
    if (nrc_dma_peri_init(&spi_rx_peri, NRC_DMA_PERI_SSP0_RX, SSP0_BASE_ADDR + 8, false, false) != 0) {
        system_printf("[%s] nrc_dma_peri_init() failed.\n",__func__);
        return -1;
    }

    if (nrc_dma_config_p2m(DMA_RX_CHANNEL, &spi_rx_peri, spi_rx_dma_inttc_isr, spi_rx_dma_interr_isr) != 0) {
        system_printf("[%s] nrc_dma_config_p2m() failed.\n",__func__);
        return -1;
    }

    init_dma_desc(false);

    return 0;
}

void psram_spi_write(uint8_t cmd, uint32_t addr, uint8_t *data, uint32_t size)
{
    int err = 1;
	uint8_t *buffer = NULL;

	/* allocate memory cmd + data */
	buffer = (uint8_t *) pvPortMalloc(size + 4);

	buffer[0] = cmd;
	buffer[1] = (addr >> 16) & 0xFF;
	buffer[2] = (addr >> 8) & 0xFF;
	buffer[3] = (addr) & 0xFF;

	memcpy(buffer + 4, data, size);

    prepare_dma_desc(true, (uint32_t) buffer, size + 4);

    err =  nrc_dma_start(DMA_TX_CHANNEL, tx_desc);
    if (err) {
        system_printf("[%s] nrc_dma_start() failed with err %d.\n",__func__, err);
        return;
    }

    nrc_spi_dma_start_xfer(&spi_dma);

    /* enable SPI controller here after start transfering data */
    nrc_spi_enable(&spi_dma, true);

    xSemaphoreTake(tx_sem, portMAX_DELAY);

    /* disable SPI controller once the data transmission completes */
    nrc_spi_enable(&spi_dma,false);
    nrc_spi_dma_stop_xfer(&spi_dma);

    nrc_dma_stop(DMA_TX_CHANNEL);

	vPortFree(buffer);
}

void psram_spi_read(uint8_t cmd, uint32_t addr, uint8_t *data, uint32_t size)
{
    int err = 1;
	uint8_t *buffer = NULL;

	/* allocate memory cmd + data */
	buffer = (uint8_t *) pvPortMalloc(size + 4);

	buffer[0] = cmd;
	buffer[1] = (addr >> 16) & 0xFF;
	buffer[2] = (addr >> 8) & 0xFF;
	buffer[3] = (addr) & 0xFF;

	prepare_dma_desc(true, (uint32_t) buffer, size + 4);
	prepare_dma_desc(false, (uint32_t) buffer, size + 4);

    /* prepare DMA RX channel to start receiving data */
    err =  nrc_dma_start(DMA_RX_CHANNEL, rx_desc);
    if (err) {
        system_printf("[%s] nrc_dma_start() failed with err %d.\n",__func__, err);
        return;
    }

	err =  nrc_dma_start(DMA_TX_CHANNEL, tx_desc);
	if (err) {
		system_printf("[%s] nrc_dma_start() failed with err %d.\n",__func__, err);
		return;
	}

    nrc_spi_dma_start_xfer(&spi_dma);
    /* enable SPI to start the SPI operation */
    nrc_spi_enable(&spi_dma, true);

    xSemaphoreTake(rx_sem, portMAX_DELAY);
    /* stop the SPI, so that DMA won't retrieve garbage data when next time DMA RX starts */
    nrc_spi_enable(&spi_dma, false);
    nrc_spi_dma_stop_xfer(&spi_dma);

	nrc_dma_stop(DMA_TX_CHANNEL);
    nrc_dma_stop(DMA_RX_CHANNEL);

	memcpy(data, buffer + 4, size);
	vPortFree(buffer);
}

void psram_spi_reset(uint8_t cmd)
{
    int err = 1;

    nrc_spi_start_xfer(&spi_dma);

    /* enable SPI controller here after start transfering data */
    nrc_spi_enable(&spi_dma, true);

	nrc_ssp_xfer(spi_dma.controller, &cmd, NULL, 1);

    /* disable SPI controller once the data transmission completes */
    nrc_spi_enable(&spi_dma, false);
    nrc_spi_stop_xfer(&spi_dma);
}

int psram_spi_init(void)
{
    tx_sem = xSemaphoreCreateBinary();
    rx_sem = xSemaphoreCreateBinary();

    spi_dma.pin_miso = PSRAM_SPI_MISO;
    spi_dma.pin_mosi = PSRAM_SPI_MOSI;
    spi_dma.pin_cs = PSRAM_SPI_CS;
    spi_dma.pin_sclk = PSRAM_SPI_SCLK;
    spi_dma.frame_bits = SPI_BIT8;
    spi_dma.clock = PSRAM_SPI_SCLK_SPEED;
    spi_dma.mode = SPI_MODE0;
    spi_dma.controller = SPI_CONTROLLER_SPI0;
    spi_dma.irq_save_flag = 0;
    spi_dma.isr_handler = NULL;

    nrc_spi_master_init(&spi_dma);
    nrc_ssp_dma(spi_dma.controller, SSP_DMA_TX | SSP_DMA_RX, true);

    if (nrc_dma_is_enabled()) {
        nrc_dma_disable();
    }
    nrc_dma_enable();

    if (spi_rx_dma_init() == NRC_FAIL) {
        return -1;
    }
    if (spi_tx_dma_init() == NRC_FAIL) {
        return -1;
    }

    return 0;
}

void psram_spi_end(void)
{
    xSemaphoreGive(tx_sem);
    vSemaphoreDelete(tx_sem);
    xSemaphoreGive(rx_sem);
    vSemaphoreDelete(rx_sem);
}
