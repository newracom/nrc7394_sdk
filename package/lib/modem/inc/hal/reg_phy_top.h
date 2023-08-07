/*********************************************************************/
/*    Newracom Library / IP Product                                  */
/*    Product Name :                                                 */
/*    Version      :                                                 */
/*    Author       :                                                 */
/*    Update       :                                                 */
/*********************************************************************/

#ifndef __REG_PHY_TOP_H__
#define __REG_PHY_TOP_H__

#ifdef __cplusplus
extern "C"{
#endif

// 0x40088000 register ------------------------------------
typedef struct {
    uint32_t                        SW_RESET                       :1 ;
    uint32_t                        SW_RST_RX_IDLE                 :1 ;
    uint32_t                        PHY_EN                         :1 ;
    uint32_t                        RF_CAL_EN                      :1 ;
    uint32_t                        TEST_MD_EN                     :1 ;
    uint32_t                        reserved0                      :3 ;
    uint32_t                        TXDEF_LATENCY_1M               :8 ;
    uint32_t                        TXDEF_LATENCY_2M               :8 ;
    uint32_t                        RF_LATENCY                     :8 ;
}   PHY_TOP_PHY_TOP_STATE00;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOP_STATE00         b;
}   PHY_TOP_PHY_TOP_STATE00_U;


// 0x40088004 register ------------------------------------
typedef struct {
    uint32_t                        EN_RXDFE                       :1 ;
    uint32_t                        EN_RXDBE                       :1 ;
    uint32_t                        EN_TXDFE                       :1 ;
    uint32_t                        EN_TXDBE                       :1 ;
    uint32_t                        TXSTART_REQ                    :1 ;
    uint32_t                        RXPPDU                         :1 ;
    uint32_t                        TXPPDU                         :1 ;
    uint32_t                        reserved0                      :1 ;
    uint32_t                        CCA                            :3 ;
    uint32_t                        reserved1                      :5 ;
    uint32_t                        CUR_PHY_TOP_STATE              :5 ;
    uint32_t                        reserved2                      :11;
}   PHY_TOP_PHY_TOP_STATE01;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOP_STATE01         b;
}   PHY_TOP_PHY_TOP_STATE01_U;


// 0x40088008 register ------------------------------------
typedef struct {
    uint32_t                        MANUAL_CTRL_AUX_PLL_CAL_CLK    :2 ;
    uint32_t                        AUX_PLL_CAL_CLK_INV            :1 ;
    uint32_t                        reserved0                      :29;
}   PHY_TOP_PHY_TOP_STATE02;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOP_STATE02         b;
}   PHY_TOP_PHY_TOP_STATE02_U;


// 0x4008800C register ------------------------------------
typedef struct {
    uint32_t                        i7_reg_txvec_sbr_length        :16;
    uint32_t                        reserved0                      :16;
}   PHY_TOP_PHY_TOP_STATE03;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOP_STATE03         b;
}   PHY_TOP_PHY_TOP_STATE03_U;


// 0x40088200 register ------------------------------------
typedef struct {
    uint32_t                        TX_SCR_SEED_MODE               :1 ;
    uint32_t                        reserved0                      :3 ;
    uint32_t                        r_reg_trx_scr_seed_rev         :1 ;
    uint32_t                        reserved1                      :3 ;
    uint32_t                        TX_SCRAMBLER_SEED              :7 ;
    uint32_t                        r_reg_tx_srv                   :1 ;
    uint32_t                        TXPWR_MODE                     :1 ;
    uint32_t                        reserved2                      :7 ;
    uint32_t                        TXPWR_LEVEL                    :8 ;
}   PHY_TOP_TX_PPDU_STATE00;

typedef union {
    uint32_t                        w;
    PHY_TOP_TX_PPDU_STATE00         b;
}   PHY_TOP_TX_PPDU_STATE00_U;


// 0x40088204 register ------------------------------------
typedef struct {
    uint32_t                        N_DBPS                         :14;
    uint32_t                        reserved0                      :2 ;
    uint32_t                        TX_FORMAT                      :2 ;
    uint32_t                        TX_CBW                         :2 ;
    uint32_t                        TX_PREAMBLE                    :1 ;
    uint32_t                        reserved1                      :3 ;
    uint32_t                        TX_MCS                         :4 ;
    uint32_t                        i_reg_txvec_sbr_enable         :1 ;
    uint32_t                        i_reg_txvec_sbr_rate           :1 ;
    uint32_t                        reserved2                      :2 ;
}   PHY_TOP_TX_PPDU_STATE01;

typedef union {
    uint32_t                        w;
    PHY_TOP_TX_PPDU_STATE01         b;
}   PHY_TOP_TX_PPDU_STATE01_U;


// 0x40088208 register ------------------------------------
typedef struct {
    uint32_t                        BYTE_LEN                       :20;
    uint32_t                        reserved0                      :12;
}   PHY_TOP_TX_PPDU_STATE02;

