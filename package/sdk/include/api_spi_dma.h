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


#ifndef __API_SPI_DMA_H__
#define __API_SPI_DMA_H__

#include "api_spi.h"

/**********************************************
 * @fn spi_dma_init(spi_device_t *spi_dma)
 *
 * @brief Initialize SPI using DMA.
 *        spi_device_t should be initialized for SPI configuration
 *        and supplied when calling spi_dma_init.
 *
 * @param spi_dma : user initialized SPI configuration.
 *
 * @return 0 if successful, -1 otherwise.
 ***********************************************/
int spi_dma_init(spi_device_t *spi_dma);

/**********************************************
 * @fn spi_dma_write(uint8_t *data, uint32_t size)
 *
 * @brief Write data to SPI using DMA. SPI related data should be prepared by user.
 *
 * @param data : to be transferred to SPI device.
 * @param size : size of data.
 *
 * @return NONE
 ***********************************************/
void spi_dma_write(uint8_t *data, uint32_t size);

/**********************************************
 * @fn spi_dma_read(uint8_t *addr, uint8_t *data, uint32_t size)
 *
 * @brief Read data from SPI interface using DMA for given address
 *        and save the data to user supplied buffer.
 *
 * @param addr : SPI peripheral address.
 * @param data : buffer to transferred data to be saved.
 * @param size : size for how much data to be read.
 *
 * @return NONE
 ***********************************************/
void spi_dma_read(uint8_t *addr, uint8_t *data, uint32_t size);


/**********************************************
 * @fn nrc_spi_slave_dma_init(spi_device_t *spi)
 *
 * @brief Initialize SPI slave side DMA support. This function prepares
 *        DMA resources to be used with the SPI slave interface that was
 *        already initialized with nrc_spi_slave_init().
 *
 * @param spi : A pointer for spi configuration which has been
 *              initialized for slave mode.
 *
 * @return 0 if successful, -1 otherwise.
 ***********************************************/
int nrc_spi_slave_dma_init(spi_device_t *spi);

/**********************************************
 * @fn nrc_spi_slave_arm_rxdma(spi_device_t *spi, uint8_t *dst_buf, uint16_t size)
 *
 * @brief Arm a DMA receive transfer for SPI slave mode. After calling this
 *        function, the SPI slave is ready to receive 'size' bytes from the
 *        SPI master and store them into dst_buf.
 *        Completion status can be checked with nrc_spi_slave_rx_done().
 *
 * @param spi     : A pointer for spi configuration.
 * @param dst_buf : Destination buffer to store received data.
 * @param size    : Number of bytes to receive.
 *
 * @return 0 if successful, -1 otherwise.
 ***********************************************/
int nrc_spi_slave_arm_rxdma(spi_device_t *spi, uint8_t *dst_buf, uint16_t size);

/**********************************************
 * @fn nrc_spi_slave_stop_rxdma(spi_device_t *spi)
 *
 * @brief Stop/disable the current SPI slave DMA receive transfer that was
 *        previously started with nrc_spi_slave_arm_rxdma().
 *
 * @param spi : A pointer for spi configuration.
 *
 * @return NONE
 ***********************************************/
void nrc_spi_slave_stop_rxdma(spi_device_t *spi);

/**********************************************
 * @fn nrc_spi_slave_rx_done(void)
 *
 * @brief Check if the DMA receive started by nrc_spi_slave_arm_rxdma()
 *        has completed successfully.
 *
 * @param NONE
 *
 * @return non-zero if DMA receive has completed, 0 otherwise.
 ***********************************************/
int nrc_spi_slave_rx_done(void);

/**********************************************
 * @fn nrc_spi_slave_rx_error(void)
 *
 * @brief Check if an error occurred during the DMA receive started by
 *        nrc_spi_slave_arm_rxdma().
 *
 * @param NONE
 *
 * @return non-zero if a DMA receive error occurred, 0 otherwise.
 ***********************************************/
int nrc_spi_slave_rx_error(void);

/**********************************************
 * @fn nrc_spi_slave_arm_txdma(spi_device_t *spi, const uint8_t *src_buf, uint16_t size)
 *
 * @brief Arm a DMA transmit transfer for SPI slave mode. After calling this
 *        function, the SPI slave is ready to provide 'size' bytes from
 *        src_buf to the SPI master on the next clocking from the master.
 *        Completion status can be checked with nrc_spi_slave_tx_done().
 *
 * @param spi     : A pointer for spi configuration.
 * @param src_buf : Source buffer containing data to send to master.
 * @param size    : Number of bytes to transmit.
 *
 * @return 0 if successful, -1 otherwise.
 ***********************************************/
int nrc_spi_slave_arm_txdma(spi_device_t *spi, const uint8_t *src_buf, uint16_t size);

/**********************************************
 * @fn nrc_spi_slave_stop_txdma(spi_device_t *spi)
 *
 * @brief Stop/disable the current SPI slave DMA transmit transfer that was
 *        previously started with nrc_spi_slave_arm_txdma().
 *
 * @param spi : A pointer for spi configuration.
 *
 * @return NONE
 ***********************************************/
void nrc_spi_slave_stop_txdma(spi_device_t *spi);

/**********************************************
 * @fn nrc_spi_slave_tx_done(void)
 *
 * @brief Check if the DMA transmit started by nrc_spi_slave_arm_txdma()
 *        has completed successfully.
 *
 * @param NONE
 *
 * @return non-zero if DMA transmit has completed, 0 otherwise.
 ***********************************************/
int nrc_spi_slave_tx_done(void);

/**********************************************
 * @fn nrc_spi_slave_tx_error(void)
 *
 * @brief Check if an error occurred during the DMA transmit started by
 *        nrc_spi_slave_arm_txdma().
 *
 * @param NONE
 *
 * @return non-zero if a DMA transmit error occurred, 0 otherwise.
 ***********************************************/
int nrc_spi_slave_tx_error(void);

#endif /* #ifndef __API_SPI_DMA_H__ */
