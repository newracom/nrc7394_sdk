/*********************************************************************/
/*    Newracom Library / IP Product                                  */
/*    Product Name :                                                 */
/*    Version      :                                                 */
/*    Author       :                                                 */
/*    Update       :                                                 */
/*********************************************************************/

#ifndef __REG_I2C_H__
#define __REG_I2C_H__

#ifdef __cplusplus
extern "C"{
#endif

// 0x40006000 register ------------------------------------
typedef struct {
    uint32_t     PRES        :16;
    uint32_t     reserved0   :16;
}   I2C_PRES;

typedef union {
    uint32_t     w;
    I2C_PRES     b;
}   I2C_PRES_U;


// 0x40006004 register ------------------------------------
typedef struct {
    uint32_t     reserved0   :5 ;
    uint32_t     MOD         :1 ;
    uint32_t     IEN         :1 ;
    uint32_t     EN          :1 ;
    uint32_t     reserved1   :24;
}   I2C_CTRL;

typedef union {
    uint32_t     w;
    I2C_CTRL     b;
}   I2C_CTRL_U;


// 0x40006008 register ------------------------------------
typedef struct {
    uint32_t     TXDATA      :16;
    uint32_t     reserved0   :16;
}   I2C_TXR;

typedef union {
    uint32_t     w;
    I2C_TXR      b;
}   I2C_TXR_U;


// 0x4000600C register ------------------------------------
typedef struct {
    uint32_t     IACK        :1 ;
    uint32_t     reserved0   :2 ;
    uint32_t     ACK         :1 ;
    uint32_t     WR          :1 ;
    uint32_t     RD          :1 ;
    uint32_t     STO         :1 ;
    uint32_t     STA         :1 ;
    uint32_t     reserved1   :24;
}   I2C_CMD;

typedef union {
    uint32_t     w;
    I2C_CMD      b;
}   I2C_CMD_U;


// 0x40006010 register ------------------------------------
typedef struct {
    uint32_t     RXDATA      :16;
    uint32_t     reserved0   :16;
}   I2C_RXR;

typedef union {
    uint32_t     w;
    I2C_RXR      b;
}   I2C_RXR_U;


// 0x40006014 register ------------------------------------
typedef struct {
    uint32_t     IF          :1 ;
    uint32_t     TIP         :1 ;
    uint32_t     reserved0   :3 ;
    uint32_t     AL          :1 ;
    uint32_t     BUSY        :1 ;
    uint32_t     RXACK       :1 ;
    uint32_t     reserved1   :24;
}   I2C_SR;

typedef union {
    uint32_t     w;
    I2C_SR       b;
}   I2C_SR_U;


// 0x40006018 register ------------------------------------
typedef struct {
    uint32_t     FC          :5 ;
    uint32_t     CKSEL       :1 ;
    uint32_t     reserved0   :2 ;
    uint32_t     RC          :8 ;
    uint32_t     reserved1   :16;
}   I2C_TR;

typedef union {
    uint32_t     w;
    I2C_TR       b;
}   I2C_TR_U;


//---------------------------------------------------------
// I2C Register Map
//---------------------------------------------------------
typedef struct {
    volatile I2C_PRES_U          PRES        ; // 0x000
    volatile I2C_CTRL_U          CTRL        ; // 0x004
    volatile I2C_TXR_U           TXR         ; // 0x008
    volatile I2C_CMD_U           CMD         ; // 0x00c
    volatile I2C_RXR_U           RXR         ; // 0x010
    volatile I2C_SR_U            SR          ; // 0x014
    volatile I2C_TR_U            TR          ; // 0x018
} I2C_Type;

#ifdef __cplusplus
}
#endif

#endif /* __REG_I2C_H__ */
