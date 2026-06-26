#ifndef LMAC_TEST_H
#define LMAC_TEST_H

#include "system_common.h"

#define TEST_MODE_LMAC	0
#define TEST_MODE_RC	1

#define TEST_PARAM_NO	0
#define TEST_PARAM_SNR	1

void lmac_test_init();
void lmac_test_tsf_handler();
bool lmac_test_timer_busy();
bool lmac_test_timer_start(uint32_t interval , int32_t (*cb)(void *param) );
void lmac_test_timer_stop();
bool lmac_test_set_freq_bw(uint8_t vif_id, uint32_t freq_100k, bw_t bw_idx);
#if defined(INCLUDE_MANUAL_CONT_TX_SUPPORT)
void lmac_test_stop(int vif_id);
bool lmac_test_set_config(uint8_t vif_id, bw_t bw_idx, uint8_t mcs, uint8_t txpwr, uint8_t type, uint32_t interval);
void lmac_test_start(void);

bool lmac_test_cont_tx(bool enable, uint32_t freq_100k, bw_t bw_idx, uint8_t mcs, uint8_t txpwr, uint8_t type, uint32_t interval);
bool lmac_test_sine_tx(bool enable, uint32_t freq_100k, bw_t bw_idx, uint8_t txpwr);
int8_t lmac_test_get_rssi_wo_conn(int vif_id);
int8_t lmac_test_get_rssi_avg_wo_conn(int vif_id);
uint8_t lmac_test_get_snr_wo_conn(int vif_id);
uint8_t lmac_test_get_snr_avg_wo_conn(int vif_id);
void lmac_test_set_rssi_wo_conn(int vif_id, int8_t rx_rssi, uint8_t snr);
bool lmac_test_get_enable_rx_rssi_snr();
void lmac_test_set_enable_rx_rssi_snr(bool enable);
#endif
int32_t test_on_timer(void *param);

#if defined(TEST_SBR)
bool get_sbr();
void set_sbr(bool v);
uint32_t * get_sbr_buffer();
uint32_t get_tsf_offset();
void set_tsf_offset(uint32_t offset);
uint32_t get_sbr_byte_length();
#endif

void set_lmac_test_report(uint8_t param);
uint8_t get_lmac_test_report();
void start_rx_gain_sweep_test();
void end_rx_gain_sweep_test();
bool is_run_rx_gain_sweep_test();
void set_run_rx_gain_auto_test(uint8_t v);
uint32_t get_rx_gain_start_tsf();
void set_rx_gain_start_tsf(uint32_t v);
uint8_t get_rx_gain_current();
void set_rx_gain_current(uint8_t v);
void add_rx_gain_current(int8_t v);
int8_t get_rx_gain_step();
void set_rx_gain_step(int8_t v);
uint8_t get_rx_gain_start();
void set_rx_gain_start(uint8_t v);
uint8_t get_rx_gain_end();
void set_rx_gain_end(uint8_t v);
uint32_t get_rx_gain_interval();
void set_rx_gain_interval(uint32_t v);
uint8_t get_rx_gain_change();
void set_rx_gain_change(uint8_t v);
uint8_t get_rx_gain_margin();
void set_rx_gain_margin(uint8_t v);
void set_rx_gain_min(uint8_t v);
void set_rx_gain_max(uint8_t v);
uint8_t get_rx_gain_min();
uint8_t get_rx_gain_max();

bool is_inifinite_txop_enabled();
bool get_emulated_per();
void set_emulated_per(bool v);
uint8_t get_per(int n);
uint8_t get_lmac_test_mode();
void add_test_tx_total_count(uint8_t mcs, int count);
int32_t lmac_test_get_packet_count();
void lmac_test_set_packet_count(int32_t v);
void inc_test_tx_fail_count(uint8_t mcs);
bool get_snr_print();
void set_snr_print(bool v);
uint8_t get_payload_type();
void set_payload_type(uint8_t v);
void set_dpd(bool v);
bool get_dpd();
int get_ac();
void set_no_backoff(bool v);
bool get_no_backoff();
void set_lpf_gain_control(bool v);
bool get_lpf_gain_control();
void esl_default_freq(uint32_t channel_freq, int bw);
#if defined(INCLUDE_MANUAL_CONT_TX_SUPPORT)
uint32_t get_interval();
#else
int32_t get_interval();
#endif

#endif /* LMAC_TEST_H */
