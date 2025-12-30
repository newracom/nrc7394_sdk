#include "nrc_sdk.h"
#include "nrc_lwip.h"
#include "wifi_config_setup.h"
#include "wifi_connect_common.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_APS 100 // Adjust if needed
#define MAX_VIE_DATA_SIZE 256 // Adjust this if needed based on expected VIE size
#define MAX_EVENTS 100  // Maximum stored Vendor IE events

// RSSI difference between connected AP and new scan AP.
#define RSSI_MARGIN 20

// Vendor IE pattern definition (Updated as required)
static uint8_t vendor_ie_pattern[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDD };  // Correct format
static size_t vendor_ie_pattern_len = sizeof(vendor_ie_pattern);

// Structure to store information about each AP
typedef struct {
	uint8_t bssid[6];
	int rssi;
	char ssid[33];
	char *vendor_ie_data;
	size_t vendor_ie_len;
	uint8_t security_scheme; // Store the security scheme (e.g., WPA2, WPA3)
} AP_Info;

// List of discovered APs
static AP_Info ap_list[MAX_APS];
static int ap_count = 0;

// Structure to store Vendor IE data with BSSID
typedef struct {
	vendor_ie_bcn_t vendor_ie_bcn;
	uint8_t bssid[6];
} VendorIEData;

// Buffers to store Vendor IE events and scan results
static VendorIEData vendor_ie_data_buffer[MAX_EVENTS];
static int vendor_ie_data_count = 0;

static volatile int scan_complete = 0;  // Flag to indicate scan completion
static volatile int connect_in_progress = 0; // flag to indicate scan and connection attempt is in progress.

static WIFI_CONFIG wifi_config;

static nrc_err_t scan_and_connect(WIFI_CONFIG *param, int initial);
static void wifi_event_handler(int vif, tWIFI_EVENT_ID event, int data_len, void *data);

// Convert BSSID string with colons to raw byte format.
static void convert_bssid_to_bytes(const char *bssid_str, uint8_t *bssid_bytes)
{
	for (int i = 0; i < 6; i++) {
		sscanf(bssid_str + i * 3, "%2hhx", &bssid_bytes[i]);
	}
}

static bool is_matching_vendor_ie(vendor_ie_bcn_t *vendor_ie_bcn, uint8_t *vendor_ie_pattern, size_t vendor_ie_pattern_len) {
	if (vendor_ie_bcn == NULL || vendor_ie_bcn->vie_data == NULL) {
		nrc_usr_print("Vendor IE or data is NULL, skipping...\n");
		return false;
	}
	if (memcmp(vendor_ie_bcn->vie_data, vendor_ie_pattern, vendor_ie_pattern_len) == 0) {
		nrc_usr_print("Vendor IE Match Found! BSSID: " MACSTR "\n", MAC2STR(vendor_ie_bcn->bssid));
		return true;
	}
	nrc_usr_print("Vendor IE does not match expected pattern. Skipping AP.\n");
	return false;
}

static bool add_ap_to_list(vendor_ie_bcn_t *vendor_ie_bcn, SCAN_RESULTS *results, int i) {
	// Check if AP is already in the list
	for (int j = 0; j < ap_count; j++) {
		if (memcmp(ap_list[j].bssid, results->result[i].bssid, 6) == 0) {
			nrc_usr_print("AP already in the list, skipping: %s\n", results->result[i].bssid);
			return false;  // Duplicate BSSID
		}
	}

	if (ap_count >= MAX_APS) {
		nrc_usr_print("AP list is full! Cannot add more APs.\n");
		return false;
	}

	// Copy BSSID and other AP info
	convert_bssid_to_bytes(results->result[i].bssid, ap_list[ap_count].bssid);
	ap_list[ap_count].rssi = atoi(results->result[i].sig_level);
	strncpy(ap_list[ap_count].ssid, results->result[i].ssid, sizeof(ap_list[ap_count].ssid)-1);
	ap_list[ap_count].ssid[sizeof(ap_list[ap_count].ssid)-1] = '\0';

	// Assign Vendor IE data pointer (which now points to our persistent copy)
	if (vendor_ie_bcn) {
		ap_list[ap_count].vendor_ie_data = (char*)vendor_ie_bcn->vie_data;
		ap_list[ap_count].vendor_ie_len = vendor_ie_bcn->vie_len;
	} else {
		nrc_usr_print("Warning: Vendor IE data is NULL for AP %s\n", results->result[i].bssid);
	}
	ap_list[ap_count].security_scheme = results->result[i].security;

	nrc_usr_print("Added AP to list: SSID: %s, BSSID: " MACSTR ", RSSI: %d, Security: %d\n",
				  ap_list[ap_count].ssid, MAC2STR(ap_list[ap_count].bssid), ap_list[ap_count].rssi, ap_list[ap_count].security_scheme);

	ap_count++;
	return true;
}

