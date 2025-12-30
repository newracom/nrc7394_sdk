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
#include "lwip/sockets.h"
#include "lwip/errno.h"
#include "api_uart_dma.h"

#define UART_TEST_DATA
#define MAX_RETRY 2
#define BUFFER_SIZE (1024*4)

#define START_MARKER 0x02
#define END_MARKER   0x03

/* Optional: avoid infinite wait in uart transmit direction switching */
#ifndef UART_TX_DONE_TIMEOUT_MS
#define UART_TX_DONE_TIMEOUT_MS 200
#endif

static NRC_UART_CONFIG uart_config;
static char uart_rx_buffer[BUFFER_SIZE] = {0, };

static int client_socket = -1;

static TaskHandle_t uart_tcp_task_handle;
static char tcp_send_buffer[BUFFER_SIZE] = {0, };
static int send_buffer_size = 0;

static SemaphoreHandle_t sync_sem;

#ifdef UART_TEST_DATA
#define PERIODIC_DELAY 1000 /* ms */
char test_data[128] = {0, };

static bool upload_data_packet(char *remote_address, uint16_t port, char* data, int data_length);
extern struct netif *nrc_netif[2];

static struct {
	char remote_addr[MAX_STATIC_IP_LENGTH+1];
	uint16_t remote_port;
} remote_info;

