/*********************************************************************/
/*    Newracom Library / IP Product                                  */
/*    Product Name :                                                 */
/*    Version      :                                                 */
/*    Author       :                                                 */
/*    Update       :                                                 */
/*********************************************************************/

#ifndef __REG_PHY_H__
#define __REG_PHY_H__

#ifdef __cplusplus
extern "C"{
#endif

// 0x40088000 register ------------------------------------
typedef struct {
    uint32_t                                SW_RESET                             :1 ;
    uint32_t                                SW_RST_RX_IDLE                       :1 ;
    uint32_t                                PHY_EN                               :1 ;
    uint32_t                                RF_CAL_EN                            :1 ;
    uint32_t                                TEST_MD_EN                           :1 ;
    uint32_t                                reserved0                            :3 ;
    uint32_t                                TXDEF_LATENCY_1M                     :8 ;
    uint32_t                                TXDEF_LATENCY_2M                     :8 ;
    uint32_t                                RF_LATENCY                           :8 ;
}   PHY_PHY_TOP_STATE00;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOP_STATE00                     b;
}   PHY_PHY_TOP_STATE00_U;


// 0x40088004 register ------------------------------------
typedef struct {
    uint32_t                                EN_RXDFE                             :1 ;
    uint32_t                                EN_RXDBE                             :1 ;
    uint32_t                                EN_TXDFE                             :1 ;
    uint32_t                                EN_TXDBE                             :1 ;
    uint32_t                                TXSTART_REQ                          :1 ;
    uint32_t                                RXPPDU                               :1 ;
    uint32_t                                TXPPDU                               :1 ;
    uint32_t                                reserved0                            :1 ;
    uint32_t                                CCA                                  :3 ;
    uint32_t                                reserved1                            :5 ;
    uint32_t                                CUR_PHY_TOP_STATE                    :5 ;
    uint32_t                                reserved2                            :11;
}   PHY_PHY_TOP_STATE01;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOP_STATE01                     b;
}   PHY_PHY_TOP_STATE01_U;


// 0x40088008 register ------------------------------------
typedef struct {
    uint32_t                                MANUAL_CTRL_AUX_PLL_CAL_CLK          :2 ;
    uint32_t                                AUX_PLL_CAL_CLK_INV                  :1 ;
    uint32_t                                reserved0                            :29;
}   PHY_PHY_TOP_STATE02;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOP_STATE02                     b;
}   PHY_PHY_TOP_STATE02_U;


// 0x4008800C register ------------------------------------
typedef struct {
    uint32_t                                i7_reg_txvec_sbr_length              :16;
    uint32_t                                reserved0                            :16;
}   PHY_PHY_TOP_STATE03;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOP_STATE03                     b;
}   PHY_PHY_TOP_STATE03_U;


// 0x40088200 register ------------------------------------
typedef struct {
    uint32_t                                TX_SCR_SEED_MODE                     :1 ;
    uint32_t                                reserved0                            :3 ;
    uint32_t                                r_reg_trx_scr_seed_rev               :1 ;
    uint32_t                                reserved1                            :3 ;
    uint32_t                                TX_SCRAMBLER_SEED                    :7 ;
    uint32_t                                r_reg_tx_srv                         :1 ;
    uint32_t                                TXPWR_MODE                           :1 ;
    uint32_t                                reserved2                            :7 ;
    uint32_t                                TXPWR_LEVEL                          :8 ;
}   PHY_TX_PPDU_STATE00;

typedef union {
    uint32_t                                w;
    PHY_TX_PPDU_STATE00                     b;
}   PHY_TX_PPDU_STATE00_U;


// 0x40088204 register ------------------------------------
typedef struct {
    uint32_t                                N_DBPS                               :14;
    uint32_t                                reserved0                            :2 ;
    uint32_t                                TX_FORMAT                            :2 ;
    uint32_t                                TX_CBW                               :2 ;
    uint32_t                                TX_PREAMBLE                          :1 ;
    uint32_t                                reserved1                            :3 ;
    uint32_t                                TX_MCS                               :4 ;
    uint32_t                                i_reg_txvec_sbr_enable               :1 ;
    uint32_t                                i_reg_txvec_sbr_rate                 :1 ;
    uint32_t                                reserved2                            :2 ;
}   PHY_TX_PPDU_STATE01;

typedef union {
    uint32_t                                w;
    PHY_TX_PPDU_STATE01                     b;
}   PHY_TX_PPDU_STATE01_U;


// 0x40088208 register ------------------------------------
typedef struct {
    uint32_t                                BYTE_LEN                             :20;
    uint32_t                                reserved0                            :12;
}   PHY_TX_PPDU_STATE02;

typedef union {
    uint32_t                                w;
    PHY_TX_PPDU_STATE02                     b;
}   PHY_TX_PPDU_STATE02_U;


// 0x4008820C register ------------------------------------
typedef struct {
    uint32_t                                TXVEC_ERR_CNT                        :32;
}   PHY_TX_PPDU_STATE03;

typedef union {
    uint32_t                                w;
    PHY_TX_PPDU_STATE03                     b;
}   PHY_TX_PPDU_STATE03_U;


// 0x40088210 register ------------------------------------
typedef struct {
    uint32_t                                TXSIG_ERR_CNT                        :32;
}   PHY_TX_PPDU_STATE04;

typedef union {
    uint32_t                                w;
    PHY_TX_PPDU_STATE04                     b;
}   PHY_TX_PPDU_STATE04_U;


// 0x40088214 register ------------------------------------
typedef struct {
    uint32_t                                PACKET_TRANSMISSION_CNT              :32;
}   PHY_TX_PPDU_STATE05;

typedef union {
    uint32_t                                w;
    PHY_TX_PPDU_STATE05                     b;
}   PHY_TX_PPDU_STATE05_U;


// 0x40088218 register ------------------------------------
typedef struct {
    uint32_t                                TXREADY_ERR_CNT                      :32;
}   PHY_TX_PPDU_STATE06;

typedef union {
    uint32_t                                w;
    PHY_TX_PPDU_STATE06                     b;
}   PHY_TX_PPDU_STATE06_U;


// 0x4008821C register ------------------------------------
typedef struct {
    uint32_t                                TXDBE_RD_ERR_CNT                     :32;
}   PHY_TX_PPDU_STATE07;

typedef union {
    uint32_t                                w;
    PHY_TX_PPDU_STATE07                     b;
}   PHY_TX_PPDU_STATE07_U;


// 0x40088220 register ------------------------------------
typedef struct {
    uint32_t                                i5_reg_tx_ppdu_state                 :32;
}   PHY_TX_PPDU_STATE08;

typedef union {
    uint32_t                                w;
    PHY_TX_PPDU_STATE08                     b;
}   PHY_TX_PPDU_STATE08_U;


// 0x40088400 register ------------------------------------
typedef struct {
    uint32_t                                MODE_ID_CHECK                        :1 ;
    uint32_t                                IGNORE_UPLINK_IND                    :1 ;
    uint32_t                                IGNORE_RSRVD_BIT                     :1 ;
    uint32_t                                reserved0                            :13;
    uint32_t                                BSSID_0                              :10;
    uint32_t                                reserved1                            :6 ;
}   PHY_RX_PPDU_STATE00;

typedef union {
    uint32_t                                w;
    PHY_RX_PPDU_STATE00                     b;
}   PHY_RX_PPDU_STATE00_U;


// 0x40088404 register ------------------------------------
typedef struct {
    uint32_t                                BSSID_1                              :10;
    uint32_t                                reserved0                            :22;
}   PHY_RX_PPDU_STATE01;

typedef union {
    uint32_t                                w;
    PHY_RX_PPDU_STATE01                     b;
}   PHY_RX_PPDU_STATE01_U;


// 0x40088408 register ------------------------------------
typedef struct {
    uint32_t                                BSSID_2                              :10;
    uint32_t                                reserved0                            :22;
}   PHY_RX_PPDU_STATE02;

typedef union {
    uint32_t                                w;
    PHY_RX_PPDU_STATE02                     b;
}   PHY_RX_PPDU_STATE02_U;


// 0x4008840C register ------------------------------------
typedef struct {
    uint32_t                                BSSID_3                              :10;
    uint32_t                                reserved0                            :22;
}   PHY_RX_PPDU_STATE03;

typedef union {
    uint32_t                                w;
    PHY_RX_PPDU_STATE03                     b;
}   PHY_RX_PPDU_STATE03_U;


// 0x40088410 register ------------------------------------
typedef struct {
    uint32_t                                BSSID_4                              :10;
    uint32_t                                reserved0                            :22;
}   PHY_RX_PPDU_STATE04;

typedef union {
    uint32_t                                w;
    PHY_RX_PPDU_STATE04                     b;
}   PHY_RX_PPDU_STATE04_U;


// 0x40088414 register ------------------------------------
typedef struct {
    uint32_t                                reserved0                            :2 ;
    uint32_t                                RX_CBW                               :2 ;
    uint32_t                                RX_PREAMBLE                          :1 ;
    uint32_t                                UNSUPPORTED                          :1 ;
    uint32_t                                ID_MATCH                             :1 ;
    uint32_t                                FD_FRAME_START                       :1 ;
    uint32_t                                BYTE_LEN                             :20;
    uint32_t                                RX_MCS                               :4 ;
}   PHY_RX_PPDU_STATE05;

typedef union {
    uint32_t                                w;
    PHY_RX_PPDU_STATE05                     b;
}   PHY_RX_PPDU_STATE05_U;


// 0x40088418 register ------------------------------------
typedef struct {
    uint32_t                                RSSI                                 :8 ;
    uint32_t                                RCPI                                 :8 ;
    uint32_t                                RX_CFO_VALUE                         :13;
    uint32_t                                reserved0                            :3 ;
}   PHY_RX_PPDU_STATE06;

typedef union {
    uint32_t                                w;
    PHY_RX_PPDU_STATE06                     b;
}   PHY_RX_PPDU_STATE06_U;


// 0x4008841C register ------------------------------------
typedef struct {
    uint32_t                                RX_TIMEOUT_CNT0                      :32;
}   PHY_RX_PPDU_STATE07;

typedef union {
    uint32_t                                w;
    PHY_RX_PPDU_STATE07                     b;
}   PHY_RX_PPDU_STATE07_U;


// 0x40088420 register ------------------------------------
typedef struct {
    uint32_t                                RX_TIMEOUT_CNT1                      :32;
}   PHY_RX_PPDU_STATE08;

typedef union {
    uint32_t                                w;
    PHY_RX_PPDU_STATE08                     b;
}   PHY_RX_PPDU_STATE08_U;


// 0x40088424 register ------------------------------------
typedef struct {
    uint32_t                                RX_TIMEOUT_CNT2                      :32;
}   PHY_RX_PPDU_STATE09;

typedef union {
    uint32_t                                w;
    PHY_RX_PPDU_STATE09                     b;
}   PHY_RX_PPDU_STATE09_U;


// 0x40088428 register ------------------------------------
typedef struct {
    uint32_t                                RX_TIMEOUT_CNT3                      :32;
}   PHY_RX_PPDU_STATE10;

typedef union {
    uint32_t                                w;
    PHY_RX_PPDU_STATE10                     b;
}   PHY_RX_PPDU_STATE10_U;


// 0x4008842C register ------------------------------------
typedef struct {
    uint32_t                                RX_TIMEOUT_CNT4                      :32;
}   PHY_RX_PPDU_STATE11;

typedef union {
    uint32_t                                w;
    PHY_RX_PPDU_STATE11                     b;
}   PHY_RX_PPDU_STATE11_U;


// 0x40088430 register ------------------------------------
typedef struct {
    uint32_t                                RX_TIMEOUT_CNT5                      :32;
}   PHY_RX_PPDU_STATE12;

typedef union {
    uint32_t                                w;
    PHY_RX_PPDU_STATE12                     b;
}   PHY_RX_PPDU_STATE12_U;


// 0x40088438 register ------------------------------------
typedef struct {
    uint32_t                                RX_PPDU_STATE                        :5 ;
    uint32_t                                FLAG_DBE_DATFIELD                    :1 ;
    uint32_t                                reserved0                            :26;
}   PHY_RX_PPDU_STATE14;

typedef union {
    uint32_t                                w;
    PHY_RX_PPDU_STATE14                     b;
}   PHY_RX_PPDU_STATE14_U;


// 0x4008843C register ------------------------------------
typedef struct {
    uint32_t                                DATA_SYM_CNT                         :10;
    uint32_t                                reserved0                            :6 ;
    uint32_t                                N_SYM                                :10;
    uint32_t                                reserved1                            :6 ;
}   PHY_RX_PPDU_STATE15;

typedef union {
    uint32_t                                w;
    PHY_RX_PPDU_STATE15                     b;
}   PHY_RX_PPDU_STATE15_U;


// 0x40088440 register ------------------------------------
typedef struct {
    uint32_t                                FRAME_END_RSSI                       :1 ;
    uint32_t                                FRAME_END_TIME                       :1 ;
    uint32_t                                FD_FRAME_END                         :1 ;
    uint32_t                                reserved0                            :29;
}   PHY_RX_PPDU_STATE16;

typedef union {
    uint32_t                                w;
    PHY_RX_PPDU_STATE16                     b;
}   PHY_RX_PPDU_STATE16_U;


// 0x40088600 register ------------------------------------
typedef struct {
    uint32_t                                PHY_TEST_MD                          :2 ;
    uint32_t                                PHY_TEST_TX_DATA_TYPE                :2 ;
    uint32_t                                PHY_TEST_CONT_TX_START               :1 ;
    uint32_t                                PHY_TEST_LOOPBACK_START              :1 ;
    uint32_t                                r_reg_test_md_txcw_start             :1 ;
    uint32_t                                reserved0                            :25;
}   PHY_PHY_TEST_MD00;

typedef union {
    uint32_t                                w;
    PHY_PHY_TEST_MD00                       b;
}   PHY_PHY_TEST_MD00_U;


// 0x40088604 register ------------------------------------
typedef struct {
    uint32_t                                TEST_TXVECTOR                        :31;
    uint32_t                                reserved0                            :1 ;
}   PHY_PHY_TEST_MD01;

typedef union {
    uint32_t                                w;
    PHY_PHY_TEST_MD01                       b;
}   PHY_PHY_TEST_MD01_U;


// 0x40088608 register ------------------------------------
typedef struct {
    uint32_t                                TEST_TXSIG                           :32;
}   PHY_PHY_TEST_MD02;

typedef union {
    uint32_t                                w;
    PHY_PHY_TEST_MD02                       b;
}   PHY_PHY_TEST_MD02_U;


// 0x4008860C register ------------------------------------
typedef struct {
    uint32_t                                TEST_TXSIG                           :10;
    uint32_t                                reserved0                            :22;
}   PHY_PHY_TEST_MD03;

typedef union {
    uint32_t                                w;
    PHY_PHY_TEST_MD03                       b;
}   PHY_PHY_TEST_MD03_U;


// 0x40088610 register ------------------------------------
typedef struct {
    uint32_t                                TEST_DATA                            :32;
}   PHY_PHY_TEST_MD04;

typedef union {
    uint32_t                                w;
    PHY_PHY_TEST_MD04                       b;
}   PHY_PHY_TEST_MD04_U;


// 0x40088614 register ------------------------------------
typedef struct {
    uint32_t                                TEST_TX_CW_FREQ                      :3 ;
    uint32_t                                reserved0                            :1 ;
    uint32_t                                TEST_TX_CW_MSB_INV                   :1 ;
    uint32_t                                reserved1                            :27;
}   PHY_PHY_TEST_MD05;

typedef union {
    uint32_t                                w;
    PHY_PHY_TEST_MD05                       b;
}   PHY_PHY_TEST_MD05_U;


// 0x40088630 register ------------------------------------
typedef struct {
    uint32_t                                SIM_TRX_MODE                         :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_PHY_SIM_TRX_MD;

typedef union {
    uint32_t                                w;
    PHY_PHY_SIM_TRX_MD                      b;
}   PHY_PHY_SIM_TRX_MD_U;


// 0x40088800 register ------------------------------------
typedef struct {
    uint32_t                                WGT_CHUP                             :2 ;
    uint32_t                                reserved0                            :30;
}   PHY_PHY_RXDBE00;

typedef union {
    uint32_t                                w;
    PHY_PHY_RXDBE00                         b;
}   PHY_PHY_RXDBE00_U;


// 0x40088804 register ------------------------------------
typedef struct {
    uint32_t                                NOISE_EST_MIN                        :26;
    uint32_t                                reserved0                            :6 ;
}   PHY_PHY_RXDBE01;

typedef union {
    uint32_t                                w;
    PHY_PHY_RXDBE01                         b;
}   PHY_PHY_RXDBE01_U;


// 0x40089000 register ------------------------------------
typedef struct {
    uint32_t                                RX_OP_MODE                           :1 ;
    uint32_t                                TX_OP_MODE                           :1 ;
    uint32_t                                reserved0                            :30;
}   PHY_PHY_TOPIF_CLK_GEN0;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOPIF_CLK_GEN0                  b;
}   PHY_PHY_TOPIF_CLK_GEN0_U;


// 0x40089004 register ------------------------------------
typedef struct {
    uint32_t                                CLKBUF_EN_RFCAL                      :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_PHY_TOPIF_CLK_GEN1;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOPIF_CLK_GEN1                  b;
}   PHY_PHY_TOPIF_CLK_GEN1_U;


// 0x40089008 register ------------------------------------
typedef struct {
    uint32_t                                CLKBUF_EN_TX_SIG_X1                  :1 ;
    uint32_t                                CLKBUF_EN_TX_SIG_X2                  :1 ;
    uint32_t                                CLKBUF_EN_TX_SIG_X4                  :1 ;
    uint32_t                                CLKBUF_EN_TX_OP_X4                   :1 ;
    uint32_t                                reserved0                            :28;
}   PHY_PHY_TOPIF_CLK_GEN2;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOPIF_CLK_GEN2                  b;
}   PHY_PHY_TOPIF_CLK_GEN2_U;


// 0x4008900C register ------------------------------------
typedef struct {
    uint32_t                                CLKBUF_EN_RX_DIV2_OP2_CS             :1 ;
    uint32_t                                CLKBUF_EN_RX_DIV2_OP2_DFE1           :1 ;
    uint32_t                                CLKBUF_EN_RX_DIV2_OP4                :1 ;
    uint32_t                                CLKBUF_EN_RX_DIV2_OP2                :1 ;
    uint32_t                                CLKBUF_EN_RX_X1_OP2_CS               :1 ;
    uint32_t                                CLKBUF_EN_RX_X1_OP2_DFE1             :1 ;
    uint32_t                                CLKBUF_EN_RX_X1_OP2                  :1 ;
    uint32_t                                CLKBUF_EN_RX_X2_OP2_DFE1             :1 ;
    uint32_t                                CLKBUF_EN_RX_X2_AGC                  :1 ;
    uint32_t                                CLKBUF_EN_RX_X4_AGC                  :1 ;
    uint32_t                                CLKBUF_EN_RX_X1X2_DFE2               :1 ;
    uint32_t                                CLKBUF_EN_RX_DIV2X1                  :1 ;
    uint32_t                                CLKBUF_EN_RX_X1X2                    :1 ;
    uint32_t                                CLKBUF_EN_RX_X2X4_DBE                :1 ;
    uint32_t                                CLKBUF_EN_RX_X2X4                    :1 ;
    uint32_t                                CLKBUF_EN_RX_X4X8                    :1 ;
    uint32_t                                CLKBUF_EN_RX_X4X8_DBE                :1 ;
    uint32_t                                reserved0                            :15;
}   PHY_PHY_TOPIF_CLK_GEN3;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOPIF_CLK_GEN3                  b;
}   PHY_PHY_TOPIF_CLK_GEN3_U;


// 0x40089010 register ------------------------------------
typedef struct {
    uint32_t                                LOOPBACK_EN                          :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_PHY_TOPIF_CLK_GEN4;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOPIF_CLK_GEN4                  b;
}   PHY_PHY_TOPIF_CLK_GEN4_U;


// 0x40089014 register ------------------------------------
typedef struct {
    uint32_t                                BW_1M_EN                             :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_PHY_TOPIF_CLK_GEN5;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOPIF_CLK_GEN5                  b;
}   PHY_PHY_TOPIF_CLK_GEN5_U;


// 0x40089100 register ------------------------------------
typedef struct {
    uint32_t                                TXFIFO_AF_LVL                        :5 ;
    uint32_t                                reserved0                            :11;
    uint32_t                                TXFIFO_MAX_LVL                       :5 ;
    uint32_t                                reserved1                            :11;
}   PHY_PHY_TOPIF_TXFIFO0;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOPIF_TXFIFO0                   b;
}   PHY_PHY_TOPIF_TXFIFO0_U;


// 0x40089104 register ------------------------------------
typedef struct {
    uint32_t                                TXFIFO_WR_CNT                        :14;
    uint32_t                                reserved0                            :18;
}   PHY_PHY_TOPIF_TXFIFO1;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOPIF_TXFIFO1                   b;
}   PHY_PHY_TOPIF_TXFIFO1_U;