typedef union {
    uint32_t                        w;
    PHY_TOP_TX_PPDU_STATE02         b;
}   PHY_TOP_TX_PPDU_STATE02_U;


// 0x4008820C register ------------------------------------
typedef struct {
    uint32_t                        TXVEC_ERR_CNT                  :32;
}   PHY_TOP_TX_PPDU_STATE03;

typedef union {
    uint32_t                        w;
    PHY_TOP_TX_PPDU_STATE03         b;
}   PHY_TOP_TX_PPDU_STATE03_U;


// 0x40088210 register ------------------------------------
typedef struct {
    uint32_t                        TXSIG_ERR_CNT                  :32;
}   PHY_TOP_TX_PPDU_STATE04;

typedef union {
    uint32_t                        w;
    PHY_TOP_TX_PPDU_STATE04         b;
}   PHY_TOP_TX_PPDU_STATE04_U;


// 0x40088214 register ------------------------------------
typedef struct {
    uint32_t                        PACKET_TRANSMISSION_CNT        :32;
}   PHY_TOP_TX_PPDU_STATE05;

typedef union {
    uint32_t                        w;
    PHY_TOP_TX_PPDU_STATE05         b;
}   PHY_TOP_TX_PPDU_STATE05_U;


// 0x40088218 register ------------------------------------
typedef struct {
    uint32_t                        TXREADY_ERR_CNT                :32;
}   PHY_TOP_TX_PPDU_STATE06;

typedef union {
    uint32_t                        w;
    PHY_TOP_TX_PPDU_STATE06         b;
}   PHY_TOP_TX_PPDU_STATE06_U;


// 0x4008821C register ------------------------------------
typedef struct {
    uint32_t                        TXDBE_RD_ERR_CNT               :32;
}   PHY_TOP_TX_PPDU_STATE07;

typedef union {
    uint32_t                        w;
    PHY_TOP_TX_PPDU_STATE07         b;
}   PHY_TOP_TX_PPDU_STATE07_U;


// 0x40088220 register ------------------------------------
typedef struct {
    uint32_t                        i5_reg_tx_ppdu_state           :32;
}   PHY_TOP_TX_PPDU_STATE08;

typedef union {
    uint32_t                        w;
    PHY_TOP_TX_PPDU_STATE08         b;
}   PHY_TOP_TX_PPDU_STATE08_U;


// 0x40088400 register ------------------------------------
typedef struct {
    uint32_t                        MODE_ID_CHECK                  :1 ;
    uint32_t                        IGNORE_UPLINK_IND              :1 ;
    uint32_t                        IGNORE_RSRVD_BIT               :1 ;
    uint32_t                        reserved0                      :13;
    uint32_t                        BSSID_0                        :10;
    uint32_t                        reserved1                      :6 ;
}   PHY_TOP_RX_PPDU_STATE00;

typedef union {
    uint32_t                        w;
    PHY_TOP_RX_PPDU_STATE00         b;
}   PHY_TOP_RX_PPDU_STATE00_U;


// 0x40088404 register ------------------------------------
typedef struct {
    uint32_t                        BSSID_1                        :10;
    uint32_t                        reserved0                      :22;
}   PHY_TOP_RX_PPDU_STATE01;

typedef union {
    uint32_t                        w;
    PHY_TOP_RX_PPDU_STATE01         b;
}   PHY_TOP_RX_PPDU_STATE01_U;


// 0x40088408 register ------------------------------------
typedef struct {
    uint32_t                        BSSID_2                        :10;
    uint32_t                        reserved0                      :22;
}   PHY_TOP_RX_PPDU_STATE02;

typedef union {
    uint32_t                        w;
    PHY_TOP_RX_PPDU_STATE02         b;
}   PHY_TOP_RX_PPDU_STATE02_U;


// 0x4008840C register ------------------------------------
typedef struct {
    uint32_t                        BSSID_3                        :10;
    uint32_t                        reserved0                      :22;
}   PHY_TOP_RX_PPDU_STATE03;

typedef union {
    uint32_t                        w;
    PHY_TOP_RX_PPDU_STATE03         b;
}   PHY_TOP_RX_PPDU_STATE03_U;


// 0x40088410 register ------------------------------------
typedef struct {
    uint32_t                        BSSID_4                        :10;
    uint32_t                        reserved0                      :22;
}   PHY_TOP_RX_PPDU_STATE04;

typedef union {
    uint32_t                        w;
    PHY_TOP_RX_PPDU_STATE04         b;
}   PHY_TOP_RX_PPDU_STATE04_U;


// 0x40088414 register ------------------------------------
typedef struct {
    uint32_t                        reserved0                      :2 ;
    uint32_t                        RX_CBW                         :2 ;
    uint32_t                        RX_PREAMBLE                    :1 ;
    uint32_t                        UNSUPPORTED                    :1 ;
    uint32_t                        ID_MATCH                       :1 ;
    uint32_t                        FD_FRAME_START                 :1 ;
    uint32_t                        BYTE_LEN                       :20;
    uint32_t                        RX_MCS                         :4 ;
}   PHY_TOP_RX_PPDU_STATE05;

