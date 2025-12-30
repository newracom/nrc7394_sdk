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
#include "nrc_lwip.h"
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
#include "sample_uart_tcp_client_version.h"

#include "nrc_tcp_server.h"

#define UART_TEST_DATA

#define SERVER_PORT 50000
#define MAX_RETRY 2
#define BUFFER_SIZE (1024*4)

#define START_MARKER 0x02
#define END_MARKER 0x03

/* UART DMA tuning */
#define UART_BAUDRATE			9600
#define UART_RX_RING_SIZE		(16 * 1024)	/* RX DMA ring bytes. 0 disables ring mode */
#define UART_TX_FIFO_SIZE		(8 * 1024)	/* TX DMA FIFO bytes. 0 disables TX DMA */

/* Optional: enable driver idle-frame (ms). Leave 0 to keep original marker logic. */
#ifndef UART_IDLE_FRAME_TIMEOUT_MS
#define UART_IDLE_FRAME_TIMEOUT_MS	0
#endif

static uint16_t control_port = 4000;
static NRC_UART_CONFIG uart_config;
static char uart_rx_buffer[BUFFER_SIZE] = {0, };

static int client_socket = -1;

WIFI_CONFIG wifi_config;
WIFI_CONFIG* param = &wifi_config;

static tcp_client_t *ctrl_clients = NULL;

static TaskHandle_t uart_tcp_task_handle;
static char tcp_send_buffer[BUFFER_SIZE] = {0, };
static int send_buffer_size = 0;

static SemaphoreHandle_t sync_sem;

/* Keep UART DMA open params globally */
static uart_dma_info_t g_uart_info;

/* Optional: let driver allocate rx ring / tx fifo when addr = NULL */
static char *g_rx_ring_mem = NULL;
static char *g_tx_fifo_mem = NULL;

#ifdef UART_TEST_DATA
#define PERIODIC_DELAY 1000 /* ms */
char test_data[128] = {0, };

static bool upload_data_packet(char *remote_address, uint16_t port, char* data, int data_length);

static void prepare_test_data()
{
	ip_addr_t server;
	test_data[0] = START_MARKER;
	test_data[127] = END_MARKER;

	test_data[1] = nrc_netif[0]->ip_addr.addr >> 24;
	ipaddr_aton(param->remote_addr, &server);
	test_data[2] = server.addr >> 24;

	char j = 'A';
	for (int i = 3; i < 125; i++, j++) {
		if (j > 'Z') {
			j = 'A';
		}
		test_data[i] = j;
	}
	test_data[125] = '\r';
	test_data[126] = '\n';
}

static void generate_test_data_task(void *pvParameters)
{
	prepare_test_data();

	while (1) {
		upload_data_packet((char *) param->remote_addr, param->remote_port,
						   test_data, 128);
		_delay_ms(PERIODIC_DELAY);
	}
}
#endif /* UART_TEST_DATA */

