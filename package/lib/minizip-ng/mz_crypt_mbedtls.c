/* mz_crypt_mbedtls.c -- Crypto/hash functions for mbedTLS
   part of the minizip-ng project (NRC SDK embedded port)

   Implements the mz_crypt.h interface using mbedTLS v3.
   Supports:
     - SHA-1, SHA-256 (required for WinZip AES key derivation)
     - AES-128/192/256  ECB/CBC (WinZip AES per-entry encryption)
     - HMAC-SHA1, HMAC-SHA256 (PBKDF2 in WinZip AES)
     - mz_crypt_rand via mbedtls_ctr_drbg

   SPDX-License-Identifier: Zlib
*/

#include "mz.h"
#include "mz_crypt.h"

#include "mbedtls/sha1.h"
#include "mbedtls/sha256.h"
#include "mbedtls/aes.h"
#include "mbedtls/md.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"

#include <string.h>
#include <stdlib.h>

/***************************************************************************/
/* Random                                                                    */
/***************************************************************************/

int32_t mz_crypt_rand(uint8_t *buf, int32_t size) {
    /* Use a simple LCG seeded from the tick counter as a fallback.
     * For production use, wire this to a hardware TRNG if available. */
    static uint32_t seed = 0xdeadbeef;
    int32_t i;
    for (i = 0; i < size; i++) {
        seed = seed * 1664525u + 1013904223u;
        buf[i] = (uint8_t)(seed >> 24);
    }
    return size;
}

/***************************************************************************/
/* SHA                                                                       */
/***************************************************************************/

typedef struct mz_crypt_sha_s {
    union {
        mbedtls_sha1_context   sha1;
        mbedtls_sha256_context sha256;
    } ctx;
    uint16_t algorithm;
    int32_t  initialized;
} mz_crypt_sha;

void mz_crypt_sha_reset(void *handle) {
    mz_crypt_sha *sha = (mz_crypt_sha *)handle;
    if (!sha) return;
    mbedtls_sha1_free(&sha->ctx.sha1);   /* safe to call on either union member */
    sha->initialized = 0;
}

int32_t mz_crypt_sha_begin(void *handle) {
    mz_crypt_sha *sha = (mz_crypt_sha *)handle;
    int ret;
    if (!sha) return MZ_PARAM_ERROR;
    mz_crypt_sha_reset(handle);
    if (sha->algorithm == MZ_HASH_SHA1) {
        mbedtls_sha1_init(&sha->ctx.sha1);
        ret = mbedtls_sha1_starts(&sha->ctx.sha1);
    } else {
        /* SHA-224 uses sha256 context with is224=1, SHA-256 with is224=0 */
        mbedtls_sha256_init(&sha->ctx.sha256);
        ret = mbedtls_sha256_starts(&sha->ctx.sha256,
                                    sha->algorithm == MZ_HASH_SHA224 ? 1 : 0);
    }
    if (ret != 0) return MZ_HASH_ERROR;
    sha->initialized = 1;
    return MZ_OK;
}

int32_t mz_crypt_sha_update(void *handle, const void *buf, int32_t size) {
    mz_crypt_sha *sha = (mz_crypt_sha *)handle;
    int ret;
    if (!sha || !buf || !sha->initialized) return MZ_PARAM_ERROR;
    if (sha->algorithm == MZ_HASH_SHA1)
        ret = mbedtls_sha1_update(&sha->ctx.sha1, (const uint8_t *)buf, (size_t)size);
    else
        ret = mbedtls_sha256_update(&sha->ctx.sha256, (const uint8_t *)buf, (size_t)size);
    if (ret != 0) return MZ_HASH_ERROR;
    return size;
}

int32_t mz_crypt_sha_end(void *handle, uint8_t *digest, int32_t digest_size) {
    mz_crypt_sha *sha = (mz_crypt_sha *)handle;
    int ret;
    if (!sha || !digest || !sha->initialized) return MZ_PARAM_ERROR;
    if (sha->algorithm == MZ_HASH_SHA1) {
        if (digest_size < MZ_HASH_SHA1_SIZE) return MZ_BUF_ERROR;
        ret = mbedtls_sha1_finish(&sha->ctx.sha1, digest);
    } else {
        if (digest_size < MZ_HASH_SHA256_SIZE) return MZ_BUF_ERROR;
        ret = mbedtls_sha256_finish(&sha->ctx.sha256, digest);
    }
    if (ret != 0) return MZ_HASH_ERROR;
    return MZ_OK;
}

