/*
 * MIT License
 *
 * Copyright (c) 2023 Newracom, Inc.
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
#include "lwip/sys.h"
#include "lwip/sockets.h"
#include "lwip/errno.h"
#include "lwip/netdb.h"
#include "wifi_config_setup.h"
#include "wifi_connect_common.h"

#include "api_uart_dma.h"
#include "driver_nrc.h"
#include "nvs.h"
#include "nvs_config.h"
#include "sample_softap_uart_tcp_server_version.h"

#include "nrc_tcp_server.h"

#define UART_LOCAL_ECHO

#define LOCAL_PORT			50000
#define MAX_RETRY			5
#define BUFFER_SIZE			(1024*4)

#define START_MARKER			0x02
#define END_MARKER			0x03

/* UART DMA tuning (new API) */
#define UART_BAUDRATE			9600
#define UART_RX_RING_SIZE		(16 * 1024)	/* RX DMA ring (bytes). 0 disables ring mode */
#define UART_TX_FIFO_SIZE		(8 * 1024)	/* TX DMA FIFO (bytes). 0 disables TX DMA */

/* If you want driver "idle-frame" delivery, set nonzero (ms). Default off. */
#ifndef UART_IDLE_FRAME_TIMEOUT_MS
#define UART_IDLE_FRAME_TIMEOUT_MS	0
#endif

static uint16_t server_port = LOCAL_PORT;
static uint16_t control_port = 4000;
static NRC_UART_CONFIG uart_config;

static char uart_rx_buffer[BUFFER_SIZE] = {0, };

static WIFI_CONFIG wifi_config;
static WIFI_CONFIG* param = &wifi_config;

/* For client stations connected to soft AP */
static tcp_client_t *sta_clients = NULL;
static tcp_client_t *ctrl_clients = NULL;

static TaskHandle_t uart_tcp_task_handle;
static char tcp_send_buffer[BUFFER_SIZE] = {0, };
static int send_buffer_size = 0;

static SemaphoreHandle_t sync_sem;

/* New API: keep UART DMA open params globally */
static uart_dma_info_t g_uart_info;

/* Optional: let driver allocate rx ring / tx fifo when addr = NULL */
static char *g_rx_ring_mem = NULL;
static char *g_tx_fifo_mem = NULL;

static void uart_transmit(char *buffer, int size)
{
	int bytes_sent = 0;
	int remain = size;
	char *ptr = buffer;

	while (remain > 0) {
		ptr += bytes_sent;

		bytes_sent = nrc_uart_write(ptr, remain);
		if (bytes_sent <= 0) {
			taskYIELD();
			continue;
		}

		if (remain == bytes_sent) {
			break;
		}
		remain -= bytes_sent;
	}
}

int tcp_transmit_data(char *buffer, int len)
{
	int retval = -1;
	tcp_client_t *station = NULL;
	tcp_client_t *next_station;

	for (station = sta_clients; station; station = next_station) {
		next_station = station->next;
		nrc_usr_print("[%s] station socket : %d\n", __func__, station->sock);
		retval = send(station->sock, buffer, len, 0);
		if (retval < 0) {
			close_socket(&sta_clients, station);
		}
	}
	return retval;
}

void handle_tcp_to_uart(int sock, char *buffer, unsigned int size)
{
	static uint64_t recv_count = 0;

	if (sock < 0) {
		return;
	}

	recv_count++;
	nrc_usr_print("[%s] %llu, socket %d, %d bytes received...\n",
				  __func__, recv_count, sock, size);
	uart_transmit(buffer, size);
#ifdef UART_LOCAL_ECHO
	send(sock, buffer, size, 0);
#endif
}