static void uart_transmit(char *buffer, int size)
{
	int bytes_sent = 0;
	int remain = size;
	char *ptr = buffer;

	while (remain > 0) {
		ptr += bytes_sent;

		/* nrc_uart_write may accept less than remain */
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

/****************************************************************************
 * FunctionName : open_connection
 * Description  : create tcp sockets and connect to server
 *****************************************************************************/
static bool open_connection(char *remote_address, uint16_t port)
{
#ifdef CONFIG_IPV6
	struct sockaddr_in6 dest_addr;
#else
	struct sockaddr_in dest_addr;
#endif
	struct sockaddr_in *addr_in = (struct sockaddr_in *) &dest_addr;
	ip_addr_t remote_addr;
	int ret = 0;

	if (ipaddr_aton((char *) remote_address, &remote_addr)) {
		if (IP_IS_V4(&remote_addr)) {
			addr_in->sin_family = AF_INET;
			addr_in->sin_len = sizeof(struct sockaddr_in);
			addr_in->sin_port = htons(port);
			addr_in->sin_addr.s_addr = inet_addr(remote_address);
		} else {
#ifdef CONFIG_IPV6
			struct sockaddr_in6 *d_addr = (struct sockaddr_in6 *) &dest_addr;
			dest_addr.sin6_family = AF_INET6;
			dest_addr.sin6_len = sizeof(struct sockaddr_in6);
			dest_addr.sin6_port = htons(port);
			dest_addr.sin6_flowinfo = 0;
			dest_addr.sin6_scope_id = ip6_addr_zone(ip_2_ip6(&remote_addr));
			inet6_addr_from_ip6addr(&dest_addr.sin6_addr, ip_2_ip6(&remote_addr));
#else
			nrc_usr_print("[%s] Unknown address type %s\n", __func__, remote_address);
			nrc_usr_print("[%s] Enable IPv6 to handle IPv6 remote address...\n", __func__);
			return false;
#endif
		}
	} else {
		nrc_usr_print("[%s] Address %s not valid or enable IPv6 support.\n", __func__, remote_address);
		nrc_usr_print("[%s] use nvs set remote_address <ip address>\n", __func__);
		return false;
	}

	nrc_usr_print("[%s] Connecting to %s:%d...\n", __func__, remote_address, port);

	client_socket = socket(addr_in->sin_family, SOCK_STREAM, IPPROTO_TCP);
	if (client_socket < 0) {
		nrc_usr_print("Create socket failed\n");
		return false;
	}

	ret = connect(client_socket, (struct sockaddr *) &dest_addr, sizeof(dest_addr));
	if (ret < 0) {
		nrc_usr_print("open_connection failed\n");
		close(client_socket);
		client_socket = -1;
		return false;
	}

	nrc_usr_print("[%s] Connected to %s:%d...\n", __func__, remote_address, port);
	return true;
}

static bool close_connection(void)
{
	if (client_socket >= 0) {
		nrc_usr_print("Connection [%d] closed.\n", client_socket);
		shutdown(client_socket, SHUT_RDWR);
		close(client_socket);
		client_socket = -1;
	}
	return true;
}

static bool retry_tcp_connection(char *remote_address, uint16_t port)
{
	if (!close_connection()) return false;
	if (!open_connection(remote_address, port)) return false;

	nrc_usr_print("Re-Connection to %s:%d succeeded.\n", remote_address, port);
	return true;
}

static bool send_socket_data(char* data, int data_length)
{
	int send_retry_count = 0;
	int send_len = 0;
	int remain_len = data_length;
	static uint64_t sent_count = 0;

	while (remain_len > 0) {
		send_len = send(client_socket, data, remain_len, 0);
		if (send_len < 0) {
			if (send_retry_count < MAX_RETRY) {
				send_retry_count++;
				_delay_ms(1000);
				continue;
			}
			nrc_usr_print("[%s] MAX retry (%d) reached, returning false\n",
				      __func__, send_retry_count);
			return false;
		}

		send_retry_count = 0;
		data       += send_len;
		remain_len -= send_len;
	}

	sent_count++;
	nrc_usr_print("[%s] %llu, %d bytes sent...\n", __func__, sent_count, data_length);
	return true;
}

static bool upload_data_packet(char *remote_address, uint16_t port, char* data, int data_length)
{
	bool bSuccess = false;
	int retryCount = 0;

	while (retryCount < MAX_RETRY) {
		bSuccess = send_socket_data(data, data_length);
		if (bSuccess) {
			break;
		}

		nrc_usr_print("upload_data_packet attempting retry %d\n", retryCount);
		if (retry_tcp_connection(remote_address, port)) {
			nrc_usr_print("Restart upload_data_packet...\n");
			retryCount = 0;
		} else {
			retryCount++;
		}
		_delay_ms(1000);
	}
	return bSuccess;
}

static void tcp_to_uart_task(void *pvParameters)
{
	int ret = 0;
	int recv_len = 0;
	struct timeval select_timeout;
	fd_set fdRead;
	char recv_buffer[BUFFER_SIZE];

	select_timeout.tv_sec = 2;
	select_timeout.tv_usec = 0;

	while (1) {
		FD_ZERO(&fdRead);
		FD_SET(client_socket, &fdRead);

		ret = select(client_socket + 1, &fdRead, NULL, NULL, &select_timeout);
		if (ret > 0 && FD_ISSET(client_socket, &fdRead)) {
			FD_CLR(client_socket, &fdRead);

			recv_len = recv(client_socket, recv_buffer, BUFFER_SIZE, 0);
			if (recv_len <= 0) {
				nrc_usr_print("Receive failed, Trying to reconnect...\n");
				while (!retry_tcp_connection(param->remote_addr, param->remote_port)) {
					_delay_ms(2000);
				}
			} else {
				uart_transmit(recv_buffer, recv_len);
			}
		}
	}
	vTaskDelete(NULL);
}

static void uart_to_tcp_task(void *pvParameters)
{
	while (1) {
		if (ulTaskNotifyTake(pdTRUE, portMAX_DELAY) == 0) {
			continue;
		}

		if (sync_sem) {
			xSemaphoreTake(sync_sem, portMAX_DELAY);
		}

		if (send_buffer_size > 0) {
			(void)upload_data_packet((char *) param->remote_addr, param->remote_port,
						 tcp_send_buffer, send_buffer_size);
			memset(tcp_send_buffer, 0, BUFFER_SIZE);
			send_buffer_size = 0;
		}

		if (sync_sem) {
			xSemaphoreGive(sync_sem);
		}

		_delay_ms(10);
	}
}

nrc_err_t start_tcp_client(void)
{
	int count;

	for (count = 0; count < MAX_RETRY; count++) {
		if (open_connection((char *)param->remote_addr, param->remote_port)) {
			nrc_usr_print("[%s] Connection successful.\n", __func__);
			nrc_usr_print("[%s] Starting upload_data_packet...\n", __func__);
			break;
		}

		if ((count + 1) == MAX_RETRY) {
			nrc_usr_print("[%s] Connection failed for remote %s.\n", __func__, param->remote_addr);
			return -1;
		}
		_delay_ms(1000);
	}

	xTaskCreate(tcp_to_uart_task, "tcp_to_uart_task", 2048,
		    NULL, uxTaskPriorityGet(NULL), NULL);

	xTaskCreate(uart_to_tcp_task, "uart_to_tcp_task", 2048,
		    NULL, uxTaskPriorityGet(NULL), &uart_tcp_task_handle);

#ifdef UART_TEST_DATA
	xTaskCreate(generate_test_data_task, "Test data sender", 1024,
		    NULL, uxTaskPriorityGet(NULL), NULL);
#endif
	return 0;
}

/* UART RX callback (called from driver's RX task context) */
void uart_data_receive(char *buf, int len)
{
	/* If disconnected, drop (keeps existing behavior) */
	if (nrc_wifi_get_state(0) != WIFI_STATE_CONNECTED) {
		nrc_usr_print("[%s] Disconnected from AP!!\n", __func__);
		return;
	}

	/* RX callback can fire very early; avoid crash */
	if (!buf || len <= 0 || !sync_sem) {
		return;
	}

	xSemaphoreTake(sync_sem, portMAX_DELAY);

	/* Protect against overflow */
	int space = BUFFER_SIZE - send_buffer_size;
	int copy = (len <= space) ? len : space;

	if (copy > 0) {
		memcpy(tcp_send_buffer + send_buffer_size, buf, copy);
		send_buffer_size += copy;
	}

	xSemaphoreGive(sync_sem);

	/* when end marker is found, notify uart_to_tcp_task */
	if (buf[len - 1] == END_MARKER) {
		if (uart_tcp_task_handle) {
			xTaskNotifyGive(uart_tcp_task_handle);
		}
	}
}

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

	/* HFC must be disabled for RX DMA ring + TX DMA in this driver */
	g_uart_info.uart.hfc = UART_HFC_DISABLE;

	/* New API: RX DMA ring */
	g_uart_info.rx_fifo.addr = g_rx_ring_mem;	/* NULL => driver alloc if supported */
	g_uart_info.rx_fifo.size = UART_RX_RING_SIZE;

	/* New API: TX DMA FIFO */
	g_uart_info.tx_fifo.addr = g_tx_fifo_mem;	/* NULL => driver alloc if supported */
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
static void init_default_backoff(void)
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

static nrc_err_t network_init(void)
{
	int i = 0, j = 0;
	int scanning_retry_count = 0;
	int backoff_time = 1;
	SCAN_RESULTS results;
	int ssid_found = false;

	memset(param, 0x0, WIFI_CONFIG_SIZE);
	nrc_wifi_set_config(param);
	param->remote_port = SERVER_PORT;

#ifdef INCLUDE_SCAN_BACKOFF
	init_default_backoff();
#endif

	if (wifi_init(param) != WIFI_SUCCESS) {
		nrc_usr_print("[%s] ASSERT! Fail for init\n", __func__);
		return NRC_FAIL;
	}

	while (1) {
		if (nrc_wifi_scan(0) == WIFI_SUCCESS) {
			if (nrc_wifi_scan_results(0, &results) == WIFI_SUCCESS) {
				nrc_usr_print("SCAN_RESULT :  bssid / frequency / signal level / flags / ssid\n");
				for (i = 0; i < results.n_result; i++) {
					nrc_usr_print("[%d] %s\t%s\t%s\t%s\t%s\n",
						      (i+1),
						      (char*)results.result[i].bssid,
						      (char*)results.result[i].freq,
						      (char*)results.result[i].sig_level,
						      (char*)results.result[i].flags,
						      (char*)results.result[i].ssid);

					if ((strcmp((char*)param->ssid, (char*)results.result[i].ssid) == 0)
					    && (results.result[i].security == param->security_mode)) {
						ssid_found = true;
						scanning_retry_count = 0;
						break;
					}
				}

				if (ssid_found) {
					nrc_usr_print("[%s] %s is found \n", __func__, param->ssid);
					backoff_time = 1;
					break;
				} else {
					nrc_usr_print("[%s] %s is not found \n", __func__, param->ssid);
				}
			}
		} else {
			nrc_usr_print("[%s] Scan fail !! \n", __func__);
		}

		++scanning_retry_count;

#if defined(INCLUDE_SCAN_BACKOFF)
		if (scanning_retry_count > nrc_get_backoff_start_count())
			backoff_time = generateRandomBackoff((scanning_retry_count - nrc_get_backoff_start_count()));

		for (j = 0; j < backoff_time; j++)
			_delay_ms(1000);
#endif
	}

	while (1) {
		if (wifi_connect(param) == WIFI_SUCCESS) {
			nrc_usr_print("[%s] connect to %s successfully !! \n", __func__, param->ssid);
			break;
		} else {
			nrc_usr_print("[%s] Fail for connection %s\n", __func__, param->ssid);
			_delay_ms(1000);
		}
	}

	if (nrc_wait_for_ip(0, param->dhcp_timeout) == NRC_FAIL) {
		return NRC_FAIL;
	}

	return NRC_SUCCESS;
}

void user_init(void)
{
	VERSION_T app_version;
	app_version.major = SAMPLE_UART_TCP_CLIENT_MAJOR;
	app_version.minor = SAMPLE_UART_TCP_CLIENT_MINOR;
	app_version.patch = SAMPLE_UART_TCP_CLIENT_PATCH;
	nrc_set_app_version(&app_version);
	nrc_set_app_name(SAMPLE_UART_TCP_CLIENT_APP_NAME);

	if (network_init() == NRC_FAIL) {
		nrc_usr_print("** network init failed **\n");
		return;
	}

	/* IMPORTANT: create sync mutex BEFORE UART open (RX callback can fire immediately) */
	sync_sem = xSemaphoreCreateMutex();
	if (!sync_sem) {
		nrc_usr_print("** sync_sem create failed **\n");
		return;
	}

	if (uart_handler_init() != 0) {
		nrc_usr_print("** UART init failed **\n");
		return;
	}

	if (start_tcp_client() != 0) {
		nrc_usr_print("** TCP client start failed **\n");
		return;
	}

