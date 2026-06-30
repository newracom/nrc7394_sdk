/*
 * link_status.c
 *
 * Provides a single source of truth for link status (connected/hop/ap_count/rssi/snr)
 * plus local MAC and parent MAC (AP BSSID).
 *
 * This module is intended to be shared by:
 * - OLED display code
 * - TCP JSON push server
 */

#include "link_status.h"

#include <string.h>

#include "FreeRTOS.h"
#include "semphr.h"

#include "nrc_sdk.h"
#include "nrc_lwip.h"
#include "api_wifi.h"
#include "api_system.h"
#include "wifi_relay_service.h"
#ifdef LINK_STATUS_PUSH_CLIENT
#include "link_status_push_client.h"
#endif
#include "api_smart_conn.h"
#include "nvs.h"

#ifdef SUPPORT_SSD1306
#include "oled96.h"
#include "api_i2c.h"
#include "app_debug.h"
#endif
#ifdef PING_ON_WIFI_CONNECT
#include "ping_on_wifi_connect.h"
#endif


/* -------------------- Defaults / configuration -------------------- */

static int	g_sta_in_relay_vif_id = WLAN1_INTERFACE;
#if LWIP_BRIDGE
static int	g_self_netif_idx = BRIDGE_INTERFACE;
#else
static int	g_self_netif_idx = WLAN0_INTERFACE;
#endif

static link_status_t prev_st = {0};
static bool prev_init = false;
static uint8_t refresh_time_sec = 5;
static uint64_t  count = 0;

static SemaphoreHandle_t	g_link_mutex;

/* English comment: Forward declarations (provided elsewhere in your project). */
extern int8_t	get_current_hop(void);
extern int8_t	get_neighbor_count(void);

/* -------------------- Internal helpers -------------------- */

static void mac_zero(uint8_t mac[6])
{
	memset(mac, 0, 6);
}

static bool parse_mac_str(const char *s, uint8_t mac[6])
{
	unsigned int b[6];

	if (!s) {
		return false;
	}

	// Expect "AA:BB:CC:DD:EE:FF"
	if (sscanf(s, "%2x:%2x:%2x:%2x:%2x:%2x",
			   &b[0], &b[1], &b[2],
			   &b[3], &b[4], &b[5]) != 6) {
		return false;
	}

	for (int i = 0; i < 6; i++) {
		mac[i] = (uint8_t)b[i];
	}

	return true;
}

static bool get_mac_from_netif(int if_index, uint8_t mac_out[6])
{
	struct netif *netif = nrc_netif_get_by_idx(if_index);
	if (!netif) {
		return false;
	}

	if (netif->hwaddr_len != 6) {
		return false;
	}

	memcpy(mac_out, netif->hwaddr, 6);
	return true;
}

static void get_self_mac(uint8_t mac_out[6])
{
	mac_zero(mac_out);

	if (get_mac_from_netif(g_self_netif_idx, mac_out)) {
		return;
	}
}


/* -------------------- Public API -------------------- */

void link_status_init(void)
{
	if (g_link_mutex == NULL) {
		g_link_mutex = xSemaphoreCreateMutex();
	}

#ifdef LINK_STATUS_PUSH_CLIENT
	link_status_push_client_start();
#endif
}

bool link_status_get(link_status_t *out)
{
	const int neigh_cnt_max = 10;
	smart_connection_neighbor_info_t neigh[neigh_cnt_max];
	int neigh_cnt;
	int i;

	if (out == NULL) {
		return false;
	}

	if (g_link_mutex) {
		if (xSemaphoreTake(g_link_mutex, pdMS_TO_TICKS(50)) != pdTRUE) {
			return false;
		}
	}

	memset(out, 0, sizeof(*out));
	get_self_mac(out->mac);

	out->connected = nrc_wifi_get_state(g_sta_in_relay_vif_id);

	if (out->connected == WIFI_STATE_CONNECTED) {

		/* Hop / neighbor counts */
		out->hop = (int)get_current_hop();
		out->ap_count = (int)get_neighbor_count();

		/* Get neighbor list */
		neigh_cnt = smart_connection_get_neighbor_list(neigh, neigh_cnt_max);
		if (neigh_cnt < 0)
			neigh_cnt = 0;
		if (neigh_cnt > neigh_cnt_max)
			neigh_cnt = neigh_cnt_max;

		/* Parent MAC = AP BSSID */
		AP_INFO ap;
		if (nrc_wifi_get_ap_info(g_sta_in_relay_vif_id, &ap) == WIFI_SUCCESS) {
			memcpy(out->parent_mac, ap.bssid, 6);
			out->parent_valid = 1;
			out->rssi = 0; /* default */
			for (i = 0; i < neigh_cnt; i++) {
				if (memcmp(neigh[i].bssid, ap.bssid, 6) == 0) {
					out->rssi = neigh[i].rssi;
					break;
				}
			}
		} else {
			mac_zero(out->parent_mac);
			out->parent_valid = 0;
			out->rssi = 0;
		}

	} else {
		out->rssi = 0;
		out->hop = -1;
		out->ap_count = relay_get_scan_ap_count();
		mac_zero(out->parent_mac);
		out->parent_valid = 0;
	}

	if (g_link_mutex) {
		xSemaphoreGive(g_link_mutex);
	}

	return true;
}