static void uart_to_tcp_task(void *pvParameters)
{
	while (1) {
		if (ulTaskNotifyTake(pdTRUE, portMAX_DELAY) == 0) {
			continue;
		}

		/* Protect shared tcp_send_buffer/send_buffer_size */
		if (sync_sem) {
			xSemaphoreTake(sync_sem, portMAX_DELAY);
		}

		if (send_buffer_size > 0) {
			(void)tcp_transmit_data(tcp_send_buffer, send_buffer_size);

			memset(tcp_send_buffer, 0, BUFFER_SIZE);
			send_buffer_size = 0;
		}

		if (sync_sem) {
			xSemaphoreGive(sync_sem);
		}

		_delay_ms(10);
	}
}

static void tcp_server_task(void *pvParameters)
{
	unsigned short port = *((unsigned short *)pvParameters);
	nrc_usr_print("Uart Server Port used : %d\n", port);
	nrc_usr_print("[%s] sta_clients = %p\n", __func__, sta_clients);
	start_server(port, &sta_clients, handle_tcp_to_uart);
}

/******************************************************************************
 * FunctionName : start_servers
 * Description  : server uart handling server and control server
 * Parameters   : None
 * Returns      : 0 or -1 (0: success, -1: fail)
 *******************************************************************************/
static nrc_err_t start_servers(void)
{
	nrc_usr_print("[%s] server port : %d\n", __func__, server_port);
	nrc_usr_print("[%s] control port : %d\n", __func__, control_port);

	xTaskCreate(tcp_server_task, "tcp_server_task", 2048,
		    (void*)&server_port, uxTaskPriorityGet(NULL), NULL);

	xTaskCreate(uart_to_tcp_task, "uart_to_tcp_task", 2048,
		    NULL, uxTaskPriorityGet(NULL), &uart_tcp_task_handle);

	_delay_ms(1000);
	return 0;
}

/* UART RX callback (called from driver's RX task context) */
void uart_data_receive(char *buf, int len)
{
	/* This callback can fire before user_init finishes creating sem/task.
	 * Make it safe.
	 */
	if (!buf || len <= 0) {
		return;
	}

	/* If queues not ready yet, drop to avoid crash */
	if (!sync_sem) {
		return;
	}

	xSemaphoreTake(sync_sem, portMAX_DELAY);

	/* Prevent overflow if sender sends > BUFFER_SIZE before END_MARKER */
	int space = BUFFER_SIZE - send_buffer_size;
	int copy = (len <= space) ? len : space;

	if (copy > 0) {
		memcpy(tcp_send_buffer + send_buffer_size, buf, copy);
		send_buffer_size += copy;
	} else {
		/* No space left -> drop until END_MARKER arrives */
	}

	xSemaphoreGive(sync_sem);

	/* when end marker is found, notify uart_tcp_task */
	if (buf[len - 1] == END_MARKER) {
		if (uart_tcp_task_handle) {
			xTaskNotifyGive(uart_tcp_task_handle);
		}
	}
}

/******************************************************************************
 * FunctionName : uart_handler_init
 * Description  : Set UART configurations
 * Parameters   : none
 * Returns      : 0 if success, -1 on failure
 *******************************************************************************/
int uart_handler_init(void)
{
	memset(&g_uart_info, 0, sizeof(g_uart_info));

#if defined(NRC7292)
	g_uart_info.uart.channel = NRC_UART_CH2;
#else
	g_uart_info.uart.channel = NRC_UART_CH1;
#endif
	g_uart_info.uart.baudrate = UART_BAUDRATE;
	g_uart_info.uart.data_bits = UART_DB8;
	g_uart_info.uart.stop_bits = UART_SB1;
	g_uart_info.uart.parity = UART_PB_NONE;

	/* HFC must be disabled to use RX DMA ring + TX DMA in this driver */
	g_uart_info.uart.hfc = UART_HFC_DISABLE;

	/* RX DMA ring (enable with size > 0) */
	g_uart_info.rx_fifo.addr = g_rx_ring_mem;	/* NULL => let driver alloc if supported */
	g_uart_info.rx_fifo.size = UART_RX_RING_SIZE;

	/* TX DMA FIFO (enable with size > 0 when HFC disabled) */
	g_uart_info.tx_fifo.addr = g_tx_fifo_mem;	/* NULL => let driver alloc if supported */
	g_uart_info.tx_fifo.size = UART_TX_FIFO_SIZE;

	/* RX staging buffer + callback */
	g_uart_info.rx_params.buf.addr = uart_rx_buffer;
	g_uart_info.rx_params.buf.size = BUFFER_SIZE;
	g_uart_info.rx_params.cb = uart_data_receive;

	if (nrc_uart_dma_open(&g_uart_info) != 0) {
		return -1;
	}

#if UART_IDLE_FRAME_TIMEOUT_MS > 0
	nrc_uart_dma_set_idle_frame_timeout(UART_IDLE_FRAME_TIMEOUT_MS);
#endif

	return 0;
}