typedef union {
    uint32_t                        w;
    PHY_TOP_RX_PPDU_STATE05         b;
}   PHY_TOP_RX_PPDU_STATE05_U;


// 0x40088418 register ------------------------------------
typedef struct {
    uint32_t                        RSSI                           :8 ;
    uint32_t                        RCPI                           :8 ;
    uint32_t                        RX_CFO_VALUE                   :13;
    uint32_t                        reserved0                      :3 ;
}   PHY_TOP_RX_PPDU_STATE06;

typedef union {
    uint32_t                        w;
    PHY_TOP_RX_PPDU_STATE06         b;
}   PHY_TOP_RX_PPDU_STATE06_U;


// 0x4008841C register ------------------------------------
typedef struct {
    uint32_t                        RX_TIMEOUT_CNT0                :32;
}   PHY_TOP_RX_PPDU_STATE07;

typedef union {
    uint32_t                        w;
    PHY_TOP_RX_PPDU_STATE07         b;
}   PHY_TOP_RX_PPDU_STATE07_U;


// 0x40088420 register ------------------------------------
typedef struct {
    uint32_t                        RX_TIMEOUT_CNT1                :32;
}   PHY_TOP_RX_PPDU_STATE08;

typedef union {
    uint32_t                        w;
    PHY_TOP_RX_PPDU_STATE08         b;
}   PHY_TOP_RX_PPDU_STATE08_U;


// 0x40088424 register ------------------------------------
typedef struct {
    uint32_t                        RX_TIMEOUT_CNT2                :32;
}   PHY_TOP_RX_PPDU_STATE09;

typedef union {
    uint32_t                        w;
    PHY_TOP_RX_PPDU_STATE09         b;
}   PHY_TOP_RX_PPDU_STATE09_U;


// 0x40088428 register ------------------------------------
typedef struct {
    uint32_t                        RX_TIMEOUT_CNT3                :32;
}   PHY_TOP_RX_PPDU_STATE10;

typedef union {
    uint32_t                        w;
    PHY_TOP_RX_PPDU_STATE10         b;
}   PHY_TOP_RX_PPDU_STATE10_U;


// 0x4008842C register ------------------------------------
typedef struct {
    uint32_t                        RX_TIMEOUT_CNT4                :32;
}   PHY_TOP_RX_PPDU_STATE11;

typedef union {
    uint32_t                        w;
    PHY_TOP_RX_PPDU_STATE11         b;
}   PHY_TOP_RX_PPDU_STATE11_U;


// 0x40088430 register ------------------------------------
typedef struct {
    uint32_t                        RX_TIMEOUT_CNT5                :32;
}   PHY_TOP_RX_PPDU_STATE12;

typedef union {
    uint32_t                        w;
    PHY_TOP_RX_PPDU_STATE12         b;
}   PHY_TOP_RX_PPDU_STATE12_U;


// 0x40088438 register ------------------------------------
typedef struct {
    uint32_t                        RX_PPDU_STATE                  :5 ;
    uint32_t                        FLAG_DBE_DATFIELD              :1 ;
    uint32_t                        reserved0                      :26;
}   PHY_TOP_RX_PPDU_STATE14;

typedef union {
    uint32_t                        w;
    PHY_TOP_RX_PPDU_STATE14         b;
}   PHY_TOP_RX_PPDU_STATE14_U;


// 0x4008843C register ------------------------------------
typedef struct {
    uint32_t                        DATA_SYM_CNT                   :10;
    uint32_t                        reserved0                      :6 ;
    uint32_t                        N_SYM                          :10;
    uint32_t                        reserved1                      :6 ;
}   PHY_TOP_RX_PPDU_STATE15;

typedef union {
    uint32_t                        w;
    PHY_TOP_RX_PPDU_STATE15         b;
}   PHY_TOP_RX_PPDU_STATE15_U;


// 0x40088440 register ------------------------------------
typedef struct {
    uint32_t                        FRAME_END_RSSI                 :1 ;
    uint32_t                        FRAME_END_TIME                 :1 ;
    uint32_t                        FD_FRAME_END                   :1 ;
    uint32_t                        reserved0                      :29;
}   PHY_TOP_RX_PPDU_STATE16;

typedef union {
    uint32_t                        w;
    PHY_TOP_RX_PPDU_STATE16         b;
}   PHY_TOP_RX_PPDU_STATE16_U;


// 0x40088600 register ------------------------------------
typedef struct {
    uint32_t                        PHY_TEST_MD                    :2 ;
    uint32_t                        PHY_TEST_TX_DATA_TYPE          :2 ;
    uint32_t                        PHY_TEST_CONT_TX_START         :1 ;
    uint32_t                        PHY_TEST_LOOPBACK_START        :1 ;
    uint32_t                        r_reg_test_md_txcw_start       :1 ;
    uint32_t                        reserved0                      :25;
}   PHY_TOP_PHY_TEST_MD00;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TEST_MD00           b;
}   PHY_TOP_PHY_TEST_MD00_U;