static AP_Info* find_strongest_ap()
{
	if (ap_count == 0) {
		return NULL;  // No APs found
	}
	AP_Info *strongest_ap = &ap_list[0];
	for (int i = 1; i < ap_count; i++) {
		if (ap_list[i].rssi > strongest_ap->rssi) {
			strongest_ap = &ap_list[i];
		}
	}
	return strongest_ap;
}

static void scan_and_connect_task(void *pvParameters)
{
	WIFI_CONFIG *param = (WIFI_CONFIG *)pvParameters;

	while (scan_and_connect(param, 0) != NRC_SUCCESS) {
		int retry_delay = 10; // second
		nrc_usr_print("Reconnect: Not connected, trying again in %d sec\n", retry_delay);
		_delay_ms(10 * 1000);
	}

	vTaskDelete(NULL);
}

static void ip_check_task(void *pvParameters)
{
	int ip_set_timeout = 60; // in second

	if (nrc_wait_for_ip(WLAN0_INTERFACE, ip_set_timeout) == NRC_FAIL) {
		nrc_usr_print("DHCP client timed out waiting for %d sec\n", ip_set_timeout);
	}

	vTaskDelete(NULL);
}

// Unified event handler for Vendor IE and scan done events.
static void wifi_event_handler(int vif, tWIFI_EVENT_ID event, int data_len, void *data)
{
	if (event == WIFI_EVT_VENDOR_IE) {
		vendor_ie_bcn_t* vendor_ie_bcn = (vendor_ie_bcn_t*) data;
		if (vendor_ie_bcn == NULL || vendor_ie_bcn->vie_data == NULL) {
			return;  // Ignore invalid events
		}
		 // Check if we already stored a vendor IE for this BSSID.
		for (int k = 0; k < vendor_ie_data_count; k++) {
			if (memcmp(vendor_ie_data_buffer[k].bssid, vendor_ie_bcn->bssid, 6) == 0) {
				// Already have vendor IE for this BSSID; skip storing this duplicate.
				return;
			}
		}
		if (vendor_ie_data_count < MAX_EVENTS) {
			// Copy the BSSID
			memcpy(vendor_ie_data_buffer[vendor_ie_data_count].bssid, vendor_ie_bcn->bssid, 6);
			// Copy the structure
			memcpy(&vendor_ie_data_buffer[vendor_ie_data_count].vendor_ie_bcn, vendor_ie_bcn, sizeof(vendor_ie_bcn_t));
			// Allocate persistent memory for the vendor IE data and copy it.
			size_t len = vendor_ie_bcn->vie_len;
			char *vie_copy = nrc_mem_malloc(len);
			if (vie_copy) {
				memcpy(vie_copy, vendor_ie_bcn->vie_data, len);
				vendor_ie_data_buffer[vendor_ie_data_count].vendor_ie_bcn.vie_data = vie_copy;
			} else {
				nrc_usr_print("Failed to allocate memory for vendor IE data copy.\n");
				return;
			}
			vendor_ie_data_count++;
		} else {
			nrc_usr_print("Vendor IE data buffer is full!\n");
		}
	} else if (event == WIFI_EVT_SCAN_DONE) {
		scan_complete = 1;  // Mark scan as complete
	} else if (event == WIFI_EVT_DISCONNECT) {
		if (!connect_in_progress) {
			nrc_usr_print("Scan and Connect Task starting...\n");
			xTaskCreate(scan_and_connect_task, "Scan and Connect Task", 1024, &wifi_config, uxTaskPriorityGet(NULL)-1, NULL);
		}
	} else if (event == WIFI_EVT_CONNECT_SUCCESS) {
		nrc_usr_print("Connected to '%s' (BSSID: %s)\n", wifi_config.ssid, wifi_config.bssid);
		xTaskCreate(ip_check_task, "IP check Task", 1024, NULL, uxTaskPriorityGet(NULL)-1, NULL);
	}
}