#ifdef INCLUDE_SCAN_BACKOFF
static void init_default_backoff()
{
	nvs_handle_t nvs_handle = 0;
	uint32_t backoff_start_count = 0;
	uint32_t scan_max_interval = 0;

	if (nvs_open(NVS_DEFAULT_NAMESPACE, NVS_READONLY, &nvs_handle) != NVS_OK) {
		return;
	}

	if (nvs_get_u32(nvs_handle, NVS_SCAN_BACKOFF_START_COUNT, &backoff_start_count) == NVS_OK) {
		nrc_set_backoff_start_count(backoff_start_count);
	}

	if (nvs_get_u32(nvs_handle, NVS_SCAN_MAX_INTERVAL, &scan_max_interval) == NVS_OK) {
		nrc_set_scan_max_interval(scan_max_interval);
	}

	nvs_close(nvs_handle);
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
	VERSION_T app_version;

	app_version.major = SAMPLE_SOFTAP_UART_TCP_SERVER_MAJOR;
	app_version.minor = SAMPLE_SOFTAP_UART_TCP_SERVER_MINOR;
	app_version.patch = SAMPLE_SOFTAP_UART_TCP_SERVER_PATCH;
	nrc_set_app_version(&app_version);
	nrc_set_app_name(SAMPLE_SOFTAP_UART_TCP_SERVER_APP_NAME);

	/* IMPORTANT: Create sync semaphore BEFORE UART open,
	 * because RX callback may fire immediately after open.
	 */
	sync_sem = xSemaphoreCreateMutex();
	if (!sync_sem) {
		nrc_usr_print("** sync_sem create failed **\n");
		return;
	}

	if (uart_handler_init() != 0) {
		nrc_usr_print("** UART init failed **\n");
		return;
	}

	memset(param, 0x0, WIFI_CONFIG_SIZE);
	nrc_wifi_set_config(param);

#ifdef INCLUDE_SCAN_BACKOFF
	init_default_backoff();
#endif

	nrc_wifi_set_use_4address(true);

	while (1) {
		if (wifi_init(param) == WIFI_SUCCESS) {
			nrc_usr_print("[%s] wifi_init Succeeded!! \n", __func__);
			break;
		} else {
			nrc_usr_print("[%s] wifi_init Failed!! \n", __func__);
			_delay_ms(1000);
		}
	}

	if (wifi_start_softap(param) != WIFI_SUCCESS) {
		nrc_usr_print("[%s] Failed to start softap\n", __func__);
		return;
	}

	if (nrc_wifi_softap_set_ip(0, (char *)&param->static_ip, (char *)&param->netmask, (char *)&param->gateway) != WIFI_SUCCESS) {
		nrc_usr_print("[%s] Failed set AP's IP\n", __func__);
		return;
	}

	if (param->dhcp_server == 1) {
		nrc_usr_print("[%s] Trying to start DHCP Server\n", __func__);
		if (nrc_wifi_softap_start_dhcp_server(0) != WIFI_SUCCESS) {
			nrc_usr_print("[%s] Failed to start dhcp server\n", __func__);
			return;
		}
	}

	start_servers();
}

