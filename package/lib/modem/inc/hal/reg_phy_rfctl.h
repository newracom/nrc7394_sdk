/*********************************************************************/
/*    Newracom Library / IP Product                                  */
/*    Product Name :                                                 */
/*    Version      :                                                 */
/*    Author       :                                                 */
/*    Update       :                                                 */
/*********************************************************************/

#ifndef __REG_PHY_RFCTL_H__
#define __REG_PHY_RFCTL_H__

#ifdef __cplusplus
extern "C"{
#endif

// 0x4008E004 register ------------------------------------
typedef struct {
    uint32_t                      r_reg_manual_tx_en                  :1 ;
    uint32_t                      reserved0                           :31;
}   PHY_RFCTL_AH_RFAFE_INT_01;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_01     b;
}   PHY_RFCTL_AH_RFAFE_INT_01_U;


// 0x4008E008 register ------------------------------------
typedef struct {
    uint32_t                      r3_reg_spi_sclk_rate                :3 ;
    uint32_t                      r5_reg_spi_tx_length                :5 ;
    uint32_t                      r2_reg_spi_rf_mode                  :2 ;
    uint32_t                      r_reg_spi_manual_mode               :1 ;
    uint32_t                      reserved0                           :20;
    uint32_t                      r_reg_spi_sync_reset                :1 ;
}   PHY_RFCTL_AH_RFAFE_INT_02;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_02     b;
}   PHY_RFCTL_AH_RFAFE_INT_02_U;


// 0x4008E00C register ------------------------------------
typedef struct {
    uint32_t                      r_reg_spi_hw_self_mode              :1 ;
    uint32_t                      reserved0                           :31;
}   PHY_RFCTL_AH_RFAFE_INT_03;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_03     b;
}   PHY_RFCTL_AH_RFAFE_INT_03_U;


// 0x4008E010 register ------------------------------------
typedef struct {
    uint32_t                      r16_reg_spi_wait                    :16;
    uint32_t                      reserved0                           :16;
}   PHY_RFCTL_AH_RFAFE_INT_04;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_04     b;
}   PHY_RFCTL_AH_RFAFE_INT_04_U;


// 0x4008E014 register ------------------------------------
typedef struct {
    uint32_t                      r5_reg_rf_center_freq               :5 ;
    uint32_t                      reserved0                           :27;
}   PHY_RFCTL_AH_RFAFE_INT_05;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_05     b;
}   PHY_RFCTL_AH_RFAFE_INT_05_U;


// 0x4008E018 register ------------------------------------
typedef struct {
    uint32_t                      i_reg_hw_self_config_done           :1 ;
    uint32_t                      reserved0                           :31;
}   PHY_RFCTL_AH_RFAFE_INT_06;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_06     b;
}   PHY_RFCTL_AH_RFAFE_INT_06_U;


// 0x4008E01C register ------------------------------------
typedef struct {
    uint32_t                      r32_reg_spi_sw_tx_data              :32;
}   PHY_RFCTL_AH_RFAFE_INT_07;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_07     b;
}   PHY_RFCTL_AH_RFAFE_INT_07_U;


// 0x4008E020 register ------------------------------------
typedef struct {
    uint32_t                      r7_reg_int_paon_delay               :7 ;
    uint32_t                      reserved0                           :25;
}   PHY_RFCTL_AH_RFAFE_INT_08;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_08     b;
}   PHY_RFCTL_AH_RFAFE_INT_08_U;


// 0x4008E024 register ------------------------------------
typedef struct {
    uint32_t                      i6_reg_spi_config                   :6 ;
    uint32_t                      reserved0                           :26;
}   PHY_RFCTL_AH_RFAFE_INT_09;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_09     b;
}   PHY_RFCTL_AH_RFAFE_INT_09_U;


// 0x4008E028 register ------------------------------------
typedef struct {
    uint32_t                      i32_reg_spi_wr_data                 :32;
}   PHY_RFCTL_AH_RFAFE_INT_10;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_10     b;
}   PHY_RFCTL_AH_RFAFE_INT_10_U;


// 0x4008E02C register ------------------------------------
typedef struct {
    uint32_t                      i32_reg_spi_rd_data                 :32;
}   PHY_RFCTL_AH_RFAFE_INT_11;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_11     b;
}   PHY_RFCTL_AH_RFAFE_INT_11_U;


// 0x4008E030 register ------------------------------------
typedef struct {
    uint32_t                      i2_reg_spi_access_status            :2 ;
    uint32_t                      reserved0                           :30;
}   PHY_RFCTL_AH_RFAFE_INT_12;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_12     b;
}   PHY_RFCTL_AH_RFAFE_INT_12_U;


// 0x4008E034 register ------------------------------------
typedef struct {
    uint32_t                      r8_reg_rf_ctl_config                :8 ;
    uint32_t                      reserved0                           :24;
}   PHY_RFCTL_AH_RFAFE_INT_13;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_13     b;
}   PHY_RFCTL_AH_RFAFE_INT_13_U;


