/*********************************************************************/
/*    Newracom Library / IP Product                                  */
/*    Product Name :                                                 */
/*    Version      :                                                 */
/*    Author       :                                                 */
/*    Update       :                                                 */
/*********************************************************************/

#ifndef __REG_PWM_H__
#define __REG_PWM_H__

#ifdef __cplusplus
extern "C"{
#endif

// 0x4000D000 register ------------------------------------
typedef struct {
    uint32_t         BUSY_A          :1 ;
    uint32_t         BUSY_B          :1 ;
    uint32_t         BUSY_C          :1 ;
    uint32_t         BUSY_D          :1 ;
    uint32_t         reserved0       :28;
}   PWM_ST;

typedef union {
    uint32_t         w;
    PWM_ST           b;
}   PWM_ST_U;


// 0x4000D004 register ------------------------------------
typedef struct {
    uint32_t         EN_A            :1 ;
    uint32_t         EN_B            :1 ;
    uint32_t         EN_C            :1 ;
    uint32_t         EN_D            :1 ;
    uint32_t         reserved0       :12;
    uint32_t         TRIG_A          :1 ;
    uint32_t         TRIG_B          :1 ;
    uint32_t         TRIG_C          :1 ;
    uint32_t         TRIG_D          :1 ;
    uint32_t         reserved1       :12;
}   PWM_EN;

typedef union {
    uint32_t         w;
    PWM_EN           b;
}   PWM_EN_U;


// 0x4000D008 register ------------------------------------
typedef struct {
    uint32_t         MODE_A          :4 ;
    uint32_t         MODE_B          :4 ;
    uint32_t         MODE_C          :4 ;
    uint32_t         MODE_D          :4 ;
    uint32_t         INV_A           :1 ;
    uint32_t         INV_B           :1 ;
    uint32_t         INV_C           :1 ;
    uint32_t         INV_D           :1 ;
    uint32_t         reserved0       :4 ;
    uint32_t         DIV_A           :2 ;
    uint32_t         DIV_B           :2 ;
    uint32_t         DIV_C           :2 ;
    uint32_t         DIV_D           :2 ;
}   PWM_MODE;

typedef union {
    uint32_t         w;
    PWM_MODE         b;
}   PWM_MODE_U;


// 0x4000D00C register ------------------------------------
typedef struct {
    uint32_t         Loop_A          :4 ;
    uint32_t         Loop_B          :4 ;
    uint32_t         Loop_C          :4 ;
    uint32_t         Loop_D          :4 ;
    uint32_t         reserved0       :16;
}   PWM_LOOP;

typedef union {
    uint32_t         w;
    PWM_LOOP         b;
}   PWM_LOOP_U;


// 0x4000D010 register ------------------------------------
typedef struct {
    uint32_t         PwmPstn1_A      :16;
    uint32_t         PwmPstn2_A      :16;
}   PWM_A_P12;

typedef union {
    uint32_t         w;
    PWM_A_P12        b;
}   PWM_A_P12_U;


// 0x4000D014 register ------------------------------------
typedef struct {
    uint32_t         PwmPstn3_A      :16;
    uint32_t         PwmPstn4_A      :16;
}   PWM_A_P34;

typedef union {
    uint32_t         w;
    PWM_A_P34        b;
}   PWM_A_P34_U;


// 0x4000D018 register ------------------------------------
typedef struct {
    uint32_t         PwmPstn1_B      :16;
    uint32_t         PwmPstn2_B      :16;
}   PWM_B_P12;

typedef union {
    uint32_t         w;
    PWM_B_P12        b;
}   PWM_B_P12_U;


// 0x4000D01C register ------------------------------------
typedef struct {
    uint32_t         PwmPstn3_B      :16;
    uint32_t         PwmPstn4_B      :16;
}   PWM_B_P34;

typedef union {
    uint32_t         w;
    PWM_B_P34        b;
}   PWM_B_P34_U;


// 0x4000D020 register ------------------------------------
typedef struct {
    uint32_t         PwmPstn1_C      :16;
    uint32_t         PwmPstn2_C      :16;
}   PWM_C_P12;

typedef union {
    uint32_t         w;
    PWM_C_P12        b;
}   PWM_C_P12_U;


// 0x4000D024 register ------------------------------------
typedef struct {
    uint32_t         PwmPstn3_C      :16;
    uint32_t         PwmPstn4_C      :16;
}   PWM_C_P34;

typedef union {
    uint32_t         w;
    PWM_C_P34        b;
}   PWM_C_P34_U;


// 0x4000D028 register ------------------------------------
typedef struct {
    uint32_t         PwmPstn1_D      :16;
    uint32_t         PwmPstn2_D      :16;
}   PWM_D_P12;

typedef union {
    uint32_t         w;
    PWM_D_P12        b;
}   PWM_D_P12_U;


// 0x4000D02C register ------------------------------------
typedef struct {
    uint32_t         PwmPstn3_D      :16;
    uint32_t         PwmPstn4_D      :16;
}   PWM_D_P34;

typedef union {
    uint32_t         w;
    PWM_D_P34        b;
}   PWM_D_P34_U;


// 0x4000D030 register ------------------------------------
typedef struct {
    uint32_t         PwmOutReg_N1    :32;
}   PWM_OutRegA1;

typedef union {
    uint32_t         w;
    PWM_OutRegA1     b;
}   PWM_OutRegA1_U;


// 0x4000D034 register ------------------------------------
typedef struct {
    uint32_t         PwmOutReg_N2    :32;
}   PWM_OutRegA2;

typedef union {
    uint32_t         w;
    PWM_OutRegA2     b;
}   PWM_OutRegA2_U;


// 0x4000D038 register ------------------------------------
typedef struct {
    uint32_t         PwmOutReg_N3    :32;
}   PWM_OutRegA3;

typedef union {
    uint32_t         w;
    PWM_OutRegA3     b;
}   PWM_OutRegA3_U;


// 0x4000D03C register ------------------------------------
typedef struct {
    uint32_t         PwmOutReg_N4    :32;
}   PWM_OutRegA4;

typedef union {
    uint32_t         w;
    PWM_OutRegA4     b;
}   PWM_OutRegA4_U;


// 0x4000D040 register ------------------------------------
typedef struct {
    uint32_t         PwmOutReg_N1    :32;
}   PWM_OutRegB1;

typedef union {
    uint32_t         w;
    PWM_OutRegB1     b;
}   PWM_OutRegB1_U;


// 0x4000D044 register ------------------------------------
typedef struct {
    uint32_t         PwmOutReg_N2    :32;
}   PWM_OutRegB2;

typedef union {
    uint32_t         w;
    PWM_OutRegB2     b;
}   PWM_OutRegB2_U;


// 0x4000D048 register ------------------------------------
typedef struct {
    uint32_t         PwmOutReg_N3    :32;
}   PWM_OutRegB3;

typedef union {
    uint32_t         w;
    PWM_OutRegB3     b;
}   PWM_OutRegB3_U;


// 0x4000D04C register ------------------------------------
typedef struct {
    uint32_t         PwmOutReg_N4    :32;
}   PWM_OutRegB4;

typedef union {
    uint32_t         w;
    PWM_OutRegB4     b;
}   PWM_OutRegB4_U;


// 0x4000D050 register ------------------------------------
typedef struct {
    uint32_t         PwmOutReg_N1    :32;
}   PWM_OutRegC1;

typedef union {
    uint32_t         w;
    PWM_OutRegC1     b;
}   PWM_OutRegC1_U;


// 0x4000D054 register ------------------------------------
typedef struct {
    uint32_t         PwmOutReg_N2    :32;
}   PWM_OutRegC2;

typedef union {
    uint32_t         w;
    PWM_OutRegC2     b;
}   PWM_OutRegC2_U;


// 0x4000D058 register ------------------------------------
typedef struct {
    uint32_t         PwmOutReg_N3    :32;
}   PWM_OutRegC3;

typedef union {
    uint32_t         w;
    PWM_OutRegC3     b;
}   PWM_OutRegC3_U;


// 0x4000D05C register ------------------------------------
typedef struct {
    uint32_t         PwmOutReg_N4    :32;
}   PWM_OutRegC4;

typedef union {
    uint32_t         w;
    PWM_OutRegC4     b;
}   PWM_OutRegC4_U;


// 0x4000D060 register ------------------------------------
typedef struct {
    uint32_t         PwmOutReg_N1    :32;
}   PWM_OutRegD1;

typedef union {
    uint32_t         w;
    PWM_OutRegD1     b;
}   PWM_OutRegD1_U;


// 0x4000D064 register ------------------------------------
typedef struct {
    uint32_t         PwmOutReg_N2    :32;
}   PWM_OutRegD2;

typedef union {
    uint32_t         w;
    PWM_OutRegD2     b;
}   PWM_OutRegD2_U;


// 0x4000D068 register ------------------------------------
typedef struct {
    uint32_t         PwmOutReg_N3    :32;
}   PWM_OutRegD3;

typedef union {
    uint32_t         w;
    PWM_OutRegD3     b;
}   PWM_OutRegD3_U;


// 0x4000D06C register ------------------------------------
typedef struct {
    uint32_t         PwmOutReg_N4    :32;
}   PWM_OutRegD4;

typedef union {
    uint32_t         w;
    PWM_OutRegD4     b;
}   PWM_OutRegD4_U;


//---------------------------------------------------------
// PWM Register Map
//---------------------------------------------------------
typedef struct {
    volatile PWM_ST_U                ST              ; // 0x00
    volatile PWM_EN_U                EN              ; // 0x04
    volatile PWM_MODE_U              MODE            ; // 0x08
    volatile PWM_LOOP_U              LOOP            ; // 0x0c
    volatile PWM_A_P12_U             A_P12           ; // 0x10
    volatile PWM_A_P34_U             A_P34           ; // 0x14
    volatile PWM_B_P12_U             B_P12           ; // 0x18
    volatile PWM_B_P34_U             B_P34           ; // 0x1c
    volatile PWM_C_P12_U             C_P12           ; // 0x20
    volatile PWM_C_P34_U             C_P34           ; // 0x24
    volatile PWM_D_P12_U             D_P12           ; // 0x28
    volatile PWM_D_P34_U             D_P34           ; // 0x2c
    volatile PWM_OutRegA1_U          OutRegA1        ; // 0x30
    volatile PWM_OutRegA2_U          OutRegA2        ; // 0x34
    volatile PWM_OutRegA3_U          OutRegA3        ; // 0x38
    volatile PWM_OutRegA4_U          OutRegA4        ; // 0x3c
    volatile PWM_OutRegB1_U          OutRegB1        ; // 0x40
    volatile PWM_OutRegB2_U          OutRegB2        ; // 0x44
    volatile PWM_OutRegB3_U          OutRegB3        ; // 0x48
    volatile PWM_OutRegB4_U          OutRegB4        ; // 0x4c
    volatile PWM_OutRegC1_U          OutRegC1        ; // 0x50
    volatile PWM_OutRegC2_U          OutRegC2        ; // 0x54
    volatile PWM_OutRegC3_U          OutRegC3        ; // 0x58
    volatile PWM_OutRegC4_U          OutRegC4        ; // 0x5c
    volatile PWM_OutRegD1_U          OutRegD1        ; // 0x60
    volatile PWM_OutRegD2_U          OutRegD2        ; // 0x64
    volatile PWM_OutRegD3_U          OutRegD3        ; // 0x68
    volatile PWM_OutRegD4_U          OutRegD4        ; // 0x6c
} PWM_Type;

#ifdef __cplusplus
}
#endif

#endif /* __REG_PWM_H__ */
