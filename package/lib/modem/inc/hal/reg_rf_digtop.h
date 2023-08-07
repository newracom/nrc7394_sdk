/*********************************************************************/
/*    Newracom Library / IP Product                                  */
/*    Product Name :                                                 */
/*    Version      :                                                 */
/*    Author       :                                                 */
/*    Update       :                                                 */
/*********************************************************************/

#ifndef __REG_RF_DIGTOP_H__
#define __REG_RF_DIGTOP_H__

#ifdef __cplusplus
extern "C"{
#endif

// 0x4004F000 register ------------------------------------
typedef struct {
    uint32_t                     adc_clk_inverse            :1 ;
    uint32_t                     dac_clk_inverse            :1 ;
    uint32_t                     RF_CLK_CTL_16or32          :1 ;
    uint32_t                     CONT_BY_RF                 :1 ;
    uint32_t                     T_SYSCLK_OFF               :1 ;
    uint32_t                     TEST_IQ_SWAP               :1 ;
    uint32_t                     reserved0                  :26;
}   RF_DIGTOP_SYS_CON;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_SYS_CON            b;
}   RF_DIGTOP_SYS_CON_U;


// 0x4004F004 register ------------------------------------
typedef struct {
    uint32_t                     EN_LNA                     :1 ;
    uint32_t                     EN_GM                      :1 ;
    uint32_t                     EN_RMX                     :1 ;
    uint32_t                     EN_RXLO                    :1 ;
    uint32_t                     EN_VGA                     :1 ;
    uint32_t                     EN_DOCDAC                  :1 ;
    uint32_t                     EN_VC                      :1 ;
    uint32_t                     EN_ADC                     :1 ;
    uint32_t                     SW_LPF                     :1 ;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     SW_AUX                     :1 ;
    uint32_t                     SW_PAD                     :1 ;
    uint32_t                     SW_TXTEST                  :1 ;
    uint32_t                     SW_EXT                     :1 ;
    uint32_t                     LNA_BAC                    :3 ;
    uint32_t                     DCDA_RAC                   :1 ;
    uint32_t                     reserved1                  :1 ;
    uint32_t                     reserved2                  :1 ;
    uint32_t                     test_gain_EN               :1 ;
    uint32_t                     trx_test_en_ovrd           :1 ;
    uint32_t                     reserved3                  :8 ;
}   RF_DIGTOP_RX_REG0;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_RX_REG0            b;
}   RF_DIGTOP_RX_REG0_U;


// 0x4004F008 register ------------------------------------
typedef struct {
    uint32_t                     RFLDO_TR                   :4 ;
    uint32_t                     RFLDO_RS                   :1 ;
    uint32_t                     RFLDO_BY                   :1 ;
    uint32_t                     RFLDO_EN_MO                :1 ;
    uint32_t                     reserved0                  :1 ;
    uint32_t                     RXRF_IBC                   :3 ;
    uint32_t                     RXRF_IBRS                  :1 ;
    uint32_t                     RMX_IBC                    :3 ;
    uint32_t                     reserved1                  :1 ;
    uint32_t                     RMX_VCMC                   :2 ;
    uint32_t                     reserved2                  :2 ;
    uint32_t                     ADC_IBC                    :2 ;
    uint32_t                     ADC_REF_IBC                :2 ;
    uint32_t                     reserved3                  :8 ;
}   RF_DIGTOP_RX_REG1;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_RX_REG1            b;
}   RF_DIGTOP_RX_REG1_U;


// 0x4004F00C register ------------------------------------
typedef struct {
    uint32_t                     VGA_BWC                    :5 ;
    uint32_t                     DA_CON                     :3 ;
    uint32_t                     RMX_BWC                    :4 ;
    uint32_t                     RLPF_GAC                   :4 ;
    uint32_t                     VGA_GAC                    :3 ;
    uint32_t                     reserved0                  :1 ;
    uint32_t                     LNA_GAC                    :3 ;
    uint32_t                     reserved1                  :9 ;
}   RF_DIGTOP_RX_REG2;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_RX_REG2            b;
}   RF_DIGTOP_RX_REG2_U;


// 0x4004F010 register ------------------------------------
typedef struct {
    uint32_t                     ADC_SAM_DLY                :3 ;
    uint32_t                     reserved0                  :1 ;
    uint32_t                     ADC_LCH_DLY                :3 ;
    uint32_t                     reserved1                  :1 ;
    uint32_t                     RLPF_BWC                   :9 ;
    uint32_t                     RLPF_Z2                    :3 ;
    uint32_t                     RLPF_Z1                    :3 ;
    uint32_t                     reserved2                  :9 ;
}   RF_DIGTOP_RX_REG3;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_RX_REG3            b;
}   RF_DIGTOP_RX_REG3_U;


// 0x4004F014 register ------------------------------------
typedef struct {
    uint32_t                     EN_PA                      :1 ;
    uint32_t                     EN_TMX                     :1 ;
    uint32_t                     EN_TXLO                    :1 ;
    uint32_t                     EN_TLPF                    :1 ;
    uint32_t                     EN_DAC                     :1 ;
    uint32_t                     EN_DA                      :1 ;
    uint32_t                     reserved0                  :2 ;
    uint32_t                     DAC_AMPC                   :2 ;
    uint32_t                     DAC_VCMC                   :2 ;
    uint32_t                     TLPF_GAC                   :4 ;
    uint32_t                     TMX_GAC                    :3 ;
    uint32_t                     reserved1                  :1 ;
    uint32_t                     PA_GAC                     :3 ;
    uint32_t                     reserved2                  :9 ;
}   RF_DIGTOP_TX_REG0;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_TX_REG0            b;
}   RF_DIGTOP_TX_REG0_U;


// 0x4004F018 register ------------------------------------
typedef struct {
    uint32_t                     PADR_IBC                   :4 ;
    uint32_t                     PA_IBC                     :4 ;
    uint32_t                     TMX_IBC                    :3 ;
    uint32_t                     TLPF_CAL_FTC               :3 ;
    uint32_t                     TLPF_1B2C                  :3 ;
    uint32_t                     TLPF_1B1C                  :3 ;
    uint32_t                     TLPF_CAL_RS                :1 ;
    uint32_t                     TLPF_RS                    :1 ;
    uint32_t                     DAC_IBC                    :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_TX_REG1;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_TX_REG1            b;
}   RF_DIGTOP_TX_REG1_U;


// 0x4004F01C register ------------------------------------
typedef struct {
    uint32_t                     PA_BAC                     :4 ;
    uint32_t                     TMX_CC                     :5 ;
    uint32_t                     TMX_GMRC                   :2 ;
    uint32_t                     TMX_GMCG                   :2 ;
    uint32_t                     TMX_IQ                     :2 ;
    uint32_t                     TMX_CMBP                   :1 ;
    uint32_t                     reserved0                  :5 ;
    uint32_t                     TLPF_RC                    :3 ;
    uint32_t                     reserved1                  :8 ;
}   RF_DIGTOP_TX_REG2;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_TX_REG2            b;
}   RF_DIGTOP_TX_REG2_U;


// 0x4004F020 register ------------------------------------
typedef struct {
    uint32_t                     EN_MMD                     :1 ;
    uint32_t                     EN_PFD_REF                 :1 ;
    uint32_t                     EN_CP                      :1 ;
    uint32_t                     EN_CP_AMP                  :1 ;
    uint32_t                     EN_LF                      :1 ;
    uint32_t                     EN_LF_MO                   :1 ;
    uint32_t                     EN_LF_MO_M                 :1 ;
    uint32_t                     EN_LF_MO_L                 :1 ;
    uint32_t                     EN_LF_MO_H                 :1 ;
    uint32_t                     EN_VCO                     :1 ;
    uint32_t                     EN_VCO_BUF                 :1 ;
    uint32_t                     FSBP0                      :1 ;
    uint32_t                     TMX_IVC                    :2 ;
    uint32_t                     TMX_ICORE                  :2 ;
    uint32_t                     TMX_LOB                    :2 ;
    uint32_t                     TMX_GMCMRC                 :2 ;
    uint32_t                     PLL_MO_SE                  :3 ;
    uint32_t                     reserved0                  :9 ;
}   RF_DIGTOP_PLL_REG0;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PLL_REG0           b;
}   RF_DIGTOP_PLL_REG0_U;


// 0x4004F024 register ------------------------------------
typedef struct {
    uint32_t                     VCOLDO_TR                  :4 ;
    uint32_t                     VCOLDO_RS                  :1 ;
    uint32_t                     VCOLDO_BY                  :1 ;
    uint32_t                     VCOLDO_EN_MO               :1 ;
    uint32_t                     reserved0                  :1 ;
    uint32_t                     CPLDO_TR                   :4 ;
    uint32_t                     CPLDO_RS                   :1 ;
    uint32_t                     CPLDO_BY                   :1 ;
    uint32_t                     CPLDO_EN_MO                :1 ;
    uint32_t                     reserved1                  :1 ;
    uint32_t                     XTLDO_TR                   :4 ;
    uint32_t                     XTLDO_RS                   :1 ;
    uint32_t                     XTLDO_BY                   :1 ;
    uint32_t                     reserved2                  :10;
}   RF_DIGTOP_PLL_REG1;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PLL_REG1           b;
}   RF_DIGTOP_PLL_REG1_U;


// 0x4004F028 register ------------------------------------
typedef struct {
    uint32_t                     XT_NCOBUF                  :3 ;
    uint32_t                     reserved0                  :1 ;
    uint32_t                     XT_PCOBUF                  :3 ;
    uint32_t                     XT_RS                      :1 ;
    uint32_t                     XT_NCO                     :4 ;
    uint32_t                     XT_PCO                     :4 ;
    uint32_t                     XT_DCXO                    :8 ;
    uint32_t                     reserved1                  :8 ;
}   RF_DIGTOP_PLL_REG2;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PLL_REG2           b;
}   RF_DIGTOP_PLL_REG2_U;


// 0x4004F02C register ------------------------------------
typedef struct {
    uint32_t                     SDM_NINT                   :6 ;
    uint32_t                     reserved0                  :2 ;
    uint32_t                     SDM_MOD_EN                 :1 ;
    uint32_t                     CHINA_BAND                 :1 ;
    uint32_t                     SDM_DI                     :1 ;
    uint32_t                     SDM_RS                     :1 ;
    uint32_t                     MMD_PW_SE                  :5 ;
    uint32_t                     reserved1                  :3 ;
    uint32_t                     MMD_MD_SE                  :1 ;
    uint32_t                     MMD_SE                     :1 ;
    uint32_t                     MMD_SYNC_ON                :1 ;
    uint32_t                     reserved2                  :9 ;
}   RF_DIGTOP_PLL_REG3;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PLL_REG3           b;
}   RF_DIGTOP_PLL_REG3_U;


// 0x4004F030 register ------------------------------------
typedef struct {
    uint32_t                     SDM_JK                     :24;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_PLL_REG4;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PLL_REG4           b;
}   RF_DIGTOP_PLL_REG4_U;


// 0x4004F034 register ------------------------------------
typedef struct {
    uint32_t                     SDM_L                      :24;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_PLL_REG5;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PLL_REG5           b;
}   RF_DIGTOP_PLL_REG5_U;


// 0x4004F038 register ------------------------------------
typedef struct {
    uint32_t                     CP_IBC                     :4 ;
    uint32_t                     CP_SNK_IBC                 :3 ;
    uint32_t                     reserved0                  :1 ;
    uint32_t                     CP_AMP_IBC                 :2 ;
    uint32_t                     reserved1                  :1 ;
    uint32_t                     CP_BI_RS                   :1 ;
    uint32_t                     PFD_DLY                    :2 ;
    uint32_t                     PFD_REF_DLY                :2 ;
    uint32_t                     PFD_REF_SE                 :1 ;
    uint32_t                     PFD_RS                     :1 ;
    uint32_t                     VCO_TP_PW_SE               :5 ;
    uint32_t                     reserved2                  :9 ;
}   RF_DIGTOP_PLL_REG6;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PLL_REG6           b;
}   RF_DIGTOP_PLL_REG6_U;


// 0x4004F03C register ------------------------------------
typedef struct {
    uint32_t                     LF_MO_HC                   :4 ;
    uint32_t                     LF_MO_LC                   :4 ;
    uint32_t                     LF_MO_MC                   :4 ;
    uint32_t                     LF_IBLE_CO                 :4 ;
    uint32_t                     LF_MO_SW                   :4 ;
    uint32_t                     reserved0                  :1 ;
    uint32_t                     LF_MOAMP_EN                :1 ;
    uint32_t                     LF_MID_FIX                 :1 ;
    uint32_t                     reserved1                  :9 ;
}   RF_DIGTOP_PLL_REG7;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PLL_REG7           b;
}   RF_DIGTOP_PLL_REG7_U;


// 0x4004F040 register ------------------------------------
typedef struct {
    uint32_t                     LF_R2C_10X                 :6 ;
    uint32_t                     reserved0                  :2 ;
    uint32_t                     LF_R2C                     :5 ;
    uint32_t                     reserved1                  :3 ;
    uint32_t                     LF_VREF_SE                 :6 ;
    uint32_t                     reserved2                  :10;
}   RF_DIGTOP_PLL_REG8;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PLL_REG8           b;
}   RF_DIGTOP_PLL_REG8_U;


// 0x4004F044 register ------------------------------------
typedef struct {
    uint32_t                     LF_C1C                     :6 ;
    uint32_t                     reserved0                  :2 ;
    uint32_t                     LF_R4C                     :5 ;
    uint32_t                     reserved1                  :3 ;
    uint32_t                     LF_R3C                     :5 ;
    uint32_t                     reserved2                  :11;
}   RF_DIGTOP_PLL_REG9;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PLL_REG9           b;
}   RF_DIGTOP_PLL_REG9_U;


// 0x4004F048 register ------------------------------------
typedef struct {
    uint32_t                     reserved0                  :1 ;
    uint32_t                     VCO_CM_RS                  :1 ;
    uint32_t                     VCO_VAR_RS                 :1 ;
    uint32_t                     VCO_IBRS                   :1 ;
    uint32_t                     LF_C4C                     :4 ;
    uint32_t                     LF_C3C                     :5 ;
    uint32_t                     reserved1                  :3 ;
    uint32_t                     LF_C2C                     :7 ;
    uint32_t                     reserved2                  :9 ;
}   RF_DIGTOP_PLL_REG10;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PLL_REG10          b;
}   RF_DIGTOP_PLL_REG10_U;


// 0x4004F04C register ------------------------------------
typedef struct {
    uint32_t                     VCO_TP_DIV                 :2 ;
    uint32_t                     VCO_BUF_SW                 :2 ;
    uint32_t                     VCO_TCOM_ICTC              :3 ;
    uint32_t                     reserved0                  :1 ;
    uint32_t                     VCO_TCOM_IPTC              :3 ;
    uint32_t                     reserved1                  :1 ;
    uint32_t                     VCO_ICTC                   :3 ;
    uint32_t                     reserved2                  :1 ;
    uint32_t                     VCO_IPTC                   :3 ;
    uint32_t                     reserved3                  :1 ;
    uint32_t                     VCO_TP_EN                  :1 ;
    uint32_t                     VCO_CB_LAT_EN              :1 ;
    uint32_t                     reserved4                  :1 ;
    uint32_t                     VCO_BUF_CC                 :1 ;
    uint32_t                     reserved5                  :8 ;
}   RF_DIGTOP_PLL_REG11;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PLL_REG11          b;
}   RF_DIGTOP_PLL_REG11_U;


// 0x4004F050 register ------------------------------------
typedef struct {
    uint32_t                     VBATCK_BWC                 :2 ;
    uint32_t                     reserved0                  :1 ;
    uint32_t                     VBATCK_EN                  :1 ;
    uint32_t                     TSEN_BWC                   :2 ;
    uint32_t                     reserved1                  :1 ;
    uint32_t                     TSEN_EN                    :1 ;
    uint32_t                     VCO_TCOM_R2C               :3 ;
    uint32_t                     reserved2                  :1 ;
    uint32_t                     VCO_TCOM_R1C               :3 ;
    uint32_t                     reserved3                  :1 ;
    uint32_t                     VCO_VAR_RC                 :3 ;
    uint32_t                     reserved4                  :1 ;
    uint32_t                     VCO_IVCO                   :3 ;
    uint32_t                     reserved5                  :9 ;
}   RF_DIGTOP_PLL_REG12;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PLL_REG12          b;
}   RF_DIGTOP_PLL_REG12_U;


// 0x4004F054 register ------------------------------------
typedef struct {
    uint32_t                     reserved0                  :4 ;
    uint32_t                     BGR_MAN_TR                 :4 ;
    uint32_t                     BGRLDO_TR                  :4 ;
    uint32_t                     BGRLDO_RS                  :1 ;
    uint32_t                     BGRLDO_BY                  :1 ;
    uint32_t                     BGRLDO_EN_MO               :1 ;
    uint32_t                     BGR_TR_SE                  :1 ;
    uint32_t                     ANALDO_TR                  :4 ;
    uint32_t                     ANALDO_RS                  :1 ;
    uint32_t                     ANALDO_BY                  :1 ;
    uint32_t                     ANALDO_EN_MO               :1 ;
    uint32_t                     reserved1                  :9 ;
}   RF_DIGTOP_MISC_REG0;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_MISC_REG0          b;
}   RF_DIGTOP_MISC_REG0_U;


// 0x4004F058 register ------------------------------------
typedef struct {
    uint32_t                     reserved0                  :8 ;
    uint32_t                     MON_SE                     :4 ;
    uint32_t                     reserved1                  :4 ;
    uint32_t                     AUXADC_SAM_DLY             :3 ;
    uint32_t                     reserved2                  :1 ;
    uint32_t                     AUXADC_LCH_DLY             :3 ;
    uint32_t                     reserved3                  :9 ;
}   RF_DIGTOP_MISC_REG1;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_MISC_REG1          b;
}   RF_DIGTOP_MISC_REG1_U;


// 0x4004F05C register ------------------------------------
typedef struct {
    uint32_t                     interp_cal_mode            :1 ;
    uint32_t                     adc_dac_test               :1 ;
    uint32_t                     reserved0                  :2 ;
    uint32_t                     adc_dump_mux               :2 ;
    uint32_t                     adc_dump_on                :1 ;
    uint32_t                     decim_clock_down           :1 ;
    uint32_t                     decim_mode                 :1 ;
    uint32_t                     adc_dump_doc_sync          :1 ;
    uint32_t                     reserved1                  :22;
}   RF_DIGTOP_DIG_REG0;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DIG_REG0           b;
}   RF_DIGTOP_DIG_REG0_U;


// 0x4004F060 register ------------------------------------
typedef struct {
    uint32_t                     ft_capcont_bw0             :5 ;
    uint32_t                     ft_capcont_bw1             :5 ;
    uint32_t                     ft_capcont_bw2             :5 ;
    uint32_t                     reserved0                  :17;
}   RF_DIGTOP_DIG_REG1;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DIG_REG1           b;
}   RF_DIGTOP_DIG_REG1_U;


// 0x4004F064 register ------------------------------------
typedef struct {
    uint32_t                     reserved0                  :4 ;
    uint32_t                     VCOCAL_C_INI               :8 ;
    uint32_t                     VCOCAL_TMR                 :3 ;
    uint32_t                     reserved1                  :1 ;
    uint32_t                     VCOCAL_FRZ                 :1 ;
    uint32_t                     VCOCAL_MD                  :1 ;
    uint32_t                     reserved2                  :1 ;
    uint32_t                     VCOCAL_RSN                 :1 ;
    uint32_t                     reserved3                  :12;
}   RF_DIGTOP_CAL_REG0;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_CAL_REG0           b;
}   RF_DIGTOP_CAL_REG0_U;


// 0x4004F068 register ------------------------------------
typedef struct {
    uint32_t                     REG1A_1_0                  :2 ;
    uint32_t                     tx_lpf_cal_done            :1 ;
    uint32_t                     REG1A_3                    :1 ;
    uint32_t                     VCOCAL_C_CD                :8 ;
    uint32_t                     REG1A_14_12                :3 ;
    uint32_t                     VCOCAL_THRES_SE            :1 ;
    uint32_t                     REG1A_23_16                :8 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_CAL_REG1;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_CAL_REG1           b;
}   RF_DIGTOP_CAL_REG1_U;


