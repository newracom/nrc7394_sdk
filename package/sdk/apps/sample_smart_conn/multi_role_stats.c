#include "nrc_sdk.h"
#include "multi_role_util.h"
#include "multi_role_stats.h"
#include "netif/etharp.h"
#include "app_debug.h"

static hash_map_t client_seq_map = {0};

// Hash function for MAC address
static uint32_t hash_function(const uint8_t *hwaddr)
{
	uint32_t hash = 0;
	for (int i = 0; i < 6; i++) {
		hash = (hash * 31) + hwaddr[i];
	}
	return hash % HASH_MAP_SIZE;
}

static client_entry_t *find_or_add_client(hash_map_t *map, struct comm_header *header, uint8_t *sa_addr)
{
	uint32_t hash = hash_function(header->addr);
	client_entry_t *entry = map->buckets[hash];

	// Traverse the linked list in the bucket
	while (entry) {
		if (memcmp(entry->addr, header->addr, 6) == 0) {
			return entry; // Found the client
		}
		entry = entry->next;
	}

	// If not found, create a new entry
	entry = (client_entry_t *)nrc_mem_malloc(sizeof(client_entry_t));
	if (!entry) {
		app_log(DEBUG_LEVEL_ALWAYS, NULL, "[ERROR] Memory allocation failed for client entry\n");
		return NULL;
	}

	// Direct initialization of the new client entry
	memcpy(entry->addr, header->addr, 6);
	memcpy(entry->ssid, header->ssid, MAX_SSID_LENGTH);
	memcpy(entry->sa_addr, sa_addr, 3);
	entry->ip_addr = header->ip_addr;
	entry->system_type = header->system_type;
	entry->etag_id = header->etag_id;
	entry->last_seq = 0;
	entry->missing_count = 0;
	entry->next = map->buckets[hash];
	map->buckets[hash] = entry;

	// Convert entry->addr to struct eth_addr
	struct eth_addr eth_mac;
	memcpy(eth_mac.addr, entry->addr, sizeof(eth_mac.addr));

	// Add static ARP entry
	if (etharp_add_static_entry((ip4_addr_t *)&entry->ip_addr, &eth_mac) != ERR_OK) {
		app_log(DEBUG_LEVEL_ALWAYS, NULL, "[ERROR] Failed to add static ARP entry for IP: %08X\n", entry->ip_addr);
	}

	return entry;
}

// Free all resources in the hash map
static void free_hash_map(hash_map_t *map)
{
	for (int i = 0; i < HASH_MAP_SIZE; i++) {
		client_entry_t *entry = map->buckets[i];
		while (entry) {
			client_entry_t *temp = entry;
			entry = entry->next;
			nrc_mem_free(temp);
		}
		map->buckets[i] = NULL;
	}
}

void track_client(struct comm_header *header, uint8_t* sa_addr, uint8_t snr, int8_t rssi)
{
	if (!header) {
		app_log(DEBUG_LEVEL_ALWAYS, NULL, "[ERROR] Invalid header provided.\n");
		return;
	}

	// Track sequence number for the client
	client_entry_t *client_entry = find_or_add_client(&client_seq_map, header, sa_addr);

	if (!client_entry) {
		app_log(DEBUG_LEVEL_ALWAYS, NULL, "[ERROR] Unable to track client %02X:%02X:%02X:%02X:%02X:%02X due to memory allocation failure.\n",
		header->addr[0], header->addr[1], header->addr[2], header->addr[3], header->addr[4], header->addr[5]);
		return;
	}

	client_entry->snr = snr;
	client_entry->rssi = rssi;
	uint64_t received_seq = header->seq;
	// Check for missing sequence numbers
	if (client_entry->last_seq != 0) {
		if (received_seq > client_entry->last_seq + 1) {
			uint64_t missing = received_seq - client_entry->last_seq - 1;
			client_entry->missing_count += missing;
			app_log(DEBUG_LEVEL_ALWAYS, NULL, "[WARNING] Missing %llu sequence(s) for client %s: Expected %llu, Received %llu\n",
						  missing, ip4addr_ntoa(&header->ip_addr), client_entry->last_seq + 1, received_seq);
		} else if (received_seq < client_entry->last_seq) {
			// Handle sequence reset or wraparound
			app_log(DEBUG_LEVEL_ALWAYS, NULL, "[INFO] Sequence number reset detected for client %s: Last %llu, Received %llu\n",
						  ip4addr_ntoa(&header->ip_addr), client_entry->last_seq, received_seq);
			client_entry->missing_count = 0; // Reset missing count
		}
	}

	// Update the last sequence number
	client_entry->last_seq = header->seq;
}

// Report the status of all tracked clients
void report_client_status(void)
{
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "\n\n[Client Status Report]\n");
	for (int i = 0; i < HASH_MAP_SIZE; i++) {
		client_entry_t *entry = client_seq_map.buckets[i];
		while (entry) {
			double loss_rate = 0.0;
			if (entry->last_seq > 0) {
				loss_rate = (entry->missing_count * 100.0) / (entry->last_seq + 1);
			}

			app_log(DEBUG_LEVEL_ALWAYS, NULL, "Client: %02X:%02X:%02X:%02X:%02X:%02X on \"%s\" type: %s, "
				"RSSI: %d, SNR: %u, Last Sequence: %llu, Missing: %llu (loss: %.2f%%), "
				"IP: %s SA_ADDR: %02X:%02X:%02X\n",
				entry->addr[0], entry->addr[1], entry->addr[2],
				entry->addr[3], entry->addr[4], entry->addr[5],
				entry->ssid,
				entry->system_type == ROLE_SOFTAP ? "SOFTAP" :
				entry->system_type == ROLE_STATION ? "STATION" :
				entry->system_type == ROLE_RELAY ? "RELAY" : "UNKNOWN",
				entry->rssi,
				entry->snr,
				entry->last_seq,
				entry->missing_count,
				loss_rate,
				ip4addr_ntoa(&entry->ip_addr),
				entry->sa_addr[0], entry->sa_addr[1], entry->sa_addr[2]);

			entry = entry->next;
		}
	}
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "[End of Report]\n\n");
}