// 0x40089108 register ------------------------------------
typedef struct {
    uint32_t                                TXFIFO_RD_CNT                        :14;
    uint32_t                                reserved0                            :18;
}   PHY_PHY_TOPIF_TXFIFO2;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOPIF_TXFIFO2                   b;
}   PHY_PHY_TOPIF_TXFIFO2_U;


// 0x4008910C register ------------------------------------
typedef struct {
    uint32_t                                TXFIFO_FULL_CNT                      :32;
}   PHY_PHY_TOPIF_TXFIFO3;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOPIF_TXFIFO3                   b;
}   PHY_PHY_TOPIF_TXFIFO3_U;


// 0x40089110 register ------------------------------------
typedef struct {
    uint32_t                                TXFIFO_OVFL_CNT                      :32;
}   PHY_PHY_TOPIF_TXFIFO4;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOPIF_TXFIFO4                   b;
}   PHY_PHY_TOPIF_TXFIFO4_U;


// 0x40089170 register ------------------------------------
typedef struct {
    uint32_t                                PHY_LOOPBACK_ON                      :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_PHY_TOPIF_LOOPBACK;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOPIF_LOOPBACK                  b;
}   PHY_PHY_TOPIF_LOOPBACK_U;


// 0x40089180 register ------------------------------------
typedef struct {
    uint32_t                                RX_PRIM_CH_LOC                       :2 ;
    uint32_t                                reserved0                            :30;
}   PHY_PHY_TOPIF_CONFIG0;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOPIF_CONFIG0                   b;
}   PHY_PHY_TOPIF_CONFIG0_U;


// 0x400891A0 register ------------------------------------
typedef struct {
    uint32_t                                RF_TYPESEL                           :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_PHY_TOPIF_RFCTRL;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOPIF_RFCTRL                    b;
}   PHY_PHY_TOPIF_RFCTRL_U;


// 0x400891B0 register ------------------------------------
typedef struct {
    uint32_t                                VMAC_TEST_MODE                       :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_PHY_TOPIF_VMACCFG0;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOPIF_VMACCFG0                  b;
}   PHY_PHY_TOPIF_VMACCFG0_U;


// 0x400891B4 register ------------------------------------
typedef struct {
    uint32_t                                VMAC_TEST_EN                         :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_PHY_TOPIF_VMACCFG1;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOPIF_VMACCFG1                  b;
}   PHY_PHY_TOPIF_VMACCFG1_U;


// 0x400891B8 register ------------------------------------
typedef struct {
    uint32_t                                VMAC_ITV_DLY                         :32;
}   PHY_PHY_TOPIF_VMACCFG2;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOPIF_VMACCFG2                  b;
}   PHY_PHY_TOPIF_VMACCFG2_U;


// 0x400891BC register ------------------------------------
typedef struct {
    uint32_t                                VMAC_FRM_CNT                         :32;
}   PHY_PHY_TOPIF_VMACCFG3;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOPIF_VMACCFG3                  b;
}   PHY_PHY_TOPIF_VMACCFG3_U;


// 0x400891C0 register ------------------------------------
typedef struct {
    uint32_t                                VMAC_TX_VECTOR                       :31;
    uint32_t                                reserved0                            :1 ;
}   PHY_PHY_TOPIF_VMACCFG4;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOPIF_VMACCFG4                  b;
}   PHY_PHY_TOPIF_VMACCFG4_U;


// 0x400891C4 register ------------------------------------
typedef struct {
    uint32_t                                VMAC_TX_DATA                         :32;
}   PHY_PHY_TOPIF_VMACCFG5;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOPIF_VMACCFG5                  b;
}   PHY_PHY_TOPIF_VMACCFG5_U;


// 0x400891C8 register ------------------------------------
typedef struct {
    uint32_t                                VMAC_TX_SIG_DATA_1                   :32;
}   PHY_PHY_TOPIF_VMACCFG6;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOPIF_VMACCFG6                  b;
}   PHY_PHY_TOPIF_VMACCFG6_U;


// 0x400891CC register ------------------------------------
typedef struct {
    uint32_t                                VMAC_TX_SIG_DATA_2                   :10;
    uint32_t                                reserved0                            :22;
}   PHY_PHY_TOPIF_VMACCFG7;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOPIF_VMACCFG7                  b;
}   PHY_PHY_TOPIF_VMACCFG7_U;


// 0x400891D0 register ------------------------------------
typedef struct {
    uint32_t                                VMAC_TX_DATA_SEL                     :2 ;
    uint32_t                                reserved0                            :30;
}   PHY_PHY_TOPIF_VMACCFG8;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOPIF_VMACCFG8                  b;
}   PHY_PHY_TOPIF_VMACCFG8_U;


// 0x400891D4 register ------------------------------------
typedef struct {
    uint32_t                                VMAC_TXIQ_PARA_0                     :11;
    uint32_t                                reserved0                            :21;
}   PHY_PHY_TOPIF_VMACCFG9;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOPIF_VMACCFG9                  b;
}   PHY_PHY_TOPIF_VMACCFG9_U;


// 0x400891D8 register ------------------------------------
typedef struct {
    uint32_t                                VMAC_TXIQ_PARA_1                     :11;
    uint32_t                                reserved0                            :21;
}   PHY_PHY_TOPIF_VMACCFG10;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOPIF_VMACCFG10                 b;
}   PHY_PHY_TOPIF_VMACCFG10_U;


// 0x400891DC register ------------------------------------
typedef struct {
    uint32_t                                VMAC_TXLO_PARA_I                     :10;
    uint32_t                                reserved0                            :22;
}   PHY_PHY_TOPIF_VMACCFG11;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOPIF_VMACCFG11                 b;
}   PHY_PHY_TOPIF_VMACCFG11_U;


// 0x400891E0 register ------------------------------------
typedef struct {
    uint32_t                                VMAC_TXLO_PARA_Q                     :10;
    uint32_t                                reserved0                            :22;
}   PHY_PHY_TOPIF_VMACCFG12;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOPIF_VMACCFG12                 b;
}   PHY_PHY_TOPIF_VMACCFG12_U;


// 0x400891E4 register ------------------------------------
typedef struct {
    uint32_t                                VMAC_TX_D_GAIN                       :12;
    uint32_t                                reserved0                            :20;
}   PHY_PHY_TOPIF_VMACCFG13;

typedef union {
    uint32_t                                w;
    PHY_PHY_TOPIF_VMACCFG13                 b;
}   PHY_PHY_TOPIF_VMACCFG13_U;


// 0x4008A000 register ------------------------------------
typedef struct {
    uint32_t                                r2_reg_tx_chpos                      :2 ;
    uint32_t                                reserved0                            :30;
}   PHY_AH_TX_DFE_LPF00;

typedef union {
    uint32_t                                w;
    PHY_AH_TX_DFE_LPF00                     b;
}   PHY_AH_TX_DFE_LPF00_U;


// 0x4008A004 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_tx_dig_mix                     :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_TX_DFE_LPF01;

typedef union {
    uint32_t                                w;
    PHY_AH_TX_DFE_LPF01                     b;
}   PHY_AH_TX_DFE_LPF01_U;


// 0x4008A008 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_tx_upplow_swap                 :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_TX_DFE_LPF02;

typedef union {
    uint32_t                                w;
    PHY_AH_TX_DFE_LPF02                     b;
}   PHY_AH_TX_DFE_LPF02_U;


// 0x4008A010 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_tx1m_use2m                     :1 ;
    uint32_t                                reserved0                            :3 ;
    uint32_t                                r_reg_sel_1m_iir                     :1 ;
    uint32_t                                reserved1                            :27;
}   PHY_AH_TX_DFE_LPF04;

typedef union {
    uint32_t                                w;
    PHY_AH_TX_DFE_LPF04                     b;
}   PHY_AH_TX_DFE_LPF04_U;


// 0x4008A014 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_tx_dac_4x                      :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_TX_DFE_LPF05;

typedef union {
    uint32_t                                w;
    PHY_AH_TX_DFE_LPF05                     b;
}   PHY_AH_TX_DFE_LPF05_U;


// 0x4008A018 register ------------------------------------
typedef struct {
    uint32_t                                r16_reg_tx_digital_gain              :16;
    uint32_t                                reserved0                            :16;
}   PHY_AH_TX_DFE_LPF06;

typedef union {
    uint32_t                                w;
    PHY_AH_TX_DFE_LPF06                     b;
}   PHY_AH_TX_DFE_LPF06_U;


// 0x4008A01C register ------------------------------------
typedef struct {
    uint32_t                                r_reg_tx_gain_sel                    :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_TX_DFE_LPF07;

typedef union {
    uint32_t                                w;
    PHY_AH_TX_DFE_LPF07                     b;
}   PHY_AH_TX_DFE_LPF07_U;


// 0x4008A020 register ------------------------------------
typedef struct {
    uint32_t                                r30_reg_thr_bpsk                     :30;
    uint32_t                                reserved0                            :2 ;
}   PHY_AH_TX_DFE_LPF08;

typedef union {
    uint32_t                                w;
    PHY_AH_TX_DFE_LPF08                     b;
}   PHY_AH_TX_DFE_LPF08_U;


// 0x4008A024 register ------------------------------------
typedef struct {
    uint32_t                                r30_reg_thr_qpsk                     :30;
    uint32_t                                reserved0                            :2 ;
}   PHY_AH_TX_DFE_LPF09;

typedef union {
    uint32_t                                w;
    PHY_AH_TX_DFE_LPF09                     b;
}   PHY_AH_TX_DFE_LPF09_U;


// 0x4008A028 register ------------------------------------
typedef struct {
    uint32_t                                r30_reg_thr_16qam                    :30;
    uint32_t                                reserved0                            :2 ;
}   PHY_AH_TX_DFE_LPF10;

typedef union {
    uint32_t                                w;
    PHY_AH_TX_DFE_LPF10                     b;
}   PHY_AH_TX_DFE_LPF10_U;


// 0x4008A02C register ------------------------------------
typedef struct {
    uint32_t                                r30_reg_thr_64qam                    :30;
    uint32_t                                reserved0                            :2 ;
}   PHY_AH_TX_DFE_LPF11;

typedef union {
    uint32_t                                w;
    PHY_AH_TX_DFE_LPF11                     b;
}   PHY_AH_TX_DFE_LPF11_U;


// 0x4008A030 register ------------------------------------
typedef struct {
    uint32_t                                r30_reg_pgain_bpsk                   :30;
    uint32_t                                reserved0                            :2 ;
}   PHY_AH_TX_DFE_LPF12;

typedef union {
    uint32_t                                w;
    PHY_AH_TX_DFE_LPF12                     b;
}   PHY_AH_TX_DFE_LPF12_U;


// 0x4008A034 register ------------------------------------
typedef struct {
    uint32_t                                r30_reg_pgain_qpsk                   :30;
    uint32_t                                reserved0                            :2 ;
}   PHY_AH_TX_DFE_LPF13;

typedef union {
    uint32_t                                w;
    PHY_AH_TX_DFE_LPF13                     b;
}   PHY_AH_TX_DFE_LPF13_U;


// 0x4008A038 register ------------------------------------
typedef struct {
    uint32_t                                r30_reg_pgain_16qam                  :30;
    uint32_t                                reserved0                            :2 ;
}   PHY_AH_TX_DFE_LPF14;

typedef union {
    uint32_t                                w;
    PHY_AH_TX_DFE_LPF14                     b;
}   PHY_AH_TX_DFE_LPF14_U;


// 0x4008A03C register ------------------------------------
typedef struct {
    uint32_t                                r30_reg_pgain_64qam                  :30;
    uint32_t                                reserved0                            :2 ;
}   PHY_AH_TX_DFE_LPF15;

typedef union {
    uint32_t                                w;
    PHY_AH_TX_DFE_LPF15                     b;
}   PHY_AH_TX_DFE_LPF15_U;


// 0x4008A040 register ------------------------------------
typedef struct {
    uint32_t                                r2_reg_cfr_control                   :2 ;
    uint32_t                                reserved0                            :30;
}   PHY_AH_TX_DFE_LPF16;

typedef union {
    uint32_t                                w;
    PHY_AH_TX_DFE_LPF16                     b;
}   PHY_AH_TX_DFE_LPF16_U;


// 0x4008A400 register ------------------------------------
typedef struct {
    uint32_t                                r11_reg_tx_iq_para0                  :11;
    uint32_t                                reserved0                            :21;
}   PHY_AH_TX_DFE_CAL00;

typedef union {
    uint32_t                                w;
    PHY_AH_TX_DFE_CAL00                     b;
}   PHY_AH_TX_DFE_CAL00_U;


// 0x4008A404 register ------------------------------------
typedef struct {
    uint32_t                                r11_reg_tx_iq_para1                  :11;
    uint32_t                                reserved0                            :21;
}   PHY_AH_TX_DFE_CAL01;

typedef union {
    uint32_t                                w;
    PHY_AH_TX_DFE_CAL01                     b;
}   PHY_AH_TX_DFE_CAL01_U;


// 0x4008A408 register ------------------------------------
typedef struct {
    uint32_t                                r10_reg_tx_lo_para_i                 :10;
    uint32_t                                reserved0                            :22;
}   PHY_AH_TX_DFE_CAL02;

typedef union {
    uint32_t                                w;
    PHY_AH_TX_DFE_CAL02                     b;
}   PHY_AH_TX_DFE_CAL02_U;


// 0x4008A40C register ------------------------------------
typedef struct {
    uint32_t                                r10_reg_tx_lo_para_q                 :10;
    uint32_t                                reserved0                            :22;
}   PHY_AH_TX_DFE_CAL03;

typedef union {
    uint32_t                                w;
    PHY_AH_TX_DFE_CAL03                     b;
}   PHY_AH_TX_DFE_CAL03_U;


// 0x4008A410 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_tx_loiq_mode_sel               :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_TX_DFE_CAL04;

typedef union {
    uint32_t                                w;
    PHY_AH_TX_DFE_CAL04                     b;
}   PHY_AH_TX_DFE_CAL04_U;


// 0x4008BC00 register ------------------------------------
typedef struct {
    uint32_t                                r32_reg_sbr_sync_seq                 :32;
}   PHY_PHY_TXSBR00;

typedef union {
    uint32_t                                w;
    PHY_PHY_TXSBR00                         b;
}   PHY_PHY_TXSBR00_U;


// 0x4008BC04 register ------------------------------------
typedef struct {
    uint32_t                                r2_reg_sbr_gain                      :2 ;
    uint32_t                                reserved0                            :30;
}   PHY_PHY_TXSBR01;

typedef union {
    uint32_t                                w;
    PHY_PHY_TXSBR01                         b;
}   PHY_PHY_TXSBR01_U;


// 0x4008BC08 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_sbr_mem_mode                   :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_PHY_TXSBR02;

typedef union {
    uint32_t                                w;
    PHY_PHY_TXSBR02                         b;
}   PHY_PHY_TXSBR02_U;


// 0x4008BC0C register ------------------------------------
typedef struct {
    uint32_t                                r_reg_sbr_mem_wr_enable              :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_PHY_TXSBR03;

typedef union {
    uint32_t                                w;
    PHY_PHY_TXSBR03                         b;
}   PHY_PHY_TXSBR03_U;


// 0x4008BC10 register ------------------------------------
typedef struct {
    uint32_t                                r7_reg_sbr_mem_wr_addr               :7 ;
    uint32_t                                reserved0                            :25;
}   PHY_PHY_TXSBR04;

typedef union {
    uint32_t                                w;
    PHY_PHY_TXSBR04                         b;
}   PHY_PHY_TXSBR04_U;


// 0x4008BC14 register ------------------------------------
typedef struct {
    uint32_t                                r20_reg_sbr_mem_wr_data              :20;
    uint32_t                                reserved0                            :12;
}   PHY_PHY_TXSBR05;

typedef union {
    uint32_t                                w;
    PHY_PHY_TXSBR05                         b;
}   PHY_PHY_TXSBR05_U;


// 0x4008C000 register ------------------------------------
typedef struct {
    uint32_t                                o8_reg_sync_pts_move                 :8 ;
    uint32_t                                reserved0                            :24;
}   PHY_RX_DFE00;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE00                            b;
}   PHY_RX_DFE00_U;


// 0x4008C004 register ------------------------------------
typedef struct {
    uint32_t                                o_reg_simul_tx_support               :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_RX_DFE01;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE01                            b;
}   PHY_RX_DFE01_U;


// 0x4008C008 register ------------------------------------
typedef struct {
    uint32_t                                o_reg_cca_lvl_type                   :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_RX_DFE02;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE02                            b;
}   PHY_RX_DFE02_U;


// 0x4008C00C register ------------------------------------
typedef struct {
    uint32_t                                o2_reg_rx_latency                    :2 ;
    uint32_t                                reserved0                            :30;
}   PHY_RX_DFE03;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE03                            b;
}   PHY_RX_DFE03_U;


// 0x4008C010 register ------------------------------------
typedef struct {
    uint32_t                                o_reg_dc_res_to_agc_in               :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_RX_DFE04;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE04                            b;
}   PHY_RX_DFE04_U;


// 0x4008C01C register ------------------------------------
typedef struct {
    uint32_t                                o9_reg_refpwr_rcpi                   :9 ;
    uint32_t                                reserved0                            :23;
}   PHY_RX_DFE07;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE07                            b;
}   PHY_RX_DFE07_U;


// 0x4008C020 register ------------------------------------
typedef struct {
    uint32_t                                o6_reg_pkt_loss_thrd                 :6 ;
    uint32_t                                reserved0                            :26;
}   PHY_RX_DFE08;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE08                            b;
}   PHY_RX_DFE08_U;


// 0x4008C024 register ------------------------------------
typedef struct {
    uint32_t                                o32_reg_cca_thrd_1                   :32;
}   PHY_RX_DFE09;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE09                            b;
}   PHY_RX_DFE09_U;


// 0x4008C028 register ------------------------------------
typedef struct {
    uint32_t                                o16_reg_cca_thrd_2                   :16;
    uint32_t                                reserved0                            :16;
}   PHY_RX_DFE10;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE10                            b;
}   PHY_RX_DFE10_U;


// 0x4008C02C register ------------------------------------
typedef struct {
    uint32_t                                o32_reg_cca_thrd_3                   :32;
}   PHY_RX_DFE11;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE11                            b;
}   PHY_RX_DFE11_U;


// 0x4008C030 register ------------------------------------
typedef struct {
    uint32_t                                o_reg_dig_amp_bypass                 :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_RX_DFE12;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE12                            b;
}   PHY_RX_DFE12_U;


// 0x4008C034 register ------------------------------------
typedef struct {
    uint32_t                                o14_reg_dump_length                  :14;
    uint32_t                                reserved0                            :2 ;
    uint32_t                                o2_reg_dump_period                   :2 ;
    uint32_t                                reserved1                            :14;
}   PHY_RX_DFE13;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE13                            b;
}   PHY_RX_DFE13_U;


// 0x4008C038 register ------------------------------------
typedef struct {
    uint32_t                                o_reg_dump_start                     :1 ;
    uint32_t                                reserved0                            :3 ;
    uint32_t                                o_reg_dump_reset                     :1 ;
    uint32_t                                reserved1                            :3 ;
    uint32_t                                i14_last_dump_addr                   :14;
    uint32_t                                reserved2                            :10;
}   PHY_RX_DFE14;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE14                            b;
}   PHY_RX_DFE14_U;


// 0x4008C03C register ------------------------------------
typedef struct {
    uint32_t                                o8_reg_dump_sel                      :8 ;
    uint32_t                                o3_reg_trig_sel                      :3 ;
    uint32_t                                reserved0                            :21;
}   PHY_RX_DFE15;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE15                            b;
}   PHY_RX_DFE15_U;


// 0x4008C040 register ------------------------------------
typedef struct {
    uint32_t                                o_reg_str_pkt_on                     :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_RX_DFE16;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE16                            b;
}   PHY_RX_DFE16_U;


// 0x4008C044 register ------------------------------------
typedef struct {
    uint32_t                                o8_reg_str_pkt_op_thrd               :7 ;
    uint32_t                                reserved0                            :25;
}   PHY_RX_DFE17;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE17                            b;
}   PHY_RX_DFE17_U;


// 0x4008C048 register ------------------------------------
typedef struct {
    uint32_t                                o3_reg_cca_rssi_cnt                  :3 ;
    uint32_t                                reserved0                            :29;
}   PHY_RX_DFE18;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE18                            b;
}   PHY_RX_DFE18_U;


// 0x4008C04C register ------------------------------------
typedef struct {
    uint32_t                                o_reg_cca_sat_sel                    :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_RX_DFE19;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE19                            b;
}   PHY_RX_DFE19_U;


// 0x4008C070 register ------------------------------------
typedef struct {
    uint32_t                                o16_reg_rdfe_idle_time               :16;
    uint32_t                                reserved0                            :16;
}   PHY_RX_DFE_TIMER00;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_TIMER00                      b;
}   PHY_RX_DFE_TIMER00_U;