// 0x40088604 register ------------------------------------
typedef struct {
    uint32_t                        TEST_TXVECTOR                  :31;
    uint32_t                        reserved0                      :1 ;
}   PHY_TOP_PHY_TEST_MD01;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TEST_MD01           b;
}   PHY_TOP_PHY_TEST_MD01_U;


// 0x40088608 register ------------------------------------
typedef struct {
    uint32_t                        TEST_TXSIG                     :32;
}   PHY_TOP_PHY_TEST_MD02;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TEST_MD02           b;
}   PHY_TOP_PHY_TEST_MD02_U;


// 0x4008860C register ------------------------------------
typedef struct {
    uint32_t                        TEST_TXSIG                     :10;
    uint32_t                        reserved0                      :22;
}   PHY_TOP_PHY_TEST_MD03;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TEST_MD03           b;
}   PHY_TOP_PHY_TEST_MD03_U;


// 0x40088610 register ------------------------------------
typedef struct {
    uint32_t                        TEST_DATA                      :32;
}   PHY_TOP_PHY_TEST_MD04;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TEST_MD04           b;
}   PHY_TOP_PHY_TEST_MD04_U;


// 0x40088614 register ------------------------------------
typedef struct {
    uint32_t                        TEST_TX_CW_FREQ                :3 ;
    uint32_t                        reserved0                      :1 ;
    uint32_t                        TEST_TX_CW_MSB_INV             :1 ;
    uint32_t                        reserved1                      :27;
}   PHY_TOP_PHY_TEST_MD05;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TEST_MD05           b;
}   PHY_TOP_PHY_TEST_MD05_U;


// 0x40088630 register ------------------------------------
typedef struct {
    uint32_t                        SIM_TRX_MODE                   :1 ;
    uint32_t                        reserved0                      :31;
}   PHY_TOP_PHY_SIM_TRX_MD;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_SIM_TRX_MD          b;
}   PHY_TOP_PHY_SIM_TRX_MD_U;


// 0x40088800 register ------------------------------------
typedef struct {
    uint32_t                        WGT_CHUP                       :2 ;
    uint32_t                        reserved0                      :30;
}   PHY_TOP_PHY_RXDBE00;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_RXDBE00             b;
}   PHY_TOP_PHY_RXDBE00_U;


// 0x40088804 register ------------------------------------
typedef struct {
    uint32_t                        NOISE_EST_MIN                  :26;
    uint32_t                        reserved0                      :6 ;
}   PHY_TOP_PHY_RXDBE01;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_RXDBE01             b;
}   PHY_TOP_PHY_RXDBE01_U;


// 0x40089000 register ------------------------------------
typedef struct {
    uint32_t                        RX_OP_MODE                     :1 ;
    uint32_t                        TX_OP_MODE                     :1 ;
    uint32_t                        reserved0                      :30;
}   PHY_TOP_PHY_TOPIF_CLK_GEN0;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOPIF_CLK_GEN0      b;
}   PHY_TOP_PHY_TOPIF_CLK_GEN0_U;


// 0x40089004 register ------------------------------------
typedef struct {
    uint32_t                        CLKBUF_EN_RFCAL                :1 ;
    uint32_t                        reserved0                      :31;
}   PHY_TOP_PHY_TOPIF_CLK_GEN1;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOPIF_CLK_GEN1      b;
}   PHY_TOP_PHY_TOPIF_CLK_GEN1_U;


// 0x40089008 register ------------------------------------
typedef struct {
    uint32_t                        CLKBUF_EN_TX_SIG_X1            :1 ;
    uint32_t                        CLKBUF_EN_TX_SIG_X2            :1 ;
    uint32_t                        CLKBUF_EN_TX_SIG_X4            :1 ;
    uint32_t                        CLKBUF_EN_TX_OP_X4             :1 ;
    uint32_t                        reserved0                      :28;
}   PHY_TOP_PHY_TOPIF_CLK_GEN2;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOPIF_CLK_GEN2      b;
}   PHY_TOP_PHY_TOPIF_CLK_GEN2_U;