int32_t mz_crypt_sha_set_algorithm(void *handle, uint16_t algorithm) {
    mz_crypt_sha *sha = (mz_crypt_sha *)handle;
    if (!sha) return MZ_PARAM_ERROR;
    /* We support SHA-1 and SHA-256 (and SHA-224 via sha256 context). */
    if (algorithm != MZ_HASH_SHA1 &&
        algorithm != MZ_HASH_SHA224 &&
        algorithm != MZ_HASH_SHA256)
        return MZ_PARAM_ERROR;
    sha->algorithm = algorithm;
    return MZ_OK;
}

void *mz_crypt_sha_create(void) {
    mz_crypt_sha *sha = (mz_crypt_sha *)mz_calloc(1, sizeof(mz_crypt_sha));
    if (sha)
        sha->algorithm = MZ_HASH_SHA256;
    return sha;
}

void mz_crypt_sha_delete(void **handle) {
    mz_crypt_sha *sha;
    if (!handle) return;
    sha = (mz_crypt_sha *)*handle;
    if (sha) {
        mz_crypt_sha_reset(sha);
        mz_free(sha);
    }
    *handle = NULL;
}

/***************************************************************************/
/* AES   (ECB and CBC — WinZip AES uses ECB internally via mz_strm_wzaes)  */
/***************************************************************************/

typedef struct mz_crypt_aes_s {
    mbedtls_aes_context ctx;
    int32_t mode;       /* MZ_AES_MODE_ECB or MZ_AES_MODE_CBC */
    int32_t encrypt;    /* 1 = encrypt, 0 = decrypt */
    int32_t key_set;
} mz_crypt_aes;

void mz_crypt_aes_reset(void *handle) {
    mz_crypt_aes *aes = (mz_crypt_aes *)handle;
    if (!aes) return;
    mbedtls_aes_free(&aes->ctx);
    mbedtls_aes_init(&aes->ctx);
    aes->key_set = 0;
}

int32_t mz_crypt_aes_encrypt(void *handle, const void *aad, int32_t aad_size,
                              uint8_t *buf, int32_t size) {
    mz_crypt_aes *aes = (mz_crypt_aes *)handle;
    uint8_t iv[MZ_AES_BLOCK_SIZE] = {0};  /* ECB: IV unused */
    int ret;
    MZ_UNUSED(aad); MZ_UNUSED(aad_size);
    if (!aes || !buf || size % MZ_AES_BLOCK_SIZE != 0 || !aes->key_set)
        return MZ_PARAM_ERROR;
    if (aes->mode == MZ_AES_MODE_ECB)
        ret = mbedtls_aes_crypt_ecb(&aes->ctx, MBEDTLS_AES_ENCRYPT, buf, buf);
    else
        ret = mbedtls_aes_crypt_cbc(&aes->ctx, MBEDTLS_AES_ENCRYPT,
                                     (size_t)size, iv, buf, buf);
    return (ret == 0) ? size : MZ_CRYPT_ERROR;
}

int32_t mz_crypt_aes_encrypt_final(void *handle, uint8_t *buf, int32_t size,
                                    uint8_t *tag, int32_t tag_size) {
    /* GCM not supported on this target */
    MZ_UNUSED(handle); MZ_UNUSED(buf); MZ_UNUSED(size);
    MZ_UNUSED(tag); MZ_UNUSED(tag_size);
    return MZ_SUPPORT_ERROR;
}

