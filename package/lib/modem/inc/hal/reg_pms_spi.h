/*********************************************************************/
/*    Newracom Library / IP Product                                  */
/*    Product Name :                                                 */
/*    Version      :                                                 */
/*    Author       :                                                 */
/*    Update       :                                                 */
/*********************************************************************/

#ifndef __REG_PMS_SPI_H__
#define __REG_PMS_SPI_H__

#ifdef __cplusplus
extern "C"{
#endif

// 0x4004E000 register ------------------------------------
typedef struct {
    uint32_t           CR          :4 ;
    uint32_t           reserved0   :27;
    uint32_t           SWR         :1 ;
}   PMS_SPI_CONFIG;

typedef union {
    uint32_t           w;
    PMS_SPI_CONFIG     b;
}   PMS_SPI_CONFIG_U;


// 0x4004E004 register ------------------------------------
typedef struct {
    uint32_t           DATA        :16;
    uint32_t           ADDR        :7 ;
    uint32_t           reserved0   :2 ;
    uint32_t           RW          :1 ;
    uint32_t           reserved1   :6 ;
}   PMS_SPI_TXDATA;

typedef union {
    uint32_t           w;
    PMS_SPI_TXDATA     b;
}   PMS_SPI_TXDATA_U;


// 0x4004E008 register ------------------------------------
typedef struct {
    uint32_t           WDATA       :16;
    uint32_t           reserved0   :16;
}   PMS_SPI_WDATA;

typedef union {
    uint32_t           w;
    PMS_SPI_WDATA      b;
}   PMS_SPI_WDATA_U;


// 0x4004E00C register ------------------------------------
typedef struct {
    uint32_t           RDATA       :26;
    uint32_t           reserved0   :6 ;
}   PMS_SPI_RDATA;

typedef union {
    uint32_t           w;
    PMS_SPI_RDATA      b;
}   PMS_SPI_RDATA_U;


// 0x4004E010 register ------------------------------------
typedef struct {
    uint32_t           SAE         :1 ;
    uint32_t           BUSY        :1 ;
    uint32_t           reserved0   :2 ;
    uint32_t           SPIMODE     :2 ;
    uint32_t           reserved1   :26;
}   PMS_SPI_STAT;

typedef union {
    uint32_t           w;
    PMS_SPI_STAT       b;
}   PMS_SPI_STAT_U;


//---------------------------------------------------------
// PMS_SPI Register Map
//---------------------------------------------------------
typedef struct {
    volatile PMS_SPI_CONFIG_U          CONFIG        ; // 0x000
    volatile PMS_SPI_TXDATA_U          TXDATA        ; // 0x004
    volatile PMS_SPI_WDATA_U           WDATA         ; // 0x008
    volatile PMS_SPI_RDATA_U           RDATA         ; // 0x00c
    volatile PMS_SPI_STAT_U            STAT          ; // 0x010
} PMS_SPI_Type;

#ifdef __cplusplus
}
#endif

#endif /* __REG_PMS_SPI_H__ */
