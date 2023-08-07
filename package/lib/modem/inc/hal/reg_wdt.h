/*********************************************************************/
/*    Newracom Library / IP Product                                  */
/*    Product Name :                                                 */
/*    Version      :                                                 */
/*    Author       :                                                 */
/*    Update       :                                                 */
/*********************************************************************/

#ifndef __REG_WDT_H__
#define __REG_WDT_H__

#ifdef __cplusplus
extern "C"{
#endif

// 0x40003000 register ------------------------------------
typedef struct {
    uint32_t        WLOAD       :32;
}   WDT_LOAD;

typedef union {
    uint32_t        w;
    WDT_LOAD        b;
}   WDT_LOAD_U;


// 0x40003004 register ------------------------------------
typedef struct {
    uint32_t        WVALUE      :32;
}   WDT_VALUE;

typedef union {
    uint32_t        w;
    WDT_VALUE       b;
}   WDT_VALUE_U;


// 0x40003008 register ------------------------------------
typedef struct {
    uint32_t        INTEN       :1 ;
    uint32_t        RESEN       :1 ;
    uint32_t        reserved0   :30;
}   WDT_CONTROL;

typedef union {
    uint32_t        w;
    WDT_CONTROL     b;
}   WDT_CONTROL_U;


// 0x4000300C register ------------------------------------
typedef struct {
    uint32_t        WINTCLR     :32;
}   WDT_INTCLR;

typedef union {
    uint32_t        w;
    WDT_INTCLR      b;
}   WDT_INTCLR_U;


// 0x40003010 register ------------------------------------
typedef struct {
    uint32_t        WDOGRIS     :1 ;
    uint32_t        reserved0   :31;
}   WDT_RIS;

typedef union {
    uint32_t        w;
    WDT_RIS         b;
}   WDT_RIS_U;


// 0x40003014 register ------------------------------------
typedef struct {
    uint32_t        WDOGMIS     :1 ;
    uint32_t        reserved0   :31;
}   WDT_MIS;

typedef union {
    uint32_t        w;
    WDT_MIS         b;
}   WDT_MIS_U;


// 0x40003C00 register ------------------------------------
typedef struct {
    uint32_t        RWES        :1 ;
    uint32_t        ERW         :31;
}   WDT_LOCK;

typedef union {
    uint32_t        w;
    WDT_LOCK        b;
}   WDT_LOCK_U;


//---------------------------------------------------------
// WDT Register Map
//---------------------------------------------------------
typedef struct {
    volatile WDT_LOAD_U             LOAD           ; // 0x00
    volatile WDT_VALUE_U            VALUE          ; // 0x04
    volatile WDT_CONTROL_U          CONTROL        ; // 0x08
    volatile WDT_INTCLR_U           INTCLR         ; // 0x0c
    volatile WDT_RIS_U              RIS            ; // 0x10
    volatile WDT_MIS_U              MIS            ; // 0x14
    volatile uint32_t                  RESERVED0[762] ; // 
    volatile WDT_LOCK_U             LOCK           ; // 0xc00
} WDT_Type;

#ifdef __cplusplus
}
#endif

#endif /* __REG_WDT_H__ */
