/*********************************************************************/
/*    Newracom Library / IP Product                                  */
/*    Product Name :                                                 */
/*    Version      :                                                 */
/*    Author       :                                                 */
/*    Update       :                                                 */
/*********************************************************************/

#ifndef __REG_TIMER_32BIT_H__
#define __REG_TIMER_32BIT_H__

#ifdef __cplusplus
extern "C"{
#endif

// 0x40004000 register ------------------------------------
typedef struct {
    uint32_t               PRESCALE    :24;
    uint32_t               ENABLE      :1 ;
    uint32_t               LOADZERO    :1 ;
    uint32_t               STOPMODE    :1 ;
    uint32_t               reserved0   :1 ;
    uint32_t               LDM0        :1 ;
    uint32_t               LDM1        :1 ;
    uint32_t               reserved1   :2 ;
}   TIMER_32BIT_TCCTRL;

typedef union {
    uint32_t               w;
    TIMER_32BIT_TCCTRL     b;
}   TIMER_32BIT_TCCTRL_U;


// 0x40004004 register ------------------------------------
typedef struct {
    uint32_t               LOADVAL     :32;
}   TIMER_32BIT_TCLDV;

typedef union {
    uint32_t               w;
    TIMER_32BIT_TCLDV      b;
}   TIMER_32BIT_TCLDV_U;


// 0x40004008 register ------------------------------------
typedef struct {
    uint32_t               CMP0        :32;
}   TIMER_32BIT_TCMV0;

typedef union {
    uint32_t               w;
    TIMER_32BIT_TCMV0      b;
}   TIMER_32BIT_TCMV0_U;


// 0x4000400C register ------------------------------------
typedef struct {
    uint32_t               CMP1        :32;
}   TIMER_32BIT_TCMV1;

typedef union {
    uint32_t               w;
    TIMER_32BIT_TCMV1      b;
}   TIMER_32BIT_TCMV1_U;


// 0x40004010 register ------------------------------------
typedef struct {
    uint32_t               PCNT        :24;
    uint32_t               reserved0   :8 ;
}   TIMER_32BIT_TCPCNT;

typedef union {
    uint32_t               w;
    TIMER_32BIT_TCPCNT     b;
}   TIMER_32BIT_TCPCNT_U;


// 0x40004014 register ------------------------------------
typedef struct {
    uint32_t               MCNT        :32;
}   TIMER_32BIT_TCMCNT;

typedef union {
    uint32_t               w;
    TIMER_32BIT_TCMCNT     b;
}   TIMER_32BIT_TCMCNT_U;


// 0x40004018 register ------------------------------------
typedef struct {
    uint32_t               IRQMSTAT    :5 ;
    uint32_t               reserved0   :3 ;
    uint32_t               IRQRSTAT    :5 ;
    uint32_t               reserved1   :3 ;
    uint32_t               IRQEN0      :1 ;
    uint32_t               IRQEN1      :1 ;
    uint32_t               IRQEN2      :1 ;
    uint32_t               IRQEN3      :1 ;
    uint32_t               IRQEN4      :1 ;
    uint32_t               reserved2   :3 ;
    uint32_t               BITSEL      :6 ;
    uint32_t               RSYNC       :1 ;
    uint32_t               IRQCLR      :1 ;
}   TIMER_32BIT_TCIRQ;

typedef union {
    uint32_t               w;
    TIMER_32BIT_TCIRQ      b;
}   TIMER_32BIT_TCIRQ_U;


//---------------------------------------------------------
// TIMER_32BIT Register Map
//---------------------------------------------------------
typedef struct {
    volatile TIMER_32BIT_TCCTRL_U          TCCTRL        ; // 0x00
    volatile TIMER_32BIT_TCLDV_U           TCLDV         ; // 0x04
    volatile TIMER_32BIT_TCMV0_U           TCMV0         ; // 0x08
    volatile TIMER_32BIT_TCMV1_U           TCMV1         ; // 0x0c
    volatile TIMER_32BIT_TCPCNT_U          TCPCNT        ; // 0x10
    volatile TIMER_32BIT_TCMCNT_U          TCMCNT        ; // 0x14
    volatile TIMER_32BIT_TCIRQ_U           TCIRQ         ; // 0x18
} TIMER_32BIT_Type;

#ifdef __cplusplus
}
#endif

#endif /* __REG_TIMER_32BIT_H__ */