// 0x4008C07C register ------------------------------------
typedef struct {
    uint32_t                                o16_reg_rdfe_sync_wait_time          :16;
    uint32_t                                reserved0                            :16;
}   PHY_RX_DFE_TIMER03;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_TIMER03                      b;
}   PHY_RX_DFE_TIMER03_U;


// 0x4008C0A0 register ------------------------------------
typedef struct {
    uint32_t                                o16_reg_rdfe_rssi_wait_time          :16;
    uint32_t                                reserved0                            :16;
}   PHY_RX_DFE_TIMER12;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_TIMER12                      b;
}   PHY_RX_DFE_TIMER12_U;


// 0x4008C0B0 register ------------------------------------
typedef struct {
    uint32_t                                o_reg_rdfe_mon_cfg                   :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_RX_DFE_LOG_CFG;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG_CFG                      b;
}   PHY_RX_DFE_LOG_CFG_U;


// 0x4008C0B4 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_00              :32;
}   PHY_RX_DFE_LOG00;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG00                        b;
}   PHY_RX_DFE_LOG00_U;


// 0x4008C0B8 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_01              :32;
}   PHY_RX_DFE_LOG01;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG01                        b;
}   PHY_RX_DFE_LOG01_U;


// 0x4008C0BC register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_02              :32;
}   PHY_RX_DFE_LOG02;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG02                        b;
}   PHY_RX_DFE_LOG02_U;


// 0x4008C0C0 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_03              :32;
}   PHY_RX_DFE_LOG03;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG03                        b;
}   PHY_RX_DFE_LOG03_U;


// 0x4008C0C4 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_04              :32;
}   PHY_RX_DFE_LOG04;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG04                        b;
}   PHY_RX_DFE_LOG04_U;


// 0x4008C0C8 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_05              :32;
}   PHY_RX_DFE_LOG05;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG05                        b;
}   PHY_RX_DFE_LOG05_U;


// 0x4008C0CC register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_06              :32;
}   PHY_RX_DFE_LOG06;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG06                        b;
}   PHY_RX_DFE_LOG06_U;


// 0x4008C0D0 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_07              :32;
}   PHY_RX_DFE_LOG07;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG07                        b;
}   PHY_RX_DFE_LOG07_U;


// 0x4008C0D4 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_08              :32;
}   PHY_RX_DFE_LOG08;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG08                        b;
}   PHY_RX_DFE_LOG08_U;


// 0x4008C0D8 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_09              :32;
}   PHY_RX_DFE_LOG09;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG09                        b;
}   PHY_RX_DFE_LOG09_U;


// 0x4008C0DC register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_10              :32;
}   PHY_RX_DFE_LOG10;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG10                        b;
}   PHY_RX_DFE_LOG10_U;


// 0x4008C0E0 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_11              :32;
}   PHY_RX_DFE_LOG11;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG11                        b;
}   PHY_RX_DFE_LOG11_U;


// 0x4008C0E4 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_12              :32;
}   PHY_RX_DFE_LOG12;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG12                        b;
}   PHY_RX_DFE_LOG12_U;


// 0x4008C0E8 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_13              :32;
}   PHY_RX_DFE_LOG13;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG13                        b;
}   PHY_RX_DFE_LOG13_U;


// 0x4008C0EC register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_14              :32;
}   PHY_RX_DFE_LOG14;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG14                        b;
}   PHY_RX_DFE_LOG14_U;


// 0x4008C0F0 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_15              :32;
}   PHY_RX_DFE_LOG15;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG15                        b;
}   PHY_RX_DFE_LOG15_U;


// 0x4008C0F4 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_16              :32;
}   PHY_RX_DFE_LOG16;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG16                        b;
}   PHY_RX_DFE_LOG16_U;


// 0x4008C0F8 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_17              :32;
}   PHY_RX_DFE_LOG17;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG17                        b;
}   PHY_RX_DFE_LOG17_U;


// 0x4008C0FC register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_18              :32;
}   PHY_RX_DFE_LOG18;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG18                        b;
}   PHY_RX_DFE_LOG18_U;


// 0x4008C100 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_19              :32;
}   PHY_RX_DFE_LOG19;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG19                        b;
}   PHY_RX_DFE_LOG19_U;


// 0x4008C104 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_20              :32;
}   PHY_RX_DFE_LOG20;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG20                        b;
}   PHY_RX_DFE_LOG20_U;


// 0x4008C108 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_21              :32;
}   PHY_RX_DFE_LOG21;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG21                        b;
}   PHY_RX_DFE_LOG21_U;


// 0x4008C10C register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_22              :32;
}   PHY_RX_DFE_LOG22;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG22                        b;
}   PHY_RX_DFE_LOG22_U;


// 0x4008C110 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_23              :32;
}   PHY_RX_DFE_LOG23;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG23                        b;
}   PHY_RX_DFE_LOG23_U;


// 0x4008C114 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_24              :32;
}   PHY_RX_DFE_LOG24;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG24                        b;
}   PHY_RX_DFE_LOG24_U;


// 0x4008C118 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_25              :32;
}   PHY_RX_DFE_LOG25;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG25                        b;
}   PHY_RX_DFE_LOG25_U;


// 0x4008C11C register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_26              :32;
}   PHY_RX_DFE_LOG26;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG26                        b;
}   PHY_RX_DFE_LOG26_U;


// 0x4008C120 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_27              :32;
}   PHY_RX_DFE_LOG27;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG27                        b;
}   PHY_RX_DFE_LOG27_U;


// 0x4008C124 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_28              :32;
}   PHY_RX_DFE_LOG28;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG28                        b;
}   PHY_RX_DFE_LOG28_U;


// 0x4008C128 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_29              :32;
}   PHY_RX_DFE_LOG29;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG29                        b;
}   PHY_RX_DFE_LOG29_U;


// 0x4008C12C register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_30              :32;
}   PHY_RX_DFE_LOG30;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG30                        b;
}   PHY_RX_DFE_LOG30_U;


// 0x4008C130 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_31              :32;
}   PHY_RX_DFE_LOG31;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG31                        b;
}   PHY_RX_DFE_LOG31_U;


// 0x4008C134 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_32              :32;
}   PHY_RX_DFE_LOG32;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG32                        b;
}   PHY_RX_DFE_LOG32_U;


// 0x4008C138 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_33              :32;
}   PHY_RX_DFE_LOG33;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG33                        b;
}   PHY_RX_DFE_LOG33_U;


// 0x4008C13C register ------------------------------------
typedef struct {
    uint32_t                                i8_cca_rssi_pri1                     :8 ;
    uint32_t                                i8_cca_rssi_sec1                     :8 ;
    uint32_t                                i8_cca_rssi_pri2                     :8 ;
    uint32_t                                i8_cca_rssi_sec2                     :8 ;
}   PHY_RX_DFE_LOG34;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG34                        b;
}   PHY_RX_DFE_LOG34_U;


// 0x4008C140 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_35              :32;
}   PHY_RX_DFE_LOG35;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG35                        b;
}   PHY_RX_DFE_LOG35_U;


// 0x4008C144 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_36              :32;
}   PHY_RX_DFE_LOG36;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG36                        b;
}   PHY_RX_DFE_LOG36_U;


// 0x4008C148 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_37              :32;
}   PHY_RX_DFE_LOG37;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG37                        b;
}   PHY_RX_DFE_LOG37_U;


// 0x4008C14C register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_38              :32;
}   PHY_RX_DFE_LOG38;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG38                        b;
}   PHY_RX_DFE_LOG38_U;


// 0x4008C150 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_rdfe_mon_log_39              :32;
}   PHY_RX_DFE_LOG39;

typedef union {
    uint32_t                                w;
    PHY_RX_DFE_LOG39                        b;
}   PHY_RX_DFE_LOG39_U;


// 0x4008C400 register ------------------------------------
typedef struct {
    uint32_t                                r3_reg_agc_cal_limit                 :3 ;
    uint32_t                                reserved0                            :29;
}   PHY_AHA1_RXDFE_AGC_00;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_00                   b;
}   PHY_AHA1_RXDFE_AGC_00_U;


// 0x4008C404 register ------------------------------------
typedef struct {
    uint32_t                                r16_reg_agc_cal_opt                  :16;
    uint32_t                                reserved0                            :16;
}   PHY_AHA1_RXDFE_AGC_01;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_01                   b;
}   PHY_AHA1_RXDFE_AGC_01_U;


// 0x4008C408 register ------------------------------------
typedef struct {
    uint32_t                                r6_reg_rxm_set_time                  :6 ;
    uint32_t                                reserved0                            :26;
}   PHY_AHA1_RXDFE_AGC_02;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_02                   b;
}   PHY_AHA1_RXDFE_AGC_02_U;


// 0x4008C40C register ------------------------------------
typedef struct {
    uint32_t                                r3_reg_manual_rf_rssi                :3 ;
    uint32_t                                reserved0                            :29;
}   PHY_AHA1_RXDFE_AGC_03;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_03                   b;
}   PHY_AHA1_RXDFE_AGC_03_U;


// 0x4008C410 register ------------------------------------
typedef struct {
    uint32_t                                r9_reg_adc_sat_int_thr               :9 ;
    uint32_t                                reserved0                            :23;
}   PHY_AHA1_RXDFE_AGC_04;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_04                   b;
}   PHY_AHA1_RXDFE_AGC_04_U;


// 0x4008C414 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_adc_sat_ext                    :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AHA1_RXDFE_AGC_05;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_05                   b;
}   PHY_AHA1_RXDFE_AGC_05_U;


// 0x4008C418 register ------------------------------------
typedef struct {
    uint32_t                                r16_reg_agcwait                      :16;
    uint32_t                                reserved0                            :16;
}   PHY_AHA1_RXDFE_AGC_06;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_06                   b;
}   PHY_AHA1_RXDFE_AGC_06_U;


// 0x4008C41C register ------------------------------------
typedef struct {
    uint32_t                                r8_reg_agcref_noise                  :8 ;
    uint32_t                                reserved0                            :24;
}   PHY_AHA1_RXDFE_AGC_07;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_07                   b;
}   PHY_AHA1_RXDFE_AGC_07_U;


// 0x4008C420 register ------------------------------------
typedef struct {
    uint32_t                                r8_reg_agcref_aamp                   :8 ;
    uint32_t                                reserved0                            :24;
}   PHY_AHA1_RXDFE_AGC_08;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_08                   b;
}   PHY_AHA1_RXDFE_AGC_08_U;


// 0x4008C424 register ------------------------------------
typedef struct {
    uint32_t                                r8_reg_agcref_damp                   :8 ;
    uint32_t                                reserved0                            :24;
}   PHY_AHA1_RXDFE_AGC_09;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_09                   b;
}   PHY_AHA1_RXDFE_AGC_09_U;


// 0x4008C428 register ------------------------------------
typedef struct {
    uint32_t                                r2_reg_agc_opt                       :2 ;
    uint32_t                                reserved0                            :30;
}   PHY_AHA1_RXDFE_AGC_10;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_10                   b;
}   PHY_AHA1_RXDFE_AGC_10_U;


// 0x4008C42C register ------------------------------------
typedef struct {
    uint32_t                                r12_reg_rxhp_option                  :12;
    uint32_t                                reserved0                            :20;
}   PHY_AHA1_RXDFE_AGC_11;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_11                   b;
}   PHY_AHA1_RXDFE_AGC_11_U;


// 0x4008C430 register ------------------------------------
typedef struct {
    uint32_t                                r5_reg_agcstepsmall                  :5 ;
    uint32_t                                reserved0                            :27;
}   PHY_AHA1_RXDFE_AGC_12;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_12                   b;
}   PHY_AHA1_RXDFE_AGC_12_U;


// 0x4008C434 register ------------------------------------
typedef struct {
    uint32_t                                r5_reg_agcsteplna                    :5 ;
    uint32_t                                reserved0                            :27;
}   PHY_AHA1_RXDFE_AGC_13;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_13                   b;
}   PHY_AHA1_RXDFE_AGC_13_U;


// 0x4008C438 register ------------------------------------
typedef struct {
    uint32_t                                r5_reg_agcstepvga                    :5 ;
    uint32_t                                reserved0                            :27;
}   PHY_AHA1_RXDFE_AGC_14;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_14                   b;
}   PHY_AHA1_RXDFE_AGC_14_U;


// 0x4008C43C register ------------------------------------
typedef struct {
    uint32_t                                r5_reg_agcstepadc                    :5 ;
    uint32_t                                reserved0                            :27;
}   PHY_AHA1_RXDFE_AGC_15;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_15                   b;
}   PHY_AHA1_RXDFE_AGC_15_U;


// 0x4008C440 register ------------------------------------
typedef struct {
    uint32_t                                r5_reg_agcstepdamp                   :5 ;
    uint32_t                                reserved0                            :27;
}   PHY_AHA1_RXDFE_AGC_16;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_16                   b;
}   PHY_AHA1_RXDFE_AGC_16_U;


// 0x4008C444 register ------------------------------------
typedef struct {
    uint32_t                                r7_reg_rx_max_gain                   :7 ;
    uint32_t                                reserved0                            :25;
}   PHY_AHA1_RXDFE_AGC_17;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_17                   b;
}   PHY_AHA1_RXDFE_AGC_17_U;


// 0x4008C448 register ------------------------------------
typedef struct {
    uint32_t                                r3_reg_agcunlock                     :3 ;
    uint32_t                                reserved0                            :29;
}   PHY_AHA1_RXDFE_AGC_18;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_18                   b;
}   PHY_AHA1_RXDFE_AGC_18_U;


// 0x4008C44C register ------------------------------------
typedef struct {
    uint32_t                                r3_reg_agclock                       :3 ;
    uint32_t                                reserved0                            :29;
}   PHY_AHA1_RXDFE_AGC_19;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_19                   b;
}   PHY_AHA1_RXDFE_AGC_19_U;


// 0x4008C450 register ------------------------------------
typedef struct {
    uint32_t                                r3_reg_agcuncal                      :3 ;
    uint32_t                                reserved0                            :29;
}   PHY_AHA1_RXDFE_AGC_20;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_20                   b;
}   PHY_AHA1_RXDFE_AGC_20_U;


// 0x4008C454 register ------------------------------------
typedef struct {
    uint32_t                                r3_reg_agccal                        :3 ;
    uint32_t                                reserved0                            :29;
}   PHY_AHA1_RXDFE_AGC_21;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_21                   b;
}   PHY_AHA1_RXDFE_AGC_21_U;


// 0x4008C458 register ------------------------------------
typedef struct {
    uint32_t                                r7_reg_db_initial_gain               :7 ;
    uint32_t                                reserved0                            :25;
}   PHY_AHA1_RXDFE_AGC_22;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_22                   b;
}   PHY_AHA1_RXDFE_AGC_22_U;


// 0x4008C45C register ------------------------------------
typedef struct {
    uint32_t                                r2_reg_rf_sel                        :2 ;
    uint32_t                                reserved0                            :30;
}   PHY_AHA1_RXDFE_AGC_23;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_23                   b;
}   PHY_AHA1_RXDFE_AGC_23_U;


// 0x4008C460 register ------------------------------------
typedef struct {
    uint32_t                                r9_reg_fast_dcoc_pck_end_opt         :9 ;
    uint32_t                                reserved0                            :23;
}   PHY_AHA1_RXDFE_AGC_24;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_24                   b;
}   PHY_AHA1_RXDFE_AGC_24_U;


// 0x4008C464 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_f_dcoc_mode                    :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AHA1_RXDFE_AGC_25;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_25                   b;
}   PHY_AHA1_RXDFE_AGC_25_U;


// 0x4008C468 register ------------------------------------
typedef struct {
    uint32_t                                r6_reg_f_dcoc_cnt                    :6 ;
    uint32_t                                reserved0                            :26;
}   PHY_AHA1_RXDFE_AGC_26;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_26                   b;
}   PHY_AHA1_RXDFE_AGC_26_U;


// 0x4008C46C register ------------------------------------
typedef struct {
    uint32_t                                r_reg_aamp_dif_sel                   :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AHA1_RXDFE_AGC_27;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_27                   b;
}   PHY_AHA1_RXDFE_AGC_27_U;


// 0x4008C470 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_gain_out_sel                   :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AHA1_RXDFE_AGC_28;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_28                   b;
}   PHY_AHA1_RXDFE_AGC_28_U;


// 0x4008C474 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_lock_option                    :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AHA1_RXDFE_AGC_29;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_29                   b;
}   PHY_AHA1_RXDFE_AGC_29_U;


// 0x4008C478 register ------------------------------------
typedef struct {
    uint32_t                                r4_reg_sat_cnt_thr                   :4 ;
    uint32_t                                reserved0                            :28;
}   PHY_AHA1_RXDFE_AGC_30;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_30                   b;
}   PHY_AHA1_RXDFE_AGC_30_U;


// 0x4008C47C register ------------------------------------
typedef struct {
    uint32_t                                r4_reg_g_ctl_cnt_thr                 :4 ;
    uint32_t                                reserved0                            :28;
}   PHY_AHA1_RXDFE_AGC_31;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_31                   b;
}   PHY_AHA1_RXDFE_AGC_31_U;


// 0x4008C480 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_sat_sel                        :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AHA1_RXDFE_AGC_32;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_32                   b;
}   PHY_AHA1_RXDFE_AGC_32_U;


// 0x4008C484 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_manual_db_gctrl_on             :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AHA1_RXDFE_AGC_33;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_33                   b;
}   PHY_AHA1_RXDFE_AGC_33_U;


// 0x4008C488 register ------------------------------------
typedef struct {
    uint32_t                                r7_reg_db_gain_manual                :7 ;
    uint32_t                                reserved0                            :25;
}   PHY_AHA1_RXDFE_AGC_34;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_34                   b;
}   PHY_AHA1_RXDFE_AGC_34_U;


// 0x4008C48C register ------------------------------------
typedef struct {
    uint32_t                                r24_reg_ext_lna_opt                  :24;
    uint32_t                                reserved0                            :8 ;
}   PHY_AHA1_RXDFE_AGC_35;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_35                   b;
}   PHY_AHA1_RXDFE_AGC_35_U;


// 0x4008C490 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_damp_on                        :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AHA1_RXDFE_AGC_36;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_36                   b;
}   PHY_AHA1_RXDFE_AGC_36_U;


// 0x4008C494 register ------------------------------------
typedef struct {
    uint32_t                                r12_reg_damp_sat_thr                 :12;
    uint32_t                                reserved0                            :20;
}   PHY_AHA1_RXDFE_AGC_37;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_37                   b;
}   PHY_AHA1_RXDFE_AGC_37_U;


// 0x4008C498 register ------------------------------------
typedef struct {
    uint32_t                                r2_reg_rxgain_mem_type               :2 ;
    uint32_t                                reserved0                            :30;
}   PHY_AHA1_RXDFE_AGC_38;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_38                   b;
}   PHY_AHA1_RXDFE_AGC_38_U;


// 0x4008C49C register ------------------------------------
typedef struct {
    uint32_t                                r_reg_rxagc_lut_wr_enable            :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AHA1_RXDFE_AGC_39;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_39                   b;
}   PHY_AHA1_RXDFE_AGC_39_U;


// 0x4008C4A0 register ------------------------------------
typedef struct {
    uint32_t                                r7_reg_rxagc_lut_wr_addr             :7 ;
    uint32_t                                reserved0                            :25;
}   PHY_AHA1_RXDFE_AGC_40;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_40                   b;
}   PHY_AHA1_RXDFE_AGC_40_U;


// 0x4008C4A4 register ------------------------------------
typedef struct {
    uint32_t                                r24_reg_rxagc_lut_wr_data            :24;
    uint32_t                                reserved0                            :8 ;
}   PHY_AHA1_RXDFE_AGC_41;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_41                   b;
}   PHY_AHA1_RXDFE_AGC_41_U;


// 0x4008C4A8 register ------------------------------------
typedef struct {
    uint32_t                                r2_reg_rxagc_lut_wr_lna              :2 ;
    uint32_t                                reserved0                            :30;
}   PHY_AHA1_RXDFE_AGC_42;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_42                   b;
}   PHY_AHA1_RXDFE_AGC_42_U;


// 0x4008C4AC register ------------------------------------
typedef struct {
    uint32_t                                r2_reg_rxagc_lut_wr_vga1             :2 ;
    uint32_t                                reserved0                            :30;
}   PHY_AHA1_RXDFE_AGC_43;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_43                   b;
}   PHY_AHA1_RXDFE_AGC_43_U;


// 0x4008C4B0 register ------------------------------------
typedef struct {
    uint32_t                                r2_reg_rxagc_lut_wr_vga2             :2 ;
    uint32_t                                reserved0                            :30;
}   PHY_AHA1_RXDFE_AGC_44;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_44                   b;
}   PHY_AHA1_RXDFE_AGC_44_U;


// 0x4008C4B4 register ------------------------------------
typedef struct {
    uint32_t                                r4_reg_rxagc_lut_wr_vga3             :4 ;
    uint32_t                                reserved0                            :28;
}   PHY_AHA1_RXDFE_AGC_45;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_45                   b;
}   PHY_AHA1_RXDFE_AGC_45_U;