// 0x4008900C register ------------------------------------
typedef struct {
    uint32_t                        CLKBUF_EN_RX_DIV2_OP2_CS       :1 ;
    uint32_t                        CLKBUF_EN_RX_DIV2_OP2_DFE1     :1 ;
    uint32_t                        CLKBUF_EN_RX_DIV2_OP4          :1 ;
    uint32_t                        CLKBUF_EN_RX_DIV2_OP2          :1 ;
    uint32_t                        CLKBUF_EN_RX_X1_OP2_CS         :1 ;
    uint32_t                        CLKBUF_EN_RX_X1_OP2_DFE1       :1 ;
    uint32_t                        CLKBUF_EN_RX_X1_OP2            :1 ;
    uint32_t                        CLKBUF_EN_RX_X2_OP2_DFE1       :1 ;
    uint32_t                        CLKBUF_EN_RX_X2_AGC            :1 ;
    uint32_t                        CLKBUF_EN_RX_X4_AGC            :1 ;
    uint32_t                        CLKBUF_EN_RX_X1X2_DFE2         :1 ;
    uint32_t                        CLKBUF_EN_RX_DIV2X1            :1 ;
    uint32_t                        CLKBUF_EN_RX_X1X2              :1 ;
    uint32_t                        CLKBUF_EN_RX_X2X4_DBE          :1 ;
    uint32_t                        CLKBUF_EN_RX_X2X4              :1 ;
    uint32_t                        CLKBUF_EN_RX_X4X8              :1 ;
    uint32_t                        CLKBUF_EN_RX_X4X8_DBE          :1 ;
    uint32_t                        reserved0                      :15;
}   PHY_TOP_PHY_TOPIF_CLK_GEN3;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOPIF_CLK_GEN3      b;
}   PHY_TOP_PHY_TOPIF_CLK_GEN3_U;


// 0x40089010 register ------------------------------------
typedef struct {
    uint32_t                        LOOPBACK_EN                    :1 ;
    uint32_t                        reserved0                      :31;
}   PHY_TOP_PHY_TOPIF_CLK_GEN4;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOPIF_CLK_GEN4      b;
}   PHY_TOP_PHY_TOPIF_CLK_GEN4_U;


// 0x40089014 register ------------------------------------
typedef struct {
    uint32_t                        BW_1M_EN                       :1 ;
    uint32_t                        reserved0                      :31;
}   PHY_TOP_PHY_TOPIF_CLK_GEN5;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOPIF_CLK_GEN5      b;
}   PHY_TOP_PHY_TOPIF_CLK_GEN5_U;


// 0x40089100 register ------------------------------------
typedef struct {
    uint32_t                        TXFIFO_AF_LVL                  :5 ;
    uint32_t                        reserved0                      :11;
    uint32_t                        TXFIFO_MAX_LVL                 :5 ;
    uint32_t                        reserved1                      :11;
}   PHY_TOP_PHY_TOPIF_TXFIFO0;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOPIF_TXFIFO0       b;
}   PHY_TOP_PHY_TOPIF_TXFIFO0_U;


// 0x40089104 register ------------------------------------
typedef struct {
    uint32_t                        TXFIFO_WR_CNT                  :14;
    uint32_t                        reserved0                      :18;
}   PHY_TOP_PHY_TOPIF_TXFIFO1;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOPIF_TXFIFO1       b;
}   PHY_TOP_PHY_TOPIF_TXFIFO1_U;


// 0x40089108 register ------------------------------------
typedef struct {
    uint32_t                        TXFIFO_RD_CNT                  :14;
    uint32_t                        reserved0                      :18;
}   PHY_TOP_PHY_TOPIF_TXFIFO2;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOPIF_TXFIFO2       b;
}   PHY_TOP_PHY_TOPIF_TXFIFO2_U;


// 0x4008910C register ------------------------------------
typedef struct {
    uint32_t                        TXFIFO_FULL_CNT                :32;
}   PHY_TOP_PHY_TOPIF_TXFIFO3;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOPIF_TXFIFO3       b;
}   PHY_TOP_PHY_TOPIF_TXFIFO3_U;


// 0x40089110 register ------------------------------------
typedef struct {
    uint32_t                        TXFIFO_OVFL_CNT                :32;
}   PHY_TOP_PHY_TOPIF_TXFIFO4;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOPIF_TXFIFO4       b;
}   PHY_TOP_PHY_TOPIF_TXFIFO4_U;


// 0x40089170 register ------------------------------------
typedef struct {
    uint32_t                        PHY_LOOPBACK_ON                :1 ;
    uint32_t                        reserved0                      :31;
}   PHY_TOP_PHY_TOPIF_LOOPBACK;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOPIF_LOOPBACK      b;
}   PHY_TOP_PHY_TOPIF_LOOPBACK_U;


// 0x40089180 register ------------------------------------
typedef struct {
    uint32_t                        RX_PRIM_CH_LOC                 :2 ;
    uint32_t                        reserved0                      :30;
}   PHY_TOP_PHY_TOPIF_CONFIG0;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOPIF_CONFIG0       b;
}   PHY_TOP_PHY_TOPIF_CONFIG0_U;


// 0x400891A0 register ------------------------------------
typedef struct {
    uint32_t                        RF_TYPESEL                     :1 ;
    uint32_t                        reserved0                      :31;
}   PHY_TOP_PHY_TOPIF_RFCTRL;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOPIF_RFCTRL        b;
}   PHY_TOP_PHY_TOPIF_RFCTRL_U;