// 0x4004F06C register ------------------------------------
typedef struct {
    uint32_t                     ft_bw_mode                 :2 ;
    uint32_t                     reserved0                  :2 ;
    uint32_t                     ft_under_bound             :4 ;
    uint32_t                     ft_upper_bound             :4 ;
    uint32_t                     ft_ana_delay               :4 ;
    uint32_t                     ft_code_offset             :4 ;
    uint32_t                     ft_external                :1 ;
    uint32_t                     ft_code_offset_sign        :1 ;
    uint32_t                     TLPF_CAL_EN                :1 ;
    uint32_t                     reserved1                  :9 ;
}   RF_DIGTOP_CAL_REG2;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_CAL_REG2           b;
}   RF_DIGTOP_CAL_REG2_U;


// 0x4004F070 register ------------------------------------
typedef struct {
    uint32_t                     ft_extcap_bw0              :5 ;
    uint32_t                     ft_extcap_bw1              :5 ;
    uint32_t                     ft_extcap_bw2              :5 ;
    uint32_t                     reserved0                  :8 ;
    uint32_t                     ft_cal_en                  :1 ;
    uint32_t                     reserved1                  :8 ;
}   RF_DIGTOP_CAL_REG3;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_CAL_REG3           b;
}   RF_DIGTOP_CAL_REG3_U;


// 0x4004F074 register ------------------------------------
typedef struct {
    uint32_t                     test_tone_on               :1 ;
    uint32_t                     nco_0_only                 :1 ;
    uint32_t                     nco_dac_test_on            :1 ;
    uint32_t                     test_tone_iq_swap          :1 ;
    uint32_t                     reserved0                  :19;
    uint32_t                     SW_ADCAL                   :1 ;
    uint32_t                     reserved1                  :8 ;
}   RF_DIGTOP_ADCAL_REG0;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_ADCAL_REG0         b;
}   RF_DIGTOP_ADCAL_REG0_U;


// 0x4004F078 register ------------------------------------
typedef struct {
    uint32_t                     adc_dump_size              :15;
    uint32_t                     reserved0                  :17;
}   RF_DIGTOP_ADCAL_REG1;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_ADCAL_REG1         b;
}   RF_DIGTOP_ADCAL_REG1_U;


// 0x4004F07C register ------------------------------------
typedef struct {
    uint32_t                     nco_neg_gain               :5 ;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     nco_1_fcw                  :5 ;
    uint32_t                     reserved1                  :3 ;
    uint32_t                     nco_0_fcw                  :5 ;
    uint32_t                     reserved2                  :11;
}   RF_DIGTOP_ADCAL_REG2;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_ADCAL_REG2         b;
}   RF_DIGTOP_ADCAL_REG2_U;


// 0x4004F080 register ------------------------------------
typedef struct {
    uint32_t                     txgain_mac_con             :1 ;
    uint32_t                     dist_mea_use               :1 ;
    uint32_t                     reserved0                  :30;
}   RF_DIGTOP_ADCAL_REG3;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_ADCAL_REG3         b;
}   RF_DIGTOP_ADCAL_REG3_U;


// 0x4004F084 register ------------------------------------
typedef struct {
    uint32_t                     dist_meas_tr_nxtcnt        :14;
    uint32_t                     reserved0                  :2 ;
    uint32_t                     dist_meas_tr_pos           :3 ;
    uint32_t                     reserved1                  :13;
}   RF_DIGTOP_ADCAL_REG4;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_ADCAL_REG4         b;
}   RF_DIGTOP_ADCAL_REG4_U;


// 0x4004F088 register ------------------------------------
typedef struct {
    uint32_t                     dist_meas_tr_pos           :15;
    uint32_t                     reserved0                  :17;
}   RF_DIGTOP_ADCAL_REG5;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_ADCAL_REG5         b;
}   RF_DIGTOP_ADCAL_REG5_U;


// 0x4004F0D0 register ------------------------------------
typedef struct {
    uint32_t                     sar_test_rnd               :1 ;
    uint32_t                     reserved0                  :31;
}   RF_DIGTOP_ADCAL_REG23;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_ADCAL_REG23        b;
}   RF_DIGTOP_ADCAL_REG23_U;


// 0x4004F0D4 register ------------------------------------
typedef struct {
    uint32_t                     TXCAL_CC                   :3 ;
    uint32_t                     reserved0                  :1 ;
    uint32_t                     TXCAL_RC                   :3 ;
    uint32_t                     reserved1                  :5 ;
    uint32_t                     TXCAL_IBC                  :3 ;
    uint32_t                     reserved2                  :1 ;
    uint32_t                     TXCAL_RS                   :1 ;
    uint32_t                     TXCAL_IB_EN                :1 ;
    uint32_t                     TXCAL_EN                   :1 ;
    uint32_t                     TXPD_EN                    :1 ;
    uint32_t                     LBATT_CO                   :2 ;
    uint32_t                     TSSI_IPA_SE                :1 ;
    uint32_t                     TMXPD_EN                   :1 ;
    uint32_t                     reserved3                  :8 ;
}   RF_DIGTOP_CAL_REG4;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_CAL_REG4           b;
}   RF_DIGTOP_CAL_REG4_U;


// 0x4004F0D8 register ------------------------------------
typedef struct {
    uint32_t                     reserved0                  :4 ;
    uint32_t                     TSSI_RC                    :3 ;
    uint32_t                     reserved1                  :1 ;
    uint32_t                     TSSI_IBC                   :3 ;
    uint32_t                     reserved2                  :9 ;
    uint32_t                     TSSI_RS                    :1 ;
    uint32_t                     TSSI_IB_EN                 :1 ;
    uint32_t                     TSSI_EN                    :1 ;
    uint32_t                     TSSI_OUT_SE                :1 ;
    uint32_t                     reserved3                  :8 ;
}   RF_DIGTOP_CAL_REG5;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_CAL_REG5           b;
}   RF_DIGTOP_CAL_REG5_U;


// 0x4004F0DC register ------------------------------------
typedef struct {
    uint32_t                     VCTU_COUNT                 :10;
    uint32_t                     reserved0                  :2 ;
    uint32_t                     VCTU_TRM                   :6 ;
    uint32_t                     reserved1                  :2 ;
    uint32_t                     VCTU_OVR                   :1 ;
    uint32_t                     XT_VCTU_CKEN               :1 ;
    uint32_t                     VCTU_EN                    :1 ;
    uint32_t                     reserved2                  :9 ;
}   RF_DIGTOP_CAL_REG6;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_CAL_REG6           b;
}   RF_DIGTOP_CAL_REG6_U;


// 0x4004F0E0 register ------------------------------------
typedef struct {
    uint32_t                     reserved0                  :16;
    uint32_t                     VCTU_TRSPI                 :6 ;
    uint32_t                     reserved1                  :1 ;
    uint32_t                     VCTU_ENSPI                 :1 ;
    uint32_t                     reserved2                  :8 ;
}   RF_DIGTOP_CAL_REG7;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_CAL_REG7           b;
}   RF_DIGTOP_CAL_REG7_U;


// 0x4004F0E4 register ------------------------------------
typedef struct {
    uint32_t                     ana_delay                  :8 ;
    uint32_t                     doc_delay                  :8 ;
    uint32_t                     spi_mea_dc_period          :4 ;
    uint32_t                     reserved0                  :12;
}   RF_DIGTOP_DOCAL_REG0;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG0         b;
}   RF_DIGTOP_DOCAL_REG0_U;


// 0x4004F0E8 register ------------------------------------
typedef struct {
    uint32_t                     RX_HP3_pole                :4 ;
    uint32_t                     RX_HP2_pole                :4 ;
    uint32_t                     RX_HP1_pole                :4 ;
    uint32_t                     auto_cal_pole              :4 ;
    uint32_t                     reserved0                  :16;
}   RF_DIGTOP_DOCAL_REG1;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG1         b;
}   RF_DIGTOP_DOCAL_REG1_U;


// 0x4004F0EC register ------------------------------------
typedef struct {
    uint32_t                     bw                         :2 ;
    uint32_t                     reserved0                  :2 ;
    uint32_t                     start_iter_num             :3 ;
    uint32_t                     reserved1                  :1 ;
    uint32_t                     doc_dac_code_lookup_use    :1 ;
    uint32_t                     doc_lut_override           :1 ;
    uint32_t                     reserved2                  :2 ;
    uint32_t                     doc_bypass                 :1 ;
    uint32_t                     auto_cal_start             :1 ;
    uint32_t                     reserved3                  :18;
}   RF_DIGTOP_DOCAL_REG2;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG2         b;
}   RF_DIGTOP_DOCAL_REG2_U;


// 0x4004F0F0 register ------------------------------------
typedef struct {
    uint32_t                     doc_dac_codeq_test         :7 ;
    uint32_t                     doc_dac_codei_test         :7 ;
    uint32_t                     doc_dac_code_test_en       :1 ;
    uint32_t                     reserved0                  :1 ;
    uint32_t                     dc_sign_inverse            :1 ;
    uint32_t                     reserved1                  :15;
}   RF_DIGTOP_DOCAL_REG3;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG3         b;
}   RF_DIGTOP_DOCAL_REG3_U;


// 0x4004F0F4 register ------------------------------------
typedef struct {
    uint32_t                     spi_doc_code_wr            :20;
    uint32_t                     reserved0                  :12;
}   RF_DIGTOP_DOCAL_REG4;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG4         b;
}   RF_DIGTOP_DOCAL_REG4_U;


// 0x4004F0F8 register ------------------------------------
typedef struct {
    uint32_t                     DCDA_COQ                   :7 ;
    uint32_t                     reserved0                  :1 ;
    uint32_t                     DCDA_COI                   :7 ;
    uint32_t                     reserved1                  :1 ;
    uint32_t                     DOC_CODEQ_EN_DIG           :1 ;
    uint32_t                     DOC_CODEI_EN_DIG           :1 ;
    uint32_t                     reserved2                  :2 ;
    uint32_t                     adc_dump_done              :1 ;
    uint32_t                     reserved3                  :2 ;
    uint32_t                     auto_cal_finish            :1 ;
    uint32_t                     reserved4                  :8 ;
}   RF_DIGTOP_DOCAL_REG5;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG5         b;
}   RF_DIGTOP_DOCAL_REG5_U;


// 0x4004F0FC register ------------------------------------
typedef struct {
    uint32_t                     reserved0                  :16;
    uint32_t                     RXCAL_ATT                  :2 ;
    uint32_t                     reserved1                  :3 ;
    uint32_t                     RXCAL_TMXSW                :1 ;
    uint32_t                     RXCAL_DASW                 :1 ;
    uint32_t                     RXCAL_EN                   :1 ;
    uint32_t                     reserved2                  :8 ;
}   RF_DIGTOP_CAL_REG8;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_CAL_REG8           b;
}   RF_DIGTOP_CAL_REG8_U;


// 0x4004F100 register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD00                  :10;
    uint32_t                     REG40_11_10                :2 ;
    uint32_t                     GAIN_CD01                  :10;
    uint32_t                     REG40_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG6;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG6         b;
}   RF_DIGTOP_DOCAL_REG6_U;


// 0x4004F104 register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD02                  :10;
    uint32_t                     REG41_11_10                :2 ;
    uint32_t                     GAIN_CD03                  :10;
    uint32_t                     REG41_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG7;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG7         b;
}   RF_DIGTOP_DOCAL_REG7_U;


// 0x4004F108 register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD04                  :10;
    uint32_t                     REG42_11_10                :2 ;
    uint32_t                     GAIN_CD05                  :10;
    uint32_t                     REG42_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG8;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG8         b;
}   RF_DIGTOP_DOCAL_REG8_U;


// 0x4004F10C register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD06                  :10;
    uint32_t                     REG43_11_10                :2 ;
    uint32_t                     GAIN_CD07                  :10;
    uint32_t                     REG43_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG9;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG9         b;
}   RF_DIGTOP_DOCAL_REG9_U;


// 0x4004F110 register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD08                  :10;
    uint32_t                     REG44_11_10                :2 ;
    uint32_t                     GAIN_CD09                  :10;
    uint32_t                     REG44_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG10;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG10        b;
}   RF_DIGTOP_DOCAL_REG10_U;


// 0x4004F114 register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD10                  :10;
    uint32_t                     REG45_11_10                :2 ;
    uint32_t                     GAIN_CD11                  :10;
    uint32_t                     REG45_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG11;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG11        b;
}   RF_DIGTOP_DOCAL_REG11_U;


// 0x4004F118 register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD12                  :10;
    uint32_t                     REG4A_11_10                :2 ;
    uint32_t                     GAIN_CD13                  :10;
    uint32_t                     REG4A_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG12;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG12        b;
}   RF_DIGTOP_DOCAL_REG12_U;


// 0x4004F11C register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD14                  :10;
    uint32_t                     REG4B_11_10                :2 ;
    uint32_t                     GAIN_CD15                  :10;
    uint32_t                     REG4B_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG13;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG13        b;
}   RF_DIGTOP_DOCAL_REG13_U;


// 0x4004F120 register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD16                  :10;
    uint32_t                     REG4C_11_10                :2 ;
    uint32_t                     GAIN_CD17                  :10;
    uint32_t                     REG4C_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG14;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG14        b;
}   RF_DIGTOP_DOCAL_REG14_U;


// 0x4004F124 register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD18                  :10;
    uint32_t                     REG4D_11_10                :2 ;
    uint32_t                     GAIN_CD19                  :10;
    uint32_t                     REG4D_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG15;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG15        b;
}   RF_DIGTOP_DOCAL_REG15_U;


// 0x4004F128 register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD20                  :10;
    uint32_t                     REG4A_11_10                :2 ;
    uint32_t                     GAIN_CD21                  :10;
    uint32_t                     REG4A_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG16;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG16        b;
}   RF_DIGTOP_DOCAL_REG16_U;


// 0x4004F12C register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD22                  :10;
    uint32_t                     REG4B_11_10                :2 ;
    uint32_t                     GAIN_CD23                  :10;
    uint32_t                     REG4B_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG17;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG17        b;
}   RF_DIGTOP_DOCAL_REG17_U;


// 0x4004F130 register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD24                  :10;
    uint32_t                     REG4C_11_10                :2 ;
    uint32_t                     GAIN_CD25                  :10;
    uint32_t                     REG4C_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG18;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG18        b;
}   RF_DIGTOP_DOCAL_REG18_U;


// 0x4004F134 register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD26                  :10;
    uint32_t                     REG4D_11_10                :2 ;
    uint32_t                     GAIN_CD27                  :10;
    uint32_t                     REG4D_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG19;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG19        b;
}   RF_DIGTOP_DOCAL_REG19_U;


// 0x4004F138 register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD28                  :10;
    uint32_t                     REG4E_11_10                :2 ;
    uint32_t                     GAIN_CD29                  :10;
    uint32_t                     REG4E_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG20;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG20        b;
}   RF_DIGTOP_DOCAL_REG20_U;


// 0x4004F13C register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD30                  :10;
    uint32_t                     REG4F_11_10                :2 ;
    uint32_t                     GAIN_CD31                  :10;
    uint32_t                     REG4F_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG21;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG21        b;
}   RF_DIGTOP_DOCAL_REG21_U;


// 0x4004F140 register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD32                  :10;
    uint32_t                     REG50_11_10                :2 ;
    uint32_t                     GAIN_CD33                  :10;
    uint32_t                     REG50_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG22;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG22        b;
}   RF_DIGTOP_DOCAL_REG22_U;


// 0x4004F144 register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD34                  :10;
    uint32_t                     REG51_11_10                :2 ;
    uint32_t                     GAIN_CD35                  :10;
    uint32_t                     REG51_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG23;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG23        b;
}   RF_DIGTOP_DOCAL_REG23_U;


// 0x4004F148 register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD36                  :10;
    uint32_t                     REG52_11_10                :2 ;
    uint32_t                     GAIN_CD37                  :10;
    uint32_t                     REG52_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG24;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG24        b;
}   RF_DIGTOP_DOCAL_REG24_U;


// 0x4004F14C register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD38                  :10;
    uint32_t                     REG53_11_10                :2 ;
    uint32_t                     GAIN_CD39                  :10;
    uint32_t                     REG53_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG25;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG25        b;
}   RF_DIGTOP_DOCAL_REG25_U;


// 0x4004F150 register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD40                  :10;
    uint32_t                     REG54_11_10                :2 ;
    uint32_t                     GAIN_CD41                  :10;
    uint32_t                     REG54_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG26;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG26        b;
}   RF_DIGTOP_DOCAL_REG26_U;


// 0x4004F154 register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD42                  :10;
    uint32_t                     REG55_11_10                :2 ;
    uint32_t                     GAIN_CD43                  :10;
    uint32_t                     REG55_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG27;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG27        b;
}   RF_DIGTOP_DOCAL_REG27_U;


// 0x4004F158 register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD44                  :10;
    uint32_t                     REG56_11_10                :2 ;
    uint32_t                     GAIN_CD45                  :10;
    uint32_t                     REG56_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG28;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG28        b;
}   RF_DIGTOP_DOCAL_REG28_U;


// 0x4004F15C register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD46                  :10;
    uint32_t                     REG57_11_10                :2 ;
    uint32_t                     GAIN_CD47                  :10;
    uint32_t                     REG57_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG29;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG29        b;
}   RF_DIGTOP_DOCAL_REG29_U;


// 0x4004F160 register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD48                  :10;
    uint32_t                     REG58_11_10                :2 ;
    uint32_t                     GAIN_CD49                  :10;
    uint32_t                     REG58_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG30;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG30        b;
}   RF_DIGTOP_DOCAL_REG30_U;


// 0x4004F164 register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD50                  :10;
    uint32_t                     REG59_11_10                :2 ;
    uint32_t                     GAIN_CD51                  :10;
    uint32_t                     REG59_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG31;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG31        b;
}   RF_DIGTOP_DOCAL_REG31_U;


// 0x4004F168 register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD52                  :10;
    uint32_t                     REG5A_11_10                :2 ;
    uint32_t                     GAIN_CD53                  :10;
    uint32_t                     REG5A_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG32;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG32        b;
}   RF_DIGTOP_DOCAL_REG32_U;


// 0x4004F16C register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD54                  :10;
    uint32_t                     REG5B_11_10                :2 ;
    uint32_t                     GAIN_CD55                  :10;
    uint32_t                     REG5B_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG33;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG33        b;
}   RF_DIGTOP_DOCAL_REG33_U;


// 0x4004F170 register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD56                  :10;
    uint32_t                     REG5C_11_10                :2 ;
    uint32_t                     GAIN_CD57                  :10;
    uint32_t                     REG5C_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG34;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG34        b;
}   RF_DIGTOP_DOCAL_REG34_U;


// 0x4004F174 register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD58                  :10;
    uint32_t                     REG5D_11_10                :2 ;
    uint32_t                     GAIN_CD59                  :10;
    uint32_t                     REG5D_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG35;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG35        b;
}   RF_DIGTOP_DOCAL_REG35_U;


// 0x4004F178 register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD60                  :10;
    uint32_t                     REG5E_11_10                :2 ;
    uint32_t                     GAIN_CD61                  :10;
    uint32_t                     REG5E_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG36;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG36        b;
}   RF_DIGTOP_DOCAL_REG36_U;


// 0x4004F17C register ------------------------------------
typedef struct {
    uint32_t                     GAIN_CD62                  :10;
    uint32_t                     REG5F_11_10                :2 ;
    uint32_t                     GAIN_CD63                  :10;
    uint32_t                     REG5F_23_22                :2 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG37;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG37        b;
}   RF_DIGTOP_DOCAL_REG37_U;


// 0x4004F180 register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i00               :6 ;
    uint32_t                     dac_code_q00               :6 ;
    uint32_t                     dac_code_i01               :6 ;
    uint32_t                     dac_code_q01               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG38;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG38        b;
}   RF_DIGTOP_DOCAL_REG38_U;


// 0x4004F184 register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i02               :6 ;
    uint32_t                     dac_code_q02               :6 ;
    uint32_t                     dac_code_i03               :6 ;
    uint32_t                     dac_code_q03               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG39;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG39        b;
}   RF_DIGTOP_DOCAL_REG39_U;


