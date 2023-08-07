/*
 * Copyright (c) 2016-2023 Newracom, Inc.
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

#include "system_common.h"
#include "system_modem_api.h"
#include "lmac_common.h"
#include "driver_nrc.h"
#include "driver_nrc_tx_agg.h"
//#include "umac_info.h"

#if defined (INCLUDE_AMPDU_AUTO_TX)
#define AUTO_TX_DBG_EN	(0)
/* 0: Disable, 1:Important ,2: Flow, 3:Details  */

#if (AUTO_TX_DBG_EN)
#define X(lvl, ...) \
	do { \
		if (lvl <= AUTO_TX_DBG_EN) { \
			A(__VA_ARGS__); \
		} \
	} while (0);

#else
#define X(lvl, ...)
#endif /* (AUTO_TX_DBG_EN) */

#define FN __func__
#endif /* defined(INCLUDE_AMPDU_AUTO_TX) */



// addba response timeout 50msec due to heavy traffic case such as iperf
#define ADDBA_RESP_TOUT  50000

#define HT_AGG_MAX_RETRIES		15
#define HT_AGG_BURST_RETRIES	3
#define HT_AGG_RETRIES_PERIOD	(15 * ADDBA_RESP_TOUT)

void nrc_stop_tx_ba_session(uint8_t vif_id, struct nrc_wpa_sta *sta, uint8_t tid)
{
	if (!sta->ampdu_mlme.tid_tx[tid]){
		return;
    }
	os_free(sta->ampdu_mlme.tid_tx[tid]);
	sta->ampdu_mlme.tid_tx[tid] = NULL;
	system_modem_tx_ampdu_control(vif_id, LMAC_AMPDU_TX_OFF, sta->addr, tid);
	X(3, "%s Done stop BA "MACSTR" tid %d \n",FN, MAC2STR(sta->addr) ,tid);
}

int nrc_check_ampdu_mlme_tx_resources(uint8_t vif_id, struct nrc_wpa_sta *sta)
{
	for(int i = 0; i < MAX_TID; i ++ ){
		nrc_stop_tx_ba_session(vif_id, sta, i);
	}
	X(3, "%s Free ampdu mlme tx resource - "MACSTR"\n",FN, MAC2STR(sta->addr));
	return 0;
}

static void nrc_tx_send_addba(uint8_t vif_id, struct nrc_wpa_sta * sta,
													struct tid_ampdu_tx *tid_tx)
{
	u8 tid = tid_tx->tid;
	if ( nrc_send_addba_req(vif_id, tid, sta->addr) > CMD_RET_SUCCESS){
		X(3, "%s FAIL: Send ADDBA "MACSTR" tid %d \n",FN,MAC2STR(sta->addr) ,tid);
		return;
	}
	sta->ampdu_mlme.addba_req_num[tid]++;
	sta->ampdu_mlme.last_addba_req_time[tid] = TSF;
	tid_tx->state = AMPDU_SES_TRIGGERED;
	X(3, "%s sent ADDBA "MACSTR" tid %d TSF:%d \n",FN,MAC2STR(sta->addr) ,tid, sta->ampdu_mlme.last_addba_req_time[tid]);
}


int nrc_tx_start_ba_session(uint8_t vif_id, struct nrc_wpa_sta * sta, uint8_t tid, uint16_t timeout)
{
	struct tid_ampdu_tx *tid_tx = NULL;
	int ret = 0;
	X(3, "%s ADDBA req for "MACSTR" tid %d \n",FN , MAC2STR(sta->addr), tid);

	if (sta->ampdu_mlme.addba_req_num[tid] > HT_AGG_MAX_RETRIES) {
		return -EBUSY;
	}

	if (sta->ampdu_mlme.addba_req_num[tid] > HT_AGG_BURST_RETRIES &&
	    (TSF > sta->ampdu_mlme.last_addba_req_time[tid] + HT_AGG_RETRIES_PERIOD)) {
		X(3, "%s ADDBA req denied - %d failed on "MACSTR" tid %d \n",
			FN, sta->ampdu_mlme.addba_req_num[tid], MAC2STR(sta->addr), tid);
		return -EBUSY;
	}

	if(sta->ampdu_mlme.tid_tx[tid] == NULL){
		tid_tx = os_zalloc(sizeof(struct tid_ampdu_tx));
		if (!tid_tx) {
			return -ENOMEM;
		}

		tid_tx->timeout = timeout;
		tid_tx->tid = tid;
		sta->ampdu_mlme.tid_tx[tid] = tid_tx;
	}else{
		tid_tx = sta->ampdu_mlme.tid_tx[tid];
	}

	sta->ampdu_mlme.dialog_token_allocator++;
	tid_tx->dialog_token = sta->ampdu_mlme.dialog_token_allocator;

	nrc_tx_send_addba(vif_id, sta, tid_tx);
	return ret;
}

void nrc_tx_check_aggr(uint8_t vif_id, struct nrc_wpa_sta * sta, uint8_t tid, uint8_t ac)
{
	if(tid > MAX_TID ){
		return ;
	}

	if (sta->block_ack[tid] & BLOCK_ACK_TX){
		//X(3, "%s Already Created : TID(%d) AID(%d) "MACSTR" \n",FN, tid, sta->aid, MAC2STR(sta->addr));		
		return;
	}

	if((sta->ampdu_mlme.tid_tx[tid]) && (sta->ampdu_mlme.tid_tx[tid]->state == AMPDU_SES_TRIGGERED) )
	{
		uint32_t cur_t = TSF;
		uint32_t addba_resp_tout = (sta->ampdu_mlme.last_addba_req_time[tid] + ADDBA_RESP_TOUT);
		if( (cur_t < addba_resp_tout)){
	 		X(3, "%s TID(%d): ADDBA req is ongoing \n",FN ,tid);		
			return;
		}
	}
	nrc_tx_start_ba_session(vif_id, sta, tid, 0);
}


