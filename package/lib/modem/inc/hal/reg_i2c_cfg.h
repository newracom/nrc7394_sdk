/*********************************************************************/
/*    Newracom Library / IP Product                                  */
/*    Product Name :                                                 */
/*    Version      :                                                 */
/*    Author       :                                                 */
/*    Update       :                                                 */
/*********************************************************************/

#ifndef __REG_I2C_CFG_H__
#define __REG_I2C_CFG_H__

#ifdef __cplusplus
extern "C"{
#endif

// 0x40006210 register ------------------------------------
typedef struct {
    uint32_t              SWRSTM0     :1 ;
    uint32_t              SWRSTM1     :1 ;
    uint32_t              reserved0   :30;
}   I2C_CFG_I2CSWRST;

typedef union {
    uint32_t              w;
    I2C_CFG_I2CSWRST      b;
}   I2C_CFG_I2CSWRST_U;


// 0x40006214 register ------------------------------------
typedef struct {
    uint32_t              IRQM0       :1 ;
    uint32_t              IRQM1       :1 ;
    uint32_t              reserved0   :30;
}   I2C_CFG_I2CSTATUS;

typedef union {
    uint32_t              w;
    I2C_CFG_I2CSTATUS     b;
}   I2C_CFG_I2CSTATUS_U;


//---------------------------------------------------------
// I2C_CFG Register Map
//---------------------------------------------------------
typedef struct {
    volatile uint32_t                    RESERVED0[4]     ; // 
    volatile I2C_CFG_I2CSWRST_U           I2CSWRST         ; // 0x10
    volatile I2C_CFG_I2CSTATUS_U          I2CSTATUS        ; // 0x14
} I2C_CFG_Type;

#ifdef __cplusplus
}
#endif

#endif /* __REG_I2C_CFG_H__ */
