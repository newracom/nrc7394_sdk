/*********************************************************************/
/*    Newracom Library / IP Product                                  */
/*    Product Name :                                                 */
/*    Version      :                                                 */
/*    Author       :                                                 */
/*    Update       :                                                 */
/*********************************************************************/

#ifndef __REG_SEC_H__
#define __REG_SEC_H__

#ifdef __cplusplus
extern "C"{
#endif

// 0x40049000 register ------------------------------------
typedef struct {
    uint32_t                   RSTn             :1 ;
    uint32_t                   reserved0        :31;
}   SEC_SOFT_RSTN;

typedef union {
    uint32_t                   w;
    SEC_SOFT_RSTN              b;
}   SEC_SOFT_RSTN_U;


// 0x40049004 register ------------------------------------
typedef struct {
    uint32_t                   DATAI_END        :1 ;
    uint32_t                   DATAO_END        :1 ;
    uint32_t                   reserved0        :6 ;
    uint32_t                   DATA_MODE        :2 ;
    uint32_t                   reserved1        :22;
}   SEC_ENDIAN;

typedef union {
    uint32_t                   w;
    SEC_ENDIAN                 b;
}   SEC_ENDIAN_U;


// 0x40049008 register ------------------------------------
typedef struct {
    uint32_t                   SHA_MODE         :1 ;
    uint32_t                   SHA2_SEL         :1 ;
    uint32_t                   SHA2_VAR         :1 ;
    uint32_t                   SHA_1ST_BLK      :1 ;
    uint32_t                   reserved0        :28;
}   SEC_SHA_CONFIG;

typedef union {
    uint32_t                   w;
    SEC_SHA_CONFIG             b;
}   SEC_SHA_CONFIG_U;


// 0x4004900C register ------------------------------------
typedef struct {
    uint32_t                   SHA_START        :1 ;
    uint32_t                   reserved0        :31;
}   SEC_SHA_CONT;

typedef union {
    uint32_t                   w;
    SEC_SHA_CONT               b;
}   SEC_SHA_CONT_U;


// 0x40049020 register ------------------------------------
typedef struct {
    uint32_t                   BIGNUM_OP        :4 ;
    uint32_t                   reserved0        :28;
}   SEC_BIGNUM_OP;

typedef union {
    uint32_t                   w;
    SEC_BIGNUM_OP              b;
}   SEC_BIGNUM_OP_U;


// 0x40049024 register ------------------------------------
typedef struct {
    uint32_t                   BIGNUM_START     :1 ;
    uint32_t                   BIGNUM_ABORT     :1 ;
    uint32_t                   reserved0        :30;
}   SEC_BIGNUM_START_ABORT;

typedef union {
    uint32_t                   w;
    SEC_BIGNUM_START_ABORT     b;
}   SEC_BIGNUM_START_ABORT_U;


// 0x40049028 register ------------------------------------
typedef struct {
    uint32_t                   CLEAR_OP_A       :1 ;
    uint32_t                   CLEAR_OP_B       :1 ;
    uint32_t                   CLEAR_OP_N       :1 ;
    uint32_t                   reserved0        :29;
}   SEC_BIGNUM_OP_CLEAR;

typedef union {
    uint32_t                   w;
    SEC_BIGNUM_OP_CLEAR        b;
}   SEC_BIGNUM_OP_CLEAR_U;


// 0x40049040 register ------------------------------------
typedef struct {
    uint32_t                   DONE             :1 ;
    uint32_t                   BUSY             :1 ;
    uint32_t                   reserved0        :30;
}   SEC_SHA_STATUS;

typedef union {
    uint32_t                   w;
    SEC_SHA_STATUS             b;
}   SEC_SHA_STATUS_U;


// 0x4004904C register ------------------------------------
typedef struct {
    uint32_t                   DONE             :1 ;
    uint32_t                   BUSY             :1 ;
    uint32_t                   ERR_OP           :1 ;
    uint32_t                   ERR_MUL          :1 ;
    uint32_t                   ERR_MOD          :1 ;
    uint32_t                   reserved0        :27;
}   SEC_BIGNUM_STATUS;

typedef union {
    uint32_t                   w;
    SEC_BIGNUM_STATUS          b;
}   SEC_BIGNUM_STATUS_U;


// 0x40049080 register ------------------------------------
typedef struct {
    uint32_t                   SHA              :1 ;
    uint32_t                   reserved0        :3 ;
    uint32_t                   BIG_NUM          :1 ;
    uint32_t                   reserved1        :27;
}   SEC_INT_MASK;

typedef union {
    uint32_t                   w;
    SEC_INT_MASK               b;
}   SEC_INT_MASK_U;


// 0x40049084 register ------------------------------------
typedef struct {
    uint32_t                   SHA              :1 ;
    uint32_t                   reserved0        :3 ;
    uint32_t                   BIG_NUM          :1 ;
    uint32_t                   reserved1        :27;
}   SEC_INT_CLR;

typedef union {
    uint32_t                   w;
    SEC_INT_CLR                b;
}   SEC_INT_CLR_U;


// 0x40049088 register ------------------------------------
typedef struct {
    uint32_t                   SHA              :1 ;
    uint32_t                   reserved0        :3 ;
    uint32_t                   BIG_NUM          :1 ;
    uint32_t                   reserved1        :27;
}   SEC_INT_STAT;

typedef union {
    uint32_t                   w;
    SEC_INT_STAT               b;
}   SEC_INT_STAT_U;


// 0x400491FC register ------------------------------------
typedef struct {
    uint32_t                   VERSION          :8 ;
    uint32_t                   reserved0        :24;
}   SEC_VER;

typedef union {
    uint32_t                   w;
    SEC_VER                    b;
}   SEC_VER_U;


// 0x40049200 register ------------------------------------
//       ~
// 0x4004927C register ------------------------------------
typedef struct {
    uint32_t                   INPUT            :32;
}   SEC_IN_DATA;

typedef union {
    uint32_t                   w;
    SEC_IN_DATA                b;
}   SEC_IN_DATA_U;


// 0x40049280 register ------------------------------------
//       ~
// 0x400492BC register ------------------------------------
typedef struct {
    uint32_t                   INPUT_Modular    :32;
}   SEC_IN_MOD;

typedef union {
    uint32_t                   w;
    SEC_IN_MOD                 b;
}   SEC_IN_MOD_U;


// 0x40049300 register ------------------------------------
//       ~
// 0x4004937C register ------------------------------------
typedef struct {
    uint32_t                   OUTPUT           :32;
}   SEC_OUT_DATA;

typedef union {
    uint32_t                   w;
    SEC_OUT_DATA               b;
}   SEC_OUT_DATA_U;


//---------------------------------------------------------
// SEC Register Map
//---------------------------------------------------------
typedef struct {
    volatile SEC_SOFT_RSTN_U                   SOFT_RSTN                 ; // 0x000
    volatile SEC_ENDIAN_U                      ENDIAN                    ; // 0x004
    volatile SEC_SHA_CONFIG_U                  SHA_CONFIG                ; // 0x008
    volatile SEC_SHA_CONT_U                    SHA_CONT                  ; // 0x00c
    volatile uint32_t                             RESERVED0[4]              ; // 
    volatile SEC_BIGNUM_OP_U                   BIGNUM_OP                 ; // 0x020
    volatile SEC_BIGNUM_START_ABORT_U          BIGNUM_START_ABORT        ; // 0x024
    volatile SEC_BIGNUM_OP_CLEAR_U             BIGNUM_OP_CLEAR           ; // 0x028
    volatile uint32_t                             RESERVED1[5]              ; // 
    volatile SEC_SHA_STATUS_U                  SHA_STATUS                ; // 0x040
    volatile uint32_t                             RESERVED2[2]              ; // 
    volatile SEC_BIGNUM_STATUS_U               BIGNUM_STATUS             ; // 0x04c
    volatile uint32_t                             RESERVED3[12]             ; // 
    volatile SEC_INT_MASK_U                    INT_MASK                  ; // 0x080
    volatile SEC_INT_CLR_U                     INT_CLR                   ; // 0x084
    volatile SEC_INT_STAT_U                    INT_STAT                  ; // 0x088
    volatile uint32_t                             RESERVED4[92]             ; // 
    volatile SEC_VER_U                         VER                       ; // 0x1fc
    volatile SEC_IN_DATA_U                     IN_DATA[32]               ; // 0x200~0x27c
    volatile SEC_IN_MOD_U                      IN_MOD[16]                ; // 0x280~0x2bc
    volatile uint32_t                             RESERVED5[16]             ; // 
    volatile SEC_OUT_DATA_U                    OUT_DATA[32]              ; // 0x300~0x37c
} SEC_Type;

#ifdef __cplusplus
}
#endif

#endif /* __REG_SEC_H__ */