// 0x4008E038 register ------------------------------------
typedef struct {
    uint32_t                      r7_reg_txen_delay                   :7 ;
    uint32_t                      reserved0                           :25;
}   PHY_RFCTL_AH_RFAFE_INT_14;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_14     b;
}   PHY_RFCTL_AH_RFAFE_INT_14_U;


// 0x4008E03C register ------------------------------------
typedef struct {
    uint32_t                      r7_reg_paon_delay                   :7 ;
    uint32_t                      reserved0                           :25;
}   PHY_RFCTL_AH_RFAFE_INT_15;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_15     b;
}   PHY_RFCTL_AH_RFAFE_INT_15_U;


// 0x4008E040 register ------------------------------------
typedef struct {
    uint32_t                      r_reg_shdn                          :1 ;
    uint32_t                      reserved0                           :31;
}   PHY_RFCTL_AH_RFAFE_INT_16;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_16     b;
}   PHY_RFCTL_AH_RFAFE_INT_16_U;


// 0x4008E044 register ------------------------------------
typedef struct {
    uint32_t                      r_reg_standby                       :1 ;
    uint32_t                      reserved0                           :31;
}   PHY_RFCTL_AH_RFAFE_INT_17;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_17     b;
}   PHY_RFCTL_AH_RFAFE_INT_17_U;


// 0x4008E048 register ------------------------------------
typedef struct {
    uint32_t                      r7_reg_rf_txgain_ctl                :7 ;
    uint32_t                      reserved0                           :25;
}   PHY_RFCTL_AH_RFAFE_INT_18;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_18     b;
}   PHY_RFCTL_AH_RFAFE_INT_18_U;


// 0x4008E04C register ------------------------------------
typedef struct {
    uint32_t                      r2_reg_rfgain_load_option           :2 ;
    uint32_t                      reserved0                           :30;
}   PHY_RFCTL_AH_RFAFE_INT_19;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_19     b;
}   PHY_RFCTL_AH_RFAFE_INT_19_U;


// 0x4008E050 register ------------------------------------
typedef struct {
    uint32_t                      r2_reg_addac_offset_bin             :2 ;
    uint32_t                      reserved0                           :30;
}   PHY_RFCTL_AH_RFAFE_INT_20;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_20     b;
}   PHY_RFCTL_AH_RFAFE_INT_20_U;


// 0x4008E054 register ------------------------------------
typedef struct {
    uint32_t                      r2_reg_addac_iq_swap                :2 ;
    uint32_t                      reserved0                           :30;
}   PHY_RFCTL_AH_RFAFE_INT_21;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_21     b;
}   PHY_RFCTL_AH_RFAFE_INT_21_U;


// 0x4008E058 register ------------------------------------
typedef struct {
    uint32_t                      r20_reg_rfgain_ctl_manual           :20;
    uint32_t                      reserved0                           :12;
}   PHY_RFCTL_AH_RFAFE_INT_22;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_22     b;
}   PHY_RFCTL_AH_RFAFE_INT_22_U;


// 0x4008E05C register ------------------------------------
typedef struct {
    uint32_t                      r_reg_rf_sel                        :1 ;
    uint32_t                      reserved0                           :31;
}   PHY_RFCTL_AH_RFAFE_INT_23;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_23     b;
}   PHY_RFCTL_AH_RFAFE_INT_23_U;


// 0x4008E060 register ------------------------------------
typedef struct {
    uint32_t                      r2_reg_loiqcal_mode                 :2 ;
    uint32_t                      reserved0                           :30;
}   PHY_RFCTL_AH_RFAFE_INT_24;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_24     b;
}   PHY_RFCTL_AH_RFAFE_INT_24_U;


// 0x4008E064 register ------------------------------------
typedef struct {
    uint32_t                      r2_reg_loiqcal_tone_freq            :2 ;
    uint32_t                      reserved0                           :30;
}   PHY_RFCTL_AH_RFAFE_INT_25;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_25     b;
}   PHY_RFCTL_AH_RFAFE_INT_25_U;


// 0x4008E068 register ------------------------------------
typedef struct {
    uint32_t                      r_reg_loiqcal_en                    :1 ;
    uint32_t                      reserved0                           :31;
}   PHY_RFCTL_AH_RFAFE_INT_26;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_26     b;
}   PHY_RFCTL_AH_RFAFE_INT_26_U;


// 0x4008E06C register ------------------------------------
typedef struct {
    uint32_t                      r8_reg_loiqcal_loopback_delay       :8 ;
    uint32_t                      reserved0                           :24;
}   PHY_RFCTL_AH_RFAFE_INT_27;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_27     b;
}   PHY_RFCTL_AH_RFAFE_INT_27_U;


