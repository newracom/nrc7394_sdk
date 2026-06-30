#ifndef __MULTI_ROLE_UTIL_H__
#define __MULTI_ROLE_UTIL_H__

#include "nrc_lwip.h"
#include "multi_role_config.h"

/* Communication header */
struct comm_header {
	uint64_t tsf;
	uint8_t ssid[MAX_SSID_LENGTH];
	uint64_t seq;
	uint8_t addr[6];
	ip4_addr_t ip_addr;
	system_role_t system_type;
	uint16_t etag_id;
} __attribute__((packed));

typedef struct generate_task_option{
	int32_t delay;
	uint16_t payload_length;
}generate_task_option_t;

int get_client_ip4addr(int client_sock, ip4_addr_t *ipaddr);

/* SoftAP : retrieve rssi and snr using client socket */
nrc_err_t get_station_sock_rssi_snr(int sock, uint8_t *snr_ap, int8_t *rssi_ap);

/* SoftAP : retrieve rssi and snr using client IP address */
nrc_err_t get_station_rssi_snr(uint8_t *addr, uint8_t *snr_ap, int8_t *rssi_ap);

/* Calculate CRC16-CCITT (polynomial 0x1021) */
uint16_t calculate_crc16(const uint8_t *data, size_t length);

/* Return WiFi TSF time */
uint64_t get_tsf_timestamp();


bool get_network_info(system_role_t system_type, ip4_addr_t *ip_addr, uint8_t *addr);
int build_packet_with_comm_header(uint8_t *dest_buf, const uint8_t *payload, int payload_len);
void parsing_packet_with_comm_header(struct comm_header *header);
void _delay_us(uint64_t duration_us);

/***********************************************************************/

#include "drv_rtc.h"

static inline void rtc_delay_us (uint64_t time_us)
{
	time_us += drv_rtc_get_us();
	while (drv_rtc_get_us() < time_us);
}
#define rtc_delay_ms(time_ms)   rtc_delay_us(time_ms * 1000)
#define rtc_get_time_us()       drv_rtc_get_us()
#define rtc_get_time_ms()       (drv_rtc_get_us() / 1000)

#endif /* __MULTI_ROLE_UTIL_H__ */
