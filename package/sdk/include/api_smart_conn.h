#ifndef __WIFI_SMART_CONNECTION__
#define __WIFI_SMART_CONNECTION__

#include <stdint.h>
#include "nrc_types.h"

#define SC_BSSID_LEN 6
#define SC_MAX_NODES 64

/* External structure for neighbor info (without ip_bitmap) */
typedef struct smart_connection_neighbor_info {
	int8_t current_hop;
	uint8_t bssid[SC_BSSID_LEN];
	int8_t rssi;
} smart_connection_neighbor_info_t;

/* External structure for blacklist info */
typedef struct smart_connection_blacklist_info {
	uint8_t conn_cnt;
	uint8_t bssid[SC_BSSID_LEN];
	uint64_t last_conn_time;
} smart_connection_blacklist_info_t;

typedef enum smart_connection_role {
	SC_ROLE_UNDEFINED = -1,
	SC_ROLE_ROOT,
	SC_ROLE_ROAMER
} smart_connection_role_t;

typedef struct smart_connection_param {
	int vif;                    	// Station VIF ID
	int ip_idx;                 	// IP interface index (IP address as a loop detection ID is important)
	smart_connection_role_t role;   // Role of the device (ROOT or ROAMER)
	uint16_t scan_interval;     	// Scan interval (sec)
	uint16_t scan_duration;     	// Scan duration (sec)
	uint32_t roam_conn_timeout;		// Connection timeout (ms)
	int8_t sig_margin;          	// Required signal improvement over current (dBm)
	int8_t sig_min;             	// Minimum signal strength to consider (dBm)
	uint32_t vendor_oui;        	// OUI for vendor IE
	uint8_t vendor_subcmd;      	// Subcommand for vendor IE
} smart_connection_param_t;

nrc_err_t start_smart_connection(smart_connection_param_t *new_param);
nrc_err_t stop_smart_connection(void);
int8_t get_current_hop(void);
int8_t get_neighbor_count(void);
int8_t get_blacklist_count(void);

/**
 * @brief Get the stored neighbor list (snapshot from last scan)
 * @param list Output array to store neighbor info
 * @param max_count Maximum number of entries to copy
 * @return Number of entries copied
 */
int smart_connection_get_neighbor_list(smart_connection_neighbor_info_t *list, int max_count);

/**
 * @brief Get the current blacklist
 * @param list Output array to store blacklist info
 * @param max_count Maximum number of entries to copy
 * @return Number of entries copied
 */
int smart_connection_get_blacklist(smart_connection_blacklist_info_t *list, int max_count);

#endif /* __WIFI_SMART_CONNECTION__ */
