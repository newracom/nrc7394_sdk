/*
 * Copyright (c) 2016-2021 Newracom, Inc.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _DRIVER_NRC_TX_H_
#define _DRIVER_NRC_TX_H_

struct nrc_wpa_if;
struct nrc_wpa_sta;
struct nrc_wpa_key;
#if defined (INCLUDE_AMPDU_AUTO_TX)
typedef struct auto_agg_tx_conf_info {
	uint8_t		on : 1;
	uint8_t		max_agg_num : 5;
} tAUTO_AGG_TX_CONF;

void nrc_show_auto_aggr_tx(uint8_t vif_id);
int nrc_set_auto_aggr_tx(uint8_t vif_id, uint8_t tid, uint8_t max_agg_num);
void nrc_set_auto_aggr_tx_all(uint8_t vif_id);

#endif

struct bu_info {
	uint16_t len;
	uint16_t age;
	uint8_t *buf;
	int (*tx_cb)(SYS_BUF*);
	struct dl_list node;
};

struct bu_queue {
	TimerHandle_t 			timer;
	struct dl_list			list;
};

int nrc_transmit_from_8023(uint8_t vif_id,uint8_t *frame, const uint16_t len);
int nrc_transmit(struct nrc_wpa_if* intf, uint8_t *frm, const uint16_t len);
int nrc_transmit_pmf(struct nrc_wpa_if* intf, uint8_t *frm, const uint16_t len,
		const uint16_t data_len, struct nrc_wpa_key *wpa_key);
int nrc_transmit_from_8023_mb(uint8_t vif_id, uint8_t **frames, uint16_t len[], int n_frames);
int nrc_raw_transmit(struct nrc_wpa_if* intf, uint8_t *frm, const uint16_t len,
				const int ac);
int nrc_send_deauth(struct nrc_wpa_if *intf, const uint8_t *addr, uint16_t reason_code, bool report_status);
int nrc_send_action(int vif, uint8_t *addr, uint8_t *payload, uint16_t payload_len);
int nrc_send_action_tx_status(int vif, const uint8_t *dst, const uint8_t *src,
		const uint8_t *bssid, const uint8_t *payload, uint16_t payload_len, uint32_t wait);
int nrc_add_sec_hdr(struct nrc_wpa_key *key, uint8_t *pos);
int nrc_send_addba_req(int vif, int tid, uint8_t* addr);
int nrc_send_delba_req(int vif, int tid, uint8_t* addr);
void nrc_bu_queue_init(struct nrc_wpa_if* intf, struct nrc_wpa_sta *sta);
void nrc_bu_queue_deinit(struct nrc_wpa_if* intf, struct nrc_wpa_sta *sta);
void nrc_set_ps_state(struct nrc_wpa_sta *sta, bool pm);

#endif // _DRIVER_NRC_TX_H_
