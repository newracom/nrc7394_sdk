/*********************************************************************/
/*    Newracom Library / IP Product                                  */
/*    Product Name :                                                 */
/*    Version      :                                                 */
/*    Author       :                                                 */
/*    Update       :                                                 */
/*********************************************************************/

#ifndef __REG_PMU_H__
#define __REG_PMU_H__

#ifdef __cplusplus
extern "C"{
#endif

// 0x40002000 register ------------------------------------
typedef struct {
    uint32_t           SWRST           :1 ;
    uint32_t           reserved0       :31;
}   PMU_PMURST;

typedef union {
    uint32_t           w;
    PMU_PMURST         b;
}   PMU_PMURST_U;


// 0x40002004 register ------------------------------------
typedef struct {
    uint32_t           OPMODE          :3 ;
    uint32_t           reserved0       :3 ;
    uint32_t           WUSRCEXT0       :1 ;
    uint32_t           WUSRCEXT1       :1 ;
    uint32_t           WUSRCEXT2       :1 ;
    uint32_t           WUSRCEXT3       :1 ;
    uint32_t           WUSRCRTC        :1 ;
    uint32_t           WUSRCHOST       :1 ;
    uint32_t           EWP0POL         :1 ;
    uint32_t           EWP1POL         :1 ;
    uint32_t           EWP2POL         :1 ;
    uint32_t           EWP3POL         :1 ;
    uint32_t           CSPI_PD_DIS     :1 ;
    uint32_t           reserved1       :13;
    uint32_t           IEN             :1 ;
    uint32_t           PMEN            :1 ;
}   PMU_CTRL0;

typedef union {
    uint32_t           w;
    PMU_CTRL0          b;
}   PMU_CTRL0_U;


// 0x40002008 register ------------------------------------
typedef struct {
    uint32_t           SXTAL_WAIT      :16;
    uint32_t           MXTAL_WAIT      :8 ;
    uint32_t           reserved0       :8 ;
}   PMU_CTRL1;

typedef union {
    uint32_t           w;
    PMU_CTRL1          b;
}   PMU_CTRL1_U;


// 0x4000200C register ------------------------------------
typedef struct {
    uint32_t           DCDC2PSW        :16;
    uint32_t           PSW2ISO         :5 ;
    uint32_t           PSW2DCDC        :2 ;
    uint32_t           reserved0       :8 ;
    uint32_t           WAITPG          :1 ;
}   PMU_CTRL2;

typedef union {
    uint32_t           w;
    PMU_CTRL2          b;
}   PMU_CTRL2_U;


// 0x40002010 register ------------------------------------
typedef struct {
    uint32_t           PMUINT          :1 ;
    uint32_t           PWRINT          :1 ;
    uint32_t           WUISRCEXT0      :1 ;
    uint32_t           WUISRCEXT1      :1 ;
    uint32_t           WUISRCEXT2      :1 ;
    uint32_t           WUISRCEXT3      :1 ;
    uint32_t           WUISRCRTC       :1 ;
    uint32_t           WUISRCHOST      :1 ;
    uint32_t           reserved0       :24;
}   PMU_STAT0;

typedef union {
    uint32_t           w;
    PMU_STAT0          b;
}   PMU_STAT0_U;


// 0x40002014 register ------------------------------------
typedef struct {
    uint32_t           CURPMU          :4 ;
    uint32_t           BUSY            :1 ;
    uint32_t           reserved0       :27;
}   PMU_STAT1;

typedef union {
    uint32_t           w;
    PMU_STAT1          b;
}   PMU_STAT1_U;


// 0x40002018 register ------------------------------------
typedef struct {
    uint32_t           PMUHIS          :24;
    uint32_t           reserved0       :8 ;
}   PMU_STAT2;

typedef union {
    uint32_t           w;
    PMU_STAT2          b;
}   PMU_STAT2_U;


// 0x40002020 register ------------------------------------
typedef struct {
    uint32_t           PMS_CTRL        :1 ;
    uint32_t           LDO_CTRL        :1 ;
    uint32_t           reserved0       :6 ;
    uint32_t           PG_CORE         :1 ;
    uint32_t           PG_WIFI         :1 ;
    uint32_t           reserved1       :1 ;
    uint32_t           PG_RF           :1 ;
    uint32_t           PG_RETMEM0      :1 ;
    uint32_t           RT_RETMEM0      :1 ;
    uint32_t           PG_RETMEM1      :1 ;
    uint32_t           RT_RETMEM1      :1 ;
    uint32_t           PG_RETMEM2      :1 ;
    uint32_t           RT_RETMEM2      :1 ;
    uint32_t           PG_SRAM0        :1 ;
    uint32_t           RT_SRAM0        :1 ;
    uint32_t           PG_SRAM1        :1 ;
    uint32_t           RT_SRAM1        :1 ;
    uint32_t           reserved2       :10;
}   PMU_PSWMASK;

typedef union {
    uint32_t           w;
    PMU_PSWMASK        b;
}   PMU_PSWMASK_U;


// 0x40002024 register ------------------------------------
typedef struct {
    uint32_t           PMS_CTRL        :1 ;
    uint32_t           LDO_CTRL        :1 ;
    uint32_t           reserved0       :6 ;
    uint32_t           PG_CORE         :1 ;
    uint32_t           PG_WIFI         :1 ;
    uint32_t           reserved1       :1 ;
    uint32_t           PG_RF           :1 ;
    uint32_t           PG_RETMEM0      :1 ;
    uint32_t           RT_RETMEM0      :1 ;
    uint32_t           PG_RETMEM1      :1 ;
    uint32_t           RT_RETMEM1      :1 ;
    uint32_t           PG_RETMEM2      :1 ;
    uint32_t           RT_RETMEM2      :1 ;
    uint32_t           PG_SRAM0        :1 ;
    uint32_t           RT_SRAM0        :1 ;
    uint32_t           PG_SRAM1        :1 ;
    uint32_t           RT_SRAM1        :1 ;
    uint32_t           reserved2       :10;
}   PMU_PSWMANEN;

typedef union {
    uint32_t           w;
    PMU_PSWMANEN       b;
}   PMU_PSWMANEN_U;


// 0x40002028 register ------------------------------------
typedef struct {
    uint32_t           PMS_CTRL        :1 ;
    uint32_t           LDO_CTRL        :1 ;
    uint32_t           reserved0       :6 ;
    uint32_t           PG_CORE         :1 ;
    uint32_t           PG_WIFI         :1 ;
    uint32_t           reserved1       :1 ;
    uint32_t           PG_RF           :1 ;
    uint32_t           PG_RETMEM0      :1 ;
    uint32_t           RT_RETMEM0      :1 ;
    uint32_t           PG_RETMEM1      :1 ;
    uint32_t           RT_RETMEM1      :1 ;
    uint32_t           PG_RETMEM2      :1 ;
    uint32_t           RT_RETMEM2      :1 ;
    uint32_t           PG_SRAM0        :1 ;
    uint32_t           RT_SRAM0        :1 ;
    uint32_t           PG_SRAM1        :1 ;
    uint32_t           RT_SRAM1        :1 ;
    uint32_t           reserved2       :10;
}   PMU_PSWCTRL;

typedef union {
    uint32_t           w;
    PMU_PSWCTRL        b;
}   PMU_PSWCTRL_U;


// 0x4000202C register ------------------------------------
typedef struct {
    uint32_t           reserved0       :8 ;
    uint32_t           PG_CORE         :1 ;
    uint32_t           PG_WIFI         :1 ;
    uint32_t           reserved1       :1 ;
    uint32_t           PG_RF           :1 ;
    uint32_t           reserved2       :20;
}   PMU_ISOCTRL;

typedef union {
    uint32_t           w;
    PMU_ISOCTRL        b;
}   PMU_ISOCTRL_U;


// 0x40002030 register ------------------------------------
typedef struct {
    uint32_t           RFOFF           :1 ;
    uint32_t           reserved0       :1 ;
    uint32_t           MXTALOFF        :1 ;
    uint32_t           LPO16MOFF       :1 ;
    uint32_t           SXTALOFF        :1 ;
    uint32_t           LPO32KOFF       :1 ;
    uint32_t           SXTALBYP        :1 ;
    uint32_t           reserved1       :1 ;
    uint32_t           RF_ISO_EN       :1 ;
    uint32_t           XTAL32K_CTRL    :2 ;
    uint32_t           reserved2       :21;
}   PMU_ETCTRL;

typedef union {
    uint32_t           w;
    PMU_ETCTRL         b;
}   PMU_ETCTRL_U;


// 0x40002034 register ------------------------------------
typedef struct {
    uint32_t           CNTVAL          :16;
    uint32_t           reserved0       :13;
    uint32_t           CLRCNT          :1 ;
    uint32_t           PALMIEN         :1 ;
    uint32_t           PALMEN          :1 ;
}   PMU_PWRALRM;

typedef union {
    uint32_t           w;
    PMU_PWRALRM        b;
}   PMU_PWRALRM_U;


// 0x40002038 register ------------------------------------
typedef struct {
    uint32_t           PCNT            :16;
    uint32_t           reserved0       :15;
    uint32_t           PWRFAIL         :1 ;
}   PMU_PWRALRMSTS;

typedef union {
    uint32_t           w;
    PMU_PWRALRMSTS     b;
}   PMU_PWRALRMSTS_U;


// 0x4000203C register ------------------------------------
typedef struct {
    uint32_t           RFSPIPG         :1 ;
    uint32_t           PWRFB           :1 ;
    uint32_t           LDOPG           :1 ;
    uint32_t           BUCKPG          :1 ;
    uint32_t           reserved0       :2 ;
    uint32_t           PWRSW_SRMEM1    :1 ;
    uint32_t           PWRSW_SRMEM0    :1 ;
    uint32_t           PWRSW_CORE      :1 ;
    uint32_t           PWRSW_MEM3      :1 ;
    uint32_t           PWRSW_MEM2      :1 ;
    uint32_t           PWRSW_MEM1      :1 ;
    uint32_t           PWRSW_MEM0      :1 ;
    uint32_t           PWRSW_MODEM     :1 ;
    uint32_t           PWRSW_RF        :1 ;
    uint32_t           reserved1       :17;
}   PMU_PWRGOOD;

typedef union {
    uint32_t           w;
    PMU_PWRGOOD        b;
}   PMU_PWRGOOD_U;


//---------------------------------------------------------
// PMU Register Map
//---------------------------------------------------------
typedef struct {
    volatile PMU_PMURST_U              PMURST            ; // 0x000
    volatile PMU_CTRL0_U               CTRL0             ; // 0x004
    volatile PMU_CTRL1_U               CTRL1             ; // 0x008
    volatile PMU_CTRL2_U               CTRL2             ; // 0x00c
    volatile PMU_STAT0_U               STAT0             ; // 0x010
    volatile PMU_STAT1_U               STAT1             ; // 0x014
    volatile PMU_STAT2_U               STAT2             ; // 0x018
    volatile uint32_t                     RESERVED0         ; // 
    volatile PMU_PSWMASK_U             PSWMASK           ; // 0x020
    volatile PMU_PSWMANEN_U            PSWMANEN          ; // 0x024
    volatile PMU_PSWCTRL_U             PSWCTRL           ; // 0x028
    volatile PMU_ISOCTRL_U             ISOCTRL           ; // 0x02c
    volatile PMU_ETCTRL_U              ETCTRL            ; // 0x030
    volatile PMU_PWRALRM_U             PWRALRM           ; // 0x034
    volatile PMU_PWRALRMSTS_U          PWRALRMSTS        ; // 0x038
    volatile PMU_PWRGOOD_U             PWRGOOD           ; // 0x03c
} PMU_Type;

#ifdef __cplusplus
}
#endif

#endif /* __REG_PMU_H__ */
