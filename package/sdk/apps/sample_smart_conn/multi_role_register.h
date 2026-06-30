/* multi_role_register.h */
#pragma once

#include <stdint.h>
#include "multi_role_config.h"
#include "multi_role_proto.h"

/* Called by user_init() on non-root nodes */
void tfota_try_register_later(void);

/* Common helpers */
uint32_t tfota_get_root_ip_nbo(void);
int tfota_get_self_mac(uint8_t mac[6]);

uint32_t make_node_id_from_mac(const uint8_t mac[6]);

/* Low-level senders (UDP -> root) */
int send_register_to_root(uint32_t root_ip_nbo,
						  const uint8_t self_mac[6],
						  const uint8_t parent_mac[6],
						  system_role_t role,
						  uint8_t hop,
						  uint32_t fw_ver_packed);

int send_status_to_root(uint32_t root_ip_nbo,
						const uint8_t self_mac[6],
						uint32_t node_id,
						uint32_t session_id,
						nrc_fota_status_t status,
						uint8_t progress_percent,
						uint32_t fw_ver_packed);

/* Lightweight liveness (UDP -> root). No ACK. */
int send_heartbeat_to_root(uint32_t root_ip_nbo,
						const uint8_t self_mac[6]);