static SCAN_RESULTS saved_results;   // Local copy of scan results

// Scan for APs and select the best one based on Vendor IE and RSSI.
static nrc_err_t scan_and_select_ap_with_vendor_ie(uint8_t *vendor_ie_pattern, size_t vendor_ie_pattern_len, AP_Info *selected_ap)
{
	memset(selected_ap, 0, sizeof(AP_Info));

	// Set scan_complete to false (0)
	scan_complete = 0;

	nrc_usr_print("Starting Wi-Fi scan...\n");
	if (nrc_wifi_scan(WLAN0_INTERFACE) != WIFI_SUCCESS) {
		nrc_usr_print("Error: Wi-Fi scan failed.\n");
		return NRC_FAIL;
	}
	while (!scan_complete) {
		_delay_ms(10);
	}

	SCAN_RESULTS results;
	if (nrc_wifi_scan_results(WLAN0_INTERFACE, &results) != WIFI_SUCCESS) {
		nrc_usr_print("Error: Wi-Fi scan results retrieval failed.\n");
		return NRC_FAIL;
	}

	// Limit number of results to MAX_SCAN_RESULTS
	saved_results.n_result = (results.n_result > MAX_SCAN_RESULTS) ? MAX_SCAN_RESULTS : results.n_result;
	memcpy(saved_results.result, results.result, saved_results.n_result * sizeof(SCAN_RESULT));
	nrc_usr_print("Stored %d scan results for processing.\n", saved_results.n_result);

	ap_count = 0;  // Reset AP list

	for (int i = 0; i < saved_results.n_result; i++) {
		uint8_t scan_bssid[6];
		convert_bssid_to_bytes(saved_results.result[i].bssid, scan_bssid);
		for (int j = 0; j < vendor_ie_data_count; j++) {
			if (memcmp(scan_bssid, vendor_ie_data_buffer[j].bssid, 6) == 0) {
				vendor_ie_bcn_t *vendor_ie_bcn = &vendor_ie_data_buffer[j].vendor_ie_bcn;
				nrc_usr_print("Processing Vendor IE for BSSID: " MACSTR "\n", MAC2STR(scan_bssid));

				/* First 3 bytes in vie_data is OUI, so skip 3 then compare */
				/* vie_data format : OUI(3), SUBCMD(1), DATA */
				if (memcmp(vendor_ie_bcn->vie_data + 3, vendor_ie_pattern, vendor_ie_pattern_len) == 0) {
					if (!add_ap_to_list(vendor_ie_bcn, &saved_results, i)) {
						nrc_usr_print("Error: Failed to add AP to list.\n");
						continue;
					}
				}
			}
		}
	}

	if (ap_count == 0) {
		return NRC_FAIL;
	}

	AP_Info *strongest_ap = find_strongest_ap();
	if (strongest_ap == NULL) {
		nrc_usr_print("Error: No AP found after filtering.\n");
		return NRC_FAIL;
	}

	memcpy(selected_ap, strongest_ap, sizeof(AP_Info));
	nrc_usr_print("Selected AP: SSID: %s, BSSID: " MACSTR ", RSSI: %d, Security: %d\n",
				  selected_ap->ssid, MAC2STR(selected_ap->bssid), selected_ap->rssi, selected_ap->security_scheme);

	ap_count = 0;

	for (int i = 0; i < vendor_ie_data_count; i++) {
		if (vendor_ie_data_buffer[i].vendor_ie_bcn.vie_data != NULL) {
			nrc_mem_free((void*)vendor_ie_data_buffer[i].vendor_ie_bcn.vie_data);
			vendor_ie_data_buffer[i].vendor_ie_bcn.vie_data = NULL;
		}
	}
	vendor_ie_data_count = 0;

	return NRC_SUCCESS;
}

