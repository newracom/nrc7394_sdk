/*********************************************************************/
/*    Newracom Library / IP Product                                  */
/*    Product Name :                                                 */
/*    Version      :                                                 */
/*    Author       :                                                 */
/*    Update       :                                                 */
/*********************************************************************/

#ifndef __REG_GPIO_H__
#define __REG_GPIO_H__

#ifdef __cplusplus
extern "C"{
#endif

// 0x40005000 register ------------------------------------
typedef struct {
    uint32_t             Pn0              :1 ;
    uint32_t             Pn1              :1 ;
    uint32_t             Pn2              :1 ;
    uint32_t             Pn3              :1 ;
    uint32_t             Pn4              :1 ;
    uint32_t             Pn5              :1 ;
    uint32_t             Pn6              :1 ;
    uint32_t             Pn7              :1 ;
    uint32_t             Pn8              :1 ;
    uint32_t             Pn9              :1 ;
    uint32_t             Pn10             :1 ;
    uint32_t             Pn11             :1 ;
    uint32_t             Pn12             :1 ;
    uint32_t             Pn13             :1 ;
    uint32_t             Pn14             :1 ;
    uint32_t             Pn15             :1 ;
    uint32_t             Pn16             :1 ;
    uint32_t             Pn17             :1 ;
    uint32_t             Pn18             :1 ;
    uint32_t             Pn19             :1 ;
    uint32_t             Pn20             :1 ;
    uint32_t             Pn21             :1 ;
    uint32_t             Pn22             :1 ;
    uint32_t             Pn23             :1 ;
    uint32_t             Pn24             :1 ;
    uint32_t             Pn25             :1 ;
    uint32_t             Pn26             :1 ;
    uint32_t             Pn27             :1 ;
    uint32_t             Pn28             :1 ;
    uint32_t             Pn29             :1 ;
    uint32_t             Pn30             :1 ;
    uint32_t             Pn31             :1 ;
}   GPIO_Pn_DATA;

typedef union {
    uint32_t             w;
    GPIO_Pn_DATA         b;
}   GPIO_Pn_DATA_U;


// 0x40005004 register ------------------------------------
typedef struct {
    uint32_t             PnDIR0           :1 ;
    uint32_t             PnDIR1           :1 ;
    uint32_t             PnDIR2           :1 ;
    uint32_t             PnDIR3           :1 ;
    uint32_t             PnDIR4           :1 ;
    uint32_t             PnDIR5           :1 ;
    uint32_t             PnDIR6           :1 ;
    uint32_t             PnDIR7           :1 ;
    uint32_t             PnDIR8           :1 ;
    uint32_t             PnDIR9           :1 ;
    uint32_t             PnDIR10          :1 ;
    uint32_t             PnDIR11          :1 ;
    uint32_t             PnDIR12          :1 ;
    uint32_t             PnDIR13          :1 ;
    uint32_t             PnDIR14          :1 ;
    uint32_t             PnDIR15          :1 ;
    uint32_t             PnDIR16          :1 ;
    uint32_t             PnDIR17          :1 ;
    uint32_t             PnDIR18          :1 ;
    uint32_t             PnDIR19          :1 ;
    uint32_t             PnDIR20          :1 ;
    uint32_t             PnDIR21          :1 ;
    uint32_t             PnDIR22          :1 ;
    uint32_t             PnDIR23          :1 ;
    uint32_t             PnDIR24          :1 ;
    uint32_t             PnDIR25          :1 ;
    uint32_t             PnDIR26          :1 ;
    uint32_t             PnDIR27          :1 ;
    uint32_t             PnDIR28          :1 ;
    uint32_t             PnDIR29          :1 ;
    uint32_t             PnDIR30          :1 ;
    uint32_t             PnDIR31          :1 ;
}   GPIO_Pn_DIR;

typedef union {
    uint32_t             w;
    GPIO_Pn_DIR          b;
}   GPIO_Pn_DIR_U;


// 0x40005008 register ------------------------------------
typedef struct {
    uint32_t             PnALT0_0         :1 ;
    uint32_t             PnALT0_1         :1 ;
    uint32_t             PnALT0_2         :1 ;
    uint32_t             PnALT0_3         :1 ;
    uint32_t             PnALT0_4         :1 ;
    uint32_t             PnALT0_5         :1 ;
    uint32_t             PnALT0_6         :1 ;
    uint32_t             PnALT0_7         :1 ;
    uint32_t             PnALT0_8         :1 ;
    uint32_t             PnALT0_9         :1 ;
    uint32_t             PnALT0_10        :1 ;
    uint32_t             PnALT0_11        :1 ;
    uint32_t             PnALT0_12        :1 ;
    uint32_t             PnALT0_13        :1 ;
    uint32_t             PnALT0_14        :1 ;
    uint32_t             PnALT0_15        :1 ;
    uint32_t             PnALT0_16        :1 ;
    uint32_t             PnALT0_17        :1 ;
    uint32_t             PnALT0_18        :1 ;
    uint32_t             PnALT0_19        :1 ;
    uint32_t             PnALT0_20        :1 ;
    uint32_t             PnALT0_21        :1 ;
    uint32_t             PnALT0_22        :1 ;
    uint32_t             PnALT0_23        :1 ;
    uint32_t             PnALT0_24        :1 ;
    uint32_t             PnALT0_25        :1 ;
    uint32_t             PnALT0_26        :1 ;
    uint32_t             PnALT0_27        :1 ;
    uint32_t             PnALT0_28        :1 ;
    uint32_t             PnALT0_29        :1 ;
    uint32_t             PnALT0_30        :1 ;
    uint32_t             PnALT0_31        :1 ;
}   GPIO_Pn_ALT0;

typedef union {
    uint32_t             w;
    GPIO_Pn_ALT0         b;
}   GPIO_Pn_ALT0_U;


// 0x4000500C register ------------------------------------
typedef struct {
    uint32_t             PnALT1_0         :1 ;
    uint32_t             PnALT1_1         :1 ;
    uint32_t             PnALT1_2         :1 ;
    uint32_t             PnALT1_3         :1 ;
    uint32_t             PnALT1_4         :1 ;
    uint32_t             PnALT1_5         :1 ;
    uint32_t             PnALT1_6         :1 ;
    uint32_t             PnALT1_7         :1 ;
    uint32_t             PnALT1_8         :1 ;
    uint32_t             PnALT1_9         :1 ;
    uint32_t             PnALT1_10        :1 ;
    uint32_t             PnALT1_11        :1 ;
    uint32_t             PnALT1_12        :1 ;
    uint32_t             PnALT1_13        :1 ;
    uint32_t             PnALT1_14        :1 ;
    uint32_t             PnALT1_15        :1 ;
    uint32_t             PnALT1_16        :1 ;
    uint32_t             PnALT1_17        :1 ;
    uint32_t             PnALT1_18        :1 ;
    uint32_t             PnALT1_19        :1 ;
    uint32_t             PnALT1_20        :1 ;
    uint32_t             PnALT1_21        :1 ;
    uint32_t             PnALT1_22        :1 ;
    uint32_t             PnALT1_23        :1 ;
    uint32_t             PnALT1_24        :1 ;
    uint32_t             PnALT1_25        :1 ;
    uint32_t             PnALT1_26        :1 ;
    uint32_t             PnALT1_27        :1 ;
    uint32_t             PnALT1_28        :1 ;
    uint32_t             PnALT1_29        :1 ;
    uint32_t             PnALT1_30        :1 ;
    uint32_t             PnALT1_31        :1 ;
}   GPIO_Pn_ALT1;

typedef union {
    uint32_t             w;
    GPIO_Pn_ALT1         b;
}   GPIO_Pn_ALT1_U;


// 0x40005010 register ------------------------------------
typedef struct {
    uint32_t             PnALT2_0         :1 ;
    uint32_t             PnALT2_1         :1 ;
    uint32_t             PnALT2_2         :1 ;
    uint32_t             PnALT2_3         :1 ;
    uint32_t             PnALT2_4         :1 ;
    uint32_t             PnALT2_5         :1 ;
    uint32_t             PnALT2_6         :1 ;
    uint32_t             PnALT2_7         :1 ;
    uint32_t             PnALT2_8         :1 ;
    uint32_t             PnALT2_9         :1 ;
    uint32_t             PnALT2_10        :1 ;
    uint32_t             PnALT2_11        :1 ;
    uint32_t             PnALT2_12        :1 ;
    uint32_t             PnALT2_13        :1 ;
    uint32_t             PnALT2_14        :1 ;
    uint32_t             PnALT2_15        :1 ;
    uint32_t             PnALT2_16        :1 ;
    uint32_t             PnALT2_17        :1 ;
    uint32_t             PnALT2_18        :1 ;
    uint32_t             PnALT2_19        :1 ;
    uint32_t             PnALT2_20        :1 ;
    uint32_t             PnALT2_21        :1 ;
    uint32_t             PnALT2_22        :1 ;
    uint32_t             PnALT2_23        :1 ;
    uint32_t             PnALT2_24        :1 ;
    uint32_t             PnALT2_25        :1 ;
    uint32_t             PnALT2_26        :1 ;
    uint32_t             PnALT2_27        :1 ;
    uint32_t             PnALT2_28        :1 ;
    uint32_t             PnALT2_29        :1 ;
    uint32_t             PnALT2_30        :1 ;
    uint32_t             PnALT2_31        :1 ;
}   GPIO_Pn_ALT2;

typedef union {
    uint32_t             w;
    GPIO_Pn_ALT2         b;
}   GPIO_Pn_ALT2_U;


// 0x40005014 register ------------------------------------
typedef struct {
    uint32_t             PnALT3_0         :1 ;
    uint32_t             PnALT3_1         :1 ;
    uint32_t             PnALT3_2         :1 ;
    uint32_t             PnALT3_3         :1 ;
    uint32_t             PnALT3_4         :1 ;
    uint32_t             PnALT3_5         :1 ;
    uint32_t             PnALT3_6         :1 ;
    uint32_t             PnALT3_7         :1 ;
    uint32_t             PnALT3_8         :1 ;
    uint32_t             PnALT3_9         :1 ;
    uint32_t             PnALT3_10        :1 ;
    uint32_t             PnALT3_11        :1 ;
    uint32_t             PnALT3_12        :1 ;
    uint32_t             PnALT3_13        :1 ;
    uint32_t             PnALT3_14        :1 ;
    uint32_t             PnALT3_15        :1 ;
    uint32_t             PnALT3_16        :1 ;
    uint32_t             PnALT3_17        :1 ;
    uint32_t             PnALT3_18        :1 ;
    uint32_t             PnALT3_19        :1 ;
    uint32_t             PnALT3_20        :1 ;
    uint32_t             PnALT3_21        :1 ;
    uint32_t             PnALT3_22        :1 ;
    uint32_t             PnALT3_23        :1 ;
    uint32_t             PnALT3_24        :1 ;
    uint32_t             PnALT3_25        :1 ;
    uint32_t             PnALT3_26        :1 ;
    uint32_t             PnALT3_27        :1 ;
    uint32_t             PnALT3_28        :1 ;
    uint32_t             PnALT3_29        :1 ;
    uint32_t             PnALT3_30        :1 ;
    uint32_t             PnALT3_31        :1 ;
}   GPIO_Pn_ALT3;

typedef union {
    uint32_t             w;
    GPIO_Pn_ALT3         b;
}   GPIO_Pn_ALT3_U;


// 0x40005018 register ------------------------------------
typedef struct {
    uint32_t             PnALT4_0         :1 ;
    uint32_t             PnALT4_1         :1 ;
    uint32_t             PnALT4_2         :1 ;
    uint32_t             PnALT4_3         :1 ;
    uint32_t             PnALT4_4         :1 ;
    uint32_t             PnALT4_5         :1 ;
    uint32_t             PnALT4_6         :1 ;
    uint32_t             PnALT4_7         :1 ;
    uint32_t             PnALT4_8         :1 ;
    uint32_t             PnALT4_9         :1 ;
    uint32_t             PnALT4_10        :1 ;
    uint32_t             PnALT4_11        :1 ;
    uint32_t             PnALT4_12        :1 ;
    uint32_t             PnALT4_13        :1 ;
    uint32_t             PnALT4_14        :1 ;
    uint32_t             PnALT4_15        :1 ;
    uint32_t             PnALT4_16        :1 ;
    uint32_t             PnALT4_17        :1 ;
    uint32_t             PnALT4_18        :1 ;
    uint32_t             PnALT4_19        :1 ;
    uint32_t             PnALT4_20        :1 ;
    uint32_t             PnALT4_21        :1 ;
    uint32_t             PnALT4_22        :1 ;
    uint32_t             PnALT4_23        :1 ;
    uint32_t             PnALT4_24        :1 ;
    uint32_t             PnALT4_25        :1 ;
    uint32_t             PnALT4_26        :1 ;
    uint32_t             PnALT4_27        :1 ;
    uint32_t             PnALT4_28        :1 ;
    uint32_t             PnALT4_29        :1 ;
    uint32_t             PnALT4_30        :1 ;
    uint32_t             PnALT4_31        :1 ;
}   GPIO_Pn_ALT4;

typedef union {
    uint32_t             w;
    GPIO_Pn_ALT4         b;
}   GPIO_Pn_ALT4_U;


// 0x40005030 register ------------------------------------
typedef struct {
    uint32_t             PnPU0            :1 ;
    uint32_t             PnPU1            :1 ;
    uint32_t             PnPU2            :1 ;
    uint32_t             PnPU3            :1 ;
    uint32_t             PnPU4            :1 ;
    uint32_t             PnPU5            :1 ;
    uint32_t             PnPU6            :1 ;
    uint32_t             PnPU7            :1 ;
    uint32_t             PnPU8            :1 ;
    uint32_t             PnPU9            :1 ;
    uint32_t             PnPU10           :1 ;
    uint32_t             PnPU11           :1 ;
    uint32_t             PnPU12           :1 ;
    uint32_t             PnPU13           :1 ;
    uint32_t             PnPU14           :1 ;
    uint32_t             PnPU15           :1 ;
    uint32_t             PnPU16           :1 ;
    uint32_t             PnPU17           :1 ;
    uint32_t             PnPU18           :1 ;
    uint32_t             PnPU19           :1 ;
    uint32_t             PnPU20           :1 ;
    uint32_t             PnPU21           :1 ;
    uint32_t             PnPU22           :1 ;
    uint32_t             PnPU23           :1 ;
    uint32_t             PnPU24           :1 ;
    uint32_t             PnPU25           :1 ;
    uint32_t             PnPU26           :1 ;
    uint32_t             PnPU27           :1 ;
    uint32_t             PnPU28           :1 ;
    uint32_t             PnPU29           :1 ;
    uint32_t             PnPU30           :1 ;
    uint32_t             PnPU31           :1 ;
}   GPIO_Pn_PULLUP;

typedef union {
    uint32_t             w;
    GPIO_Pn_PULLUP       b;
}   GPIO_Pn_PULLUP_U;


// 0x40005038 register ------------------------------------
typedef struct {
    uint32_t             PnDRV0           :16;
    uint32_t             reserved0        :16;
}   GPIO_Pn_DRV0;

typedef union {
    uint32_t             w;
    GPIO_Pn_DRV0         b;
}   GPIO_Pn_DRV0_U;


// 0x4000503C register ------------------------------------
typedef struct {
    uint32_t             PnDRV1           :16;
    uint32_t             reserved0        :16;
}   GPIO_Pn_DRV1;

typedef union {
    uint32_t             w;
    GPIO_Pn_DRV1         b;
}   GPIO_Pn_DRV1_U;


// 0x40005200 register ------------------------------------
typedef struct {
    uint32_t             PnOUT_CLR0       :1 ;
    uint32_t             PnOUT_CLR1       :1 ;
    uint32_t             PnOUT_CLR2       :1 ;
    uint32_t             PnOUT_CLR3       :1 ;
    uint32_t             PnOUT_CLR4       :1 ;
    uint32_t             PnOUT_CLR5       :1 ;
    uint32_t             PnOUT_CLR6       :1 ;
    uint32_t             PnOUT_CLR7       :1 ;
    uint32_t             PnOUT_CLR8       :1 ;
    uint32_t             PnOUT_CLR9       :1 ;
    uint32_t             PnOUT_CLR10      :1 ;
    uint32_t             PnOUT_CLR11      :1 ;
    uint32_t             PnOUT_CLR12      :1 ;
    uint32_t             PnOUT_CLR13      :1 ;
    uint32_t             PnOUT_CLR14      :1 ;
    uint32_t             PnOUT_CLR15      :1 ;
    uint32_t             PnOUT_CLR16      :1 ;
    uint32_t             PnOUT_CLR17      :1 ;
    uint32_t             PnOUT_CLR18      :1 ;
    uint32_t             PnOUT_CLR19      :1 ;
    uint32_t             PnOUT_CLR20      :1 ;
    uint32_t             PnOUT_CLR21      :1 ;
    uint32_t             PnOUT_CLR22      :1 ;
    uint32_t             PnOUT_CLR23      :1 ;
    uint32_t             PnOUT_CLR24      :1 ;
    uint32_t             PnOUT_CLR25      :1 ;
    uint32_t             PnOUT_CLR26      :1 ;
    uint32_t             PnOUT_CLR27      :1 ;
    uint32_t             PnOUT_CLR28      :1 ;
    uint32_t             PnOUT_CLR29      :1 ;
    uint32_t             PnOUT_CLR30      :1 ;
    uint32_t             PnOUT_CLR31      :1 ;
}   GPIO_Pn_DATA_CLR;

typedef union {
    uint32_t             w;
    GPIO_Pn_DATA_CLR     b;
}   GPIO_Pn_DATA_CLR_U;


// 0x40005204 register ------------------------------------
typedef struct {
    uint32_t             PnDIR_CLR0       :1 ;
    uint32_t             PnDIR_CLR1       :1 ;
    uint32_t             PnDIR_CLR2       :1 ;
    uint32_t             PnDIR_CLR3       :1 ;
    uint32_t             PnDIR_CLR4       :1 ;
    uint32_t             PnDIR_CLR5       :1 ;
    uint32_t             PnDIR_CLR6       :1 ;
    uint32_t             PnDIR_CLR7       :1 ;
    uint32_t             PnDIR_CLR8       :1 ;
    uint32_t             PnDIR_CLR9       :1 ;
    uint32_t             PnDIR_CLR10      :1 ;
    uint32_t             PnDIR_CLR11      :1 ;
    uint32_t             PnDIR_CLR12      :1 ;
    uint32_t             PnDIR_CLR13      :1 ;
    uint32_t             PnDIR_CLR14      :1 ;
    uint32_t             PnDIR_CLR15      :1 ;
    uint32_t             PnDIR_CLR16      :1 ;
    uint32_t             PnDIR_CLR17      :1 ;
    uint32_t             PnDIR_CLR18      :1 ;
    uint32_t             PnDIR_CLR19      :1 ;
    uint32_t             PnDIR_CLR20      :1 ;
    uint32_t             PnDIR_CLR21      :1 ;
    uint32_t             PnDIR_CLR22      :1 ;
    uint32_t             PnDIR_CLR23      :1 ;
    uint32_t             PnDIR_CLR24      :1 ;
    uint32_t             PnDIR_CLR25      :1 ;
    uint32_t             PnDIR_CLR26      :1 ;
    uint32_t             PnDIR_CLR27      :1 ;
    uint32_t             PnDIR_CLR28      :1 ;
    uint32_t             PnDIR_CLR29      :1 ;
    uint32_t             PnDIR_CLR30      :1 ;
    uint32_t             PnDIR_CLR31      :1 ;
}   GPIO_Pn_DIR_CLR;

typedef union {
    uint32_t             w;
    GPIO_Pn_DIR_CLR      b;
}   GPIO_Pn_DIR_CLR_U;


// 0x40005208 register ------------------------------------
typedef struct {
    uint32_t             PnALT0_CLR0      :1 ;
    uint32_t             PnALT0_CLR1      :1 ;
    uint32_t             PnALT0_CLR2      :1 ;
    uint32_t             PnALT0_CLR3      :1 ;
    uint32_t             PnALT0_CLR4      :1 ;
    uint32_t             PnALT0_CLR5      :1 ;
    uint32_t             PnALT0_CLR6      :1 ;
    uint32_t             PnALT0_CLR7      :1 ;
    uint32_t             PnALT0_CLR8      :1 ;
    uint32_t             PnALT0_CLR9      :1 ;
    uint32_t             PnALT0_CLR10     :1 ;
    uint32_t             PnALT0_CLR11     :1 ;
    uint32_t             PnALT0_CLR12     :1 ;
    uint32_t             PnALT0_CLR13     :1 ;
    uint32_t             PnALT0_CLR14     :1 ;
    uint32_t             PnALT0_CLR15     :1 ;
    uint32_t             PnALT0_CLR16     :1 ;
    uint32_t             PnALT0_CLR17     :1 ;
    uint32_t             PnALT0_CLR18     :1 ;
    uint32_t             PnALT0_CLR19     :1 ;
    uint32_t             PnALT0_CLR20     :1 ;
    uint32_t             PnALT0_CLR21     :1 ;
    uint32_t             PnALT0_CLR22     :1 ;
    uint32_t             PnALT0_CLR23     :1 ;
    uint32_t             PnALT0_CLR24     :1 ;
    uint32_t             PnALT0_CLR25     :1 ;
    uint32_t             PnALT0_CLR26     :1 ;
    uint32_t             PnALT0_CLR27     :1 ;
    uint32_t             PnALT0_CLR28     :1 ;
    uint32_t             PnALT0_CLR29     :1 ;
    uint32_t             PnALT0_CLR30     :1 ;
    uint32_t             PnALT0_CLR31     :1 ;
}   GPIO_Pn_ALT0_CLR;

typedef union {
    uint32_t             w;
    GPIO_Pn_ALT0_CLR     b;
}   GPIO_Pn_ALT0_CLR_U;


// 0x4000520C register ------------------------------------
typedef struct {
    uint32_t             PnALT1_CLR0      :1 ;
    uint32_t             PnALT1_CLR1      :1 ;
    uint32_t             PnALT1_CLR2      :1 ;
    uint32_t             PnALT1_CLR3      :1 ;
    uint32_t             PnALT1_CLR4      :1 ;
    uint32_t             PnALT1_CLR5      :1 ;
    uint32_t             PnALT1_CLR6      :1 ;
    uint32_t             PnALT1_CLR7      :1 ;
    uint32_t             PnALT1_CLR8      :1 ;
    uint32_t             PnALT1_CLR9      :1 ;
    uint32_t             PnALT1_CLR10     :1 ;
    uint32_t             PnALT1_CLR11     :1 ;
    uint32_t             PnALT1_CLR12     :1 ;
    uint32_t             PnALT1_CLR13     :1 ;
    uint32_t             PnALT1_CLR14     :1 ;
    uint32_t             PnALT1_CLR15     :1 ;
    uint32_t             PnALT1_CLR16     :1 ;
    uint32_t             PnALT1_CLR17     :1 ;
    uint32_t             PnALT1_CLR18     :1 ;
    uint32_t             PnALT1_CLR19     :1 ;
    uint32_t             PnALT1_CLR20     :1 ;
    uint32_t             PnALT1_CLR21     :1 ;
    uint32_t             PnALT1_CLR22     :1 ;
    uint32_t             PnALT1_CLR23     :1 ;
    uint32_t             PnALT1_CLR24     :1 ;
    uint32_t             PnALT1_CLR25     :1 ;
    uint32_t             PnALT1_CLR26     :1 ;
    uint32_t             PnALT1_CLR27     :1 ;
    uint32_t             PnALT1_CLR28     :1 ;
    uint32_t             PnALT1_CLR29     :1 ;
    uint32_t             PnALT1_CLR30     :1 ;
    uint32_t             PnALT1_CLR31     :1 ;
}   GPIO_Pn_ALT1_CLR;

typedef union {
    uint32_t             w;
    GPIO_Pn_ALT1_CLR     b;
}   GPIO_Pn_ALT1_CLR_U;


// 0x40005210 register ------------------------------------
typedef struct {
    uint32_t             PnALT2_CLR0      :1 ;
    uint32_t             PnALT2_CLR1      :1 ;
    uint32_t             PnALT2_CLR2      :1 ;
    uint32_t             PnALT2_CLR3      :1 ;
    uint32_t             PnALT2_CLR4      :1 ;
    uint32_t             PnALT2_CLR5      :1 ;
    uint32_t             PnALT2_CLR6      :1 ;
    uint32_t             PnALT2_CLR7      :1 ;
    uint32_t             PnALT2_CLR8      :1 ;
    uint32_t             PnALT2_CLR9      :1 ;
    uint32_t             PnALT2_CLR10     :1 ;
    uint32_t             PnALT2_CLR11     :1 ;
    uint32_t             PnALT2_CLR12     :1 ;
    uint32_t             PnALT2_CLR13     :1 ;
    uint32_t             PnALT2_CLR14     :1 ;
    uint32_t             PnALT2_CLR15     :1 ;
    uint32_t             PnALT2_CLR16     :1 ;
    uint32_t             PnALT2_CLR17     :1 ;
    uint32_t             PnALT2_CLR18     :1 ;
    uint32_t             PnALT2_CLR19     :1 ;
    uint32_t             PnALT2_CLR20     :1 ;
    uint32_t             PnALT2_CLR21     :1 ;
    uint32_t             PnALT2_CLR22     :1 ;
    uint32_t             PnALT2_CLR23     :1 ;
    uint32_t             PnALT2_CLR24     :1 ;
    uint32_t             PnALT2_CLR25     :1 ;
    uint32_t             PnALT2_CLR26     :1 ;
    uint32_t             PnALT2_CLR27     :1 ;
    uint32_t             PnALT2_CLR28     :1 ;
    uint32_t             PnALT2_CLR29     :1 ;
    uint32_t             PnALT2_CLR30     :1 ;
    uint32_t             PnALT2_CLR31     :1 ;
}   GPIO_Pn_ALT2_CLR;

typedef union {
    uint32_t             w;
    GPIO_Pn_ALT2_CLR     b;
}   GPIO_Pn_ALT2_CLR_U;


// 0x40005214 register ------------------------------------
typedef struct {
    uint32_t             PnALT3_CLR0      :1 ;
    uint32_t             PnALT3_CLR1      :1 ;
    uint32_t             PnALT3_CLR2      :1 ;
    uint32_t             PnALT3_CLR3      :1 ;
    uint32_t             PnALT3_CLR4      :1 ;
    uint32_t             PnALT3_CLR5      :1 ;
    uint32_t             PnALT3_CLR6      :1 ;
    uint32_t             PnALT3_CLR7      :1 ;
    uint32_t             PnALT3_CLR8      :1 ;
    uint32_t             PnALT3_CLR9      :1 ;
    uint32_t             PnALT3_CLR10     :1 ;
    uint32_t             PnALT3_CLR11     :1 ;
    uint32_t             PnALT3_CLR12     :1 ;
    uint32_t             PnALT3_CLR13     :1 ;
    uint32_t             PnALT3_CLR14     :1 ;
    uint32_t             PnALT3_CLR15     :1 ;
    uint32_t             PnALT3_CLR16     :1 ;
    uint32_t             PnALT3_CLR17     :1 ;
    uint32_t             PnALT3_CLR18     :1 ;
    uint32_t             PnALT3_CLR19     :1 ;
    uint32_t             PnALT3_CLR20     :1 ;
    uint32_t             PnALT3_CLR21     :1 ;
    uint32_t             PnALT3_CLR22     :1 ;
    uint32_t             PnALT3_CLR23     :1 ;
    uint32_t             PnALT3_CLR24     :1 ;
    uint32_t             PnALT3_CLR25     :1 ;
    uint32_t             PnALT3_CLR26     :1 ;
    uint32_t             PnALT3_CLR27     :1 ;
    uint32_t             PnALT3_CLR28     :1 ;
    uint32_t             PnALT3_CLR29     :1 ;
    uint32_t             PnALT3_CLR30     :1 ;
    uint32_t             PnALT3_CLR31     :1 ;
}   GPIO_Pn_ALT3_CLR;

typedef union {
    uint32_t             w;
    GPIO_Pn_ALT3_CLR     b;
}   GPIO_Pn_ALT3_CLR_U;


// 0x40005218 register ------------------------------------
typedef struct {
    uint32_t             PnALT4_CLR0      :1 ;
    uint32_t             PnALT4_CLR1      :1 ;
    uint32_t             PnALT4_CLR2      :1 ;
    uint32_t             PnALT4_CLR3      :1 ;
    uint32_t             PnALT4_CLR4      :1 ;
    uint32_t             PnALT4_CLR5      :1 ;
    uint32_t             PnALT4_CLR6      :1 ;
    uint32_t             PnALT4_CLR7      :1 ;
    uint32_t             PnALT4_CLR8      :1 ;
    uint32_t             PnALT4_CLR9      :1 ;
    uint32_t             PnALT4_CLR10     :1 ;
    uint32_t             PnALT4_CLR11     :1 ;
    uint32_t             PnALT4_CLR12     :1 ;
    uint32_t             PnALT4_CLR13     :1 ;
    uint32_t             PnALT4_CLR14     :1 ;
    uint32_t             PnALT4_CLR15     :1 ;
    uint32_t             PnALT4_CLR16     :1 ;
    uint32_t             PnALT4_CLR17     :1 ;
    uint32_t             PnALT4_CLR18     :1 ;
    uint32_t             PnALT4_CLR19     :1 ;
    uint32_t             PnALT4_CLR20     :1 ;
    uint32_t             PnALT4_CLR21     :1 ;
    uint32_t             PnALT4_CLR22     :1 ;
    uint32_t             PnALT4_CLR23     :1 ;
    uint32_t             PnALT4_CLR24     :1 ;
    uint32_t             PnALT4_CLR25     :1 ;
    uint32_t             PnALT4_CLR26     :1 ;
    uint32_t             PnALT4_CLR27     :1 ;
    uint32_t             PnALT4_CLR28     :1 ;
    uint32_t             PnALT4_CLR29     :1 ;
    uint32_t             PnALT4_CLR30     :1 ;
    uint32_t             PnALT4_CLR31     :1 ;
}   GPIO_Pn_ALT4_CLR;

typedef union {
    uint32_t             w;
    GPIO_Pn_ALT4_CLR     b;
}   GPIO_Pn_ALT4_CLR_U;


// 0x40005230 register ------------------------------------
typedef struct {
    uint32_t             PnPU_CLR0        :1 ;
    uint32_t             PnPU_CLR1        :1 ;
    uint32_t             PnPU_CLR2        :1 ;
    uint32_t             PnPU_CLR3        :1 ;
    uint32_t             PnPU_CLR4        :1 ;
    uint32_t             PnPU_CLR5        :1 ;
    uint32_t             PnPU_CLR6        :1 ;
    uint32_t             PnPU_CLR7        :1 ;
    uint32_t             PnPU_CLR8        :1 ;
    uint32_t             PnPU_CLR9        :1 ;
    uint32_t             PnPU_CLR10       :1 ;
    uint32_t             PnPU_CLR11       :1 ;
    uint32_t             PnPU_CLR12       :1 ;
    uint32_t             PnPU_CLR13       :1 ;
    uint32_t             PnPU_CLR14       :1 ;
    uint32_t             PnPU_CLR15       :1 ;
    uint32_t             PnPU_CLR16       :1 ;
    uint32_t             PnPU_CLR17       :1 ;
    uint32_t             PnPU_CLR18       :1 ;
    uint32_t             PnPU_CLR19       :1 ;
    uint32_t             PnPU_CLR20       :1 ;
    uint32_t             PnPU_CLR21       :1 ;
    uint32_t             PnPU_CLR22       :1 ;
    uint32_t             PnPU_CLR23       :1 ;
    uint32_t             PnPU_CLR24       :1 ;
    uint32_t             PnPU_CLR25       :1 ;
    uint32_t             PnPU_CLR26       :1 ;
    uint32_t             PnPU_CLR27       :1 ;
    uint32_t             PnPU_CLR28       :1 ;
    uint32_t             PnPU_CLR29       :1 ;
    uint32_t             PnPU_CLR30       :1 ;
    uint32_t             PnPU_CLR31       :1 ;
}   GPIO_Pn_PU_CLR;

typedef union {
    uint32_t             w;
    GPIO_Pn_PU_CLR       b;
}   GPIO_Pn_PU_CLR_U;


// 0x40005238 register ------------------------------------
typedef struct {
    uint32_t             PnDRV0_CLR       :16;
    uint32_t             reserved0        :16;
}   GPIO_Pn_DRV0_CLR;

typedef union {
    uint32_t             w;
    GPIO_Pn_DRV0_CLR     b;
}   GPIO_Pn_DRV0_CLR_U;


// 0x4000523C register ------------------------------------
typedef struct {
    uint32_t             PnDRV1_CLR       :16;
    uint32_t             reserved0        :16;
}   GPIO_Pn_DRV1_CLR;

typedef union {
    uint32_t             w;
    GPIO_Pn_DRV1_CLR     b;
}   GPIO_Pn_DRV1_CLR_U;


// 0x40005400 register ------------------------------------
typedef struct {
    uint32_t             PnOUT_SET0       :1 ;
    uint32_t             PnOUT_SET1       :1 ;
    uint32_t             PnOUT_SET2       :1 ;
    uint32_t             PnOUT_SET3       :1 ;
    uint32_t             PnOUT_SET4       :1 ;
    uint32_t             PnOUT_SET5       :1 ;
    uint32_t             PnOUT_SET6       :1 ;
    uint32_t             PnOUT_SET7       :1 ;
    uint32_t             PnOUT_SET8       :1 ;
    uint32_t             PnOUT_SET9       :1 ;
    uint32_t             PnOUT_SET10      :1 ;
    uint32_t             PnOUT_SET11      :1 ;
    uint32_t             PnOUT_SET12      :1 ;
    uint32_t             PnOUT_SET13      :1 ;
    uint32_t             PnOUT_SET14      :1 ;
    uint32_t             PnOUT_SET15      :1 ;
    uint32_t             PnOUT_SET16      :1 ;
    uint32_t             PnOUT_SET17      :1 ;
    uint32_t             PnOUT_SET18      :1 ;
    uint32_t             PnOUT_SET19      :1 ;
    uint32_t             PnOUT_SET20      :1 ;
    uint32_t             PnOUT_SET21      :1 ;
    uint32_t             PnOUT_SET22      :1 ;
    uint32_t             PnOUT_SET23      :1 ;
    uint32_t             PnOUT_SET24      :1 ;
    uint32_t             PnOUT_SET25      :1 ;
    uint32_t             PnOUT_SET26      :1 ;
    uint32_t             PnOUT_SET27      :1 ;
    uint32_t             PnOUT_SET28      :1 ;
    uint32_t             PnOUT_SET29      :1 ;
    uint32_t             PnOUT_SET30      :1 ;
    uint32_t             PnOUT_SET31      :1 ;
}   GPIO_Pn_DATA_SET;

typedef union {
    uint32_t             w;
    GPIO_Pn_DATA_SET     b;
}   GPIO_Pn_DATA_SET_U;


// 0x40005404 register ------------------------------------
typedef struct {
    uint32_t             PnDIR_SET0       :1 ;
    uint32_t             PnDIR_SET1       :1 ;
    uint32_t             PnDIR_SET2       :1 ;
    uint32_t             PnDIR_SET3       :1 ;
    uint32_t             PnDIR_SET4       :1 ;
    uint32_t             PnDIR_SET5       :1 ;
    uint32_t             PnDIR_SET6       :1 ;
    uint32_t             PnDIR_SET7       :1 ;
    uint32_t             PnDIR_SET8       :1 ;
    uint32_t             PnDIR_SET9       :1 ;
    uint32_t             PnDIR_SET10      :1 ;
    uint32_t             PnDIR_SET11      :1 ;
    uint32_t             PnDIR_SET12      :1 ;
    uint32_t             PnDIR_SET13      :1 ;
    uint32_t             PnDIR_SET14      :1 ;
    uint32_t             PnDIR_SET15      :1 ;
    uint32_t             PnDIR_SET16      :1 ;
    uint32_t             PnDIR_SET17      :1 ;
    uint32_t             PnDIR_SET18      :1 ;
    uint32_t             PnDIR_SET19      :1 ;
    uint32_t             PnDIR_SET20      :1 ;
    uint32_t             PnDIR_SET21      :1 ;
    uint32_t             PnDIR_SET22      :1 ;
    uint32_t             PnDIR_SET23      :1 ;
    uint32_t             PnDIR_SET24      :1 ;
    uint32_t             PnDIR_SET25      :1 ;
    uint32_t             PnDIR_SET26      :1 ;
    uint32_t             PnDIR_SET27      :1 ;
    uint32_t             PnDIR_SET28      :1 ;
    uint32_t             PnDIR_SET29      :1 ;
    uint32_t             PnDIR_SET30      :1 ;
    uint32_t             PnDIR_SET31      :1 ;
}   GPIO_Pn_DIR_SET;

typedef union {
    uint32_t             w;
    GPIO_Pn_DIR_SET      b;
}   GPIO_Pn_DIR_SET_U;


// 0x40005408 register ------------------------------------
typedef struct {
    uint32_t             PnALT0_SET0      :1 ;
    uint32_t             PnALT0_SET1      :1 ;
    uint32_t             PnALT0_SET2      :1 ;
    uint32_t             PnALT0_SET3      :1 ;
    uint32_t             PnALT0_SET4      :1 ;
    uint32_t             PnALT0_SET5      :1 ;
    uint32_t             PnALT0_SET6      :1 ;
    uint32_t             PnALT0_SET7      :1 ;
    uint32_t             PnALT0_SET8      :1 ;
    uint32_t             PnALT0_SET9      :1 ;
    uint32_t             PnALT0_SET10     :1 ;
    uint32_t             PnALT0_SET11     :1 ;
    uint32_t             PnALT0_SET12     :1 ;
    uint32_t             PnALT0_SET13     :1 ;
    uint32_t             PnALT0_SET14     :1 ;
    uint32_t             PnALT0_SET15     :1 ;
    uint32_t             PnALT0_SET16     :1 ;
    uint32_t             PnALT0_SET17     :1 ;
    uint32_t             PnALT0_SET18     :1 ;
    uint32_t             PnALT0_SET19     :1 ;
    uint32_t             PnALT0_SET20     :1 ;
    uint32_t             PnALT0_SET21     :1 ;
    uint32_t             PnALT0_SET22     :1 ;
    uint32_t             PnALT0_SET23     :1 ;
    uint32_t             PnALT0_SET24     :1 ;
    uint32_t             PnALT0_SET25     :1 ;
    uint32_t             PnALT0_SET26     :1 ;
    uint32_t             PnALT0_SET27     :1 ;
    uint32_t             PnALT0_SET28     :1 ;
    uint32_t             PnALT0_SET29     :1 ;
    uint32_t             PnALT0_SET30     :1 ;
    uint32_t             PnALT0_SET31     :1 ;
}   GPIO_Pn_ALT0_SET;

typedef union {
    uint32_t             w;
    GPIO_Pn_ALT0_SET     b;
}   GPIO_Pn_ALT0_SET_U;


// 0x4000540C register ------------------------------------
typedef struct {
    uint32_t             PnALT1_SET0      :1 ;
    uint32_t             PnALT1_SET1      :1 ;
    uint32_t             PnALT1_SET2      :1 ;
    uint32_t             PnALT1_SET3      :1 ;
    uint32_t             PnALT1_SET4      :1 ;
    uint32_t             PnALT1_SET5      :1 ;
    uint32_t             PnALT1_SET6      :1 ;
    uint32_t             PnALT1_SET7      :1 ;
    uint32_t             PnALT1_SET8      :1 ;
    uint32_t             PnALT1_SET9      :1 ;
    uint32_t             PnALT1_SET10     :1 ;
    uint32_t             PnALT1_SET11     :1 ;
    uint32_t             PnALT1_SET12     :1 ;
    uint32_t             PnALT1_SET13     :1 ;
    uint32_t             PnALT1_SET14     :1 ;
    uint32_t             PnALT1_SET15     :1 ;
    uint32_t             PnALT1_SET16     :1 ;
    uint32_t             PnALT1_SET17     :1 ;
    uint32_t             PnALT1_SET18     :1 ;
    uint32_t             PnALT1_SET19     :1 ;
    uint32_t             PnALT1_SET20     :1 ;
    uint32_t             PnALT1_SET21     :1 ;
    uint32_t             PnALT1_SET22     :1 ;
    uint32_t             PnALT1_SET23     :1 ;
    uint32_t             PnALT1_SET24     :1 ;
    uint32_t             PnALT1_SET25     :1 ;
    uint32_t             PnALT1_SET26     :1 ;
    uint32_t             PnALT1_SET27     :1 ;
    uint32_t             PnALT1_SET28     :1 ;
    uint32_t             PnALT1_SET29     :1 ;
    uint32_t             PnALT1_SET30     :1 ;
    uint32_t             PnALT1_SET31     :1 ;
}   GPIO_Pn_ALT1_SET;

typedef union {
    uint32_t             w;
    GPIO_Pn_ALT1_SET     b;
}   GPIO_Pn_ALT1_SET_U;


// 0x40005410 register ------------------------------------
typedef struct {
    uint32_t             PnALT2_SET0      :1 ;
    uint32_t             PnALT2_SET1      :1 ;
    uint32_t             PnALT2_SET2      :1 ;
    uint32_t             PnALT2_SET3      :1 ;
    uint32_t             PnALT2_SET4      :1 ;
    uint32_t             PnALT2_SET5      :1 ;
    uint32_t             PnALT2_SET6      :1 ;
    uint32_t             PnALT2_SET7      :1 ;
    uint32_t             PnALT2_SET8      :1 ;
    uint32_t             PnALT2_SET9      :1 ;
    uint32_t             PnALT2_SET10     :1 ;
    uint32_t             PnALT2_SET11     :1 ;
    uint32_t             PnALT2_SET12     :1 ;
    uint32_t             PnALT2_SET13     :1 ;
    uint32_t             PnALT2_SET14     :1 ;
    uint32_t             PnALT2_SET15     :1 ;
    uint32_t             PnALT2_SET16     :1 ;
    uint32_t             PnALT2_SET17     :1 ;
    uint32_t             PnALT2_SET18     :1 ;
    uint32_t             PnALT2_SET19     :1 ;
    uint32_t             PnALT2_SET20     :1 ;
    uint32_t             PnALT2_SET21     :1 ;
    uint32_t             PnALT2_SET22     :1 ;
    uint32_t             PnALT2_SET23     :1 ;
    uint32_t             PnALT2_SET24     :1 ;
    uint32_t             PnALT2_SET25     :1 ;
    uint32_t             PnALT2_SET26     :1 ;
    uint32_t             PnALT2_SET27     :1 ;
    uint32_t             PnALT2_SET28     :1 ;
    uint32_t             PnALT2_SET29     :1 ;
    uint32_t             PnALT2_SET30     :1 ;
    uint32_t             PnALT2_SET31     :1 ;
}   GPIO_Pn_ALT2_SET;

typedef union {
    uint32_t             w;
    GPIO_Pn_ALT2_SET     b;
}   GPIO_Pn_ALT2_SET_U;


// 0x40005414 register ------------------------------------
typedef struct {
    uint32_t             PnALT3_SET0      :1 ;
    uint32_t             PnALT3_SET1      :1 ;
    uint32_t             PnALT3_SET2      :1 ;
    uint32_t             PnALT3_SET3      :1 ;
    uint32_t             PnALT3_SET4      :1 ;
    uint32_t             PnALT3_SET5      :1 ;
    uint32_t             PnALT3_SET6      :1 ;
    uint32_t             PnALT3_SET7      :1 ;
    uint32_t             PnALT3_SET8      :1 ;
    uint32_t             PnALT3_SET9      :1 ;
    uint32_t             PnALT3_SET10     :1 ;
    uint32_t             PnALT3_SET11     :1 ;
    uint32_t             PnALT3_SET12     :1 ;
    uint32_t             PnALT3_SET13     :1 ;
    uint32_t             PnALT3_SET14     :1 ;
    uint32_t             PnALT3_SET15     :1 ;
    uint32_t             PnALT3_SET16     :1 ;
    uint32_t             PnALT3_SET17     :1 ;
    uint32_t             PnALT3_SET18     :1 ;
    uint32_t             PnALT3_SET19     :1 ;
    uint32_t             PnALT3_SET20     :1 ;
    uint32_t             PnALT3_SET21     :1 ;
    uint32_t             PnALT3_SET22     :1 ;
    uint32_t             PnALT3_SET23     :1 ;
    uint32_t             PnALT3_SET24     :1 ;
    uint32_t             PnALT3_SET25     :1 ;
    uint32_t             PnALT3_SET26     :1 ;
    uint32_t             PnALT3_SET27     :1 ;
    uint32_t             PnALT3_SET28     :1 ;
    uint32_t             PnALT3_SET29     :1 ;
    uint32_t             PnALT3_SET30     :1 ;
    uint32_t             PnALT3_SET31     :1 ;
}   GPIO_Pn_ALT3_SET;

typedef union {
    uint32_t             w;
    GPIO_Pn_ALT3_SET     b;
}   GPIO_Pn_ALT3_SET_U;


// 0x40005418 register ------------------------------------
typedef struct {
    uint32_t             PnALT4_SET0      :1 ;
    uint32_t             PnALT4_SET1      :1 ;
    uint32_t             PnALT4_SET2      :1 ;
    uint32_t             PnALT4_SET3      :1 ;
    uint32_t             PnALT4_SET4      :1 ;
    uint32_t             PnALT4_SET5      :1 ;
    uint32_t             PnALT4_SET6      :1 ;
    uint32_t             PnALT4_SET7      :1 ;
    uint32_t             PnALT4_SET8      :1 ;
    uint32_t             PnALT4_SET9      :1 ;
    uint32_t             PnALT4_SET10     :1 ;
    uint32_t             PnALT4_SET11     :1 ;
    uint32_t             PnALT4_SET12     :1 ;
    uint32_t             PnALT4_SET13     :1 ;
    uint32_t             PnALT4_SET14     :1 ;
    uint32_t             PnALT4_SET15     :1 ;
    uint32_t             PnALT4_SET16     :1 ;
    uint32_t             PnALT4_SET17     :1 ;
    uint32_t             PnALT4_SET18     :1 ;
    uint32_t             PnALT4_SET19     :1 ;
    uint32_t             PnALT4_SET20     :1 ;
    uint32_t             PnALT4_SET21     :1 ;
    uint32_t             PnALT4_SET22     :1 ;
    uint32_t             PnALT4_SET23     :1 ;
    uint32_t             PnALT4_SET24     :1 ;
    uint32_t             PnALT4_SET25     :1 ;
    uint32_t             PnALT4_SET26     :1 ;
    uint32_t             PnALT4_SET27     :1 ;
    uint32_t             PnALT4_SET28     :1 ;
    uint32_t             PnALT4_SET29     :1 ;
    uint32_t             PnALT4_SET30     :1 ;
    uint32_t             PnALT4_SET31     :1 ;
}   GPIO_Pn_ALT4_SET;

typedef union {
    uint32_t             w;
    GPIO_Pn_ALT4_SET     b;
}   GPIO_Pn_ALT4_SET_U;


// 0x40005430 register ------------------------------------
typedef struct {
    uint32_t             PnPU_SET0        :1 ;
    uint32_t             PnPU_SET1        :1 ;
    uint32_t             PnPU_SET2        :1 ;
    uint32_t             PnPU_SET3        :1 ;
    uint32_t             PnPU_SET4        :1 ;
    uint32_t             PnPU_SET5        :1 ;
    uint32_t             PnPU_SET6        :1 ;
    uint32_t             PnPU_SET7        :1 ;
    uint32_t             PnPU_SET8        :1 ;
    uint32_t             PnPU_SET9        :1 ;
    uint32_t             PnPU_SET10       :1 ;
    uint32_t             PnPU_SET11       :1 ;
    uint32_t             PnPU_SET12       :1 ;
    uint32_t             PnPU_SET13       :1 ;
    uint32_t             PnPU_SET14       :1 ;
    uint32_t             PnPU_SET15       :1 ;
    uint32_t             PnPU_SET16       :1 ;
    uint32_t             PnPU_SET17       :1 ;
    uint32_t             PnPU_SET18       :1 ;
    uint32_t             PnPU_SET19       :1 ;
    uint32_t             PnPU_SET20       :1 ;
    uint32_t             PnPU_SET21       :1 ;
    uint32_t             PnPU_SET22       :1 ;
    uint32_t             PnPU_SET23       :1 ;
    uint32_t             PnPU_SET24       :1 ;
    uint32_t             PnPU_SET25       :1 ;
    uint32_t             PnPU_SET26       :1 ;
    uint32_t             PnPU_SET27       :1 ;
    uint32_t             PnPU_SET28       :1 ;
    uint32_t             PnPU_SET29       :1 ;
    uint32_t             PnPU_SET30       :1 ;
    uint32_t             PnPU_SET31       :1 ;
}   GPIO_Pn_PU_SET;

typedef union {
    uint32_t             w;
    GPIO_Pn_PU_SET       b;
}   GPIO_Pn_PU_SET_U;


// 0x40005438 register ------------------------------------
typedef struct {
    uint32_t             PnDRV0_SET       :16;
    uint32_t             reserved0        :16;
}   GPIO_Pn_DRV0_SET;

typedef union {
    uint32_t             w;
    GPIO_Pn_DRV0_SET     b;
}   GPIO_Pn_DRV0_SET_U;


// 0x4000543C register ------------------------------------
typedef struct {
    uint32_t             PnDRV1_SET       :16;
    uint32_t             reserved0        :16;
}   GPIO_Pn_DRV1_SET;

typedef union {
    uint32_t             w;
    GPIO_Pn_DRV1_SET     b;
}   GPIO_Pn_DRV1_SET_U;


// 0x40005600 register ------------------------------------
typedef struct {
    uint32_t             PnOUT_TGL0       :1 ;
    uint32_t             PnOUT_TGL1       :1 ;
    uint32_t             PnOUT_TGL2       :1 ;
    uint32_t             PnOUT_TGL3       :1 ;
    uint32_t             PnOUT_TGL4       :1 ;
    uint32_t             PnOUT_TGL5       :1 ;
    uint32_t             PnOUT_TGL6       :1 ;
    uint32_t             PnOUT_TGL7       :1 ;
    uint32_t             PnOUT_TGL8       :1 ;
    uint32_t             PnOUT_TGL9       :1 ;
    uint32_t             PnOUT_TGL10      :1 ;
    uint32_t             PnOUT_TGL11      :1 ;
    uint32_t             PnOUT_TGL12      :1 ;
    uint32_t             PnOUT_TGL13      :1 ;
    uint32_t             PnOUT_TGL14      :1 ;
    uint32_t             PnOUT_TGL15      :1 ;
    uint32_t             PnOUT_TGL16      :1 ;
    uint32_t             PnOUT_TGL17      :1 ;
    uint32_t             PnOUT_TGL18      :1 ;
    uint32_t             PnOUT_TGL19      :1 ;
    uint32_t             PnOUT_TGL20      :1 ;
    uint32_t             PnOUT_TGL21      :1 ;
    uint32_t             PnOUT_TGL22      :1 ;
    uint32_t             PnOUT_TGL23      :1 ;
    uint32_t             PnOUT_TGL24      :1 ;
    uint32_t             PnOUT_TGL25      :1 ;
    uint32_t             PnOUT_TGL26      :1 ;
    uint32_t             PnOUT_TGL27      :1 ;
    uint32_t             PnOUT_TGL28      :1 ;
    uint32_t             PnOUT_TGL29      :1 ;
    uint32_t             PnOUT_TGL30      :1 ;
    uint32_t             PnOUT_TGL31      :1 ;
}   GPIO_Pn_DATA_TGL;

typedef union {
    uint32_t             w;
    GPIO_Pn_DATA_TGL     b;
}   GPIO_Pn_DATA_TGL_U;


// 0x40005604 register ------------------------------------
typedef struct {
    uint32_t             PnDIR_TGL0       :1 ;
    uint32_t             PnDIR_TGL1       :1 ;
    uint32_t             PnDIR_TGL2       :1 ;
    uint32_t             PnDIR_TGL3       :1 ;
    uint32_t             PnDIR_TGL4       :1 ;
    uint32_t             PnDIR_TGL5       :1 ;
    uint32_t             PnDIR_TGL6       :1 ;
    uint32_t             PnDIR_TGL7       :1 ;
    uint32_t             PnDIR_TGL8       :1 ;
    uint32_t             PnDIR_TGL9       :1 ;
    uint32_t             PnDIR_TGL10      :1 ;
    uint32_t             PnDIR_TGL11      :1 ;
    uint32_t             PnDIR_TGL12      :1 ;
    uint32_t             PnDIR_TGL13      :1 ;
    uint32_t             PnDIR_TGL14      :1 ;
    uint32_t             PnDIR_TGL15      :1 ;
    uint32_t             PnDIR_TGL16      :1 ;
    uint32_t             PnDIR_TGL17      :1 ;
    uint32_t             PnDIR_TGL18      :1 ;
    uint32_t             PnDIR_TGL19      :1 ;
    uint32_t             PnDIR_TGL20      :1 ;
    uint32_t             PnDIR_TGL21      :1 ;
    uint32_t             PnDIR_TGL22      :1 ;
    uint32_t             PnDIR_TGL23      :1 ;
    uint32_t             PnDIR_TGL24      :1 ;
    uint32_t             PnDIR_TGL25      :1 ;
    uint32_t             PnDIR_TGL26      :1 ;
    uint32_t             PnDIR_TGL27      :1 ;
    uint32_t             PnDIR_TGL28      :1 ;
    uint32_t             PnDIR_TGL29      :1 ;
    uint32_t             PnDIR_TGL30      :1 ;
    uint32_t             PnDIR_TGL31      :1 ;
}   GPIO_Pn_DIR_TGL;

typedef union {
    uint32_t             w;
    GPIO_Pn_DIR_TGL      b;
}   GPIO_Pn_DIR_TGL_U;


// 0x40005608 register ------------------------------------
typedef struct {
    uint32_t             PnALT0_TGL0      :1 ;
    uint32_t             PnALT0_TGL1      :1 ;
    uint32_t             PnALT0_TGL2      :1 ;
    uint32_t             PnALT0_TGL3      :1 ;
    uint32_t             PnALT0_TGL4      :1 ;
    uint32_t             PnALT0_TGL5      :1 ;
    uint32_t             PnALT0_TGL6      :1 ;
    uint32_t             PnALT0_TGL7      :1 ;
    uint32_t             PnALT0_TGL8      :1 ;
    uint32_t             PnALT0_TGL9      :1 ;
    uint32_t             PnALT0_TGL10     :1 ;
    uint32_t             PnALT0_TGL11     :1 ;
    uint32_t             PnALT0_TGL12     :1 ;
    uint32_t             PnALT0_TGL13     :1 ;
    uint32_t             PnALT0_TGL14     :1 ;
    uint32_t             PnALT0_TGL15     :1 ;
    uint32_t             PnALT0_TGL16     :1 ;
    uint32_t             PnALT0_TGL17     :1 ;
    uint32_t             PnALT0_TGL18     :1 ;
    uint32_t             PnALT0_TGL19     :1 ;
    uint32_t             PnALT0_TGL20     :1 ;
    uint32_t             PnALT0_TGL21     :1 ;
    uint32_t             PnALT0_TGL22     :1 ;
    uint32_t             PnALT0_TGL23     :1 ;
    uint32_t             PnALT0_TGL24     :1 ;
    uint32_t             PnALT0_TGL25     :1 ;
    uint32_t             PnALT0_TGL26     :1 ;
    uint32_t             PnALT0_TGL27     :1 ;
    uint32_t             PnALT0_TGL28     :1 ;
    uint32_t             PnALT0_TGL29     :1 ;
    uint32_t             PnALT0_TGL30     :1 ;
    uint32_t             PnALT0_TGL31     :1 ;
}   GPIO_Pn_ALT0_TGL;

typedef union {
    uint32_t             w;
    GPIO_Pn_ALT0_TGL     b;
}   GPIO_Pn_ALT0_TGL_U;


// 0x4000560C register ------------------------------------
typedef struct {
    uint32_t             PnALT1_TGL0      :1 ;
    uint32_t             PnALT1_TGL1      :1 ;
    uint32_t             PnALT1_TGL2      :1 ;
    uint32_t             PnALT1_TGL3      :1 ;
    uint32_t             PnALT1_TGL4      :1 ;
    uint32_t             PnALT1_TGL5      :1 ;
    uint32_t             PnALT1_TGL6      :1 ;
    uint32_t             PnALT1_TGL7      :1 ;
    uint32_t             PnALT1_TGL8      :1 ;
    uint32_t             PnALT1_TGL9      :1 ;
    uint32_t             PnALT1_TGL10     :1 ;
    uint32_t             PnALT1_TGL11     :1 ;
    uint32_t             PnALT1_TGL12     :1 ;
    uint32_t             PnALT1_TGL13     :1 ;
    uint32_t             PnALT1_TGL14     :1 ;
    uint32_t             PnALT1_TGL15     :1 ;
    uint32_t             PnALT1_TGL16     :1 ;
    uint32_t             PnALT1_TGL17     :1 ;
    uint32_t             PnALT1_TGL18     :1 ;
    uint32_t             PnALT1_TGL19     :1 ;
    uint32_t             PnALT1_TGL20     :1 ;
    uint32_t             PnALT1_TGL21     :1 ;
    uint32_t             PnALT1_TGL22     :1 ;
    uint32_t             PnALT1_TGL23     :1 ;
    uint32_t             PnALT1_TGL24     :1 ;
    uint32_t             PnALT1_TGL25     :1 ;
    uint32_t             PnALT1_TGL26     :1 ;
    uint32_t             PnALT1_TGL27     :1 ;
    uint32_t             PnALT1_TGL28     :1 ;
    uint32_t             PnALT1_TGL29     :1 ;
    uint32_t             PnALT1_TGL30     :1 ;
    uint32_t             PnALT1_TGL31     :1 ;
}   GPIO_Pn_ALT1_TGL;

typedef union {
    uint32_t             w;
    GPIO_Pn_ALT1_TGL     b;
}   GPIO_Pn_ALT1_TGL_U;


// 0x40005610 register ------------------------------------
typedef struct {
    uint32_t             PnALT2_TGL0      :1 ;
    uint32_t             PnALT2_TGL1      :1 ;
    uint32_t             PnALT2_TGL2      :1 ;
    uint32_t             PnALT2_TGL3      :1 ;
    uint32_t             PnALT2_TGL4      :1 ;
    uint32_t             PnALT2_TGL5      :1 ;
    uint32_t             PnALT2_TGL6      :1 ;
    uint32_t             PnALT2_TGL7      :1 ;
    uint32_t             PnALT2_TGL8      :1 ;
    uint32_t             PnALT2_TGL9      :1 ;
    uint32_t             PnALT2_TGL10     :1 ;
    uint32_t             PnALT2_TGL11     :1 ;
    uint32_t             PnALT2_TGL12     :1 ;
    uint32_t             PnALT2_TGL13     :1 ;
    uint32_t             PnALT2_TGL14     :1 ;
    uint32_t             PnALT2_TGL15     :1 ;
    uint32_t             PnALT2_TGL16     :1 ;
    uint32_t             PnALT2_TGL17     :1 ;
    uint32_t             PnALT2_TGL18     :1 ;
    uint32_t             PnALT2_TGL19     :1 ;
    uint32_t             PnALT2_TGL20     :1 ;
    uint32_t             PnALT2_TGL21     :1 ;
    uint32_t             PnALT2_TGL22     :1 ;
    uint32_t             PnALT2_TGL23     :1 ;
    uint32_t             PnALT2_TGL24     :1 ;
    uint32_t             PnALT2_TGL25     :1 ;
    uint32_t             PnALT2_TGL26     :1 ;
    uint32_t             PnALT2_TGL27     :1 ;
    uint32_t             PnALT2_TGL28     :1 ;
    uint32_t             PnALT2_TGL29     :1 ;
    uint32_t             PnALT2_TGL30     :1 ;
    uint32_t             PnALT2_TGL31     :1 ;
}   GPIO_Pn_ALT2_TGL;

typedef union {
    uint32_t             w;
    GPIO_Pn_ALT2_TGL     b;
}   GPIO_Pn_ALT2_TGL_U;


// 0x40005614 register ------------------------------------
typedef struct {
    uint32_t             PnALT3_TGL0      :1 ;
    uint32_t             PnALT3_TGL1      :1 ;
    uint32_t             PnALT3_TGL2      :1 ;
    uint32_t             PnALT3_TGL3      :1 ;
    uint32_t             PnALT3_TGL4      :1 ;
    uint32_t             PnALT3_TGL5      :1 ;
    uint32_t             PnALT3_TGL6      :1 ;
    uint32_t             PnALT3_TGL7      :1 ;
    uint32_t             PnALT3_TGL8      :1 ;
    uint32_t             PnALT3_TGL9      :1 ;
    uint32_t             PnALT3_TGL10     :1 ;
    uint32_t             PnALT3_TGL11     :1 ;
    uint32_t             PnALT3_TGL12     :1 ;
    uint32_t             PnALT3_TGL13     :1 ;
    uint32_t             PnALT3_TGL14     :1 ;
    uint32_t             PnALT3_TGL15     :1 ;
    uint32_t             PnALT3_TGL16     :1 ;
    uint32_t             PnALT3_TGL17     :1 ;
    uint32_t             PnALT3_TGL18     :1 ;
    uint32_t             PnALT3_TGL19     :1 ;
    uint32_t             PnALT3_TGL20     :1 ;
    uint32_t             PnALT3_TGL21     :1 ;
    uint32_t             PnALT3_TGL22     :1 ;
    uint32_t             PnALT3_TGL23     :1 ;
    uint32_t             PnALT3_TGL24     :1 ;
    uint32_t             PnALT3_TGL25     :1 ;
    uint32_t             PnALT3_TGL26     :1 ;
    uint32_t             PnALT3_TGL27     :1 ;
    uint32_t             PnALT3_TGL28     :1 ;
    uint32_t             PnALT3_TGL29     :1 ;
    uint32_t             PnALT3_TGL30     :1 ;
    uint32_t             PnALT3_TGL31     :1 ;
}   GPIO_Pn_ALT3_TGL;

typedef union {
    uint32_t             w;
    GPIO_Pn_ALT3_TGL     b;
}   GPIO_Pn_ALT3_TGL_U;


// 0x40005618 register ------------------------------------
typedef struct {
    uint32_t             PnALT4_TGL0      :1 ;
    uint32_t             PnALT4_TGL1      :1 ;
    uint32_t             PnALT4_TGL2      :1 ;
    uint32_t             PnALT4_TGL3      :1 ;
    uint32_t             PnALT4_TGL4      :1 ;
    uint32_t             PnALT4_TGL5      :1 ;
    uint32_t             PnALT4_TGL6      :1 ;
    uint32_t             PnALT4_TGL7      :1 ;
    uint32_t             PnALT4_TGL8      :1 ;
    uint32_t             PnALT4_TGL9      :1 ;
    uint32_t             PnALT4_TGL10     :1 ;
    uint32_t             PnALT4_TGL11     :1 ;
    uint32_t             PnALT4_TGL12     :1 ;
    uint32_t             PnALT4_TGL13     :1 ;
    uint32_t             PnALT4_TGL14     :1 ;
    uint32_t             PnALT4_TGL15     :1 ;
    uint32_t             PnALT4_TGL16     :1 ;
    uint32_t             PnALT4_TGL17     :1 ;
    uint32_t             PnALT4_TGL18     :1 ;
    uint32_t             PnALT4_TGL19     :1 ;
    uint32_t             PnALT4_TGL20     :1 ;
    uint32_t             PnALT4_TGL21     :1 ;
    uint32_t             PnALT4_TGL22     :1 ;
    uint32_t             PnALT4_TGL23     :1 ;
    uint32_t             PnALT4_TGL24     :1 ;
    uint32_t             PnALT4_TGL25     :1 ;
    uint32_t             PnALT4_TGL26     :1 ;
    uint32_t             PnALT4_TGL27     :1 ;
    uint32_t             PnALT4_TGL28     :1 ;
    uint32_t             PnALT4_TGL29     :1 ;
    uint32_t             PnALT4_TGL30     :1 ;
    uint32_t             PnALT4_TGL31     :1 ;
}   GPIO_Pn_ALT4_TGL;

typedef union {
    uint32_t             w;
    GPIO_Pn_ALT4_TGL     b;
}   GPIO_Pn_ALT4_TGL_U;


// 0x40005630 register ------------------------------------
typedef struct {
    uint32_t             PnPU_TGL0        :1 ;
    uint32_t             PnPU_TGL1        :1 ;
    uint32_t             PnPU_TGL2        :1 ;
    uint32_t             PnPU_TGL3        :1 ;
    uint32_t             PnPU_TGL4        :1 ;
    uint32_t             PnPU_TGL5        :1 ;
    uint32_t             PnPU_TGL6        :1 ;
    uint32_t             PnPU_TGL7        :1 ;
    uint32_t             PnPU_TGL8        :1 ;
    uint32_t             PnPU_TGL9        :1 ;
    uint32_t             PnPU_TGL10       :1 ;
    uint32_t             PnPU_TGL11       :1 ;
    uint32_t             PnPU_TGL12       :1 ;
    uint32_t             PnPU_TGL13       :1 ;
    uint32_t             PnPU_TGL14       :1 ;
    uint32_t             PnPU_TGL15       :1 ;
    uint32_t             PnPU_TGL16       :1 ;
    uint32_t             PnPU_TGL17       :1 ;
    uint32_t             PnPU_TGL18       :1 ;
    uint32_t             PnPU_TGL19       :1 ;
    uint32_t             PnPU_TGL20       :1 ;
    uint32_t             PnPU_TGL21       :1 ;
    uint32_t             PnPU_TGL22       :1 ;
    uint32_t             PnPU_TGL23       :1 ;
    uint32_t             PnPU_TGL24       :1 ;
    uint32_t             PnPU_TGL25       :1 ;
    uint32_t             PnPU_TGL26       :1 ;
    uint32_t             PnPU_TGL27       :1 ;
    uint32_t             PnPU_TGL28       :1 ;
    uint32_t             PnPU_TGL29       :1 ;
    uint32_t             PnPU_TGL30       :1 ;
    uint32_t             PnPU_TGL31       :1 ;
}   GPIO_Pn_PU_TGL;

typedef union {
    uint32_t             w;
    GPIO_Pn_PU_TGL       b;
}   GPIO_Pn_PU_TGL_U;


// 0x40005638 register ------------------------------------
typedef struct {
    uint32_t             PnDRV0_TGL       :16;
    uint32_t             reserved0        :16;
}   GPIO_Pn_DRV0_TGL;

typedef union {
    uint32_t             w;
    GPIO_Pn_DRV0_TGL     b;
}   GPIO_Pn_DRV0_TGL_U;


// 0x4000563C register ------------------------------------
typedef struct {
    uint32_t             PnDRV1_TGL       :16;
    uint32_t             reserved0        :16;
}   GPIO_Pn_DRV1_TGL;

typedef union {
    uint32_t             w;
    GPIO_Pn_DRV1_TGL     b;
}   GPIO_Pn_DRV1_TGL_U;


// 0x40005800 register ------------------------------------
typedef struct {
    uint32_t             I2C0_SCL         :8 ;
    uint32_t             I2C0_SDA         :8 ;
    uint32_t             I2C1_SCL         :8 ;
    uint32_t             I2C1_SDA         :8 ;
}   GPIO_UIO_SEL00;

typedef union {
    uint32_t             w;
    GPIO_UIO_SEL00       b;
}   GPIO_UIO_SEL00_U;


// 0x4000580C register ------------------------------------
typedef struct {
    uint32_t             LNA_EN           :8 ;
    uint32_t             PA_EN            :8 ;
    uint32_t             ANTSEL           :8 ;
    uint32_t             reserved0        :8 ;
}   GPIO_UIO_SEL03;

typedef union {
    uint32_t             w;
    GPIO_UIO_SEL03       b;
}   GPIO_UIO_SEL03_U;


// 0x40005810 register ------------------------------------
typedef struct {
    uint32_t             SPI00_CLK        :8 ;
    uint32_t             SPI00_FSS        :8 ;
    uint32_t             SPI00_TXD        :8 ;
    uint32_t             SPI00_RXD        :8 ;
}   GPIO_UIO_SEL04;

typedef union {
    uint32_t             w;
    GPIO_UIO_SEL04       b;
}   GPIO_UIO_SEL04_U;


// 0x40005814 register ------------------------------------
typedef struct {
    uint32_t             SPI01_CLK        :8 ;
    uint32_t             SPI01_FSS        :8 ;
    uint32_t             SPI01_TXD        :8 ;
    uint32_t             SPI01_RXD        :8 ;
}   GPIO_UIO_SEL05;

typedef union {
    uint32_t             w;
    GPIO_UIO_SEL05       b;
}   GPIO_UIO_SEL05_U;


// 0x40005818 register ------------------------------------
typedef struct {
    uint32_t             HSPI_CLK         :8 ;
    uint32_t             HSPI_FRM         :8 ;
    uint32_t             HSPI_MISO        :8 ;
    uint32_t             HSPI_MOSI        :8 ;
}   GPIO_UIO_SEL06;

typedef union {
    uint32_t             w;
    GPIO_UIO_SEL06       b;
}   GPIO_UIO_SEL06_U;


// 0x4000581C register ------------------------------------
typedef struct {
    uint32_t             HSPI_EIRQ        :8 ;
    uint32_t             reserved0        :24;
}   GPIO_UIO_SEL07;

typedef union {
    uint32_t             w;
    GPIO_UIO_SEL07       b;
}   GPIO_UIO_SEL07_U;


// 0x40005820 register ------------------------------------
typedef struct {
    uint32_t             UART00_TXD       :8 ;
    uint32_t             UART00_RXD       :8 ;
    uint32_t             UART00_RTS       :8 ;
    uint32_t             UART00_CTS       :8 ;
}   GPIO_UIO_SEL08;

typedef union {
    uint32_t             w;
    GPIO_UIO_SEL08       b;
}   GPIO_UIO_SEL08_U;


// 0x40005824 register ------------------------------------
typedef struct {
    uint32_t             UART01_TXD       :8 ;
    uint32_t             UART01_RXD       :8 ;
    uint32_t             UART01_RTS       :8 ;
    uint32_t             UART01_CTS       :8 ;
}   GPIO_UIO_SEL09;

typedef union {
    uint32_t             w;
    GPIO_UIO_SEL09       b;
}   GPIO_UIO_SEL09_U;


// 0x40005830 register ------------------------------------
typedef struct {
    uint32_t             PWM_A            :8 ;
    uint32_t             PWM_B            :8 ;
    uint32_t             PWM_C            :8 ;
    uint32_t             PWM_D            :8 ;
}   GPIO_UIO_SEL12;

typedef union {
    uint32_t             w;
    GPIO_UIO_SEL12       b;
}   GPIO_UIO_SEL12_U;


// 0x40005838 register ------------------------------------
typedef struct {
    uint32_t             EINT00           :8 ;
    uint32_t             EINT01           :8 ;
    uint32_t             EINT02           :8 ;
    uint32_t             EINT03           :8 ;
}   GPIO_UIO_SEL14;

typedef union {
    uint32_t             w;
    GPIO_UIO_SEL14       b;
}   GPIO_UIO_SEL14_U;


// 0x4000583C register ------------------------------------
typedef struct {
    uint32_t             NRC_SMC_DATA     :8 ;
    uint32_t             NRC_SMC_CLK      :8 ;
    uint32_t             NRC_SCM_RESET    :8 ;
    uint32_t             NRC_SMC_VCC      :8 ;
}   GPIO_UIO_SEL15;

typedef union {
    uint32_t             w;
    GPIO_UIO_SEL15       b;
}   GPIO_UIO_SEL15_U;


// 0x40005840 register ------------------------------------
typedef struct {
    uint32_t             EN               :1 ;
    uint32_t             POL              :1 ;
    uint32_t             SEL              :1 ;
    uint32_t             DBEN             :1 ;
    uint32_t             reserved0        :28;
}   GPIO_EINT00CTL;

typedef union {
    uint32_t             w;
    GPIO_EINT00CTL       b;
}   GPIO_EINT00CTL_U;


// 0x40005844 register ------------------------------------
typedef struct {
    uint32_t             EINTF            :1 ;
    uint32_t             reserved0        :31;
}   GPIO_EINT00STAT;

typedef union {
    uint32_t             w;
    GPIO_EINT00STAT      b;
}   GPIO_EINT00STAT_U;


// 0x40005848 register ------------------------------------
typedef struct {
    uint32_t             EN               :1 ;
    uint32_t             POL              :1 ;
    uint32_t             SEL              :1 ;
    uint32_t             DBEN             :1 ;
    uint32_t             reserved0        :28;
}   GPIO_EINT01CTL;

typedef union {
    uint32_t             w;
    GPIO_EINT01CTL       b;
}   GPIO_EINT01CTL_U;


// 0x4000584C register ------------------------------------
typedef struct {
    uint32_t             EINTF            :1 ;
    uint32_t             reserved0        :31;
}   GPIO_EINT01STAT;

typedef union {
    uint32_t             w;
    GPIO_EINT01STAT      b;
}   GPIO_EINT01STAT_U;


// 0x40005850 register ------------------------------------
typedef struct {
    uint32_t             EN               :1 ;
    uint32_t             POL              :1 ;
    uint32_t             SEL              :1 ;
    uint32_t             DBEN             :1 ;
    uint32_t             reserved0        :28;
}   GPIO_EINT02CTL;

typedef union {
    uint32_t             w;
    GPIO_EINT02CTL       b;
}   GPIO_EINT02CTL_U;


// 0x40005854 register ------------------------------------
typedef struct {
    uint32_t             EINTF            :1 ;
    uint32_t             reserved0        :31;
}   GPIO_EINT02STAT;

typedef union {
    uint32_t             w;
    GPIO_EINT02STAT      b;
}   GPIO_EINT02STAT_U;


// 0x40005858 register ------------------------------------
typedef struct {
    uint32_t             EN               :1 ;
    uint32_t             POL              :1 ;
    uint32_t             SEL              :1 ;
    uint32_t             DBEN             :1 ;
    uint32_t             reserved0        :28;
}   GPIO_EINT03CTL;

typedef union {
    uint32_t             w;
    GPIO_EINT03CTL       b;
}   GPIO_EINT03CTL_U;


// 0x4000585C register ------------------------------------
typedef struct {
    uint32_t             EINTF            :1 ;
    uint32_t             reserved0        :31;
}   GPIO_EINT03STAT;

typedef union {
    uint32_t             w;
    GPIO_EINT03STAT      b;
}   GPIO_EINT03STAT_U;


//---------------------------------------------------------
// GPIO Register Map
//---------------------------------------------------------
typedef struct {
    volatile GPIO_Pn_DATA_U              Pn_DATA            ; // 0x000
    volatile GPIO_Pn_DIR_U               Pn_DIR             ; // 0x004
    volatile GPIO_Pn_ALT0_U              Pn_ALT0            ; // 0x008
    volatile GPIO_Pn_ALT1_U              Pn_ALT1            ; // 0x00c
    volatile GPIO_Pn_ALT2_U              Pn_ALT2            ; // 0x010
    volatile GPIO_Pn_ALT3_U              Pn_ALT3            ; // 0x014
    volatile GPIO_Pn_ALT4_U              Pn_ALT4            ; // 0x018
    volatile uint32_t                      RESERVED0[5]       ; // 
    volatile GPIO_Pn_PULLUP_U            Pn_PULLUP          ; // 0x030
    volatile uint32_t                      RESERVED1          ; // 
    volatile GPIO_Pn_DRV0_U              Pn_DRV0            ; // 0x038
    volatile GPIO_Pn_DRV1_U              Pn_DRV1            ; // 0x03c
    volatile uint32_t                      RESERVED2[112]     ; // 
    volatile GPIO_Pn_DATA_CLR_U          Pn_DATA_CLR        ; // 0x200
    volatile GPIO_Pn_DIR_CLR_U           Pn_DIR_CLR         ; // 0x204
    volatile GPIO_Pn_ALT0_CLR_U          Pn_ALT0_CLR        ; // 0x208
    volatile GPIO_Pn_ALT1_CLR_U          Pn_ALT1_CLR        ; // 0x20c
    volatile GPIO_Pn_ALT2_CLR_U          Pn_ALT2_CLR        ; // 0x210
    volatile GPIO_Pn_ALT3_CLR_U          Pn_ALT3_CLR        ; // 0x214
    volatile GPIO_Pn_ALT4_CLR_U          Pn_ALT4_CLR        ; // 0x218
    volatile uint32_t                      RESERVED3[5]       ; // 
    volatile GPIO_Pn_PU_CLR_U            Pn_PU_CLR          ; // 0x230
    volatile uint32_t                      RESERVED4          ; // 
    volatile GPIO_Pn_DRV0_CLR_U          Pn_DRV0_CLR        ; // 0x238
    volatile GPIO_Pn_DRV1_CLR_U          Pn_DRV1_CLR        ; // 0x23c
    volatile uint32_t                      RESERVED5[112]     ; // 
    volatile GPIO_Pn_DATA_SET_U          Pn_DATA_SET        ; // 0x400
    volatile GPIO_Pn_DIR_SET_U           Pn_DIR_SET         ; // 0x404
    volatile GPIO_Pn_ALT0_SET_U          Pn_ALT0_SET        ; // 0x408
    volatile GPIO_Pn_ALT1_SET_U          Pn_ALT1_SET        ; // 0x40c
    volatile GPIO_Pn_ALT2_SET_U          Pn_ALT2_SET        ; // 0x410
    volatile GPIO_Pn_ALT3_SET_U          Pn_ALT3_SET        ; // 0x414
    volatile GPIO_Pn_ALT4_SET_U          Pn_ALT4_SET        ; // 0x418
    volatile uint32_t                      RESERVED6[5]       ; // 
    volatile GPIO_Pn_PU_SET_U            Pn_PU_SET          ; // 0x430
    volatile uint32_t                      RESERVED7          ; // 
    volatile GPIO_Pn_DRV0_SET_U          Pn_DRV0_SET        ; // 0x438
    volatile GPIO_Pn_DRV1_SET_U          Pn_DRV1_SET        ; // 0x43c
    volatile uint32_t                      RESERVED8[112]     ; // 
    volatile GPIO_Pn_DATA_TGL_U          Pn_DATA_TGL        ; // 0x600
    volatile GPIO_Pn_DIR_TGL_U           Pn_DIR_TGL         ; // 0x604
    volatile GPIO_Pn_ALT0_TGL_U          Pn_ALT0_TGL        ; // 0x608
    volatile GPIO_Pn_ALT1_TGL_U          Pn_ALT1_TGL        ; // 0x60c
    volatile GPIO_Pn_ALT2_TGL_U          Pn_ALT2_TGL        ; // 0x610
    volatile GPIO_Pn_ALT3_TGL_U          Pn_ALT3_TGL        ; // 0x614
    volatile GPIO_Pn_ALT4_TGL_U          Pn_ALT4_TGL        ; // 0x618
    volatile uint32_t                      RESERVED9[5]       ; // 
    volatile GPIO_Pn_PU_TGL_U            Pn_PU_TGL          ; // 0x630
    volatile uint32_t                      RESERVED10         ; // 
    volatile GPIO_Pn_DRV0_TGL_U          Pn_DRV0_TGL        ; // 0x638
    volatile GPIO_Pn_DRV1_TGL_U          Pn_DRV1_TGL        ; // 0x63c
    volatile uint32_t                      RESERVED11[112]    ; // 
    volatile GPIO_UIO_SEL00_U            UIO_SEL00          ; // 0x800
    volatile uint32_t                      RESERVED12[2]      ; // 
    volatile GPIO_UIO_SEL03_U            UIO_SEL03          ; // 0x80c
    volatile GPIO_UIO_SEL04_U            UIO_SEL04          ; // 0x810
    volatile GPIO_UIO_SEL05_U            UIO_SEL05          ; // 0x814
    volatile GPIO_UIO_SEL06_U            UIO_SEL06          ; // 0x818
    volatile GPIO_UIO_SEL07_U            UIO_SEL07          ; // 0x81c
    volatile GPIO_UIO_SEL08_U            UIO_SEL08          ; // 0x820
    volatile GPIO_UIO_SEL09_U            UIO_SEL09          ; // 0x824
    volatile uint32_t                      RESERVED13[2]      ; // 
    volatile GPIO_UIO_SEL12_U            UIO_SEL12          ; // 0x830
    volatile uint32_t                      RESERVED14         ; // 
    volatile GPIO_UIO_SEL14_U            UIO_SEL14          ; // 0x838
    volatile GPIO_UIO_SEL15_U            UIO_SEL15          ; // 0x83c
    volatile GPIO_EINT00CTL_U            EINT00CTL          ; // 0x840
    volatile GPIO_EINT00STAT_U           EINT00STAT         ; // 0x844
    volatile GPIO_EINT01CTL_U            EINT01CTL          ; // 0x848
    volatile GPIO_EINT01STAT_U           EINT01STAT         ; // 0x84c
    volatile GPIO_EINT02CTL_U            EINT02CTL          ; // 0x850
    volatile GPIO_EINT02STAT_U           EINT02STAT         ; // 0x854
    volatile GPIO_EINT03CTL_U            EINT03CTL          ; // 0x858
    volatile GPIO_EINT03STAT_U           EINT03STAT         ; // 0x85c
} GPIO_Type;

#ifdef __cplusplus
}
#endif

#endif /* __REG_GPIO_H__ */