void display_link_status(const link_status_t *st)
{
	char* ip_addr = NULL;
	char mac[18];
	char parent_mac[18];
	int disp_mode;

	if (!st) return;

	const char *conn_str = (st->connected == WIFI_STATE_CONNECTED) ? "CONN" : "DISC";
	VERSION_T* ver = nrc_get_app_version();

#ifdef SUPPORT_SSD1306
	oledFill(0);
	oledPrintf(0,0, FONT_NORMAL, "R:%d H:%2d A:%2d", st->rssi, st->hop, st->ap_count);
#endif
	printf("%s RSSI:%d H:%d AP:%d ", conn_str,  st->rssi, st->hop, st->ap_count);

	if (st->connected == WIFI_STATE_CONNECTED) {
#ifdef PING_ON_WIFI_CONNECT
		if(count == 0) {
			ping_on_wifi_connected_notify();
		}
#endif
		snprintf(mac, sizeof(mac), "%02X:%02X:%02X:%02X:%02X:%02X",
				 st->mac[0], st->mac[1], st->mac[2], st->mac[3], st->mac[4], st->mac[5]);
		snprintf(parent_mac, sizeof(parent_mac), "%02X:%02X:%02X:%02X:%02X:%02X",
				 st->parent_mac[0], st->parent_mac[1], st->parent_mac[2], st->parent_mac[3], st->parent_mac[4], st->parent_mac[5]);

		disp_mode = count % 3;

		if(disp_mode == 0) {
#ifdef SUPPORT_SSD1306
			oledPrintf(0, 1, FONT_NORMAL, "%02X%02X %02X%02X %02X%02X",
					 st->mac[0], st->mac[1], st->mac[2], st->mac[3], st->mac[4], st->mac[5]);
#endif
		} else if(disp_mode == 1) {
			struct netif *interface = nrc_netif_get_by_idx(BRIDGE_INTERFACE);
			if (interface != NULL) {
				ip_addr = ip4addr_ntoa(netif_ip4_addr(interface));
#ifdef SUPPORT_SSD1306
				oledPrintf(0, 1, FONT_NORMAL, "%s", ip_addr);
#endif
				printf("IP:%s ", ip_addr);
			}
		} else {
#ifdef SUPPORT_SSD1306
			if (ver) {
				oledPrintf(0, 1, FONT_NORMAL, "V: %u.%u.%u", ver->major, ver->minor, ver->patch);
			} else {
				oledPrintf(0, 1, FONT_NORMAL, "V: N/A");
			}
#endif
			printf("Ver: %u.%u.%u\n", ver->major, ver->minor, ver->patch);
		}

#ifdef SUPPORT_SSD1306
		oledPrintf(0, 3, FONT_NORMAL, "%02X%02X %02X%02X %02X%02X/P",
				 st->parent_mac[0], st->parent_mac[1], st->parent_mac[2], st->parent_mac[3], st->parent_mac[4], st->parent_mac[5]);
#endif
		printf("SELF:%s PARENT:%s ", mac, parent_mac);

		count++;
	}
	printf("\n");
}

void update_current_link_status(void)
{
	link_status_t st;

	if (!link_status_get(&st)) {
		return;
	}

	if (st.connected != WIFI_STATE_CONNECTED) {
		count = 0;
	}

    if (!prev_init) {
        display_link_status(&st);
        prev_st = st;
        prev_init = true;
        return;
    }

    if (memcmp(&st, &prev_st, sizeof(link_status_t)) != 0) {
        display_link_status(&st);
        prev_st = st;
    }
}

ATTR_NC void link_status_update_task(void *pvParameters)
{
	while (1) {
		update_current_link_status();
		_delay_ms(refresh_time_sec*1000);
	}
	vTaskDelete(NULL);
}

static void sta_wifi_event_handler(int vif, tWIFI_EVENT_ID event, int data_len, void *data)
{
	switch(event) {
		case WIFI_EVT_CONNECT_SUCCESS:
		case WIFI_EVT_DISCONNECT:
			update_current_link_status();
			break;
		default:
			break;
	}
}

nrc_err_t start_link_status_update(void)
{
	const uint8_t display_sda = 6;
	const uint8_t display_scl = 7;
	const uint8_t display_address= 0x3c;

#ifdef SUPPORT_SSD1306
	oledInit(display_sda, display_scl, I2C_MASTER_1,
		display_address, OLED_128x32, false, false);

	oledFill(0);
	oledPrintf(0,0, FONT_NORMAL, nrc_get_app_name());
	_delay_ms(1000);
#endif

	nvs_handle_t nvs_handle = 0;
	if (nvs_open(NVS_DEFAULT_NAMESPACE, NVS_READWRITE, &nvs_handle) != NVS_OK) {;
		return NRC_FAIL;
	}

	nvs_get_u8(nvs_handle, "refresh_time", &refresh_time_sec);
	nvs_close(nvs_handle);
	printf("refresh_time_sec : %d\n", refresh_time_sec);

	link_status_init();

	if (nrc_wifi_register_event_handler(1, sta_wifi_event_handler) != WIFI_SUCCESS){
		return NRC_FAIL;
	}

	if (xTaskCreate(link_status_update_task, "link_status_update_task", 1024,
			NULL, USER_APP_TASK_PRIORITY, NULL) != pdPASS) {
		return NRC_FAIL;
	}

#ifdef PING_ON_WIFI_CONNECT
	ping_on_wifi_connect_init();
	ping_on_wifi_connect_start();
#endif

	return NRC_SUCCESS;
}


