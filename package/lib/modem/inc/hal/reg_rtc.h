/*********************************************************************/
/*    Newracom Library / IP Product                                  */
/*    Product Name :                                                 */
/*    Version      :                                                 */
/*    Author       :                                                 */
/*    Update       :                                                 */
/*********************************************************************/

#ifndef __REG_RTC_H__
#define __REG_RTC_H__

#ifdef __cplusplus
extern "C"{
#endif

// 0x40000000 register ------------------------------------
typedef struct {
    uint32_t         EN          :1 ;
    uint32_t         STOP        :1 ;
    uint32_t         reserved0   :1 ;
    uint32_t         MODE        :1 ;
    uint32_t         INTEN       :1 ;
    uint32_t         LOAD        :1 ;
    uint32_t         reserved1   :26;
}   RTC_CTRL;

typedef union {
    uint32_t         w;
    RTC_CTRL         b;
}   RTC_CTRL_U;


// 0x40000004 register ------------------------------------
typedef struct {
    uint32_t         ALRCNTH     :32;
}   RTC_ALRCNTH;

typedef union {
    uint32_t         w;
    RTC_ALRCNTH      b;
}   RTC_ALRCNTH_U;


// 0x40000008 register ------------------------------------
typedef struct {
    uint32_t         ALRCNTL     :32;
}   RTC_ALRCNTL;

typedef union {
    uint32_t         w;
    RTC_ALRCNTL      b;
}   RTC_ALRCNTL_U;


// 0x4000000C register ------------------------------------
typedef struct {
    uint32_t         CURCNTH     :32;
}   RTC_CURCNTH;

typedef union {
    uint32_t         w;
    RTC_CURCNTH      b;
}   RTC_CURCNTH_U;


// 0x40000010 register ------------------------------------
typedef struct {
    uint32_t         CURCNTL     :32;
}   RTC_CURCNTL;

typedef union {
    uint32_t         w;
    RTC_CURCNTL      b;
}   RTC_CURCNTL_U;


// 0x40000018 register ------------------------------------
typedef struct {
    uint32_t         LOADCNTH    :32;
}   RTC_LOADCNTH;

typedef union {
    uint32_t         w;
    RTC_LOADCNTH     b;
}   RTC_LOADCNTH_U;


// 0x4000001C register ------------------------------------
typedef struct {
    uint32_t         LOADCNTL    :32;
}   RTC_LOADCNTL;

typedef union {
    uint32_t         w;
    RTC_LOADCNTL     b;
}   RTC_LOADCNTL_U;


// 0x40000030 register ------------------------------------
typedef struct {
    uint32_t         INTF        :1 ;
    uint32_t         BUSY        :1 ;
    uint32_t         reserved0   :30;
}   RTC_STATUS;

typedef union {
    uint32_t         w;
    RTC_STATUS       b;
}   RTC_STATUS_U;


//---------------------------------------------------------
// RTC Register Map
//---------------------------------------------------------
typedef struct {
    volatile RTC_CTRL_U              CTRL            ; // 0x000
    volatile RTC_ALRCNTH_U           ALRCNTH         ; // 0x004
    volatile RTC_ALRCNTL_U           ALRCNTL         ; // 0x008
    volatile RTC_CURCNTH_U           CURCNTH         ; // 0x00c
    volatile RTC_CURCNTL_U           CURCNTL         ; // 0x010
    volatile uint32_t                   RESERVED0       ; // 
    volatile RTC_LOADCNTH_U          LOADCNTH        ; // 0x018
    volatile RTC_LOADCNTL_U          LOADCNTL        ; // 0x01c
    volatile uint32_t                   RESERVED1[4]    ; // 
    volatile RTC_STATUS_U            STATUS          ; // 0x030
} RTC_Type;

#ifdef __cplusplus
}
#endif

#endif /* __REG_RTC_H__ */
