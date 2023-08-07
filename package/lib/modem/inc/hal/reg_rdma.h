/*********************************************************************/
/*    Newracom Library / IP Product                                  */
/*    Product Name :                                                 */
/*    Version      :                                                 */
/*    Author       :                                                 */
/*    Update       :                                                 */
/*********************************************************************/

#ifndef __REG_RDMA_H__
#define __REG_RDMA_H__

#ifdef __cplusplus
extern "C"{
#endif

// 0x40048000 register ------------------------------------
typedef struct {
    uint32_t          DSTADDR      :32;
}   RDMA_DST;

typedef union {
    uint32_t          w;
    RDMA_DST          b;
}   RDMA_DST_U;


// 0x40048004 register ------------------------------------
typedef struct {
    uint32_t          DMAEN        :1 ;
    uint32_t          WENEDGE      :1 ;
    uint32_t          SRC_SEL      :1 ;
    uint32_t          reserved0    :1 ;
    uint32_t          reserved1    :28;
}   RDMA_CTRL;

typedef union {
    uint32_t          w;
    RDMA_CTRL         b;
}   RDMA_CTRL_U;


// 0x40048008 register ------------------------------------
typedef struct {
    uint32_t          CADDR        :32;
}   RDMA_CADDR;

typedef union {
    uint32_t          w;
    RDMA_CADDR        b;
}   RDMA_CADDR_U;


// 0x4004800C register ------------------------------------
typedef struct {
    uint32_t          TRANSCNT     :14;
    uint32_t          reserved0    :18;
}   RDMA_TRANSCNT;

typedef union {
    uint32_t          w;
    RDMA_TRANSCNT     b;
}   RDMA_TRANSCNT_U;


// 0x40048010 register ------------------------------------
typedef struct {
    uint32_t          reserved0    :1 ;
    uint32_t          DONE         :1 ;
    uint32_t          BUSY         :1 ;
    uint32_t          START        :1 ;
    uint32_t          FIFORWST     :1 ;
    uint32_t          FIFOOFCNT    :2 ;
    uint32_t          FIFOOFST     :1 ;
    uint32_t          reserved1    :8 ;
    uint32_t          STATE        :5 ;
    uint32_t          reserved2    :11;
}   RDMA_STATUS;

typedef union {
    uint32_t          w;
    RDMA_STATUS       b;
}   RDMA_STATUS_U;


// 0x40048014 register ------------------------------------
typedef struct {
    uint32_t          reserved0    :1 ;
    uint32_t          DONE         :1 ;
    uint32_t          reserved1    :1 ;
    uint32_t          START        :1 ;
    uint32_t          reserved2    :3 ;
    uint32_t          DFOVIE       :1 ;
    uint32_t          reserved3    :24;
}   RDMA_INTEN;

typedef union {
    uint32_t          w;
    RDMA_INTEN        b;
}   RDMA_INTEN_U;


// 0x40048018 register ------------------------------------
typedef struct {
    uint32_t          reserved0    :1 ;
    uint32_t          DONE         :1 ;
    uint32_t          reserved1    :1 ;
    uint32_t          START        :1 ;
    uint32_t          reserved2    :3 ;
    uint32_t          DFOVIC       :1 ;
    uint32_t          reserved3    :24;
}   RDMA_INTCLR;

typedef union {
    uint32_t          w;
    RDMA_INTCLR       b;
}   RDMA_INTCLR_U;


//---------------------------------------------------------
// RDMA Register Map
//---------------------------------------------------------
typedef struct {
    volatile RDMA_DST_U               DST             ; // 0x000
    volatile RDMA_CTRL_U              CTRL            ; // 0x004
    volatile RDMA_CADDR_U             CADDR           ; // 0x008
    volatile RDMA_TRANSCNT_U          TRANSCNT        ; // 0x00c
    volatile RDMA_STATUS_U            STATUS          ; // 0x010
    volatile RDMA_INTEN_U             INTEN           ; // 0x014
    volatile RDMA_INTCLR_U            INTCLR          ; // 0x018
} RDMA_Type;

#ifdef __cplusplus
}
#endif

#endif /* __REG_RDMA_H__ */
