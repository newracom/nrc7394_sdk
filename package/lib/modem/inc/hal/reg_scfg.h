/*********************************************************************/
/*    Newracom Library / IP Product                                  */
/*    Product Name :                                                 */
/*    Version      :                                                 */
/*    Author       :                                                 */
/*    Update       :                                                 */
/*********************************************************************/

#ifndef __REG_SCFG_H__
#define __REG_SCFG_H__

#ifdef __cplusplus
extern "C"{
#endif

// 0x4000F000 register ------------------------------------
typedef struct {
    uint32_t            MODE             :1 ;
    uint32_t            reserved0        :31;
}   SCFG_MODE;

typedef union {
    uint32_t            w;
    SCFG_MODE           b;
}   SCFG_MODE_U;


// 0x4000F004 register ------------------------------------
typedef struct {
    uint32_t            REMAP            :3 ;
    uint32_t            reserved0        :29;
}   SCFG_REMAP;

typedef union {
    uint32_t            w;
    SCFG_REMAP          b;
}   SCFG_REMAP_U;


// 0x4000F008 register ------------------------------------
typedef struct {
    uint32_t            ROM_RWAIT        :1 ;
    uint32_t            reserved0        :1 ;
    uint32_t            SRAM0_RWAIT      :1 ;
    uint32_t            SRAM1_RWAIT      :1 ;
    uint32_t            SRAM2_RWAIT      :1 ;
    uint32_t            SRAM3_RWAIT      :1 ;
    uint32_t            SRAM4_RWAIT      :1 ;
    uint32_t            reserved1        :25;
}   SCFG_MEM_RWAIT;

typedef union {
    uint32_t            w;
    SCFG_MEM_RWAIT      b;
}   SCFG_MEM_RWAIT_U;


// 0x4000F010 register ------------------------------------
typedef struct {
    uint32_t            RF_CON           :1 ;
    uint32_t            SEL_32K          :1 ;
    uint32_t            reserved0        :1 ;
    uint32_t            TCLK_EN          :1 ;
    uint32_t            reserved1        :28;
}   SCFG_CONFIG0;

typedef union {
    uint32_t            w;
    SCFG_CONFIG0        b;
}   SCFG_CONFIG0_U;


// 0x4000F014 register ------------------------------------
typedef struct {
    uint32_t            CAL              :13;
    uint32_t            reserved0        :19;
}   SCFG_LPO32K_CAL;

typedef union {
    uint32_t            w;
    SCFG_LPO32K_CAL     b;
}   SCFG_LPO32K_CAL_U;


// 0x4000F018 register ------------------------------------
typedef struct {
    uint32_t            PoR              :1 ;
    uint32_t            WDTREQ           :1 ;
    uint32_t            PMC              :1 ;
    uint32_t            HOSTREQ          :1 ;
    uint32_t            CPUREQ           :1 ;
    uint32_t            reserved0        :1 ;
    uint32_t            reserved1        :26;
}   SCFG_BR;

typedef union {
    uint32_t            w;
    SCFG_BR             b;
}   SCFG_BR_U;


// 0x4000F01C register ------------------------------------
typedef struct {
    uint32_t            PDOD             :6 ;
    uint32_t            reserved0        :2 ;
    uint32_t            POEN             :6 ;
    uint32_t            reserved1        :2 ;
    uint32_t            PUEN             :6 ;
    uint32_t            reserved2        :9 ;
    uint32_t            ENB              :1 ;
}   SCFG_XIP_DS;

typedef union {
    uint32_t            w;
    SCFG_XIP_DS         b;
}   SCFG_XIP_DS_U;


// 0x4000F020 register ------------------------------------
typedef struct {
    uint32_t            TOUT_SEL         :4 ;
    uint32_t            reserved0        :28;
}   SCFG_TEST_OUT;

typedef union {
    uint32_t            w;
    SCFG_TEST_OUT       b;
}   SCFG_TEST_OUT_U;


// 0x4000F024 register ------------------------------------
typedef struct {
    uint32_t            RF_DUMP_EN       :1 ;
    uint32_t            PHY_DUMP_EN      :1 ;
    uint32_t            reserved0        :30;
}   SCFG_RA_DUMP;

typedef union {
    uint32_t            w;
    SCFG_RA_DUMP        b;
}   SCFG_RA_DUMP_U;


// 0x4000F028 register ------------------------------------
typedef struct {
    uint32_t            PKG_OPT          :1 ;
    uint32_t            reserved0        :31;
}   SCFG_PKG_OPT;

typedef union {
    uint32_t            w;
    SCFG_PKG_OPT        b;
}   SCFG_PKG_OPT_U;


// 0x4000F02C register ------------------------------------
typedef struct {
    uint32_t            POR_F            :1 ;
    uint32_t            reserved0        :31;
}   SCFG_POR_FLAG;

typedef union {
    uint32_t            w;
    SCFG_POR_FLAG       b;
}   SCFG_POR_FLAG_U;


// 0x4000F030 register ------------------------------------
typedef struct {
    uint32_t            REMAP_AFT_RST    :3 ;
    uint32_t            reserved0        :13;
    uint32_t            EN_REMAPRST      :16;
}   SCFG_REMAP_RST;

typedef union {
    uint32_t            w;
    SCFG_REMAP_RST      b;
}   SCFG_REMAP_RST_U;


// 0x4000F034 register ------------------------------------
typedef struct {
    uint32_t            MEM_SRAM2        :1 ;
    uint32_t            MEM_SRAM3        :1 ;
    uint32_t            reserved0        :30;
}   SCFG_MEMCONFIG;

typedef union {
    uint32_t            w;
    SCFG_MEMCONFIG      b;
}   SCFG_MEMCONFIG_U;


// 0x4000F0F0 register ------------------------------------
typedef struct {
    uint32_t            VID              :32;
}   SCFG_VENDORID;

typedef union {
    uint32_t            w;
    SCFG_VENDORID       b;
}   SCFG_VENDORID_U;


// 0x4000F0F4 register ------------------------------------
typedef struct {
    uint32_t            CID              :32;
}   SCFG_CHIPID;

typedef union {
    uint32_t            w;
    SCFG_CHIPID         b;
}   SCFG_CHIPID_U;


// 0x4000F0F8 register ------------------------------------
typedef struct {
    uint32_t            RID              :32;
}   SCFG_REVNR;

typedef union {
    uint32_t            w;
    SCFG_REVNR          b;
}   SCFG_REVNR_U;


//---------------------------------------------------------
// SCFG Register Map
//---------------------------------------------------------
typedef struct {
    volatile SCFG_MODE_U                MODE              ; // 0x000
    volatile SCFG_REMAP_U               REMAP             ; // 0x004
    volatile SCFG_MEM_RWAIT_U           MEM_RWAIT         ; // 0x008
    volatile uint32_t                     RESERVED0         ; // 
    volatile SCFG_CONFIG0_U             CONFIG0           ; // 0x010
    volatile SCFG_LPO32K_CAL_U          LPO32K_CAL        ; // 0x014
    volatile SCFG_BR_U                  BR                ; // 0x018
    volatile SCFG_XIP_DS_U              XIP_DS            ; // 0x01c
    volatile SCFG_TEST_OUT_U            TEST_OUT          ; // 0x020
    volatile SCFG_RA_DUMP_U             RA_DUMP           ; // 0x024
    volatile SCFG_PKG_OPT_U             PKG_OPT           ; // 0x028
    volatile SCFG_POR_FLAG_U            POR_FLAG          ; // 0x02c
    volatile SCFG_REMAP_RST_U           REMAP_RST         ; // 0x030
    volatile SCFG_MEMCONFIG_U           MEMCONFIG         ; // 0x034
    volatile uint32_t                     RESERVED1[46]     ; // 
    volatile SCFG_VENDORID_U            VENDORID          ; // 0x0f0
    volatile SCFG_CHIPID_U              CHIPID            ; // 0x0f4
    volatile SCFG_REVNR_U               REVNR             ; // 0x0f8
} SCFG_Type;

#ifdef __cplusplus
}
#endif

#endif /* __REG_SCFG_H__ */
