/*********************************************************************/
/*    Newracom Library / IP Product                                  */
/*    Product Name :                                                 */
/*    Version      :                                                 */
/*    Author       :                                                 */
/*    Update       :                                                 */
/*********************************************************************/

#ifndef __REG_PMS_H__
#define __REG_PMS_H__

#ifdef __cplusplus
extern "C"{
#endif

// 0x0 register ------------------------------------
typedef struct {
    uint32_t      VREF07            :4 ;
    uint32_t      IOLDO             :4 ;
    uint32_t      BGR               :5 ;
    uint32_t      reserved0         :19;
}   PMS_REG00;

typedef union {
    uint32_t      w;
    PMS_REG00     b;
}   PMS_REG00_U;


// 0x1 register ------------------------------------
typedef struct {
    uint32_t      IBIAS             :4 ;
    uint32_t      VREF035           :4 ;
    uint32_t      VREF04BK          :4 ;
    uint32_t      VPOR              :4 ;
    uint32_t      reserved0         :16;
}   PMS_REG01;

typedef union {
    uint32_t      w;
    PMS_REG01     b;
}   PMS_REG01_U;


// 0x2 register ------------------------------------
typedef struct {
    uint32_t      VPWRFB_F          :4 ;
    uint32_t      reserved0         :4 ;
    uint32_t      VSLREF07          :4 ;
    uint32_t      VSLREFL           :4 ;
    uint32_t      reserved1         :16;
}   PMS_REG02;

typedef union {
    uint32_t      w;
    PMS_REG02     b;
}   PMS_REG02_U;


// 0x3 register ------------------------------------
typedef struct {
    uint32_t      VSLREFLPIO        :4 ;
    uint32_t      reserved0         :4 ;
    uint32_t      VSLREFLP          :4 ;
    uint32_t      SL_TON            :2 ;
    uint32_t      reserved1         :18;
}   PMS_REG03;

typedef union {
    uint32_t      w;
    PMS_REG03     b;
}   PMS_REG03_U;


// 0x4 register ------------------------------------
typedef struct {
    uint32_t      BCLK              :5 ;
    uint32_t      ZCD               :3 ;
    uint32_t      OCP               :4 ;
    uint32_t      SLOPE             :4 ;
    uint32_t      reserved0         :16;
}   PMS_REG04;

typedef union {
    uint32_t      w;
    PMS_REG04     b;
}   PMS_REG04_U;


// 0x5 register ------------------------------------
typedef struct {
    uint32_t      DDT               :4 ;
    uint32_t      reserved0         :3 ;
    uint32_t      LPO32K_BSUP       :1 ;
    uint32_t      RRF               :4 ;
    uint32_t      VREF07_BK         :4 ;
    uint32_t      reserved1         :16;
}   PMS_REG05;

typedef union {
    uint32_t      w;
    PMS_REG05     b;
}   PMS_REG05_U;


// 0x6 register ------------------------------------
typedef struct {
    uint32_t      LPOCAL_SPI        :13;
    uint32_t      LPOCAL_SEL        :1 ;
    uint32_t      ENSL_SPI          :1 ;
    uint32_t      ENSL_SEL          :1 ;
    uint32_t      reserved0         :16;
}   PMS_REG06;

typedef union {
    uint32_t      w;
    PMS_REG06     b;
}   PMS_REG06_U;


// 0x7 register ------------------------------------
typedef struct {
    uint32_t      TSTEN             :1 ;
    uint32_t      EN_LPO16M_SPI     :1 ;
    uint32_t      LPO16M_SEL        :1 ;
    uint32_t      reserved0         :2 ;
    uint32_t      PFWM_CLKS         :1 ;
    uint32_t      PFWM_Time         :2 ;
    uint32_t      PWFM_CNT          :1 ;
    uint32_t      PWFM_BCLKBB       :1 ;
    uint32_t      ILDET_UP          :1 ;
    uint32_t      EN_PFMCMP         :1 ;
    uint32_t      PFM_CMPOFS        :2 ;
    uint32_t      OCP_DN            :1 ;
    uint32_t      ENLPO32K_SOC      :1 ;
    uint32_t      reserved1         :16;
}   PMS_REG07;

typedef union {
    uint32_t      w;
    PMS_REG07     b;
}   PMS_REG07_U;


// 0x8 register ------------------------------------
typedef struct {
    uint32_t      TM_GNDA           :1 ;
    uint32_t      TM_PRE_IBIAS      :1 ;
    uint32_t      TM_Main_IBIAS     :1 ;
    uint32_t      TM_MBGR           :1 ;
    uint32_t      TM_VREF07         :1 ;
    uint32_t      TM_RES            :1 ;
    uint32_t      TM_VREG055        :1 ;
    uint32_t      TM_VILDET         :1 ;
    uint32_t      TM_VSLREF07       :1 ;
    uint32_t      TM_VSLREFL        :1 ;
    uint32_t      TM_SL_BIAS        :1 ;
    uint32_t      TM_VPBGR          :1 ;
    uint32_t      TM_VPRE_HALF      :1 ;
    uint32_t      TM_SST            :1 ;
    uint32_t      TM_ILSEN          :1 ;
    uint32_t      TM_SLOPE          :1 ;
    uint32_t      reserved0         :16;
}   PMS_REG08;

typedef union {
    uint32_t      w;
    PMS_REG08     b;
}   PMS_REG08_U;


// 0x9 register ------------------------------------
typedef struct {
    uint32_t      TM_IRF            :1 ;
    uint32_t      TM_RRF            :1 ;
    uint32_t      TM_VLPO           :1 ;
    uint32_t      reserved0         :3 ;
    uint32_t      TM_POR_AN         :1 ;
    uint32_t      TM_PWRF           :1 ;
    uint32_t      VDD_PG            :1 ;
    uint32_t      EN_SLM_SL         :1 ;
    uint32_t      EN_SLM_FS         :1 ;
    uint32_t      EN_SLPRE          :1 ;
    uint32_t      SSPWM             :1 ;
    uint32_t      TM_BCLK           :1 ;
    uint32_t      ZCD_OUT           :1 ;
    uint32_t      PFM_CMPO          :1 ;
    uint32_t      reserved1         :16;
}   PMS_REG09;

typedef union {
    uint32_t      w;
    PMS_REG09     b;
}   PMS_REG09_U;


// 0xA register ------------------------------------
typedef struct {
    uint32_t      EN_BKD            :1 ;
    uint32_t      EN_FET            :1 ;
    uint32_t      BUCK_PG           :1 ;
    uint32_t      TM_OCP            :1 ;
    uint32_t      TM_OVP            :1 ;
    uint32_t      TON_MIN           :1 ;
    uint32_t      TON_MAX           :1 ;
    uint32_t      TOFF_MIN          :1 ;
    uint32_t      TOFF_MAX          :1 ;
    uint32_t      TM_IPEAK          :1 ;
    uint32_t      TM_IL_DET         :1 ;
    uint32_t      ENPWM             :1 ;
    uint32_t      TM_LPO32K         :1 ;
    uint32_t      TM_LPO16M         :1 ;
    uint32_t      TM_SCLK           :1 ;
    uint32_t      LPO_CMPO          :1 ;
    uint32_t      reserved0         :16;
}   PMS_REG0A;

typedef union {
    uint32_t      w;
    PMS_REG0A     b;
}   PMS_REG0A_U;


// 0xB register ------------------------------------
typedef struct {
    uint32_t      SLMD_SPLY_SEL     :1 ;
    uint32_t      reserved0         :1 ;
    uint32_t      SWFET_HS          :1 ;
    uint32_t      SWFET_LS          :1 ;
    uint32_t      SWFET_LKG         :1 ;
    uint32_t      PFM_DIS           :1 ;
    uint32_t      PWM_DIS           :1 ;
    uint32_t      reserved1         :1 ;
    uint32_t      LPLDO_SPLY_CNG    :1 ;
    uint32_t      SLMD_DUTY100      :1 ;
    uint32_t      ENLPO32K_DIS      :1 ;
    uint32_t      DCM               :1 ;
    uint32_t      PFMO              :1 ;
    uint32_t      reserved2         :19;
}   PMS_REG0B;

typedef union {
    uint32_t      w;
    PMS_REG0B     b;
}   PMS_REG0B_U;


// 0xC register ------------------------------------
typedef struct {
    uint32_t      reserved0         :32;
}   PMS_REG0C;

typedef union {
    uint32_t      w;
    PMS_REG0C     b;
}   PMS_REG0C_U;


// 0xD register ------------------------------------
typedef struct {
    uint32_t      reserved0         :32;
}   PMS_REG0D;

typedef union {
    uint32_t      w;
    PMS_REG0D     b;
}   PMS_REG0D_U;


// 0xE register ------------------------------------
typedef struct {
    uint32_t      reserved0         :32;
}   PMS_REG0E;

typedef union {
    uint32_t      w;
    PMS_REG0E     b;
}   PMS_REG0E_U;


// 0xF register ------------------------------------
typedef struct {
    uint32_t      reserved0         :32;
}   PMS_REG0F;

typedef union {
    uint32_t      w;
    PMS_REG0F     b;
}   PMS_REG0F_U;


//---------------------------------------------------------
// PMS Register Map
//---------------------------------------------------------
typedef struct {
    volatile PMS_REG00_U          REG00        ; // 0x000
    volatile PMS_REG01_U          REG01        ; // 0x001
    volatile PMS_REG02_U          REG02        ; // 0x002
    volatile PMS_REG03_U          REG03        ; // 0x003
    volatile PMS_REG04_U          REG04        ; // 0x004
    volatile PMS_REG05_U          REG05        ; // 0x005
    volatile PMS_REG06_U          REG06        ; // 0x006
    volatile PMS_REG07_U          REG07        ; // 0x007
    volatile PMS_REG08_U          REG08        ; // 0x008
    volatile PMS_REG09_U          REG09        ; // 0x009
    volatile PMS_REG0A_U          REG0A        ; // 0x00a
    volatile PMS_REG0B_U          REG0B        ; // 0x00b
    volatile PMS_REG0C_U          REG0C        ; // 0x00c
    volatile PMS_REG0D_U          REG0D        ; // 0x00d
    volatile PMS_REG0E_U          REG0E        ; // 0x00e
    volatile PMS_REG0F_U          REG0F        ; // 0x00f
} PMS_Type;

#ifdef __cplusplus
}
#endif

#endif /* __REG_PMS_H__ */
