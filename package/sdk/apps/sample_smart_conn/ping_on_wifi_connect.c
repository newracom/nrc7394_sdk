#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"

#include "lwip/sockets.h"
#include "lwip/inet.h"
#include "lwip/ip4.h"
#include "nrc_ping.h"
#include "ping_task.h"

// -------------------- Config --------------------
#define PING_TARGET_IP_STR		"192.168.200.1"
#define PING_INTERVAL_MS		2000
#define PING_TIMEOUT_MS			500
#define PING_PAYLOAD_SIZE		16
#define PING_REPEAT_PERIOD_MS   (120000)   // 120 sec

#define WIFI_CONNECTED_BIT		(1U << 0)

// -------------------- Globals --------------------
static EventGroupHandle_t g_wifi_evt;

// -------------------- ICMP definitions (IPv4) --------------------
#define ICMP_ECHO			8
#define ICMP_ER				0

typedef struct {
	uint8_t	type;
	uint8_t	code;
	uint16_t chksum;
	uint16_t id;
	uint16_t seqno;
} icmp_echo_hdr_t;

static uint16_t inet_chksum(const void *dataptr, uint16_t len)
{
	const uint8_t *pb = (const uint8_t *)dataptr;
	uint32_t acc = 0;

	while (len > 1) {
		uint16_t w = (uint16_t)((pb[0] << 8) | pb[1]);
		acc += w;
		pb += 2;
		len -= 2;
	}
	if (len == 1) {
		acc += (uint16_t)(pb[0] << 8);
	}

	while (acc >> 16) {
		acc = (acc & 0xFFFF) + (acc >> 16);
	}
	return (uint16_t)~acc;
}


// -------------------- FreeRTOS task --------------------
void ping_on_wifi_connect_task(void *arg)
{
	(void)arg;

	printf("[PING_TASK] start\r\n");

	for (;;) {
		// Wait for Wi-Fi connected.
		(void)xEventGroupWaitBits(g_wifi_evt,
								 WIFI_CONNECTED_BIT,
								 pdFALSE,
								 pdTRUE,
								 portMAX_DELAY);

		printf("[PING_TASK] WIFI connected\r\n");

		// While connected: ping once every 120 seconds (stop-on-success).
		while (xEventGroupGetBits(g_wifi_evt) & WIFI_CONNECTED_BIT) {
			ip_addr_t target_addr;
			if (!ipaddr_aton(PING_TARGET_IP_STR, &target_addr)) {
				printf("[PING_TASK][ERR] invalid target: %s\r\n", PING_TARGET_IP_STR);
				vTaskDelay(pdMS_TO_TICKS(1000));
				continue;
			}

			if (ping_get_session(&target_addr) != NULL) {
				// Session already running -> wait until it ends or Wi-Fi disconnects.
				while ((xEventGroupGetBits(g_wifi_evt) & WIFI_CONNECTED_BIT) &&
					   (ping_get_session(&target_addr) != NULL)) {
					vTaskDelay(pdMS_TO_TICKS(200));
				}
				// If disconnected, break out to outer loop.
				if (!(xEventGroupGetBits(g_wifi_evt) & WIFI_CONNECTED_BIT)) {
					break;
				}
			}

			ping_parm_t *p = ping_init_parameters();
			if (!p) {
				printf("[PING_TASK][ERR] ping_init_parameters failed\r\n");
				vTaskDelay(pdMS_TO_TICKS(1000));
				continue;
			}

			// Set target and interval.
			p->addr = target_addr;
			p->interval = PING_INTERVAL_MS;
			p->target_count = 100000;

			// Stop when first success occurs (so this becomes "ping once until success").
			p->stop_on_success = 1;

			ping_mutex_init();

			printf("[PING_TASK] ping %s (stop on success)\r\n", PING_TARGET_IP_STR);

			p->ping_thread = ping_init((void *)p);
			if (p->ping_thread.thread_handle == NULL) {
				printf("[PING_TASK][ERR] ping_init failed\r\n");
				ping_deinit_parameters(p);
				vTaskDelay(pdMS_TO_TICKS(1000));
				continue;
			}

			// Wait for this ping session to end (success or other stop),
			// but break early if Wi-Fi disconnects.
			while ((xEventGroupGetBits(g_wifi_evt) & WIFI_CONNECTED_BIT) &&
				   (ping_get_session(&target_addr) != NULL)) {
				vTaskDelay(pdMS_TO_TICKS(200));
			}

			// If disconnected, go back to waiting for next connection.
			if (!(xEventGroupGetBits(g_wifi_evt) & WIFI_CONNECTED_BIT)) {
				break;
			}

			// Sleep 120 seconds before next "one-shot until success" run.
			vTaskDelay(pdMS_TO_TICKS(PING_REPEAT_PERIOD_MS));
		}

		printf("[PING_TASK] WIFI disconnected\r\n");
	}
}

// -------------------- Hook from Wi-Fi event handler --------------------
void ping_on_wifi_connect_init(void)
{
	if (g_wifi_evt == NULL) {
		g_wifi_evt = xEventGroupCreate();
	}
}

// Call these in your Wi-Fi event handler:
void ping_on_wifi_connected_notify(void)
{
	xEventGroupSetBits(g_wifi_evt, WIFI_CONNECTED_BIT);
}

// Start task
void ping_on_wifi_connect_start(void)
{
	if (xTaskCreate(ping_on_wifi_connect_task,
					  "ping_wifi",
					  1024,
					  NULL,
					  USER_APP_TASK_PRIORITY,
					  NULL) != pdPASS) {
		printf("Failed to create ping_wifi\n");
	}
}