// Connect to an AP that matches the Vendor IE.
static nrc_err_t scan_and_connect(WIFI_CONFIG *param, int initial)
{
	AP_Info selected_ap;

	memset(&selected_ap, 0, sizeof(AP_Info));

	connect_in_progress = 1;

	if (scan_and_select_ap_with_vendor_ie(vendor_ie_pattern, vendor_ie_pattern_len, &selected_ap) == NRC_SUCCESS) {
		strcpy((char *) param->ssid, selected_ap.ssid);
		sprintf((char *) param->bssid, MACSTR, MAC2STR(selected_ap.bssid));

		if (!initial) {
			nrc_wifi_auto_reconnect(WLAN0_INTERFACE, 0);
			nrc_wifi_set_ssid(WLAN0_INTERFACE, (char *) param->ssid);
			nrc_wifi_set_bssid(WLAN0_INTERFACE, (char *) param->bssid);
			if (nrc_wifi_select_network(WLAN0_INTERFACE) == WIFI_SUCCESS) {
				connect_in_progress = 0;
				return NRC_SUCCESS;
			} else {
				return NRC_FAIL;
			}
		} else {
			nrc_wifi_auto_reconnect(WLAN0_INTERFACE, 0);
			if (wifi_connect(param) != WIFI_SUCCESS) {
				nrc_usr_print("Failed to connect to AP: %s.\n", param->ssid);
				connect_in_progress = 0;
				return NRC_FAIL;
			}
		}
	} else {
		nrc_usr_print("No suitable AP found with Vendor IE.\n");
		connect_in_progress = 0;
		return NRC_FAIL;
	}

	connect_in_progress = 0;
	return NRC_SUCCESS;
}

// Periodically scan for a better AP with Vendor IE.
static void periodic_scan_and_connect_task(void *pvParameters)
{
	WIFI_CONFIG *param = (WIFI_CONFIG *) pvParameters;
	AP_Info selected_ap;
	memset(&selected_ap, 0, sizeof(AP_Info));

	while (1) {
		_delay_ms(60000);
		if (connect_in_progress) {
			continue;
		} else {
			connect_in_progress = 1;
		}

		int8_t rssi_ap = 0;
		if (nrc_wifi_get_rssi(WLAN0_INTERFACE, &rssi_ap) != WIFI_SUCCESS) {
			connect_in_progress = 0;
			continue;
		}

		nrc_usr_print("Current AP RSSI: %d\n", rssi_ap);
		if (scan_and_select_ap_with_vendor_ie(vendor_ie_pattern, vendor_ie_pattern_len, &selected_ap) == NRC_SUCCESS) {
			if (selected_ap.rssi > rssi_ap + RSSI_MARGIN) {
				if (nrc_wifi_disconnect(WLAN0_INTERFACE, 5000) != WIFI_SUCCESS) {
					connect_in_progress = 0;
					continue;
				}

				// Select network associated with network interface to enable association.
				nrc_wifi_auto_reconnect(WLAN0_INTERFACE, 0);
				strcpy((char *) param->ssid, selected_ap.ssid);
				sprintf((char *) param->bssid, MACSTR, MAC2STR(selected_ap.bssid));

				nrc_usr_print("Switching to AP: %s, BSSID: %s.\n", param->ssid, param->bssid);
				nrc_wifi_set_ssid(WLAN0_INTERFACE, (char *) param->ssid);
				nrc_wifi_set_bssid(WLAN0_INTERFACE, (char *) param->bssid);
				if (nrc_wifi_select_network(WLAN0_INTERFACE) != WIFI_SUCCESS) {
					nrc_usr_print("Failed to select network.\n");
				}
			} else {
				nrc_usr_print("Not Switching : Current AP RSSi (%d), New RSSI (%d), RSSI margin (%d)\n",
							  rssi_ap, selected_ap.rssi, RSSI_MARGIN);
			}
		}
		connect_in_progress = 0;
	}
	vTaskDelete(NULL);
}

// Initialize the system.
void user_init(void)
{
	nrc_usr_print("Initializing Vendor IE AP connection sample...\n");
	memset(&wifi_config, 0x0, sizeof(WIFI_CONFIG));
	nrc_wifi_set_config(&wifi_config);

	if (wifi_init(&wifi_config) != WIFI_SUCCESS) {
		nrc_usr_print("Wi-Fi initialization failed.\n");
		return;
	}
	nrc_wifi_register_event_handler(WLAN0_INTERFACE, wifi_event_handler);
	// For initial connect, and second parameter to 1 indicating the firmst connection attempt.
	while (scan_and_connect(&wifi_config, 1) != NRC_SUCCESS) {
		int retry_delay = 10; // second
		nrc_usr_print("Not connected, trying again in %d sec\n", retry_delay);
		_delay_ms(10 * 1000);
	}
	xTaskCreate(periodic_scan_and_connect_task, "Periodic Scan Task", 1024, &wifi_config, uxTaskPriorityGet(NULL), NULL);
}