// 0x4004F188 register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i04               :6 ;
    uint32_t                     dac_code_q04               :6 ;
    uint32_t                     dac_code_i05               :6 ;
    uint32_t                     dac_code_q05               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG40;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG40        b;
}   RF_DIGTOP_DOCAL_REG40_U;


// 0x4004F18C register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i06               :6 ;
    uint32_t                     dac_code_q06               :6 ;
    uint32_t                     dac_code_i07               :6 ;
    uint32_t                     dac_code_q07               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG41;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG41        b;
}   RF_DIGTOP_DOCAL_REG41_U;


// 0x4004F190 register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i08               :6 ;
    uint32_t                     dac_code_q08               :6 ;
    uint32_t                     dac_code_i09               :6 ;
    uint32_t                     dac_code_q09               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG42;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG42        b;
}   RF_DIGTOP_DOCAL_REG42_U;


// 0x4004F194 register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i10               :6 ;
    uint32_t                     dac_code_q10               :6 ;
    uint32_t                     dac_code_i11               :6 ;
    uint32_t                     dac_code_q11               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG43;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG43        b;
}   RF_DIGTOP_DOCAL_REG43_U;


// 0x4004F198 register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i12               :6 ;
    uint32_t                     dac_code_q12               :6 ;
    uint32_t                     dac_code_i13               :6 ;
    uint32_t                     dac_code_q13               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG44;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG44        b;
}   RF_DIGTOP_DOCAL_REG44_U;


// 0x4004F19C register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i14               :6 ;
    uint32_t                     dac_code_q14               :6 ;
    uint32_t                     dac_code_i15               :6 ;
    uint32_t                     dac_code_q15               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG45;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG45        b;
}   RF_DIGTOP_DOCAL_REG45_U;


// 0x4004F1A0 register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i16               :6 ;
    uint32_t                     dac_code_q16               :6 ;
    uint32_t                     dac_code_i17               :6 ;
    uint32_t                     dac_code_q17               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG46;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG46        b;
}   RF_DIGTOP_DOCAL_REG46_U;


// 0x4004F1A4 register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i18               :6 ;
    uint32_t                     dac_code_q18               :6 ;
    uint32_t                     dac_code_i19               :6 ;
    uint32_t                     dac_code_q19               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG47;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG47        b;
}   RF_DIGTOP_DOCAL_REG47_U;


// 0x4004F1A8 register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i20               :6 ;
    uint32_t                     dac_code_q20               :6 ;
    uint32_t                     dac_code_i21               :6 ;
    uint32_t                     dac_code_q21               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG48;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG48        b;
}   RF_DIGTOP_DOCAL_REG48_U;


// 0x4004F1AC register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i22               :6 ;
    uint32_t                     dac_code_q22               :6 ;
    uint32_t                     dac_code_i23               :6 ;
    uint32_t                     dac_code_q23               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG49;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG49        b;
}   RF_DIGTOP_DOCAL_REG49_U;


// 0x4004F1B0 register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i24               :6 ;
    uint32_t                     dac_code_q24               :6 ;
    uint32_t                     dac_code_i25               :6 ;
    uint32_t                     dac_code_q25               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG50;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG50        b;
}   RF_DIGTOP_DOCAL_REG50_U;


// 0x4004F1B4 register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i26               :6 ;
    uint32_t                     dac_code_q26               :6 ;
    uint32_t                     dac_code_i27               :6 ;
    uint32_t                     dac_code_q27               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG51;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG51        b;
}   RF_DIGTOP_DOCAL_REG51_U;


// 0x4004F1B8 register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i28               :6 ;
    uint32_t                     dac_code_q28               :6 ;
    uint32_t                     dac_code_i29               :6 ;
    uint32_t                     dac_code_q29               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG52;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG52        b;
}   RF_DIGTOP_DOCAL_REG52_U;


// 0x4004F1BC register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i30               :6 ;
    uint32_t                     dac_code_q30               :6 ;
    uint32_t                     dac_code_i31               :6 ;
    uint32_t                     dac_code_q31               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG53;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG53        b;
}   RF_DIGTOP_DOCAL_REG53_U;


// 0x4004F1C0 register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i32               :6 ;
    uint32_t                     dac_code_q32               :6 ;
    uint32_t                     dac_code_i33               :6 ;
    uint32_t                     dac_code_q33               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG54;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG54        b;
}   RF_DIGTOP_DOCAL_REG54_U;


// 0x4004F1C4 register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i34               :6 ;
    uint32_t                     dac_code_q34               :6 ;
    uint32_t                     dac_code_i35               :6 ;
    uint32_t                     dac_code_q35               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG55;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG55        b;
}   RF_DIGTOP_DOCAL_REG55_U;


// 0x4004F1C8 register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i36               :6 ;
    uint32_t                     dac_code_q36               :6 ;
    uint32_t                     dac_code_i37               :6 ;
    uint32_t                     dac_code_q37               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG56;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG56        b;
}   RF_DIGTOP_DOCAL_REG56_U;


// 0x4004F1CC register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i38               :6 ;
    uint32_t                     dac_code_q38               :6 ;
    uint32_t                     dac_code_i39               :6 ;
    uint32_t                     dac_code_q39               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG57;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG57        b;
}   RF_DIGTOP_DOCAL_REG57_U;


// 0x4004F1D0 register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i40               :6 ;
    uint32_t                     dac_code_q40               :6 ;
    uint32_t                     dac_code_i41               :6 ;
    uint32_t                     dac_code_q41               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG58;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG58        b;
}   RF_DIGTOP_DOCAL_REG58_U;


// 0x4004F1D4 register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i42               :6 ;
    uint32_t                     dac_code_q42               :6 ;
    uint32_t                     dac_code_i43               :6 ;
    uint32_t                     dac_code_q43               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG59;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG59        b;
}   RF_DIGTOP_DOCAL_REG59_U;


// 0x4004F1D8 register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i44               :6 ;
    uint32_t                     dac_code_q44               :6 ;
    uint32_t                     dac_code_i45               :6 ;
    uint32_t                     dac_code_q45               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG60;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG60        b;
}   RF_DIGTOP_DOCAL_REG60_U;


// 0x4004F1DC register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i46               :6 ;
    uint32_t                     dac_code_q46               :6 ;
    uint32_t                     dac_code_i47               :6 ;
    uint32_t                     dac_code_q47               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG61;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG61        b;
}   RF_DIGTOP_DOCAL_REG61_U;


// 0x4004F1E0 register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i48               :6 ;
    uint32_t                     dac_code_q48               :6 ;
    uint32_t                     dac_code_i49               :6 ;
    uint32_t                     dac_code_q49               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG62;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG62        b;
}   RF_DIGTOP_DOCAL_REG62_U;


// 0x4004F1E4 register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i50               :6 ;
    uint32_t                     dac_code_q50               :6 ;
    uint32_t                     dac_code_i51               :6 ;
    uint32_t                     dac_code_q51               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG63;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG63        b;
}   RF_DIGTOP_DOCAL_REG63_U;


// 0x4004F1E8 register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i52               :6 ;
    uint32_t                     dac_code_q52               :6 ;
    uint32_t                     dac_code_i53               :6 ;
    uint32_t                     dac_code_q53               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG64;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG64        b;
}   RF_DIGTOP_DOCAL_REG64_U;


// 0x4004F1EC register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i54               :6 ;
    uint32_t                     dac_code_q54               :6 ;
    uint32_t                     dac_code_i55               :6 ;
    uint32_t                     dac_code_q55               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG65;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG65        b;
}   RF_DIGTOP_DOCAL_REG65_U;


// 0x4004F1F0 register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i56               :6 ;
    uint32_t                     dac_code_q56               :6 ;
    uint32_t                     dac_code_i57               :6 ;
    uint32_t                     dac_code_q57               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG66;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG66        b;
}   RF_DIGTOP_DOCAL_REG66_U;


// 0x4004F1F4 register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i58               :6 ;
    uint32_t                     dac_code_q58               :6 ;
    uint32_t                     dac_code_i59               :6 ;
    uint32_t                     dac_code_q59               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG67;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG67        b;
}   RF_DIGTOP_DOCAL_REG67_U;


// 0x4004F1F8 register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i60               :6 ;
    uint32_t                     dac_code_q60               :6 ;
    uint32_t                     dac_code_i61               :6 ;
    uint32_t                     dac_code_q61               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG68;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG68        b;
}   RF_DIGTOP_DOCAL_REG68_U;


// 0x4004F1FC register ------------------------------------
typedef struct {
    uint32_t                     dac_code_i62               :6 ;
    uint32_t                     dac_code_q62               :6 ;
    uint32_t                     dac_code_i63               :6 ;
    uint32_t                     dac_code_q63               :6 ;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_DOCAL_REG69;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DOCAL_REG69        b;
}   RF_DIGTOP_DOCAL_REG69_U;


// 0x4004F200 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a00             :12;
    uint32_t                     bb_dpd_lut_a01             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A00;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A00     b;
}   RF_DIGTOP_BB_DPD_LUT_A00_U;


// 0x4004F204 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a02             :12;
    uint32_t                     bb_dpd_lut_a03             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A01;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A01     b;
}   RF_DIGTOP_BB_DPD_LUT_A01_U;


// 0x4004F208 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a04             :12;
    uint32_t                     bb_dpd_lut_a05             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A02;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A02     b;
}   RF_DIGTOP_BB_DPD_LUT_A02_U;


// 0x4004F20C register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a06             :12;
    uint32_t                     bb_dpd_lut_a07             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A03;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A03     b;
}   RF_DIGTOP_BB_DPD_LUT_A03_U;


// 0x4004F210 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a08             :12;
    uint32_t                     bb_dpd_lut_a09             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A04;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A04     b;
}   RF_DIGTOP_BB_DPD_LUT_A04_U;


// 0x4004F214 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a10             :12;
    uint32_t                     bb_dpd_lut_a11             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A05;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A05     b;
}   RF_DIGTOP_BB_DPD_LUT_A05_U;


// 0x4004F218 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a12             :12;
    uint32_t                     bb_dpd_lut_a13             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A06;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A06     b;
}   RF_DIGTOP_BB_DPD_LUT_A06_U;


// 0x4004F21C register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a14             :12;
    uint32_t                     bb_dpd_lut_a15             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A07;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A07     b;
}   RF_DIGTOP_BB_DPD_LUT_A07_U;


// 0x4004F220 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a16             :12;
    uint32_t                     bb_dpd_lut_a17             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A08;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A08     b;
}   RF_DIGTOP_BB_DPD_LUT_A08_U;


// 0x4004F224 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a18             :12;
    uint32_t                     bb_dpd_lut_a19             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A09;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A09     b;
}   RF_DIGTOP_BB_DPD_LUT_A09_U;


// 0x4004F228 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a20             :12;
    uint32_t                     bb_dpd_lut_a21             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A10;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A10     b;
}   RF_DIGTOP_BB_DPD_LUT_A10_U;


// 0x4004F22C register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a22             :12;
    uint32_t                     bb_dpd_lut_a23             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A11;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A11     b;
}   RF_DIGTOP_BB_DPD_LUT_A11_U;


// 0x4004F230 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a24             :12;
    uint32_t                     bb_dpd_lut_a25             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A12;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A12     b;
}   RF_DIGTOP_BB_DPD_LUT_A12_U;


// 0x4004F234 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a26             :12;
    uint32_t                     bb_dpd_lut_a27             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A13;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A13     b;
}   RF_DIGTOP_BB_DPD_LUT_A13_U;


// 0x4004F238 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a28             :12;
    uint32_t                     bb_dpd_lut_a29             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A14;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A14     b;
}   RF_DIGTOP_BB_DPD_LUT_A14_U;


// 0x4004F23C register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a30             :12;
    uint32_t                     bb_dpd_lut_a31             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A15;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A15     b;
}   RF_DIGTOP_BB_DPD_LUT_A15_U;


// 0x4004F240 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a32             :12;
    uint32_t                     bb_dpd_lut_a33             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A16;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A16     b;
}   RF_DIGTOP_BB_DPD_LUT_A16_U;


// 0x4004F244 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a34             :12;
    uint32_t                     bb_dpd_lut_a35             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A17;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A17     b;
}   RF_DIGTOP_BB_DPD_LUT_A17_U;


// 0x4004F248 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a36             :12;
    uint32_t                     bb_dpd_lut_a37             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A18;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A18     b;
}   RF_DIGTOP_BB_DPD_LUT_A18_U;


// 0x4004F24C register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a38             :12;
    uint32_t                     bb_dpd_lut_a39             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A19;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A19     b;
}   RF_DIGTOP_BB_DPD_LUT_A19_U;


// 0x4004F250 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a40             :12;
    uint32_t                     bb_dpd_lut_a41             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A20;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A20     b;
}   RF_DIGTOP_BB_DPD_LUT_A20_U;


// 0x4004F254 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a42             :12;
    uint32_t                     bb_dpd_lut_a43             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A21;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A21     b;
}   RF_DIGTOP_BB_DPD_LUT_A21_U;


// 0x4004F258 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a44             :12;
    uint32_t                     bb_dpd_lut_a45             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A22;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A22     b;
}   RF_DIGTOP_BB_DPD_LUT_A22_U;


// 0x4004F25C register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a46             :12;
    uint32_t                     bb_dpd_lut_a47             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A23;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A23     b;
}   RF_DIGTOP_BB_DPD_LUT_A23_U;


// 0x4004F260 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a48             :12;
    uint32_t                     bb_dpd_lut_a49             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A24;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A24     b;
}   RF_DIGTOP_BB_DPD_LUT_A24_U;


// 0x4004F264 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a50             :12;
    uint32_t                     bb_dpd_lut_a51             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A25;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A25     b;
}   RF_DIGTOP_BB_DPD_LUT_A25_U;


// 0x4004F268 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a52             :12;
    uint32_t                     bb_dpd_lut_a53             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A26;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A26     b;
}   RF_DIGTOP_BB_DPD_LUT_A26_U;


// 0x4004F26C register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a54             :12;
    uint32_t                     bb_dpd_lut_a55             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A27;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A27     b;
}   RF_DIGTOP_BB_DPD_LUT_A27_U;


// 0x4004F270 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a56             :12;
    uint32_t                     bb_dpd_lut_a57             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A28;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A28     b;
}   RF_DIGTOP_BB_DPD_LUT_A28_U;


// 0x4004F274 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a58             :12;
    uint32_t                     bb_dpd_lut_a59             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A29;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A29     b;
}   RF_DIGTOP_BB_DPD_LUT_A29_U;


// 0x4004F278 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a60             :12;
    uint32_t                     bb_dpd_lut_a61             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A30;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A30     b;
}   RF_DIGTOP_BB_DPD_LUT_A30_U;


// 0x4004F27C register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_a62             :12;
    uint32_t                     bb_dpd_lut_a63             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_A31;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_A31     b;
}   RF_DIGTOP_BB_DPD_LUT_A31_U;


// 0x4004F280 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a00              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a00              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A00;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A00     b;
}   RF_DIGTOP_PA_DPD_LUT_A00_U;


// 0x4004F284 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a01              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a01              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A01;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A01     b;
}   RF_DIGTOP_PA_DPD_LUT_A01_U;


// 0x4004F288 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a02              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a02              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A02;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A02     b;
}   RF_DIGTOP_PA_DPD_LUT_A02_U;


// 0x4004F28C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a03              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a03              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A03;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A03     b;
}   RF_DIGTOP_PA_DPD_LUT_A03_U;


// 0x4004F290 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a04              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a04              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A04;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A04     b;
}   RF_DIGTOP_PA_DPD_LUT_A04_U;


// 0x4004F294 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a05              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a05              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A05;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A05     b;
}   RF_DIGTOP_PA_DPD_LUT_A05_U;


// 0x4004F298 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a06              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a06              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A06;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A06     b;
}   RF_DIGTOP_PA_DPD_LUT_A06_U;


// 0x4004F29C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a07              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a07              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A07;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A07     b;
}   RF_DIGTOP_PA_DPD_LUT_A07_U;


// 0x4004F2A0 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a08              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a08              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A08;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A08     b;
}   RF_DIGTOP_PA_DPD_LUT_A08_U;


// 0x4004F2A4 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a09              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a09              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A09;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A09     b;
}   RF_DIGTOP_PA_DPD_LUT_A09_U;


// 0x4004F2A8 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a10              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a10              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A10;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A10     b;
}   RF_DIGTOP_PA_DPD_LUT_A10_U;


// 0x4004F2AC register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a11              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a11              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A11;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A11     b;
}   RF_DIGTOP_PA_DPD_LUT_A11_U;


// 0x4004F2B0 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a12              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a12              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A12;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A12     b;
}   RF_DIGTOP_PA_DPD_LUT_A12_U;


// 0x4004F2B4 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a13              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a13              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A13;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A13     b;
}   RF_DIGTOP_PA_DPD_LUT_A13_U;


// 0x4004F2B8 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a14              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a14              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A14;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A14     b;
}   RF_DIGTOP_PA_DPD_LUT_A14_U;


// 0x4004F2BC register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a15              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a15              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A15;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A15     b;
}   RF_DIGTOP_PA_DPD_LUT_A15_U;


// 0x4004F2C0 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a16              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a16              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A16;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A16     b;
}   RF_DIGTOP_PA_DPD_LUT_A16_U;


// 0x4004F2C4 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a17              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a17              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A17;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A17     b;
}   RF_DIGTOP_PA_DPD_LUT_A17_U;


// 0x4004F2C8 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a18              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a18              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A18;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A18     b;
}   RF_DIGTOP_PA_DPD_LUT_A18_U;


// 0x4004F2CC register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a19              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a19              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A19;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A19     b;
}   RF_DIGTOP_PA_DPD_LUT_A19_U;


// 0x4004F2D0 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a20              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a20              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A20;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A20     b;
}   RF_DIGTOP_PA_DPD_LUT_A20_U;


// 0x4004F2D4 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a21              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a21              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A21;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A21     b;
}   RF_DIGTOP_PA_DPD_LUT_A21_U;


// 0x4004F2D8 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a22              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a22              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A22;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A22     b;
}   RF_DIGTOP_PA_DPD_LUT_A22_U;


// 0x4004F2DC register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a23              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a23              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A23;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A23     b;
}   RF_DIGTOP_PA_DPD_LUT_A23_U;


// 0x4004F2E0 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a24              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a24              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A24;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A24     b;
}   RF_DIGTOP_PA_DPD_LUT_A24_U;


// 0x4004F2E4 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a25              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a25              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A25;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A25     b;
}   RF_DIGTOP_PA_DPD_LUT_A25_U;


// 0x4004F2E8 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a26              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a26              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A26;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A26     b;
}   RF_DIGTOP_PA_DPD_LUT_A26_U;


// 0x4004F2EC register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a27              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a27              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A27;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A27     b;
}   RF_DIGTOP_PA_DPD_LUT_A27_U;


// 0x4004F2F0 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a28              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a28              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A28;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A28     b;
}   RF_DIGTOP_PA_DPD_LUT_A28_U;


// 0x4004F2F4 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a29              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a29              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A29;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A29     b;
}   RF_DIGTOP_PA_DPD_LUT_A29_U;


// 0x4004F2F8 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a30              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a30              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A30;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A30     b;
}   RF_DIGTOP_PA_DPD_LUT_A30_U;


// 0x4004F2FC register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a31              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a31              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A31;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A31     b;
}   RF_DIGTOP_PA_DPD_LUT_A31_U;


// 0x4004F300 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a32              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a32              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A32;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A32     b;
}   RF_DIGTOP_PA_DPD_LUT_A32_U;


// 0x4004F304 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a33              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a33              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A33;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A33     b;
}   RF_DIGTOP_PA_DPD_LUT_A33_U;


// 0x4004F308 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a34              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a34              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A34;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A34     b;
}   RF_DIGTOP_PA_DPD_LUT_A34_U;


// 0x4004F30C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a35              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a35              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A35;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A35     b;
}   RF_DIGTOP_PA_DPD_LUT_A35_U;


// 0x4004F310 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a36              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a36              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A36;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A36     b;
}   RF_DIGTOP_PA_DPD_LUT_A36_U;