// 0x400891B0 register ------------------------------------
typedef struct {
    uint32_t                        VMAC_TEST_MODE                 :1 ;
    uint32_t                        reserved0                      :31;
}   PHY_TOP_PHY_TOPIF_VMACCFG0;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOPIF_VMACCFG0      b;
}   PHY_TOP_PHY_TOPIF_VMACCFG0_U;


// 0x400891B4 register ------------------------------------
typedef struct {
    uint32_t                        VMAC_TEST_EN                   :1 ;
    uint32_t                        reserved0                      :31;
}   PHY_TOP_PHY_TOPIF_VMACCFG1;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOPIF_VMACCFG1      b;
}   PHY_TOP_PHY_TOPIF_VMACCFG1_U;


// 0x400891B8 register ------------------------------------
typedef struct {
    uint32_t                        VMAC_ITV_DLY                   :32;
}   PHY_TOP_PHY_TOPIF_VMACCFG2;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOPIF_VMACCFG2      b;
}   PHY_TOP_PHY_TOPIF_VMACCFG2_U;


// 0x400891BC register ------------------------------------
typedef struct {
    uint32_t                        VMAC_FRM_CNT                   :32;
}   PHY_TOP_PHY_TOPIF_VMACCFG3;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOPIF_VMACCFG3      b;
}   PHY_TOP_PHY_TOPIF_VMACCFG3_U;


// 0x400891C0 register ------------------------------------
typedef struct {
    uint32_t                        VMAC_TX_VECTOR                 :31;
    uint32_t                        reserved0                      :1 ;
}   PHY_TOP_PHY_TOPIF_VMACCFG4;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOPIF_VMACCFG4      b;
}   PHY_TOP_PHY_TOPIF_VMACCFG4_U;


// 0x400891C4 register ------------------------------------
typedef struct {
    uint32_t                        VMAC_TX_DATA                   :32;
}   PHY_TOP_PHY_TOPIF_VMACCFG5;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOPIF_VMACCFG5      b;
}   PHY_TOP_PHY_TOPIF_VMACCFG5_U;


// 0x400891C8 register ------------------------------------
typedef struct {
    uint32_t                        VMAC_TX_SIG_DATA_1             :32;
}   PHY_TOP_PHY_TOPIF_VMACCFG6;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOPIF_VMACCFG6      b;
}   PHY_TOP_PHY_TOPIF_VMACCFG6_U;


// 0x400891CC register ------------------------------------
typedef struct {
    uint32_t                        VMAC_TX_SIG_DATA_2             :10;
    uint32_t                        reserved0                      :22;
}   PHY_TOP_PHY_TOPIF_VMACCFG7;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOPIF_VMACCFG7      b;
}   PHY_TOP_PHY_TOPIF_VMACCFG7_U;


// 0x400891D0 register ------------------------------------
typedef struct {
    uint32_t                        VMAC_TX_DATA_SEL               :2 ;
    uint32_t                        reserved0                      :30;
}   PHY_TOP_PHY_TOPIF_VMACCFG8;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOPIF_VMACCFG8      b;
}   PHY_TOP_PHY_TOPIF_VMACCFG8_U;


// 0x400891D4 register ------------------------------------
typedef struct {
    uint32_t                        VMAC_TXIQ_PARA_0               :11;
    uint32_t                        reserved0                      :21;
}   PHY_TOP_PHY_TOPIF_VMACCFG9;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOPIF_VMACCFG9      b;
}   PHY_TOP_PHY_TOPIF_VMACCFG9_U;


// 0x400891D8 register ------------------------------------
typedef struct {
    uint32_t                        VMAC_TXIQ_PARA_1               :11;
    uint32_t                        reserved0                      :21;
}   PHY_TOP_PHY_TOPIF_VMACCFG10;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOPIF_VMACCFG10     b;
}   PHY_TOP_PHY_TOPIF_VMACCFG10_U;


// 0x400891DC register ------------------------------------
typedef struct {
    uint32_t                        VMAC_TXLO_PARA_I               :10;
    uint32_t                        reserved0                      :22;
}   PHY_TOP_PHY_TOPIF_VMACCFG11;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOPIF_VMACCFG11     b;
}   PHY_TOP_PHY_TOPIF_VMACCFG11_U;


// 0x400891E0 register ------------------------------------
typedef struct {
    uint32_t                        VMAC_TXLO_PARA_Q               :10;
    uint32_t                        reserved0                      :22;
}   PHY_TOP_PHY_TOPIF_VMACCFG12;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOPIF_VMACCFG12     b;
}   PHY_TOP_PHY_TOPIF_VMACCFG12_U;


// 0x400891E4 register ------------------------------------
typedef struct {
    uint32_t                        VMAC_TX_D_GAIN                 :12;
    uint32_t                        reserved0                      :20;
}   PHY_TOP_PHY_TOPIF_VMACCFG13;

typedef union {
    uint32_t                        w;
    PHY_TOP_PHY_TOPIF_VMACCFG13     b;
}   PHY_TOP_PHY_TOPIF_VMACCFG13_U;