static void prepare_test_data(char *remote_addr)
{
	ip_addr_t server;
	test_data[0] = START_MARKER;
	test_data[127] = END_MARKER;

	test_data[1] = nrc_netif[0]->ip_addr.addr >> 24;
	ipaddr_aton(remote_addr, &server);
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
	(void)pvParameters;

	prepare_test_data(remote_info.remote_addr);

	while (1) {
		upload_data_packet((char *)remote_info.remote_addr, remote_info.remote_port,
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
		/* nrc_uart_write sends maximum of 16 bytes at a time (can be partial) */
		bytes_sent = nrc_uart_write(ptr, remain);
		if (bytes_sent <= 0) {
			_delay_ms(1);
			continue;
		}
		remain -= bytes_sent;
		ptr += bytes_sent;
	}

	/* Avoid hanging forever */
	for (int t = 0; !nrc_uart_write_done(); t++) {
		if (t >= UART_TX_DONE_TIMEOUT_MS) {
			nrc_usr_print("[WARN] uart_transmit: write_done timeout\n");
			break;
		}
		_delay_ms(1);
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
	struct sockaddr_in *addr_in = (struct sockaddr_in *)&dest_addr;
	ip_addr_t remote_addr;
	int ret = 0;

	memset(&dest_addr, 0, sizeof(dest_addr));

	if (ipaddr_aton((char *)remote_address, &remote_addr)) {
		if (IP_IS_V4(&remote_addr)) {
			addr_in->sin_family = AF_INET;
			addr_in->sin_len = sizeof(struct sockaddr_in);
			addr_in->sin_port = htons(port);
			addr_in->sin_addr.s_addr = inet_addr(remote_address);
		} else {
#ifdef CONFIG_IPV6
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
		return false;
	}

	nrc_usr_print("[%s] Connecting to %s:%d...\n", __func__, remote_address, port);

	client_socket = socket(addr_in->sin_family, SOCK_STREAM, IPPROTO_TCP);
	if (client_socket < 0) {
		nrc_usr_print("Create socket failed\n");
		return false;
	}

	ret = connect(client_socket, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
	if (ret < 0) {
		nrc_usr_print("open_connection failed (errno=%d)\n", errno);
		close(client_socket);
		client_socket = -1;
		return false;
	}

	nrc_usr_print("[%s] Connected to %s:%d...\n", __func__, remote_address, port);
	return true;
}

/****************************************************************************
 * FunctionName : close_connection
 * Description  : shutdown connection and close socket
 *****************************************************************************/
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

/****************************************************************************
 * FunctionName : retry_tcp_connection
 * Description  : retry tcp connection for given address and port
 *****************************************************************************/
static bool retry_tcp_connection(char *remote_address, uint16_t port)
{
	if (!close_connection()) {
		return false;
	}

	if (!open_connection(remote_address, port)) {
		return false;
	}

	nrc_usr_print("Re-Connection to %s:%d succeeded.\n", remote_address, port);
	return true;
}

/****************************************************************************
 * FunctionName : send_socket_data
 * Description  : send data to remote target
 *****************************************************************************/
static bool send_socket_data(char *data, int data_length)
{
	int send_retry_count = 0;
	int send_len = 0;
	int remain_len = data_length;
	static uint64_t sent_count = 0;

	while (remain_len > 0) {
		send_len = send(client_socket, data, remain_len, 0);
		if (send_len < 0) {
			/* If socket got reset, reconnect rather than looping forever */
			if (send_retry_count < MAX_RETRY) {
				send_retry_count++;
				_delay_ms(1000);
				continue;
			}

			nrc_usr_print("[%s] send failed (errno=%d), MAX retry (%d) reached\n",
			              __func__, errno, send_retry_count);
			return false;
		}

		send_retry_count = 0;
		data += send_len;
		remain_len -= send_len;
	}

	sent_count++;
	nrc_usr_print("[%s] %llu, %d bytes sent...\n", __func__, sent_count, data_length);
	return true;
}

/****************************************************************************
 * FunctionName : upload_data_packet
 * Description  : attempt send; if fails, reconnect and retry
 *****************************************************************************/
static bool upload_data_packet(char *remote_address, uint16_t port, char *data, int data_length)
{
	bool bSuccess = false;
	int retryCount = 0;

	while (retryCount < MAX_RETRY) {
		bSuccess = send_socket_data(data, data_length);
		if (bSuccess) {
			return true;
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

	return false;
}

/****************************************************************************
 * FunctionName : tcp_to_uart_task
 * Description  : receive data from client_socket, and forward it to uart
 *****************************************************************************/
static void tcp_to_uart_task(void *pvParameters)
{
	(void)pvParameters;

	int ret = 0;
	int recv_len = 0;
	struct timeval select_timeout;
	fd_set fdRead;
	char recv_buffer[BUFFER_SIZE];

	/* setting select_timeout */
	select_timeout.tv_sec = 2;
	select_timeout.tv_usec = 0;

	while (1) {
		/* If socket is not connected yet, wait and retry */
		if (client_socket < 0) {
			_delay_ms(200);
			continue;
		}

		FD_ZERO(&fdRead);
		FD_SET(client_socket, &fdRead);

		ret = select(client_socket + 1, &fdRead, NULL, NULL, &select_timeout);

		if (ret > 0 && FD_ISSET(client_socket, &fdRead)) {
			FD_CLR(client_socket, &fdRead);

			recv_len = recv(client_socket, recv_buffer, BUFFER_SIZE, 0);
			if (recv_len <= 0) {
				nrc_usr_print("Receive failed, Trying to reconnect...\n");
				while (!retry_tcp_connection(remote_info.remote_addr, remote_info.remote_port)) {
					_delay_ms(2000);
				}
			} else {
				uart_transmit(recv_buffer, recv_len);
			}
		}
	}

	/* unreachable */
	vTaskDelete(NULL);
}

static void uart_to_tcp_task(void *pvParameters)
{
	(void)pvParameters;

	while (1) {
		if (ulTaskNotifyTake(pdTRUE, portMAX_DELAY) == 0) {
			continue;
		}

		xSemaphoreTake(sync_sem, portMAX_DELAY);
		if (send_buffer_size > 0) {
			if (upload_data_packet(remote_info.remote_addr, remote_info.remote_port,
			                       tcp_send_buffer, send_buffer_size)) {
				memset(tcp_send_buffer, 0, BUFFER_SIZE);
				send_buffer_size = 0;
			}
		}
		xSemaphoreGive(sync_sem);

		_delay_ms(10);
	}
}

/******************************************************************************
 * FunctionName : start_tcp_client
 * Description  : tcp client
 * Parameters   : server address and port
 * Returns      : 0 or -1 (0: success, -1: fail)
 *******************************************************************************/
nrc_err_t start_tcp_client(char *remote_addr, uint16_t remote_port)
{
	int count;

	/* Connect to tcp server */
	for (count = 0; count < MAX_RETRY; count++) {
		if (open_connection((char *)remote_addr, remote_port)) {
			nrc_usr_print("[%s] Connection successful.\n", __func__);
			break;
		}

		if ((count + 1) >= MAX_RETRY) {
			nrc_usr_print("[%s] Connection failed for remote %s.\n", __func__, remote_addr);
			return -1;
		}

		_delay_ms(1000);
	}

	sync_sem = xSemaphoreCreateMutex();

	xTaskCreate(tcp_to_uart_task, "tcp_to_uart", 2048,
	            NULL, uxTaskPriorityGet(NULL), NULL);

	xTaskCreate(uart_to_tcp_task, "uart_to_tcp", 2048,
	            NULL, uxTaskPriorityGet(NULL), &uart_tcp_task_handle);

#ifdef UART_TEST_DATA
	xTaskCreate(generate_test_data_task, "Test data sender", 1024,
	            NULL, uxTaskPriorityGet(NULL), NULL);
#endif

	return 0;
}

void uart_data_receive(char *buf, int len)
{
	/* Upload data to tcp server */
	if (client_socket < 0) {
		/* not connected yet */
		return;
	}

	if (!buf || len <= 0) {
		return;
	}

	xSemaphoreTake(sync_sem, portMAX_DELAY);

	/* Prevent overflow */
	if (send_buffer_size + len > BUFFER_SIZE) {
		nrc_usr_print("[%s] tcp_send_buffer overflow: dropping (%d + %d)\n",
		              __func__, send_buffer_size, len);
		send_buffer_size = 0;
		memset(tcp_send_buffer, 0, BUFFER_SIZE);
		xSemaphoreGive(sync_sem);
		return;
	}

	memcpy(tcp_send_buffer + send_buffer_size, buf, len);
	send_buffer_size += len;

	/* when end marker is found, notify uart_tcp_task */
	if ((uint8_t)buf[len - 1] == END_MARKER) {
		xTaskNotifyGive(uart_tcp_task_handle);
	}

	xSemaphoreGive(sync_sem);
}

/******************************************************************************
 * FunctionName : uart_handler_init
 * Description  : Set UART configurations
 * Returns      : 0 if success, -1 on failure
 *******************************************************************************/
int uart_handler_init(void)
{
	uart_dma_info_t info;

	memset(&info, 0, sizeof(info));

#if defined(NRC7292)
	info.uart.channel = NRC_UART_CH2;
#else
	info.uart.channel = NRC_UART_CH1;
#endif
	info.uart.baudrate = 9600;
	info.uart.data_bits = UART_DB8;
	info.uart.stop_bits = UART_SB1;
	info.uart.parity = UART_PB_NONE;
	info.uart.hfc = UART_HFC_DISABLE;
	info.rx_params.buf.addr = uart_rx_buffer;
	info.rx_params.buf.size = BUFFER_SIZE;
	info.rx_params.cb = uart_data_receive;

	return nrc_uart_dma_open(&info);
}

void uart_tcp_client_init(char *remote_addr, uint16_t remote_port)
{
	/* Safe copy */
	memset(remote_info.remote_addr, 0, sizeof(remote_info.remote_addr));
	strncpy(remote_info.remote_addr, remote_addr, sizeof(remote_info.remote_addr) - 1);
	remote_info.remote_port = remote_port;

	if (uart_handler_init()) {
		nrc_usr_print("** UART init failed **\n");
		return;
	}

	start_tcp_client(remote_info.remote_addr, remote_info.remote_port);
}