// 0x4004F314 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a37              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a37              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A37;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A37     b;
}   RF_DIGTOP_PA_DPD_LUT_A37_U;


// 0x4004F318 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a38              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a38              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A38;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A38     b;
}   RF_DIGTOP_PA_DPD_LUT_A38_U;


// 0x4004F31C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a39              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a39              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A39;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A39     b;
}   RF_DIGTOP_PA_DPD_LUT_A39_U;


// 0x4004F320 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a40              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a40              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A40;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A40     b;
}   RF_DIGTOP_PA_DPD_LUT_A40_U;


// 0x4004F324 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a41              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a41              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A41;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A41     b;
}   RF_DIGTOP_PA_DPD_LUT_A41_U;


// 0x4004F328 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a42              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a42              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A42;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A42     b;
}   RF_DIGTOP_PA_DPD_LUT_A42_U;


// 0x4004F32C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a43              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a43              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A43;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A43     b;
}   RF_DIGTOP_PA_DPD_LUT_A43_U;


// 0x4004F330 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a44              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a44              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A44;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A44     b;
}   RF_DIGTOP_PA_DPD_LUT_A44_U;


// 0x4004F334 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a45              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a45              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A45;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A45     b;
}   RF_DIGTOP_PA_DPD_LUT_A45_U;


// 0x4004F338 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a46              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a46              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A46;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A46     b;
}   RF_DIGTOP_PA_DPD_LUT_A46_U;


// 0x4004F33C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a47              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a47              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A47;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A47     b;
}   RF_DIGTOP_PA_DPD_LUT_A47_U;


// 0x4004F340 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a48              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a48              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A48;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A48     b;
}   RF_DIGTOP_PA_DPD_LUT_A48_U;


// 0x4004F344 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a49              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a49              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A49;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A49     b;
}   RF_DIGTOP_PA_DPD_LUT_A49_U;


// 0x4004F348 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a50              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a50              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A50;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A50     b;
}   RF_DIGTOP_PA_DPD_LUT_A50_U;


// 0x4004F34C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a51              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a51              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A51;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A51     b;
}   RF_DIGTOP_PA_DPD_LUT_A51_U;


// 0x4004F350 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a52              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a52              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A52;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A52     b;
}   RF_DIGTOP_PA_DPD_LUT_A52_U;


// 0x4004F354 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a53              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a53              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A53;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A53     b;
}   RF_DIGTOP_PA_DPD_LUT_A53_U;


// 0x4004F358 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a54              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a54              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A54;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A54     b;
}   RF_DIGTOP_PA_DPD_LUT_A54_U;


// 0x4004F35C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a55              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a55              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A55;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A55     b;
}   RF_DIGTOP_PA_DPD_LUT_A55_U;


// 0x4004F360 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a56              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a56              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A56;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A56     b;
}   RF_DIGTOP_PA_DPD_LUT_A56_U;


// 0x4004F364 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a57              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a57              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A57;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A57     b;
}   RF_DIGTOP_PA_DPD_LUT_A57_U;


// 0x4004F368 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a58              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a58              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A58;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A58     b;
}   RF_DIGTOP_PA_DPD_LUT_A58_U;


// 0x4004F36C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a59              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a59              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A59;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A59     b;
}   RF_DIGTOP_PA_DPD_LUT_A59_U;


// 0x4004F370 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a60              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a60              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A60;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A60     b;
}   RF_DIGTOP_PA_DPD_LUT_A60_U;


// 0x4004F374 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a61              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a61              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A61;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A61     b;
}   RF_DIGTOP_PA_DPD_LUT_A61_U;


// 0x4004F378 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a62              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a62              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A62;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A62     b;
}   RF_DIGTOP_PA_DPD_LUT_A62_U;


// 0x4004F37C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_a63              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_a63              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_A63;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_A63     b;
}   RF_DIGTOP_PA_DPD_LUT_A63_U;


// 0x4004F380 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b00             :12;
    uint32_t                     bb_dpd_lut_b01             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B00;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B00     b;
}   RF_DIGTOP_BB_DPD_LUT_B00_U;


// 0x4004F384 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b02             :12;
    uint32_t                     bb_dpd_lut_b03             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B01;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B01     b;
}   RF_DIGTOP_BB_DPD_LUT_B01_U;


// 0x4004F388 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b04             :12;
    uint32_t                     bb_dpd_lut_b05             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B02;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B02     b;
}   RF_DIGTOP_BB_DPD_LUT_B02_U;


// 0x4004F38C register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b06             :12;
    uint32_t                     bb_dpd_lut_b07             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B03;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B03     b;
}   RF_DIGTOP_BB_DPD_LUT_B03_U;


// 0x4004F390 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b08             :12;
    uint32_t                     bb_dpd_lut_b09             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B04;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B04     b;
}   RF_DIGTOP_BB_DPD_LUT_B04_U;


// 0x4004F394 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b10             :12;
    uint32_t                     bb_dpd_lut_b11             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B05;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B05     b;
}   RF_DIGTOP_BB_DPD_LUT_B05_U;


// 0x4004F398 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b12             :12;
    uint32_t                     bb_dpd_lut_b13             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B06;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B06     b;
}   RF_DIGTOP_BB_DPD_LUT_B06_U;


// 0x4004F39C register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b14             :12;
    uint32_t                     bb_dpd_lut_b15             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B07;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B07     b;
}   RF_DIGTOP_BB_DPD_LUT_B07_U;


// 0x4004F3A0 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b16             :12;
    uint32_t                     bb_dpd_lut_b17             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B08;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B08     b;
}   RF_DIGTOP_BB_DPD_LUT_B08_U;


// 0x4004F3A4 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b18             :12;
    uint32_t                     bb_dpd_lut_b19             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B09;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B09     b;
}   RF_DIGTOP_BB_DPD_LUT_B09_U;


// 0x4004F3A8 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b20             :12;
    uint32_t                     bb_dpd_lut_b21             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B10;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B10     b;
}   RF_DIGTOP_BB_DPD_LUT_B10_U;


// 0x4004F3AC register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b22             :12;
    uint32_t                     bb_dpd_lut_b23             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B11;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B11     b;
}   RF_DIGTOP_BB_DPD_LUT_B11_U;


// 0x4004F3B0 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b24             :12;
    uint32_t                     bb_dpd_lut_b25             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B12;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B12     b;
}   RF_DIGTOP_BB_DPD_LUT_B12_U;


// 0x4004F3B4 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b26             :12;
    uint32_t                     bb_dpd_lut_b27             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B13;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B13     b;
}   RF_DIGTOP_BB_DPD_LUT_B13_U;


// 0x4004F3B8 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b28             :12;
    uint32_t                     bb_dpd_lut_b29             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B14;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B14     b;
}   RF_DIGTOP_BB_DPD_LUT_B14_U;


// 0x4004F3BC register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b30             :12;
    uint32_t                     bb_dpd_lut_b31             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B15;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B15     b;
}   RF_DIGTOP_BB_DPD_LUT_B15_U;


// 0x4004F3C0 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b32             :12;
    uint32_t                     bb_dpd_lut_b33             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B16;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B16     b;
}   RF_DIGTOP_BB_DPD_LUT_B16_U;


// 0x4004F3C4 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b34             :12;
    uint32_t                     bb_dpd_lut_b35             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B17;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B17     b;
}   RF_DIGTOP_BB_DPD_LUT_B17_U;


// 0x4004F3C8 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b36             :12;
    uint32_t                     bb_dpd_lut_b37             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B18;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B18     b;
}   RF_DIGTOP_BB_DPD_LUT_B18_U;


// 0x4004F3CC register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b38             :12;
    uint32_t                     bb_dpd_lut_b39             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B19;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B19     b;
}   RF_DIGTOP_BB_DPD_LUT_B19_U;


// 0x4004F3D0 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b40             :12;
    uint32_t                     bb_dpd_lut_b41             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B20;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B20     b;
}   RF_DIGTOP_BB_DPD_LUT_B20_U;


// 0x4004F3D4 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b42             :12;
    uint32_t                     bb_dpd_lut_b43             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B21;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B21     b;
}   RF_DIGTOP_BB_DPD_LUT_B21_U;


// 0x4004F3D8 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b44             :12;
    uint32_t                     bb_dpd_lut_b45             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B22;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B22     b;
}   RF_DIGTOP_BB_DPD_LUT_B22_U;


// 0x4004F3DC register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b46             :12;
    uint32_t                     bb_dpd_lut_b47             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B23;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B23     b;
}   RF_DIGTOP_BB_DPD_LUT_B23_U;


// 0x4004F3E0 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b48             :12;
    uint32_t                     bb_dpd_lut_b49             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B24;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B24     b;
}   RF_DIGTOP_BB_DPD_LUT_B24_U;


// 0x4004F3E4 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b50             :12;
    uint32_t                     bb_dpd_lut_b51             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B25;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B25     b;
}   RF_DIGTOP_BB_DPD_LUT_B25_U;


// 0x4004F3E8 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b52             :12;
    uint32_t                     bb_dpd_lut_b53             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B26;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B26     b;
}   RF_DIGTOP_BB_DPD_LUT_B26_U;


// 0x4004F3EC register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b54             :12;
    uint32_t                     bb_dpd_lut_b55             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B27;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B27     b;
}   RF_DIGTOP_BB_DPD_LUT_B27_U;


// 0x4004F3F0 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b56             :12;
    uint32_t                     bb_dpd_lut_b57             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B28;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B28     b;
}   RF_DIGTOP_BB_DPD_LUT_B28_U;


// 0x4004F3F4 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b58             :12;
    uint32_t                     bb_dpd_lut_b59             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B29;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B29     b;
}   RF_DIGTOP_BB_DPD_LUT_B29_U;


// 0x4004F3F8 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b60             :12;
    uint32_t                     bb_dpd_lut_b61             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B30;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B30     b;
}   RF_DIGTOP_BB_DPD_LUT_B30_U;


// 0x4004F3FC register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_b62             :12;
    uint32_t                     bb_dpd_lut_b63             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_B31;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_B31     b;
}   RF_DIGTOP_BB_DPD_LUT_B31_U;


// 0x4004F400 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b00              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b00              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B00;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B00     b;
}   RF_DIGTOP_PA_DPD_LUT_B00_U;


// 0x4004F404 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b01              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b01              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B01;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B01     b;
}   RF_DIGTOP_PA_DPD_LUT_B01_U;


// 0x4004F408 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b02              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b02              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B02;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B02     b;
}   RF_DIGTOP_PA_DPD_LUT_B02_U;


// 0x4004F40C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b03              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b03              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B03;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B03     b;
}   RF_DIGTOP_PA_DPD_LUT_B03_U;


// 0x4004F410 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b04              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b04              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B04;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B04     b;
}   RF_DIGTOP_PA_DPD_LUT_B04_U;


// 0x4004F414 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b05              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b05              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B05;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B05     b;
}   RF_DIGTOP_PA_DPD_LUT_B05_U;


// 0x4004F418 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b06              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b06              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B06;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B06     b;
}   RF_DIGTOP_PA_DPD_LUT_B06_U;


// 0x4004F41C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b07              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b07              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B07;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B07     b;
}   RF_DIGTOP_PA_DPD_LUT_B07_U;


// 0x4004F420 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b08              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b08              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B08;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B08     b;
}   RF_DIGTOP_PA_DPD_LUT_B08_U;


// 0x4004F424 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b09              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b09              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B09;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B09     b;
}   RF_DIGTOP_PA_DPD_LUT_B09_U;


// 0x4004F428 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b10              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b10              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B10;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B10     b;
}   RF_DIGTOP_PA_DPD_LUT_B10_U;


// 0x4004F42C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b11              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b11              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B11;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B11     b;
}   RF_DIGTOP_PA_DPD_LUT_B11_U;


// 0x4004F430 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b12              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b12              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B12;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B12     b;
}   RF_DIGTOP_PA_DPD_LUT_B12_U;


// 0x4004F434 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b13              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b13              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B13;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B13     b;
}   RF_DIGTOP_PA_DPD_LUT_B13_U;


// 0x4004F438 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b14              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b14              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B14;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B14     b;
}   RF_DIGTOP_PA_DPD_LUT_B14_U;


// 0x4004F43C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b15              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b15              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B15;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B15     b;
}   RF_DIGTOP_PA_DPD_LUT_B15_U;


// 0x4004F440 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b16              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b16              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B16;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B16     b;
}   RF_DIGTOP_PA_DPD_LUT_B16_U;


// 0x4004F444 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b17              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b17              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B17;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B17     b;
}   RF_DIGTOP_PA_DPD_LUT_B17_U;


// 0x4004F448 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b18              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b18              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B18;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B18     b;
}   RF_DIGTOP_PA_DPD_LUT_B18_U;


// 0x4004F44C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b19              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b19              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B19;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B19     b;
}   RF_DIGTOP_PA_DPD_LUT_B19_U;


// 0x4004F450 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b20              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b20              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B20;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B20     b;
}   RF_DIGTOP_PA_DPD_LUT_B20_U;


// 0x4004F454 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b21              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b21              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B21;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B21     b;
}   RF_DIGTOP_PA_DPD_LUT_B21_U;


// 0x4004F458 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b22              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b22              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B22;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B22     b;
}   RF_DIGTOP_PA_DPD_LUT_B22_U;


// 0x4004F45C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b23              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b23              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B23;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B23     b;
}   RF_DIGTOP_PA_DPD_LUT_B23_U;


// 0x4004F460 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b24              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b24              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B24;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B24     b;
}   RF_DIGTOP_PA_DPD_LUT_B24_U;


// 0x4004F464 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b25              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b25              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B25;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B25     b;
}   RF_DIGTOP_PA_DPD_LUT_B25_U;


// 0x4004F468 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b26              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b26              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B26;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B26     b;
}   RF_DIGTOP_PA_DPD_LUT_B26_U;


// 0x4004F46C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b27              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b27              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B27;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B27     b;
}   RF_DIGTOP_PA_DPD_LUT_B27_U;


// 0x4004F470 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b28              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b28              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B28;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B28     b;
}   RF_DIGTOP_PA_DPD_LUT_B28_U;


// 0x4004F474 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b29              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b29              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B29;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B29     b;
}   RF_DIGTOP_PA_DPD_LUT_B29_U;


// 0x4004F478 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b30              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b30              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B30;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B30     b;
}   RF_DIGTOP_PA_DPD_LUT_B30_U;


// 0x4004F47C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b31              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b31              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B31;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B31     b;
}   RF_DIGTOP_PA_DPD_LUT_B31_U;


// 0x4004F480 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b32              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b32              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B32;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B32     b;
}   RF_DIGTOP_PA_DPD_LUT_B32_U;


// 0x4004F484 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b33              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b33              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B33;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B33     b;
}   RF_DIGTOP_PA_DPD_LUT_B33_U;


// 0x4004F488 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b34              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b34              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B34;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B34     b;
}   RF_DIGTOP_PA_DPD_LUT_B34_U;


// 0x4004F48C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b35              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b35              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B35;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B35     b;
}   RF_DIGTOP_PA_DPD_LUT_B35_U;


// 0x4004F490 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b36              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b36              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B36;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B36     b;
}   RF_DIGTOP_PA_DPD_LUT_B36_U;


// 0x4004F494 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b37              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b37              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B37;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B37     b;
}   RF_DIGTOP_PA_DPD_LUT_B37_U;


// 0x4004F498 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b38              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b38              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B38;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B38     b;
}   RF_DIGTOP_PA_DPD_LUT_B38_U;


// 0x4004F49C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b39              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b39              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B39;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B39     b;
}   RF_DIGTOP_PA_DPD_LUT_B39_U;


// 0x4004F4A0 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b40              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b40              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B40;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B40     b;
}   RF_DIGTOP_PA_DPD_LUT_B40_U;


// 0x4004F4A4 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b41              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b41              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B41;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B41     b;
}   RF_DIGTOP_PA_DPD_LUT_B41_U;


// 0x4004F4A8 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b42              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b42              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B42;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B42     b;
}   RF_DIGTOP_PA_DPD_LUT_B42_U;


// 0x4004F4AC register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b43              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b43              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B43;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B43     b;
}   RF_DIGTOP_PA_DPD_LUT_B43_U;


// 0x4004F4B0 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b44              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b44              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B44;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B44     b;
}   RF_DIGTOP_PA_DPD_LUT_B44_U;


// 0x4004F4B4 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b45              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b45              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B45;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B45     b;
}   RF_DIGTOP_PA_DPD_LUT_B45_U;


// 0x4004F4B8 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b46              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b46              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B46;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B46     b;
}   RF_DIGTOP_PA_DPD_LUT_B46_U;


// 0x4004F4BC register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b47              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b47              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B47;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B47     b;
}   RF_DIGTOP_PA_DPD_LUT_B47_U;


// 0x4004F4C0 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b48              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b48              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B48;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B48     b;
}   RF_DIGTOP_PA_DPD_LUT_B48_U;


// 0x4004F4C4 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b49              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b49              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B49;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B49     b;
}   RF_DIGTOP_PA_DPD_LUT_B49_U;


// 0x4004F4C8 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b50              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b50              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B50;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B50     b;
}   RF_DIGTOP_PA_DPD_LUT_B50_U;


// 0x4004F4CC register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b51              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b51              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B51;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B51     b;
}   RF_DIGTOP_PA_DPD_LUT_B51_U;


// 0x4004F4D0 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b52              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b52              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B52;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B52     b;
}   RF_DIGTOP_PA_DPD_LUT_B52_U;


// 0x4004F4D4 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b53              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b53              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B53;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B53     b;
}   RF_DIGTOP_PA_DPD_LUT_B53_U;


// 0x4004F4D8 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b54              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b54              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B54;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B54     b;
}   RF_DIGTOP_PA_DPD_LUT_B54_U;


// 0x4004F4DC register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b55              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b55              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B55;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B55     b;
}   RF_DIGTOP_PA_DPD_LUT_B55_U;


// 0x4004F4E0 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b56              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b56              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B56;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B56     b;
}   RF_DIGTOP_PA_DPD_LUT_B56_U;


// 0x4004F4E4 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b57              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b57              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B57;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B57     b;
}   RF_DIGTOP_PA_DPD_LUT_B57_U;


// 0x4004F4E8 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b58              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b58              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B58;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B58     b;
}   RF_DIGTOP_PA_DPD_LUT_B58_U;


// 0x4004F4EC register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b59              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b59              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B59;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B59     b;
}   RF_DIGTOP_PA_DPD_LUT_B59_U;


// 0x4004F4F0 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b60              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b60              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B60;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B60     b;
}   RF_DIGTOP_PA_DPD_LUT_B60_U;


// 0x4004F4F4 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b61              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b61              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B61;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B61     b;
}   RF_DIGTOP_PA_DPD_LUT_B61_U;


// 0x4004F4F8 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b62              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b62              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B62;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B62     b;
}   RF_DIGTOP_PA_DPD_LUT_B62_U;


// 0x4004F4FC register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_b63              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_b63              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_B63;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_B63     b;
}   RF_DIGTOP_PA_DPD_LUT_B63_U;


// 0x4004F500 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c00             :12;
    uint32_t                     bb_dpd_lut_c01             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C00;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C00     b;
}   RF_DIGTOP_BB_DPD_LUT_C00_U;


// 0x4004F504 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c02             :12;
    uint32_t                     bb_dpd_lut_c03             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C01;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C01     b;
}   RF_DIGTOP_BB_DPD_LUT_C01_U;


// 0x4004F508 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c04             :12;
    uint32_t                     bb_dpd_lut_c05             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C02;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C02     b;
}   RF_DIGTOP_BB_DPD_LUT_C02_U;


// 0x4004F50C register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c06             :12;
    uint32_t                     bb_dpd_lut_c07             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C03;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C03     b;
}   RF_DIGTOP_BB_DPD_LUT_C03_U;


// 0x4004F510 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c08             :12;
    uint32_t                     bb_dpd_lut_c09             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C04;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C04     b;
}   RF_DIGTOP_BB_DPD_LUT_C04_U;


// 0x4004F514 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c10             :12;
    uint32_t                     bb_dpd_lut_c11             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C05;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C05     b;
}   RF_DIGTOP_BB_DPD_LUT_C05_U;


// 0x4004F518 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c12             :12;
    uint32_t                     bb_dpd_lut_c13             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C06;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C06     b;
}   RF_DIGTOP_BB_DPD_LUT_C06_U;