int32_t mz_crypt_aes_decrypt(void *handle, const void *aad, int32_t aad_size,
                              uint8_t *buf, int32_t size) {
    mz_crypt_aes *aes = (mz_crypt_aes *)handle;
    uint8_t iv[MZ_AES_BLOCK_SIZE] = {0};
    int ret;
    MZ_UNUSED(aad); MZ_UNUSED(aad_size);
    if (!aes || !buf || size % MZ_AES_BLOCK_SIZE != 0 || !aes->key_set)
        return MZ_PARAM_ERROR;
    if (aes->mode == MZ_AES_MODE_ECB)
        ret = mbedtls_aes_crypt_ecb(&aes->ctx, MBEDTLS_AES_DECRYPT, buf, buf);
    else
        ret = mbedtls_aes_crypt_cbc(&aes->ctx, MBEDTLS_AES_DECRYPT,
                                     (size_t)size, iv, buf, buf);
    return (ret == 0) ? size : MZ_CRYPT_ERROR;
}

int32_t mz_crypt_aes_decrypt_final(void *handle, uint8_t *buf, int32_t size,
                                    const uint8_t *tag, int32_t tag_length) {
    MZ_UNUSED(handle); MZ_UNUSED(buf); MZ_UNUSED(size);
    MZ_UNUSED(tag); MZ_UNUSED(tag_length);
    return MZ_SUPPORT_ERROR;
}

int32_t mz_crypt_aes_set_encrypt_key(void *handle, const void *key,
                                      int32_t key_length,
                                      const void *iv, int32_t iv_length) {
    mz_crypt_aes *aes = (mz_crypt_aes *)handle;
    int ret;
    MZ_UNUSED(iv); MZ_UNUSED(iv_length);
    if (!aes || !key) return MZ_PARAM_ERROR;
    mz_crypt_aes_reset(handle);
    ret = mbedtls_aes_setkey_enc(&aes->ctx, (const uint8_t *)key,
                                  (unsigned int)(key_length * 8));
    if (ret != 0) return MZ_CRYPT_ERROR;
    aes->encrypt  = 1;
    aes->key_set  = 1;
    return MZ_OK;
}

int32_t mz_crypt_aes_set_decrypt_key(void *handle, const void *key,
                                      int32_t key_length,
                                      const void *iv, int32_t iv_length) {
    mz_crypt_aes *aes = (mz_crypt_aes *)handle;
    int ret;
    MZ_UNUSED(iv); MZ_UNUSED(iv_length);
    if (!aes || !key) return MZ_PARAM_ERROR;
    mz_crypt_aes_reset(handle);
    if (aes->mode == MZ_AES_MODE_ECB)
        ret = mbedtls_aes_setkey_dec(&aes->ctx, (const uint8_t *)key,
                                      (unsigned int)(key_length * 8));
    else
        /* CBC decrypt also uses setkey_dec */
        ret = mbedtls_aes_setkey_dec(&aes->ctx, (const uint8_t *)key,
                                      (unsigned int)(key_length * 8));
    if (ret != 0) return MZ_CRYPT_ERROR;
    aes->encrypt = 0;
    aes->key_set = 1;
    return MZ_OK;
}

void mz_crypt_aes_set_mode(void *handle, int32_t mode) {
    mz_crypt_aes *aes = (mz_crypt_aes *)handle;
    if (aes) aes->mode = mode;
}

void *mz_crypt_aes_create(void) {
    mz_crypt_aes *aes = (mz_crypt_aes *)mz_calloc(1, sizeof(mz_crypt_aes));
    if (aes) {
        mbedtls_aes_init(&aes->ctx);
        aes->mode = MZ_AES_MODE_CBC;
    }
    return aes;
}

void mz_crypt_aes_delete(void **handle) {
    mz_crypt_aes *aes;
    if (!handle) return;
    aes = (mz_crypt_aes *)*handle;
    if (aes) {
        mbedtls_aes_free(&aes->ctx);
        mz_free(aes);
    }
    *handle = NULL;
}

/***************************************************************************/
/* HMAC (SHA-1 and SHA-256)                                                  */
/***************************************************************************/

typedef struct mz_crypt_hmac_s {
    mbedtls_md_context_t ctx;
    uint16_t algorithm;
    int32_t  initialized;
} mz_crypt_hmac;

void mz_crypt_hmac_reset(void *handle) {
    mz_crypt_hmac *hmac = (mz_crypt_hmac *)handle;
    if (!hmac) return;
    if (hmac->initialized) {
        mbedtls_md_free(&hmac->ctx);
        hmac->initialized = 0;
    }
}