// 0x4008C4B8 register ------------------------------------
typedef struct {
    uint32_t                                i_reg_nc_done                        :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AHA1_RXDFE_AGC_46;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_46                   b;
}   PHY_AHA1_RXDFE_AGC_46_U;


// 0x4008C4BC register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_nc_out                       :32;
}   PHY_AHA1_RXDFE_AGC_47;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_47                   b;
}   PHY_AHA1_RXDFE_AGC_47_U;


// 0x4008C4C0 register ------------------------------------
typedef struct {
    uint32_t                                i_reg_ic_done                        :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AHA1_RXDFE_AGC_48;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_48                   b;
}   PHY_AHA1_RXDFE_AGC_48_U;


// 0x4008C4C4 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_ic_out                       :32;
}   PHY_AHA1_RXDFE_AGC_49;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_49                   b;
}   PHY_AHA1_RXDFE_AGC_49_U;


// 0x4008C4C8 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_rx_nic_cal_en                  :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AHA1_RXDFE_AGC_50;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_50                   b;
}   PHY_AHA1_RXDFE_AGC_50_U;


// 0x4008C4CC register ------------------------------------
typedef struct {
    uint32_t                                r_reg_rx_nic_en                      :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AHA1_RXDFE_AGC_51;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_51                   b;
}   PHY_AHA1_RXDFE_AGC_51_U;


// 0x4008C4D0 register ------------------------------------
typedef struct {
    uint32_t                                r10_reg_nc_en_delay                  :10;
    uint32_t                                reserved0                            :22;
}   PHY_AHA1_RXDFE_AGC_52;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_52                   b;
}   PHY_AHA1_RXDFE_AGC_52_U;


// 0x4008C4D4 register ------------------------------------
typedef struct {
    uint32_t                                r3_reg_nic_cnt_thr_opt               :3 ;
    uint32_t                                reserved0                            :29;
}   PHY_AHA1_RXDFE_AGC_53;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_53                   b;
}   PHY_AHA1_RXDFE_AGC_53_U;


// 0x4008C4D8 register ------------------------------------
typedef struct {
    uint32_t                                r16_reg_prev_st_nc_cond              :16;
    uint32_t                                reserved0                            :16;
}   PHY_AHA1_RXDFE_AGC_54;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_54                   b;
}   PHY_AHA1_RXDFE_AGC_54_U;


// 0x4008C4DC register ------------------------------------
typedef struct {
    uint32_t                                r16_reg_curr_st_nc_cond              :16;
    uint32_t                                reserved0                            :16;
}   PHY_AHA1_RXDFE_AGC_55;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_55                   b;
}   PHY_AHA1_RXDFE_AGC_55_U;


// 0x4008C4E0 register ------------------------------------
typedef struct {
    uint32_t                                r16_reg_prev_st_ic_cond              :16;
    uint32_t                                reserved0                            :16;
}   PHY_AHA1_RXDFE_AGC_56;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_56                   b;
}   PHY_AHA1_RXDFE_AGC_56_U;


// 0x4008C4E4 register ------------------------------------
typedef struct {
    uint32_t                                r16_reg_curr_st_ic_cond              :16;
    uint32_t                                reserved0                            :16;
}   PHY_AHA1_RXDFE_AGC_57;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_57                   b;
}   PHY_AHA1_RXDFE_AGC_57_U;


// 0x4008C4E8 register ------------------------------------
typedef struct {
    uint32_t                                r16_reg_disable_st_cond              :16;
    uint32_t                                reserved0                            :16;
}   PHY_AHA1_RXDFE_AGC_58;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_58                   b;
}   PHY_AHA1_RXDFE_AGC_58_U;


// 0x4008C4EC register ------------------------------------
typedef struct {
    uint32_t                                r2_reg_nic_mode                      :2 ;
    uint32_t                                reserved0                            :30;
}   PHY_AHA1_RXDFE_AGC_59;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_59                   b;
}   PHY_AHA1_RXDFE_AGC_59_U;


// 0x4008C4F0 register ------------------------------------
typedef struct {
    uint32_t                                r2_reg_nic_damp_in_loc               :2 ;
    uint32_t                                reserved0                            :30;
}   PHY_AHA1_RXDFE_AGC_60;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_60                   b;
}   PHY_AHA1_RXDFE_AGC_60_U;


// 0x4008C4F4 register ------------------------------------
typedef struct {
    uint32_t                                r3_reg_gv_delay                      :3 ;
    uint32_t                                reserved0                            :29;
}   PHY_AHA1_RXDFE_AGC_61;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_61                   b;
}   PHY_AHA1_RXDFE_AGC_61_U;


// 0x4008C4F8 register ------------------------------------
typedef struct {
    uint32_t                                i_reg_nic_sat_ind                    :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AHA1_RXDFE_AGC_62;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_62                   b;
}   PHY_AHA1_RXDFE_AGC_62_U;


// 0x4008C4FC register ------------------------------------
typedef struct {
    uint32_t                                r8_reg_rx_min_gain                   :8 ;
    uint32_t                                reserved0                            :24;
}   PHY_AHA1_RXDFE_AGC_63;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_63                   b;
}   PHY_AHA1_RXDFE_AGC_63_U;


// 0x4008C500 register ------------------------------------
typedef struct {
    uint32_t                                r32_reg_rx_idle_time_cnt_thr         :32;
}   PHY_AHA1_RXDFE_AGC_64;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_64                   b;
}   PHY_AHA1_RXDFE_AGC_64_U;


// 0x4008C504 register ------------------------------------
typedef struct {
    uint32_t                                r16_reg_gcal_trk1_upd_thr            :16;
    uint32_t                                reserved0                            :16;
}   PHY_AHA1_RXDFE_AGC_65;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_65                   b;
}   PHY_AHA1_RXDFE_AGC_65_U;


// 0x4008C508 register ------------------------------------
typedef struct {
    uint32_t                                r16_reg_gcal_trk2_upd_thr            :16;
    uint32_t                                reserved0                            :16;
}   PHY_AHA1_RXDFE_AGC_66;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_66                   b;
}   PHY_AHA1_RXDFE_AGC_66_U;


// 0x4008C50C register ------------------------------------
typedef struct {
    uint32_t                                r_reg_gcal_wait_en                   :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AHA1_RXDFE_AGC_67;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_67                   b;
}   PHY_AHA1_RXDFE_AGC_67_U;


// 0x4008C510 register ------------------------------------
typedef struct {
    uint32_t                                r32_reg_gcal_wait1                   :32;
}   PHY_AHA1_RXDFE_AGC_68;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_68                   b;
}   PHY_AHA1_RXDFE_AGC_68_U;


// 0x4008C514 register ------------------------------------
typedef struct {
    uint32_t                                r32_reg_gcal_wait2                   :32;
}   PHY_AHA1_RXDFE_AGC_69;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_69                   b;
}   PHY_AHA1_RXDFE_AGC_69_U;


// 0x4008C518 register ------------------------------------
typedef struct {
    uint32_t                                r32_reg_gcal_wait3                   :32;
}   PHY_AHA1_RXDFE_AGC_70;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_70                   b;
}   PHY_AHA1_RXDFE_AGC_70_U;


// 0x4008C51C register ------------------------------------
typedef struct {
    uint32_t                                r16_reg_3rd_option                   :16;
    uint32_t                                reserved0                            :16;
}   PHY_AHA1_RXDFE_AGC_71;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_71                   b;
}   PHY_AHA1_RXDFE_AGC_71_U;


// 0x4008C520 register ------------------------------------
typedef struct {
    uint32_t                                r5_reg_rxagc_lut_wr_vga4             :5 ;
    uint32_t                                reserved0                            :27;
}   PHY_AHA1_RXDFE_AGC_72;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_AGC_72                   b;
}   PHY_AHA1_RXDFE_AGC_72_U;


// 0x4008C800 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_is1mcen                        :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AHA1_RXDFE_LPF_00;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_LPF_00                   b;
}   PHY_AHA1_RXDFE_LPF_00_U;


// 0x4008C804 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_rxlpf_uplow_swap               :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AHA1_RXDFE_LPF_01;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_LPF_01                   b;
}   PHY_AHA1_RXDFE_LPF_01_U;


// 0x4008C808 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_rxdfe_lowif_en                 :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AHA1_RXDFE_LPF_02;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_LPF_02                   b;
}   PHY_AHA1_RXDFE_LPF_02_U;


// 0x4008C80C register ------------------------------------
typedef struct {
    uint32_t                                r_reg_rxdfe_lowif_pos                :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AHA1_RXDFE_LPF_03;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_LPF_03                   b;
}   PHY_AHA1_RXDFE_LPF_03_U;


// 0x4008C810 register ------------------------------------
typedef struct {
    uint32_t                                r2_reg_rxlpf_option                  :2 ;
    uint32_t                                reserved0                            :30;
}   PHY_AHA1_RXDFE_LPF_04;

typedef union {
    uint32_t                                w;
    PHY_AHA1_RXDFE_LPF_04                   b;
}   PHY_AHA1_RXDFE_LPF_04_U;


// 0x4008CC00 register ------------------------------------
typedef struct {
    uint32_t                                reserved0                            :8 ;
    uint32_t                                o6_reg_1Mthreshold2                  :6 ;
    uint32_t                                reserved1                            :2 ;
    uint32_t                                o6_reg_1Mthreshold3                  :6 ;
    uint32_t                                reserved2                            :10;
}   PHY_AH_RX_SYNC_1MTHRE;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_SYNC_1MTHRE                   b;
}   PHY_AH_RX_SYNC_1MTHRE_U;


// 0x4008CC04 register ------------------------------------
typedef struct {
    uint32_t                                o9_reg_1MstfTOcnt                    :9 ;
    uint32_t                                reserved0                            :7 ;
    uint32_t                                o9_reg_1Mstfchkcnt                   :9 ;
    uint32_t                                reserved1                            :7 ;
}   PHY_AH_RX_SYNC_1MSTF1;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_SYNC_1MSTF1                   b;
}   PHY_AH_RX_SYNC_1MSTF1_U;


// 0x4008CC08 register ------------------------------------
typedef struct {
    uint32_t                                o9_reg_1Mstfwait                     :9 ;
    uint32_t                                reserved0                            :23;
}   PHY_AH_RX_SYNC_1MSTF2;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_SYNC_1MSTF2                   b;
}   PHY_AH_RX_SYNC_1MSTF2_U;


// 0x4008CC0C register ------------------------------------
typedef struct {
    uint32_t                                o8_reg_1MfsyncTOcnt                  :8 ;
    uint32_t                                o8_reg_1Mfsyncconfirmcnt             :8 ;
    uint32_t                                o8_reg_1Mfsync2ndwait                :8 ;
    uint32_t                                reserved0                            :8 ;
}   PHY_AH_RX_SYNC_1MFSYNC;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_SYNC_1MFSYNC                  b;
}   PHY_AH_RX_SYNC_1MFSYNC_U;


// 0x4008CC10 register ------------------------------------
typedef struct {
    uint32_t                                o6_reg_1Mcfoidlecnt                  :6 ;
    uint32_t                                reserved0                            :2 ;
    uint32_t                                o6_reg_1Mcfodur1                     :6 ;
    uint32_t                                reserved1                            :2 ;
    uint32_t                                o6_reg_1Mcfowait4                    :6 ;
    uint32_t                                reserved2                            :2 ;
    uint32_t                                o6_reg_1Mcfodur2                     :6 ;
    uint32_t                                reserved3                            :2 ;
}   PHY_AH_RX_SYNC_1MCFO1;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_SYNC_1MCFO1                   b;
}   PHY_AH_RX_SYNC_1MCFO1_U;


// 0x4008CC14 register ------------------------------------
typedef struct {
    uint32_t                                o6_reg_1Mcfodur3                     :6 ;
    uint32_t                                reserved0                            :2 ;
    uint32_t                                o8_reg_1Mcfowait3                    :8 ;
    uint32_t                                reserved1                            :16;
}   PHY_AH_RX_SYNC_1MCFO2;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_SYNC_1MCFO2                   b;
}   PHY_AH_RX_SYNC_1MCFO2_U;


// 0x4008CC18 register ------------------------------------
typedef struct {
    uint32_t                                o_reg_skip2ndccfo                    :1 ;
    uint32_t                                o_reg_1mcenabssel                    :1 ;
    uint32_t                                reserved0                            :30;
}   PHY_AH_RX_SYNC_1MCTRL;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_SYNC_1MCTRL                   b;
}   PHY_AH_RX_SYNC_1MCTRL_U;


// 0x4008CC20 register ------------------------------------
typedef struct {
    uint32_t                                reserved0                            :8 ;
    uint32_t                                o6_reg_2Mthreshold3                  :6 ;
    uint32_t                                reserved1                            :18;
}   PHY_AH_RX_SYNC_2MTHRE;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_SYNC_2MTHRE                   b;
}   PHY_AH_RX_SYNC_2MTHRE_U;


// 0x4008CC24 register ------------------------------------
typedef struct {
    uint32_t                                o9_reg_2Mstfwait                     :9 ;
    uint32_t                                reserved0                            :7 ;
    uint32_t                                o9_reg_2MstfTOcnt                    :9 ;
    uint32_t                                reserved1                            :7 ;
}   PHY_AH_RX_SYNC_2MSTF;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_SYNC_2MSTF                    b;
}   PHY_AH_RX_SYNC_2MSTF_U;


// 0x4008CC28 register ------------------------------------
typedef struct {
    uint32_t                                o8_reg_2MfsyncTOcnt                  :8 ;
    uint32_t                                o8_reg_2Mfsyncconfirmcnt             :8 ;
    uint32_t                                o8_reg_2Mfsync2ndwait                :8 ;
    uint32_t                                reserved0                            :8 ;
}   PHY_AH_RX_SYNC_2MFSYNC;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_SYNC_2MFSYNC                  b;
}   PHY_AH_RX_SYNC_2MFSYNC_U;


// 0x4008CC2C register ------------------------------------
typedef struct {
    uint32_t                                o6_reg_2Mcfoidlecnt                  :6 ;
    uint32_t                                reserved0                            :2 ;
    uint32_t                                o6_reg_2Mcfodur1                     :6 ;
    uint32_t                                reserved1                            :2 ;
    uint32_t                                o6_reg_2Mcfodur2                     :8 ;
    uint32_t                                reserved2                            :8 ;
}   PHY_AH_RX_SYNC_2MCFO;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_SYNC_2MCFO                    b;
}   PHY_AH_RX_SYNC_2MCFO_U;


// 0x4008CC30 register ------------------------------------
typedef struct {
    uint32_t                                i13_reg_cfoerr                       :13;
    uint32_t                                reserved0                            :19;
}   PHY_AH_RX_SYNC_CFOERR;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_SYNC_CFOERR                   b;
}   PHY_AH_RX_SYNC_CFOERR_U;


// 0x4008CC34 register ------------------------------------
typedef struct {
    uint32_t                                o9_reg_fltdly1M_op2                  :9 ;
    uint32_t                                reserved0                            :7 ;
    uint32_t                                o9_reg_fltdly1M_op4                  :9 ;
    uint32_t                                reserved1                            :7 ;
}   PHY_AH_RX_SYNC_FLTDLY1M;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_SYNC_FLTDLY1M                 b;
}   PHY_AH_RX_SYNC_FLTDLY1M_U;


// 0x4008CC38 register ------------------------------------
typedef struct {
    uint32_t                                o9_reg_fltdly2M_op2                  :9 ;
    uint32_t                                reserved0                            :7 ;
    uint32_t                                o9_reg_fltdly2M_op4                  :9 ;
    uint32_t                                reserved1                            :7 ;
}   PHY_AH_RX_SYNC_FLTDLY2M;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_SYNC_FLTDLY2M                 b;
}   PHY_AH_RX_SYNC_FLTDLY2M_U;


// 0x4008CC3C register ------------------------------------
typedef struct {
    uint32_t                                o16_reg_1Mxcorrmin                   :16;
    uint32_t                                o16_reg_2Mxcorrmin                   :16;
}   PHY_AH_RX_SYNC_XCORRMIN;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_SYNC_XCORRMIN                 b;
}   PHY_AH_RX_SYNC_XCORRMIN_U;


// 0x4008CC40 register ------------------------------------
typedef struct {
    uint32_t                                o5_reg_fsyncdelay1M_op2              :5 ;
    uint32_t                                reserved0                            :3 ;
    uint32_t                                o5_reg_fsyncdelay1M_op4              :5 ;
    uint32_t                                reserved1                            :3 ;
    uint32_t                                o5_reg_fsyncdelay2M_op2              :5 ;
    uint32_t                                reserved2                            :3 ;
    uint32_t                                o5_reg_fsyncdelay2M_op4              :5 ;
    uint32_t                                reserved3                            :3 ;
}   PHY_AH_RX_SYNC_FSYNCD;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_SYNC_FSYNCD                   b;
}   PHY_AH_RX_SYNC_FSYNCD_U;


// 0x4008CC44 register ------------------------------------
typedef struct {
    uint32_t                                o4_reg_snrest1delay                  :4 ;
    uint32_t                                o4_reg_snrest2delay                  :4 ;
    uint32_t                                o5_reg_fsyncdelay1M_op1              :5 ;
    uint32_t                                reserved0                            :19;
}   PHY_AH_RX_SYNC_SNRESTD;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_SYNC_SNRESTD                  b;
}   PHY_AH_RX_SYNC_SNRESTD_U;


// 0x4008D000 register ------------------------------------
typedef struct {
    uint32_t                                r16_reg_conv_ratio1                  :16;
    uint32_t                                reserved0                            :16;
}   PHY_AH_PHTRK_EST_00;

typedef union {
    uint32_t                                w;
    PHY_AH_PHTRK_EST_00                     b;
}   PHY_AH_PHTRK_EST_00_U;


// 0x4008D004 register ------------------------------------
typedef struct {
    uint32_t                                r16_reg_conv_ratio2                  :16;
    uint32_t                                reserved0                            :16;
}   PHY_AH_PHTRK_EST_01;

typedef union {
    uint32_t                                w;
    PHY_AH_PHTRK_EST_01                     b;
}   PHY_AH_PHTRK_EST_01_U;


// 0x4008D008 register ------------------------------------
typedef struct {
    uint32_t                                r16_reg_conv_ratio3                  :16;
    uint32_t                                reserved0                            :16;
}   PHY_AH_PHTRK_EST_02;

typedef union {
    uint32_t                                w;
    PHY_AH_PHTRK_EST_02                     b;
}   PHY_AH_PHTRK_EST_02_U;


// 0x4008D00C register ------------------------------------
typedef struct {
    uint32_t                                r21_reg_cfo_rf_bias                  :16;
    uint32_t                                reserved0                            :16;
}   PHY_AH_PHTRK_EST_03;

typedef union {
    uint32_t                                w;
    PHY_AH_PHTRK_EST_03                     b;
}   PHY_AH_PHTRK_EST_03_U;


// 0x4008D400 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_cs_chk_dly_en                  :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_RX_CS00;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_CS00                          b;
}   PHY_AH_RX_CS00_U;


// 0x4008D404 register ------------------------------------
typedef struct {
    uint32_t                                r16_reg_cs_chk_dly_cnt               :16;
    uint32_t                                reserved0                            :16;
}   PHY_AH_RX_CS01;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_CS01                          b;
}   PHY_AH_RX_CS01_U;


// 0x4008D408 register ------------------------------------
typedef struct {
    uint32_t                                r4_reg_cs_enable                     :4 ;
    uint32_t                                reserved0                            :28;
}   PHY_AH_RX_CS02;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_CS02                          b;
}   PHY_AH_RX_CS02_U;


// 0x4008D40C register ------------------------------------
typedef struct {
    uint32_t                                r10_reg_cs_sat_thr                   :10;
    uint32_t                                reserved0                            :22;
}   PHY_AH_RX_CS03;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_CS03                          b;
}   PHY_AH_RX_CS03_U;


// 0x4008D410 register ------------------------------------
typedef struct {
    uint32_t                                r4_reg_cs_sat_det_cnt                :4 ;
    uint32_t                                reserved0                            :28;
}   PHY_AH_RX_CS04;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_CS04                          b;
}   PHY_AH_RX_CS04_U;


// 0x4008D414 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_cs_sat_wait_en                 :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_RX_CS05;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_CS05                          b;
}   PHY_AH_RX_CS05_U;


// 0x4008D418 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_cs_sat_scheme_sel              :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_RX_CS06;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_CS06                          b;
}   PHY_AH_RX_CS06_U;


// 0x4008D41C register ------------------------------------
typedef struct {
    uint32_t                                r_reg_cs_sat_op1m_sel                :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_RX_CS07;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_CS07                          b;
}   PHY_AH_RX_CS07_U;


// 0x4008D420 register ------------------------------------
typedef struct {
    uint32_t                                r8_reg_cs_sat_pwr_thr1               :8 ;
    uint32_t                                reserved0                            :24;
}   PHY_AH_RX_CS08;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_CS08                          b;
}   PHY_AH_RX_CS08_U;


