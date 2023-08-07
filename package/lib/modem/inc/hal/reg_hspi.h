/*********************************************************************/
/*    Newracom Library / IP Product                                  */
/*    Product Name :                                                 */
/*    Version      :                                                 */
/*    Author       :                                                 */
/*    Update       :                                                 */
/*********************************************************************/

#ifndef __REG_HSPI_H__
#define __REG_HSPI_H__

#ifdef __cplusplus
extern "C"{
#endif

// 0x40090000 register ------------------------------------
typedef struct {
    uint32_t                   DEVRDY              :32;
}   HSPI_DEVRDY;

typedef union {
    uint32_t                   w;
    HSPI_DEVRDY                b;
}   HSPI_DEVRDY_U;


// 0x40090004 register ------------------------------------
typedef struct {
    uint32_t                   DEVSLP              :32;
}   HSPI_DEVSLP;

typedef union {
    uint32_t                   w;
    HSPI_DEVSLP                b;
}   HSPI_DEVSLP_U;


// 0x40090008 register ------------------------------------
typedef struct {
    uint32_t                   DEVSLP              :1 ;
    uint32_t                   DEVRDY              :1 ;
    uint32_t                   RXIRQEN             :1 ;
    uint32_t                   TXEIRQEN            :1 ;
    uint32_t                   reserved0           :28;
}   HSPI_HOSTSTAT;

typedef union {
    uint32_t                   w;
    HSPI_HOSTSTAT              b;
}   HSPI_HOSTSTAT_U;


// 0x40090010 register ------------------------------------
typedef struct {
    uint32_t                   MSG_00              :32;
}   HSPI_Device_Message_00;

typedef union {
    uint32_t                   w;
    HSPI_Device_Message_00     b;
}   HSPI_Device_Message_00_U;


// 0x40090014 register ------------------------------------
typedef struct {
    uint32_t                   MSG_01              :32;
}   HSPI_Device_Message_01;

typedef union {
    uint32_t                   w;
    HSPI_Device_Message_01     b;
}   HSPI_Device_Message_01_U;


// 0x40090018 register ------------------------------------
typedef struct {
    uint32_t                   MSG_02              :32;
}   HSPI_Device_Message_02;

typedef union {
    uint32_t                   w;
    HSPI_Device_Message_02     b;
}   HSPI_Device_Message_02_U;


// 0x4009001C register ------------------------------------
typedef struct {
    uint32_t                   MSG_03              :32;
}   HSPI_Device_Message_03;

typedef union {
    uint32_t                   w;
    HSPI_Device_Message_03     b;
}   HSPI_Device_Message_03_U;


// 0x40090030 register ------------------------------------
typedef struct {
    uint32_t                   CHIPVER             :32;
}   HSPI_CHIP_version;

typedef union {
    uint32_t                   w;
    HSPI_CHIP_version          b;
}   HSPI_CHIP_version_U;


// 0x40090034 register ------------------------------------
typedef struct {
    uint32_t                   MODEMVER            :32;
}   HSPI_MODEM_version;

typedef union {
    uint32_t                   w;
    HSPI_MODEM_version         b;
}   HSPI_MODEM_version_U;


// 0x40090038 register ------------------------------------
typedef struct {
    uint32_t                   SWVER               :32;
}   HSPI_SW_version;

typedef union {
    uint32_t                   w;
    HSPI_SW_version            b;
}   HSPI_SW_version_U;


// 0x4009003C register ------------------------------------
typedef struct {
    uint32_t                   BDVER               :32;
}   HSPI_Board_version;

typedef union {
    uint32_t                   w;
    HSPI_Board_version         b;
}   HSPI_Board_version_U;


// 0x40090040 register ------------------------------------
typedef struct {
    uint32_t                   CNTCTRL             :32;
}   HSPI_CNTCTRL;

typedef union {
    uint32_t                   w;
    HSPI_CNTCTRL               b;
}   HSPI_CNTCTRL_U;


// 0x40090044 register ------------------------------------
typedef struct {
    uint32_t                   CNTVAL              :32;
}   HSPI_CNTVAL;

typedef union {
    uint32_t                   w;
    HSPI_CNTVAL                b;
}   HSPI_CNTVAL_U;


// 0x40090100 register ------------------------------------
typedef struct {
    uint32_t                   RST                 :1 ;
    uint32_t                   reserved0           :31;
}   HSPI_TXQUERST;

typedef union {
    uint32_t                   w;
    HSPI_TXQUERST              b;
}   HSPI_TXQUERST_U;


// 0x40090104 register ------------------------------------
typedef struct {
    uint32_t                   BITMSB              :1 ;
    uint32_t                   BYTEMSB             :1 ;
    uint32_t                   reserved0           :2 ;
    uint32_t                   HEADER              :1 ;
    uint32_t                   reserved1           :26;
    uint32_t                   EN                  :1 ;
}   HSPI_TXQMODE;

typedef union {
    uint32_t                   w;
    HSPI_TXQMODE               b;
}   HSPI_TXQMODE_U;


// 0x40090108 register ------------------------------------
typedef struct {
    uint32_t                   TXQUE_irq_mode0     :1 ;
    uint32_t                   TXQUE_irq_mode1     :1 ;
    uint32_t                   reserved0           :29;
    uint32_t                   TXQUE_irq_enable    :1 ;
}   HSPI_TXQUE_IRQ_MODE;

typedef union {
    uint32_t                   w;
    HSPI_TXQUE_IRQ_MODE        b;
}   HSPI_TXQUE_IRQ_MODE_U;


// 0x40090110 register ------------------------------------
typedef struct {
    uint32_t                   ADDR                :32;
}   HSPI_TXQSET0;

typedef union {
    uint32_t                   w;
    HSPI_TXQSET0               b;
}   HSPI_TXQSET0_U;


// 0x40090114 register ------------------------------------
typedef struct {
    uint32_t                   SIZE                :16;
    uint32_t                   reserved0           :11;
    uint32_t                   INTMSK              :1 ;
    uint32_t                   reserved1           :2 ;
    uint32_t                   SENDEIRQ            :1 ;
    uint32_t                   QUPDATE             :1 ;
}   HSPI_TXQSET1;

typedef union {
    uint32_t                   w;
    HSPI_TXQSET1               b;
}   HSPI_TXQSET1_U;


// 0x40090118 register ------------------------------------
typedef struct {
    uint32_t                   QUE_TOT             :16;
    uint32_t                   QUE_CNT             :6 ;
    uint32_t                   reserved0           :1 ;
    uint32_t                   QUE_ERR             :1 ;
    uint32_t                   reserved1           :7 ;
    uint32_t                   QUE_IRQ             :1 ;
}   HSPI_TXQSTAT;

typedef union {
    uint32_t                   w;
    HSPI_TXQSTAT               b;
}   HSPI_TXQSTAT_U;


// 0x40090200 register ------------------------------------
typedef struct {
    uint32_t                   RST                 :1 ;
    uint32_t                   reserved0           :31;
}   HSPI_RXQRST;

typedef union {
    uint32_t                   w;
    HSPI_RXQRST                b;
}   HSPI_RXQRST_U;


// 0x40090204 register ------------------------------------
typedef struct {
    uint32_t                   BITMSB              :1 ;
    uint32_t                   BYTEMSB             :1 ;
    uint32_t                   reserved0           :2 ;
    uint32_t                   HEADER              :1 ;
    uint32_t                   reserved1           :26;
    uint32_t                   EN                  :1 ;
}   HSPI_RXQMODE;

typedef union {
    uint32_t                   w;
    HSPI_RXQMODE               b;
}   HSPI_RXQMODE_U;


// 0x40090208 register ------------------------------------
typedef struct {
    uint32_t                   IRQPOL              :1 ;
    uint32_t                   IRQMD               :1 ;
    uint32_t                   reserved0           :29;
    uint32_t                   IRQEN               :1 ;
}   HSPI_RXQIRQ;

typedef union {
    uint32_t                   w;
    HSPI_RXQIRQ                b;
}   HSPI_RXQIRQ_U;


// 0x40090210 register ------------------------------------
typedef struct {
    uint32_t                   ADDR                :32;
}   HSPI_RXQSET0;

typedef union {
    uint32_t                   w;
    HSPI_RXQSET0               b;
}   HSPI_RXQSET0_U;


// 0x40090214 register ------------------------------------
typedef struct {
    uint32_t                   SIZE                :16;
    uint32_t                   reserved0           :11;
    uint32_t                   INTMSK              :1 ;
    uint32_t                   reserved1           :3 ;
    uint32_t                   QUPDATE             :1 ;
}   HSPI_RXQSET1;

typedef union {
    uint32_t                   w;
    HSPI_RXQSET1               b;
}   HSPI_RXQSET1_U;


// 0x40090218 register ------------------------------------
typedef struct {
    uint32_t                   TOT                 :16;
    uint32_t                   CNT                 :6 ;
    uint32_t                   reserved0           :1 ;
    uint32_t                   ERR                 :1 ;
    uint32_t                   reserved1           :7 ;
    uint32_t                   IRQ                 :1 ;
}   HSPI_RXQSTAT;

typedef union {
    uint32_t                   w;
    HSPI_RXQSTAT               b;
}   HSPI_RXQSTAT_U;


//---------------------------------------------------------
// HSPI Register Map
//---------------------------------------------------------
typedef struct {
    volatile HSPI_DEVRDY_U                     DEVRDY                   ; // 0x00
    volatile HSPI_DEVSLP_U                     DEVSLP                   ; // 0x04
    volatile HSPI_HOSTSTAT_U                   HOSTSTAT                 ; // 0x08
    volatile uint32_t                            RESERVED0                ; // 
    volatile HSPI_Device_Message_00_U          Device_Message_00        ; // 0x10
    volatile HSPI_Device_Message_01_U          Device_Message_01        ; // 0x14
    volatile HSPI_Device_Message_02_U          Device_Message_02        ; // 0x18
    volatile HSPI_Device_Message_03_U          Device_Message_03        ; // 0x1c
    volatile uint32_t                            RESERVED1[4]             ; // 
    volatile HSPI_CHIP_version_U               CHIP_version             ; // 0x30
    volatile HSPI_MODEM_version_U              MODEM_version            ; // 0x34
    volatile HSPI_SW_version_U                 SW_version               ; // 0x38
    volatile HSPI_Board_version_U              Board_version            ; // 0x3c
    volatile HSPI_CNTCTRL_U                    CNTCTRL                  ; // 0x40
    volatile HSPI_CNTVAL_U                     CNTVAL                   ; // 0x44
    volatile uint32_t                            RESERVED2[46]            ; // 
    volatile HSPI_TXQUERST_U                   TXQUERST                 ; // 0x100
    volatile HSPI_TXQMODE_U                    TXQMODE                  ; // 0x104
    volatile HSPI_TXQUE_IRQ_MODE_U             TXQUE_IRQ_MODE           ; // 0x108
    volatile uint32_t                            RESERVED3                ; // 
    volatile HSPI_TXQSET0_U                    TXQSET0                  ; // 0x110
    volatile HSPI_TXQSET1_U                    TXQSET1                  ; // 0x114
    volatile HSPI_TXQSTAT_U                    TXQSTAT                  ; // 0x118
    volatile uint32_t                            RESERVED4[57]            ; // 
    volatile HSPI_RXQRST_U                     RXQRST                   ; // 0x200
    volatile HSPI_RXQMODE_U                    RXQMODE                  ; // 0x204
    volatile HSPI_RXQIRQ_U                     RXQIRQ                   ; // 0x208
    volatile uint32_t                            RESERVED5                ; // 
    volatile HSPI_RXQSET0_U                    RXQSET0                  ; // 0x210
    volatile HSPI_RXQSET1_U                    RXQSET1                  ; // 0x214
    volatile HSPI_RXQSTAT_U                    RXQSTAT                  ; // 0x218
} HSPI_Type;

#ifdef __cplusplus
}
#endif

#endif /* __REG_HSPI_H__ */