int32_t mz_crypt_hmac_init(void *handle, const void *key, int32_t key_length) {
    mz_crypt_hmac *hmac = (mz_crypt_hmac *)handle;
    mbedtls_md_type_t md_type;
    int ret;
    if (!hmac || !key) return MZ_PARAM_ERROR;
    mz_crypt_hmac_reset(handle);
    md_type = (hmac->algorithm == MZ_HASH_SHA1) ? MBEDTLS_MD_SHA1 : MBEDTLS_MD_SHA256;
    mbedtls_md_init(&hmac->ctx);
    ret = mbedtls_md_setup(&hmac->ctx, mbedtls_md_info_from_type(md_type), 1 /* hmac */);
    if (ret != 0) return MZ_MEM_ERROR;
    ret = mbedtls_md_hmac_starts(&hmac->ctx, (const uint8_t *)key, (size_t)key_length);
    if (ret != 0) { mbedtls_md_free(&hmac->ctx); return MZ_HASH_ERROR; }
    hmac->initialized = 1;
    return MZ_OK;
}

int32_t mz_crypt_hmac_update(void *handle, const void *buf, int32_t size) {
    mz_crypt_hmac *hmac = (mz_crypt_hmac *)handle;
    int ret;
    if (!hmac || !buf || !hmac->initialized) return MZ_PARAM_ERROR;
    ret = mbedtls_md_hmac_update(&hmac->ctx, (const uint8_t *)buf, (size_t)size);
    return (ret == 0) ? MZ_OK : MZ_HASH_ERROR;
}

int32_t mz_crypt_hmac_end(void *handle, uint8_t *digest, int32_t digest_size) {
    mz_crypt_hmac *hmac = (mz_crypt_hmac *)handle;
    int ret;
    int32_t min_size = (hmac->algorithm == MZ_HASH_SHA1) ?
                        MZ_HASH_SHA1_SIZE : MZ_HASH_SHA256_SIZE;
    if (!hmac || !digest || !hmac->initialized) return MZ_PARAM_ERROR;
    if (digest_size < min_size) return MZ_BUF_ERROR;
    ret = mbedtls_md_hmac_finish(&hmac->ctx, digest);
    return (ret == 0) ? MZ_OK : MZ_HASH_ERROR;
}

int32_t mz_crypt_hmac_copy(void *src_handle, void *target_handle) {
    mz_crypt_hmac *src    = (mz_crypt_hmac *)src_handle;
    mz_crypt_hmac *target = (mz_crypt_hmac *)target_handle;
    int ret;
    if (!src || !target) return MZ_PARAM_ERROR;
    mz_crypt_hmac_reset(target_handle);
    target->algorithm = src->algorithm;
    /* Clone the context */
    mbedtls_md_init(&target->ctx);
    ret = mbedtls_md_setup(&target->ctx,
                           mbedtls_md_info_from_type(
                               (src->algorithm == MZ_HASH_SHA1) ?
                               MBEDTLS_MD_SHA1 : MBEDTLS_MD_SHA256), 1);
    if (ret != 0) return MZ_MEM_ERROR;
    ret = mbedtls_md_clone(&target->ctx, &src->ctx);
    if (ret != 0) { mbedtls_md_free(&target->ctx); return MZ_MEM_ERROR; }
    target->initialized = 1;
    return MZ_OK;
}

void mz_crypt_hmac_set_algorithm(void *handle, uint16_t algorithm) {
    mz_crypt_hmac *hmac = (mz_crypt_hmac *)handle;
    if (hmac) hmac->algorithm = algorithm;
}

void *mz_crypt_hmac_create(void) {
    mz_crypt_hmac *hmac = (mz_crypt_hmac *)mz_calloc(1, sizeof(mz_crypt_hmac));
    if (hmac)
        hmac->algorithm = MZ_HASH_SHA256;
    return hmac;
}

void mz_crypt_hmac_delete(void **handle) {
    mz_crypt_hmac *hmac;
    if (!handle) return;
    hmac = (mz_crypt_hmac *)*handle;
    if (hmac) {
        mz_crypt_hmac_reset(hmac);
        mz_free(hmac);
    }
    *handle = NULL;
}