// 0x4008D424 register ------------------------------------
typedef struct {
    uint32_t                                r8_reg_cs_sat_pwr_thr2               :8 ;
    uint32_t                                reserved0                            :24;
}   PHY_AH_RX_CS09;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_CS09                          b;
}   PHY_AH_RX_CS09_U;


// 0x4008D440 register ------------------------------------
typedef struct {
    uint32_t                                r2_reg_cs_xcor_out_sel               :2 ;
    uint32_t                                reserved0                            :30;
}   PHY_AH_RX_CS10;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_CS10                          b;
}   PHY_AH_RX_CS10_U;


// 0x4008D444 register ------------------------------------
typedef struct {
    uint32_t                                r16_reg_cs_xcor_pwr_wgt              :16;
    uint32_t                                reserved0                            :16;
}   PHY_AH_RX_CS11;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_CS11                          b;
}   PHY_AH_RX_CS11_U;


// 0x4008D448 register ------------------------------------
typedef struct {
    uint32_t                                r24_reg_cs_xcor_pwr_thr1             :24;
    uint32_t                                reserved0                            :8 ;
}   PHY_AH_RX_CS12;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_CS12                          b;
}   PHY_AH_RX_CS12_U;


// 0x4008D44C register ------------------------------------
typedef struct {
    uint32_t                                r24_reg_cs_xcor_pwr_thr2             :24;
    uint32_t                                reserved0                            :8 ;
}   PHY_AH_RX_CS13;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_CS13                          b;
}   PHY_AH_RX_CS13_U;


// 0x4008D450 register ------------------------------------
typedef struct {
    uint32_t                                r8_reg_cs_rssi_thr1                  :8 ;
    uint32_t                                reserved0                            :24;
}   PHY_AH_RX_CS14;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_CS14                          b;
}   PHY_AH_RX_CS14_U;


// 0x4008D454 register ------------------------------------
typedef struct {
    uint32_t                                r8_reg_cs_rssi_thr2                  :8 ;
    uint32_t                                reserved0                            :24;
}   PHY_AH_RX_CS15;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_CS15                          b;
}   PHY_AH_RX_CS15_U;


// 0x4008D458 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_cs_xcor_1m_sel                 :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_RX_CS16;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_CS16                          b;
}   PHY_AH_RX_CS16_U;


// 0x4008D45C register ------------------------------------
typedef struct {
    uint32_t                                r_reg_cs_xcor_scheme_sel             :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_RX_CS17;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_CS17                          b;
}   PHY_AH_RX_CS17_U;


// 0x4008D460 register ------------------------------------
typedef struct {
    uint32_t                                r16_reg_cs_xcor_pwr_wgt_r            :16;
    uint32_t                                reserved0                            :16;
}   PHY_AH_RX_CS18;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_CS18                          b;
}   PHY_AH_RX_CS18_U;


// 0x4008D464 register ------------------------------------
typedef struct {
    uint32_t                                r24_reg_cs_xcor_pwr_thr1_r           :24;
    uint32_t                                reserved0                            :8 ;
}   PHY_AH_RX_CS19;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_CS19                          b;
}   PHY_AH_RX_CS19_U;


// 0x4008D468 register ------------------------------------
typedef struct {
    uint32_t                                r24_reg_cs_xcor_pwr_thr2_r           :24;
    uint32_t                                reserved0                            :8 ;
}   PHY_AH_RX_CS1A;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_CS1A                          b;
}   PHY_AH_RX_CS1A_U;


// 0x4008D480 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_mid_cca_en                     :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_RX_CS20;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_CS20                          b;
}   PHY_AH_RX_CS20_U;


// 0x4008D484 register ------------------------------------
typedef struct {
    uint32_t                                r8_reg_mid_cca_time                  :20;
    uint32_t                                reserved0                            :12;
}   PHY_AH_RX_CS21;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_CS21                          b;
}   PHY_AH_RX_CS21_U;


// 0x4008D488 register ------------------------------------
typedef struct {
    uint32_t                                r6_reg_mid_cca_acr_wgt               :6 ;
    uint32_t                                reserved0                            :26;
}   PHY_AH_RX_CS22;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_CS22                          b;
}   PHY_AH_RX_CS22_U;


// 0x4008D48C register ------------------------------------
typedef struct {
    uint32_t                                r20_reg_mid_cca_pwr_avg_thr          :20;
    uint32_t                                reserved0                            :12;
}   PHY_AH_RX_CS23;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_CS23                          b;
}   PHY_AH_RX_CS23_U;


// 0x4008D490 register ------------------------------------
typedef struct {
    uint32_t                                r5_reg_mid_cca_det_thr               :5 ;
    uint32_t                                reserved0                            :27;
}   PHY_AH_RX_CS24;

typedef union {
    uint32_t                                w;
    PHY_AH_RX_CS24                          b;
}   PHY_AH_RX_CS24_U;


// 0x4008DC00 register ------------------------------------
typedef struct {
    uint32_t                                o_reg_iqdc_hpf_on                    :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_RXDFE_IQDC_HPF_ON;

typedef union {
    uint32_t                                w;
    PHY_RXDFE_IQDC_HPF_ON                   b;
}   PHY_RXDFE_IQDC_HPF_ON_U;


// 0x4008DC04 register ------------------------------------
typedef struct {
    uint32_t                                o_reg_iqdc_hpf_while_agc             :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_RXDFE_IQDC_HPF_WHILE_AGC;

typedef union {
    uint32_t                                w;
    PHY_RXDFE_IQDC_HPF_WHILE_AGC            b;
}   PHY_RXDFE_IQDC_HPF_WHILE_AGC_U;


// 0x4008DC08 register ------------------------------------
typedef struct {
    uint32_t                                o3_reg_iqdc_hpf_wgt0                 :3 ;
    uint32_t                                reserved0                            :29;
}   PHY_RXDFE_IQDC_HPF_WGT0;

typedef union {
    uint32_t                                w;
    PHY_RXDFE_IQDC_HPF_WGT0                 b;
}   PHY_RXDFE_IQDC_HPF_WGT0_U;


// 0x4008DC0C register ------------------------------------
typedef struct {
    uint32_t                                o3_reg_iqdc_hpf_wgt1                 :3 ;
    uint32_t                                reserved0                            :29;
}   PHY_RXDFE_IQDC_HPF_WGT1;

typedef union {
    uint32_t                                w;
    PHY_RXDFE_IQDC_HPF_WGT1                 b;
}   PHY_RXDFE_IQDC_HPF_WGT1_U;


// 0x4008DC10 register ------------------------------------
typedef struct {
    uint32_t                                o3_reg_iqdc_hpf_wgt2                 :3 ;
    uint32_t                                reserved0                            :29;
}   PHY_RXDFE_IQDC_HPF_WGT2;

typedef union {
    uint32_t                                w;
    PHY_RXDFE_IQDC_HPF_WGT2                 b;
}   PHY_RXDFE_IQDC_HPF_WGT2_U;


// 0x4008DC14 register ------------------------------------
typedef struct {
    uint32_t                                o8_reg_iqdc_hpf_dur_wgt2             :8 ;
    uint32_t                                reserved0                            :24;
}   PHY_RXDFE_IQDC_HPF_DUR_WGT2;

typedef union {
    uint32_t                                w;
    PHY_RXDFE_IQDC_HPF_DUR_WGT2             b;
}   PHY_RXDFE_IQDC_HPF_DUR_WGT2_U;


// 0x4008DC18 register ------------------------------------
typedef struct {
    uint32_t                                o10_reg_iqdc_lut_highpwr_det_thr     :10;
    uint32_t                                reserved0                            :10;
    uint32_t                                o_reg_iqdc_lut_autorun_start         :1 ;
    uint32_t                                reserved1                            :3 ;
    uint32_t                                o_reg_iqdc_lut_manual_cfg            :1 ;
    uint32_t                                reserved2                            :3 ;
    uint32_t                                o_reg_iqdc_lut_ena                   :1 ;
    uint32_t                                reserved3                            :3 ;
}   PHY_RXDFE_IQDC_LUT_CFG;

typedef union {
    uint32_t                                w;
    PHY_RXDFE_IQDC_LUT_CFG                  b;
}   PHY_RXDFE_IQDC_LUT_CFG_U;


// 0x4008DC1C register ------------------------------------
typedef struct {
    uint32_t                                o8_reg_iqdc_lut_gainset_wait         :8 ;
    uint32_t                                o2_reg_iqdc_lut_msr_len              :2 ;
    uint32_t                                reserved0                            :6 ;
    uint32_t                                o8_reg_iqdc_lut_mingain              :8 ;
    uint32_t                                o8_reg_iqdc_lut_maxgain              :8 ;
}   PHY_RXDFE_IQDC_LUT_ALG;

typedef union {
    uint32_t                                w;
    PHY_RXDFE_IQDC_LUT_ALG                  b;
}   PHY_RXDFE_IQDC_LUT_ALG_U;


// 0x4008DC20 register ------------------------------------
typedef struct {
    uint32_t                                o20_reg_iqdc_lut_wrdata              :20;
    uint32_t                                reserved0                            :4 ;
    uint32_t                                o8_reg_iqdc_lut_wraddr               :8 ;
}   PHY_RXDFE_IQDC_LUT_WRITE;

typedef union {
    uint32_t                                w;
    PHY_RXDFE_IQDC_LUT_WRITE                b;
}   PHY_RXDFE_IQDC_LUT_WRITE_U;


// 0x4008DC24 register ------------------------------------
typedef struct {
    uint32_t                                reserved0                            :24;
    uint32_t                                o8_reg_iqdc_lut_rdaddr               :8 ;
}   PHY_RXDFE_IQDC_LUT_READ;

typedef union {
    uint32_t                                w;
    PHY_RXDFE_IQDC_LUT_READ                 b;
}   PHY_RXDFE_IQDC_LUT_READ_U;


// 0x4008DC28 register ------------------------------------
typedef struct {
    uint32_t                                i20_reg_iqdc_lut_rddata_out          :20;
    uint32_t                                reserved0                            :4 ;
    uint32_t                                i8_reg_iqdc_lut_rdaddr_out           :8 ;
}   PHY_RXDFE_IQDC_LUT_READ_RES;

typedef union {
    uint32_t                                w;
    PHY_RXDFE_IQDC_LUT_READ_RES             b;
}   PHY_RXDFE_IQDC_LUT_READ_RES_U;


// 0x4008DC2C register ------------------------------------
typedef struct {
    uint32_t                                i_ctl_iqdc_lut_autorun_done          :1 ;
    uint32_t                                i_reg_iqdc_lut_highpwr_det           :1 ;
    uint32_t                                reserved0                            :2 ;
    uint32_t                                i10_reg_iqdc_lut_highpwr_res         :10;
    uint32_t                                reserved1                            :18;
}   PHY_RXDFE_IQDC_LUT_AUTO_RES;

typedef union {
    uint32_t                                w;
    PHY_RXDFE_IQDC_LUT_AUTO_RES             b;
}   PHY_RXDFE_IQDC_LUT_AUTO_RES_U;


// 0x4008DC30 register ------------------------------------
typedef struct {
    uint32_t                                o8_reg_iqdc_cal_para0                :8 ;
    uint32_t                                reserved0                            :24;
}   PHY_RXDFE_IQDC_CAL_PARA0;

typedef union {
    uint32_t                                w;
    PHY_RXDFE_IQDC_CAL_PARA0                b;
}   PHY_RXDFE_IQDC_CAL_PARA0_U;


// 0x4008DC34 register ------------------------------------
typedef struct {
    uint32_t                                o8_reg_iqdc_cal_para1                :8 ;
    uint32_t                                reserved0                            :24;
}   PHY_RXDFE_IQDC_CAL_PARA1;

typedef union {
    uint32_t                                w;
    PHY_RXDFE_IQDC_CAL_PARA1                b;
}   PHY_RXDFE_IQDC_CAL_PARA1_U;


// 0x4008DC38 register ------------------------------------
typedef struct {
    uint32_t                                o_reg_iqdc_cal_self_val              :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_RXDFE_IQDC_CAL_SELF_VAL;

typedef union {
    uint32_t                                w;
    PHY_RXDFE_IQDC_CAL_SELF_VAL             b;
}   PHY_RXDFE_IQDC_CAL_SELF_VAL_U;


// 0x4008DC3C register ------------------------------------
typedef struct {
    uint32_t                                o16_reg_iqdc_cal_self_param_gain     :16;
    uint32_t                                reserved0                            :16;
}   PHY_RXDFE_IQDC_CAL_SELF_PARAM_GAIN;

typedef union {
    uint32_t                                w;
    PHY_RXDFE_IQDC_CAL_SELF_PARAM_GAIN      b;
}   PHY_RXDFE_IQDC_CAL_SELF_PARAM_GAIN_U;


// 0x4008DC40 register ------------------------------------
typedef struct {
    uint32_t                                o16_reg_iqdc_cal_self_param_phase    :16;
    uint32_t                                reserved0                            :16;
}   PHY_RXDFE_IQDC_CAL_SELF_PARAM_PHASE;

typedef union {
    uint32_t                                w;
    PHY_RXDFE_IQDC_CAL_SELF_PARAM_PHASE     b;
}   PHY_RXDFE_IQDC_CAL_SELF_PARAM_PHASE_U;


// 0x4008E004 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_manual_tx_en                   :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_RFAFE_INT_01;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_01                     b;
}   PHY_AH_RFAFE_INT_01_U;


// 0x4008E008 register ------------------------------------
typedef struct {
    uint32_t                                r3_reg_spi_sclk_rate                 :3 ;
    uint32_t                                r5_reg_spi_tx_length                 :5 ;
    uint32_t                                r2_reg_spi_rf_mode                   :2 ;
    uint32_t                                r_reg_spi_manual_mode                :1 ;
    uint32_t                                reserved0                            :20;
    uint32_t                                r_reg_spi_sync_reset                 :1 ;
}   PHY_AH_RFAFE_INT_02;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_02                     b;
}   PHY_AH_RFAFE_INT_02_U;


// 0x4008E00C register ------------------------------------
typedef struct {
    uint32_t                                r_reg_spi_hw_self_mode               :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_RFAFE_INT_03;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_03                     b;
}   PHY_AH_RFAFE_INT_03_U;


// 0x4008E010 register ------------------------------------
typedef struct {
    uint32_t                                r16_reg_spi_wait                     :16;
    uint32_t                                reserved0                            :16;
}   PHY_AH_RFAFE_INT_04;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_04                     b;
}   PHY_AH_RFAFE_INT_04_U;


// 0x4008E014 register ------------------------------------
typedef struct {
    uint32_t                                r5_reg_rf_center_freq                :5 ;
    uint32_t                                reserved0                            :27;
}   PHY_AH_RFAFE_INT_05;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_05                     b;
}   PHY_AH_RFAFE_INT_05_U;


// 0x4008E018 register ------------------------------------
typedef struct {
    uint32_t                                i_reg_hw_self_config_done            :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_RFAFE_INT_06;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_06                     b;
}   PHY_AH_RFAFE_INT_06_U;


// 0x4008E01C register ------------------------------------
typedef struct {
    uint32_t                                r32_reg_spi_sw_tx_data               :32;
}   PHY_AH_RFAFE_INT_07;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_07                     b;
}   PHY_AH_RFAFE_INT_07_U;


// 0x4008E020 register ------------------------------------
typedef struct {
    uint32_t                                r7_reg_int_paon_delay                :7 ;
    uint32_t                                reserved0                            :25;
}   PHY_AH_RFAFE_INT_08;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_08                     b;
}   PHY_AH_RFAFE_INT_08_U;


// 0x4008E024 register ------------------------------------
typedef struct {
    uint32_t                                i6_reg_spi_config                    :6 ;
    uint32_t                                reserved0                            :26;
}   PHY_AH_RFAFE_INT_09;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_09                     b;
}   PHY_AH_RFAFE_INT_09_U;


// 0x4008E028 register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_spi_wr_data                  :32;
}   PHY_AH_RFAFE_INT_10;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_10                     b;
}   PHY_AH_RFAFE_INT_10_U;


// 0x4008E02C register ------------------------------------
typedef struct {
    uint32_t                                i32_reg_spi_rd_data                  :32;
}   PHY_AH_RFAFE_INT_11;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_11                     b;
}   PHY_AH_RFAFE_INT_11_U;


// 0x4008E030 register ------------------------------------
typedef struct {
    uint32_t                                i2_reg_spi_access_status             :2 ;
    uint32_t                                reserved0                            :30;
}   PHY_AH_RFAFE_INT_12;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_12                     b;
}   PHY_AH_RFAFE_INT_12_U;


// 0x4008E034 register ------------------------------------
typedef struct {
    uint32_t                                r8_reg_rf_ctl_config                 :8 ;
    uint32_t                                reserved0                            :24;
}   PHY_AH_RFAFE_INT_13;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_13                     b;
}   PHY_AH_RFAFE_INT_13_U;


// 0x4008E038 register ------------------------------------
typedef struct {
    uint32_t                                r7_reg_txen_delay                    :7 ;
    uint32_t                                reserved0                            :25;
}   PHY_AH_RFAFE_INT_14;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_14                     b;
}   PHY_AH_RFAFE_INT_14_U;


// 0x4008E03C register ------------------------------------
typedef struct {
    uint32_t                                r7_reg_paon_delay                    :7 ;
    uint32_t                                reserved0                            :25;
}   PHY_AH_RFAFE_INT_15;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_15                     b;
}   PHY_AH_RFAFE_INT_15_U;


// 0x4008E040 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_shdn                           :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_RFAFE_INT_16;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_16                     b;
}   PHY_AH_RFAFE_INT_16_U;


// 0x4008E044 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_standby                        :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_RFAFE_INT_17;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_17                     b;
}   PHY_AH_RFAFE_INT_17_U;


// 0x4008E048 register ------------------------------------
typedef struct {
    uint32_t                                r7_reg_rf_txgain_ctl                 :7 ;
    uint32_t                                reserved0                            :25;
}   PHY_AH_RFAFE_INT_18;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_18                     b;
}   PHY_AH_RFAFE_INT_18_U;


// 0x4008E04C register ------------------------------------
typedef struct {
    uint32_t                                r2_reg_rfgain_load_option            :2 ;
    uint32_t                                reserved0                            :30;
}   PHY_AH_RFAFE_INT_19;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_19                     b;
}   PHY_AH_RFAFE_INT_19_U;


// 0x4008E050 register ------------------------------------
typedef struct {
    uint32_t                                r2_reg_addac_offset_bin              :2 ;
    uint32_t                                reserved0                            :30;
}   PHY_AH_RFAFE_INT_20;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_20                     b;
}   PHY_AH_RFAFE_INT_20_U;


// 0x4008E054 register ------------------------------------
typedef struct {
    uint32_t                                r2_reg_addac_iq_swap                 :2 ;
    uint32_t                                reserved0                            :30;
}   PHY_AH_RFAFE_INT_21;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_21                     b;
}   PHY_AH_RFAFE_INT_21_U;


// 0x4008E058 register ------------------------------------
typedef struct {
    uint32_t                                r20_reg_rfgain_ctl_manual            :20;
    uint32_t                                reserved0                            :12;
}   PHY_AH_RFAFE_INT_22;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_22                     b;
}   PHY_AH_RFAFE_INT_22_U;


// 0x4008E05C register ------------------------------------
typedef struct {
    uint32_t                                r_reg_rf_sel                         :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_RFAFE_INT_23;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_23                     b;
}   PHY_AH_RFAFE_INT_23_U;


// 0x4008E060 register ------------------------------------
typedef struct {
    uint32_t                                r2_reg_loiqcal_mode                  :2 ;
    uint32_t                                reserved0                            :30;
}   PHY_AH_RFAFE_INT_24;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_24                     b;
}   PHY_AH_RFAFE_INT_24_U;


// 0x4008E064 register ------------------------------------
typedef struct {
    uint32_t                                r2_reg_loiqcal_tone_freq             :2 ;
    uint32_t                                reserved0                            :30;
}   PHY_AH_RFAFE_INT_25;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_25                     b;
}   PHY_AH_RFAFE_INT_25_U;


// 0x4008E068 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_loiqcal_en                     :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_RFAFE_INT_26;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_26                     b;
}   PHY_AH_RFAFE_INT_26_U;


// 0x4008E06C register ------------------------------------
typedef struct {
    uint32_t                                r8_reg_loiqcal_loopback_delay        :8 ;
    uint32_t                                reserved0                            :24;
}   PHY_AH_RFAFE_INT_27;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_27                     b;
}   PHY_AH_RFAFE_INT_27_U;


// 0x4008E070 register ------------------------------------
typedef struct {
    uint32_t                                r2_reg_loiqcal_len                   :2 ;
    uint32_t                                reserved0                            :30;
}   PHY_AH_RFAFE_INT_28;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_28                     b;
}   PHY_AH_RFAFE_INT_28_U;


// 0x4008E074 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_loiqcal_stg_test               :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_RFAFE_INT_29;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_29                     b;
}   PHY_AH_RFAFE_INT_29_U;