// 0x4008E070 register ------------------------------------
typedef struct {
    uint32_t                      r2_reg_loiqcal_len                  :2 ;
    uint32_t                      reserved0                           :30;
}   PHY_RFCTL_AH_RFAFE_INT_28;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_28     b;
}   PHY_RFCTL_AH_RFAFE_INT_28_U;


// 0x4008E074 register ------------------------------------
typedef struct {
    uint32_t                      r_reg_loiqcal_stg_test              :1 ;
    uint32_t                      reserved0                           :31;
}   PHY_RFCTL_AH_RFAFE_INT_29;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_29     b;
}   PHY_RFCTL_AH_RFAFE_INT_29_U;


// 0x4008E078 register ------------------------------------
typedef struct {
    uint32_t                      i_reg_loiqcal_error                 :1 ;
    uint32_t                      reserved0                           :31;
}   PHY_RFCTL_AH_RFAFE_INT_30;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_30     b;
}   PHY_RFCTL_AH_RFAFE_INT_30_U;


// 0x4008E07C register ------------------------------------
typedef struct {
    uint32_t                      i_reg_loiqcal_val                   :1 ;
    uint32_t                      reserved0                           :31;
}   PHY_RFCTL_AH_RFAFE_INT_31;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_31     b;
}   PHY_RFCTL_AH_RFAFE_INT_31_U;


// 0x4008E080 register ------------------------------------
typedef struct {
    uint32_t                      i15_reg_loiqcal_out_i               :5 ;
    uint32_t                      reserved0                           :27;
}   PHY_RFCTL_AH_RFAFE_INT_32;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_32     b;
}   PHY_RFCTL_AH_RFAFE_INT_32_U;


// 0x4008E084 register ------------------------------------
typedef struct {
    uint32_t                      i15_reg_loiqcal_out_q               :5 ;
    uint32_t                      reserved0                           :27;
}   PHY_RFCTL_AH_RFAFE_INT_33;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_33     b;
}   PHY_RFCTL_AH_RFAFE_INT_33_U;


// 0x4008E088 register ------------------------------------
typedef struct {
    uint32_t                      r11_reg_loiqcal_txiq_para_0         :11;
    uint32_t                      reserved0                           :21;
}   PHY_RFCTL_AH_RFAFE_INT_34;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_34     b;
}   PHY_RFCTL_AH_RFAFE_INT_34_U;


// 0x4008E08C register ------------------------------------
typedef struct {
    uint32_t                      r11_reg_loiqcal_txiq_para_1         :11;
    uint32_t                      reserved0                           :21;
}   PHY_RFCTL_AH_RFAFE_INT_35;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_35     b;
}   PHY_RFCTL_AH_RFAFE_INT_35_U;


// 0x4008E090 register ------------------------------------
typedef struct {
    uint32_t                      r10_reg_loiqcal_txlo_para_i         :10;
    uint32_t                      reserved0                           :22;
}   PHY_RFCTL_AH_RFAFE_INT_36;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_36     b;
}   PHY_RFCTL_AH_RFAFE_INT_36_U;


// 0x4008E094 register ------------------------------------
typedef struct {
    uint32_t                      r10_reg_loiqcal_txlo_para_q         :10;
    uint32_t                      reserved0                           :22;
}   PHY_RFCTL_AH_RFAFE_INT_37;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_37     b;
}   PHY_RFCTL_AH_RFAFE_INT_37_U;


// 0x4008E098 register ------------------------------------
typedef struct {
    uint32_t                      r8_reg_loiqcal_rxiq_para_0          :8 ;
    uint32_t                      reserved0                           :24;
}   PHY_RFCTL_AH_RFAFE_INT_38;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_38     b;
}   PHY_RFCTL_AH_RFAFE_INT_38_U;


// 0x4008E09C register ------------------------------------
typedef struct {
    uint32_t                      r8_reg_loiqcal_rxiq_para_1          :8 ;
    uint32_t                      reserved0                           :24;
}   PHY_RFCTL_AH_RFAFE_INT_39;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_39     b;
}   PHY_RFCTL_AH_RFAFE_INT_39_U;


// 0x4008E0A0 register ------------------------------------
typedef struct {
    uint32_t                      r_reg_loiqcal_txloiq_pmsr_iqsel     :1 ;
    uint32_t                      reserved0                           :31;
}   PHY_RFCTL_AH_RFAFE_INT_40;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_40     b;
}   PHY_RFCTL_AH_RFAFE_INT_40_U;


// 0x4008E0A4 register ------------------------------------
typedef struct {
    uint32_t                      r10_reg_loiqcal_self_len_est        :10;
    uint32_t                      reserved0                           :22;
}   PHY_RFCTL_AH_RFAFE_INT_41;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_41     b;
}   PHY_RFCTL_AH_RFAFE_INT_41_U;