// 0x4004F51C register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c14             :12;
    uint32_t                     bb_dpd_lut_c15             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C07;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C07     b;
}   RF_DIGTOP_BB_DPD_LUT_C07_U;


// 0x4004F520 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c16             :12;
    uint32_t                     bb_dpd_lut_c17             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C08;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C08     b;
}   RF_DIGTOP_BB_DPD_LUT_C08_U;


// 0x4004F524 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c18             :12;
    uint32_t                     bb_dpd_lut_c19             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C09;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C09     b;
}   RF_DIGTOP_BB_DPD_LUT_C09_U;


// 0x4004F528 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c20             :12;
    uint32_t                     bb_dpd_lut_c21             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C10;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C10     b;
}   RF_DIGTOP_BB_DPD_LUT_C10_U;


// 0x4004F52C register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c22             :12;
    uint32_t                     bb_dpd_lut_c23             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C11;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C11     b;
}   RF_DIGTOP_BB_DPD_LUT_C11_U;


// 0x4004F530 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c24             :12;
    uint32_t                     bb_dpd_lut_c25             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C12;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C12     b;
}   RF_DIGTOP_BB_DPD_LUT_C12_U;


// 0x4004F534 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c26             :12;
    uint32_t                     bb_dpd_lut_c27             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C13;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C13     b;
}   RF_DIGTOP_BB_DPD_LUT_C13_U;


// 0x4004F538 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c28             :12;
    uint32_t                     bb_dpd_lut_c29             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C14;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C14     b;
}   RF_DIGTOP_BB_DPD_LUT_C14_U;


// 0x4004F53C register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c30             :12;
    uint32_t                     bb_dpd_lut_c31             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C15;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C15     b;
}   RF_DIGTOP_BB_DPD_LUT_C15_U;


// 0x4004F540 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c32             :12;
    uint32_t                     bb_dpd_lut_c33             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C16;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C16     b;
}   RF_DIGTOP_BB_DPD_LUT_C16_U;


// 0x4004F544 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c34             :12;
    uint32_t                     bb_dpd_lut_c35             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C17;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C17     b;
}   RF_DIGTOP_BB_DPD_LUT_C17_U;


// 0x4004F548 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c36             :12;
    uint32_t                     bb_dpd_lut_c37             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C18;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C18     b;
}   RF_DIGTOP_BB_DPD_LUT_C18_U;


// 0x4004F54C register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c38             :12;
    uint32_t                     bb_dpd_lut_c39             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C19;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C19     b;
}   RF_DIGTOP_BB_DPD_LUT_C19_U;


// 0x4004F550 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c40             :12;
    uint32_t                     bb_dpd_lut_c41             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C20;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C20     b;
}   RF_DIGTOP_BB_DPD_LUT_C20_U;


// 0x4004F554 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c42             :12;
    uint32_t                     bb_dpd_lut_c43             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C21;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C21     b;
}   RF_DIGTOP_BB_DPD_LUT_C21_U;


// 0x4004F558 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c44             :12;
    uint32_t                     bb_dpd_lut_c45             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C22;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C22     b;
}   RF_DIGTOP_BB_DPD_LUT_C22_U;


// 0x4004F55C register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c46             :12;
    uint32_t                     bb_dpd_lut_c47             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C23;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C23     b;
}   RF_DIGTOP_BB_DPD_LUT_C23_U;


// 0x4004F560 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c48             :12;
    uint32_t                     bb_dpd_lut_c49             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C24;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C24     b;
}   RF_DIGTOP_BB_DPD_LUT_C24_U;


// 0x4004F564 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c50             :12;
    uint32_t                     bb_dpd_lut_c51             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C25;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C25     b;
}   RF_DIGTOP_BB_DPD_LUT_C25_U;


// 0x4004F568 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c52             :12;
    uint32_t                     bb_dpd_lut_c53             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C26;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C26     b;
}   RF_DIGTOP_BB_DPD_LUT_C26_U;


// 0x4004F56C register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c54             :12;
    uint32_t                     bb_dpd_lut_c55             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C27;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C27     b;
}   RF_DIGTOP_BB_DPD_LUT_C27_U;


// 0x4004F570 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c56             :12;
    uint32_t                     bb_dpd_lut_c57             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C28;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C28     b;
}   RF_DIGTOP_BB_DPD_LUT_C28_U;


// 0x4004F574 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c58             :12;
    uint32_t                     bb_dpd_lut_c59             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C29;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C29     b;
}   RF_DIGTOP_BB_DPD_LUT_C29_U;


// 0x4004F578 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c60             :12;
    uint32_t                     bb_dpd_lut_c61             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C30;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C30     b;
}   RF_DIGTOP_BB_DPD_LUT_C30_U;


// 0x4004F57C register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_lut_c62             :12;
    uint32_t                     bb_dpd_lut_c63             :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_BB_DPD_LUT_C31;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_BB_DPD_LUT_C31     b;
}   RF_DIGTOP_BB_DPD_LUT_C31_U;


// 0x4004F580 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c00              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c00              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C00;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C00     b;
}   RF_DIGTOP_PA_DPD_LUT_C00_U;


// 0x4004F584 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c01              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c01              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C01;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C01     b;
}   RF_DIGTOP_PA_DPD_LUT_C01_U;


// 0x4004F588 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c02              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c02              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C02;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C02     b;
}   RF_DIGTOP_PA_DPD_LUT_C02_U;


// 0x4004F58C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c03              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c03              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C03;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C03     b;
}   RF_DIGTOP_PA_DPD_LUT_C03_U;


// 0x4004F590 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c04              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c04              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C04;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C04     b;
}   RF_DIGTOP_PA_DPD_LUT_C04_U;


// 0x4004F594 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c05              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c05              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C05;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C05     b;
}   RF_DIGTOP_PA_DPD_LUT_C05_U;


// 0x4004F598 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c06              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c06              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C06;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C06     b;
}   RF_DIGTOP_PA_DPD_LUT_C06_U;


// 0x4004F59C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c07              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c07              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C07;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C07     b;
}   RF_DIGTOP_PA_DPD_LUT_C07_U;


// 0x4004F5A0 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c08              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c08              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C08;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C08     b;
}   RF_DIGTOP_PA_DPD_LUT_C08_U;


// 0x4004F5A4 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c09              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c09              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C09;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C09     b;
}   RF_DIGTOP_PA_DPD_LUT_C09_U;


// 0x4004F5A8 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c10              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c10              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C10;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C10     b;
}   RF_DIGTOP_PA_DPD_LUT_C10_U;


// 0x4004F5AC register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c11              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c11              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C11;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C11     b;
}   RF_DIGTOP_PA_DPD_LUT_C11_U;


// 0x4004F5B0 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c12              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c12              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C12;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C12     b;
}   RF_DIGTOP_PA_DPD_LUT_C12_U;


// 0x4004F5B4 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c13              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c13              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C13;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C13     b;
}   RF_DIGTOP_PA_DPD_LUT_C13_U;


// 0x4004F5B8 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c14              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c14              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C14;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C14     b;
}   RF_DIGTOP_PA_DPD_LUT_C14_U;


// 0x4004F5BC register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c15              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c15              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C15;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C15     b;
}   RF_DIGTOP_PA_DPD_LUT_C15_U;


// 0x4004F5C0 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c16              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c16              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C16;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C16     b;
}   RF_DIGTOP_PA_DPD_LUT_C16_U;


// 0x4004F5C4 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c17              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c17              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C17;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C17     b;
}   RF_DIGTOP_PA_DPD_LUT_C17_U;


// 0x4004F5C8 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c18              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c18              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C18;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C18     b;
}   RF_DIGTOP_PA_DPD_LUT_C18_U;


// 0x4004F5CC register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c19              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c19              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C19;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C19     b;
}   RF_DIGTOP_PA_DPD_LUT_C19_U;


// 0x4004F5D0 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c20              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c20              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C20;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C20     b;
}   RF_DIGTOP_PA_DPD_LUT_C20_U;


// 0x4004F5D4 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c21              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c21              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C21;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C21     b;
}   RF_DIGTOP_PA_DPD_LUT_C21_U;


// 0x4004F5D8 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c22              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c22              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C22;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C22     b;
}   RF_DIGTOP_PA_DPD_LUT_C22_U;


// 0x4004F5DC register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c23              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c23              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C23;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C23     b;
}   RF_DIGTOP_PA_DPD_LUT_C23_U;


// 0x4004F5E0 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c24              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c24              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C24;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C24     b;
}   RF_DIGTOP_PA_DPD_LUT_C24_U;


// 0x4004F5E4 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c25              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c25              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C25;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C25     b;
}   RF_DIGTOP_PA_DPD_LUT_C25_U;


// 0x4004F5E8 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c26              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c26              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C26;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C26     b;
}   RF_DIGTOP_PA_DPD_LUT_C26_U;


// 0x4004F5EC register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c27              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c27              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C27;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C27     b;
}   RF_DIGTOP_PA_DPD_LUT_C27_U;


// 0x4004F5F0 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c28              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c28              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C28;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C28     b;
}   RF_DIGTOP_PA_DPD_LUT_C28_U;


// 0x4004F5F4 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c29              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c29              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C29;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C29     b;
}   RF_DIGTOP_PA_DPD_LUT_C29_U;


// 0x4004F5F8 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c30              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c30              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C30;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C30     b;
}   RF_DIGTOP_PA_DPD_LUT_C30_U;


// 0x4004F5FC register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c31              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c31              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C31;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C31     b;
}   RF_DIGTOP_PA_DPD_LUT_C31_U;


// 0x4004F600 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c32              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c32              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C32;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C32     b;
}   RF_DIGTOP_PA_DPD_LUT_C32_U;


// 0x4004F604 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c33              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c33              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C33;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C33     b;
}   RF_DIGTOP_PA_DPD_LUT_C33_U;


// 0x4004F608 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c34              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c34              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C34;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C34     b;
}   RF_DIGTOP_PA_DPD_LUT_C34_U;


// 0x4004F60C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c35              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c35              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C35;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C35     b;
}   RF_DIGTOP_PA_DPD_LUT_C35_U;


// 0x4004F610 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c36              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c36              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C36;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C36     b;
}   RF_DIGTOP_PA_DPD_LUT_C36_U;


// 0x4004F614 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c37              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c37              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C37;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C37     b;
}   RF_DIGTOP_PA_DPD_LUT_C37_U;


// 0x4004F618 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c38              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c38              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C38;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C38     b;
}   RF_DIGTOP_PA_DPD_LUT_C38_U;


// 0x4004F61C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c39              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c39              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C39;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C39     b;
}   RF_DIGTOP_PA_DPD_LUT_C39_U;


// 0x4004F620 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c40              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c40              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C40;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C40     b;
}   RF_DIGTOP_PA_DPD_LUT_C40_U;


// 0x4004F624 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c41              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c41              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C41;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C41     b;
}   RF_DIGTOP_PA_DPD_LUT_C41_U;


// 0x4004F628 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c42              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c42              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C42;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C42     b;
}   RF_DIGTOP_PA_DPD_LUT_C42_U;


// 0x4004F62C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c43              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c43              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C43;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C43     b;
}   RF_DIGTOP_PA_DPD_LUT_C43_U;


// 0x4004F630 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c44              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c44              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C44;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C44     b;
}   RF_DIGTOP_PA_DPD_LUT_C44_U;


// 0x4004F634 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c45              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c45              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C45;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C45     b;
}   RF_DIGTOP_PA_DPD_LUT_C45_U;


// 0x4004F638 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c46              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c46              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C46;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C46     b;
}   RF_DIGTOP_PA_DPD_LUT_C46_U;


// 0x4004F63C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c47              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c47              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C47;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C47     b;
}   RF_DIGTOP_PA_DPD_LUT_C47_U;


// 0x4004F640 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c48              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c48              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C48;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C48     b;
}   RF_DIGTOP_PA_DPD_LUT_C48_U;


// 0x4004F644 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c49              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c49              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C49;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C49     b;
}   RF_DIGTOP_PA_DPD_LUT_C49_U;


// 0x4004F648 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c50              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c50              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C50;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C50     b;
}   RF_DIGTOP_PA_DPD_LUT_C50_U;


// 0x4004F64C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c51              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c51              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C51;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C51     b;
}   RF_DIGTOP_PA_DPD_LUT_C51_U;


// 0x4004F650 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c52              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c52              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C52;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C52     b;
}   RF_DIGTOP_PA_DPD_LUT_C52_U;


// 0x4004F654 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c53              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c53              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C53;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C53     b;
}   RF_DIGTOP_PA_DPD_LUT_C53_U;


// 0x4004F658 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c54              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c54              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C54;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C54     b;
}   RF_DIGTOP_PA_DPD_LUT_C54_U;


// 0x4004F65C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c55              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c55              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C55;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C55     b;
}   RF_DIGTOP_PA_DPD_LUT_C55_U;


// 0x4004F660 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c56              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c56              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C56;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C56     b;
}   RF_DIGTOP_PA_DPD_LUT_C56_U;


// 0x4004F664 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c57              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c57              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C57;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C57     b;
}   RF_DIGTOP_PA_DPD_LUT_C57_U;


// 0x4004F668 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c58              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c58              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C58;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C58     b;
}   RF_DIGTOP_PA_DPD_LUT_C58_U;


// 0x4004F66C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c59              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c59              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C59;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C59     b;
}   RF_DIGTOP_PA_DPD_LUT_C59_U;


// 0x4004F670 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c60              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c60              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C60;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C60     b;
}   RF_DIGTOP_PA_DPD_LUT_C60_U;


// 0x4004F674 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c61              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c61              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C61;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C61     b;
}   RF_DIGTOP_PA_DPD_LUT_C61_U;


// 0x4004F678 register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c62              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c62              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C62;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C62     b;
}   RF_DIGTOP_PA_DPD_LUT_C62_U;


// 0x4004F67C register ------------------------------------
typedef struct {
    uint32_t                     pa_im_lut_c63              :13;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     pa_re_lut_c63              :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_PA_DPD_LUT_C63;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_PA_DPD_LUT_C63     b;
}   RF_DIGTOP_PA_DPD_LUT_C63_U;


// 0x4004F680 register ------------------------------------
typedef struct {
    uint32_t                     th_bb_mag_a0               :12;
    uint32_t                     th_bb_mag_a1               :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_TH_BB_MAGA_0;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_TH_BB_MAGA_0       b;
}   RF_DIGTOP_TH_BB_MAGA_0_U;


// 0x4004F684 register ------------------------------------
typedef struct {
    uint32_t                     th_bb_mag_a2               :12;
    uint32_t                     th_bb_mag_a3               :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_TH_BB_MAGA_1;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_TH_BB_MAGA_1       b;
}   RF_DIGTOP_TH_BB_MAGA_1_U;


// 0x4004F688 register ------------------------------------
typedef struct {
    uint32_t                     th_bb_mag_b0               :12;
    uint32_t                     th_bb_mag_b1               :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_TH_BB_MAGB_0;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_TH_BB_MAGB_0       b;
}   RF_DIGTOP_TH_BB_MAGB_0_U;


// 0x4004F68C register ------------------------------------
typedef struct {
    uint32_t                     th_bb_mag_b2               :12;
    uint32_t                     th_bb_mag_b3               :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_TH_BB_MAGB_1;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_TH_BB_MAGB_1       b;
}   RF_DIGTOP_TH_BB_MAGB_1_U;


// 0x4004F690 register ------------------------------------
typedef struct {
    uint32_t                     th_bb_mag_c0               :12;
    uint32_t                     th_bb_mag_c1               :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_TH_BB_MAGC_0;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_TH_BB_MAGC_0       b;
}   RF_DIGTOP_TH_BB_MAGC_0_U;


// 0x4004F694 register ------------------------------------
typedef struct {
    uint32_t                     th_bb_mag_c2               :12;
    uint32_t                     th_bb_mag_c3               :12;
    uint32_t                     reserved0                  :8 ;
}   RF_DIGTOP_TH_BB_MAGC_1;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_TH_BB_MAGC_1       b;
}   RF_DIGTOP_TH_BB_MAGC_1_U;


// 0x4004F698 register ------------------------------------
typedef struct {
    uint32_t                     th_pa_mag_a0               :12;
    uint32_t                     reserved0                  :4 ;
    uint32_t                     th_pa_mag_a1               :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_TH_PA_MAGA_0;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_TH_PA_MAGA_0       b;
}   RF_DIGTOP_TH_PA_MAGA_0_U;


// 0x4004F69C register ------------------------------------
typedef struct {
    uint32_t                     th_pa_mag_a2               :12;
    uint32_t                     reserved0                  :4 ;
    uint32_t                     th_pa_mag_a3               :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_TH_PA_MAGA_1;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_TH_PA_MAGA_1       b;
}   RF_DIGTOP_TH_PA_MAGA_1_U;


// 0x4004F6A0 register ------------------------------------
typedef struct {
    uint32_t                     th_pa_mag_b0               :12;
    uint32_t                     reserved0                  :4 ;
    uint32_t                     th_pa_mag_b1               :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_TH_PA_MAGB_0;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_TH_PA_MAGB_0       b;
}   RF_DIGTOP_TH_PA_MAGB_0_U;


// 0x4004F6A4 register ------------------------------------
typedef struct {
    uint32_t                     th_pa_mag_b2               :12;
    uint32_t                     reserved0                  :4 ;
    uint32_t                     th_pa_mag_b3               :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_TH_PA_MAGB_1;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_TH_PA_MAGB_1       b;
}   RF_DIGTOP_TH_PA_MAGB_1_U;


// 0x4004F6A8 register ------------------------------------
typedef struct {
    uint32_t                     th_pa_mag_c0               :12;
    uint32_t                     reserved0                  :4 ;
    uint32_t                     th_pa_mag_c1               :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_TH_PA_MAGC_0;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_TH_PA_MAGC_0       b;
}   RF_DIGTOP_TH_PA_MAGC_0_U;


// 0x4004F6AC register ------------------------------------
typedef struct {
    uint32_t                     th_pa_mag_c2               :12;
    uint32_t                     reserved0                  :4 ;
    uint32_t                     th_pa_mag_c3               :13;
    uint32_t                     reserved1                  :3 ;
}   RF_DIGTOP_TH_PA_MAGC_1;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_TH_PA_MAGC_1       b;
}   RF_DIGTOP_TH_PA_MAGC_1_U;


// 0x4004F6B0 register ------------------------------------
typedef struct {
    uint32_t                     th_cfr_mag                 :11;
    uint32_t                     reserved0                  :21;
}   RF_DIGTOP_TH_CFR_MAG;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_TH_CFR_MAG         b;
}   RF_DIGTOP_TH_CFR_MAG_U;


// 0x4004F6B4 register ------------------------------------
typedef struct {
    uint32_t                     bb_dpd_on                  :1 ;
    uint32_t                     pa_dpd_on                  :1 ;
    uint32_t                     hard_clip_on               :1 ;
    uint32_t                     txcal_on                   :1 ;
    uint32_t                     bb_train_on                :1 ;
    uint32_t                     ramp_comp_on               :1 ;
    uint32_t                     txcal_mode_sel             :1 ;
    uint32_t                     dpd_mux_rf_con             :1 ;
    uint32_t                     fdiq_mux_sel               :1 ;
    uint32_t                     fdiq_cal_on                :1 ;
    uint32_t                     fdiq_manual_set            :1 ;
    uint32_t                     reserved0                  :21;
}   RF_DIGTOP_DPD_CTRL_SET;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DPD_CTRL_SET       b;
}   RF_DIGTOP_DPD_CTRL_SET_U;


// 0x4004F6B8 register ------------------------------------
typedef struct {
    uint32_t                     loiqcal_txiq_para_sel      :2 ;
    uint32_t                     reserved0                  :30;
}   RF_DIGTOP_TXCAL_CTRL_SET;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_TXCAL_CTRL_SET     b;
}   RF_DIGTOP_TXCAL_CTRL_SET_U;


// 0x4004F6BC register ------------------------------------
typedef struct {
    uint32_t                     tx_iq_para0                :11;
    uint32_t                     reserved0                  :21;
}   RF_DIGTOP_TX_IQ_PARA_0;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_TX_IQ_PARA_0       b;
}   RF_DIGTOP_TX_IQ_PARA_0_U;


