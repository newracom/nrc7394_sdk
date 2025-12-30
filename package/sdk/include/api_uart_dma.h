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

#ifndef __API_UART_DMA_H__
#define __API_UART_DMA_H__
/*****************************************************************************/

#include "nrc_sdk.h"
#include "api_dma.h"

/* -------------------------------------------------------------------------- */
/* Types                                                                       */
/* -------------------------------------------------------------------------- */

typedef struct
{
	int channel;
	int baudrate;

	enum uart_data_bit               data_bits;
	enum uart_stop_bit               stop_bits;
	enum uart_parity_bit             parity;
	enum uart_hardware_flow_control  hfc;        /**< UART_HFC_DISABLE or UART_HFC_ENABLE */
} uart_dma_t;

/** Simple buffer descriptor. The memory may be provided by the caller or
 *  allocated internally depending on the build configuration.
 */
typedef struct
{
	char *addr;   /**< Start of buffer (optional; pass NULL to let driver alloc) */
	int   size;   /**< Size in bytes (must be > 0 when used) */
} uart_dma_buf_t;

/** RX callback signature. Called from the RX task context. */
typedef void (*uart_dma_rxcb_t)(char *buf, int len);

/** RX task parameters: a user-provided staging buffer and a callback. */
typedef struct
{
	uart_dma_buf_t  buf;  /**< Caller-owned scratch buffer passed to cb(). */
	uart_dma_rxcb_t cb;   /**< Called when data is available. */
} uart_dma_rx_params_t; // used by internal uart_dma_rx_task().

/** Aggregate open parameters. */
typedef struct
{
	uart_dma_t      uart;      /**< UART line settings */

	/** RX SW FIFO backing store.
	 *  - size > 0 enables the RX DMA ring / IRQ buffering.
	 *  - addr == NULL lets the driver allocate.
	 */
	uart_dma_buf_t  rx_fifo;

	/** TX SW FIFO backing store.
	 *  - When size > 0 *and* hfc == UART_HFC_DISABLE, TX uses on-demand DMA
	 *    from this FIFO (zero-copy into the UART).
	 *  - When size == 0 or hfc == UART_HFC_ENABLE, TX falls back to the
	 *    legacy polled FIFO write (no TX DMA).
	 *  - addr == NULL lets the driver allocate (if supported by build).
	 */
	uart_dma_buf_t  tx_fifo;

	/** RX task parameters (staging buffer + callback). */
	uart_dma_rx_params_t rx_params;
} uart_dma_info_t;

/* -------------------------------------------------------------------------- */
/* Public API                                                                  */
/* -------------------------------------------------------------------------- */

/**
 * @brief Initialize UART and DMA settings and start the RX task.
 *
 * Typical usage:
 * @code
 *  static char rx_stage[1024];
 *  uart_dma_info_t info = {0};
 *
 *  info.uart.channel   = NRC_UART_CH2;
 *  info.uart.baudrate  = 115200;
 *  info.uart.data_bits = UART_DB8;
 *  info.uart.stop_bits = UART_SB1;
 *  info.uart.parity    = UART_PB_NONE;
 *  info.uart.hfc       = UART_HFC_DISABLE; // HFC enables IRQ RX mode; disable for DMA RX ring
 *
 *  // RX FIFO for DMA ring:
 *  info.rx_fifo.addr = NULL;                         // let driver alloc (if supported) or set your buffer
 *  info.rx_fifo.size = 32 * 1024;                    // e.g., 32 KB
 *
 *  // TX FIFO enables TX DMA when HFC is disabled:
 *  info.tx_fifo.addr = NULL;                         // optional; enable for TX DMA
 *  info.tx_fifo.size = 8 * 1024;                     // e.g., 8 KB (0 => no TX DMA)
 *
 *  // RX delivery to app:
 *  info.rx_params.buf.addr = rx_stage;               // staging buffer used by callback
 *  info.rx_params.buf.size = sizeof(rx_stage);
 *  info.rx_params.cb       = my_rx_callback;
 */

/**********************************************
 * @fn nrc_uart_dma_open (uart_dma_info_t *info)
 *
 * @brief Initialize UART and DMA setting.
 *        uart_dma_info_t should be initialize and passed to this function.
 *        i.e.
 *        // uart channel to be used.
 *        info.uart.channel = NRC_UART_CH2;
 *        // uart baud rate.
 *        info.uart.baudrate = 9600;
 *        // data bit setting for uart communication.
 *        info.uart.data_bits = UART_DB8;
 *        // stop bit setting for uart communication.
 *        info.uart.stop_bits = UART_SB1;
 *        // parity bit for uart communication.
 *        info.uart.parity = UART_PB_NONE;
 *        // whether to enable/disable hardware flow control.
 *        info.uart.hfc = UART_HFC_DISABLE;
 *        // Buffer used for data received.
 *        info.rx_params.buf.addr = uart_rx_buffer;
 *        // size of buffer to be used for RX data.
 *        info.rx_params.buf.size = RXBUF_SIZE;
 *        // callback function when there is RX data available.
 *        info.rx_params.cb = uart_data_receive;
 *
 * @param info : uart setting to be used.
 *
 * @return 0 if successful, -1 otherwise.
 ***********************************************/
