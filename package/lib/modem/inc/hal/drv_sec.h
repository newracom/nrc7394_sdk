
#ifndef __DRV_SEC_H__
#define __DRV_SEC_H__

#include "system_common.h"

#define DATA_MODE_SHA       (0)
#define DATA_MODE_AES       (1)
#define DATA_MODE_DES       (2)
#define DATA_MODE_BIGNUM    (3)

#define ASM_OPT

void convert_endian(uint8_t *p, int len);
void convert_endian_32(uint32_t *p, int len);
void to_big_endian (uint8_t *dest, uint32_t src, uint8_t or_flag );

//uint8_t get_version_info(void);
uint32_t get_irq_status(void);
void set_irq_clear(uint32_t clr);
//void set_irq_mask(uint32_t mask);

void sha_init(uint8_t little_endian);
uint8_t sha_is_busy(void);
uint8_t sha_is_done(void);
int sha_configure (uint8_t is_sha2, uint8_t is_sha2_512, 
        uint8_t is_sha2_variant, uint8_t first_blk);
int sha_set_firstblk (uint8_t first_blk);
int sha_start (void);
int sha_msg_update (const uint8_t* in, uint32_t len);
int sha_get_result (uint8_t* out, uint32_t len);

void aes_init(uint8_t little_endian);
uint8_t aes_is_busy(void);
uint8_t aes_is_done(void);
int aes_configure (uint8_t aes_mode, uint8_t aes_forward);
int aes_start (void);
int aes_msg_update (const uint8_t* in, uint32_t byte_offset, uint32_t len);
int aes_key_update (const uint8_t* in, uint32_t byte_offset, uint32_t len);
int aes_get_result (uint8_t* out, uint32_t len);

void des_init(uint8_t little_endian);
uint8_t des_is_busy(void);
uint8_t des_is_done(void);
int des_configure (uint8_t des_mode, uint32_t des_blk_len);
int des_request (void);
int des_start (void);
int des_msg_update (const uint8_t* in, uint32_t byte_offset, uint32_t len);
int des_iv_update (const uint8_t* in);
int des_key_update (const uint8_t* in, uint8_t index);
int des_get_result (uint8_t* out, uint32_t len);

void bignum_init(uint8_t little_endian);
uint8_t bignum_is_busy(void);
uint8_t bignum_is_done(void);
int bignum_configure (uint8_t op_mode);
int bignum_op_start (uint8_t op_mode);
int bignum_clear_op (uint8_t op_clear);
int bignum_start (void);
int bignum_abort (void);
int bignum_operand_update (const uint8_t* in, uint32_t byte_offset, uint32_t len);
void bignum_operand32_update (const uint32_t* in, uint32_t word_offset, uint32_t word_len);
int bignum_opA (const uint8_t* in, uint32_t byte_offset, uint32_t len);
int bignum_opB (const uint8_t* in, uint32_t byte_offset, uint32_t len);
int bignum_opN (const uint8_t* in, uint32_t byte_offset, uint32_t len);
int bignum_opA32 (const uint32_t* in, uint32_t word_offset, uint32_t word_len);
int bignum_opB32 (const uint32_t* in, uint32_t word_offset, uint32_t word_len);
int bignum_opN32 (const uint32_t* in, uint32_t word_offset, uint32_t word_len);
int bignum_get_result (uint8_t* out, uint32_t len);
int bignum_get32_result (uint32_t* out, uint32_t word_len);

#define SHA_POLLING_TEST

#define STATUS_OK   (0)
#define STATUS_ERR  (-1)
#define ENDIAN_BI 0
#define ENDIAN_LE 1

#define SHA_MODE_1  0        // SHA-1
#define SHA_MODE_2  1        // SHA-2

#define SHA_BIT_256 0
#define SHA_BIT_512 1

#define SHA_VERIANT_DIS     0
#define SHA_VERIANT_EN      1


#define INTR_ALL            (0x1F)
#define INTR_SHA_DONE       (1UL<<0)
#define INTR_AES_DONE       (1UL<<1)
#define INTR_DES_DONE       (1UL<<2)
#define INTR_DES_RESP       (1UL<<3)
#define INTR_BIGNUM_DONE    (1UL<<4)

#define BIGNUM_OPA_CLR      (1UL<<0)
#define BIGNUM_OPB_CLR      (1UL<<1)
#define BIGNUM_OPN_CLR      (1UL<<2)


#define BIGNUM_MODE_NONE    (0)
#define BIGNUM_MODE_ADD     (1)
#define BIGNUM_MODE_SUB     (2)
#define BIGNUM_MODE_MUL     (3)
#define BIGNUM_MODE_MOD     (4)
#define BIGNUM_MODE_ADDMOD  (5)
#define BIGNUM_MODE_SUBMOD  (6)
#define BIGNUM_MODE_MULMOD  (7)
#define BIGNUM_MODE_SHIFT_L (8)
#define BIGNUM_MODE_SHIFT_R (9)

#define STATUS_OK   (0)
#define STATUS_ERR  (-1)

//INCLUDE_HW_SECURITY_ACC
#endif // __SEC_IP_DRV_H__