// 0x4004F6C0 register ------------------------------------
typedef struct {
    uint32_t                     tx_iq_para1                :11;
    uint32_t                     reserved0                  :21;
}   RF_DIGTOP_TX_IQ_PARA_1;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_TX_IQ_PARA_1       b;
}   RF_DIGTOP_TX_IQ_PARA_1_U;


// 0x4004F6C4 register ------------------------------------
typedef struct {
    uint32_t                     tx_lo_para_i               :10;
    uint32_t                     reserved0                  :22;
}   RF_DIGTOP_TX_LO_PARA_0;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_TX_LO_PARA_0       b;
}   RF_DIGTOP_TX_LO_PARA_0_U;


// 0x4004F6C8 register ------------------------------------
typedef struct {
    uint32_t                     tx_lo_para_q               :10;
    uint32_t                     reserved0                  :22;
}   RF_DIGTOP_TX_LO_PARA_1;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_TX_LO_PARA_1       b;
}   RF_DIGTOP_TX_LO_PARA_1_U;


// 0x4004F6CC register ------------------------------------
typedef struct {
    uint32_t                     ramp_prd_00                :4 ;
    uint32_t                     ramp_prd_01                :4 ;
    uint32_t                     ramp_prd_02                :4 ;
    uint32_t                     ramp_prd_03                :4 ;
    uint32_t                     ramp_prd_04                :4 ;
    uint32_t                     ramp_prd_05                :4 ;
    uint32_t                     ramp_prd_06                :4 ;
    uint32_t                     ramp_prd_07                :4 ;
}   RF_DIGTOP_RAMP_PRD_0;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_RAMP_PRD_0         b;
}   RF_DIGTOP_RAMP_PRD_0_U;


// 0x4004F6D0 register ------------------------------------
typedef struct {
    uint32_t                     ramp_prd_08                :4 ;
    uint32_t                     ramp_prd_09                :4 ;
    uint32_t                     ramp_prd_10                :4 ;
    uint32_t                     ramp_prd_11                :4 ;
    uint32_t                     ramp_prd_12                :4 ;
    uint32_t                     ramp_prd_13                :4 ;
    uint32_t                     ramp_prd_14                :4 ;
    uint32_t                     ramp_prd_15                :4 ;
}   RF_DIGTOP_RAMP_PRD_1;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_RAMP_PRD_1         b;
}   RF_DIGTOP_RAMP_PRD_1_U;


// 0x4004F6D4 register ------------------------------------
typedef struct {
    uint32_t                     ramp_mul_00                :5 ;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     ramp_mul_01                :5 ;
    uint32_t                     reserved1                  :3 ;
    uint32_t                     ramp_mul_02                :5 ;
    uint32_t                     reserved2                  :3 ;
    uint32_t                     ramp_mul_03                :5 ;
    uint32_t                     reserved3                  :3 ;
}   RF_DIGTOP_RAMP_MUL_SET0;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_RAMP_MUL_SET0      b;
}   RF_DIGTOP_RAMP_MUL_SET0_U;


// 0x4004F6D8 register ------------------------------------
typedef struct {
    uint32_t                     ramp_mul_04                :5 ;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     ramp_mul_05                :5 ;
    uint32_t                     reserved1                  :3 ;
    uint32_t                     ramp_mul_06                :5 ;
    uint32_t                     reserved2                  :3 ;
    uint32_t                     ramp_mul_07                :5 ;
    uint32_t                     reserved3                  :3 ;
}   RF_DIGTOP_RAMP_MUL_SET1;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_RAMP_MUL_SET1      b;
}   RF_DIGTOP_RAMP_MUL_SET1_U;


// 0x4004F6DC register ------------------------------------
typedef struct {
    uint32_t                     ramp_mul_08                :5 ;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     ramp_mul_09                :5 ;
    uint32_t                     reserved1                  :3 ;
    uint32_t                     ramp_mul_10                :5 ;
    uint32_t                     reserved2                  :3 ;
    uint32_t                     ramp_mul_11                :5 ;
    uint32_t                     reserved3                  :3 ;
}   RF_DIGTOP_RAMP_MUL_SET2;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_RAMP_MUL_SET2      b;
}   RF_DIGTOP_RAMP_MUL_SET2_U;


// 0x4004F6E0 register ------------------------------------
typedef struct {
    uint32_t                     ramp_mul_12                :5 ;
    uint32_t                     reserved0                  :3 ;
    uint32_t                     ramp_mul_13                :5 ;
    uint32_t                     reserved1                  :3 ;
    uint32_t                     ramp_mul_14                :5 ;
    uint32_t                     reserved2                  :3 ;
    uint32_t                     ramp_mul_15                :5 ;
    uint32_t                     reserved3                  :3 ;
}   RF_DIGTOP_RAMP_MUL_SET3;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_RAMP_MUL_SET3      b;
}   RF_DIGTOP_RAMP_MUL_SET3_U;


// 0x4004F6E4 register ------------------------------------
typedef struct {
    uint32_t                     ramp_delay                 :9 ;
    uint32_t                     reserved0                  :23;
}   RF_DIGTOP_RAMP_DELAY;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_RAMP_DELAY         b;
}   RF_DIGTOP_RAMP_DELAY_U;


// 0x4004F6E8 register ------------------------------------
typedef struct {
    uint32_t                     dpd_lut_index              :8 ;
    uint32_t                     reserved0                  :24;
}   RF_DIGTOP_DPD_LUT_INDEX;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_DPD_LUT_INDEX      b;
}   RF_DIGTOP_DPD_LUT_INDEX_U;


// 0x4004F6EC register ------------------------------------
typedef struct {
    uint32_t                     fdiq_rez_ctrl              :2 ;
    uint32_t                     reserved0                  :30;
}   RF_DIGTOP_FDIQ_CTRL_SET;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_FDIQ_CTRL_SET      b;
}   RF_DIGTOP_FDIQ_CTRL_SET_U;


// 0x4004F6F0 register ------------------------------------
typedef struct {
    uint32_t                     fdiq_coef_phi1             :11;
    uint32_t                     reserved0                  :21;
}   RF_DIGTOP_FDIQ_COEF_PHI1;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_FDIQ_COEF_PHI1     b;
}   RF_DIGTOP_FDIQ_COEF_PHI1_U;


// 0x4004F6F4 register ------------------------------------
typedef struct {
    uint32_t                     fdiq_coef_esp1             :11;
    uint32_t                     reserved0                  :21;
}   RF_DIGTOP_FDIQ_COEF_ESP1;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_FDIQ_COEF_ESP1     b;
}   RF_DIGTOP_FDIQ_COEF_ESP1_U;


// 0x4004F6F8 register ------------------------------------
typedef struct {
    uint32_t                     fdiq_coef_phi2             :11;
    uint32_t                     reserved0                  :21;
}   RF_DIGTOP_FDIQ_COEF_PHI2;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_FDIQ_COEF_PHI2     b;
}   RF_DIGTOP_FDIQ_COEF_PHI2_U;


// 0x4004F6FC register ------------------------------------
typedef struct {
    uint32_t                     fdiq_coef_esp2             :11;
    uint32_t                     reserved0                  :21;
}   RF_DIGTOP_FDIQ_COEF_ESP2;

typedef union {
    uint32_t                     w;
    RF_DIGTOP_FDIQ_COEF_ESP2     b;
}   RF_DIGTOP_FDIQ_COEF_ESP2_U;


