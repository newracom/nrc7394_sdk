#include "nrc_sdk.h"
#include "nrc_lwip.h"
#include "lwip/sockets.h"
#include "lwip/etharp.h"
#include "dhcpserver.h"
#include "multi_role_config.h"
#include "multi_role_util.h"
#include "multi_role_stats.h"

#include "app_debug.h"
#include "drv_rtc.h"

extern nvs_handle_t nvs_handle;

/* Helper function to correctly match bridge interface */
/* Assumption is the relay will have the same mac address as softap interface except 4th octet. */
static int compare_mac_special(uint8_t *addr1, uint8_t *addr2, size_t len)
{
	if (!addr1 || !addr2) {
		return -1;
	}

	for (int i = 0; i < len; i++) {
		if (i == 3) {
			continue;
		}
		if (addr1[i] != addr2[i]) {
			return -1;
		}
	}
	return 0;
}

nrc_err_t get_station_rssi_snr(uint8_t *addr, uint8_t *snr_ap, int8_t *rssi_ap)
{
	if (!snr_ap || !rssi_ap) {
		app_log(DEBUG_LEVEL_ERROR,  NULL, "[%s] Invalid input parameters\n", __func__);
		return NRC_FAIL;
	}

	*snr_ap = 0;
	*rssi_ap = 0;
	system_role_t role = get_system_type();
	STA_LIST list;

	if (role == ROLE_SOFTAP || role == ROLE_RELAY) {
		if (nrc_wifi_softap_get_sta_list(WLAN0_INTERFACE, &list, sizeof(list)) == WIFI_SUCCESS) {
			for (int i = 0; i < list.total_num; i++) {
				if (compare_mac_special(list.sta[i].addr, addr, 6) == 0) {
					*snr_ap = list.sta[i].snr;
					*rssi_ap = list.sta[i].rssi;
					return NRC_SUCCESS;
				}
			}
		}

		if (role == ROLE_RELAY) {
			nrc_wifi_get_snr(WLAN1_INTERFACE, snr_ap);
			nrc_wifi_get_rssi(WLAN1_INTERFACE, rssi_ap);
			return NRC_SUCCESS;
		}
	}

	if (role == ROLE_STATION) {
		nrc_wifi_get_snr(WLAN0_INTERFACE, snr_ap);
		nrc_wifi_get_rssi(WLAN0_INTERFACE, rssi_ap);
		return NRC_SUCCESS;
	}

	return NRC_FAIL;
}


/* Calculate CRC16-CCITT (polynomial 0x1021) */
ATTR_NC uint16_t calculate_crc16(const uint8_t *data, size_t length)
{
	uint16_t crc = 0x0000;
	for (size_t i = 0; i < length; ++i) {
		crc ^= ((uint16_t)data[i]) << 8;
		for (int j = 0; j < 8; ++j) {
			if (crc & 0x8000) {
				crc = (crc << 1) ^ 0x1021;
			} else {
				crc <<= 1;
			}
		}
	}

	return crc;
}

uint64_t get_tsf_timestamp()
{
	uint64_t tsf = 0;
	uint32_t *low;
	uint32_t *high;

	low = (uint32_t *) &tsf;
	high = low + 1;

	*high = lmac_get_tsf_h(0); // Get the high part of the TSF for the interface 0
	*low = lmac_get_tsf_l(0); // Get the low part of the TSF for the interface 0

	return tsf;
}

bool get_network_info(system_role_t system_type, ip4_addr_t *ip_addr, uint8_t *addr)
{
	int if_index;
	if(system_type == ROLE_RELAY) {
		if_index = BRIDGE_INTERFACE;
	} else {
		if_index = WLAN0_INTERFACE;
	}

	struct netif *netif = nrc_netif_get_by_idx(if_index);

	if (netif == NULL) {
		app_log(DEBUG_LEVEL_ERROR,  NULL, "[%s] Invalid if_index: %d\n", __func__, if_index);
		return false;
	}

	memcpy(addr, netif->hwaddr, NETIF_MAX_HWADDR_LEN);

#if LWIP_IPV4
	*ip_addr = netif->ip_addr;
#else
	ip4_addr_set_zero(ip_addr);
#endif /* LWIP_IPV4 */

	return true;
}

