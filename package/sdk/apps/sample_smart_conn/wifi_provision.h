#ifndef WIFI_PROVISION_H
#define WIFI_PROVISION_H

#include <stdint.h>
#include "nvs.h"
#include "lwip/ip4_addr.h"

#define CONFIG_MSG_MAGIC 0xA5A5A5A5
#define CONFIG_MSG_TYPE_UPDATE 1
#define CONFIG_MSG_TYPE_REBOOT 2
#define CONFIG_MSG_TYPE_FACTORYRESET 3

#define CONFIG_FLAG_ACK_REQUEST 0x01
#define CONFIG_FLAG_ACK_REPLY   0x02

#define COMM_PORT 5000
#define ACK_PORT  5001

#define KEEPALIVE_PORT 5002

#define MULTICAST_GROUP "239.255.0.1"
#define BROADCAST_IP "255.255.255.255"

#define MAX_CHILD_NODES 16

#define SA_LEN 3

#define DEVICE_EXT_SA
// Device structure
typedef struct {
	uint8_t mac[6];
	uint8_t sa[SA_LEN];
#ifdef DEVICE_EXT_SA
	uint8_t ext_sa[SA_LEN];
#endif
	ip4_addr_t ip;
	int config_updated;
	int reboot_acknowledged;
	int factoryreset_acknowledged;
	int active;
	TickType_t timestamp;
	uint32_t unicast_tx_count;
	uint32_t unicast_rx_count;
} device_info_t;

// Payload structure
typedef union {
	struct {
		char ssid[32];
		char password[64];
		uint8_t sender_mac[6];
		uint64_t timestamp;
	} config;
} config_payload_t;

// Message structure
typedef struct {
	uint32_t magic;
	uint8_t msg_type;
	uint8_t flags;
	uint16_t length;
	config_payload_t payload;
	uint32_t crc32;
} config_message_t;

typedef struct {
	uint8_t mac[6];
	ip4_addr_t ip;
	uint64_t timestamp;
} keepalive_pkt_t;

#ifdef __cplusplus
extern "C" {
#endif

extern uint8_t max_addressed_devices;

static inline uint8_t get_max_device (void)
{
	return max_addressed_devices;
}

uint32_t get_softap_ip();
device_info_t* get_device_list();
int get_device_count();
void print_device_list();
#define print_device_list_all()	print_device_list(-1)
void init_device_list (system_role_t role);
void child_status_check_task(void *pvParameters);
void prepare_config_message(config_message_t* msg, const char* ssid, const char* pw, int request_ack);
void prepare_reboot_message(config_message_t* msg, int request_ack);
void send_message_unicast(const ip4_addr_t* ip, const config_message_t* msg);
void send_message_multicast(const config_message_t* msg);

void softap_save_ssid_password(nvs_handle_t nvs_handle);
void send_reboot_sequence();
void send_factoryreset_sequence();
void ap_config_msg_task(void *pvParameters);
void sta_config_msg_task(void *pvParameters);

int device_list_get_active_count();
int device_list_get_reboot_ack_count();
int device_list_get_factoryreset_ack_count();
int device_list_update_active (const char *str_ip, const uint8_t mac[], const uint8_t sa[]);
void device_list_check_active (uint16_t *count);

void start_keepalive_server_task();
void start_keepalive_task();
#ifdef __cplusplus
}
#endif

#endif // WIFI_PROVISION_H
