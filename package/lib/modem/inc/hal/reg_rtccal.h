/*********************************************************************/
/*    Newracom Library / IP Product                                  */
/*    Product Name :                                                 */
/*    Version      :                                                 */
/*    Author       :                                                 */
/*    Update       :                                                 */
/*********************************************************************/

#ifndef __REG_RTCCAL_H__
#define __REG_RTCCAL_H__

#ifdef __cplusplus
extern "C"{
#endif

// 0x4004A000 register ------------------------------------
typedef struct {
    uint32_t           START       :1 ;
    uint32_t           reserved0   :2 ;
    uint32_t           INTEN       :1 ;
    uint32_t           reserved1   :12;
    uint32_t           DUR         :16;
}   RTCCAL_CTRL;

typedef union {
    uint32_t           w;
    RTCCAL_CTRL        b;
}   RTCCAL_CTRL_U;


// 0x4004A004 register ------------------------------------
typedef struct {
    uint32_t           INTF        :1 ;
    uint32_t           BUSY        :1 ;
    uint32_t           reserved0   :30;
}   RTCCAL_STATUS;

typedef union {
    uint32_t           w;
    RTCCAL_STATUS      b;
}   RTCCAL_STATUS_U;


// 0x4004A008 register ------------------------------------
typedef struct {
    uint32_t           REF         :32;
}   RTCCAL_REFCNT;

typedef union {
    uint32_t           w;
    RTCCAL_REFCNT      b;
}   RTCCAL_REFCNT_U;


// 0x4004A00C register ------------------------------------
typedef struct {
    uint32_t           RESID       :32;
}   RTCCAL_RESID;

typedef union {
    uint32_t           w;
    RTCCAL_RESID       b;
}   RTCCAL_RESID_U;


// 0x4004A010 register ------------------------------------
typedef struct {
    uint32_t           MCNT        :32;
}   RTCCAL_MEASCNT;

typedef union {
    uint32_t           w;
    RTCCAL_MEASCNT     b;
}   RTCCAL_MEASCNT_U;


//---------------------------------------------------------
// RTCCAL Register Map
//---------------------------------------------------------
typedef struct {
    volatile RTCCAL_CTRL_U             CTRL           ; // 0x000
    volatile RTCCAL_STATUS_U           STATUS         ; // 0x004
    volatile RTCCAL_REFCNT_U           REFCNT         ; // 0x008
    volatile RTCCAL_RESID_U            RESID          ; // 0x00c
    volatile RTCCAL_MEASCNT_U          MEASCNT        ; // 0x010
} RTCCAL_Type;

#ifdef __cplusplus
}
#endif

#endif /* __REG_RTCCAL_H__ */