// 0x4008E0A8 register ------------------------------------
typedef struct {
    uint32_t                      r16_reg_loiqcal_self_len_cal        :16;
    uint32_t                      reserved0                           :16;
}   PHY_RFCTL_AH_RFAFE_INT_42;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_42     b;
}   PHY_RFCTL_AH_RFAFE_INT_42_U;


// 0x4008E0AC register ------------------------------------
typedef struct {
    uint32_t                      r4_reg_loiqcal_self_step_gain       :4 ;
    uint32_t                      reserved0                           :28;
}   PHY_RFCTL_AH_RFAFE_INT_43;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_43     b;
}   PHY_RFCTL_AH_RFAFE_INT_43_U;


// 0x4008E0B0 register ------------------------------------
typedef struct {
    uint32_t                      r4_reg_loiqcal_self_step_phase      :4 ;
    uint32_t                      reserved0                           :28;
}   PHY_RFCTL_AH_RFAFE_INT_44;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_44     b;
}   PHY_RFCTL_AH_RFAFE_INT_44_U;


// 0x4008E0B4 register ------------------------------------
typedef struct {
    uint32_t                      i_reg_loiqcal_self_val              :1 ;
    uint32_t                      reserved0                           :31;
}   PHY_RFCTL_AH_RFAFE_INT_45;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_45     b;
}   PHY_RFCTL_AH_RFAFE_INT_45_U;


// 0x4008E0B8 register ------------------------------------
typedef struct {
    uint32_t                      i21_reg_loiqcal_self_param_gain     :21;
    uint32_t                      reserved0                           :11;
}   PHY_RFCTL_AH_RFAFE_INT_46;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_46     b;
}   PHY_RFCTL_AH_RFAFE_INT_46_U;


// 0x4008E0BC register ------------------------------------
typedef struct {
    uint32_t                      i21_reg_loiqcal_self_param_phase    :21;
    uint32_t                      reserved0                           :11;
}   PHY_RFCTL_AH_RFAFE_INT_47;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_47     b;
}   PHY_RFCTL_AH_RFAFE_INT_47_U;


// 0x4008E0C0 register ------------------------------------
typedef struct {
    uint32_t                      r_reg_loiqcal_txcal_test            :1 ;
    uint32_t                      reserved0                           :31;
}   PHY_RFCTL_AH_RFAFE_INT_48;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_48     b;
}   PHY_RFCTL_AH_RFAFE_INT_48_U;


// 0x4008E0C4 register ------------------------------------
typedef struct {
    uint32_t                      r_reg_loiqcal_rxcal_test            :1 ;
    uint32_t                      reserved0                           :31;
}   PHY_RFCTL_AH_RFAFE_INT_49;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_49     b;
}   PHY_RFCTL_AH_RFAFE_INT_49_U;


// 0x4008E0C8 register ------------------------------------
typedef struct {
    uint32_t                      r8_reg_loiqcal_txiq_mis_0           :8 ;
    uint32_t                      reserved0                           :24;
}   PHY_RFCTL_AH_RFAFE_INT_50;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_50     b;
}   PHY_RFCTL_AH_RFAFE_INT_50_U;


// 0x4008E0CC register ------------------------------------
typedef struct {
    uint32_t                      r8_reg_loiqcal_txiq_mis_1           :8 ;
    uint32_t                      reserved0                           :24;
}   PHY_RFCTL_AH_RFAFE_INT_51;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_51     b;
}   PHY_RFCTL_AH_RFAFE_INT_51_U;


// 0x4008E0D0 register ------------------------------------
typedef struct {
    uint32_t                      r10_reg_loiqcal_txlo_mis_i          :10;
    uint32_t                      reserved0                           :22;
}   PHY_RFCTL_AH_RFAFE_INT_52;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_52     b;
}   PHY_RFCTL_AH_RFAFE_INT_52_U;


// 0x4008E0D4 register ------------------------------------
typedef struct {
    uint32_t                      r10_reg_loiqcal_txlo_mis_q          :10;
    uint32_t                      reserved0                           :22;
}   PHY_RFCTL_AH_RFAFE_INT_53;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_53     b;
}   PHY_RFCTL_AH_RFAFE_INT_53_U;


// 0x4008E0D8 register ------------------------------------
typedef struct {
    uint32_t                      r8_reg_loiqcal_rxiq_mis_0           :8 ;
    uint32_t                      reserved0                           :24;
}   PHY_RFCTL_AH_RFAFE_INT_54;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_54     b;
}   PHY_RFCTL_AH_RFAFE_INT_54_U;


// 0x4008E0DC register ------------------------------------
typedef struct {
    uint32_t                      r8_reg_loiqcal_rxiq_mis_1           :8 ;
    uint32_t                      reserved0                           :24;
}   PHY_RFCTL_AH_RFAFE_INT_55;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_55     b;
}   PHY_RFCTL_AH_RFAFE_INT_55_U;