int build_packet_with_comm_header(uint8_t *dest_buf, const uint8_t *payload, int payload_len)
{
	if (!dest_buf || !payload || payload_len == 0) {
		return 0;
	}

	static uint64_t seq = 1;
	size_t header_size = sizeof(struct comm_header);
	size_t total_size = header_size + payload_len;

	struct comm_header *header = (struct comm_header *)dest_buf;
	WIFI_CONFIG *config = get_system_config();

	if (!config || !config->ssid) {
		return 0;
	}

	memset(header->ssid, 0, MAX_SSID_LENGTH);
	memcpy(header->ssid, config->ssid, strlen((char *)config->ssid));
	header->system_type = get_system_type();
	header->seq = seq++;
	header->tsf = get_tsf_timestamp();
	header->etag_id = 0;

	if (!get_network_info(header->system_type, &header->ip_addr, header->addr)) {
		return 0;
	}

	memcpy(dest_buf + header_size, payload, payload_len);

	return total_size;
}

void parsing_packet_with_comm_header(struct comm_header *header)
{
	if (!header) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "[%s] Null header\n", __func__);
		return;
	}

	uint64_t current = get_tsf_timestamp();
	uint64_t latency = (current >= header->tsf) ? (current - header->tsf) : 0;
	system_role_t role = get_system_role(nvs_handle);
	uint8_t snr = 0;
	int8_t rssi = 0;

	app_log(DEBUG_LEVEL_INFO, NULL,
		"[E-%04d] From %s(%02X:%02X:%02X:%02X:%02X:%02X) (type: %s) on \"%s\", seq: %llu, latency: %llu ms\n",
		header->etag_id,
		ip4addr_ntoa(&header->ip_addr),
		header->addr[0], header->addr[1], header->addr[2],
		header->addr[3], header->addr[4], header->addr[5],
		(header->system_type == ROLE_SOFTAP)  ? "SOFTAP" :
		(header->system_type == ROLE_STATION) ? "STATION" :
		(header->system_type == ROLE_RELAY)   ? "RELAY"   : "UNKNOWN",
		header->ssid,
		header->seq,
		latency / 1000);

	if (role == ROLE_STATION &&
		get_station_rssi_snr((uint8_t *)header->addr, &snr, &rssi) == NRC_SUCCESS) {
		app_log(DEBUG_LEVEL_INFO, NULL,
			"\t %s(%02X:%02X:%02X:%02X:%02X:%02X) snr:%d rssi:%d\n",
			ip4addr_ntoa(&header->ip_addr),
			header->addr[0], header->addr[1], header->addr[2],
			header->addr[3], header->addr[4], header->addr[5], snr, rssi);
	}

	uint8_t sa_addr[3];
	memcpy(sa_addr, (uint8_t *)header + sizeof(struct comm_header) + 3, 3);
	track_client((struct comm_header *)header, sa_addr, snr, rssi);
}

ATTR_NC void _delay_us(uint64_t duration_us)
{
	const uint64_t BUSY_WAIT_THRESHOLD_US = 1500;
	const float CORRECTION_FACTOR = 1.0f;

	uint64_t corrected_busy_wait_us = (uint64_t)(duration_us * CORRECTION_FACTOR);
	uint64_t start = drv_rtc_get_us();
	uint64_t end = start + corrected_busy_wait_us;

	if (duration_us > BUSY_WAIT_THRESHOLD_US) {
		uint64_t sleep_us = duration_us - BUSY_WAIT_THRESHOLD_US;
		vTaskDelay(pdMS_TO_TICKS((sleep_us + 999) / 1000));  // Round up to nearest ms
	}

	while (drv_rtc_get_us() < end) {
		__asm__ volatile ("nop");
	}
}