//---------------------------------------------------------
// PHY_TOP Register Map
//---------------------------------------------------------
typedef struct {
    volatile PHY_TOP_PHY_TOP_STATE00_U              PHY_TOP_STATE00            ; // 0x000
    volatile PHY_TOP_PHY_TOP_STATE01_U              PHY_TOP_STATE01            ; // 0x004
    volatile PHY_TOP_PHY_TOP_STATE02_U              PHY_TOP_STATE02            ; // 0x008
    volatile PHY_TOP_PHY_TOP_STATE03_U              PHY_TOP_STATE03            ; // 0x00c
    volatile uint32_t                              RESERVED0[124]             ; // 
    volatile PHY_TOP_TX_PPDU_STATE00_U              TX_PPDU_STATE00            ; // 0x200
    volatile PHY_TOP_TX_PPDU_STATE01_U              TX_PPDU_STATE01            ; // 0x204
    volatile PHY_TOP_TX_PPDU_STATE02_U              TX_PPDU_STATE02            ; // 0x208
    volatile PHY_TOP_TX_PPDU_STATE03_U              TX_PPDU_STATE03            ; // 0x20c
    volatile PHY_TOP_TX_PPDU_STATE04_U              TX_PPDU_STATE04            ; // 0x210
    volatile PHY_TOP_TX_PPDU_STATE05_U              TX_PPDU_STATE05            ; // 0x214
    volatile PHY_TOP_TX_PPDU_STATE06_U              TX_PPDU_STATE06            ; // 0x218
    volatile PHY_TOP_TX_PPDU_STATE07_U              TX_PPDU_STATE07            ; // 0x21c
    volatile PHY_TOP_TX_PPDU_STATE08_U              TX_PPDU_STATE08            ; // 0x220
    volatile uint32_t                              RESERVED1[119]             ; // 
    volatile PHY_TOP_RX_PPDU_STATE00_U              RX_PPDU_STATE00            ; // 0x400
    volatile PHY_TOP_RX_PPDU_STATE01_U              RX_PPDU_STATE01            ; // 0x404
    volatile PHY_TOP_RX_PPDU_STATE02_U              RX_PPDU_STATE02            ; // 0x408
    volatile PHY_TOP_RX_PPDU_STATE03_U              RX_PPDU_STATE03            ; // 0x40c
    volatile PHY_TOP_RX_PPDU_STATE04_U              RX_PPDU_STATE04            ; // 0x410
    volatile PHY_TOP_RX_PPDU_STATE05_U              RX_PPDU_STATE05            ; // 0x414
    volatile PHY_TOP_RX_PPDU_STATE06_U              RX_PPDU_STATE06            ; // 0x418
    volatile PHY_TOP_RX_PPDU_STATE07_U              RX_PPDU_STATE07            ; // 0x41c
    volatile PHY_TOP_RX_PPDU_STATE08_U              RX_PPDU_STATE08            ; // 0x420
    volatile PHY_TOP_RX_PPDU_STATE09_U              RX_PPDU_STATE09            ; // 0x424
    volatile PHY_TOP_RX_PPDU_STATE10_U              RX_PPDU_STATE10            ; // 0x428
    volatile PHY_TOP_RX_PPDU_STATE11_U              RX_PPDU_STATE11            ; // 0x42c
    volatile PHY_TOP_RX_PPDU_STATE12_U              RX_PPDU_STATE12            ; // 0x430
    volatile uint32_t                              RESERVED2                  ; // 
    volatile PHY_TOP_RX_PPDU_STATE14_U              RX_PPDU_STATE14            ; // 0x438
    volatile PHY_TOP_RX_PPDU_STATE15_U              RX_PPDU_STATE15            ; // 0x43c
    volatile PHY_TOP_RX_PPDU_STATE16_U              RX_PPDU_STATE16            ; // 0x440
    volatile uint32_t                              RESERVED3[111]             ; // 
    volatile PHY_TOP_PHY_TEST_MD00_U                PHY_TEST_MD00              ; // 0x600
    volatile PHY_TOP_PHY_TEST_MD01_U                PHY_TEST_MD01              ; // 0x604
    volatile PHY_TOP_PHY_TEST_MD02_U                PHY_TEST_MD02              ; // 0x608
    volatile PHY_TOP_PHY_TEST_MD03_U                PHY_TEST_MD03              ; // 0x60c
    volatile PHY_TOP_PHY_TEST_MD04_U                PHY_TEST_MD04              ; // 0x610
    volatile PHY_TOP_PHY_TEST_MD05_U                PHY_TEST_MD05              ; // 0x614
    volatile uint32_t                              RESERVED4[6]               ; // 
    volatile PHY_TOP_PHY_SIM_TRX_MD_U               PHY_SIM_TRX_MD             ; // 0x630
    volatile uint32_t                              RESERVED5[115]             ; // 
    volatile PHY_TOP_PHY_RXDBE00_U                  PHY_RXDBE00                ; // 0x800
    volatile PHY_TOP_PHY_RXDBE01_U                  PHY_RXDBE01                ; // 0x804
    volatile uint32_t                              RESERVED6[510]             ; // 
    volatile PHY_TOP_PHY_TOPIF_CLK_GEN0_U           PHY_TOPIF_CLK_GEN0         ; // 0x1000
    volatile PHY_TOP_PHY_TOPIF_CLK_GEN1_U           PHY_TOPIF_CLK_GEN1         ; // 0x1004
    volatile PHY_TOP_PHY_TOPIF_CLK_GEN2_U           PHY_TOPIF_CLK_GEN2         ; // 0x1008
    volatile PHY_TOP_PHY_TOPIF_CLK_GEN3_U           PHY_TOPIF_CLK_GEN3         ; // 0x100c
    volatile PHY_TOP_PHY_TOPIF_CLK_GEN4_U           PHY_TOPIF_CLK_GEN4         ; // 0x1010
    volatile PHY_TOP_PHY_TOPIF_CLK_GEN5_U           PHY_TOPIF_CLK_GEN5         ; // 0x1014
    volatile uint32_t                              RESERVED7[58]              ; // 
    volatile PHY_TOP_PHY_TOPIF_TXFIFO0_U            PHY_TOPIF_TXFIFO0          ; // 0x1100
    volatile PHY_TOP_PHY_TOPIF_TXFIFO1_U            PHY_TOPIF_TXFIFO1          ; // 0x1104
    volatile PHY_TOP_PHY_TOPIF_TXFIFO2_U            PHY_TOPIF_TXFIFO2          ; // 0x1108
    volatile PHY_TOP_PHY_TOPIF_TXFIFO3_U            PHY_TOPIF_TXFIFO3          ; // 0x110c
    volatile PHY_TOP_PHY_TOPIF_TXFIFO4_U            PHY_TOPIF_TXFIFO4          ; // 0x1110
    volatile uint32_t                              RESERVED8[23]              ; // 
    volatile PHY_TOP_PHY_TOPIF_LOOPBACK_U           PHY_TOPIF_LOOPBACK         ; // 0x1170
    volatile uint32_t                              RESERVED9[3]               ; // 
    volatile PHY_TOP_PHY_TOPIF_CONFIG0_U            PHY_TOPIF_CONFIG0          ; // 0x1180
    volatile uint32_t                              RESERVED10[7]              ; // 
    volatile PHY_TOP_PHY_TOPIF_RFCTRL_U             PHY_TOPIF_RFCTRL           ; // 0x11a0
    volatile uint32_t                              RESERVED11[3]              ; // 
    volatile PHY_TOP_PHY_TOPIF_VMACCFG0_U           PHY_TOPIF_VMACCFG0         ; // 0x11b0
    volatile PHY_TOP_PHY_TOPIF_VMACCFG1_U           PHY_TOPIF_VMACCFG1         ; // 0x11b4
    volatile PHY_TOP_PHY_TOPIF_VMACCFG2_U           PHY_TOPIF_VMACCFG2         ; // 0x11b8
    volatile PHY_TOP_PHY_TOPIF_VMACCFG3_U           PHY_TOPIF_VMACCFG3         ; // 0x11bc
    volatile PHY_TOP_PHY_TOPIF_VMACCFG4_U           PHY_TOPIF_VMACCFG4         ; // 0x11c0
    volatile PHY_TOP_PHY_TOPIF_VMACCFG5_U           PHY_TOPIF_VMACCFG5         ; // 0x11c4
    volatile PHY_TOP_PHY_TOPIF_VMACCFG6_U           PHY_TOPIF_VMACCFG6         ; // 0x11c8
    volatile PHY_TOP_PHY_TOPIF_VMACCFG7_U           PHY_TOPIF_VMACCFG7         ; // 0x11cc
    volatile PHY_TOP_PHY_TOPIF_VMACCFG8_U           PHY_TOPIF_VMACCFG8         ; // 0x11d0
    volatile PHY_TOP_PHY_TOPIF_VMACCFG9_U           PHY_TOPIF_VMACCFG9         ; // 0x11d4
    volatile PHY_TOP_PHY_TOPIF_VMACCFG10_U          PHY_TOPIF_VMACCFG10        ; // 0x11d8
    volatile PHY_TOP_PHY_TOPIF_VMACCFG11_U          PHY_TOPIF_VMACCFG11        ; // 0x11dc
    volatile PHY_TOP_PHY_TOPIF_VMACCFG12_U          PHY_TOPIF_VMACCFG12        ; // 0x11e0
    volatile PHY_TOP_PHY_TOPIF_VMACCFG13_U          PHY_TOPIF_VMACCFG13        ; // 0x11e4
} PHY_TOP_Type;

#ifdef __cplusplus
}
#endif

#endif /* __REG_PHY_TOP_H__ */