// 0x4008E0E0 register ------------------------------------
typedef struct {
    uint32_t                      r8_reg_loiqcal_tx_dgain             :8 ;
    uint32_t                      reserved0                           :24;
}   PHY_RFCTL_AH_RFAFE_INT_56;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_56     b;
}   PHY_RFCTL_AH_RFAFE_INT_56_U;


// 0x4008E0E4 register ------------------------------------
typedef struct {
    uint32_t                      r2_reg_rx_gain_load_delay           :2 ;
    uint32_t                      reserved0                           :30;
}   PHY_RFCTL_AH_RFAFE_INT_57;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_57     b;
}   PHY_RFCTL_AH_RFAFE_INT_57_U;


// 0x4008E0E8 register ------------------------------------
typedef struct {
    uint32_t                      r2_reg_tx_gain_load_delay           :2 ;
    uint32_t                      reserved0                           :30;
}   PHY_RFCTL_AH_RFAFE_INT_58;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_58     b;
}   PHY_RFCTL_AH_RFAFE_INT_58_U;


// 0x4008E0EC register ------------------------------------
typedef struct {
    uint32_t                      r2_reg_txgain_mem_type              :2 ;
    uint32_t                      reserved0                           :30;
}   PHY_RFCTL_AH_RFAFE_INT_59;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_59     b;
}   PHY_RFCTL_AH_RFAFE_INT_59_U;


// 0x4008E0F0 register ------------------------------------
typedef struct {
    uint32_t                      r_reg_txgain_lut_wr_enable          :1 ;
    uint32_t                      reserved0                           :31;
}   PHY_RFCTL_AH_RFAFE_INT_60;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_60     b;
}   PHY_RFCTL_AH_RFAFE_INT_60_U;


// 0x4008E0F4 register ------------------------------------
typedef struct {
    uint32_t                      r7_reg_txgain_lut_wr_addr           :7 ;
    uint32_t                      reserved0                           :25;
}   PHY_RFCTL_AH_RFAFE_INT_61;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_61     b;
}   PHY_RFCTL_AH_RFAFE_INT_61_U;


// 0x4008E0F8 register ------------------------------------
typedef struct {
    uint32_t                      r24_reg_txgain_lut_wr_data          :24;
    uint32_t                      reserved0                           :8 ;
}   PHY_RFCTL_AH_RFAFE_INT_62;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_62     b;
}   PHY_RFCTL_AH_RFAFE_INT_62_U;


// 0x4008E0FC register ------------------------------------
typedef struct {
    uint32_t                      r4_reg_txgain_lut_wr_vga            :4 ;
    uint32_t                      reserved0                           :28;
}   PHY_RFCTL_AH_RFAFE_INT_63;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_63     b;
}   PHY_RFCTL_AH_RFAFE_INT_63_U;


// 0x4008E100 register ------------------------------------
typedef struct {
    uint32_t                      r3_reg_txgain_lut_wr_mixer          :4 ;
    uint32_t                      reserved0                           :28;
}   PHY_RFCTL_AH_RFAFE_INT_64;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_64     b;
}   PHY_RFCTL_AH_RFAFE_INT_64_U;


// 0x4008E104 register ------------------------------------
typedef struct {
    uint32_t                      r3_reg_txgain_lut_wr_pa_dr          :4 ;
    uint32_t                      reserved0                           :28;
}   PHY_RFCTL_AH_RFAFE_INT_65;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_65     b;
}   PHY_RFCTL_AH_RFAFE_INT_65_U;


// 0x4008E108 register ------------------------------------
typedef struct {
    uint32_t                      r_reg_hw_spi_mem_type               :1 ;
    uint32_t                      reserved0                           :31;
}   PHY_RFCTL_AH_RFAFE_INT_66;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_66     b;
}   PHY_RFCTL_AH_RFAFE_INT_66_U;


// 0x4008E10C register ------------------------------------
typedef struct {
    uint32_t                      r_reg_hw_spi_lut_wr_enable          :1 ;
    uint32_t                      reserved0                           :31;
}   PHY_RFCTL_AH_RFAFE_INT_67;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_67     b;
}   PHY_RFCTL_AH_RFAFE_INT_67_U;


// 0x4008E110 register ------------------------------------
typedef struct {
    uint32_t                      r7_reg_hw_spi_lut_wr_addr           :7 ;
    uint32_t                      reserved0                           :25;
}   PHY_RFCTL_AH_RFAFE_INT_68;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_68     b;
}   PHY_RFCTL_AH_RFAFE_INT_68_U;


// 0x4008E114 register ------------------------------------
typedef struct {
    uint32_t                      r24_reg_hw_spi_lut_wr_data          :24;
    uint32_t                      reserved0                           :8 ;
}   PHY_RFCTL_AH_RFAFE_INT_69;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_69     b;
}   PHY_RFCTL_AH_RFAFE_INT_69_U;


