#ifndef __UDP_STATISTICS_H__
#define __UDP_STATISTICS_H__

#include "nrc_sdk.h"
#include "multi_role_util.h"
#include "lwip/ip4_addr.h"

#define HASH_MAP_SIZE 128 // Number of buckets in the hash map

typedef struct client_entry {
	uint8_t addr[6];
	uint8_t ssid[MAX_SSID_LENGTH];
	system_role_t system_type;
	ip4_addr_t ip_addr;
	uint16_t etag_id;
	uint8_t sa_addr[3];
	uint8_t snr;
	int8_t rssi;
	uint64_t last_seq;
	uint64_t missing_count;
	struct client_entry *next;
} client_entry_t;

typedef struct {
	client_entry_t *buckets[HASH_MAP_SIZE];
} hash_map_t;

void track_client(struct comm_header *header, uint8_t* sa_addr, uint8_t snr, int8_t rssi);
void report_client_status(void);

#endif // __UDP_STATISTICS_H__