// 0x4008E078 register ------------------------------------
typedef struct {
    uint32_t                                i_reg_loiqcal_error                  :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_RFAFE_INT_30;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_30                     b;
}   PHY_AH_RFAFE_INT_30_U;


// 0x4008E07C register ------------------------------------
typedef struct {
    uint32_t                                i_reg_loiqcal_val                    :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_RFAFE_INT_31;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_31                     b;
}   PHY_AH_RFAFE_INT_31_U;


// 0x4008E080 register ------------------------------------
typedef struct {
    uint32_t                                i15_reg_loiqcal_out_i                :15;
    uint32_t                                reserved0                            :17;
}   PHY_AH_RFAFE_INT_32;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_32                     b;
}   PHY_AH_RFAFE_INT_32_U;


// 0x4008E084 register ------------------------------------
typedef struct {
    uint32_t                                i15_reg_loiqcal_out_q                :15;
    uint32_t                                reserved0                            :17;
}   PHY_AH_RFAFE_INT_33;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_33                     b;
}   PHY_AH_RFAFE_INT_33_U;


// 0x4008E088 register ------------------------------------
typedef struct {
    uint32_t                                r11_reg_loiqcal_txiq_para_0          :11;
    uint32_t                                reserved0                            :21;
}   PHY_AH_RFAFE_INT_34;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_34                     b;
}   PHY_AH_RFAFE_INT_34_U;


// 0x4008E08C register ------------------------------------
typedef struct {
    uint32_t                                r11_reg_loiqcal_txiq_para_1          :11;
    uint32_t                                reserved0                            :21;
}   PHY_AH_RFAFE_INT_35;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_35                     b;
}   PHY_AH_RFAFE_INT_35_U;


// 0x4008E090 register ------------------------------------
typedef struct {
    uint32_t                                r10_reg_loiqcal_txlo_para_i          :10;
    uint32_t                                reserved0                            :22;
}   PHY_AH_RFAFE_INT_36;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_36                     b;
}   PHY_AH_RFAFE_INT_36_U;


// 0x4008E094 register ------------------------------------
typedef struct {
    uint32_t                                r10_reg_loiqcal_txlo_para_q          :10;
    uint32_t                                reserved0                            :22;
}   PHY_AH_RFAFE_INT_37;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_37                     b;
}   PHY_AH_RFAFE_INT_37_U;


// 0x4008E098 register ------------------------------------
typedef struct {
    uint32_t                                r8_reg_loiqcal_rxiq_para_0           :8 ;
    uint32_t                                reserved0                            :24;
}   PHY_AH_RFAFE_INT_38;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_38                     b;
}   PHY_AH_RFAFE_INT_38_U;


// 0x4008E09C register ------------------------------------
typedef struct {
    uint32_t                                r8_reg_loiqcal_rxiq_para_1           :8 ;
    uint32_t                                reserved0                            :24;
}   PHY_AH_RFAFE_INT_39;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_39                     b;
}   PHY_AH_RFAFE_INT_39_U;


// 0x4008E0A0 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_loiqcal_txloiq_pmsr_iqsel      :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_RFAFE_INT_40;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_40                     b;
}   PHY_AH_RFAFE_INT_40_U;


// 0x4008E0A4 register ------------------------------------
typedef struct {
    uint32_t                                r10_reg_loiqcal_self_len_est         :10;
    uint32_t                                reserved0                            :22;
}   PHY_AH_RFAFE_INT_41;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_41                     b;
}   PHY_AH_RFAFE_INT_41_U;


// 0x4008E0A8 register ------------------------------------
typedef struct {
    uint32_t                                r16_reg_loiqcal_self_len_cal         :16;
    uint32_t                                reserved0                            :16;
}   PHY_AH_RFAFE_INT_42;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_42                     b;
}   PHY_AH_RFAFE_INT_42_U;


// 0x4008E0AC register ------------------------------------
typedef struct {
    uint32_t                                r4_reg_loiqcal_self_step_gain        :4 ;
    uint32_t                                reserved0                            :28;
}   PHY_AH_RFAFE_INT_43;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_43                     b;
}   PHY_AH_RFAFE_INT_43_U;


// 0x4008E0B0 register ------------------------------------
typedef struct {
    uint32_t                                r4_reg_loiqcal_self_step_phase       :4 ;
    uint32_t                                reserved0                            :28;
}   PHY_AH_RFAFE_INT_44;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_44                     b;
}   PHY_AH_RFAFE_INT_44_U;


// 0x4008E0B4 register ------------------------------------
typedef struct {
    uint32_t                                i_reg_loiqcal_self_val               :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_RFAFE_INT_45;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_45                     b;
}   PHY_AH_RFAFE_INT_45_U;


// 0x4008E0B8 register ------------------------------------
typedef struct {
    uint32_t                                i21_reg_loiqcal_self_param_gain      :21;
    uint32_t                                reserved0                            :11;
}   PHY_AH_RFAFE_INT_46;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_46                     b;
}   PHY_AH_RFAFE_INT_46_U;


// 0x4008E0BC register ------------------------------------
typedef struct {
    uint32_t                                i21_reg_loiqcal_self_param_phase     :21;
    uint32_t                                reserved0                            :11;
}   PHY_AH_RFAFE_INT_47;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_47                     b;
}   PHY_AH_RFAFE_INT_47_U;


// 0x4008E0C0 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_loiqcal_txcal_test             :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_RFAFE_INT_48;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_48                     b;
}   PHY_AH_RFAFE_INT_48_U;


// 0x4008E0C4 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_loiqcal_rxcal_test             :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_RFAFE_INT_49;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_49                     b;
}   PHY_AH_RFAFE_INT_49_U;


// 0x4008E0C8 register ------------------------------------
typedef struct {
    uint32_t                                r8_reg_loiqcal_txiq_mis_0            :8 ;
    uint32_t                                reserved0                            :24;
}   PHY_AH_RFAFE_INT_50;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_50                     b;
}   PHY_AH_RFAFE_INT_50_U;


// 0x4008E0CC register ------------------------------------
typedef struct {
    uint32_t                                r8_reg_loiqcal_txiq_mis_1            :8 ;
    uint32_t                                reserved0                            :24;
}   PHY_AH_RFAFE_INT_51;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_51                     b;
}   PHY_AH_RFAFE_INT_51_U;


// 0x4008E0D0 register ------------------------------------
typedef struct {
    uint32_t                                r10_reg_loiqcal_txlo_mis_i           :10;
    uint32_t                                reserved0                            :22;
}   PHY_AH_RFAFE_INT_52;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_52                     b;
}   PHY_AH_RFAFE_INT_52_U;


// 0x4008E0D4 register ------------------------------------
typedef struct {
    uint32_t                                r10_reg_loiqcal_txlo_mis_q           :10;
    uint32_t                                reserved0                            :22;
}   PHY_AH_RFAFE_INT_53;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_53                     b;
}   PHY_AH_RFAFE_INT_53_U;


// 0x4008E0D8 register ------------------------------------
typedef struct {
    uint32_t                                r8_reg_loiqcal_rxiq_mis_0            :8 ;
    uint32_t                                reserved0                            :24;
}   PHY_AH_RFAFE_INT_54;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_54                     b;
}   PHY_AH_RFAFE_INT_54_U;


// 0x4008E0DC register ------------------------------------
typedef struct {
    uint32_t                                r8_reg_loiqcal_rxiq_mis_1            :8 ;
    uint32_t                                reserved0                            :24;
}   PHY_AH_RFAFE_INT_55;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_55                     b;
}   PHY_AH_RFAFE_INT_55_U;


// 0x4008E0E0 register ------------------------------------
typedef struct {
    uint32_t                                r8_reg_loiqcal_tx_dgain              :8 ;
    uint32_t                                reserved0                            :24;
}   PHY_AH_RFAFE_INT_56;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_56                     b;
}   PHY_AH_RFAFE_INT_56_U;


// 0x4008E0E4 register ------------------------------------
typedef struct {
    uint32_t                                r2_reg_rx_gain_load_delay            :2 ;
    uint32_t                                reserved0                            :30;
}   PHY_AH_RFAFE_INT_57;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_57                     b;
}   PHY_AH_RFAFE_INT_57_U;


// 0x4008E0E8 register ------------------------------------
typedef struct {
    uint32_t                                r2_reg_tx_gain_load_delay            :2 ;
    uint32_t                                reserved0                            :30;
}   PHY_AH_RFAFE_INT_58;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_58                     b;
}   PHY_AH_RFAFE_INT_58_U;


// 0x4008E0EC register ------------------------------------
typedef struct {
    uint32_t                                r2_reg_txgain_mem_type               :2 ;
    uint32_t                                reserved0                            :30;
}   PHY_AH_RFAFE_INT_59;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_59                     b;
}   PHY_AH_RFAFE_INT_59_U;


// 0x4008E0F0 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_txgain_lut_wr_enable           :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_RFAFE_INT_60;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_60                     b;
}   PHY_AH_RFAFE_INT_60_U;


// 0x4008E0F4 register ------------------------------------
typedef struct {
    uint32_t                                r7_reg_txgain_lut_wr_addr            :7 ;
    uint32_t                                reserved0                            :25;
}   PHY_AH_RFAFE_INT_61;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_61                     b;
}   PHY_AH_RFAFE_INT_61_U;


// 0x4008E0F8 register ------------------------------------
typedef struct {
    uint32_t                                r24_reg_txgain_lut_wr_data           :24;
    uint32_t                                reserved0                            :8 ;
}   PHY_AH_RFAFE_INT_62;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_62                     b;
}   PHY_AH_RFAFE_INT_62_U;


// 0x4008E0FC register ------------------------------------
typedef struct {
    uint32_t                                r4_reg_txgain_lut_wr_vga             :4 ;
    uint32_t                                reserved0                            :28;
}   PHY_AH_RFAFE_INT_63;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_63                     b;
}   PHY_AH_RFAFE_INT_63_U;


// 0x4008E100 register ------------------------------------
typedef struct {
    uint32_t                                r3_reg_txgain_lut_wr_mixer           :4 ;
    uint32_t                                reserved0                            :28;
}   PHY_AH_RFAFE_INT_64;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_64                     b;
}   PHY_AH_RFAFE_INT_64_U;


// 0x4008E104 register ------------------------------------
typedef struct {
    uint32_t                                r3_reg_txgain_lut_wr_pa_dr           :4 ;
    uint32_t                                reserved0                            :28;
}   PHY_AH_RFAFE_INT_65;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_65                     b;
}   PHY_AH_RFAFE_INT_65_U;


// 0x4008E108 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_hw_spi_mem_type                :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_RFAFE_INT_66;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_66                     b;
}   PHY_AH_RFAFE_INT_66_U;


// 0x4008E10C register ------------------------------------
typedef struct {
    uint32_t                                r_reg_hw_spi_lut_wr_enable           :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_RFAFE_INT_67;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_67                     b;
}   PHY_AH_RFAFE_INT_67_U;


// 0x4008E110 register ------------------------------------
typedef struct {
    uint32_t                                r7_reg_hw_spi_lut_wr_addr            :7 ;
    uint32_t                                reserved0                            :25;
}   PHY_AH_RFAFE_INT_68;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_68                     b;
}   PHY_AH_RFAFE_INT_68_U;


// 0x4008E114 register ------------------------------------
typedef struct {
    uint32_t                                r24_reg_hw_spi_lut_wr_data           :24;
    uint32_t                                reserved0                            :8 ;
}   PHY_AH_RFAFE_INT_69;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_69                     b;
}   PHY_AH_RFAFE_INT_69_U;


// 0x4008E118 register ------------------------------------
typedef struct {
    uint32_t                                r7_reg_prf_reg_num                   :7 ;
    uint32_t                                reserved0                            :25;
}   PHY_AH_RFAFE_INT_70;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_70                     b;
}   PHY_AH_RFAFE_INT_70_U;


// 0x4008E11C register ------------------------------------
typedef struct {
    uint32_t                                r7_reg_rf_ctl_toggle                 :7 ;
    uint32_t                                reserved0                            :25;
}   PHY_AH_RFAFE_INT_71;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_71                     b;
}   PHY_AH_RFAFE_INT_71_U;


// 0x4008E120 register ------------------------------------
typedef struct {
    uint32_t                                r7_reg_rf_ctl_low                    :7 ;
    uint32_t                                reserved0                            :25;
}   PHY_AH_RFAFE_INT_72;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_72                     b;
}   PHY_AH_RFAFE_INT_72_U;


// 0x4008E124 register ------------------------------------
typedef struct {
    uint32_t                                r2_reg_ext_lna_load_delay            :2 ;
    uint32_t                                reserved0                            :30;
}   PHY_AH_RFAFE_INT_73;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_73                     b;
}   PHY_AH_RFAFE_INT_73_U;


// 0x4008E128 register ------------------------------------
typedef struct {
    uint32_t                                r7_reg_rxen_delay                    :7 ;
    uint32_t                                reserved0                            :25;
}   PHY_AH_RFAFE_INT_74;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_74                     b;
}   PHY_AH_RFAFE_INT_74_U;


// 0x4008E12C register ------------------------------------
typedef struct {
    uint32_t                                r7_reg_antsel_delay                  :7 ;
    uint32_t                                reserved0                            :25;
}   PHY_AH_RFAFE_INT_75;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_75                     b;
}   PHY_AH_RFAFE_INT_75_U;


// 0x4008E130 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_txen_sel                       :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_RFAFE_INT_76;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_76                     b;
}   PHY_AH_RFAFE_INT_76_U;


// 0x4008E134 register ------------------------------------
typedef struct {
    uint32_t                                r_reg_txpwr_sel                      :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_RFAFE_INT_77;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_77                     b;
}   PHY_AH_RFAFE_INT_77_U;


// 0x4008E138 register ------------------------------------
typedef struct {
    uint32_t                                r2_reg_loiqcal_txiq_para_sel         :2 ;
    uint32_t                                reserved0                            :30;
}   PHY_AH_RFAFE_INT_78;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_78                     b;
}   PHY_AH_RFAFE_INT_78_U;


// 0x4008E13C register ------------------------------------
typedef struct {
    uint32_t                                r_reg_loiqcal_txiq_mode_sel          :1 ;
    uint32_t                                reserved0                            :31;
}   PHY_AH_RFAFE_INT_79;

typedef union {
    uint32_t                                w;
    PHY_AH_RFAFE_INT_79                     b;
}   PHY_AH_RFAFE_INT_79_U;


