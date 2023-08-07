/*********************************************************************/
/*    Newracom Library / IP Product                                  */
/*    Product Name :                                                 */
/*    Version      :                                                 */
/*    Author       :                                                 */
/*    Update       :                                                 */
/*********************************************************************/

#ifndef __REG_PHY_DFE_DBE_H__
#define __REG_PHY_DFE_DBE_H__

#ifdef __cplusplus
extern "C"{
#endif

// 0x4008A000 register ------------------------------------
typedef struct {
    uint32_t                                        r2_reg_tx_chpos                      :2 ;
    uint32_t                                        reserved0                            :30;
}   PHY_DFE_DBE_AH_TX_DFE_LPF00;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_TX_DFE_LPF00                     b;
}   PHY_DFE_DBE_AH_TX_DFE_LPF00_U;


// 0x4008A004 register ------------------------------------
typedef struct {
    uint32_t                                        r_reg_tx_dig_mix                     :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_AH_TX_DFE_LPF01;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_TX_DFE_LPF01                     b;
}   PHY_DFE_DBE_AH_TX_DFE_LPF01_U;


// 0x4008A008 register ------------------------------------
typedef struct {
    uint32_t                                        r_reg_tx_upplow_swap                 :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_AH_TX_DFE_LPF02;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_TX_DFE_LPF02                     b;
}   PHY_DFE_DBE_AH_TX_DFE_LPF02_U;


// 0x4008A010 register ------------------------------------
typedef struct {
    uint32_t                                        r_reg_tx1m_use2m                     :1 ;
    uint32_t                                        reserved0                            :3 ;
    uint32_t                                        r_reg_sel_1m_iir                     :1 ;
    uint32_t                                        reserved1                            :27;
}   PHY_DFE_DBE_AH_TX_DFE_LPF04;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_TX_DFE_LPF04                     b;
}   PHY_DFE_DBE_AH_TX_DFE_LPF04_U;


// 0x4008A014 register ------------------------------------
typedef struct {
    uint32_t                                        r_reg_tx_dac_4x                      :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_AH_TX_DFE_LPF05;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_TX_DFE_LPF05                     b;
}   PHY_DFE_DBE_AH_TX_DFE_LPF05_U;


// 0x4008A018 register ------------------------------------
typedef struct {
    uint32_t                                        r16_reg_tx_digital_gain              :16;
    uint32_t                                        reserved0                            :16;
}   PHY_DFE_DBE_AH_TX_DFE_LPF06;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_TX_DFE_LPF06                     b;
}   PHY_DFE_DBE_AH_TX_DFE_LPF06_U;


// 0x4008A01C register ------------------------------------
typedef struct {
    uint32_t                                        r_reg_tx_gain_sel                    :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_AH_TX_DFE_LPF07;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_TX_DFE_LPF07                     b;
}   PHY_DFE_DBE_AH_TX_DFE_LPF07_U;


// 0x4008A020 register ------------------------------------
typedef struct {
    uint32_t                                        r30_reg_thr_bpsk                     :30;
    uint32_t                                        reserved0                            :2 ;
}   PHY_DFE_DBE_AH_TX_DFE_LPF08;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_TX_DFE_LPF08                     b;
}   PHY_DFE_DBE_AH_TX_DFE_LPF08_U;


// 0x4008A024 register ------------------------------------
typedef struct {
    uint32_t                                        r30_reg_thr_qpsk                     :30;
    uint32_t                                        reserved0                            :2 ;
}   PHY_DFE_DBE_AH_TX_DFE_LPF09;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_TX_DFE_LPF09                     b;
}   PHY_DFE_DBE_AH_TX_DFE_LPF09_U;


// 0x4008A028 register ------------------------------------
typedef struct {
    uint32_t                                        r30_reg_thr_16qam                    :30;
    uint32_t                                        reserved0                            :2 ;
}   PHY_DFE_DBE_AH_TX_DFE_LPF10;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_TX_DFE_LPF10                     b;
}   PHY_DFE_DBE_AH_TX_DFE_LPF10_U;


// 0x4008A02C register ------------------------------------
typedef struct {
    uint32_t                                        r30_reg_thr_64qam                    :30;
    uint32_t                                        reserved0                            :2 ;
}   PHY_DFE_DBE_AH_TX_DFE_LPF11;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_TX_DFE_LPF11                     b;
}   PHY_DFE_DBE_AH_TX_DFE_LPF11_U;


// 0x4008A030 register ------------------------------------
typedef struct {
    uint32_t                                        r30_reg_pgain_bpsk                   :30;
    uint32_t                                        reserved0                            :2 ;
}   PHY_DFE_DBE_AH_TX_DFE_LPF12;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_TX_DFE_LPF12                     b;
}   PHY_DFE_DBE_AH_TX_DFE_LPF12_U;


// 0x4008A034 register ------------------------------------
typedef struct {
    uint32_t                                        r30_reg_pgain_qpsk                   :30;
    uint32_t                                        reserved0                            :2 ;
}   PHY_DFE_DBE_AH_TX_DFE_LPF13;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_TX_DFE_LPF13                     b;
}   PHY_DFE_DBE_AH_TX_DFE_LPF13_U;


// 0x4008A038 register ------------------------------------
typedef struct {
    uint32_t                                        r30_reg_pgain_16qam                  :30;
    uint32_t                                        reserved0                            :2 ;
}   PHY_DFE_DBE_AH_TX_DFE_LPF14;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_TX_DFE_LPF14                     b;
}   PHY_DFE_DBE_AH_TX_DFE_LPF14_U;


// 0x4008A03C register ------------------------------------
typedef struct {
    uint32_t                                        r30_reg_pgain_64qam                  :30;
    uint32_t                                        reserved0                            :2 ;
}   PHY_DFE_DBE_AH_TX_DFE_LPF15;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_TX_DFE_LPF15                     b;
}   PHY_DFE_DBE_AH_TX_DFE_LPF15_U;


// 0x4008A040 register ------------------------------------
typedef struct {
    uint32_t                                        r2_reg_cfr_control                   :2 ;
    uint32_t                                        reserved0                            :30;
}   PHY_DFE_DBE_AH_TX_DFE_LPF16;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_TX_DFE_LPF16                     b;
}   PHY_DFE_DBE_AH_TX_DFE_LPF16_U;


// 0x4008A400 register ------------------------------------
typedef struct {
    uint32_t                                        r11_reg_tx_iq_para0                  :11;
    uint32_t                                        reserved0                            :21;
}   PHY_DFE_DBE_AH_TX_DFE_CAL00;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_TX_DFE_CAL00                     b;
}   PHY_DFE_DBE_AH_TX_DFE_CAL00_U;


// 0x4008A404 register ------------------------------------
typedef struct {
    uint32_t                                        r11_reg_tx_iq_para1                  :11;
    uint32_t                                        reserved0                            :21;
}   PHY_DFE_DBE_AH_TX_DFE_CAL01;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_TX_DFE_CAL01                     b;
}   PHY_DFE_DBE_AH_TX_DFE_CAL01_U;


// 0x4008A408 register ------------------------------------
typedef struct {
    uint32_t                                        r10_reg_tx_lo_para_i                 :10;
    uint32_t                                        reserved0                            :22;
}   PHY_DFE_DBE_AH_TX_DFE_CAL02;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_TX_DFE_CAL02                     b;
}   PHY_DFE_DBE_AH_TX_DFE_CAL02_U;


// 0x4008A40C register ------------------------------------
typedef struct {
    uint32_t                                        r10_reg_tx_lo_para_q                 :10;
    uint32_t                                        reserved0                            :22;
}   PHY_DFE_DBE_AH_TX_DFE_CAL03;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_TX_DFE_CAL03                     b;
}   PHY_DFE_DBE_AH_TX_DFE_CAL03_U;


// 0x4008A410 register ------------------------------------
typedef struct {
    uint32_t                                        r_reg_tx_loiq_mode_sel               :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_AH_TX_DFE_CAL04;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_TX_DFE_CAL04                     b;
}   PHY_DFE_DBE_AH_TX_DFE_CAL04_U;


// 0x4008BC00 register ------------------------------------
typedef struct {
    uint32_t                                        r32_reg_sbr_sync_seq                 :32;
}   PHY_DFE_DBE_PHY_TXSBR00;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_PHY_TXSBR00                         b;
}   PHY_DFE_DBE_PHY_TXSBR00_U;


// 0x4008BC04 register ------------------------------------
typedef struct {
    uint32_t                                        r2_reg_sbr_gain                      :2 ;
    uint32_t                                        reserved0                            :30;
}   PHY_DFE_DBE_PHY_TXSBR01;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_PHY_TXSBR01                         b;
}   PHY_DFE_DBE_PHY_TXSBR01_U;


// 0x4008BC08 register ------------------------------------
typedef struct {
    uint32_t                                        r_reg_sbr_mem_mode                   :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_PHY_TXSBR02;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_PHY_TXSBR02                         b;
}   PHY_DFE_DBE_PHY_TXSBR02_U;


// 0x4008BC0C register ------------------------------------
typedef struct {
    uint32_t                                        r_reg_sbr_mem_wr_enable              :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_PHY_TXSBR03;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_PHY_TXSBR03                         b;
}   PHY_DFE_DBE_PHY_TXSBR03_U;


// 0x4008BC10 register ------------------------------------
typedef struct {
    uint32_t                                        r7_reg_sbr_mem_wr_addr               :7 ;
    uint32_t                                        reserved0                            :25;
}   PHY_DFE_DBE_PHY_TXSBR04;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_PHY_TXSBR04                         b;
}   PHY_DFE_DBE_PHY_TXSBR04_U;


// 0x4008BC14 register ------------------------------------
typedef struct {
    uint32_t                                        r20_reg_sbr_mem_wr_data              :20;
    uint32_t                                        reserved0                            :12;
}   PHY_DFE_DBE_PHY_TXSBR05;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_PHY_TXSBR05                         b;
}   PHY_DFE_DBE_PHY_TXSBR05_U;


// 0x4008C000 register ------------------------------------
typedef struct {
    uint32_t                                        o8_reg_sync_pts_move                 :8 ;
    uint32_t                                        reserved0                            :24;
}   PHY_DFE_DBE_RX_DFE00;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE00                            b;
}   PHY_DFE_DBE_RX_DFE00_U;


// 0x4008C004 register ------------------------------------
typedef struct {
    uint32_t                                        o_reg_simul_tx_support               :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_RX_DFE01;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE01                            b;
}   PHY_DFE_DBE_RX_DFE01_U;


// 0x4008C008 register ------------------------------------
typedef struct {
    uint32_t                                        o_reg_cca_lvl_type                   :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_RX_DFE02;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE02                            b;
}   PHY_DFE_DBE_RX_DFE02_U;


// 0x4008C00C register ------------------------------------
typedef struct {
    uint32_t                                        o2_reg_rx_latency                    :2 ;
    uint32_t                                        reserved0                            :30;
}   PHY_DFE_DBE_RX_DFE03;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE03                            b;
}   PHY_DFE_DBE_RX_DFE03_U;


// 0x4008C010 register ------------------------------------
typedef struct {
    uint32_t                                        o_reg_dc_res_to_agc_in               :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_RX_DFE04;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE04                            b;
}   PHY_DFE_DBE_RX_DFE04_U;


// 0x4008C01C register ------------------------------------
typedef struct {
    uint32_t                                        o9_reg_refpwr_rcpi                   :9 ;
    uint32_t                                        reserved0                            :23;
}   PHY_DFE_DBE_RX_DFE07;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE07                            b;
}   PHY_DFE_DBE_RX_DFE07_U;


