/*
 * link_status.h
 *
 * Link status snapshot provider for OLED display and TCP JSON push server.
 *
 * - FreeRTOS safe (uses mutex internally)
 * - No UI/log side effects
 * - Provides local MAC and parent (AP BSSID) MAC when connected
 */

#ifndef __LINK_STATUS_H__
#define __LINK_STATUS_H__

#include <stdint.h>
#include <stdbool.h>
#include "nrc_types.h"

typedef struct {
	uint8_t	connected;			/* WIFI_STATE_* */
	int		hop;				/* Current hop number */
	int		ap_count;			/* Neighbor AP count */
	int		rssi;				/* dBm */

	uint8_t	mac[6];		/* Local (STA) MAC */
	uint8_t	parent_mac[6];		/* Parent AP BSSID (valid if connected) */
	uint8_t	parent_valid;		/* 1 if parent_mac is valid */
} link_status_t;

void	link_status_init(void);
bool	link_status_get(link_status_t *out);
nrc_err_t start_link_status_update(void);

#endif /* __LINK_STATUS_H__ */