//---------------------------------------------------------
// PHY Register Map
//---------------------------------------------------------
typedef struct {
    volatile PHY_PHY_TOP_STATE00_U                          PHY_TOP_STATE00                        ; // 0x000
    volatile PHY_PHY_TOP_STATE01_U                          PHY_TOP_STATE01                        ; // 0x004
    volatile PHY_PHY_TOP_STATE02_U                          PHY_TOP_STATE02                        ; // 0x008
    volatile PHY_PHY_TOP_STATE03_U                          PHY_TOP_STATE03                        ; // 0x00c
    volatile uint32_t                                          RESERVED0[124]                         ; // 
    volatile PHY_TX_PPDU_STATE00_U                          TX_PPDU_STATE00                        ; // 0x200
    volatile PHY_TX_PPDU_STATE01_U                          TX_PPDU_STATE01                        ; // 0x204
    volatile PHY_TX_PPDU_STATE02_U                          TX_PPDU_STATE02                        ; // 0x208
    volatile PHY_TX_PPDU_STATE03_U                          TX_PPDU_STATE03                        ; // 0x20c
    volatile PHY_TX_PPDU_STATE04_U                          TX_PPDU_STATE04                        ; // 0x210
    volatile PHY_TX_PPDU_STATE05_U                          TX_PPDU_STATE05                        ; // 0x214
    volatile PHY_TX_PPDU_STATE06_U                          TX_PPDU_STATE06                        ; // 0x218
    volatile PHY_TX_PPDU_STATE07_U                          TX_PPDU_STATE07                        ; // 0x21c
    volatile PHY_TX_PPDU_STATE08_U                          TX_PPDU_STATE08                        ; // 0x220
    volatile uint32_t                                          RESERVED1[119]                         ; // 
    volatile PHY_RX_PPDU_STATE00_U                          RX_PPDU_STATE00                        ; // 0x400
    volatile PHY_RX_PPDU_STATE01_U                          RX_PPDU_STATE01                        ; // 0x404
    volatile PHY_RX_PPDU_STATE02_U                          RX_PPDU_STATE02                        ; // 0x408
    volatile PHY_RX_PPDU_STATE03_U                          RX_PPDU_STATE03                        ; // 0x40c
    volatile PHY_RX_PPDU_STATE04_U                          RX_PPDU_STATE04                        ; // 0x410
    volatile PHY_RX_PPDU_STATE05_U                          RX_PPDU_STATE05                        ; // 0x414
    volatile PHY_RX_PPDU_STATE06_U                          RX_PPDU_STATE06                        ; // 0x418
    volatile PHY_RX_PPDU_STATE07_U                          RX_PPDU_STATE07                        ; // 0x41c
    volatile PHY_RX_PPDU_STATE08_U                          RX_PPDU_STATE08                        ; // 0x420
    volatile PHY_RX_PPDU_STATE09_U                          RX_PPDU_STATE09                        ; // 0x424
    volatile PHY_RX_PPDU_STATE10_U                          RX_PPDU_STATE10                        ; // 0x428
    volatile PHY_RX_PPDU_STATE11_U                          RX_PPDU_STATE11                        ; // 0x42c
    volatile PHY_RX_PPDU_STATE12_U                          RX_PPDU_STATE12                        ; // 0x430
    volatile uint32_t                                          RESERVED2                              ; // 
    volatile PHY_RX_PPDU_STATE14_U                          RX_PPDU_STATE14                        ; // 0x438
    volatile PHY_RX_PPDU_STATE15_U                          RX_PPDU_STATE15                        ; // 0x43c
    volatile PHY_RX_PPDU_STATE16_U                          RX_PPDU_STATE16                        ; // 0x440
    volatile uint32_t                                          RESERVED3[111]                         ; // 
    volatile PHY_PHY_TEST_MD00_U                            PHY_TEST_MD00                          ; // 0x600
    volatile PHY_PHY_TEST_MD01_U                            PHY_TEST_MD01                          ; // 0x604
    volatile PHY_PHY_TEST_MD02_U                            PHY_TEST_MD02                          ; // 0x608
    volatile PHY_PHY_TEST_MD03_U                            PHY_TEST_MD03                          ; // 0x60c
    volatile PHY_PHY_TEST_MD04_U                            PHY_TEST_MD04                          ; // 0x610
    volatile PHY_PHY_TEST_MD05_U                            PHY_TEST_MD05                          ; // 0x614
    volatile uint32_t                                          RESERVED4[6]                           ; // 
    volatile PHY_PHY_SIM_TRX_MD_U                           PHY_SIM_TRX_MD                         ; // 0x630
    volatile uint32_t                                          RESERVED5[115]                         ; // 
    volatile PHY_PHY_RXDBE00_U                              PHY_RXDBE00                            ; // 0x800
    volatile PHY_PHY_RXDBE01_U                              PHY_RXDBE01                            ; // 0x804
    volatile uint32_t                                          RESERVED6[510]                         ; // 
    volatile PHY_PHY_TOPIF_CLK_GEN0_U                       PHY_TOPIF_CLK_GEN0                     ; // 0x1000
    volatile PHY_PHY_TOPIF_CLK_GEN1_U                       PHY_TOPIF_CLK_GEN1                     ; // 0x1004
    volatile PHY_PHY_TOPIF_CLK_GEN2_U                       PHY_TOPIF_CLK_GEN2                     ; // 0x1008
    volatile PHY_PHY_TOPIF_CLK_GEN3_U                       PHY_TOPIF_CLK_GEN3                     ; // 0x100c
    volatile PHY_PHY_TOPIF_CLK_GEN4_U                       PHY_TOPIF_CLK_GEN4                     ; // 0x1010
    volatile PHY_PHY_TOPIF_CLK_GEN5_U                       PHY_TOPIF_CLK_GEN5                     ; // 0x1014
    volatile uint32_t                                          RESERVED7[58]                          ; // 
    volatile PHY_PHY_TOPIF_TXFIFO0_U                        PHY_TOPIF_TXFIFO0                      ; // 0x1100
    volatile PHY_PHY_TOPIF_TXFIFO1_U                        PHY_TOPIF_TXFIFO1                      ; // 0x1104
    volatile PHY_PHY_TOPIF_TXFIFO2_U                        PHY_TOPIF_TXFIFO2                      ; // 0x1108
    volatile PHY_PHY_TOPIF_TXFIFO3_U                        PHY_TOPIF_TXFIFO3                      ; // 0x110c
    volatile PHY_PHY_TOPIF_TXFIFO4_U                        PHY_TOPIF_TXFIFO4                      ; // 0x1110
    volatile uint32_t                                          RESERVED8[23]                          ; // 
    volatile PHY_PHY_TOPIF_LOOPBACK_U                       PHY_TOPIF_LOOPBACK                     ; // 0x1170
    volatile uint32_t                                          RESERVED9[3]                           ; // 
    volatile PHY_PHY_TOPIF_CONFIG0_U                        PHY_TOPIF_CONFIG0                      ; // 0x1180
    volatile uint32_t                                          RESERVED10[7]                          ; // 
    volatile PHY_PHY_TOPIF_RFCTRL_U                         PHY_TOPIF_RFCTRL                       ; // 0x11a0
    volatile uint32_t                                          RESERVED11[3]                          ; // 
    volatile PHY_PHY_TOPIF_VMACCFG0_U                       PHY_TOPIF_VMACCFG0                     ; // 0x11b0
    volatile PHY_PHY_TOPIF_VMACCFG1_U                       PHY_TOPIF_VMACCFG1                     ; // 0x11b4
    volatile PHY_PHY_TOPIF_VMACCFG2_U                       PHY_TOPIF_VMACCFG2                     ; // 0x11b8
    volatile PHY_PHY_TOPIF_VMACCFG3_U                       PHY_TOPIF_VMACCFG3                     ; // 0x11bc
    volatile PHY_PHY_TOPIF_VMACCFG4_U                       PHY_TOPIF_VMACCFG4                     ; // 0x11c0
    volatile PHY_PHY_TOPIF_VMACCFG5_U                       PHY_TOPIF_VMACCFG5                     ; // 0x11c4
    volatile PHY_PHY_TOPIF_VMACCFG6_U                       PHY_TOPIF_VMACCFG6                     ; // 0x11c8
    volatile PHY_PHY_TOPIF_VMACCFG7_U                       PHY_TOPIF_VMACCFG7                     ; // 0x11cc
    volatile PHY_PHY_TOPIF_VMACCFG8_U                       PHY_TOPIF_VMACCFG8                     ; // 0x11d0
    volatile PHY_PHY_TOPIF_VMACCFG9_U                       PHY_TOPIF_VMACCFG9                     ; // 0x11d4
    volatile PHY_PHY_TOPIF_VMACCFG10_U                      PHY_TOPIF_VMACCFG10                    ; // 0x11d8
    volatile PHY_PHY_TOPIF_VMACCFG11_U                      PHY_TOPIF_VMACCFG11                    ; // 0x11dc
    volatile PHY_PHY_TOPIF_VMACCFG12_U                      PHY_TOPIF_VMACCFG12                    ; // 0x11e0
    volatile PHY_PHY_TOPIF_VMACCFG13_U                      PHY_TOPIF_VMACCFG13                    ; // 0x11e4
    volatile uint32_t                                          RESERVED12[902]                        ; // 
    volatile PHY_AH_TX_DFE_LPF00_U                          AH_TX_DFE_LPF00                        ; // 0x2000
    volatile PHY_AH_TX_DFE_LPF01_U                          AH_TX_DFE_LPF01                        ; // 0x2004
    volatile PHY_AH_TX_DFE_LPF02_U                          AH_TX_DFE_LPF02                        ; // 0x2008
    volatile uint32_t                                          RESERVED13                             ; // 
    volatile PHY_AH_TX_DFE_LPF04_U                          AH_TX_DFE_LPF04                        ; // 0x2010
    volatile PHY_AH_TX_DFE_LPF05_U                          AH_TX_DFE_LPF05                        ; // 0x2014
    volatile PHY_AH_TX_DFE_LPF06_U                          AH_TX_DFE_LPF06                        ; // 0x2018
    volatile PHY_AH_TX_DFE_LPF07_U                          AH_TX_DFE_LPF07                        ; // 0x201c
    volatile PHY_AH_TX_DFE_LPF08_U                          AH_TX_DFE_LPF08                        ; // 0x2020
    volatile PHY_AH_TX_DFE_LPF09_U                          AH_TX_DFE_LPF09                        ; // 0x2024
    volatile PHY_AH_TX_DFE_LPF10_U                          AH_TX_DFE_LPF10                        ; // 0x2028
    volatile PHY_AH_TX_DFE_LPF11_U                          AH_TX_DFE_LPF11                        ; // 0x202c
    volatile PHY_AH_TX_DFE_LPF12_U                          AH_TX_DFE_LPF12                        ; // 0x2030
    volatile PHY_AH_TX_DFE_LPF13_U                          AH_TX_DFE_LPF13                        ; // 0x2034
    volatile PHY_AH_TX_DFE_LPF14_U                          AH_TX_DFE_LPF14                        ; // 0x2038
    volatile PHY_AH_TX_DFE_LPF15_U                          AH_TX_DFE_LPF15                        ; // 0x203c
    volatile PHY_AH_TX_DFE_LPF16_U                          AH_TX_DFE_LPF16                        ; // 0x2040
    volatile uint32_t                                          RESERVED14[239]                        ; // 
    volatile PHY_AH_TX_DFE_CAL00_U                          AH_TX_DFE_CAL00                        ; // 0x2400
    volatile PHY_AH_TX_DFE_CAL01_U                          AH_TX_DFE_CAL01                        ; // 0x2404
    volatile PHY_AH_TX_DFE_CAL02_U                          AH_TX_DFE_CAL02                        ; // 0x2408
    volatile PHY_AH_TX_DFE_CAL03_U                          AH_TX_DFE_CAL03                        ; // 0x240c
    volatile PHY_AH_TX_DFE_CAL04_U                          AH_TX_DFE_CAL04                        ; // 0x2410
    volatile uint32_t                                          RESERVED15[1531]                       ; // 
    volatile PHY_PHY_TXSBR00_U                              PHY_TXSBR00                            ; // 0x3c00
    volatile PHY_PHY_TXSBR01_U                              PHY_TXSBR01                            ; // 0x3c04
    volatile PHY_PHY_TXSBR02_U                              PHY_TXSBR02                            ; // 0x3c08
    volatile PHY_PHY_TXSBR03_U                              PHY_TXSBR03                            ; // 0x3c0c
    volatile PHY_PHY_TXSBR04_U                              PHY_TXSBR04                            ; // 0x3c10
    volatile PHY_PHY_TXSBR05_U                              PHY_TXSBR05                            ; // 0x3c14
    volatile uint32_t                                          RESERVED16[250]                        ; // 
    volatile PHY_RX_DFE00_U                                 RX_DFE00                               ; // 0x4000
    volatile PHY_RX_DFE01_U                                 RX_DFE01                               ; // 0x4004
    volatile PHY_RX_DFE02_U                                 RX_DFE02                               ; // 0x4008
    volatile PHY_RX_DFE03_U                                 RX_DFE03                               ; // 0x400c
    volatile PHY_RX_DFE04_U                                 RX_DFE04                               ; // 0x4010
    volatile uint32_t                                          RESERVED17[2]                          ; // 
    volatile PHY_RX_DFE07_U                                 RX_DFE07                               ; // 0x401c
    volatile PHY_RX_DFE08_U                                 RX_DFE08                               ; // 0x4020
    volatile PHY_RX_DFE09_U                                 RX_DFE09                               ; // 0x4024
    volatile PHY_RX_DFE10_U                                 RX_DFE10                               ; // 0x4028
    volatile PHY_RX_DFE11_U                                 RX_DFE11                               ; // 0x402c
    volatile PHY_RX_DFE12_U                                 RX_DFE12                               ; // 0x4030
    volatile PHY_RX_DFE13_U                                 RX_DFE13                               ; // 0x4034
    volatile PHY_RX_DFE14_U                                 RX_DFE14                               ; // 0x4038
    volatile PHY_RX_DFE15_U                                 RX_DFE15                               ; // 0x403c
    volatile PHY_RX_DFE16_U                                 RX_DFE16                               ; // 0x4040
    volatile PHY_RX_DFE17_U                                 RX_DFE17                               ; // 0x4044
    volatile PHY_RX_DFE18_U                                 RX_DFE18                               ; // 0x4048
    volatile PHY_RX_DFE19_U                                 RX_DFE19                               ; // 0x404c
    volatile uint32_t                                          RESERVED18[8]                          ; // 
    volatile PHY_RX_DFE_TIMER00_U                           RX_DFE_TIMER00                         ; // 0x4070
    volatile uint32_t                                          RESERVED19[2]                          ; // 
    volatile PHY_RX_DFE_TIMER03_U                           RX_DFE_TIMER03                         ; // 0x407c
    volatile uint32_t                                          RESERVED20[8]                          ; // 
    volatile PHY_RX_DFE_TIMER12_U                           RX_DFE_TIMER12                         ; // 0x40a0
    volatile uint32_t                                          RESERVED21[3]                          ; // 
    volatile PHY_RX_DFE_LOG_CFG_U                           RX_DFE_LOG_CFG                         ; // 0x40b0
    volatile PHY_RX_DFE_LOG00_U                             RX_DFE_LOG00                           ; // 0x40b4
    volatile PHY_RX_DFE_LOG01_U                             RX_DFE_LOG01                           ; // 0x40b8
    volatile PHY_RX_DFE_LOG02_U                             RX_DFE_LOG02                           ; // 0x40bc
    volatile PHY_RX_DFE_LOG03_U                             RX_DFE_LOG03                           ; // 0x40c0
    volatile PHY_RX_DFE_LOG04_U                             RX_DFE_LOG04                           ; // 0x40c4
    volatile PHY_RX_DFE_LOG05_U                             RX_DFE_LOG05                           ; // 0x40c8
    volatile PHY_RX_DFE_LOG06_U                             RX_DFE_LOG06                           ; // 0x40cc
    volatile PHY_RX_DFE_LOG07_U                             RX_DFE_LOG07                           ; // 0x40d0
    volatile PHY_RX_DFE_LOG08_U                             RX_DFE_LOG08                           ; // 0x40d4
    volatile PHY_RX_DFE_LOG09_U                             RX_DFE_LOG09                           ; // 0x40d8
    volatile PHY_RX_DFE_LOG10_U                             RX_DFE_LOG10                           ; // 0x40dc
    volatile PHY_RX_DFE_LOG11_U                             RX_DFE_LOG11                           ; // 0x40e0
    volatile PHY_RX_DFE_LOG12_U                             RX_DFE_LOG12                           ; // 0x40e4
    volatile PHY_RX_DFE_LOG13_U                             RX_DFE_LOG13                           ; // 0x40e8
    volatile PHY_RX_DFE_LOG14_U                             RX_DFE_LOG14                           ; // 0x40ec
    volatile PHY_RX_DFE_LOG15_U                             RX_DFE_LOG15                           ; // 0x40f0
    volatile PHY_RX_DFE_LOG16_U                             RX_DFE_LOG16                           ; // 0x40f4
    volatile PHY_RX_DFE_LOG17_U                             RX_DFE_LOG17                           ; // 0x40f8
    volatile PHY_RX_DFE_LOG18_U                             RX_DFE_LOG18                           ; // 0x40fc
    volatile PHY_RX_DFE_LOG19_U                             RX_DFE_LOG19                           ; // 0x4100
    volatile PHY_RX_DFE_LOG20_U                             RX_DFE_LOG20                           ; // 0x4104
    volatile PHY_RX_DFE_LOG21_U                             RX_DFE_LOG21                           ; // 0x4108
    volatile PHY_RX_DFE_LOG22_U                             RX_DFE_LOG22                           ; // 0x410c
    volatile PHY_RX_DFE_LOG23_U                             RX_DFE_LOG23                           ; // 0x4110
    volatile PHY_RX_DFE_LOG24_U                             RX_DFE_LOG24                           ; // 0x4114
    volatile PHY_RX_DFE_LOG25_U                             RX_DFE_LOG25                           ; // 0x4118
    volatile PHY_RX_DFE_LOG26_U                             RX_DFE_LOG26                           ; // 0x411c
    volatile PHY_RX_DFE_LOG27_U                             RX_DFE_LOG27                           ; // 0x4120
    volatile PHY_RX_DFE_LOG28_U                             RX_DFE_LOG28                           ; // 0x4124
    volatile PHY_RX_DFE_LOG29_U                             RX_DFE_LOG29                           ; // 0x4128
    volatile PHY_RX_DFE_LOG30_U                             RX_DFE_LOG30                           ; // 0x412c
    volatile PHY_RX_DFE_LOG31_U                             RX_DFE_LOG31                           ; // 0x4130
    volatile PHY_RX_DFE_LOG32_U                             RX_DFE_LOG32                           ; // 0x4134
    volatile PHY_RX_DFE_LOG33_U                             RX_DFE_LOG33                           ; // 0x4138
    volatile PHY_RX_DFE_LOG34_U                             RX_DFE_LOG34                           ; // 0x413c
    volatile PHY_RX_DFE_LOG35_U                             RX_DFE_LOG35                           ; // 0x4140
    volatile PHY_RX_DFE_LOG36_U                             RX_DFE_LOG36                           ; // 0x4144
    volatile PHY_RX_DFE_LOG37_U                             RX_DFE_LOG37                           ; // 0x4148
    volatile PHY_RX_DFE_LOG38_U                             RX_DFE_LOG38                           ; // 0x414c
    volatile PHY_RX_DFE_LOG39_U                             RX_DFE_LOG39                           ; // 0x4150
    volatile uint32_t                                          RESERVED22[171]                        ; // 
    volatile PHY_AHA1_RXDFE_AGC_00_U                        AHA1_RXDFE_AGC_00                      ; // 0x4400
    volatile PHY_AHA1_RXDFE_AGC_01_U                        AHA1_RXDFE_AGC_01                      ; // 0x4404
    volatile PHY_AHA1_RXDFE_AGC_02_U                        AHA1_RXDFE_AGC_02                      ; // 0x4408
    volatile PHY_AHA1_RXDFE_AGC_03_U                        AHA1_RXDFE_AGC_03                      ; // 0x440c
    volatile PHY_AHA1_RXDFE_AGC_04_U                        AHA1_RXDFE_AGC_04                      ; // 0x4410
    volatile PHY_AHA1_RXDFE_AGC_05_U                        AHA1_RXDFE_AGC_05                      ; // 0x4414
    volatile PHY_AHA1_RXDFE_AGC_06_U                        AHA1_RXDFE_AGC_06                      ; // 0x4418
    volatile PHY_AHA1_RXDFE_AGC_07_U                        AHA1_RXDFE_AGC_07                      ; // 0x441c
    volatile PHY_AHA1_RXDFE_AGC_08_U                        AHA1_RXDFE_AGC_08                      ; // 0x4420
    volatile PHY_AHA1_RXDFE_AGC_09_U                        AHA1_RXDFE_AGC_09                      ; // 0x4424
    volatile PHY_AHA1_RXDFE_AGC_10_U                        AHA1_RXDFE_AGC_10                      ; // 0x4428
    volatile PHY_AHA1_RXDFE_AGC_11_U                        AHA1_RXDFE_AGC_11                      ; // 0x442c
    volatile PHY_AHA1_RXDFE_AGC_12_U                        AHA1_RXDFE_AGC_12                      ; // 0x4430
    volatile PHY_AHA1_RXDFE_AGC_13_U                        AHA1_RXDFE_AGC_13                      ; // 0x4434
    volatile PHY_AHA1_RXDFE_AGC_14_U                        AHA1_RXDFE_AGC_14                      ; // 0x4438
    volatile PHY_AHA1_RXDFE_AGC_15_U                        AHA1_RXDFE_AGC_15                      ; // 0x443c
    volatile PHY_AHA1_RXDFE_AGC_16_U                        AHA1_RXDFE_AGC_16                      ; // 0x4440
    volatile PHY_AHA1_RXDFE_AGC_17_U                        AHA1_RXDFE_AGC_17                      ; // 0x4444
    volatile PHY_AHA1_RXDFE_AGC_18_U                        AHA1_RXDFE_AGC_18                      ; // 0x4448
    volatile PHY_AHA1_RXDFE_AGC_19_U                        AHA1_RXDFE_AGC_19                      ; // 0x444c
    volatile PHY_AHA1_RXDFE_AGC_20_U                        AHA1_RXDFE_AGC_20                      ; // 0x4450
    volatile PHY_AHA1_RXDFE_AGC_21_U                        AHA1_RXDFE_AGC_21                      ; // 0x4454
    volatile PHY_AHA1_RXDFE_AGC_22_U                        AHA1_RXDFE_AGC_22                      ; // 0x4458
    volatile PHY_AHA1_RXDFE_AGC_23_U                        AHA1_RXDFE_AGC_23                      ; // 0x445c
    volatile PHY_AHA1_RXDFE_AGC_24_U                        AHA1_RXDFE_AGC_24                      ; // 0x4460
    volatile PHY_AHA1_RXDFE_AGC_25_U                        AHA1_RXDFE_AGC_25                      ; // 0x4464
    volatile PHY_AHA1_RXDFE_AGC_26_U                        AHA1_RXDFE_AGC_26                      ; // 0x4468
    volatile PHY_AHA1_RXDFE_AGC_27_U                        AHA1_RXDFE_AGC_27                      ; // 0x446c
    volatile PHY_AHA1_RXDFE_AGC_28_U                        AHA1_RXDFE_AGC_28                      ; // 0x4470
    volatile PHY_AHA1_RXDFE_AGC_29_U                        AHA1_RXDFE_AGC_29                      ; // 0x4474
    volatile PHY_AHA1_RXDFE_AGC_30_U                        AHA1_RXDFE_AGC_30                      ; // 0x4478
    volatile PHY_AHA1_RXDFE_AGC_31_U                        AHA1_RXDFE_AGC_31                      ; // 0x447c
    volatile PHY_AHA1_RXDFE_AGC_32_U                        AHA1_RXDFE_AGC_32                      ; // 0x4480
    volatile PHY_AHA1_RXDFE_AGC_33_U                        AHA1_RXDFE_AGC_33                      ; // 0x4484
    volatile PHY_AHA1_RXDFE_AGC_34_U                        AHA1_RXDFE_AGC_34                      ; // 0x4488
    volatile PHY_AHA1_RXDFE_AGC_35_U                        AHA1_RXDFE_AGC_35                      ; // 0x448c
    volatile PHY_AHA1_RXDFE_AGC_36_U                        AHA1_RXDFE_AGC_36                      ; // 0x4490
    volatile PHY_AHA1_RXDFE_AGC_37_U                        AHA1_RXDFE_AGC_37                      ; // 0x4494
    volatile PHY_AHA1_RXDFE_AGC_38_U                        AHA1_RXDFE_AGC_38                      ; // 0x4498
    volatile PHY_AHA1_RXDFE_AGC_39_U                        AHA1_RXDFE_AGC_39                      ; // 0x449c
    volatile PHY_AHA1_RXDFE_AGC_40_U                        AHA1_RXDFE_AGC_40                      ; // 0x44a0
    volatile PHY_AHA1_RXDFE_AGC_41_U                        AHA1_RXDFE_AGC_41                      ; // 0x44a4
    volatile PHY_AHA1_RXDFE_AGC_42_U                        AHA1_RXDFE_AGC_42                      ; // 0x44a8
    volatile PHY_AHA1_RXDFE_AGC_43_U                        AHA1_RXDFE_AGC_43                      ; // 0x44ac
    volatile PHY_AHA1_RXDFE_AGC_44_U                        AHA1_RXDFE_AGC_44                      ; // 0x44b0
    volatile PHY_AHA1_RXDFE_AGC_45_U                        AHA1_RXDFE_AGC_45                      ; // 0x44b4
    volatile PHY_AHA1_RXDFE_AGC_46_U                        AHA1_RXDFE_AGC_46                      ; // 0x44b8
    volatile PHY_AHA1_RXDFE_AGC_47_U                        AHA1_RXDFE_AGC_47                      ; // 0x44bc
    volatile PHY_AHA1_RXDFE_AGC_48_U                        AHA1_RXDFE_AGC_48                      ; // 0x44c0
    volatile PHY_AHA1_RXDFE_AGC_49_U                        AHA1_RXDFE_AGC_49                      ; // 0x44c4
    volatile PHY_AHA1_RXDFE_AGC_50_U                        AHA1_RXDFE_AGC_50                      ; // 0x44c8
    volatile PHY_AHA1_RXDFE_AGC_51_U                        AHA1_RXDFE_AGC_51                      ; // 0x44cc
    volatile PHY_AHA1_RXDFE_AGC_52_U                        AHA1_RXDFE_AGC_52                      ; // 0x44d0
    volatile PHY_AHA1_RXDFE_AGC_53_U                        AHA1_RXDFE_AGC_53                      ; // 0x44d4
    volatile PHY_AHA1_RXDFE_AGC_54_U                        AHA1_RXDFE_AGC_54                      ; // 0x44d8
    volatile PHY_AHA1_RXDFE_AGC_55_U                        AHA1_RXDFE_AGC_55                      ; // 0x44dc
    volatile PHY_AHA1_RXDFE_AGC_56_U                        AHA1_RXDFE_AGC_56                      ; // 0x44e0
    volatile PHY_AHA1_RXDFE_AGC_57_U                        AHA1_RXDFE_AGC_57                      ; // 0x44e4
    volatile PHY_AHA1_RXDFE_AGC_58_U                        AHA1_RXDFE_AGC_58                      ; // 0x44e8
    volatile PHY_AHA1_RXDFE_AGC_59_U                        AHA1_RXDFE_AGC_59                      ; // 0x44ec
    volatile PHY_AHA1_RXDFE_AGC_60_U                        AHA1_RXDFE_AGC_60                      ; // 0x44f0
    volatile PHY_AHA1_RXDFE_AGC_61_U                        AHA1_RXDFE_AGC_61                      ; // 0x44f4
    volatile PHY_AHA1_RXDFE_AGC_62_U                        AHA1_RXDFE_AGC_62                      ; // 0x44f8
    volatile PHY_AHA1_RXDFE_AGC_63_U                        AHA1_RXDFE_AGC_63                      ; // 0x44fc
    volatile PHY_AHA1_RXDFE_AGC_64_U                        AHA1_RXDFE_AGC_64                      ; // 0x4500
    volatile PHY_AHA1_RXDFE_AGC_65_U                        AHA1_RXDFE_AGC_65                      ; // 0x4504
    volatile PHY_AHA1_RXDFE_AGC_66_U                        AHA1_RXDFE_AGC_66                      ; // 0x4508
    volatile PHY_AHA1_RXDFE_AGC_67_U                        AHA1_RXDFE_AGC_67                      ; // 0x450c
    volatile PHY_AHA1_RXDFE_AGC_68_U                        AHA1_RXDFE_AGC_68                      ; // 0x4510
    volatile PHY_AHA1_RXDFE_AGC_69_U                        AHA1_RXDFE_AGC_69                      ; // 0x4514
    volatile PHY_AHA1_RXDFE_AGC_70_U                        AHA1_RXDFE_AGC_70                      ; // 0x4518
    volatile PHY_AHA1_RXDFE_AGC_71_U                        AHA1_RXDFE_AGC_71                      ; // 0x451c
    volatile PHY_AHA1_RXDFE_AGC_72_U                        AHA1_RXDFE_AGC_72                      ; // 0x4520
    volatile uint32_t                                          RESERVED23[183]                        ; // 
    volatile PHY_AHA1_RXDFE_LPF_00_U                        AHA1_RXDFE_LPF_00                      ; // 0x4800
    volatile PHY_AHA1_RXDFE_LPF_01_U                        AHA1_RXDFE_LPF_01                      ; // 0x4804
    volatile PHY_AHA1_RXDFE_LPF_02_U                        AHA1_RXDFE_LPF_02                      ; // 0x4808
    volatile PHY_AHA1_RXDFE_LPF_03_U                        AHA1_RXDFE_LPF_03                      ; // 0x480c
    volatile PHY_AHA1_RXDFE_LPF_04_U                        AHA1_RXDFE_LPF_04                      ; // 0x4810
    volatile uint32_t                                          RESERVED24[251]                        ; // 
    volatile PHY_AH_RX_SYNC_1MTHRE_U                        AH_RX_SYNC_1MTHRE                      ; // 0x4c00
    volatile PHY_AH_RX_SYNC_1MSTF1_U                        AH_RX_SYNC_1MSTF1                      ; // 0x4c04
    volatile PHY_AH_RX_SYNC_1MSTF2_U                        AH_RX_SYNC_1MSTF2                      ; // 0x4c08
    volatile PHY_AH_RX_SYNC_1MFSYNC_U                       AH_RX_SYNC_1MFSYNC                     ; // 0x4c0c
    volatile PHY_AH_RX_SYNC_1MCFO1_U                        AH_RX_SYNC_1MCFO1                      ; // 0x4c10
    volatile PHY_AH_RX_SYNC_1MCFO2_U                        AH_RX_SYNC_1MCFO2                      ; // 0x4c14
    volatile PHY_AH_RX_SYNC_1MCTRL_U                        AH_RX_SYNC_1MCTRL                      ; // 0x4c18
    volatile uint32_t                                          RESERVED25                             ; // 
    volatile PHY_AH_RX_SYNC_2MTHRE_U                        AH_RX_SYNC_2MTHRE                      ; // 0x4c20
    volatile PHY_AH_RX_SYNC_2MSTF_U                         AH_RX_SYNC_2MSTF                       ; // 0x4c24
    volatile PHY_AH_RX_SYNC_2MFSYNC_U                       AH_RX_SYNC_2MFSYNC                     ; // 0x4c28
    volatile PHY_AH_RX_SYNC_2MCFO_U                         AH_RX_SYNC_2MCFO                       ; // 0x4c2c
    volatile PHY_AH_RX_SYNC_CFOERR_U                        AH_RX_SYNC_CFOERR                      ; // 0x4c30
    volatile PHY_AH_RX_SYNC_FLTDLY1M_U                      AH_RX_SYNC_FLTDLY1M                    ; // 0x4c34
    volatile PHY_AH_RX_SYNC_FLTDLY2M_U                      AH_RX_SYNC_FLTDLY2M                    ; // 0x4c38
    volatile PHY_AH_RX_SYNC_XCORRMIN_U                      AH_RX_SYNC_XCORRMIN                    ; // 0x4c3c
    volatile PHY_AH_RX_SYNC_FSYNCD_U                        AH_RX_SYNC_FSYNCD                      ; // 0x4c40
    volatile PHY_AH_RX_SYNC_SNRESTD_U                       AH_RX_SYNC_SNRESTD                     ; // 0x4c44
    volatile uint32_t                                          RESERVED26[238]                        ; // 
    volatile PHY_AH_PHTRK_EST_00_U                          AH_PHTRK_EST_00                        ; // 0x5000
    volatile PHY_AH_PHTRK_EST_01_U                          AH_PHTRK_EST_01                        ; // 0x5004
    volatile PHY_AH_PHTRK_EST_02_U                          AH_PHTRK_EST_02                        ; // 0x5008
    volatile PHY_AH_PHTRK_EST_03_U                          AH_PHTRK_EST_03                        ; // 0x500c
    volatile uint32_t                                          RESERVED27[252]                        ; // 
    volatile PHY_AH_RX_CS00_U                               AH_RX_CS00                             ; // 0x5400
    volatile PHY_AH_RX_CS01_U                               AH_RX_CS01                             ; // 0x5404
    volatile PHY_AH_RX_CS02_U                               AH_RX_CS02                             ; // 0x5408
    volatile PHY_AH_RX_CS03_U                               AH_RX_CS03                             ; // 0x540c
    volatile PHY_AH_RX_CS04_U                               AH_RX_CS04                             ; // 0x5410
    volatile PHY_AH_RX_CS05_U                               AH_RX_CS05                             ; // 0x5414
    volatile PHY_AH_RX_CS06_U                               AH_RX_CS06                             ; // 0x5418
    volatile PHY_AH_RX_CS07_U                               AH_RX_CS07                             ; // 0x541c
    volatile PHY_AH_RX_CS08_U                               AH_RX_CS08                             ; // 0x5420
    volatile PHY_AH_RX_CS09_U                               AH_RX_CS09                             ; // 0x5424
    volatile uint32_t                                          RESERVED28[6]                          ; // 
    volatile PHY_AH_RX_CS10_U                               AH_RX_CS10                             ; // 0x5440
    volatile PHY_AH_RX_CS11_U                               AH_RX_CS11                             ; // 0x5444
    volatile PHY_AH_RX_CS12_U                               AH_RX_CS12                             ; // 0x5448
    volatile PHY_AH_RX_CS13_U                               AH_RX_CS13                             ; // 0x544c
    volatile PHY_AH_RX_CS14_U                               AH_RX_CS14                             ; // 0x5450
    volatile PHY_AH_RX_CS15_U                               AH_RX_CS15                             ; // 0x5454
    volatile PHY_AH_RX_CS16_U                               AH_RX_CS16                             ; // 0x5458
    volatile PHY_AH_RX_CS17_U                               AH_RX_CS17                             ; // 0x545c
    volatile PHY_AH_RX_CS18_U                               AH_RX_CS18                             ; // 0x5460
    volatile PHY_AH_RX_CS19_U                               AH_RX_CS19                             ; // 0x5464
    volatile PHY_AH_RX_CS1A_U                               AH_RX_CS1A                             ; // 0x5468
    volatile uint32_t                                          RESERVED29[5]                          ; // 
    volatile PHY_AH_RX_CS20_U                               AH_RX_CS20                             ; // 0x5480
    volatile PHY_AH_RX_CS21_U                               AH_RX_CS21                             ; // 0x5484
    volatile PHY_AH_RX_CS22_U                               AH_RX_CS22                             ; // 0x5488
    volatile PHY_AH_RX_CS23_U                               AH_RX_CS23                             ; // 0x548c
    volatile PHY_AH_RX_CS24_U                               AH_RX_CS24                             ; // 0x5490
    volatile uint32_t                                          RESERVED30[475]                        ; // 
    volatile PHY_RXDFE_IQDC_HPF_ON_U                        RXDFE_IQDC_HPF_ON                      ; // 0x5c00
    volatile PHY_RXDFE_IQDC_HPF_WHILE_AGC_U                 RXDFE_IQDC_HPF_WHILE_AGC               ; // 0x5c04
    volatile PHY_RXDFE_IQDC_HPF_WGT0_U                      RXDFE_IQDC_HPF_WGT0                    ; // 0x5c08
    volatile PHY_RXDFE_IQDC_HPF_WGT1_U                      RXDFE_IQDC_HPF_WGT1                    ; // 0x5c0c
    volatile PHY_RXDFE_IQDC_HPF_WGT2_U                      RXDFE_IQDC_HPF_WGT2                    ; // 0x5c10
    volatile PHY_RXDFE_IQDC_HPF_DUR_WGT2_U                  RXDFE_IQDC_HPF_DUR_WGT2                ; // 0x5c14
    volatile PHY_RXDFE_IQDC_LUT_CFG_U                       RXDFE_IQDC_LUT_CFG                     ; // 0x5c18
    volatile PHY_RXDFE_IQDC_LUT_ALG_U                       RXDFE_IQDC_LUT_ALG                     ; // 0x5c1c
    volatile PHY_RXDFE_IQDC_LUT_WRITE_U                     RXDFE_IQDC_LUT_WRITE                   ; // 0x5c20
    volatile PHY_RXDFE_IQDC_LUT_READ_U                      RXDFE_IQDC_LUT_READ                    ; // 0x5c24
    volatile PHY_RXDFE_IQDC_LUT_READ_RES_U                  RXDFE_IQDC_LUT_READ_RES                ; // 0x5c28
    volatile PHY_RXDFE_IQDC_LUT_AUTO_RES_U                  RXDFE_IQDC_LUT_AUTO_RES                ; // 0x5c2c
    volatile PHY_RXDFE_IQDC_CAL_PARA0_U                     RXDFE_IQDC_CAL_PARA0                   ; // 0x5c30
    volatile PHY_RXDFE_IQDC_CAL_PARA1_U                     RXDFE_IQDC_CAL_PARA1                   ; // 0x5c34
    volatile PHY_RXDFE_IQDC_CAL_SELF_VAL_U                  RXDFE_IQDC_CAL_SELF_VAL                ; // 0x5c38
    volatile PHY_RXDFE_IQDC_CAL_SELF_PARAM_GAIN_U           RXDFE_IQDC_CAL_SELF_PARAM_GAIN         ; // 0x5c3c
    volatile PHY_RXDFE_IQDC_CAL_SELF_PARAM_PHASE_U          RXDFE_IQDC_CAL_SELF_PARAM_PHASE        ; // 0x5c40
    volatile uint32_t                                          RESERVED31[240]                        ; // 
    volatile PHY_AH_RFAFE_INT_01_U                          AH_RFAFE_INT_01                        ; // 0x6004
    volatile PHY_AH_RFAFE_INT_02_U                          AH_RFAFE_INT_02                        ; // 0x6008
    volatile PHY_AH_RFAFE_INT_03_U                          AH_RFAFE_INT_03                        ; // 0x600c
    volatile PHY_AH_RFAFE_INT_04_U                          AH_RFAFE_INT_04                        ; // 0x6010
    volatile PHY_AH_RFAFE_INT_05_U                          AH_RFAFE_INT_05                        ; // 0x6014
    volatile PHY_AH_RFAFE_INT_06_U                          AH_RFAFE_INT_06                        ; // 0x6018
    volatile PHY_AH_RFAFE_INT_07_U                          AH_RFAFE_INT_07                        ; // 0x601c
    volatile PHY_AH_RFAFE_INT_08_U                          AH_RFAFE_INT_08                        ; // 0x6020
    volatile PHY_AH_RFAFE_INT_09_U                          AH_RFAFE_INT_09                        ; // 0x6024
    volatile PHY_AH_RFAFE_INT_10_U                          AH_RFAFE_INT_10                        ; // 0x6028
    volatile PHY_AH_RFAFE_INT_11_U                          AH_RFAFE_INT_11                        ; // 0x602c
    volatile PHY_AH_RFAFE_INT_12_U                          AH_RFAFE_INT_12                        ; // 0x6030
    volatile PHY_AH_RFAFE_INT_13_U                          AH_RFAFE_INT_13                        ; // 0x6034
    volatile PHY_AH_RFAFE_INT_14_U                          AH_RFAFE_INT_14                        ; // 0x6038
    volatile PHY_AH_RFAFE_INT_15_U                          AH_RFAFE_INT_15                        ; // 0x603c
    volatile PHY_AH_RFAFE_INT_16_U                          AH_RFAFE_INT_16                        ; // 0x6040
    volatile PHY_AH_RFAFE_INT_17_U                          AH_RFAFE_INT_17                        ; // 0x6044
    volatile PHY_AH_RFAFE_INT_18_U                          AH_RFAFE_INT_18                        ; // 0x6048
    volatile PHY_AH_RFAFE_INT_19_U                          AH_RFAFE_INT_19                        ; // 0x604c
    volatile PHY_AH_RFAFE_INT_20_U                          AH_RFAFE_INT_20                        ; // 0x6050
    volatile PHY_AH_RFAFE_INT_21_U                          AH_RFAFE_INT_21                        ; // 0x6054
    volatile PHY_AH_RFAFE_INT_22_U                          AH_RFAFE_INT_22                        ; // 0x6058
    volatile PHY_AH_RFAFE_INT_23_U                          AH_RFAFE_INT_23                        ; // 0x605c
    volatile PHY_AH_RFAFE_INT_24_U                          AH_RFAFE_INT_24                        ; // 0x6060
    volatile PHY_AH_RFAFE_INT_25_U                          AH_RFAFE_INT_25                        ; // 0x6064
    volatile PHY_AH_RFAFE_INT_26_U                          AH_RFAFE_INT_26                        ; // 0x6068
    volatile PHY_AH_RFAFE_INT_27_U                          AH_RFAFE_INT_27                        ; // 0x606c
    volatile PHY_AH_RFAFE_INT_28_U                          AH_RFAFE_INT_28                        ; // 0x6070
    volatile PHY_AH_RFAFE_INT_29_U                          AH_RFAFE_INT_29                        ; // 0x6074
    volatile PHY_AH_RFAFE_INT_30_U                          AH_RFAFE_INT_30                        ; // 0x6078
    volatile PHY_AH_RFAFE_INT_31_U                          AH_RFAFE_INT_31                        ; // 0x607c
    volatile PHY_AH_RFAFE_INT_32_U                          AH_RFAFE_INT_32                        ; // 0x6080
    volatile PHY_AH_RFAFE_INT_33_U                          AH_RFAFE_INT_33                        ; // 0x6084
    volatile PHY_AH_RFAFE_INT_34_U                          AH_RFAFE_INT_34                        ; // 0x6088
    volatile PHY_AH_RFAFE_INT_35_U                          AH_RFAFE_INT_35                        ; // 0x608c
    volatile PHY_AH_RFAFE_INT_36_U                          AH_RFAFE_INT_36                        ; // 0x6090
    volatile PHY_AH_RFAFE_INT_37_U                          AH_RFAFE_INT_37                        ; // 0x6094
    volatile PHY_AH_RFAFE_INT_38_U                          AH_RFAFE_INT_38                        ; // 0x6098
    volatile PHY_AH_RFAFE_INT_39_U                          AH_RFAFE_INT_39                        ; // 0x609c
    volatile PHY_AH_RFAFE_INT_40_U                          AH_RFAFE_INT_40                        ; // 0x60a0
    volatile PHY_AH_RFAFE_INT_41_U                          AH_RFAFE_INT_41                        ; // 0x60a4
    volatile PHY_AH_RFAFE_INT_42_U                          AH_RFAFE_INT_42                        ; // 0x60a8
    volatile PHY_AH_RFAFE_INT_43_U                          AH_RFAFE_INT_43                        ; // 0x60ac
    volatile PHY_AH_RFAFE_INT_44_U                          AH_RFAFE_INT_44                        ; // 0x60b0
    volatile PHY_AH_RFAFE_INT_45_U                          AH_RFAFE_INT_45                        ; // 0x60b4
    volatile PHY_AH_RFAFE_INT_46_U                          AH_RFAFE_INT_46                        ; // 0x60b8
    volatile PHY_AH_RFAFE_INT_47_U                          AH_RFAFE_INT_47                        ; // 0x60bc
    volatile PHY_AH_RFAFE_INT_48_U                          AH_RFAFE_INT_48                        ; // 0x60c0
    volatile PHY_AH_RFAFE_INT_49_U                          AH_RFAFE_INT_49                        ; // 0x60c4
    volatile PHY_AH_RFAFE_INT_50_U                          AH_RFAFE_INT_50                        ; // 0x60c8
    volatile PHY_AH_RFAFE_INT_51_U                          AH_RFAFE_INT_51                        ; // 0x60cc
    volatile PHY_AH_RFAFE_INT_52_U                          AH_RFAFE_INT_52                        ; // 0x60d0
    volatile PHY_AH_RFAFE_INT_53_U                          AH_RFAFE_INT_53                        ; // 0x60d4
    volatile PHY_AH_RFAFE_INT_54_U                          AH_RFAFE_INT_54                        ; // 0x60d8
    volatile PHY_AH_RFAFE_INT_55_U                          AH_RFAFE_INT_55                        ; // 0x60dc
    volatile PHY_AH_RFAFE_INT_56_U                          AH_RFAFE_INT_56                        ; // 0x60e0
    volatile PHY_AH_RFAFE_INT_57_U                          AH_RFAFE_INT_57                        ; // 0x60e4
    volatile PHY_AH_RFAFE_INT_58_U                          AH_RFAFE_INT_58                        ; // 0x60e8
    volatile PHY_AH_RFAFE_INT_59_U                          AH_RFAFE_INT_59                        ; // 0x60ec
    volatile PHY_AH_RFAFE_INT_60_U                          AH_RFAFE_INT_60                        ; // 0x60f0
    volatile PHY_AH_RFAFE_INT_61_U                          AH_RFAFE_INT_61                        ; // 0x60f4
    volatile PHY_AH_RFAFE_INT_62_U                          AH_RFAFE_INT_62                        ; // 0x60f8
    volatile PHY_AH_RFAFE_INT_63_U                          AH_RFAFE_INT_63                        ; // 0x60fc
    volatile PHY_AH_RFAFE_INT_64_U                          AH_RFAFE_INT_64                        ; // 0x6100
    volatile PHY_AH_RFAFE_INT_65_U                          AH_RFAFE_INT_65                        ; // 0x6104
    volatile PHY_AH_RFAFE_INT_66_U                          AH_RFAFE_INT_66                        ; // 0x6108
    volatile PHY_AH_RFAFE_INT_67_U                          AH_RFAFE_INT_67                        ; // 0x610c
    volatile PHY_AH_RFAFE_INT_68_U                          AH_RFAFE_INT_68                        ; // 0x6110
    volatile PHY_AH_RFAFE_INT_69_U                          AH_RFAFE_INT_69                        ; // 0x6114
    volatile PHY_AH_RFAFE_INT_70_U                          AH_RFAFE_INT_70                        ; // 0x6118
    volatile PHY_AH_RFAFE_INT_71_U                          AH_RFAFE_INT_71                        ; // 0x611c
    volatile PHY_AH_RFAFE_INT_72_U                          AH_RFAFE_INT_72                        ; // 0x6120
    volatile PHY_AH_RFAFE_INT_73_U                          AH_RFAFE_INT_73                        ; // 0x6124
    volatile PHY_AH_RFAFE_INT_74_U                          AH_RFAFE_INT_74                        ; // 0x6128
    volatile PHY_AH_RFAFE_INT_75_U                          AH_RFAFE_INT_75                        ; // 0x612c
    volatile PHY_AH_RFAFE_INT_76_U                          AH_RFAFE_INT_76                        ; // 0x6130
    volatile PHY_AH_RFAFE_INT_77_U                          AH_RFAFE_INT_77                        ; // 0x6134
    volatile PHY_AH_RFAFE_INT_78_U                          AH_RFAFE_INT_78                        ; // 0x6138
    volatile PHY_AH_RFAFE_INT_79_U                          AH_RFAFE_INT_79                        ; // 0x613c
} PHY_Type;

#ifdef __cplusplus
}
#endif

#endif /* __REG_PHY_H__ */