// 0x4008C020 register ------------------------------------
typedef struct {
    uint32_t                                        o6_reg_pkt_loss_thrd                 :6 ;
    uint32_t                                        reserved0                            :26;
}   PHY_DFE_DBE_RX_DFE08;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE08                            b;
}   PHY_DFE_DBE_RX_DFE08_U;


// 0x4008C024 register ------------------------------------
typedef struct {
    uint32_t                                        o32_reg_cca_thrd_1                   :32;
}   PHY_DFE_DBE_RX_DFE09;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE09                            b;
}   PHY_DFE_DBE_RX_DFE09_U;


// 0x4008C028 register ------------------------------------
typedef struct {
    uint32_t                                        o16_reg_cca_thrd_2                   :16;
    uint32_t                                        reserved0                            :16;
}   PHY_DFE_DBE_RX_DFE10;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE10                            b;
}   PHY_DFE_DBE_RX_DFE10_U;


// 0x4008C02C register ------------------------------------
typedef struct {
    uint32_t                                        o32_reg_cca_thrd_3                   :32;
}   PHY_DFE_DBE_RX_DFE11;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE11                            b;
}   PHY_DFE_DBE_RX_DFE11_U;


// 0x4008C030 register ------------------------------------
typedef struct {
    uint32_t                                        o_reg_dig_amp_bypass                 :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_RX_DFE12;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE12                            b;
}   PHY_DFE_DBE_RX_DFE12_U;


// 0x4008C034 register ------------------------------------
typedef struct {
    uint32_t                                        o14_reg_dump_length                  :14;
    uint32_t                                        reserved0                            :2 ;
    uint32_t                                        o2_reg_dump_period                   :2 ;
    uint32_t                                        reserved1                            :14;
}   PHY_DFE_DBE_RX_DFE13;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE13                            b;
}   PHY_DFE_DBE_RX_DFE13_U;


// 0x4008C038 register ------------------------------------
typedef struct {
    uint32_t                                        o_reg_dump_start                     :1 ;
    uint32_t                                        reserved0                            :3 ;
    uint32_t                                        o_reg_dump_reset                     :1 ;
    uint32_t                                        reserved1                            :3 ;
    uint32_t                                        i14_last_dump_addr                   :14;
    uint32_t                                        reserved2                            :10;
}   PHY_DFE_DBE_RX_DFE14;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE14                            b;
}   PHY_DFE_DBE_RX_DFE14_U;


// 0x4008C03C register ------------------------------------
typedef struct {
    uint32_t                                        o8_reg_dump_sel                      :8 ;
    uint32_t                                        o3_reg_trig_sel                      :3 ;
    uint32_t                                        reserved0                            :21;
}   PHY_DFE_DBE_RX_DFE15;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE15                            b;
}   PHY_DFE_DBE_RX_DFE15_U;


// 0x4008C040 register ------------------------------------
typedef struct {
    uint32_t                                        o_reg_str_pkt_on                     :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_RX_DFE16;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE16                            b;
}   PHY_DFE_DBE_RX_DFE16_U;


// 0x4008C044 register ------------------------------------
typedef struct {
    uint32_t                                        o8_reg_str_pkt_op_thrd               :7 ;
    uint32_t                                        reserved0                            :25;
}   PHY_DFE_DBE_RX_DFE17;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE17                            b;
}   PHY_DFE_DBE_RX_DFE17_U;


// 0x4008C070 register ------------------------------------
typedef struct {
    uint32_t                                        o16_reg_rdfe_idle_time               :16;
    uint32_t                                        reserved0                            :16;
}   PHY_DFE_DBE_RX_DFE_TIMER00;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_TIMER00                      b;
}   PHY_DFE_DBE_RX_DFE_TIMER00_U;


// 0x4008C07C register ------------------------------------
typedef struct {
    uint32_t                                        o16_reg_rdfe_sync_wait_time          :16;
    uint32_t                                        reserved0                            :16;
}   PHY_DFE_DBE_RX_DFE_TIMER03;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_TIMER03                      b;
}   PHY_DFE_DBE_RX_DFE_TIMER03_U;


// 0x4008C0A0 register ------------------------------------
typedef struct {
    uint32_t                                        o16_reg_rdfe_rssi_wait_time          :16;
    uint32_t                                        reserved0                            :16;
}   PHY_DFE_DBE_RX_DFE_TIMER12;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_TIMER12                      b;
}   PHY_DFE_DBE_RX_DFE_TIMER12_U;


// 0x4008C0B0 register ------------------------------------
typedef struct {
    uint32_t                                        o_reg_rdfe_mon_cfg                   :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_RX_DFE_LOG_CFG;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG_CFG                      b;
}   PHY_DFE_DBE_RX_DFE_LOG_CFG_U;


// 0x4008C0B4 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_00              :32;
}   PHY_DFE_DBE_RX_DFE_LOG00;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG00                        b;
}   PHY_DFE_DBE_RX_DFE_LOG00_U;


// 0x4008C0B8 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_01              :32;
}   PHY_DFE_DBE_RX_DFE_LOG01;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG01                        b;
}   PHY_DFE_DBE_RX_DFE_LOG01_U;


// 0x4008C0BC register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_02              :32;
}   PHY_DFE_DBE_RX_DFE_LOG02;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG02                        b;
}   PHY_DFE_DBE_RX_DFE_LOG02_U;


// 0x4008C0C0 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_03              :32;
}   PHY_DFE_DBE_RX_DFE_LOG03;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG03                        b;
}   PHY_DFE_DBE_RX_DFE_LOG03_U;


// 0x4008C0C4 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_04              :32;
}   PHY_DFE_DBE_RX_DFE_LOG04;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG04                        b;
}   PHY_DFE_DBE_RX_DFE_LOG04_U;


// 0x4008C0C8 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_05              :32;
}   PHY_DFE_DBE_RX_DFE_LOG05;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG05                        b;
}   PHY_DFE_DBE_RX_DFE_LOG05_U;


// 0x4008C0CC register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_06              :32;
}   PHY_DFE_DBE_RX_DFE_LOG06;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG06                        b;
}   PHY_DFE_DBE_RX_DFE_LOG06_U;


// 0x4008C0D0 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_07              :32;
}   PHY_DFE_DBE_RX_DFE_LOG07;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG07                        b;
}   PHY_DFE_DBE_RX_DFE_LOG07_U;


// 0x4008C0D4 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_08              :32;
}   PHY_DFE_DBE_RX_DFE_LOG08;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG08                        b;
}   PHY_DFE_DBE_RX_DFE_LOG08_U;


// 0x4008C0D8 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_09              :32;
}   PHY_DFE_DBE_RX_DFE_LOG09;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG09                        b;
}   PHY_DFE_DBE_RX_DFE_LOG09_U;


// 0x4008C0DC register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_10              :32;
}   PHY_DFE_DBE_RX_DFE_LOG10;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG10                        b;
}   PHY_DFE_DBE_RX_DFE_LOG10_U;


// 0x4008C0E0 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_11              :32;
}   PHY_DFE_DBE_RX_DFE_LOG11;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG11                        b;
}   PHY_DFE_DBE_RX_DFE_LOG11_U;


// 0x4008C0E4 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_12              :32;
}   PHY_DFE_DBE_RX_DFE_LOG12;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG12                        b;
}   PHY_DFE_DBE_RX_DFE_LOG12_U;


// 0x4008C0E8 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_13              :32;
}   PHY_DFE_DBE_RX_DFE_LOG13;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG13                        b;
}   PHY_DFE_DBE_RX_DFE_LOG13_U;


// 0x4008C0EC register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_14              :32;
}   PHY_DFE_DBE_RX_DFE_LOG14;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG14                        b;
}   PHY_DFE_DBE_RX_DFE_LOG14_U;


// 0x4008C0F0 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_15              :32;
}   PHY_DFE_DBE_RX_DFE_LOG15;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG15                        b;
}   PHY_DFE_DBE_RX_DFE_LOG15_U;


// 0x4008C0F4 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_16              :32;
}   PHY_DFE_DBE_RX_DFE_LOG16;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG16                        b;
}   PHY_DFE_DBE_RX_DFE_LOG16_U;


// 0x4008C0F8 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_17              :32;
}   PHY_DFE_DBE_RX_DFE_LOG17;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG17                        b;
}   PHY_DFE_DBE_RX_DFE_LOG17_U;


// 0x4008C0FC register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_18              :32;
}   PHY_DFE_DBE_RX_DFE_LOG18;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG18                        b;
}   PHY_DFE_DBE_RX_DFE_LOG18_U;


// 0x4008C100 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_19              :32;
}   PHY_DFE_DBE_RX_DFE_LOG19;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG19                        b;
}   PHY_DFE_DBE_RX_DFE_LOG19_U;


// 0x4008C104 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_20              :32;
}   PHY_DFE_DBE_RX_DFE_LOG20;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG20                        b;
}   PHY_DFE_DBE_RX_DFE_LOG20_U;


// 0x4008C108 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_21              :32;
}   PHY_DFE_DBE_RX_DFE_LOG21;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG21                        b;
}   PHY_DFE_DBE_RX_DFE_LOG21_U;


// 0x4008C10C register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_22              :32;
}   PHY_DFE_DBE_RX_DFE_LOG22;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG22                        b;
}   PHY_DFE_DBE_RX_DFE_LOG22_U;


// 0x4008C110 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_23              :32;
}   PHY_DFE_DBE_RX_DFE_LOG23;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG23                        b;
}   PHY_DFE_DBE_RX_DFE_LOG23_U;


// 0x4008C114 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_24              :32;
}   PHY_DFE_DBE_RX_DFE_LOG24;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG24                        b;
}   PHY_DFE_DBE_RX_DFE_LOG24_U;


// 0x4008C118 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_25              :32;
}   PHY_DFE_DBE_RX_DFE_LOG25;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG25                        b;
}   PHY_DFE_DBE_RX_DFE_LOG25_U;


// 0x4008C11C register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_26              :32;
}   PHY_DFE_DBE_RX_DFE_LOG26;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG26                        b;
}   PHY_DFE_DBE_RX_DFE_LOG26_U;


// 0x4008C120 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_27              :32;
}   PHY_DFE_DBE_RX_DFE_LOG27;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG27                        b;
}   PHY_DFE_DBE_RX_DFE_LOG27_U;


// 0x4008C124 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_28              :32;
}   PHY_DFE_DBE_RX_DFE_LOG28;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG28                        b;
}   PHY_DFE_DBE_RX_DFE_LOG28_U;


// 0x4008C128 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_29              :32;
}   PHY_DFE_DBE_RX_DFE_LOG29;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG29                        b;
}   PHY_DFE_DBE_RX_DFE_LOG29_U;


// 0x4008C12C register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_30              :32;
}   PHY_DFE_DBE_RX_DFE_LOG30;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG30                        b;
}   PHY_DFE_DBE_RX_DFE_LOG30_U;


// 0x4008C130 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_31              :32;
}   PHY_DFE_DBE_RX_DFE_LOG31;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG31                        b;
}   PHY_DFE_DBE_RX_DFE_LOG31_U;


// 0x4008C134 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_32              :32;
}   PHY_DFE_DBE_RX_DFE_LOG32;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG32                        b;
}   PHY_DFE_DBE_RX_DFE_LOG32_U;


// 0x4008C138 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_33              :32;
}   PHY_DFE_DBE_RX_DFE_LOG33;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG33                        b;
}   PHY_DFE_DBE_RX_DFE_LOG33_U;


// 0x4008C13C register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_34              :32;
}   PHY_DFE_DBE_RX_DFE_LOG34;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG34                        b;
}   PHY_DFE_DBE_RX_DFE_LOG34_U;


// 0x4008C140 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_35              :32;
}   PHY_DFE_DBE_RX_DFE_LOG35;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG35                        b;
}   PHY_DFE_DBE_RX_DFE_LOG35_U;