int nrc_uart_dma_open(uart_dma_info_t *info);

/**********************************************
 * @fn void nrc_uart_dma_close (void)
 *
 * @brief Close the UART, stop the RX task, and release resources.
 *
 * @param NONE
 *
 * @return NONE
 ***********************************************/
void nrc_uart_dma_close(void);

/**********************************************
 * @fn int nrc_uart_dma_change(uart_dma_t *uart)
 *
 * @brief Change UART line settings at runtime.
 *
 * If HFC state changes:
 *  - switching to UART_HFC_DISABLE enables DMA RX ring and optional TX DMA (if tx_fifo.size > 0),
 *  - switching to UART_HFC_ENABLE uses IRQ RX path and disables TX DMA.
 *
 * @param uart [in] New UART settings.
 *
 * @return 0 on success, -1 on failure, -2 for invalid parameter.
 */
int nrc_uart_dma_change(uart_dma_t *uart);

/**********************************************
 * @fn nrc_uart_dma_read (char *buf, int len)
 *
 * @brief Read UART data (non-blocking).
 *
 * @param buf [out] Destination buffer.
 * @param len [in]  Size of @p buf in bytes.
 *
 * @return Number of bytes copied (0 if none).
 ***********************************************/
int nrc_uart_dma_read(char *buf, int len);

/**********************************************
 * @fn nrc_uart_write (char *buf, int len)
 *
 * @brief Write data to UART.
 *
 * @param buf [in] Data to transmit.
 * @param len [in] Size in bytes.
 *
 * @return Number of bytes accepted (may be less than @p len if FIFO is full).
 ***********************************************/
int nrc_uart_write(char *buf, int len);

/**********************************************
 * @fn nrc_uart_write_done (void)
 *
 * @brief Check if all queued TX data has left the device.
 *
 * @return true if TX DMA is idle (or not in use), SW TX FIFO is empty (or not present),
 *         and the UART HW FIFO/shifter is empty; false otherwise.
 ***********************************************/
bool nrc_uart_write_done(void);

/**********************************************
 * @fn nrc_uart_dma_set_idle_frame_timeout(uint32_t ms)
 *
 * @brief Set quiet-window framing timeout for UART RX (IDLE-like).
 *        When ms > 0, bytes arriving via the RX DMA ring are accumulated and
 *        delivered to the application's RX callback as a single frame once the line
 *        has been idle (no new bytes) for ms. When ms == 0, framing is disabled
 *        and data is delivered in streaming chunks as it becomes available.
 *
 * @param ms Quiet-window duration in milliseconds; 0 disables idle framing.
 *
 * @return NONE
 ***********************************************/
void nrc_uart_dma_set_idle_frame_timeout(uint32_t ms);

/**********************************************
 * @fn nrc_uart_dma_set_idle_frame_gap_bytes(uint32_t gap_bytes)
 *
 * @brief Set quiet-window framing timeout as a *byte gap* instead of ms.
 *        The driver converts bytes -> time using the configured baud rate.
 *
 *        Assumes UART 8N1 framing (10 bits per byte):
 *          gap_time_seconds = (gap_bytes * 10) / baudrate
 *
 *        Example @115200:
 *          gap_bytes = 350
 *          bits = 350 * 10 = 3500 bits
 *          time = 3500 / 115200 = 0.03038 s ≈ 30.4 ms
 *
 * @param gap_bytes Quiet-window in "byte-times"; 0 disables this mode.
 *
 * @return NONE
 ***********************************************/
void nrc_uart_dma_set_idle_frame_gap_bytes(uint32_t gap_bytes);

/**********************************************
 * @fn nrc_uart_dma_set_frame_mode(uint32_t max_frame_bytes, uint32_t idle_gap_bytes)
 *
 * @brief Convenience API for the common "frame-based echo" use case:
 *        - accumulate RX until either:
 *            (a) max_frame_bytes received, OR
 *            (b) idle gap detected (idle_gap_bytes converted to time)
 *        - then deliver exactly that accumulated frame to RX callback
 *          (application can enqueue TX to echo it in one continuous TX DMA transfer).
 *
 * @param max_frame_bytes Maximum frame bytes expected on RX (0 => use rx_params.buf.size)
 * @param idle_gap_bytes  Idle gap threshold in byte-times (0 => disable idle framing)
 *
 * @return NONE
 ***********************************************/
void nrc_uart_dma_set_frame_mode(uint32_t max_frame_bytes, uint32_t idle_gap_bytes);

/*****************************************************************************/
#endif /* __API_UART_DMA_H__ */
