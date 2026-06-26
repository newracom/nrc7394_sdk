/*
 * MIT License
 *
 * Copyright (c) 2025 Newracom, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#ifndef __NRC_API_TEST_H__
#define __NRC_API_TEST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "nrc_types.h"
#include "nrc_sdk.h"

/**********************************************
 * @fn	tWIFI_STATUS nrc_test_set_channel_freq_bw(int vif_id,
 *												 uint32_t freq_100k,
 *												 uint8_t bw)
 *
 * @brief Configure RF channel using frequency and bandwidth,
 *		  then apply TX LPF settings.
 *
 * @param vif_id: Network interface index
 *
 * @param freq_100k: Frequency in 100 kHz units
 *
 * @param bw: Bandwidth
 *
 * @return If success, then WIFI_SUCCESS.
 *		   Otherwise, error code(tWIFI_STATUS) is returned.
 *
 ***********************************************/
tWIFI_STATUS nrc_test_set_channel_freq_bw(int vif_id,
										  uint32_t freq_100k,
										  uint8_t bw);


/**********************************************
 * @fn	tWIFI_STATUS nrc_test_set_cont_tx_config(int vif_id,
 *												 uint8_t bw,
 *												 uint8_t mcs,
 *												 uint8_t txpwr,
 *												 uint8_t type,
 *												 uint32_t interval)
 *
 * @brief Configure continuous TX parameters without changing frequency.
 *
 * @param vif_id: Network interface index
 *
 * @param bw: Bandwidth
 *
 * @param mcs: Modulation and Coding Scheme
 *
 * @param txpwr: Transmit power
 *
 * @param type: Transmission type
 *
 * @param interval: Transmission interval
 *
 * @return If success, then WIFI_SUCCESS.
 *		   Otherwise, error code(tWIFI_STATUS) is returned.
 ***********************************************/
tWIFI_STATUS nrc_test_set_cont_tx_config(int vif_id,
										 uint8_t bw,
										 uint8_t mcs,
										 uint8_t txpwr,
										 uint8_t type,
										 uint32_t interval);

/**********************************************
 * @fn  tWIFI_STATUS nrc_test_set_packet_cnt(int packet_cnt)
 *
 * @brief Set packet count for modem RF test operations.
 *
 * @param packet_cnt: Number of packets to transmit.
 *                    0 means infinite transmission.
 *                    A positive value means transmission stops
 *                    after the specified number of packets.
 *
 * @return If success, then WIFI_SUCCESS.
 *         Otherwise, error code(tWIFI_STATUS) is returned.
 *
 ***********************************************/
tWIFI_STATUS nrc_test_set_packet_cnt(int packet_cnt);

/**********************************************
 * @fn  int nrc_test_get_packet_cnt(void)
 *
 * @brief Get Remaining packet count to target packet count
 *
 * @return Remaining packet count value.
 *
 ***********************************************/
int nrc_test_get_packet_cnt(void);


/**********************************************
 * @fn	void nrc_test_cont_tx_start(void)
 *
 * @brief Start continuous transmission.
 ***********************************************/
void nrc_test_cont_tx_start(void);


/**********************************************
 * @fn	void nrc_test_cont_tx_stop(uint8_t vif_id)
 *
 * @brief Stop continuous transmission.
 *
 * @param vif_id: Network interface index
 ***********************************************/
void nrc_test_cont_tx_stop(uint8_t vif_id);


/**********************************************
 * @fn	int nrc_test_get_rx_count(void)
 *
 * @brief Get received packet count in test mode.
 *
 * @return RX packet count
 ***********************************************/
int nrc_test_get_rx_count(void);


/**********************************************
 * @fn	void nrc_test_clear_rx_count(void)
 *
 * @brief Clear received packet count in test mode.
 *
 * @return void
 ***********************************************/
void nrc_test_clear_rx_count(void);


/**********************************************
 * @fn	tWIFI_STATUS nrc_test_set_enable_rssi_snr_wo_conn(int vif_id, bool enable)
 *
 * @brief Enable or disable RSSI and SNR measurement without connection.
 *
 * @param vif_id: Network interface index
 *
 * @param enable: true to enable, false to disable
 *
 * @return If success, then WIFI_SUCCESS.
 *		   Otherwise, error code(tWIFI_STATUS) is returned.
 ***********************************************/
tWIFI_STATUS nrc_test_set_enable_rssi_snr_wo_conn(int vif_id,
												  bool enable);


/**********************************************
 * @fn	tWIFI_STATUS nrc_test_get_rssi_wo_conn(int vif_id, int8_t *rssi)
 *
 * @brief Get the RSSI from the latest packet without connection.
 *
 * @param vif_id: Network interface index
 *
 * @param rssi: Pointer where RSSI value will be stored (dB)
 *
 * @return If success, then WIFI_SUCCESS.
 *		   Otherwise, error code(tWIFI_STATUS) is returned.
 ***********************************************/
tWIFI_STATUS nrc_test_get_rssi_wo_conn(int vif_id, int8_t *rssi);


/**********************************************
 * @fn	tWIFI_STATUS nrc_test_get_snr_wo_conn(int vif_id, uint8_t *snr)
 *
 * @brief Get the SNR (Signal-to-Noise Ratio) from the latest packet
 *		  without connection.
 *
 * @param vif_id: Network interface index
 *
 * @param snr: Pointer to a variable where the SNR value will be stored (dB)
 *
 * @return If success, then WIFI_SUCCESS.
 *		   Otherwise, error code(tWIFI_STATUS) is returned.
 *
 * @note SNR measurement must be enabled via
 *		 nrc_test_set_enable_rssi_snr_wo_conn().
 ***********************************************/
tWIFI_STATUS nrc_test_get_snr_wo_conn(int vif_id, uint8_t *snr);

#ifdef __cplusplus
}
#endif

#endif /* __NRC_API_TEST_H__ */
