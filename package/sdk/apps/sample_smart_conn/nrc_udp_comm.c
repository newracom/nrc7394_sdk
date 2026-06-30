/*
 * MIT License
 *
 * Copyright (c) 2025 Newracom, Inc.
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

#include "multi_role_util.h"
#include "multi_role_config.h"

#include "nrc_udp_comm.h"
#include "app_debug.h"

#include "wifi_provision.h"
#include "api_smart_conn.h"


struct server_task_param {
	uint16_t port;
};
static struct server_task_param server_param;

#define UDP_RX_RINGBUF_SIZE 512

static uint8_t udp_rx_buf[UDP_RX_RINGBUF_SIZE];

extern uint8_t unicast_on;

ATTR_NC static void udp_parse_and_dispatch(uint8_t byte)
{

}

ATTR_NC void udp_server_task(void *pvParameters) {
	struct server_task_param *param = (struct server_task_param *)pvParameters;

	if (!param) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "Invalid parameters to udp_server_task\n");
		vTaskDelete(NULL);
	}

	struct sockaddr_in serveraddr, clientaddr;
	int sockfd = -1;
	int ret = 0;
	socklen_t clientlen = sizeof(clientaddr);
	fd_set read_set;
	int recved_len;
	int i;

	// Create a socket
	if( (sockfd = socket(AF_INET , SOCK_DGRAM , 0)) < 0)  {
		app_log(DEBUG_LEVEL_ERROR,  NULL, "Unable to create socket. Errno: %d\n");
		vTaskDelete(NULL);
	}

	// Enable broadcast support
	int enable = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &enable, sizeof(enable)) < 0) {
		app_log(DEBUG_LEVEL_ERROR,  NULL, "Failed to set SO_BROADCAST. Errno: %d\n", errno);
		close(sockfd);
		vTaskDelete(NULL);
	}

	// Configure server address
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_len = sizeof(struct sockaddr_in);
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(param->port);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// Bind the socket to the specified port
	if (bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0){
		app_log(DEBUG_LEVEL_ERROR,  NULL, "Unable to bind socket. Errno: %d\n", errno);
		close(sockfd);
		vTaskDelete(NULL);
	}

	app_log(DEBUG_LEVEL_ALWAYS, NULL, "UDP Server on port %d]\n", param->port);

	uint8_t rx_buf[2048];

	while (1) {
		// Initialize the file descriptor set
		FD_ZERO(&read_set);
		FD_SET(sockfd, &read_set);

		// Wait for data using select
		ret = select(sockfd + 1, &read_set, NULL, NULL, NULL);
		if (ret < 0) {
			app_log(DEBUG_LEVEL_ERROR, NULL, "Select failed. Errno: %d\n", errno);
			_delay_ms(10);
			continue;
		}

		if (FD_ISSET(sockfd, &read_set)) {
			for (recved_len = 0,  i = 0 ; ; recved_len += ret, i++)
			{
				memset(&clientaddr, 0, sizeof(clientaddr));

				// Receive data from client
				ret = recvfrom(sockfd, rx_buf, sizeof(rx_buf), MSG_DONTWAIT,
						(struct sockaddr *) &clientaddr, &clientlen);

				if (ret <= 0) {
					//app_log(DEBUG_LEVEL_ALWAYS, NULL, "[%s] i=%d len=%d\n", __func__, i, recved_len);
					if (ret < 0 && errno != EAGAIN) {
						app_log(DEBUG_LEVEL_ERROR, NULL, "[%s] %s (%d)\n", __func__, strerror(errno), errno);
					}
					break;
				}

				app_debug_print_hex(DEBUG_LEVEL_WARN, (const uint8_t *)rx_buf, ret, (const uint8_t *)"UdpServer");

				for (int i = 0; i < ret; i++) {
					udp_parse_and_dispatch(rx_buf[i]);
				}
			}
		}
	}
	shutdown(sockfd, SHUT_RDWR);
	close(sockfd);
	vTaskDelete(NULL);
}

nrc_err_t start_udp_server(uint16_t port, server_input_handler input_handler)
{
	server_param.port = port;

	if (xTaskCreate(udp_server_task, "udp_server", 1024,
			(void *)&server_param, USER_APP_TASK_PRIORITY, NULL) != pdPASS) {
		app_log(DEBUG_LEVEL_ERROR, NULL,"Failed to create UDP server task\n");
		return NRC_FAIL;
	}

	return NRC_SUCCESS;
}

void calculate_broadcast_ip(struct netif *netif, char *broadcast_ip, size_t ip_size)
{
	struct in_addr broadcast_addr;

	// Compute broadcast address: (IP & Netmask) | (~Netmask)
	broadcast_addr.s_addr = (netif_ip_addr4(netif)->addr & netif_ip_netmask4(netif)->addr) | ~netif_ip_netmask4(netif)->addr;

	// Convert back to string form
	if (inet_ntop(AF_INET, &broadcast_addr, broadcast_ip, ip_size) == NULL) {
		app_log(DEBUG_LEVEL_ERROR, NULL,"Failed to convert broadcast address to string\n");
		return;
	}
}

static int dest_sockfd = -1;

static int init_send_socket()
{
	int opt = 1;

	if (dest_sockfd != -1) {
		return dest_sockfd;  // Return the existing socket if it's already initialized
	}

	// Create a socket
	if ((dest_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		app_log(DEBUG_LEVEL_ERROR, NULL,"Unable to create socket. Errno: %d\n", errno);
		return -1;
	}

	// Enable reuse address.
	if (setsockopt(dest_sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "Failed to set SO_REUSEADDR, Errno: %d\n", errno);
		close(dest_sockfd);
		dest_sockfd = -1;
		return -1;
	}
	// Enable broadcast support
	if (setsockopt(dest_sockfd, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt)) < 0) {
		app_log(DEBUG_LEVEL_ERROR, NULL,"Failed to set SO_BROADCAST. Errno: %d\n", errno);
		close(dest_sockfd);
		dest_sockfd = -1;
		return -1;
	}

	return dest_sockfd;
}

int sendto_network(const char *ip, uint16_t remote_port, const void  *message, size_t size, bool unicast)
{
	static uint32_t seq = 0;
	const int retry_max = 100;
	const int retry_interval = 10; /* ms */
	system_role_t role = get_system_type();
	struct sockaddr_in peer;
	int ret = -1;
	int i;

	if (role != ROLE_SOFTAP) {
		int vif_id = (role == ROLE_RELAY) ? 1 : 0;

		if (nrc_wifi_get_state(vif_id) != WIFI_STATE_CONNECTED) {
			app_log(DEBUG_LEVEL_INFO, NULL,"[%s] not connected\n", __func__);
			return -1;
		}
		if (get_current_hop() == -1) {
			app_log(DEBUG_LEVEL_INFO, NULL, "[%s] path lost\n", __func__);
			return -1;
		}
	}

	// Initialize the socket if it's not already initialized
	if (dest_sockfd == -1) {
		if (init_send_socket() == -1) {
			return -1;  // Initialization failed
		}
	}

	memset(&peer, 0, sizeof(peer));
	peer.sin_family = AF_INET;
	peer.sin_port = htons(remote_port);

	if (!inet_aton(ip, &peer.sin_addr)) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "[%s] Invalid IP address: %s\n", __func__, ip);
		return -1;
	}

	for (i = 0 ; i < retry_max ; i++) {
		// Send message to the server
		if (role == ROLE_RELAY) {
			ret = sendto_if(dest_sockfd, message, size, MSG_DONTWAIT,
							(struct sockaddr *)&peer, sizeof(peer),
							nrc_netif_get_by_idx(BRIDGE_INTERFACE));
		} else {
			ret = sendto(dest_sockfd, message, size, MSG_DONTWAIT,
						(struct sockaddr *)&peer, sizeof(peer));
		}

		if (ret > 0)
		{
//			app_log(DEBUG_LEVEL_INFO, NULL,"[%s] seq=%u len=%d\n", __func__, seq++, ret);
			break;
		}
		else if (errno != ENOMEM && errno != EAGAIN)
		{
			app_log(DEBUG_LEVEL_ERROR, NULL,"[%s] %s (%d)\n", __func__, strerror(errno), errno);
			break;
		}

		app_log(DEBUG_LEVEL_ERROR, NULL,"[%s] seq=%u retry %d/%d\n", __func__, seq, i + 1, retry_max);

		_delay_ms(retry_interval);
	}

	if (ret > 0)
		return 0;
	else
	{
		return -1;
	}
}