// 0x4008E118 register ------------------------------------
typedef struct {
    uint32_t                      r7_reg_prf_reg_num                  :7 ;
    uint32_t                      reserved0                           :25;
}   PHY_RFCTL_AH_RFAFE_INT_70;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_70     b;
}   PHY_RFCTL_AH_RFAFE_INT_70_U;


// 0x4008E11C register ------------------------------------
typedef struct {
    uint32_t                      r7_reg_rf_ctl_toggle                :7 ;
    uint32_t                      reserved0                           :25;
}   PHY_RFCTL_AH_RFAFE_INT_71;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_71     b;
}   PHY_RFCTL_AH_RFAFE_INT_71_U;


// 0x4008E120 register ------------------------------------
typedef struct {
    uint32_t                      r7_reg_rf_ctl_low                   :7 ;
    uint32_t                      reserved0                           :25;
}   PHY_RFCTL_AH_RFAFE_INT_72;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_72     b;
}   PHY_RFCTL_AH_RFAFE_INT_72_U;


// 0x4008E124 register ------------------------------------
typedef struct {
    uint32_t                      r2_reg_ext_lna_load_delay           :2 ;
    uint32_t                      reserved0                           :30;
}   PHY_RFCTL_AH_RFAFE_INT_73;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_73     b;
}   PHY_RFCTL_AH_RFAFE_INT_73_U;


// 0x4008E128 register ------------------------------------
typedef struct {
    uint32_t                      r7_reg_rxen_delay                   :7 ;
    uint32_t                      reserved0                           :25;
}   PHY_RFCTL_AH_RFAFE_INT_74;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_74     b;
}   PHY_RFCTL_AH_RFAFE_INT_74_U;


// 0x4008E12C register ------------------------------------
typedef struct {
    uint32_t                      r7_reg_antsel_delay                 :7 ;
    uint32_t                      reserved0                           :25;
}   PHY_RFCTL_AH_RFAFE_INT_75;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_75     b;
}   PHY_RFCTL_AH_RFAFE_INT_75_U;


// 0x4008E130 register ------------------------------------
typedef struct {
    uint32_t                      r_reg_txen_sel                      :1 ;
    uint32_t                      reserved0                           :31;
}   PHY_RFCTL_AH_RFAFE_INT_76;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_76     b;
}   PHY_RFCTL_AH_RFAFE_INT_76_U;


// 0x4008E134 register ------------------------------------
typedef struct {
    uint32_t                      r_reg_txpwr_sel                     :1 ;
    uint32_t                      reserved0                           :31;
}   PHY_RFCTL_AH_RFAFE_INT_77;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_77     b;
}   PHY_RFCTL_AH_RFAFE_INT_77_U;


// 0x4008E138 register ------------------------------------
typedef struct {
    uint32_t                      r2_reg_loiqcal_txiq_para_sel        :2 ;
    uint32_t                      reserved0                           :30;
}   PHY_RFCTL_AH_RFAFE_INT_78;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_78     b;
}   PHY_RFCTL_AH_RFAFE_INT_78_U;


// 0x4008E13C register ------------------------------------
typedef struct {
    uint32_t                      r_reg_loiqcal_txiq_mode_sel         :1 ;
    uint32_t                      reserved0                           :31;
}   PHY_RFCTL_AH_RFAFE_INT_79;

typedef union {
    uint32_t                      w;
    PHY_RFCTL_AH_RFAFE_INT_79     b;
}   PHY_RFCTL_AH_RFAFE_INT_79_U;