//---------------------------------------------------------
// RF_DIGTOP Register Map
//---------------------------------------------------------
typedef struct {
    volatile RF_DIGTOP_SYS_CON_U                 SYS_CON               ; // 0x000
    volatile RF_DIGTOP_RX_REG0_U                 RX_REG0               ; // 0x004
    volatile RF_DIGTOP_RX_REG1_U                 RX_REG1               ; // 0x008
    volatile RF_DIGTOP_RX_REG2_U                 RX_REG2               ; // 0x00c
    volatile RF_DIGTOP_RX_REG3_U                 RX_REG3               ; // 0x010
    volatile RF_DIGTOP_TX_REG0_U                 TX_REG0               ; // 0x014
    volatile RF_DIGTOP_TX_REG1_U                 TX_REG1               ; // 0x018
    volatile RF_DIGTOP_TX_REG2_U                 TX_REG2               ; // 0x01c
    volatile RF_DIGTOP_PLL_REG0_U                PLL_REG0              ; // 0x020
    volatile RF_DIGTOP_PLL_REG1_U                PLL_REG1              ; // 0x024
    volatile RF_DIGTOP_PLL_REG2_U                PLL_REG2              ; // 0x028
    volatile RF_DIGTOP_PLL_REG3_U                PLL_REG3              ; // 0x02c
    volatile RF_DIGTOP_PLL_REG4_U                PLL_REG4              ; // 0x030
    volatile RF_DIGTOP_PLL_REG5_U                PLL_REG5              ; // 0x034
    volatile RF_DIGTOP_PLL_REG6_U                PLL_REG6              ; // 0x038
    volatile RF_DIGTOP_PLL_REG7_U                PLL_REG7              ; // 0x03c
    volatile RF_DIGTOP_PLL_REG8_U                PLL_REG8              ; // 0x040
    volatile RF_DIGTOP_PLL_REG9_U                PLL_REG9              ; // 0x044
    volatile RF_DIGTOP_PLL_REG10_U               PLL_REG10             ; // 0x048
    volatile RF_DIGTOP_PLL_REG11_U               PLL_REG11             ; // 0x04c
    volatile RF_DIGTOP_PLL_REG12_U               PLL_REG12             ; // 0x050
    volatile RF_DIGTOP_MISC_REG0_U               MISC_REG0             ; // 0x054
    volatile RF_DIGTOP_MISC_REG1_U               MISC_REG1             ; // 0x058
    volatile RF_DIGTOP_DIG_REG0_U                DIG_REG0              ; // 0x05c
    volatile RF_DIGTOP_DIG_REG1_U                DIG_REG1              ; // 0x060
    volatile RF_DIGTOP_CAL_REG0_U                CAL_REG0              ; // 0x064
    volatile RF_DIGTOP_CAL_REG1_U                CAL_REG1              ; // 0x068
    volatile RF_DIGTOP_CAL_REG2_U                CAL_REG2              ; // 0x06c
    volatile RF_DIGTOP_CAL_REG3_U                CAL_REG3              ; // 0x070
    volatile RF_DIGTOP_ADCAL_REG0_U              ADCAL_REG0            ; // 0x074
    volatile RF_DIGTOP_ADCAL_REG1_U              ADCAL_REG1            ; // 0x078
    volatile RF_DIGTOP_ADCAL_REG2_U              ADCAL_REG2            ; // 0x07c
    volatile RF_DIGTOP_ADCAL_REG3_U              ADCAL_REG3            ; // 0x080
    volatile RF_DIGTOP_ADCAL_REG4_U              ADCAL_REG4            ; // 0x084
    volatile RF_DIGTOP_ADCAL_REG5_U              ADCAL_REG5            ; // 0x088
    volatile uint32_t                         RESERVED0[17]         ; // 
    volatile RF_DIGTOP_ADCAL_REG23_U             ADCAL_REG23           ; // 0x0d0
    volatile RF_DIGTOP_CAL_REG4_U                CAL_REG4              ; // 0x0d4
    volatile RF_DIGTOP_CAL_REG5_U                CAL_REG5              ; // 0x0d8
    volatile RF_DIGTOP_CAL_REG6_U                CAL_REG6              ; // 0x0dc
    volatile RF_DIGTOP_CAL_REG7_U                CAL_REG7              ; // 0x0e0
    volatile RF_DIGTOP_DOCAL_REG0_U              DOCAL_REG0            ; // 0x0e4
    volatile RF_DIGTOP_DOCAL_REG1_U              DOCAL_REG1            ; // 0x0e8
    volatile RF_DIGTOP_DOCAL_REG2_U              DOCAL_REG2            ; // 0x0ec
    volatile RF_DIGTOP_DOCAL_REG3_U              DOCAL_REG3            ; // 0x0f0
    volatile RF_DIGTOP_DOCAL_REG4_U              DOCAL_REG4            ; // 0x0f4
    volatile RF_DIGTOP_DOCAL_REG5_U              DOCAL_REG5            ; // 0x0f8
    volatile RF_DIGTOP_CAL_REG8_U                CAL_REG8              ; // 0x0fc
    volatile RF_DIGTOP_DOCAL_REG6_U              DOCAL_REG6            ; // 0x100
    volatile RF_DIGTOP_DOCAL_REG7_U              DOCAL_REG7            ; // 0x104
    volatile RF_DIGTOP_DOCAL_REG8_U              DOCAL_REG8            ; // 0x108
    volatile RF_DIGTOP_DOCAL_REG9_U              DOCAL_REG9            ; // 0x10c
    volatile RF_DIGTOP_DOCAL_REG10_U             DOCAL_REG10           ; // 0x110
    volatile RF_DIGTOP_DOCAL_REG11_U             DOCAL_REG11           ; // 0x114
    volatile RF_DIGTOP_DOCAL_REG12_U             DOCAL_REG12           ; // 0x118
    volatile RF_DIGTOP_DOCAL_REG13_U             DOCAL_REG13           ; // 0x11c
    volatile RF_DIGTOP_DOCAL_REG14_U             DOCAL_REG14           ; // 0x120
    volatile RF_DIGTOP_DOCAL_REG15_U             DOCAL_REG15           ; // 0x124
    volatile RF_DIGTOP_DOCAL_REG16_U             DOCAL_REG16           ; // 0x128
    volatile RF_DIGTOP_DOCAL_REG17_U             DOCAL_REG17           ; // 0x12c
    volatile RF_DIGTOP_DOCAL_REG18_U             DOCAL_REG18           ; // 0x130
    volatile RF_DIGTOP_DOCAL_REG19_U             DOCAL_REG19           ; // 0x134
    volatile RF_DIGTOP_DOCAL_REG20_U             DOCAL_REG20           ; // 0x138
    volatile RF_DIGTOP_DOCAL_REG21_U             DOCAL_REG21           ; // 0x13c
    volatile RF_DIGTOP_DOCAL_REG22_U             DOCAL_REG22           ; // 0x140
    volatile RF_DIGTOP_DOCAL_REG23_U             DOCAL_REG23           ; // 0x144
    volatile RF_DIGTOP_DOCAL_REG24_U             DOCAL_REG24           ; // 0x148
    volatile RF_DIGTOP_DOCAL_REG25_U             DOCAL_REG25           ; // 0x14c
    volatile RF_DIGTOP_DOCAL_REG26_U             DOCAL_REG26           ; // 0x150
    volatile RF_DIGTOP_DOCAL_REG27_U             DOCAL_REG27           ; // 0x154
    volatile RF_DIGTOP_DOCAL_REG28_U             DOCAL_REG28           ; // 0x158
    volatile RF_DIGTOP_DOCAL_REG29_U             DOCAL_REG29           ; // 0x15c
    volatile RF_DIGTOP_DOCAL_REG30_U             DOCAL_REG30           ; // 0x160
    volatile RF_DIGTOP_DOCAL_REG31_U             DOCAL_REG31           ; // 0x164
    volatile RF_DIGTOP_DOCAL_REG32_U             DOCAL_REG32           ; // 0x168
    volatile RF_DIGTOP_DOCAL_REG33_U             DOCAL_REG33           ; // 0x16c
    volatile RF_DIGTOP_DOCAL_REG34_U             DOCAL_REG34           ; // 0x170
    volatile RF_DIGTOP_DOCAL_REG35_U             DOCAL_REG35           ; // 0x174
    volatile RF_DIGTOP_DOCAL_REG36_U             DOCAL_REG36           ; // 0x178
    volatile RF_DIGTOP_DOCAL_REG37_U             DOCAL_REG37           ; // 0x17c
    volatile RF_DIGTOP_DOCAL_REG38_U             DOCAL_REG38           ; // 0x180
    volatile RF_DIGTOP_DOCAL_REG39_U             DOCAL_REG39           ; // 0x184
    volatile RF_DIGTOP_DOCAL_REG40_U             DOCAL_REG40           ; // 0x188
    volatile RF_DIGTOP_DOCAL_REG41_U             DOCAL_REG41           ; // 0x18c
    volatile RF_DIGTOP_DOCAL_REG42_U             DOCAL_REG42           ; // 0x190
    volatile RF_DIGTOP_DOCAL_REG43_U             DOCAL_REG43           ; // 0x194
    volatile RF_DIGTOP_DOCAL_REG44_U             DOCAL_REG44           ; // 0x198
    volatile RF_DIGTOP_DOCAL_REG45_U             DOCAL_REG45           ; // 0x19c
    volatile RF_DIGTOP_DOCAL_REG46_U             DOCAL_REG46           ; // 0x1a0
    volatile RF_DIGTOP_DOCAL_REG47_U             DOCAL_REG47           ; // 0x1a4
    volatile RF_DIGTOP_DOCAL_REG48_U             DOCAL_REG48           ; // 0x1a8
    volatile RF_DIGTOP_DOCAL_REG49_U             DOCAL_REG49           ; // 0x1ac
    volatile RF_DIGTOP_DOCAL_REG50_U             DOCAL_REG50           ; // 0x1b0
    volatile RF_DIGTOP_DOCAL_REG51_U             DOCAL_REG51           ; // 0x1b4
    volatile RF_DIGTOP_DOCAL_REG52_U             DOCAL_REG52           ; // 0x1b8
    volatile RF_DIGTOP_DOCAL_REG53_U             DOCAL_REG53           ; // 0x1bc
    volatile RF_DIGTOP_DOCAL_REG54_U             DOCAL_REG54           ; // 0x1c0
    volatile RF_DIGTOP_DOCAL_REG55_U             DOCAL_REG55           ; // 0x1c4
    volatile RF_DIGTOP_DOCAL_REG56_U             DOCAL_REG56           ; // 0x1c8
    volatile RF_DIGTOP_DOCAL_REG57_U             DOCAL_REG57           ; // 0x1cc
    volatile RF_DIGTOP_DOCAL_REG58_U             DOCAL_REG58           ; // 0x1d0
    volatile RF_DIGTOP_DOCAL_REG59_U             DOCAL_REG59           ; // 0x1d4
    volatile RF_DIGTOP_DOCAL_REG60_U             DOCAL_REG60           ; // 0x1d8
    volatile RF_DIGTOP_DOCAL_REG61_U             DOCAL_REG61           ; // 0x1dc
    volatile RF_DIGTOP_DOCAL_REG62_U             DOCAL_REG62           ; // 0x1e0
    volatile RF_DIGTOP_DOCAL_REG63_U             DOCAL_REG63           ; // 0x1e4
    volatile RF_DIGTOP_DOCAL_REG64_U             DOCAL_REG64           ; // 0x1e8
    volatile RF_DIGTOP_DOCAL_REG65_U             DOCAL_REG65           ; // 0x1ec
    volatile RF_DIGTOP_DOCAL_REG66_U             DOCAL_REG66           ; // 0x1f0
    volatile RF_DIGTOP_DOCAL_REG67_U             DOCAL_REG67           ; // 0x1f4
    volatile RF_DIGTOP_DOCAL_REG68_U             DOCAL_REG68           ; // 0x1f8
    volatile RF_DIGTOP_DOCAL_REG69_U             DOCAL_REG69           ; // 0x1fc
    volatile RF_DIGTOP_BB_DPD_LUT_A00_U          BB_DPD_LUT_A00        ; // 0x200
    volatile RF_DIGTOP_BB_DPD_LUT_A01_U          BB_DPD_LUT_A01        ; // 0x204
    volatile RF_DIGTOP_BB_DPD_LUT_A02_U          BB_DPD_LUT_A02        ; // 0x208
    volatile RF_DIGTOP_BB_DPD_LUT_A03_U          BB_DPD_LUT_A03        ; // 0x20c
    volatile RF_DIGTOP_BB_DPD_LUT_A04_U          BB_DPD_LUT_A04        ; // 0x210
    volatile RF_DIGTOP_BB_DPD_LUT_A05_U          BB_DPD_LUT_A05        ; // 0x214
    volatile RF_DIGTOP_BB_DPD_LUT_A06_U          BB_DPD_LUT_A06        ; // 0x218
    volatile RF_DIGTOP_BB_DPD_LUT_A07_U          BB_DPD_LUT_A07        ; // 0x21c
    volatile RF_DIGTOP_BB_DPD_LUT_A08_U          BB_DPD_LUT_A08        ; // 0x220
    volatile RF_DIGTOP_BB_DPD_LUT_A09_U          BB_DPD_LUT_A09        ; // 0x224
    volatile RF_DIGTOP_BB_DPD_LUT_A10_U          BB_DPD_LUT_A10        ; // 0x228
    volatile RF_DIGTOP_BB_DPD_LUT_A11_U          BB_DPD_LUT_A11        ; // 0x22c
    volatile RF_DIGTOP_BB_DPD_LUT_A12_U          BB_DPD_LUT_A12        ; // 0x230
    volatile RF_DIGTOP_BB_DPD_LUT_A13_U          BB_DPD_LUT_A13        ; // 0x234
    volatile RF_DIGTOP_BB_DPD_LUT_A14_U          BB_DPD_LUT_A14        ; // 0x238
    volatile RF_DIGTOP_BB_DPD_LUT_A15_U          BB_DPD_LUT_A15        ; // 0x23c
    volatile RF_DIGTOP_BB_DPD_LUT_A16_U          BB_DPD_LUT_A16        ; // 0x240
    volatile RF_DIGTOP_BB_DPD_LUT_A17_U          BB_DPD_LUT_A17        ; // 0x244
    volatile RF_DIGTOP_BB_DPD_LUT_A18_U          BB_DPD_LUT_A18        ; // 0x248
    volatile RF_DIGTOP_BB_DPD_LUT_A19_U          BB_DPD_LUT_A19        ; // 0x24c
    volatile RF_DIGTOP_BB_DPD_LUT_A20_U          BB_DPD_LUT_A20        ; // 0x250
    volatile RF_DIGTOP_BB_DPD_LUT_A21_U          BB_DPD_LUT_A21        ; // 0x254
    volatile RF_DIGTOP_BB_DPD_LUT_A22_U          BB_DPD_LUT_A22        ; // 0x258
    volatile RF_DIGTOP_BB_DPD_LUT_A23_U          BB_DPD_LUT_A23        ; // 0x25c
    volatile RF_DIGTOP_BB_DPD_LUT_A24_U          BB_DPD_LUT_A24        ; // 0x260
    volatile RF_DIGTOP_BB_DPD_LUT_A25_U          BB_DPD_LUT_A25        ; // 0x264
    volatile RF_DIGTOP_BB_DPD_LUT_A26_U          BB_DPD_LUT_A26        ; // 0x268
    volatile RF_DIGTOP_BB_DPD_LUT_A27_U          BB_DPD_LUT_A27        ; // 0x26c
    volatile RF_DIGTOP_BB_DPD_LUT_A28_U          BB_DPD_LUT_A28        ; // 0x270
    volatile RF_DIGTOP_BB_DPD_LUT_A29_U          BB_DPD_LUT_A29        ; // 0x274
    volatile RF_DIGTOP_BB_DPD_LUT_A30_U          BB_DPD_LUT_A30        ; // 0x278
    volatile RF_DIGTOP_BB_DPD_LUT_A31_U          BB_DPD_LUT_A31        ; // 0x27c
    volatile RF_DIGTOP_PA_DPD_LUT_A00_U          PA_DPD_LUT_A00        ; // 0x280
    volatile RF_DIGTOP_PA_DPD_LUT_A01_U          PA_DPD_LUT_A01        ; // 0x284
    volatile RF_DIGTOP_PA_DPD_LUT_A02_U          PA_DPD_LUT_A02        ; // 0x288
    volatile RF_DIGTOP_PA_DPD_LUT_A03_U          PA_DPD_LUT_A03        ; // 0x28c
    volatile RF_DIGTOP_PA_DPD_LUT_A04_U          PA_DPD_LUT_A04        ; // 0x290
    volatile RF_DIGTOP_PA_DPD_LUT_A05_U          PA_DPD_LUT_A05        ; // 0x294
    volatile RF_DIGTOP_PA_DPD_LUT_A06_U          PA_DPD_LUT_A06        ; // 0x298
    volatile RF_DIGTOP_PA_DPD_LUT_A07_U          PA_DPD_LUT_A07        ; // 0x29c
    volatile RF_DIGTOP_PA_DPD_LUT_A08_U          PA_DPD_LUT_A08        ; // 0x2a0
    volatile RF_DIGTOP_PA_DPD_LUT_A09_U          PA_DPD_LUT_A09        ; // 0x2a4
    volatile RF_DIGTOP_PA_DPD_LUT_A10_U          PA_DPD_LUT_A10        ; // 0x2a8
    volatile RF_DIGTOP_PA_DPD_LUT_A11_U          PA_DPD_LUT_A11        ; // 0x2ac
    volatile RF_DIGTOP_PA_DPD_LUT_A12_U          PA_DPD_LUT_A12        ; // 0x2b0
    volatile RF_DIGTOP_PA_DPD_LUT_A13_U          PA_DPD_LUT_A13        ; // 0x2b4
    volatile RF_DIGTOP_PA_DPD_LUT_A14_U          PA_DPD_LUT_A14        ; // 0x2b8
    volatile RF_DIGTOP_PA_DPD_LUT_A15_U          PA_DPD_LUT_A15        ; // 0x2bc
    volatile RF_DIGTOP_PA_DPD_LUT_A16_U          PA_DPD_LUT_A16        ; // 0x2c0
    volatile RF_DIGTOP_PA_DPD_LUT_A17_U          PA_DPD_LUT_A17        ; // 0x2c4
    volatile RF_DIGTOP_PA_DPD_LUT_A18_U          PA_DPD_LUT_A18        ; // 0x2c8
    volatile RF_DIGTOP_PA_DPD_LUT_A19_U          PA_DPD_LUT_A19        ; // 0x2cc
    volatile RF_DIGTOP_PA_DPD_LUT_A20_U          PA_DPD_LUT_A20        ; // 0x2d0
    volatile RF_DIGTOP_PA_DPD_LUT_A21_U          PA_DPD_LUT_A21        ; // 0x2d4
    volatile RF_DIGTOP_PA_DPD_LUT_A22_U          PA_DPD_LUT_A22        ; // 0x2d8
    volatile RF_DIGTOP_PA_DPD_LUT_A23_U          PA_DPD_LUT_A23        ; // 0x2dc
    volatile RF_DIGTOP_PA_DPD_LUT_A24_U          PA_DPD_LUT_A24        ; // 0x2e0
    volatile RF_DIGTOP_PA_DPD_LUT_A25_U          PA_DPD_LUT_A25        ; // 0x2e4
    volatile RF_DIGTOP_PA_DPD_LUT_A26_U          PA_DPD_LUT_A26        ; // 0x2e8
    volatile RF_DIGTOP_PA_DPD_LUT_A27_U          PA_DPD_LUT_A27        ; // 0x2ec
    volatile RF_DIGTOP_PA_DPD_LUT_A28_U          PA_DPD_LUT_A28        ; // 0x2f0
    volatile RF_DIGTOP_PA_DPD_LUT_A29_U          PA_DPD_LUT_A29        ; // 0x2f4
    volatile RF_DIGTOP_PA_DPD_LUT_A30_U          PA_DPD_LUT_A30        ; // 0x2f8
    volatile RF_DIGTOP_PA_DPD_LUT_A31_U          PA_DPD_LUT_A31        ; // 0x2fc
    volatile RF_DIGTOP_PA_DPD_LUT_A32_U          PA_DPD_LUT_A32        ; // 0x300
    volatile RF_DIGTOP_PA_DPD_LUT_A33_U          PA_DPD_LUT_A33        ; // 0x304
    volatile RF_DIGTOP_PA_DPD_LUT_A34_U          PA_DPD_LUT_A34        ; // 0x308
    volatile RF_DIGTOP_PA_DPD_LUT_A35_U          PA_DPD_LUT_A35        ; // 0x30c
    volatile RF_DIGTOP_PA_DPD_LUT_A36_U          PA_DPD_LUT_A36        ; // 0x310
    volatile RF_DIGTOP_PA_DPD_LUT_A37_U          PA_DPD_LUT_A37        ; // 0x314
    volatile RF_DIGTOP_PA_DPD_LUT_A38_U          PA_DPD_LUT_A38        ; // 0x318
    volatile RF_DIGTOP_PA_DPD_LUT_A39_U          PA_DPD_LUT_A39        ; // 0x31c
    volatile RF_DIGTOP_PA_DPD_LUT_A40_U          PA_DPD_LUT_A40        ; // 0x320
    volatile RF_DIGTOP_PA_DPD_LUT_A41_U          PA_DPD_LUT_A41        ; // 0x324
    volatile RF_DIGTOP_PA_DPD_LUT_A42_U          PA_DPD_LUT_A42        ; // 0x328
    volatile RF_DIGTOP_PA_DPD_LUT_A43_U          PA_DPD_LUT_A43        ; // 0x32c
    volatile RF_DIGTOP_PA_DPD_LUT_A44_U          PA_DPD_LUT_A44        ; // 0x330
    volatile RF_DIGTOP_PA_DPD_LUT_A45_U          PA_DPD_LUT_A45        ; // 0x334
    volatile RF_DIGTOP_PA_DPD_LUT_A46_U          PA_DPD_LUT_A46        ; // 0x338
    volatile RF_DIGTOP_PA_DPD_LUT_A47_U          PA_DPD_LUT_A47        ; // 0x33c
    volatile RF_DIGTOP_PA_DPD_LUT_A48_U          PA_DPD_LUT_A48        ; // 0x340
    volatile RF_DIGTOP_PA_DPD_LUT_A49_U          PA_DPD_LUT_A49        ; // 0x344
    volatile RF_DIGTOP_PA_DPD_LUT_A50_U          PA_DPD_LUT_A50        ; // 0x348
    volatile RF_DIGTOP_PA_DPD_LUT_A51_U          PA_DPD_LUT_A51        ; // 0x34c
    volatile RF_DIGTOP_PA_DPD_LUT_A52_U          PA_DPD_LUT_A52        ; // 0x350
    volatile RF_DIGTOP_PA_DPD_LUT_A53_U          PA_DPD_LUT_A53        ; // 0x354
    volatile RF_DIGTOP_PA_DPD_LUT_A54_U          PA_DPD_LUT_A54        ; // 0x358
    volatile RF_DIGTOP_PA_DPD_LUT_A55_U          PA_DPD_LUT_A55        ; // 0x35c
    volatile RF_DIGTOP_PA_DPD_LUT_A56_U          PA_DPD_LUT_A56        ; // 0x360
    volatile RF_DIGTOP_PA_DPD_LUT_A57_U          PA_DPD_LUT_A57        ; // 0x364
    volatile RF_DIGTOP_PA_DPD_LUT_A58_U          PA_DPD_LUT_A58        ; // 0x368
    volatile RF_DIGTOP_PA_DPD_LUT_A59_U          PA_DPD_LUT_A59        ; // 0x36c
    volatile RF_DIGTOP_PA_DPD_LUT_A60_U          PA_DPD_LUT_A60        ; // 0x370
    volatile RF_DIGTOP_PA_DPD_LUT_A61_U          PA_DPD_LUT_A61        ; // 0x374
    volatile RF_DIGTOP_PA_DPD_LUT_A62_U          PA_DPD_LUT_A62        ; // 0x378
    volatile RF_DIGTOP_PA_DPD_LUT_A63_U          PA_DPD_LUT_A63        ; // 0x37c
    volatile RF_DIGTOP_BB_DPD_LUT_B00_U          BB_DPD_LUT_B00        ; // 0x380
    volatile RF_DIGTOP_BB_DPD_LUT_B01_U          BB_DPD_LUT_B01        ; // 0x384
    volatile RF_DIGTOP_BB_DPD_LUT_B02_U          BB_DPD_LUT_B02        ; // 0x388
    volatile RF_DIGTOP_BB_DPD_LUT_B03_U          BB_DPD_LUT_B03        ; // 0x38c
    volatile RF_DIGTOP_BB_DPD_LUT_B04_U          BB_DPD_LUT_B04        ; // 0x390
    volatile RF_DIGTOP_BB_DPD_LUT_B05_U          BB_DPD_LUT_B05        ; // 0x394
    volatile RF_DIGTOP_BB_DPD_LUT_B06_U          BB_DPD_LUT_B06        ; // 0x398
    volatile RF_DIGTOP_BB_DPD_LUT_B07_U          BB_DPD_LUT_B07        ; // 0x39c
    volatile RF_DIGTOP_BB_DPD_LUT_B08_U          BB_DPD_LUT_B08        ; // 0x3a0
    volatile RF_DIGTOP_BB_DPD_LUT_B09_U          BB_DPD_LUT_B09        ; // 0x3a4
    volatile RF_DIGTOP_BB_DPD_LUT_B10_U          BB_DPD_LUT_B10        ; // 0x3a8
    volatile RF_DIGTOP_BB_DPD_LUT_B11_U          BB_DPD_LUT_B11        ; // 0x3ac
    volatile RF_DIGTOP_BB_DPD_LUT_B12_U          BB_DPD_LUT_B12        ; // 0x3b0
    volatile RF_DIGTOP_BB_DPD_LUT_B13_U          BB_DPD_LUT_B13        ; // 0x3b4
    volatile RF_DIGTOP_BB_DPD_LUT_B14_U          BB_DPD_LUT_B14        ; // 0x3b8
    volatile RF_DIGTOP_BB_DPD_LUT_B15_U          BB_DPD_LUT_B15        ; // 0x3bc
    volatile RF_DIGTOP_BB_DPD_LUT_B16_U          BB_DPD_LUT_B16        ; // 0x3c0
    volatile RF_DIGTOP_BB_DPD_LUT_B17_U          BB_DPD_LUT_B17        ; // 0x3c4
    volatile RF_DIGTOP_BB_DPD_LUT_B18_U          BB_DPD_LUT_B18        ; // 0x3c8
    volatile RF_DIGTOP_BB_DPD_LUT_B19_U          BB_DPD_LUT_B19        ; // 0x3cc
    volatile RF_DIGTOP_BB_DPD_LUT_B20_U          BB_DPD_LUT_B20        ; // 0x3d0
    volatile RF_DIGTOP_BB_DPD_LUT_B21_U          BB_DPD_LUT_B21        ; // 0x3d4
    volatile RF_DIGTOP_BB_DPD_LUT_B22_U          BB_DPD_LUT_B22        ; // 0x3d8
    volatile RF_DIGTOP_BB_DPD_LUT_B23_U          BB_DPD_LUT_B23        ; // 0x3dc
    volatile RF_DIGTOP_BB_DPD_LUT_B24_U          BB_DPD_LUT_B24        ; // 0x3e0
    volatile RF_DIGTOP_BB_DPD_LUT_B25_U          BB_DPD_LUT_B25        ; // 0x3e4
    volatile RF_DIGTOP_BB_DPD_LUT_B26_U          BB_DPD_LUT_B26        ; // 0x3e8
    volatile RF_DIGTOP_BB_DPD_LUT_B27_U          BB_DPD_LUT_B27        ; // 0x3ec
    volatile RF_DIGTOP_BB_DPD_LUT_B28_U          BB_DPD_LUT_B28        ; // 0x3f0
    volatile RF_DIGTOP_BB_DPD_LUT_B29_U          BB_DPD_LUT_B29        ; // 0x3f4
    volatile RF_DIGTOP_BB_DPD_LUT_B30_U          BB_DPD_LUT_B30        ; // 0x3f8
    volatile RF_DIGTOP_BB_DPD_LUT_B31_U          BB_DPD_LUT_B31        ; // 0x3fc
    volatile RF_DIGTOP_PA_DPD_LUT_B00_U          PA_DPD_LUT_B00        ; // 0x400
    volatile RF_DIGTOP_PA_DPD_LUT_B01_U          PA_DPD_LUT_B01        ; // 0x404
    volatile RF_DIGTOP_PA_DPD_LUT_B02_U          PA_DPD_LUT_B02        ; // 0x408
    volatile RF_DIGTOP_PA_DPD_LUT_B03_U          PA_DPD_LUT_B03        ; // 0x40c
    volatile RF_DIGTOP_PA_DPD_LUT_B04_U          PA_DPD_LUT_B04        ; // 0x410
    volatile RF_DIGTOP_PA_DPD_LUT_B05_U          PA_DPD_LUT_B05        ; // 0x414
    volatile RF_DIGTOP_PA_DPD_LUT_B06_U          PA_DPD_LUT_B06        ; // 0x418
    volatile RF_DIGTOP_PA_DPD_LUT_B07_U          PA_DPD_LUT_B07        ; // 0x41c
    volatile RF_DIGTOP_PA_DPD_LUT_B08_U          PA_DPD_LUT_B08        ; // 0x420
    volatile RF_DIGTOP_PA_DPD_LUT_B09_U          PA_DPD_LUT_B09        ; // 0x424
    volatile RF_DIGTOP_PA_DPD_LUT_B10_U          PA_DPD_LUT_B10        ; // 0x428
    volatile RF_DIGTOP_PA_DPD_LUT_B11_U          PA_DPD_LUT_B11        ; // 0x42c
    volatile RF_DIGTOP_PA_DPD_LUT_B12_U          PA_DPD_LUT_B12        ; // 0x430
    volatile RF_DIGTOP_PA_DPD_LUT_B13_U          PA_DPD_LUT_B13        ; // 0x434
    volatile RF_DIGTOP_PA_DPD_LUT_B14_U          PA_DPD_LUT_B14        ; // 0x438
    volatile RF_DIGTOP_PA_DPD_LUT_B15_U          PA_DPD_LUT_B15        ; // 0x43c
    volatile RF_DIGTOP_PA_DPD_LUT_B16_U          PA_DPD_LUT_B16        ; // 0x440
    volatile RF_DIGTOP_PA_DPD_LUT_B17_U          PA_DPD_LUT_B17        ; // 0x444
    volatile RF_DIGTOP_PA_DPD_LUT_B18_U          PA_DPD_LUT_B18        ; // 0x448
    volatile RF_DIGTOP_PA_DPD_LUT_B19_U          PA_DPD_LUT_B19        ; // 0x44c
    volatile RF_DIGTOP_PA_DPD_LUT_B20_U          PA_DPD_LUT_B20        ; // 0x450
    volatile RF_DIGTOP_PA_DPD_LUT_B21_U          PA_DPD_LUT_B21        ; // 0x454
    volatile RF_DIGTOP_PA_DPD_LUT_B22_U          PA_DPD_LUT_B22        ; // 0x458
    volatile RF_DIGTOP_PA_DPD_LUT_B23_U          PA_DPD_LUT_B23        ; // 0x45c
    volatile RF_DIGTOP_PA_DPD_LUT_B24_U          PA_DPD_LUT_B24        ; // 0x460
    volatile RF_DIGTOP_PA_DPD_LUT_B25_U          PA_DPD_LUT_B25        ; // 0x464
    volatile RF_DIGTOP_PA_DPD_LUT_B26_U          PA_DPD_LUT_B26        ; // 0x468
    volatile RF_DIGTOP_PA_DPD_LUT_B27_U          PA_DPD_LUT_B27        ; // 0x46c
    volatile RF_DIGTOP_PA_DPD_LUT_B28_U          PA_DPD_LUT_B28        ; // 0x470
    volatile RF_DIGTOP_PA_DPD_LUT_B29_U          PA_DPD_LUT_B29        ; // 0x474
    volatile RF_DIGTOP_PA_DPD_LUT_B30_U          PA_DPD_LUT_B30        ; // 0x478
    volatile RF_DIGTOP_PA_DPD_LUT_B31_U          PA_DPD_LUT_B31        ; // 0x47c
    volatile RF_DIGTOP_PA_DPD_LUT_B32_U          PA_DPD_LUT_B32        ; // 0x480
    volatile RF_DIGTOP_PA_DPD_LUT_B33_U          PA_DPD_LUT_B33        ; // 0x484
    volatile RF_DIGTOP_PA_DPD_LUT_B34_U          PA_DPD_LUT_B34        ; // 0x488
    volatile RF_DIGTOP_PA_DPD_LUT_B35_U          PA_DPD_LUT_B35        ; // 0x48c
    volatile RF_DIGTOP_PA_DPD_LUT_B36_U          PA_DPD_LUT_B36        ; // 0x490
    volatile RF_DIGTOP_PA_DPD_LUT_B37_U          PA_DPD_LUT_B37        ; // 0x494
    volatile RF_DIGTOP_PA_DPD_LUT_B38_U          PA_DPD_LUT_B38        ; // 0x498
    volatile RF_DIGTOP_PA_DPD_LUT_B39_U          PA_DPD_LUT_B39        ; // 0x49c
    volatile RF_DIGTOP_PA_DPD_LUT_B40_U          PA_DPD_LUT_B40        ; // 0x4a0
    volatile RF_DIGTOP_PA_DPD_LUT_B41_U          PA_DPD_LUT_B41        ; // 0x4a4
    volatile RF_DIGTOP_PA_DPD_LUT_B42_U          PA_DPD_LUT_B42        ; // 0x4a8
    volatile RF_DIGTOP_PA_DPD_LUT_B43_U          PA_DPD_LUT_B43        ; // 0x4ac
    volatile RF_DIGTOP_PA_DPD_LUT_B44_U          PA_DPD_LUT_B44        ; // 0x4b0
    volatile RF_DIGTOP_PA_DPD_LUT_B45_U          PA_DPD_LUT_B45        ; // 0x4b4
    volatile RF_DIGTOP_PA_DPD_LUT_B46_U          PA_DPD_LUT_B46        ; // 0x4b8
    volatile RF_DIGTOP_PA_DPD_LUT_B47_U          PA_DPD_LUT_B47        ; // 0x4bc
    volatile RF_DIGTOP_PA_DPD_LUT_B48_U          PA_DPD_LUT_B48        ; // 0x4c0
    volatile RF_DIGTOP_PA_DPD_LUT_B49_U          PA_DPD_LUT_B49        ; // 0x4c4
    volatile RF_DIGTOP_PA_DPD_LUT_B50_U          PA_DPD_LUT_B50        ; // 0x4c8
    volatile RF_DIGTOP_PA_DPD_LUT_B51_U          PA_DPD_LUT_B51        ; // 0x4cc
    volatile RF_DIGTOP_PA_DPD_LUT_B52_U          PA_DPD_LUT_B52        ; // 0x4d0
    volatile RF_DIGTOP_PA_DPD_LUT_B53_U          PA_DPD_LUT_B53        ; // 0x4d4
    volatile RF_DIGTOP_PA_DPD_LUT_B54_U          PA_DPD_LUT_B54        ; // 0x4d8
    volatile RF_DIGTOP_PA_DPD_LUT_B55_U          PA_DPD_LUT_B55        ; // 0x4dc
    volatile RF_DIGTOP_PA_DPD_LUT_B56_U          PA_DPD_LUT_B56        ; // 0x4e0
    volatile RF_DIGTOP_PA_DPD_LUT_B57_U          PA_DPD_LUT_B57        ; // 0x4e4
    volatile RF_DIGTOP_PA_DPD_LUT_B58_U          PA_DPD_LUT_B58        ; // 0x4e8
    volatile RF_DIGTOP_PA_DPD_LUT_B59_U          PA_DPD_LUT_B59        ; // 0x4ec
    volatile RF_DIGTOP_PA_DPD_LUT_B60_U          PA_DPD_LUT_B60        ; // 0x4f0
    volatile RF_DIGTOP_PA_DPD_LUT_B61_U          PA_DPD_LUT_B61        ; // 0x4f4
    volatile RF_DIGTOP_PA_DPD_LUT_B62_U          PA_DPD_LUT_B62        ; // 0x4f8
    volatile RF_DIGTOP_PA_DPD_LUT_B63_U          PA_DPD_LUT_B63        ; // 0x4fc
    volatile RF_DIGTOP_BB_DPD_LUT_C00_U          BB_DPD_LUT_C00        ; // 0x500
    volatile RF_DIGTOP_BB_DPD_LUT_C01_U          BB_DPD_LUT_C01        ; // 0x504
    volatile RF_DIGTOP_BB_DPD_LUT_C02_U          BB_DPD_LUT_C02        ; // 0x508
    volatile RF_DIGTOP_BB_DPD_LUT_C03_U          BB_DPD_LUT_C03        ; // 0x50c
    volatile RF_DIGTOP_BB_DPD_LUT_C04_U          BB_DPD_LUT_C04        ; // 0x510
    volatile RF_DIGTOP_BB_DPD_LUT_C05_U          BB_DPD_LUT_C05        ; // 0x514
    volatile RF_DIGTOP_BB_DPD_LUT_C06_U          BB_DPD_LUT_C06        ; // 0x518
    volatile RF_DIGTOP_BB_DPD_LUT_C07_U          BB_DPD_LUT_C07        ; // 0x51c
    volatile RF_DIGTOP_BB_DPD_LUT_C08_U          BB_DPD_LUT_C08        ; // 0x520
    volatile RF_DIGTOP_BB_DPD_LUT_C09_U          BB_DPD_LUT_C09        ; // 0x524
    volatile RF_DIGTOP_BB_DPD_LUT_C10_U          BB_DPD_LUT_C10        ; // 0x528
    volatile RF_DIGTOP_BB_DPD_LUT_C11_U          BB_DPD_LUT_C11        ; // 0x52c
    volatile RF_DIGTOP_BB_DPD_LUT_C12_U          BB_DPD_LUT_C12        ; // 0x530
    volatile RF_DIGTOP_BB_DPD_LUT_C13_U          BB_DPD_LUT_C13        ; // 0x534
    volatile RF_DIGTOP_BB_DPD_LUT_C14_U          BB_DPD_LUT_C14        ; // 0x538
    volatile RF_DIGTOP_BB_DPD_LUT_C15_U          BB_DPD_LUT_C15        ; // 0x53c
    volatile RF_DIGTOP_BB_DPD_LUT_C16_U          BB_DPD_LUT_C16        ; // 0x540
    volatile RF_DIGTOP_BB_DPD_LUT_C17_U          BB_DPD_LUT_C17        ; // 0x544
    volatile RF_DIGTOP_BB_DPD_LUT_C18_U          BB_DPD_LUT_C18        ; // 0x548
    volatile RF_DIGTOP_BB_DPD_LUT_C19_U          BB_DPD_LUT_C19        ; // 0x54c
    volatile RF_DIGTOP_BB_DPD_LUT_C20_U          BB_DPD_LUT_C20        ; // 0x550
    volatile RF_DIGTOP_BB_DPD_LUT_C21_U          BB_DPD_LUT_C21        ; // 0x554
    volatile RF_DIGTOP_BB_DPD_LUT_C22_U          BB_DPD_LUT_C22        ; // 0x558
    volatile RF_DIGTOP_BB_DPD_LUT_C23_U          BB_DPD_LUT_C23        ; // 0x55c
    volatile RF_DIGTOP_BB_DPD_LUT_C24_U          BB_DPD_LUT_C24        ; // 0x560
    volatile RF_DIGTOP_BB_DPD_LUT_C25_U          BB_DPD_LUT_C25        ; // 0x564
    volatile RF_DIGTOP_BB_DPD_LUT_C26_U          BB_DPD_LUT_C26        ; // 0x568
    volatile RF_DIGTOP_BB_DPD_LUT_C27_U          BB_DPD_LUT_C27        ; // 0x56c
    volatile RF_DIGTOP_BB_DPD_LUT_C28_U          BB_DPD_LUT_C28        ; // 0x570
    volatile RF_DIGTOP_BB_DPD_LUT_C29_U          BB_DPD_LUT_C29        ; // 0x574
    volatile RF_DIGTOP_BB_DPD_LUT_C30_U          BB_DPD_LUT_C30        ; // 0x578
    volatile RF_DIGTOP_BB_DPD_LUT_C31_U          BB_DPD_LUT_C31        ; // 0x57c
    volatile RF_DIGTOP_PA_DPD_LUT_C00_U          PA_DPD_LUT_C00        ; // 0x580
    volatile RF_DIGTOP_PA_DPD_LUT_C01_U          PA_DPD_LUT_C01        ; // 0x584
    volatile RF_DIGTOP_PA_DPD_LUT_C02_U          PA_DPD_LUT_C02        ; // 0x588
    volatile RF_DIGTOP_PA_DPD_LUT_C03_U          PA_DPD_LUT_C03        ; // 0x58c
    volatile RF_DIGTOP_PA_DPD_LUT_C04_U          PA_DPD_LUT_C04        ; // 0x590
    volatile RF_DIGTOP_PA_DPD_LUT_C05_U          PA_DPD_LUT_C05        ; // 0x594
    volatile RF_DIGTOP_PA_DPD_LUT_C06_U          PA_DPD_LUT_C06        ; // 0x598
    volatile RF_DIGTOP_PA_DPD_LUT_C07_U          PA_DPD_LUT_C07        ; // 0x59c
    volatile RF_DIGTOP_PA_DPD_LUT_C08_U          PA_DPD_LUT_C08        ; // 0x5a0
    volatile RF_DIGTOP_PA_DPD_LUT_C09_U          PA_DPD_LUT_C09        ; // 0x5a4
    volatile RF_DIGTOP_PA_DPD_LUT_C10_U          PA_DPD_LUT_C10        ; // 0x5a8
    volatile RF_DIGTOP_PA_DPD_LUT_C11_U          PA_DPD_LUT_C11        ; // 0x5ac
    volatile RF_DIGTOP_PA_DPD_LUT_C12_U          PA_DPD_LUT_C12        ; // 0x5b0
    volatile RF_DIGTOP_PA_DPD_LUT_C13_U          PA_DPD_LUT_C13        ; // 0x5b4
    volatile RF_DIGTOP_PA_DPD_LUT_C14_U          PA_DPD_LUT_C14        ; // 0x5b8
    volatile RF_DIGTOP_PA_DPD_LUT_C15_U          PA_DPD_LUT_C15        ; // 0x5bc
    volatile RF_DIGTOP_PA_DPD_LUT_C16_U          PA_DPD_LUT_C16        ; // 0x5c0
    volatile RF_DIGTOP_PA_DPD_LUT_C17_U          PA_DPD_LUT_C17        ; // 0x5c4
    volatile RF_DIGTOP_PA_DPD_LUT_C18_U          PA_DPD_LUT_C18        ; // 0x5c8
    volatile RF_DIGTOP_PA_DPD_LUT_C19_U          PA_DPD_LUT_C19        ; // 0x5cc
    volatile RF_DIGTOP_PA_DPD_LUT_C20_U          PA_DPD_LUT_C20        ; // 0x5d0
    volatile RF_DIGTOP_PA_DPD_LUT_C21_U          PA_DPD_LUT_C21        ; // 0x5d4
    volatile RF_DIGTOP_PA_DPD_LUT_C22_U          PA_DPD_LUT_C22        ; // 0x5d8
    volatile RF_DIGTOP_PA_DPD_LUT_C23_U          PA_DPD_LUT_C23        ; // 0x5dc
    volatile RF_DIGTOP_PA_DPD_LUT_C24_U          PA_DPD_LUT_C24        ; // 0x5e0
    volatile RF_DIGTOP_PA_DPD_LUT_C25_U          PA_DPD_LUT_C25        ; // 0x5e4
    volatile RF_DIGTOP_PA_DPD_LUT_C26_U          PA_DPD_LUT_C26        ; // 0x5e8
    volatile RF_DIGTOP_PA_DPD_LUT_C27_U          PA_DPD_LUT_C27        ; // 0x5ec
    volatile RF_DIGTOP_PA_DPD_LUT_C28_U          PA_DPD_LUT_C28        ; // 0x5f0
    volatile RF_DIGTOP_PA_DPD_LUT_C29_U          PA_DPD_LUT_C29        ; // 0x5f4
    volatile RF_DIGTOP_PA_DPD_LUT_C30_U          PA_DPD_LUT_C30        ; // 0x5f8
    volatile RF_DIGTOP_PA_DPD_LUT_C31_U          PA_DPD_LUT_C31        ; // 0x5fc
    volatile RF_DIGTOP_PA_DPD_LUT_C32_U          PA_DPD_LUT_C32        ; // 0x600
    volatile RF_DIGTOP_PA_DPD_LUT_C33_U          PA_DPD_LUT_C33        ; // 0x604
    volatile RF_DIGTOP_PA_DPD_LUT_C34_U          PA_DPD_LUT_C34        ; // 0x608
    volatile RF_DIGTOP_PA_DPD_LUT_C35_U          PA_DPD_LUT_C35        ; // 0x60c
    volatile RF_DIGTOP_PA_DPD_LUT_C36_U          PA_DPD_LUT_C36        ; // 0x610
    volatile RF_DIGTOP_PA_DPD_LUT_C37_U          PA_DPD_LUT_C37        ; // 0x614
    volatile RF_DIGTOP_PA_DPD_LUT_C38_U          PA_DPD_LUT_C38        ; // 0x618
    volatile RF_DIGTOP_PA_DPD_LUT_C39_U          PA_DPD_LUT_C39        ; // 0x61c
    volatile RF_DIGTOP_PA_DPD_LUT_C40_U          PA_DPD_LUT_C40        ; // 0x620
    volatile RF_DIGTOP_PA_DPD_LUT_C41_U          PA_DPD_LUT_C41        ; // 0x624
    volatile RF_DIGTOP_PA_DPD_LUT_C42_U          PA_DPD_LUT_C42        ; // 0x628
    volatile RF_DIGTOP_PA_DPD_LUT_C43_U          PA_DPD_LUT_C43        ; // 0x62c
    volatile RF_DIGTOP_PA_DPD_LUT_C44_U          PA_DPD_LUT_C44        ; // 0x630
    volatile RF_DIGTOP_PA_DPD_LUT_C45_U          PA_DPD_LUT_C45        ; // 0x634
    volatile RF_DIGTOP_PA_DPD_LUT_C46_U          PA_DPD_LUT_C46        ; // 0x638
    volatile RF_DIGTOP_PA_DPD_LUT_C47_U          PA_DPD_LUT_C47        ; // 0x63c
    volatile RF_DIGTOP_PA_DPD_LUT_C48_U          PA_DPD_LUT_C48        ; // 0x640
    volatile RF_DIGTOP_PA_DPD_LUT_C49_U          PA_DPD_LUT_C49        ; // 0x644
    volatile RF_DIGTOP_PA_DPD_LUT_C50_U          PA_DPD_LUT_C50        ; // 0x648
    volatile RF_DIGTOP_PA_DPD_LUT_C51_U          PA_DPD_LUT_C51        ; // 0x64c
    volatile RF_DIGTOP_PA_DPD_LUT_C52_U          PA_DPD_LUT_C52        ; // 0x650
    volatile RF_DIGTOP_PA_DPD_LUT_C53_U          PA_DPD_LUT_C53        ; // 0x654
    volatile RF_DIGTOP_PA_DPD_LUT_C54_U          PA_DPD_LUT_C54        ; // 0x658
    volatile RF_DIGTOP_PA_DPD_LUT_C55_U          PA_DPD_LUT_C55        ; // 0x65c
    volatile RF_DIGTOP_PA_DPD_LUT_C56_U          PA_DPD_LUT_C56        ; // 0x660
    volatile RF_DIGTOP_PA_DPD_LUT_C57_U          PA_DPD_LUT_C57        ; // 0x664
    volatile RF_DIGTOP_PA_DPD_LUT_C58_U          PA_DPD_LUT_C58        ; // 0x668
    volatile RF_DIGTOP_PA_DPD_LUT_C59_U          PA_DPD_LUT_C59        ; // 0x66c
    volatile RF_DIGTOP_PA_DPD_LUT_C60_U          PA_DPD_LUT_C60        ; // 0x670
    volatile RF_DIGTOP_PA_DPD_LUT_C61_U          PA_DPD_LUT_C61        ; // 0x674
    volatile RF_DIGTOP_PA_DPD_LUT_C62_U          PA_DPD_LUT_C62        ; // 0x678
    volatile RF_DIGTOP_PA_DPD_LUT_C63_U          PA_DPD_LUT_C63        ; // 0x67c
    volatile RF_DIGTOP_TH_BB_MAGA_0_U            TH_BB_MAGA_0          ; // 0x680
    volatile RF_DIGTOP_TH_BB_MAGA_1_U            TH_BB_MAGA_1          ; // 0x684
    volatile RF_DIGTOP_TH_BB_MAGB_0_U            TH_BB_MAGB_0          ; // 0x688
    volatile RF_DIGTOP_TH_BB_MAGB_1_U            TH_BB_MAGB_1          ; // 0x68c
    volatile RF_DIGTOP_TH_BB_MAGC_0_U            TH_BB_MAGC_0          ; // 0x690
    volatile RF_DIGTOP_TH_BB_MAGC_1_U            TH_BB_MAGC_1          ; // 0x694
    volatile RF_DIGTOP_TH_PA_MAGA_0_U            TH_PA_MAGA_0          ; // 0x698
    volatile RF_DIGTOP_TH_PA_MAGA_1_U            TH_PA_MAGA_1          ; // 0x69c
    volatile RF_DIGTOP_TH_PA_MAGB_0_U            TH_PA_MAGB_0          ; // 0x6a0
    volatile RF_DIGTOP_TH_PA_MAGB_1_U            TH_PA_MAGB_1          ; // 0x6a4
    volatile RF_DIGTOP_TH_PA_MAGC_0_U            TH_PA_MAGC_0          ; // 0x6a8
    volatile RF_DIGTOP_TH_PA_MAGC_1_U            TH_PA_MAGC_1          ; // 0x6ac
    volatile RF_DIGTOP_TH_CFR_MAG_U              TH_CFR_MAG            ; // 0x6b0
    volatile RF_DIGTOP_DPD_CTRL_SET_U            DPD_CTRL_SET          ; // 0x6b4
    volatile RF_DIGTOP_TXCAL_CTRL_SET_U          TXCAL_CTRL_SET        ; // 0x6b8
    volatile RF_DIGTOP_TX_IQ_PARA_0_U            TX_IQ_PARA_0          ; // 0x6bc
    volatile RF_DIGTOP_TX_IQ_PARA_1_U            TX_IQ_PARA_1          ; // 0x6c0
    volatile RF_DIGTOP_TX_LO_PARA_0_U            TX_LO_PARA_0          ; // 0x6c4
    volatile RF_DIGTOP_TX_LO_PARA_1_U            TX_LO_PARA_1          ; // 0x6c8
    volatile RF_DIGTOP_RAMP_PRD_0_U              RAMP_PRD_0            ; // 0x6cc
    volatile RF_DIGTOP_RAMP_PRD_1_U              RAMP_PRD_1            ; // 0x6d0
    volatile RF_DIGTOP_RAMP_MUL_SET0_U           RAMP_MUL_SET0         ; // 0x6d4
    volatile RF_DIGTOP_RAMP_MUL_SET1_U           RAMP_MUL_SET1         ; // 0x6d8
    volatile RF_DIGTOP_RAMP_MUL_SET2_U           RAMP_MUL_SET2         ; // 0x6dc
    volatile RF_DIGTOP_RAMP_MUL_SET3_U           RAMP_MUL_SET3         ; // 0x6e0
    volatile RF_DIGTOP_RAMP_DELAY_U              RAMP_DELAY            ; // 0x6e4
    volatile RF_DIGTOP_DPD_LUT_INDEX_U           DPD_LUT_INDEX         ; // 0x6e8
    volatile RF_DIGTOP_FDIQ_CTRL_SET_U           FDIQ_CTRL_SET         ; // 0x6ec
    volatile RF_DIGTOP_FDIQ_COEF_PHI1_U          FDIQ_COEF_PHI1        ; // 0x6f0
    volatile RF_DIGTOP_FDIQ_COEF_ESP1_U          FDIQ_COEF_ESP1        ; // 0x6f4
    volatile RF_DIGTOP_FDIQ_COEF_PHI2_U          FDIQ_COEF_PHI2        ; // 0x6f8
    volatile RF_DIGTOP_FDIQ_COEF_ESP2_U          FDIQ_COEF_ESP2        ; // 0x6fc
} RF_DIGTOP_Type;

#ifdef __cplusplus
}
#endif

#endif /* __REG_RF_DIGTOP_H__ */