// 0x4008C144 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_36              :32;
}   PHY_DFE_DBE_RX_DFE_LOG36;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG36                        b;
}   PHY_DFE_DBE_RX_DFE_LOG36_U;


// 0x4008C148 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_37              :32;
}   PHY_DFE_DBE_RX_DFE_LOG37;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG37                        b;
}   PHY_DFE_DBE_RX_DFE_LOG37_U;


// 0x4008C14C register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_38              :32;
}   PHY_DFE_DBE_RX_DFE_LOG38;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG38                        b;
}   PHY_DFE_DBE_RX_DFE_LOG38_U;


// 0x4008C150 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_rdfe_mon_log_39              :32;
}   PHY_DFE_DBE_RX_DFE_LOG39;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RX_DFE_LOG39                        b;
}   PHY_DFE_DBE_RX_DFE_LOG39_U;


// 0x4008C400 register ------------------------------------
typedef struct {
    uint32_t                                        r3_reg_agc_cal_limit                 :3 ;
    uint32_t                                        reserved0                            :29;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_00;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_00                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_00_U;


// 0x4008C404 register ------------------------------------
typedef struct {
    uint32_t                                        r16_reg_agc_cal_opt                  :16;
    uint32_t                                        reserved0                            :16;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_01;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_01                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_01_U;


// 0x4008C408 register ------------------------------------
typedef struct {
    uint32_t                                        r6_reg_rxm_set_time                  :6 ;
    uint32_t                                        reserved0                            :26;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_02;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_02                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_02_U;


// 0x4008C40C register ------------------------------------
typedef struct {
    uint32_t                                        r3_reg_manual_rf_rssi                :3 ;
    uint32_t                                        reserved0                            :29;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_03;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_03                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_03_U;


// 0x4008C410 register ------------------------------------
typedef struct {
    uint32_t                                        r9_reg_adc_sat_int_thr               :9 ;
    uint32_t                                        reserved0                            :23;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_04;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_04                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_04_U;


// 0x4008C414 register ------------------------------------
typedef struct {
    uint32_t                                        r_reg_adc_sat_ext                    :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_05;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_05                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_05_U;


// 0x4008C418 register ------------------------------------
typedef struct {
    uint32_t                                        r16_reg_agcwait                      :16;
    uint32_t                                        reserved0                            :16;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_06;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_06                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_06_U;


// 0x4008C41C register ------------------------------------
typedef struct {
    uint32_t                                        r8_reg_agcref_noise                  :8 ;
    uint32_t                                        reserved0                            :24;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_07;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_07                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_07_U;


// 0x4008C420 register ------------------------------------
typedef struct {
    uint32_t                                        r8_reg_agcref_aamp                   :8 ;
    uint32_t                                        reserved0                            :24;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_08;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_08                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_08_U;


// 0x4008C424 register ------------------------------------
typedef struct {
    uint32_t                                        r8_reg_agcref_damp                   :8 ;
    uint32_t                                        reserved0                            :24;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_09;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_09                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_09_U;


// 0x4008C428 register ------------------------------------
typedef struct {
    uint32_t                                        r2_reg_agc_opt                       :2 ;
    uint32_t                                        reserved0                            :30;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_10;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_10                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_10_U;


// 0x4008C42C register ------------------------------------
typedef struct {
    uint32_t                                        r12_reg_rxhp_option                  :12;
    uint32_t                                        reserved0                            :20;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_11;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_11                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_11_U;


// 0x4008C430 register ------------------------------------
typedef struct {
    uint32_t                                        r5_reg_agcstepsmall                  :5 ;
    uint32_t                                        reserved0                            :27;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_12;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_12                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_12_U;


// 0x4008C434 register ------------------------------------
typedef struct {
    uint32_t                                        r5_reg_agcsteplna                    :5 ;
    uint32_t                                        reserved0                            :27;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_13;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_13                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_13_U;


// 0x4008C438 register ------------------------------------
typedef struct {
    uint32_t                                        r5_reg_agcstepvga                    :5 ;
    uint32_t                                        reserved0                            :27;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_14;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_14                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_14_U;


// 0x4008C43C register ------------------------------------
typedef struct {
    uint32_t                                        r5_reg_agcstepadc                    :5 ;
    uint32_t                                        reserved0                            :27;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_15;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_15                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_15_U;


// 0x4008C440 register ------------------------------------
typedef struct {
    uint32_t                                        r5_reg_agcstepdamp                   :5 ;
    uint32_t                                        reserved0                            :27;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_16;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_16                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_16_U;


// 0x4008C444 register ------------------------------------
typedef struct {
    uint32_t                                        r7_reg_rx_max_gain                   :7 ;
    uint32_t                                        reserved0                            :25;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_17;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_17                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_17_U;


// 0x4008C448 register ------------------------------------
typedef struct {
    uint32_t                                        r3_reg_agcunlock                     :3 ;
    uint32_t                                        reserved0                            :29;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_18;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_18                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_18_U;


// 0x4008C44C register ------------------------------------
typedef struct {
    uint32_t                                        r3_reg_agclock                       :3 ;
    uint32_t                                        reserved0                            :29;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_19;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_19                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_19_U;


// 0x4008C450 register ------------------------------------
typedef struct {
    uint32_t                                        r3_reg_agcuncal                      :3 ;
    uint32_t                                        reserved0                            :29;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_20;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_20                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_20_U;


// 0x4008C454 register ------------------------------------
typedef struct {
    uint32_t                                        r3_reg_agccal                        :3 ;
    uint32_t                                        reserved0                            :29;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_21;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_21                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_21_U;


// 0x4008C458 register ------------------------------------
typedef struct {
    uint32_t                                        r7_reg_db_initial_gain               :7 ;
    uint32_t                                        reserved0                            :25;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_22;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_22                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_22_U;


// 0x4008C45C register ------------------------------------
typedef struct {
    uint32_t                                        r2_reg_rf_sel                        :2 ;
    uint32_t                                        reserved0                            :30;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_23;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_23                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_23_U;


// 0x4008C460 register ------------------------------------
typedef struct {
    uint32_t                                        r9_reg_fast_dcoc_pck_end_opt         :9 ;
    uint32_t                                        reserved0                            :23;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_24;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_24                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_24_U;


// 0x4008C464 register ------------------------------------
typedef struct {
    uint32_t                                        r_reg_f_dcoc_mode                    :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_25;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_25                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_25_U;


// 0x4008C468 register ------------------------------------
typedef struct {
    uint32_t                                        r6_reg_f_dcoc_cnt                    :6 ;
    uint32_t                                        reserved0                            :26;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_26;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_26                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_26_U;


// 0x4008C46C register ------------------------------------
typedef struct {
    uint32_t                                        r_reg_aamp_dif_sel                   :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_27;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_27                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_27_U;


// 0x4008C470 register ------------------------------------
typedef struct {
    uint32_t                                        r_reg_gain_out_sel                   :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_28;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_28                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_28_U;


// 0x4008C474 register ------------------------------------
typedef struct {
    uint32_t                                        r_reg_lock_option                    :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_29;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_29                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_29_U;


// 0x4008C478 register ------------------------------------
typedef struct {
    uint32_t                                        r4_reg_sat_cnt_thr                   :4 ;
    uint32_t                                        reserved0                            :28;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_30;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_30                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_30_U;


// 0x4008C47C register ------------------------------------
typedef struct {
    uint32_t                                        r4_reg_g_ctl_cnt_thr                 :4 ;
    uint32_t                                        reserved0                            :28;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_31;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_31                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_31_U;


// 0x4008C480 register ------------------------------------
typedef struct {
    uint32_t                                        r_reg_sat_sel                        :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_32;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_32                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_32_U;


// 0x4008C484 register ------------------------------------
typedef struct {
    uint32_t                                        r_reg_manual_db_gctrl_on             :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_33;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_33                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_33_U;


// 0x4008C488 register ------------------------------------
typedef struct {
    uint32_t                                        r7_reg_db_gain_manual                :7 ;
    uint32_t                                        reserved0                            :25;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_34;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_34                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_34_U;


// 0x4008C48C register ------------------------------------
typedef struct {
    uint32_t                                        r24_reg_ext_lna_opt                  :24;
    uint32_t                                        reserved0                            :8 ;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_35;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_35                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_35_U;


// 0x4008C490 register ------------------------------------
typedef struct {
    uint32_t                                        r_reg_damp_on                        :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_36;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_36                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_36_U;


// 0x4008C494 register ------------------------------------
typedef struct {
    uint32_t                                        r12_reg_damp_sat_thr                 :12;
    uint32_t                                        reserved0                            :20;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_37;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_37                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_37_U;


// 0x4008C498 register ------------------------------------
typedef struct {
    uint32_t                                        r2_reg_rxgain_mem_type               :2 ;
    uint32_t                                        reserved0                            :30;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_38;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_38                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_38_U;


// 0x4008C49C register ------------------------------------
typedef struct {
    uint32_t                                        r_reg_rxagc_lut_wr_enable            :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_39;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_39                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_39_U;


// 0x4008C4A0 register ------------------------------------
typedef struct {
    uint32_t                                        r7_reg_rxagc_lut_wr_addr             :7 ;
    uint32_t                                        reserved0                            :25;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_40;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_40                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_40_U;


// 0x4008C4A4 register ------------------------------------
typedef struct {
    uint32_t                                        r24_reg_rxagc_lut_wr_data            :24;
    uint32_t                                        reserved0                            :8 ;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_41;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_41                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_41_U;


// 0x4008C4A8 register ------------------------------------
typedef struct {
    uint32_t                                        r2_reg_rxagc_lut_wr_lna              :2 ;
    uint32_t                                        reserved0                            :30;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_42;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_42                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_42_U;


// 0x4008C4AC register ------------------------------------
typedef struct {
    uint32_t                                        r2_reg_rxagc_lut_wr_vga1             :2 ;
    uint32_t                                        reserved0                            :30;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_43;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_43                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_43_U;


// 0x4008C4B0 register ------------------------------------
typedef struct {
    uint32_t                                        r2_reg_rxagc_lut_wr_vga2             :2 ;
    uint32_t                                        reserved0                            :30;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_44;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_44                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_44_U;


// 0x4008C4B4 register ------------------------------------
typedef struct {
    uint32_t                                        r4_reg_rxagc_lut_wr_vga3             :4 ;
    uint32_t                                        reserved0                            :28;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_45;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_45                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_45_U;


// 0x4008C4B8 register ------------------------------------
typedef struct {
    uint32_t                                        i_reg_nc_done                        :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_46;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_46                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_46_U;


// 0x4008C4BC register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_nc_out                       :32;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_47;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_47                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_47_U;


// 0x4008C4C0 register ------------------------------------
typedef struct {
    uint32_t                                        i_reg_ic_done                        :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_48;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_48                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_48_U;


// 0x4008C4C4 register ------------------------------------
typedef struct {
    uint32_t                                        i32_reg_ic_out                       :32;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_49;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_49                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_49_U;


// 0x4008C4C8 register ------------------------------------
typedef struct {
    uint32_t                                        r_reg_rx_nic_cal_en                  :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_50;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_50                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_50_U;


// 0x4008C4CC register ------------------------------------
typedef struct {
    uint32_t                                        r_reg_rx_nic_en                      :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_51;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_51                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_51_U;


// 0x4008C4D0 register ------------------------------------
typedef struct {
    uint32_t                                        r10_reg_nc_en_delay                  :10;
    uint32_t                                        reserved0                            :22;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_52;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_52                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_52_U;


// 0x4008C4D4 register ------------------------------------
typedef struct {
    uint32_t                                        r3_reg_nic_cnt_thr_opt               :3 ;
    uint32_t                                        reserved0                            :29;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_53;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_53                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_53_U;


// 0x4008C4D8 register ------------------------------------
typedef struct {
    uint32_t                                        r16_reg_prev_st_nc_cond              :16;
    uint32_t                                        reserved0                            :16;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_54;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_54                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_54_U;


// 0x4008C4DC register ------------------------------------
typedef struct {
    uint32_t                                        r16_reg_curr_st_nc_cond              :16;
    uint32_t                                        reserved0                            :16;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_55;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_55                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_55_U;


// 0x4008C4E0 register ------------------------------------
typedef struct {
    uint32_t                                        r16_reg_prev_st_ic_cond              :16;
    uint32_t                                        reserved0                            :16;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_56;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_56                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_56_U;


// 0x4008C4E4 register ------------------------------------
typedef struct {
    uint32_t                                        r16_reg_curr_st_ic_cond              :16;
    uint32_t                                        reserved0                            :16;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_57;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_57                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_57_U;


// 0x4008C4E8 register ------------------------------------
typedef struct {
    uint32_t                                        r16_reg_disable_st_cond              :16;
    uint32_t                                        reserved0                            :16;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_58;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_58                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_58_U;


// 0x4008C4EC register ------------------------------------
typedef struct {
    uint32_t                                        r2_reg_nic_mode                      :2 ;
    uint32_t                                        reserved0                            :30;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_59;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_59                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_59_U;


// 0x4008C4F0 register ------------------------------------
typedef struct {
    uint32_t                                        r2_reg_nic_damp_in_loc               :2 ;
    uint32_t                                        reserved0                            :30;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_60;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_60                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_60_U;


// 0x4008C4F4 register ------------------------------------
typedef struct {
    uint32_t                                        r3_reg_gv_delay                      :3 ;
    uint32_t                                        reserved0                            :29;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_61;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_61                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_61_U;


// 0x4008C4F8 register ------------------------------------
typedef struct {
    uint32_t                                        i_reg_nic_sat_ind                    :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_62;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_62                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_62_U;


// 0x4008C4FC register ------------------------------------
typedef struct {
    uint32_t                                        r8_reg_rx_min_gain                   :8 ;
    uint32_t                                        reserved0                            :24;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_63;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_63                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_63_U;


// 0x4008C500 register ------------------------------------
typedef struct {
    uint32_t                                        r32_reg_rx_idle_time_cnt_thr         :32;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_64;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_64                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_64_U;


// 0x4008C504 register ------------------------------------
typedef struct {
    uint32_t                                        r16_reg_gcal_trk1_upd_thr            :16;
    uint32_t                                        reserved0                            :16;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_65;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_65                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_65_U;


// 0x4008C508 register ------------------------------------
typedef struct {
    uint32_t                                        r16_reg_gcal_trk2_upd_thr            :16;
    uint32_t                                        reserved0                            :16;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_66;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_66                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_66_U;


// 0x4008C50C register ------------------------------------
typedef struct {
    uint32_t                                        r_reg_gcal_wait_en                   :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_67;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_67                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_67_U;


// 0x4008C510 register ------------------------------------
typedef struct {
    uint32_t                                        r32_reg_gcal_wait1                   :32;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_68;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_68                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_68_U;


// 0x4008C514 register ------------------------------------
typedef struct {
    uint32_t                                        r32_reg_gcal_wait2                   :32;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_69;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_69                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_69_U;


// 0x4008C518 register ------------------------------------
typedef struct {
    uint32_t                                        r32_reg_gcal_wait3                   :32;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_70;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_70                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_70_U;


// 0x4008C51C register ------------------------------------
typedef struct {
    uint32_t                                        r16_reg_3rd_option                   :16;
    uint32_t                                        reserved0                            :16;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_71;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_71                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_71_U;


// 0x4008C520 register ------------------------------------
typedef struct {
    uint32_t                                        r5_reg_rxagc_lut_wr_vga4             :5 ;
    uint32_t                                        reserved0                            :27;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_72;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_AGC_72                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_AGC_72_U;


// 0x4008C800 register ------------------------------------
typedef struct {
    uint32_t                                        r_reg_is1mcen                        :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_AHA1_RXDFE_LPF_00;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_LPF_00                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_LPF_00_U;


// 0x4008C804 register ------------------------------------
typedef struct {
    uint32_t                                        r_reg_rxlpf_uplow_swap               :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_AHA1_RXDFE_LPF_01;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_LPF_01                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_LPF_01_U;


// 0x4008C808 register ------------------------------------
typedef struct {
    uint32_t                                        r_reg_rxdfe_lowif_en                 :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_AHA1_RXDFE_LPF_02;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_LPF_02                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_LPF_02_U;


// 0x4008C80C register ------------------------------------
typedef struct {
    uint32_t                                        r_reg_rxdfe_lowif_pos                :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_AHA1_RXDFE_LPF_03;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_LPF_03                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_LPF_03_U;


// 0x4008C810 register ------------------------------------
typedef struct {
    uint32_t                                        r2_reg_rxlpf_option                  :2 ;
    uint32_t                                        reserved0                            :30;
}   PHY_DFE_DBE_AHA1_RXDFE_LPF_04;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AHA1_RXDFE_LPF_04                   b;
}   PHY_DFE_DBE_AHA1_RXDFE_LPF_04_U;


// 0x4008CC00 register ------------------------------------
typedef struct {
    uint32_t                                        reserved0                            :8 ;
    uint32_t                                        o6_reg_1Mthreshold2                  :6 ;
    uint32_t                                        reserved1                            :2 ;
    uint32_t                                        o6_reg_1Mthreshold3                  :6 ;
    uint32_t                                        reserved2                            :10;
}   PHY_DFE_DBE_AH_RX_SYNC_1MTHRE;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_SYNC_1MTHRE                   b;
}   PHY_DFE_DBE_AH_RX_SYNC_1MTHRE_U;


// 0x4008CC04 register ------------------------------------
typedef struct {
    uint32_t                                        o9_reg_1MstfTOcnt                    :9 ;
    uint32_t                                        reserved0                            :7 ;
    uint32_t                                        o9_reg_1Mstfchkcnt                   :9 ;
    uint32_t                                        reserved1                            :7 ;
}   PHY_DFE_DBE_AH_RX_SYNC_1MSTF1;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_SYNC_1MSTF1                   b;
}   PHY_DFE_DBE_AH_RX_SYNC_1MSTF1_U;


// 0x4008CC08 register ------------------------------------
typedef struct {
    uint32_t                                        o9_reg_1Mstfwait                     :9 ;
    uint32_t                                        reserved0                            :23;
}   PHY_DFE_DBE_AH_RX_SYNC_1MSTF2;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_SYNC_1MSTF2                   b;
}   PHY_DFE_DBE_AH_RX_SYNC_1MSTF2_U;


// 0x4008CC0C register ------------------------------------
typedef struct {
    uint32_t                                        o8_reg_1MfsyncTOcnt                  :8 ;
    uint32_t                                        o8_reg_1Mfsyncconfirmcnt             :8 ;
    uint32_t                                        o8_reg_1Mfsync2ndwait                :8 ;
    uint32_t                                        reserved0                            :8 ;
}   PHY_DFE_DBE_AH_RX_SYNC_1MFSYNC;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_SYNC_1MFSYNC                  b;
}   PHY_DFE_DBE_AH_RX_SYNC_1MFSYNC_U;


// 0x4008CC10 register ------------------------------------
typedef struct {
    uint32_t                                        o6_reg_1Mcfoidlecnt                  :6 ;
    uint32_t                                        reserved0                            :2 ;
    uint32_t                                        o6_reg_1Mcfodur1                     :6 ;
    uint32_t                                        reserved1                            :2 ;
    uint32_t                                        o6_reg_1Mcfowait4                    :6 ;
    uint32_t                                        reserved2                            :2 ;
    uint32_t                                        o6_reg_1Mcfodur2                     :6 ;
    uint32_t                                        reserved3                            :2 ;
}   PHY_DFE_DBE_AH_RX_SYNC_1MCFO1;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_SYNC_1MCFO1                   b;
}   PHY_DFE_DBE_AH_RX_SYNC_1MCFO1_U;


// 0x4008CC14 register ------------------------------------
typedef struct {
    uint32_t                                        o6_reg_1Mcfodur3                     :6 ;
    uint32_t                                        reserved0                            :2 ;
    uint32_t                                        o8_reg_1Mcfowait3                    :8 ;
    uint32_t                                        reserved1                            :16;
}   PHY_DFE_DBE_AH_RX_SYNC_1MCFO2;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_SYNC_1MCFO2                   b;
}   PHY_DFE_DBE_AH_RX_SYNC_1MCFO2_U;


// 0x4008CC18 register ------------------------------------
typedef struct {
    uint32_t                                        o_reg_skip2ndccfo                    :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_AH_RX_SYNC_1MCTRL;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_SYNC_1MCTRL                   b;
}   PHY_DFE_DBE_AH_RX_SYNC_1MCTRL_U;


// 0x4008CC20 register ------------------------------------
typedef struct {
    uint32_t                                        reserved0                            :8 ;
    uint32_t                                        o6_reg_2Mthreshold3                  :6 ;
    uint32_t                                        reserved1                            :18;
}   PHY_DFE_DBE_AH_RX_SYNC_2MTHRE;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_SYNC_2MTHRE                   b;
}   PHY_DFE_DBE_AH_RX_SYNC_2MTHRE_U;


// 0x4008CC24 register ------------------------------------
typedef struct {
    uint32_t                                        o9_reg_2Mstfwait                     :9 ;
    uint32_t                                        reserved0                            :7 ;
    uint32_t                                        o9_reg_2MstfTOcnt                    :9 ;
    uint32_t                                        reserved1                            :7 ;
}   PHY_DFE_DBE_AH_RX_SYNC_2MSTF;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_SYNC_2MSTF                    b;
}   PHY_DFE_DBE_AH_RX_SYNC_2MSTF_U;


// 0x4008CC28 register ------------------------------------
typedef struct {
    uint32_t                                        o8_reg_2MfsyncTOcnt                  :8 ;
    uint32_t                                        o8_reg_2Mfsyncconfirmcnt             :8 ;
    uint32_t                                        o8_reg_2Mfsync2ndwait                :8 ;
    uint32_t                                        reserved0                            :8 ;
}   PHY_DFE_DBE_AH_RX_SYNC_2MFSYNC;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_SYNC_2MFSYNC                  b;
}   PHY_DFE_DBE_AH_RX_SYNC_2MFSYNC_U;


// 0x4008CC2C register ------------------------------------
typedef struct {
    uint32_t                                        o6_reg_2Mcfoidlecnt                  :6 ;
    uint32_t                                        reserved0                            :2 ;
    uint32_t                                        o6_reg_2Mcfodur1                     :6 ;
    uint32_t                                        reserved1                            :2 ;
    uint32_t                                        o6_reg_2Mcfodur2                     :8 ;
    uint32_t                                        reserved2                            :8 ;
}   PHY_DFE_DBE_AH_RX_SYNC_2MCFO;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_SYNC_2MCFO                    b;
}   PHY_DFE_DBE_AH_RX_SYNC_2MCFO_U;


// 0x4008CC30 register ------------------------------------
typedef struct {
    uint32_t                                        i13_reg_cfoerr                       :13;
    uint32_t                                        reserved0                            :19;
}   PHY_DFE_DBE_AH_RX_SYNC_CFOERR;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_SYNC_CFOERR                   b;
}   PHY_DFE_DBE_AH_RX_SYNC_CFOERR_U;


// 0x4008CC34 register ------------------------------------
typedef struct {
    uint32_t                                        o9_reg_fltdly1M_op2                  :9 ;
    uint32_t                                        reserved0                            :7 ;
    uint32_t                                        o9_reg_fltdly1M_op4                  :9 ;
    uint32_t                                        reserved1                            :7 ;
}   PHY_DFE_DBE_AH_RX_SYNC_FLTDLY1M;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_SYNC_FLTDLY1M                 b;
}   PHY_DFE_DBE_AH_RX_SYNC_FLTDLY1M_U;


// 0x4008CC38 register ------------------------------------
typedef struct {
    uint32_t                                        o9_reg_fltdly2M_op2                  :9 ;
    uint32_t                                        reserved0                            :7 ;
    uint32_t                                        o9_reg_fltdly2M_op4                  :9 ;
    uint32_t                                        reserved1                            :7 ;
}   PHY_DFE_DBE_AH_RX_SYNC_FLTDLY2M;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_SYNC_FLTDLY2M                 b;
}   PHY_DFE_DBE_AH_RX_SYNC_FLTDLY2M_U;


// 0x4008CC3C register ------------------------------------
typedef struct {
    uint32_t                                        o16_reg_1Mxcorrmin                   :16;
    uint32_t                                        o16_reg_2Mxcorrmin                   :16;
}   PHY_DFE_DBE_AH_RX_SYNC_XCORRMIN;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_SYNC_XCORRMIN                 b;
}   PHY_DFE_DBE_AH_RX_SYNC_XCORRMIN_U;


// 0x4008CC40 register ------------------------------------
typedef struct {
    uint32_t                                        o5_reg_fsyncdelay1M_op2              :5 ;
    uint32_t                                        reserved0                            :3 ;
    uint32_t                                        o5_reg_fsyncdelay1M_op4              :5 ;
    uint32_t                                        reserved1                            :3 ;
    uint32_t                                        o5_reg_fsyncdelay2M_op2              :5 ;
    uint32_t                                        reserved2                            :3 ;
    uint32_t                                        o5_reg_fsyncdelay2M_op4              :5 ;
    uint32_t                                        reserved3                            :3 ;
}   PHY_DFE_DBE_AH_RX_SYNC_FSYNCD;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_SYNC_FSYNCD                   b;
}   PHY_DFE_DBE_AH_RX_SYNC_FSYNCD_U;


// 0x4008CC44 register ------------------------------------
typedef struct {
    uint32_t                                        o4_reg_snrest1delay                  :4 ;
    uint32_t                                        o4_reg_snrest2delay                  :4 ;
    uint32_t                                        reserved0                            :24;
}   PHY_DFE_DBE_AH_RX_SYNC_SNRESTD;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_SYNC_SNRESTD                  b;
}   PHY_DFE_DBE_AH_RX_SYNC_SNRESTD_U;


// 0x4008D000 register ------------------------------------
typedef struct {
    uint32_t                                        r16_reg_conv_ratio1                  :16;
    uint32_t                                        reserved0                            :16;
}   PHY_DFE_DBE_AH_PHTRK_EST_00;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_PHTRK_EST_00                     b;
}   PHY_DFE_DBE_AH_PHTRK_EST_00_U;


// 0x4008D004 register ------------------------------------
typedef struct {
    uint32_t                                        r16_reg_conv_ratio2                  :16;
    uint32_t                                        reserved0                            :16;
}   PHY_DFE_DBE_AH_PHTRK_EST_01;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_PHTRK_EST_01                     b;
}   PHY_DFE_DBE_AH_PHTRK_EST_01_U;


// 0x4008D008 register ------------------------------------
typedef struct {
    uint32_t                                        r16_reg_conv_ratio3                  :16;
    uint32_t                                        reserved0                            :16;
}   PHY_DFE_DBE_AH_PHTRK_EST_02;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_PHTRK_EST_02                     b;
}   PHY_DFE_DBE_AH_PHTRK_EST_02_U;


// 0x4008D00C register ------------------------------------
typedef struct {
    uint32_t                                        r21_reg_cfo_rf_bias                  :16;
    uint32_t                                        reserved0                            :16;
}   PHY_DFE_DBE_AH_PHTRK_EST_03;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_PHTRK_EST_03                     b;
}   PHY_DFE_DBE_AH_PHTRK_EST_03_U;


// 0x4008D400 register ------------------------------------
typedef struct {
    uint32_t                                        r_reg_cs_chk_dly_en                  :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_AH_RX_CS00;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_CS00                          b;
}   PHY_DFE_DBE_AH_RX_CS00_U;


// 0x4008D404 register ------------------------------------
typedef struct {
    uint32_t                                        r16_reg_cs_chk_dly_cnt               :16;
    uint32_t                                        reserved0                            :16;
}   PHY_DFE_DBE_AH_RX_CS01;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_CS01                          b;
}   PHY_DFE_DBE_AH_RX_CS01_U;


// 0x4008D408 register ------------------------------------
typedef struct {
    uint32_t                                        r4_reg_cs_enable                     :4 ;
    uint32_t                                        reserved0                            :28;
}   PHY_DFE_DBE_AH_RX_CS02;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_CS02                          b;
}   PHY_DFE_DBE_AH_RX_CS02_U;


// 0x4008D40C register ------------------------------------
typedef struct {
    uint32_t                                        r10_reg_cs_sat_thr                   :10;
    uint32_t                                        reserved0                            :22;
}   PHY_DFE_DBE_AH_RX_CS03;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_CS03                          b;
}   PHY_DFE_DBE_AH_RX_CS03_U;


// 0x4008D410 register ------------------------------------
typedef struct {
    uint32_t                                        r4_reg_cs_sat_det_cnt                :4 ;
    uint32_t                                        reserved0                            :28;
}   PHY_DFE_DBE_AH_RX_CS04;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_CS04                          b;
}   PHY_DFE_DBE_AH_RX_CS04_U;


// 0x4008D414 register ------------------------------------
typedef struct {
    uint32_t                                        r_reg_cs_sat_wait_en                 :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_AH_RX_CS05;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_CS05                          b;
}   PHY_DFE_DBE_AH_RX_CS05_U;


// 0x4008D440 register ------------------------------------
typedef struct {
    uint32_t                                        r2_reg_cs_xcor_out_sel               :2 ;
    uint32_t                                        reserved0                            :30;
}   PHY_DFE_DBE_AH_RX_CS10;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_CS10                          b;
}   PHY_DFE_DBE_AH_RX_CS10_U;


// 0x4008D444 register ------------------------------------
typedef struct {
    uint32_t                                        r16_reg_cs_xcor_pwr_wgt              :16;
    uint32_t                                        reserved0                            :16;
}   PHY_DFE_DBE_AH_RX_CS11;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_CS11                          b;
}   PHY_DFE_DBE_AH_RX_CS11_U;


// 0x4008D448 register ------------------------------------
typedef struct {
    uint32_t                                        r24_reg_cs_xcor_pwr_thr1             :24;
    uint32_t                                        reserved0                            :8 ;
}   PHY_DFE_DBE_AH_RX_CS12;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_CS12                          b;
}   PHY_DFE_DBE_AH_RX_CS12_U;


// 0x4008D44C register ------------------------------------
typedef struct {
    uint32_t                                        r24_reg_cs_xcor_pwr_thr2             :24;
    uint32_t                                        reserved0                            :8 ;
}   PHY_DFE_DBE_AH_RX_CS13;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_CS13                          b;
}   PHY_DFE_DBE_AH_RX_CS13_U;


// 0x4008D450 register ------------------------------------
typedef struct {
    uint32_t                                        r8_reg_cs_rssi_thr1                  :8 ;
    uint32_t                                        reserved0                            :24;
}   PHY_DFE_DBE_AH_RX_CS14;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_CS14                          b;
}   PHY_DFE_DBE_AH_RX_CS14_U;


// 0x4008D454 register ------------------------------------
typedef struct {
    uint32_t                                        r8_reg_cs_rssi_thr2                  :8 ;
    uint32_t                                        reserved0                            :24;
}   PHY_DFE_DBE_AH_RX_CS15;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_CS15                          b;
}   PHY_DFE_DBE_AH_RX_CS15_U;


// 0x4008D458 register ------------------------------------
typedef struct {
    uint32_t                                        r_reg_cs_xcor_1m_sel                 :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_AH_RX_CS16;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_CS16                          b;
}   PHY_DFE_DBE_AH_RX_CS16_U;


// 0x4008D480 register ------------------------------------
typedef struct {
    uint32_t                                        r_reg_mid_cca_en                     :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_AH_RX_CS20;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_CS20                          b;
}   PHY_DFE_DBE_AH_RX_CS20_U;


// 0x4008D484 register ------------------------------------
typedef struct {
    uint32_t                                        r8_reg_mid_cca_time                  :20;
    uint32_t                                        reserved0                            :12;
}   PHY_DFE_DBE_AH_RX_CS21;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_CS21                          b;
}   PHY_DFE_DBE_AH_RX_CS21_U;


// 0x4008D488 register ------------------------------------
typedef struct {
    uint32_t                                        r6_reg_mid_cca_acr_wgt               :6 ;
    uint32_t                                        reserved0                            :26;
}   PHY_DFE_DBE_AH_RX_CS22;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_CS22                          b;
}   PHY_DFE_DBE_AH_RX_CS22_U;


// 0x4008D48C register ------------------------------------
typedef struct {
    uint32_t                                        r20_reg_mid_cca_pwr_avg_thr          :20;
    uint32_t                                        reserved0                            :12;
}   PHY_DFE_DBE_AH_RX_CS23;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_CS23                          b;
}   PHY_DFE_DBE_AH_RX_CS23_U;


// 0x4008D490 register ------------------------------------
typedef struct {
    uint32_t                                        r5_reg_mid_cca_det_thr               :5 ;
    uint32_t                                        reserved0                            :27;
}   PHY_DFE_DBE_AH_RX_CS24;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_AH_RX_CS24                          b;
}   PHY_DFE_DBE_AH_RX_CS24_U;


// 0x4008DC00 register ------------------------------------
typedef struct {
    uint32_t                                        o_reg_iqdc_hpf_on                    :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_RXDFE_IQDC_HPF_ON;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RXDFE_IQDC_HPF_ON                   b;
}   PHY_DFE_DBE_RXDFE_IQDC_HPF_ON_U;


// 0x4008DC04 register ------------------------------------
typedef struct {
    uint32_t                                        o_reg_iqdc_hpf_while_agc             :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_RXDFE_IQDC_HPF_WHILE_AGC;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RXDFE_IQDC_HPF_WHILE_AGC            b;
}   PHY_DFE_DBE_RXDFE_IQDC_HPF_WHILE_AGC_U;


// 0x4008DC08 register ------------------------------------
typedef struct {
    uint32_t                                        o3_reg_iqdc_hpf_wgt0                 :3 ;
    uint32_t                                        reserved0                            :29;
}   PHY_DFE_DBE_RXDFE_IQDC_HPF_WGT0;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RXDFE_IQDC_HPF_WGT0                 b;
}   PHY_DFE_DBE_RXDFE_IQDC_HPF_WGT0_U;


// 0x4008DC0C register ------------------------------------
typedef struct {
    uint32_t                                        o3_reg_iqdc_hpf_wgt1                 :3 ;
    uint32_t                                        reserved0                            :29;
}   PHY_DFE_DBE_RXDFE_IQDC_HPF_WGT1;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RXDFE_IQDC_HPF_WGT1                 b;
}   PHY_DFE_DBE_RXDFE_IQDC_HPF_WGT1_U;


// 0x4008DC10 register ------------------------------------
typedef struct {
    uint32_t                                        o3_reg_iqdc_hpf_wgt2                 :3 ;
    uint32_t                                        reserved0                            :29;
}   PHY_DFE_DBE_RXDFE_IQDC_HPF_WGT2;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RXDFE_IQDC_HPF_WGT2                 b;
}   PHY_DFE_DBE_RXDFE_IQDC_HPF_WGT2_U;


// 0x4008DC14 register ------------------------------------
typedef struct {
    uint32_t                                        o8_reg_iqdc_hpf_dur_wgt2             :8 ;
    uint32_t                                        reserved0                            :24;
}   PHY_DFE_DBE_RXDFE_IQDC_HPF_DUR_WGT2;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RXDFE_IQDC_HPF_DUR_WGT2             b;
}   PHY_DFE_DBE_RXDFE_IQDC_HPF_DUR_WGT2_U;


// 0x4008DC18 register ------------------------------------
typedef struct {
    uint32_t                                        o10_reg_iqdc_lut_highpwr_det_thr     :10;
    uint32_t                                        reserved0                            :10;
    uint32_t                                        o_reg_iqdc_lut_autorun_start         :1 ;
    uint32_t                                        reserved1                            :3 ;
    uint32_t                                        o_reg_iqdc_lut_manual_cfg            :1 ;
    uint32_t                                        reserved2                            :3 ;
    uint32_t                                        o_reg_iqdc_lut_ena                   :1 ;
    uint32_t                                        reserved3                            :3 ;
}   PHY_DFE_DBE_RXDFE_IQDC_LUT_CFG;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RXDFE_IQDC_LUT_CFG                  b;
}   PHY_DFE_DBE_RXDFE_IQDC_LUT_CFG_U;


// 0x4008DC1C register ------------------------------------
typedef struct {
    uint32_t                                        o8_reg_iqdc_lut_gainset_wait         :8 ;
    uint32_t                                        o2_reg_iqdc_lut_msr_len              :2 ;
    uint32_t                                        reserved0                            :6 ;
    uint32_t                                        o8_reg_iqdc_lut_mingain              :8 ;
    uint32_t                                        o8_reg_iqdc_lut_maxgain              :8 ;
}   PHY_DFE_DBE_RXDFE_IQDC_LUT_ALG;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RXDFE_IQDC_LUT_ALG                  b;
}   PHY_DFE_DBE_RXDFE_IQDC_LUT_ALG_U;


// 0x4008DC20 register ------------------------------------
typedef struct {
    uint32_t                                        o20_reg_iqdc_lut_wrdata              :20;
    uint32_t                                        reserved0                            :4 ;
    uint32_t                                        o8_reg_iqdc_lut_wraddr               :8 ;
}   PHY_DFE_DBE_RXDFE_IQDC_LUT_WRITE;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RXDFE_IQDC_LUT_WRITE                b;
}   PHY_DFE_DBE_RXDFE_IQDC_LUT_WRITE_U;


// 0x4008DC24 register ------------------------------------
typedef struct {
    uint32_t                                        reserved0                            :24;
    uint32_t                                        o8_reg_iqdc_lut_rdaddr               :8 ;
}   PHY_DFE_DBE_RXDFE_IQDC_LUT_READ;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RXDFE_IQDC_LUT_READ                 b;
}   PHY_DFE_DBE_RXDFE_IQDC_LUT_READ_U;


// 0x4008DC28 register ------------------------------------
typedef struct {
    uint32_t                                        i20_reg_iqdc_lut_rddata_out          :20;
    uint32_t                                        reserved0                            :4 ;
    uint32_t                                        i8_reg_iqdc_lut_rdaddr_out           :8 ;
}   PHY_DFE_DBE_RXDFE_IQDC_LUT_READ_RES;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RXDFE_IQDC_LUT_READ_RES             b;
}   PHY_DFE_DBE_RXDFE_IQDC_LUT_READ_RES_U;


// 0x4008DC2C register ------------------------------------
typedef struct {
    uint32_t                                        i_ctl_iqdc_lut_autorun_done          :1 ;
    uint32_t                                        i_reg_iqdc_lut_highpwr_det           :1 ;
    uint32_t                                        reserved0                            :2 ;
    uint32_t                                        i10_reg_iqdc_lut_highpwr_res         :10;
    uint32_t                                        reserved1                            :18;
}   PHY_DFE_DBE_RXDFE_IQDC_LUT_AUTO_RES;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RXDFE_IQDC_LUT_AUTO_RES             b;
}   PHY_DFE_DBE_RXDFE_IQDC_LUT_AUTO_RES_U;


// 0x4008DC30 register ------------------------------------
typedef struct {
    uint32_t                                        o8_reg_iqdc_cal_para0                :8 ;
    uint32_t                                        reserved0                            :24;
}   PHY_DFE_DBE_RXDFE_IQDC_CAL_PARA0;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RXDFE_IQDC_CAL_PARA0                b;
}   PHY_DFE_DBE_RXDFE_IQDC_CAL_PARA0_U;


// 0x4008DC34 register ------------------------------------
typedef struct {
    uint32_t                                        o8_reg_iqdc_cal_para1                :8 ;
    uint32_t                                        reserved0                            :24;
}   PHY_DFE_DBE_RXDFE_IQDC_CAL_PARA1;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RXDFE_IQDC_CAL_PARA1                b;
}   PHY_DFE_DBE_RXDFE_IQDC_CAL_PARA1_U;


// 0x4008DC38 register ------------------------------------
typedef struct {
    uint32_t                                        o_reg_iqdc_cal_self_val              :1 ;
    uint32_t                                        reserved0                            :31;
}   PHY_DFE_DBE_RXDFE_IQDC_CAL_SELF_VAL;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RXDFE_IQDC_CAL_SELF_VAL             b;
}   PHY_DFE_DBE_RXDFE_IQDC_CAL_SELF_VAL_U;


// 0x4008DC3C register ------------------------------------
typedef struct {
    uint32_t                                        o16_reg_iqdc_cal_self_param_gain     :16;
    uint32_t                                        reserved0                            :16;
}   PHY_DFE_DBE_RXDFE_IQDC_CAL_SELF_PARAM_GAIN;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RXDFE_IQDC_CAL_SELF_PARAM_GAIN      b;
}   PHY_DFE_DBE_RXDFE_IQDC_CAL_SELF_PARAM_GAIN_U;


// 0x4008DC40 register ------------------------------------
typedef struct {
    uint32_t                                        o16_reg_iqdc_cal_self_param_phase    :16;
    uint32_t                                        reserved0                            :16;
}   PHY_DFE_DBE_RXDFE_IQDC_CAL_SELF_PARAM_PHASE;

typedef union {
    uint32_t                                        w;
    PHY_DFE_DBE_RXDFE_IQDC_CAL_SELF_PARAM_PHASE     b;
}   PHY_DFE_DBE_RXDFE_IQDC_CAL_SELF_PARAM_PHASE_U;


//---------------------------------------------------------
// PHY_DFE_DBE Register Map
//---------------------------------------------------------
typedef struct {
    volatile PHY_DFE_DBE_AH_TX_DFE_LPF00_U                          AH_TX_DFE_LPF00                        ; // 0x0000
    volatile PHY_DFE_DBE_AH_TX_DFE_LPF01_U                          AH_TX_DFE_LPF01                        ; // 0x0004
    volatile PHY_DFE_DBE_AH_TX_DFE_LPF02_U                          AH_TX_DFE_LPF02                        ; // 0x0008
    volatile uint32_t                                          RESERVED0                              ; // 
    volatile PHY_DFE_DBE_AH_TX_DFE_LPF04_U                          AH_TX_DFE_LPF04                        ; // 0x0010
    volatile PHY_DFE_DBE_AH_TX_DFE_LPF05_U                          AH_TX_DFE_LPF05                        ; // 0x0014
    volatile PHY_DFE_DBE_AH_TX_DFE_LPF06_U                          AH_TX_DFE_LPF06                        ; // 0x0018
    volatile PHY_DFE_DBE_AH_TX_DFE_LPF07_U                          AH_TX_DFE_LPF07                        ; // 0x001c
    volatile PHY_DFE_DBE_AH_TX_DFE_LPF08_U                          AH_TX_DFE_LPF08                        ; // 0x0020
    volatile PHY_DFE_DBE_AH_TX_DFE_LPF09_U                          AH_TX_DFE_LPF09                        ; // 0x0024
    volatile PHY_DFE_DBE_AH_TX_DFE_LPF10_U                          AH_TX_DFE_LPF10                        ; // 0x0028
    volatile PHY_DFE_DBE_AH_TX_DFE_LPF11_U                          AH_TX_DFE_LPF11                        ; // 0x002c
    volatile PHY_DFE_DBE_AH_TX_DFE_LPF12_U                          AH_TX_DFE_LPF12                        ; // 0x0030
    volatile PHY_DFE_DBE_AH_TX_DFE_LPF13_U                          AH_TX_DFE_LPF13                        ; // 0x0034
    volatile PHY_DFE_DBE_AH_TX_DFE_LPF14_U                          AH_TX_DFE_LPF14                        ; // 0x0038
    volatile PHY_DFE_DBE_AH_TX_DFE_LPF15_U                          AH_TX_DFE_LPF15                        ; // 0x003c
    volatile PHY_DFE_DBE_AH_TX_DFE_LPF16_U                          AH_TX_DFE_LPF16                        ; // 0x0040
    volatile uint32_t                                          RESERVED1[239]                         ; // 
    volatile PHY_DFE_DBE_AH_TX_DFE_CAL00_U                          AH_TX_DFE_CAL00                        ; // 0x0400
    volatile PHY_DFE_DBE_AH_TX_DFE_CAL01_U                          AH_TX_DFE_CAL01                        ; // 0x0404
    volatile PHY_DFE_DBE_AH_TX_DFE_CAL02_U                          AH_TX_DFE_CAL02                        ; // 0x0408
    volatile PHY_DFE_DBE_AH_TX_DFE_CAL03_U                          AH_TX_DFE_CAL03                        ; // 0x040c
    volatile PHY_DFE_DBE_AH_TX_DFE_CAL04_U                          AH_TX_DFE_CAL04                        ; // 0x0410
    volatile uint32_t                                          RESERVED2[1531]                        ; // 
    volatile PHY_DFE_DBE_PHY_TXSBR00_U                              PHY_TXSBR00                            ; // 0x1c00
    volatile PHY_DFE_DBE_PHY_TXSBR01_U                              PHY_TXSBR01                            ; // 0x1c04
    volatile PHY_DFE_DBE_PHY_TXSBR02_U                              PHY_TXSBR02                            ; // 0x1c08
    volatile PHY_DFE_DBE_PHY_TXSBR03_U                              PHY_TXSBR03                            ; // 0x1c0c
    volatile PHY_DFE_DBE_PHY_TXSBR04_U                              PHY_TXSBR04                            ; // 0x1c10
    volatile PHY_DFE_DBE_PHY_TXSBR05_U                              PHY_TXSBR05                            ; // 0x1c14
    volatile uint32_t                                          RESERVED3[250]                         ; // 
    volatile PHY_DFE_DBE_RX_DFE00_U                                 RX_DFE00                               ; // 0x2000
    volatile PHY_DFE_DBE_RX_DFE01_U                                 RX_DFE01                               ; // 0x2004
    volatile PHY_DFE_DBE_RX_DFE02_U                                 RX_DFE02                               ; // 0x2008
    volatile PHY_DFE_DBE_RX_DFE03_U                                 RX_DFE03                               ; // 0x200c
    volatile PHY_DFE_DBE_RX_DFE04_U                                 RX_DFE04                               ; // 0x2010
    volatile uint32_t                                          RESERVED4[2]                           ; // 
    volatile PHY_DFE_DBE_RX_DFE07_U                                 RX_DFE07                               ; // 0x201c
    volatile PHY_DFE_DBE_RX_DFE08_U                                 RX_DFE08                               ; // 0x2020
    volatile PHY_DFE_DBE_RX_DFE09_U                                 RX_DFE09                               ; // 0x2024
    volatile PHY_DFE_DBE_RX_DFE10_U                                 RX_DFE10                               ; // 0x2028
    volatile PHY_DFE_DBE_RX_DFE11_U                                 RX_DFE11                               ; // 0x202c
    volatile PHY_DFE_DBE_RX_DFE12_U                                 RX_DFE12                               ; // 0x2030
    volatile PHY_DFE_DBE_RX_DFE13_U                                 RX_DFE13                               ; // 0x2034
    volatile PHY_DFE_DBE_RX_DFE14_U                                 RX_DFE14                               ; // 0x2038
    volatile PHY_DFE_DBE_RX_DFE15_U                                 RX_DFE15                               ; // 0x203c
    volatile PHY_DFE_DBE_RX_DFE16_U                                 RX_DFE16                               ; // 0x2040
    volatile PHY_DFE_DBE_RX_DFE17_U                                 RX_DFE17                               ; // 0x2044
    volatile uint32_t                                          RESERVED5[10]                          ; // 
    volatile PHY_DFE_DBE_RX_DFE_TIMER00_U                           RX_DFE_TIMER00                         ; // 0x2070
    volatile uint32_t                                          RESERVED6[2]                           ; // 
    volatile PHY_DFE_DBE_RX_DFE_TIMER03_U                           RX_DFE_TIMER03                         ; // 0x207c
    volatile uint32_t                                          RESERVED7[8]                           ; // 
    volatile PHY_DFE_DBE_RX_DFE_TIMER12_U                           RX_DFE_TIMER12                         ; // 0x20a0
    volatile uint32_t                                          RESERVED8[3]                           ; // 
    volatile PHY_DFE_DBE_RX_DFE_LOG_CFG_U                           RX_DFE_LOG_CFG                         ; // 0x20b0
    volatile PHY_DFE_DBE_RX_DFE_LOG00_U                             RX_DFE_LOG00                           ; // 0x20b4
    volatile PHY_DFE_DBE_RX_DFE_LOG01_U                             RX_DFE_LOG01                           ; // 0x20b8
    volatile PHY_DFE_DBE_RX_DFE_LOG02_U                             RX_DFE_LOG02                           ; // 0x20bc
    volatile PHY_DFE_DBE_RX_DFE_LOG03_U                             RX_DFE_LOG03                           ; // 0x20c0
    volatile PHY_DFE_DBE_RX_DFE_LOG04_U                             RX_DFE_LOG04                           ; // 0x20c4
    volatile PHY_DFE_DBE_RX_DFE_LOG05_U                             RX_DFE_LOG05                           ; // 0x20c8
    volatile PHY_DFE_DBE_RX_DFE_LOG06_U                             RX_DFE_LOG06                           ; // 0x20cc
    volatile PHY_DFE_DBE_RX_DFE_LOG07_U                             RX_DFE_LOG07                           ; // 0x20d0
    volatile PHY_DFE_DBE_RX_DFE_LOG08_U                             RX_DFE_LOG08                           ; // 0x20d4
    volatile PHY_DFE_DBE_RX_DFE_LOG09_U                             RX_DFE_LOG09                           ; // 0x20d8
    volatile PHY_DFE_DBE_RX_DFE_LOG10_U                             RX_DFE_LOG10                           ; // 0x20dc
    volatile PHY_DFE_DBE_RX_DFE_LOG11_U                             RX_DFE_LOG11                           ; // 0x20e0
    volatile PHY_DFE_DBE_RX_DFE_LOG12_U                             RX_DFE_LOG12                           ; // 0x20e4
    volatile PHY_DFE_DBE_RX_DFE_LOG13_U                             RX_DFE_LOG13                           ; // 0x20e8
    volatile PHY_DFE_DBE_RX_DFE_LOG14_U                             RX_DFE_LOG14                           ; // 0x20ec
    volatile PHY_DFE_DBE_RX_DFE_LOG15_U                             RX_DFE_LOG15                           ; // 0x20f0
    volatile PHY_DFE_DBE_RX_DFE_LOG16_U                             RX_DFE_LOG16                           ; // 0x20f4
    volatile PHY_DFE_DBE_RX_DFE_LOG17_U                             RX_DFE_LOG17                           ; // 0x20f8
    volatile PHY_DFE_DBE_RX_DFE_LOG18_U                             RX_DFE_LOG18                           ; // 0x20fc
    volatile PHY_DFE_DBE_RX_DFE_LOG19_U                             RX_DFE_LOG19                           ; // 0x2100
    volatile PHY_DFE_DBE_RX_DFE_LOG20_U                             RX_DFE_LOG20                           ; // 0x2104
    volatile PHY_DFE_DBE_RX_DFE_LOG21_U                             RX_DFE_LOG21                           ; // 0x2108
    volatile PHY_DFE_DBE_RX_DFE_LOG22_U                             RX_DFE_LOG22                           ; // 0x210c
    volatile PHY_DFE_DBE_RX_DFE_LOG23_U                             RX_DFE_LOG23                           ; // 0x2110
    volatile PHY_DFE_DBE_RX_DFE_LOG24_U                             RX_DFE_LOG24                           ; // 0x2114
    volatile PHY_DFE_DBE_RX_DFE_LOG25_U                             RX_DFE_LOG25                           ; // 0x2118
    volatile PHY_DFE_DBE_RX_DFE_LOG26_U                             RX_DFE_LOG26                           ; // 0x211c
    volatile PHY_DFE_DBE_RX_DFE_LOG27_U                             RX_DFE_LOG27                           ; // 0x2120
    volatile PHY_DFE_DBE_RX_DFE_LOG28_U                             RX_DFE_LOG28                           ; // 0x2124
    volatile PHY_DFE_DBE_RX_DFE_LOG29_U                             RX_DFE_LOG29                           ; // 0x2128
    volatile PHY_DFE_DBE_RX_DFE_LOG30_U                             RX_DFE_LOG30                           ; // 0x212c
    volatile PHY_DFE_DBE_RX_DFE_LOG31_U                             RX_DFE_LOG31                           ; // 0x2130
    volatile PHY_DFE_DBE_RX_DFE_LOG32_U                             RX_DFE_LOG32                           ; // 0x2134
    volatile PHY_DFE_DBE_RX_DFE_LOG33_U                             RX_DFE_LOG33                           ; // 0x2138
    volatile PHY_DFE_DBE_RX_DFE_LOG34_U                             RX_DFE_LOG34                           ; // 0x213c
    volatile PHY_DFE_DBE_RX_DFE_LOG35_U                             RX_DFE_LOG35                           ; // 0x2140
    volatile PHY_DFE_DBE_RX_DFE_LOG36_U                             RX_DFE_LOG36                           ; // 0x2144
    volatile PHY_DFE_DBE_RX_DFE_LOG37_U                             RX_DFE_LOG37                           ; // 0x2148
    volatile PHY_DFE_DBE_RX_DFE_LOG38_U                             RX_DFE_LOG38                           ; // 0x214c
    volatile PHY_DFE_DBE_RX_DFE_LOG39_U                             RX_DFE_LOG39                           ; // 0x2150
    volatile uint32_t                                          RESERVED9[171]                         ; // 
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_00_U                        AHA1_RXDFE_AGC_00                      ; // 0x2400
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_01_U                        AHA1_RXDFE_AGC_01                      ; // 0x2404
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_02_U                        AHA1_RXDFE_AGC_02                      ; // 0x2408
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_03_U                        AHA1_RXDFE_AGC_03                      ; // 0x240c
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_04_U                        AHA1_RXDFE_AGC_04                      ; // 0x2410
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_05_U                        AHA1_RXDFE_AGC_05                      ; // 0x2414
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_06_U                        AHA1_RXDFE_AGC_06                      ; // 0x2418
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_07_U                        AHA1_RXDFE_AGC_07                      ; // 0x241c
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_08_U                        AHA1_RXDFE_AGC_08                      ; // 0x2420
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_09_U                        AHA1_RXDFE_AGC_09                      ; // 0x2424
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_10_U                        AHA1_RXDFE_AGC_10                      ; // 0x2428
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_11_U                        AHA1_RXDFE_AGC_11                      ; // 0x242c
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_12_U                        AHA1_RXDFE_AGC_12                      ; // 0x2430
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_13_U                        AHA1_RXDFE_AGC_13                      ; // 0x2434
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_14_U                        AHA1_RXDFE_AGC_14                      ; // 0x2438
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_15_U                        AHA1_RXDFE_AGC_15                      ; // 0x243c
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_16_U                        AHA1_RXDFE_AGC_16                      ; // 0x2440
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_17_U                        AHA1_RXDFE_AGC_17                      ; // 0x2444
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_18_U                        AHA1_RXDFE_AGC_18                      ; // 0x2448
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_19_U                        AHA1_RXDFE_AGC_19                      ; // 0x244c
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_20_U                        AHA1_RXDFE_AGC_20                      ; // 0x2450
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_21_U                        AHA1_RXDFE_AGC_21                      ; // 0x2454
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_22_U                        AHA1_RXDFE_AGC_22                      ; // 0x2458
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_23_U                        AHA1_RXDFE_AGC_23                      ; // 0x245c
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_24_U                        AHA1_RXDFE_AGC_24                      ; // 0x2460
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_25_U                        AHA1_RXDFE_AGC_25                      ; // 0x2464
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_26_U                        AHA1_RXDFE_AGC_26                      ; // 0x2468
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_27_U                        AHA1_RXDFE_AGC_27                      ; // 0x246c
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_28_U                        AHA1_RXDFE_AGC_28                      ; // 0x2470
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_29_U                        AHA1_RXDFE_AGC_29                      ; // 0x2474
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_30_U                        AHA1_RXDFE_AGC_30                      ; // 0x2478
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_31_U                        AHA1_RXDFE_AGC_31                      ; // 0x247c
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_32_U                        AHA1_RXDFE_AGC_32                      ; // 0x2480
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_33_U                        AHA1_RXDFE_AGC_33                      ; // 0x2484
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_34_U                        AHA1_RXDFE_AGC_34                      ; // 0x2488
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_35_U                        AHA1_RXDFE_AGC_35                      ; // 0x248c
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_36_U                        AHA1_RXDFE_AGC_36                      ; // 0x2490
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_37_U                        AHA1_RXDFE_AGC_37                      ; // 0x2494
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_38_U                        AHA1_RXDFE_AGC_38                      ; // 0x2498
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_39_U                        AHA1_RXDFE_AGC_39                      ; // 0x249c
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_40_U                        AHA1_RXDFE_AGC_40                      ; // 0x24a0
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_41_U                        AHA1_RXDFE_AGC_41                      ; // 0x24a4
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_42_U                        AHA1_RXDFE_AGC_42                      ; // 0x24a8
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_43_U                        AHA1_RXDFE_AGC_43                      ; // 0x24ac
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_44_U                        AHA1_RXDFE_AGC_44                      ; // 0x24b0
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_45_U                        AHA1_RXDFE_AGC_45                      ; // 0x24b4
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_46_U                        AHA1_RXDFE_AGC_46                      ; // 0x24b8
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_47_U                        AHA1_RXDFE_AGC_47                      ; // 0x24bc
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_48_U                        AHA1_RXDFE_AGC_48                      ; // 0x24c0
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_49_U                        AHA1_RXDFE_AGC_49                      ; // 0x24c4
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_50_U                        AHA1_RXDFE_AGC_50                      ; // 0x24c8
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_51_U                        AHA1_RXDFE_AGC_51                      ; // 0x24cc
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_52_U                        AHA1_RXDFE_AGC_52                      ; // 0x24d0
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_53_U                        AHA1_RXDFE_AGC_53                      ; // 0x24d4
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_54_U                        AHA1_RXDFE_AGC_54                      ; // 0x24d8
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_55_U                        AHA1_RXDFE_AGC_55                      ; // 0x24dc
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_56_U                        AHA1_RXDFE_AGC_56                      ; // 0x24e0
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_57_U                        AHA1_RXDFE_AGC_57                      ; // 0x24e4
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_58_U                        AHA1_RXDFE_AGC_58                      ; // 0x24e8
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_59_U                        AHA1_RXDFE_AGC_59                      ; // 0x24ec
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_60_U                        AHA1_RXDFE_AGC_60                      ; // 0x24f0
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_61_U                        AHA1_RXDFE_AGC_61                      ; // 0x24f4
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_62_U                        AHA1_RXDFE_AGC_62                      ; // 0x24f8
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_63_U                        AHA1_RXDFE_AGC_63                      ; // 0x24fc
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_64_U                        AHA1_RXDFE_AGC_64                      ; // 0x2500
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_65_U                        AHA1_RXDFE_AGC_65                      ; // 0x2504
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_66_U                        AHA1_RXDFE_AGC_66                      ; // 0x2508
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_67_U                        AHA1_RXDFE_AGC_67                      ; // 0x250c
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_68_U                        AHA1_RXDFE_AGC_68                      ; // 0x2510
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_69_U                        AHA1_RXDFE_AGC_69                      ; // 0x2514
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_70_U                        AHA1_RXDFE_AGC_70                      ; // 0x2518
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_71_U                        AHA1_RXDFE_AGC_71                      ; // 0x251c
    volatile PHY_DFE_DBE_AHA1_RXDFE_AGC_72_U                        AHA1_RXDFE_AGC_72                      ; // 0x2520
    volatile uint32_t                                          RESERVED10[183]                        ; // 
    volatile PHY_DFE_DBE_AHA1_RXDFE_LPF_00_U                        AHA1_RXDFE_LPF_00                      ; // 0x2800
    volatile PHY_DFE_DBE_AHA1_RXDFE_LPF_01_U                        AHA1_RXDFE_LPF_01                      ; // 0x2804
    volatile PHY_DFE_DBE_AHA1_RXDFE_LPF_02_U                        AHA1_RXDFE_LPF_02                      ; // 0x2808
    volatile PHY_DFE_DBE_AHA1_RXDFE_LPF_03_U                        AHA1_RXDFE_LPF_03                      ; // 0x280c
    volatile PHY_DFE_DBE_AHA1_RXDFE_LPF_04_U                        AHA1_RXDFE_LPF_04                      ; // 0x2810
    volatile uint32_t                                          RESERVED11[251]                        ; // 
    volatile PHY_DFE_DBE_AH_RX_SYNC_1MTHRE_U                        AH_RX_SYNC_1MTHRE                      ; // 0x2c00
    volatile PHY_DFE_DBE_AH_RX_SYNC_1MSTF1_U                        AH_RX_SYNC_1MSTF1                      ; // 0x2c04
    volatile PHY_DFE_DBE_AH_RX_SYNC_1MSTF2_U                        AH_RX_SYNC_1MSTF2                      ; // 0x2c08
    volatile PHY_DFE_DBE_AH_RX_SYNC_1MFSYNC_U                       AH_RX_SYNC_1MFSYNC                     ; // 0x2c0c
    volatile PHY_DFE_DBE_AH_RX_SYNC_1MCFO1_U                        AH_RX_SYNC_1MCFO1                      ; // 0x2c10
    volatile PHY_DFE_DBE_AH_RX_SYNC_1MCFO2_U                        AH_RX_SYNC_1MCFO2                      ; // 0x2c14
    volatile PHY_DFE_DBE_AH_RX_SYNC_1MCTRL_U                        AH_RX_SYNC_1MCTRL                      ; // 0x2c18
    volatile uint32_t                                          RESERVED12                             ; // 
    volatile PHY_DFE_DBE_AH_RX_SYNC_2MTHRE_U                        AH_RX_SYNC_2MTHRE                      ; // 0x2c20
    volatile PHY_DFE_DBE_AH_RX_SYNC_2MSTF_U                         AH_RX_SYNC_2MSTF                       ; // 0x2c24
    volatile PHY_DFE_DBE_AH_RX_SYNC_2MFSYNC_U                       AH_RX_SYNC_2MFSYNC                     ; // 0x2c28
    volatile PHY_DFE_DBE_AH_RX_SYNC_2MCFO_U                         AH_RX_SYNC_2MCFO                       ; // 0x2c2c
    volatile PHY_DFE_DBE_AH_RX_SYNC_CFOERR_U                        AH_RX_SYNC_CFOERR                      ; // 0x2c30
    volatile PHY_DFE_DBE_AH_RX_SYNC_FLTDLY1M_U                      AH_RX_SYNC_FLTDLY1M                    ; // 0x2c34
    volatile PHY_DFE_DBE_AH_RX_SYNC_FLTDLY2M_U                      AH_RX_SYNC_FLTDLY2M                    ; // 0x2c38
    volatile PHY_DFE_DBE_AH_RX_SYNC_XCORRMIN_U                      AH_RX_SYNC_XCORRMIN                    ; // 0x2c3c
    volatile PHY_DFE_DBE_AH_RX_SYNC_FSYNCD_U                        AH_RX_SYNC_FSYNCD                      ; // 0x2c40
    volatile PHY_DFE_DBE_AH_RX_SYNC_SNRESTD_U                       AH_RX_SYNC_SNRESTD                     ; // 0x2c44
    volatile uint32_t                                          RESERVED13[238]                        ; // 
    volatile PHY_DFE_DBE_AH_PHTRK_EST_00_U                          AH_PHTRK_EST_00                        ; // 0x3000
    volatile PHY_DFE_DBE_AH_PHTRK_EST_01_U                          AH_PHTRK_EST_01                        ; // 0x3004
    volatile PHY_DFE_DBE_AH_PHTRK_EST_02_U                          AH_PHTRK_EST_02                        ; // 0x3008
    volatile PHY_DFE_DBE_AH_PHTRK_EST_03_U                          AH_PHTRK_EST_03                        ; // 0x300c
    volatile uint32_t                                          RESERVED14[252]                        ; // 
    volatile PHY_DFE_DBE_AH_RX_CS00_U                               AH_RX_CS00                             ; // 0x3400
    volatile PHY_DFE_DBE_AH_RX_CS01_U                               AH_RX_CS01                             ; // 0x3404
    volatile PHY_DFE_DBE_AH_RX_CS02_U                               AH_RX_CS02                             ; // 0x3408
    volatile PHY_DFE_DBE_AH_RX_CS03_U                               AH_RX_CS03                             ; // 0x340c
    volatile PHY_DFE_DBE_AH_RX_CS04_U                               AH_RX_CS04                             ; // 0x3410
    volatile PHY_DFE_DBE_AH_RX_CS05_U                               AH_RX_CS05                             ; // 0x3414
    volatile uint32_t                                          RESERVED15[10]                         ; // 
    volatile PHY_DFE_DBE_AH_RX_CS10_U                               AH_RX_CS10                             ; // 0x3440
    volatile PHY_DFE_DBE_AH_RX_CS11_U                               AH_RX_CS11                             ; // 0x3444
    volatile PHY_DFE_DBE_AH_RX_CS12_U                               AH_RX_CS12                             ; // 0x3448
    volatile PHY_DFE_DBE_AH_RX_CS13_U                               AH_RX_CS13                             ; // 0x344c
    volatile PHY_DFE_DBE_AH_RX_CS14_U                               AH_RX_CS14                             ; // 0x3450
    volatile PHY_DFE_DBE_AH_RX_CS15_U                               AH_RX_CS15                             ; // 0x3454
    volatile PHY_DFE_DBE_AH_RX_CS16_U                               AH_RX_CS16                             ; // 0x3458
    volatile uint32_t                                          RESERVED16[9]                          ; // 
    volatile PHY_DFE_DBE_AH_RX_CS20_U                               AH_RX_CS20                             ; // 0x3480
    volatile PHY_DFE_DBE_AH_RX_CS21_U                               AH_RX_CS21                             ; // 0x3484
    volatile PHY_DFE_DBE_AH_RX_CS22_U                               AH_RX_CS22                             ; // 0x3488
    volatile PHY_DFE_DBE_AH_RX_CS23_U                               AH_RX_CS23                             ; // 0x348c
    volatile PHY_DFE_DBE_AH_RX_CS24_U                               AH_RX_CS24                             ; // 0x3490
    volatile uint32_t                                          RESERVED17[475]                        ; // 
    volatile PHY_DFE_DBE_RXDFE_IQDC_HPF_ON_U                        RXDFE_IQDC_HPF_ON                      ; // 0x3c00
    volatile PHY_DFE_DBE_RXDFE_IQDC_HPF_WHILE_AGC_U                 RXDFE_IQDC_HPF_WHILE_AGC               ; // 0x3c04
    volatile PHY_DFE_DBE_RXDFE_IQDC_HPF_WGT0_U                      RXDFE_IQDC_HPF_WGT0                    ; // 0x3c08
    volatile PHY_DFE_DBE_RXDFE_IQDC_HPF_WGT1_U                      RXDFE_IQDC_HPF_WGT1                    ; // 0x3c0c
    volatile PHY_DFE_DBE_RXDFE_IQDC_HPF_WGT2_U                      RXDFE_IQDC_HPF_WGT2                    ; // 0x3c10
    volatile PHY_DFE_DBE_RXDFE_IQDC_HPF_DUR_WGT2_U                  RXDFE_IQDC_HPF_DUR_WGT2                ; // 0x3c14
    volatile PHY_DFE_DBE_RXDFE_IQDC_LUT_CFG_U                       RXDFE_IQDC_LUT_CFG                     ; // 0x3c18
    volatile PHY_DFE_DBE_RXDFE_IQDC_LUT_ALG_U                       RXDFE_IQDC_LUT_ALG                     ; // 0x3c1c
    volatile PHY_DFE_DBE_RXDFE_IQDC_LUT_WRITE_U                     RXDFE_IQDC_LUT_WRITE                   ; // 0x3c20
    volatile PHY_DFE_DBE_RXDFE_IQDC_LUT_READ_U                      RXDFE_IQDC_LUT_READ                    ; // 0x3c24
    volatile PHY_DFE_DBE_RXDFE_IQDC_LUT_READ_RES_U                  RXDFE_IQDC_LUT_READ_RES                ; // 0x3c28
    volatile PHY_DFE_DBE_RXDFE_IQDC_LUT_AUTO_RES_U                  RXDFE_IQDC_LUT_AUTO_RES                ; // 0x3c2c
    volatile PHY_DFE_DBE_RXDFE_IQDC_CAL_PARA0_U                     RXDFE_IQDC_CAL_PARA0                   ; // 0x3c30
    volatile PHY_DFE_DBE_RXDFE_IQDC_CAL_PARA1_U                     RXDFE_IQDC_CAL_PARA1                   ; // 0x3c34
    volatile PHY_DFE_DBE_RXDFE_IQDC_CAL_SELF_VAL_U                  RXDFE_IQDC_CAL_SELF_VAL                ; // 0x3c38
    volatile PHY_DFE_DBE_RXDFE_IQDC_CAL_SELF_PARAM_GAIN_U           RXDFE_IQDC_CAL_SELF_PARAM_GAIN         ; // 0x3c3c
    volatile PHY_DFE_DBE_RXDFE_IQDC_CAL_SELF_PARAM_PHASE_U          RXDFE_IQDC_CAL_SELF_PARAM_PHASE        ; // 0x3c40
} PHY_DFE_DBE_Type;

#ifdef __cplusplus
}
#endif

#endif /* __REG_PHY_DFE_DBE_H__ */
