/* multi_role_directory.h */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "multi_role_proto.h"
#include "multi_role_config.h"

#ifndef NRC_MAX_NODES
#define NRC_MAX_NODES	64
#endif

/* Provisioning / configuration ACK flags stored per node (root-side). */
#define DIR_PROV_FLAG_CONFIG_UPDATED		0x01
#define DIR_PROV_FLAG_REBOOT_ACK		0x02
#define DIR_PROV_FLAG_FACTORYRESET_ACK		0x04

typedef struct {
	uint32_t		node_id;
	uint8_t			mac[6];
	uint8_t			parent_mac[6];
	uint8_t			role;
	uint8_t			hop;

	/* Provisioning / config ACK tracking (root-side) */
	uint8_t			prov_flags;

	uint32_t		ipv4_addr;		/* NBO */
	uint32_t		fw_ver_packed;
	char			app_name[NRC_APP_NAME_MAX];	/* null-terminated */

	uint32_t		last_session_id;
	uint8_t			fota_status;
	uint8_t			progress_percent;

	/* For detecting stuck IN_PROGRESS and reducing log spam */
	uint8_t			last_fota_status_seen;
	uint8_t			last_fota_prog_seen;
	uint16_t		_rsvd1;
	uint32_t		last_status_ms;        /* last time we received a STATUS */
	uint32_t		last_fota_change_ms;   /* last time fota_status/progress/session changed */

	uint32_t		last_log_ms;          /* rate-limit REGISTER logs */

	uint32_t		last_seen_ms;
	uint32_t		last_register_ms;
	uint32_t		last_fw_change_ms;
	uint32_t		tfota_backoff_until_ms;
	bool			online;
	bool			valid;
} nrc_node_record_t;

typedef struct {
	nrc_node_record_t	nodes[NRC_MAX_NODES];
	uint16_t		count;
	uint32_t		dir_version;
	uint32_t		last_update_ms;
} nrc_node_directory_t;

/* Root-only init (others may no-op) */
void directory_init(system_role_t role);

/* Update on keepalive receive (optional) */
void directory_on_keepalive(const uint8_t mac[6],
			    uint32_t ipv4_addr_nbo);

/* Explicit registration from node */
void directory_on_register(const nrc_dir_register_t *reg);

/* Status update from node */
void directory_on_status(const nrc_dir_status_t *st);

/* Lightweight liveness heartbeat */
void directory_on_heartbeat(const nrc_dir_heartbeat_t *hb);

/* Compute or refresh hop based on parent relationships */
void directory_recompute_hops(void);

/* Snapshot for host */
int directory_get_list(nrc_dir_node_info_t *out, int max,
		       uint32_t *dir_version_out);

/* Convenience helpers (root-side) */
int directory_get_active_count(void);
int directory_get_config_updated_count(void);
int directory_get_reboot_ack_count(void);
int directory_get_factoryreset_ack_count(void);

bool directory_is_config_updated(const uint8_t mac[6]);
bool directory_is_reboot_acked(const uint8_t mac[6]);
bool directory_is_factoryreset_acked(const uint8_t mac[6]);

void directory_mark_config_updated(const uint8_t mac[6], bool on);
void directory_mark_reboot_ack(const uint8_t mac[6], bool on);
void directory_mark_factoryreset_ack(const uint8_t mac[6], bool on);

/* Clear provisioning flags on all nodes (mask = DIR_PROV_FLAG_*) */
void directory_clear_prov_flags_all(uint8_t mask);

/* Root control server (UDP register/status + TCP list query) */
void start_directory_server(system_role_t role);

void dir_dump_node(const nrc_node_record_t *n, const char *prefix);

nrc_node_directory_t *directory_get_dir();
