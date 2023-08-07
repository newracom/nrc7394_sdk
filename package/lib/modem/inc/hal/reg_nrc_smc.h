/*********************************************************************/
/*    Newracom Library / IP Product                                  */
/*    Product Name :                                                 */
/*    Version      :                                                 */
/*    Author       :                                                 */
/*    Update       :                                                 */
/*********************************************************************/

#ifndef __REG_NRC_SMC_H__
#define __REG_NRC_SMC_H__

#ifdef __cplusplus
extern "C"{
#endif

// 0x4000B000 register ------------------------------------
typedef struct {
    uint32_t              STARTACT        :1 ;
    uint32_t              STARTDACT       :1 ;
    uint32_t              reserved0       :6 ;
    uint32_t              BUFFULLEN       :1 ;
    uint32_t              FRAMEERREN      :1 ;
    uint32_t              OVERRUNERREN    :1 ;
    uint32_t              TXONEN          :1 ;
    uint32_t              RXSTARTBITEN    :1 ;
    uint32_t              RXRUNEN         :1 ;
    uint32_t              TXPENDINGEN     :1 ;
    uint32_t              TXRUNEN         :1 ;
    uint32_t              CLKDIV          :7 ;
    uint32_t              CLKDIVEN        :1 ;
    uint32_t              CLKINVSEL       :1 ;
    uint32_t              reserved1       :7 ;
}   NRC_SMC_SMCCR0;

typedef union {
    uint32_t              w;
    NRC_SMC_SMCCR0        b;
}   NRC_SMC_SMCCR0_U;


// 0x4000B004 register ------------------------------------
typedef struct {
    uint32_t              ETU             :14;
    uint32_t              reserved0       :18;
}   NRC_SMC_SMCCR1;

typedef union {
    uint32_t              w;
    NRC_SMC_SMCCR1        b;
}   NRC_SMC_SMCCR1_U;


// 0x4000B008 register ------------------------------------
typedef struct {
    uint32_t              WRDATA          :8 ;
    uint32_t              reserved0       :7 ;
    uint32_t              WEN             :1 ;
    uint32_t              reserved1       :16;
}   NRC_SMC_SMCWRDATA;

typedef union {
    uint32_t              w;
    NRC_SMC_SMCWRDATA     b;
}   NRC_SMC_SMCWRDATA_U;


// 0x4000B00C register ------------------------------------
typedef struct {
    uint32_t              RDDATA          :8 ;
    uint32_t              reserved0       :7 ;
    uint32_t              REN             :1 ;
    uint32_t              reserved1       :16;
}   NRC_SMC_SMCRDDATA;

typedef union {
    uint32_t              w;
    NRC_SMC_SMCRDDATA     b;
}   NRC_SMC_SMCRDDATA_U;


// 0x4000B010 register ------------------------------------
typedef struct {
    uint32_t              BUFFULL         :1 ;
    uint32_t              FRAMEERR        :1 ;
    uint32_t              OVERRUNERR      :1 ;
    uint32_t              TXON            :1 ;
    uint32_t              RXSTARTBIT      :1 ;
    uint32_t              RXRUN           :1 ;
    uint32_t              TXPENDING       :1 ;
    uint32_t              TXRUN           :1 ;
    uint32_t              reserved0       :24;
}   NRC_SMC_SMCSTS;

typedef union {
    uint32_t              w;
    NRC_SMC_SMCSTS        b;
}   NRC_SMC_SMCSTS_U;


//---------------------------------------------------------
// NRC_SMC Register Map
//---------------------------------------------------------
typedef struct {
    volatile NRC_SMC_SMCCR0_U             SMCCR0           ; // 0x00
    volatile NRC_SMC_SMCCR1_U             SMCCR1           ; // 0x04
    volatile NRC_SMC_SMCWRDATA_U          SMCWRDATA        ; // 0x08
    volatile NRC_SMC_SMCRDDATA_U          SMCRDDATA        ; // 0x0c
    volatile NRC_SMC_SMCSTS_U             SMCSTS           ; // 0x10
} NRC_SMC_Type;

#ifdef __cplusplus
}
#endif

#endif /* __REG_NRC_SMC_H__ */
