/*********************************************************************/
/*    Newracom Library / IP Product                                  */
/*    Product Name :                                                 */
/*    Version      :                                                 */
/*    Author       :                                                 */
/*    Update       :                                                 */
/*********************************************************************/

#ifndef __REG_SFC_H__
#define __REG_SFC_H__

#ifdef __cplusplus
extern "C"{
#endif

// 0x40092000 register ------------------------------------
typedef struct {
    uint32_t        FLRMOD      :2 ;
    uint32_t        reserved0   :1 ;
    uint32_t        BUSRC       :1 ;
    uint32_t        PEM         :1 ;
    uint32_t        EQIOF       :1 ;
    uint32_t        reserved1   :1 ;
    uint32_t        BUSEEn      :1 ;
    uint32_t        CSC         :1 ;
    uint32_t        reserved2   :23;
}   SFC_FLMOD;

typedef union {
    uint32_t        w;
    SFC_FLMOD       b;
}   SFC_FLMOD_U;


// 0x40092004 register ------------------------------------
typedef struct {
    uint32_t        SCKL        :4 ;
    uint32_t        SCKH        :4 ;
    uint32_t        SCKB        :1 ;
    uint32_t        reserved0   :23;
}   SFC_FLBRT;

typedef union {
    uint32_t        w;
    SFC_FLBRT       b;
}   SFC_FLBRT_U;


// 0x40092008 register ------------------------------------
typedef struct {
    uint32_t        CSHPW       :4 ;
    uint32_t        reserved0   :28;
}   SFC_FLCSH;

typedef union {
    uint32_t        w;
    SFC_FLCSH       b;
}   SFC_FLCSH_U;


// 0x4009200C register ------------------------------------
typedef struct {
    uint32_t        EN          :1 ;
    uint32_t        reserved0   :31;
}   SFC_FLPEM;

typedef union {
    uint32_t        w;
    SFC_FLPEM       b;
}   SFC_FLPEM_U;


// 0x40092010 register ------------------------------------
typedef struct {
    uint32_t        CMD         :8 ;
    uint32_t        reserved0   :24;
}   SFC_FLCMD;

typedef union {
    uint32_t        w;
    SFC_FLCMD       b;
}   SFC_FLCMD_U;


// 0x40092014 register ------------------------------------
typedef struct {
    uint32_t        STS         :8 ;
    uint32_t        reserved0   :24;
}   SFC_FLSTS;

typedef union {
    uint32_t        w;
    SFC_FLSTS       b;
}   SFC_FLSTS_U;


// 0x40092018 register ------------------------------------
typedef struct {
    uint32_t        SEA         :24;
    uint32_t        reserved0   :8 ;
}   SFC_FLSEA;

typedef union {
    uint32_t        w;
    SFC_FLSEA       b;
}   SFC_FLSEA_U;


// 0x4009201C register ------------------------------------
typedef struct {
    uint32_t        BEA         :24;
    uint32_t        reserved0   :8 ;
}   SFC_FLBEA;

typedef union {
    uint32_t        w;
    SFC_FLBEA       b;
}   SFC_FLBEA_U;


// 0x40092020 register ------------------------------------
typedef struct {
    uint32_t        FLDAT       :32;
}   SFC_FLDAT;

typedef union {
    uint32_t        w;
    SFC_FLDAT       b;
}   SFC_FLDAT_U;


// 0x40092024 register ------------------------------------
typedef struct {
    uint32_t        FLWCP       :32;
}   SFC_FLWCP;

typedef union {
    uint32_t        w;
    SFC_FLWCP       b;
}   SFC_FLWCP_U;


// 0x40092028 register ------------------------------------
typedef struct {
    uint32_t        SFFCDV      :4 ;
    uint32_t        reserved0   :28;
}   SFC_FLCKDLY;

typedef union {
    uint32_t        w;
    SFC_FLCKDLY     b;
}   SFC_FLCKDLY_U;


// 0x4009202C register ------------------------------------
typedef struct {
    uint32_t        STS2        :8 ;
    uint32_t        reserved0   :24;
}   SFC_FLSTS2;

typedef union {
    uint32_t        w;
    SFC_FLSTS2      b;
}   SFC_FLSTS2_U;


// 0x40092100 register ------------------------------------
typedef struct {
    uint32_t        EN          :1 ;
    uint32_t        DIRTY       :1 ;
    uint32_t        reserved0   :2 ;
    uint32_t        WAY         :1 ;
    uint32_t        reserved1   :27;
}   SFC_CTRL;

typedef union {
    uint32_t        w;
    SFC_CTRL        b;
}   SFC_CTRL_U;


// 0x40092104 register ------------------------------------
typedef struct {
    uint32_t        BUSY        :1 ;
    uint32_t        ENABLED     :1 ;
    uint32_t        DISABLED    :1 ;
    uint32_t        reserved0   :29;
}   SFC_STAT;

typedef union {
    uint32_t        w;
    SFC_STAT        b;
}   SFC_STAT_U;


// 0x40092108 register ------------------------------------
typedef struct {
    uint32_t        NOHIT       :32;
}   SFC_NOHIT;

typedef union {
    uint32_t        w;
    SFC_NOHIT       b;
}   SFC_NOHIT_U;


// 0x4009210C register ------------------------------------
typedef struct {
    uint32_t        NOMIS       :32;
}   SFC_NOMIS;

typedef union {
    uint32_t        w;
    SFC_NOMIS       b;
}   SFC_NOMIS_U;


// 0x40092110 register ------------------------------------
typedef struct {
    uint32_t        TCS         :32;
}   SFC_PARA0;

typedef union {
    uint32_t        w;
    SFC_PARA0       b;
}   SFC_PARA0_U;


// 0x40092114 register ------------------------------------
typedef struct {
    uint32_t        AW          :8 ;
    uint32_t        WAY         :8 ;
    uint32_t        CLS         :16;
}   SFC_PARA1;

typedef union {
    uint32_t        w;
    SFC_PARA1       b;
}   SFC_PARA1_U;


//---------------------------------------------------------
// SFC Register Map
//---------------------------------------------------------
typedef struct {
    volatile SFC_FLMOD_U            FLMOD          ; // 0x000
    volatile SFC_FLBRT_U            FLBRT          ; // 0x04
    volatile SFC_FLCSH_U            FLCSH          ; // 0x08
    volatile SFC_FLPEM_U            FLPEM          ; // 0x00c
    volatile SFC_FLCMD_U            FLCMD          ; // 0x010
    volatile SFC_FLSTS_U            FLSTS          ; // 0x014
    volatile SFC_FLSEA_U            FLSEA          ; // 0x018
    volatile SFC_FLBEA_U            FLBEA          ; // 0x01c
    volatile SFC_FLDAT_U            FLDAT          ; // 0x020
    volatile SFC_FLWCP_U            FLWCP          ; // 0x024
    volatile SFC_FLCKDLY_U          FLCKDLY        ; // 0x028
    volatile SFC_FLSTS2_U           FLSTS2         ; // 0x02c
    volatile uint32_t                  RESERVED0[52]  ; // 
    volatile SFC_CTRL_U             CTRL           ; // 0x100
    volatile SFC_STAT_U             STAT           ; // 0x104
    volatile SFC_NOHIT_U            NOHIT          ; // 0x108
    volatile SFC_NOMIS_U            NOMIS          ; // 0x10c
    volatile SFC_PARA0_U            PARA0          ; // 0x110
    volatile SFC_PARA1_U            PARA1          ; // 0x114
} SFC_Type;

#ifdef __cplusplus
}
#endif

#endif /* __REG_SFC_H__ */
