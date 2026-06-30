#include "nrc_sdk.h"
#include "nrc_lwip.h"
#include "lwip/sockets.h"
#include "multi_role_config.h"
#include "nrc_ps_api.h"
#include "api_bcast_fota.h"
#include "sample_smart_conn_version.h"
#include "wifi_user_config.h"
#include "app_debug.h"

#ifdef SUPPORT_BCAST_FOTA
#define TCP_UPSTREAM_PAYLOAD_SIZE 4096
static uint8_t payload[TCP_UPSTREAM_PAYLOAD_SIZE];

extern void get_standalone_macaddr(int vif_id, uint8_t *mac);

static int open_connection(char *remote_address, uint16_t port)
{
	struct sockaddr_in dest_addr;
	ip_addr_t remote_addr;
	int sockfd = -1;

	if (ipaddr_aton((char *) remote_address, &remote_addr)) {
		if (IP_IS_V4(&remote_addr)) {
			struct sockaddr_in *d_addr = (struct sockaddr_in *) &dest_addr;
			dest_addr.sin_family = AF_INET;
			dest_addr.sin_len = sizeof(struct sockaddr_in);
			dest_addr.sin_port = htons(port);
			dest_addr.sin_addr.s_addr = inet_addr(remote_address);
		}
		else {
			app_log(DEBUG_LEVEL_ERROR, NULL, "[%s] Unknown address type %s\n", __func__, remote_address);
			app_log(DEBUG_LEVEL_ERROR, NULL, "[%s] Enable IPv6 to handle IPv6 remote address...\n", __func__);
			return -1;
		}
	}
	else {
		app_log(DEBUG_LEVEL_ERROR, NULL, "[%s] Invalid IP address %s.\n", __func__, remote_address);
		return -1;
	}

	app_log(DEBUG_LEVEL_ALWAYS, NULL, "[%s] Connecting to %s port %d...\n", __func__,
					remote_address, port);

	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockfd < 0)
	{
		app_log(DEBUG_LEVEL_ERROR, NULL, "Create socket failed\n");
		return -1;
	}

	if (connect(sockfd, (struct sockaddr *) &dest_addr, sizeof(dest_addr)) < 0) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "Failed to connect to %s on port %d\n", remote_address, port);
		close(sockfd);
		sockfd = -1;
		return -1;
	}

	return sockfd;
}

static void close_connection(int sockfd)
{
	if(sockfd >= 0) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "close_connection :%d\n", sockfd);
		shutdown(sockfd, SHUT_RDWR);
		close(sockfd);
	}
}

static void bfota_report_task(void *pvParameters)
{
	int bfota_sockfd = -1;
	int vif = 0;

	while (1) {
		vif = (get_system_type() == ROLE_RELAY) ? WLAN1_INTERFACE : WLAN0_INTERFACE;
		if (nrc_wifi_get_state(vif) != WIFI_STATE_CONNECTED) {
			_delay_ms(2000);
			continue;
		}

		bfota_sockfd = open_connection((char *) BCAST_SERVER_URL, 3333);
		if (bfota_sockfd != -1) {
			uint8_t addr[6];
			uint16_t etag_id = nrc_sf_get_etag_id();
			char date[] = __DATE__;
			char time[] = __TIME__;
			get_standalone_macaddr(0,addr);

			app_log(DEBUG_LEVEL_ALWAYS, NULL, "[%s] Connection successful.\n", __func__);
			app_log(DEBUG_LEVEL_ALWAYS, NULL, "[%s] Sending broadcast FOTA report...\n", __func__);
			sprintf((char*)payload, "%02x:%02x:%02x:%02x:%02x:%02x, %d, %d.%d.%d, %s, %s",
					addr[0],addr[1],addr[2],addr[3],addr[4],addr[5],
					etag_id,
					SAMPLE_SMART_CONN_MAJOR, SAMPLE_SMART_CONN_MINOR, SAMPLE_SMART_CONN_PATCH,
					date, time);

			int send_len = send(bfota_sockfd, payload, TCP_UPSTREAM_PAYLOAD_SIZE, 0);
			if (send_len < 0)
				app_log(DEBUG_LEVEL_ALWAYS, NULL, "[%s] Send failed...\n", __func__);

			close_connection(bfota_sockfd);
			app_log(DEBUG_LEVEL_ALWAYS, NULL, "[%s] Closing connection.\n", __func__);

			vTaskDelete(NULL);
		}
		else {
			app_log(DEBUG_LEVEL_ALWAYS, NULL, "[%s] Retrying TCP connection.\n", __func__);
			_delay_ms(2000);
		}
	}
	vTaskDelete(NULL);
}

void init_broadcast_fota()
{
	nrc_bcast_fota_init();
	nrc_bcast_fota_enable(true);
	nrc_bcast_fota_set_mode(BC_FOTA_MODE_CONNECTED);

	/* Report success to the server once the broadcast FOTA is completed successfully. */
	if (nrc_ps_get_retention_info()->fota_done) {
		xTaskCreate(bfota_report_task, "broadcast fota task", configMINIMAL_STACK_SIZE, NULL, USER_APP_TASK_PRIORITY, NULL);
	}
}
#endif // SUPPORT_BCAST_FOTA