//---------------------------------------------------------
// PHY_RFCTL Register Map
//---------------------------------------------------------
typedef struct {
    volatile uint32_t                          RESERVED0              ; // 
    volatile PHY_RFCTL_AH_RFAFE_INT_01_U          AH_RFAFE_INT_01        ; // 0x0004
    volatile PHY_RFCTL_AH_RFAFE_INT_02_U          AH_RFAFE_INT_02        ; // 0x0008
    volatile PHY_RFCTL_AH_RFAFE_INT_03_U          AH_RFAFE_INT_03        ; // 0x000c
    volatile PHY_RFCTL_AH_RFAFE_INT_04_U          AH_RFAFE_INT_04        ; // 0x0010
    volatile PHY_RFCTL_AH_RFAFE_INT_05_U          AH_RFAFE_INT_05        ; // 0x0014
    volatile PHY_RFCTL_AH_RFAFE_INT_06_U          AH_RFAFE_INT_06        ; // 0x0018
    volatile PHY_RFCTL_AH_RFAFE_INT_07_U          AH_RFAFE_INT_07        ; // 0x001c
    volatile PHY_RFCTL_AH_RFAFE_INT_08_U          AH_RFAFE_INT_08        ; // 0x0020
    volatile PHY_RFCTL_AH_RFAFE_INT_09_U          AH_RFAFE_INT_09        ; // 0x0024
    volatile PHY_RFCTL_AH_RFAFE_INT_10_U          AH_RFAFE_INT_10        ; // 0x0028
    volatile PHY_RFCTL_AH_RFAFE_INT_11_U          AH_RFAFE_INT_11        ; // 0x002c
    volatile PHY_RFCTL_AH_RFAFE_INT_12_U          AH_RFAFE_INT_12        ; // 0x0030
    volatile PHY_RFCTL_AH_RFAFE_INT_13_U          AH_RFAFE_INT_13        ; // 0x0034
    volatile PHY_RFCTL_AH_RFAFE_INT_14_U          AH_RFAFE_INT_14        ; // 0x0038
    volatile PHY_RFCTL_AH_RFAFE_INT_15_U          AH_RFAFE_INT_15        ; // 0x003c
    volatile PHY_RFCTL_AH_RFAFE_INT_16_U          AH_RFAFE_INT_16        ; // 0x0040
    volatile PHY_RFCTL_AH_RFAFE_INT_17_U          AH_RFAFE_INT_17        ; // 0x0044
    volatile PHY_RFCTL_AH_RFAFE_INT_18_U          AH_RFAFE_INT_18        ; // 0x0048
    volatile PHY_RFCTL_AH_RFAFE_INT_19_U          AH_RFAFE_INT_19        ; // 0x004c
    volatile PHY_RFCTL_AH_RFAFE_INT_20_U          AH_RFAFE_INT_20        ; // 0x0050
    volatile PHY_RFCTL_AH_RFAFE_INT_21_U          AH_RFAFE_INT_21        ; // 0x0054
    volatile PHY_RFCTL_AH_RFAFE_INT_22_U          AH_RFAFE_INT_22        ; // 0x0058
    volatile PHY_RFCTL_AH_RFAFE_INT_23_U          AH_RFAFE_INT_23        ; // 0x005c
    volatile PHY_RFCTL_AH_RFAFE_INT_24_U          AH_RFAFE_INT_24        ; // 0x0060
    volatile PHY_RFCTL_AH_RFAFE_INT_25_U          AH_RFAFE_INT_25        ; // 0x0064
    volatile PHY_RFCTL_AH_RFAFE_INT_26_U          AH_RFAFE_INT_26        ; // 0x0068
    volatile PHY_RFCTL_AH_RFAFE_INT_27_U          AH_RFAFE_INT_27        ; // 0x006c
    volatile PHY_RFCTL_AH_RFAFE_INT_28_U          AH_RFAFE_INT_28        ; // 0x0070
    volatile PHY_RFCTL_AH_RFAFE_INT_29_U          AH_RFAFE_INT_29        ; // 0x0074
    volatile PHY_RFCTL_AH_RFAFE_INT_30_U          AH_RFAFE_INT_30        ; // 0x0078
    volatile PHY_RFCTL_AH_RFAFE_INT_31_U          AH_RFAFE_INT_31        ; // 0x007c
    volatile PHY_RFCTL_AH_RFAFE_INT_32_U          AH_RFAFE_INT_32        ; // 0x0080
    volatile PHY_RFCTL_AH_RFAFE_INT_33_U          AH_RFAFE_INT_33        ; // 0x0084
    volatile PHY_RFCTL_AH_RFAFE_INT_34_U          AH_RFAFE_INT_34        ; // 0x0088
    volatile PHY_RFCTL_AH_RFAFE_INT_35_U          AH_RFAFE_INT_35        ; // 0x008c
    volatile PHY_RFCTL_AH_RFAFE_INT_36_U          AH_RFAFE_INT_36        ; // 0x0090
    volatile PHY_RFCTL_AH_RFAFE_INT_37_U          AH_RFAFE_INT_37        ; // 0x0094
    volatile PHY_RFCTL_AH_RFAFE_INT_38_U          AH_RFAFE_INT_38        ; // 0x0098
    volatile PHY_RFCTL_AH_RFAFE_INT_39_U          AH_RFAFE_INT_39        ; // 0x009c
    volatile PHY_RFCTL_AH_RFAFE_INT_40_U          AH_RFAFE_INT_40        ; // 0x00a0
    volatile PHY_RFCTL_AH_RFAFE_INT_41_U          AH_RFAFE_INT_41        ; // 0x00a4
    volatile PHY_RFCTL_AH_RFAFE_INT_42_U          AH_RFAFE_INT_42        ; // 0x00a8
    volatile PHY_RFCTL_AH_RFAFE_INT_43_U          AH_RFAFE_INT_43        ; // 0x00ac
    volatile PHY_RFCTL_AH_RFAFE_INT_44_U          AH_RFAFE_INT_44        ; // 0x00b0
    volatile PHY_RFCTL_AH_RFAFE_INT_45_U          AH_RFAFE_INT_45        ; // 0x00b4
    volatile PHY_RFCTL_AH_RFAFE_INT_46_U          AH_RFAFE_INT_46        ; // 0x00b8
    volatile PHY_RFCTL_AH_RFAFE_INT_47_U          AH_RFAFE_INT_47        ; // 0x00bc
    volatile PHY_RFCTL_AH_RFAFE_INT_48_U          AH_RFAFE_INT_48        ; // 0x00c0
    volatile PHY_RFCTL_AH_RFAFE_INT_49_U          AH_RFAFE_INT_49        ; // 0x00c4
    volatile PHY_RFCTL_AH_RFAFE_INT_50_U          AH_RFAFE_INT_50        ; // 0x00c8
    volatile PHY_RFCTL_AH_RFAFE_INT_51_U          AH_RFAFE_INT_51        ; // 0x00cc
    volatile PHY_RFCTL_AH_RFAFE_INT_52_U          AH_RFAFE_INT_52        ; // 0x00d0
    volatile PHY_RFCTL_AH_RFAFE_INT_53_U          AH_RFAFE_INT_53        ; // 0x00d4
    volatile PHY_RFCTL_AH_RFAFE_INT_54_U          AH_RFAFE_INT_54        ; // 0x00d8
    volatile PHY_RFCTL_AH_RFAFE_INT_55_U          AH_RFAFE_INT_55        ; // 0x00dc
    volatile PHY_RFCTL_AH_RFAFE_INT_56_U          AH_RFAFE_INT_56        ; // 0x00e0
    volatile PHY_RFCTL_AH_RFAFE_INT_57_U          AH_RFAFE_INT_57        ; // 0x00e4
    volatile PHY_RFCTL_AH_RFAFE_INT_58_U          AH_RFAFE_INT_58        ; // 0x00e8
    volatile PHY_RFCTL_AH_RFAFE_INT_59_U          AH_RFAFE_INT_59        ; // 0x00ec
    volatile PHY_RFCTL_AH_RFAFE_INT_60_U          AH_RFAFE_INT_60        ; // 0x00f0
    volatile PHY_RFCTL_AH_RFAFE_INT_61_U          AH_RFAFE_INT_61        ; // 0x00f4
    volatile PHY_RFCTL_AH_RFAFE_INT_62_U          AH_RFAFE_INT_62        ; // 0x00f8
    volatile PHY_RFCTL_AH_RFAFE_INT_63_U          AH_RFAFE_INT_63        ; // 0x00fc
    volatile PHY_RFCTL_AH_RFAFE_INT_64_U          AH_RFAFE_INT_64        ; // 0x0100
    volatile PHY_RFCTL_AH_RFAFE_INT_65_U          AH_RFAFE_INT_65        ; // 0x0104
    volatile PHY_RFCTL_AH_RFAFE_INT_66_U          AH_RFAFE_INT_66        ; // 0x0108
    volatile PHY_RFCTL_AH_RFAFE_INT_67_U          AH_RFAFE_INT_67        ; // 0x010c
    volatile PHY_RFCTL_AH_RFAFE_INT_68_U          AH_RFAFE_INT_68        ; // 0x0110
    volatile PHY_RFCTL_AH_RFAFE_INT_69_U          AH_RFAFE_INT_69        ; // 0x0114
    volatile PHY_RFCTL_AH_RFAFE_INT_70_U          AH_RFAFE_INT_70        ; // 0x0118
    volatile PHY_RFCTL_AH_RFAFE_INT_71_U          AH_RFAFE_INT_71        ; // 0x011c
    volatile PHY_RFCTL_AH_RFAFE_INT_72_U          AH_RFAFE_INT_72        ; // 0x0120
    volatile PHY_RFCTL_AH_RFAFE_INT_73_U          AH_RFAFE_INT_73        ; // 0x0124
    volatile PHY_RFCTL_AH_RFAFE_INT_74_U          AH_RFAFE_INT_74        ; // 0x0128
    volatile PHY_RFCTL_AH_RFAFE_INT_75_U          AH_RFAFE_INT_75        ; // 0x012c
    volatile PHY_RFCTL_AH_RFAFE_INT_76_U          AH_RFAFE_INT_76        ; // 0x0130
    volatile PHY_RFCTL_AH_RFAFE_INT_77_U          AH_RFAFE_INT_77        ; // 0x0134
    volatile PHY_RFCTL_AH_RFAFE_INT_78_U          AH_RFAFE_INT_78        ; // 0x0138
    volatile PHY_RFCTL_AH_RFAFE_INT_79_U          AH_RFAFE_INT_79        ; // 0x013c
} PHY_RFCTL_Type;

#ifdef __cplusplus
}
#endif

#endif /* __REG_PHY_RFCTL_H__ */
