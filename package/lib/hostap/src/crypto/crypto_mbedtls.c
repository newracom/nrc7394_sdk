/*
 * WPA Supplicant / wrapper functions for mbedtls
 * Copyright (c) 2004-2009, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#include "includes.h"

#include "common.h"
#include "crypto.h"

#include "mbedtls/md5.h"
#include "mbedtls/des.h"

#include "mbedtls/sha1.h"
#include "mbedtls/sha256.h"
#if defined(MBEDTLS_SHA512_C)
#include "mbedtls/sha512.h"
#endif
#include "mbedtls/pkcs5.h"

#include "mbedtls/aes.h"
#include "mbedtls/rsa.h"
#if (MBEDTLS_VERSION_MAJOR < 3)
#include "mbedtls/md4.h"
#include "mbedtls/arc4.h"
#endif

#include "mbedtls/oid.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/x509_csr.h"
#include "mbedtls/pkcs7.h"
#include "mbedtls/pem.h"

#include "system.h"
#include "platform.h"

#include "system_common.h"

#if defined(CONFIG_ECC)
#include "random.h"

#include "mbedtls/ecp.h"

#include "mbedtls/pk.h"
#include "mbedtls/ecdh.h"
#include "mbedtls/asn1write.h"
#include "mbedtls/error.h"

#include "mbedtls/bignum.h"

#define ECP_PRV_DER_MAX_BYTES   ( 29 + 3 * MBEDTLS_ECP_MAX_BYTES )
#define ECP_PUB_DER_MAX_BYTES   ( 30 + 2 * MBEDTLS_ECP_MAX_BYTES )

#ifdef CONFIG_MBEDTLS_ECDH_LEGACY_CONTEXT
#define ACCESS_ECDH(S, var) S->MBEDTLS_PRIVATE(var)
#else
#define ACCESS_ECDH(S, var) S->MBEDTLS_PRIVATE(ctx).MBEDTLS_PRIVATE(mbed_ecdh).MBEDTLS_PRIVATE(var)
#endif

//Print Elapsed time for ECC Proceeing for SAE/OWE/DPP for debug
#define DEBUG_ECC_PROCESS_TIME 1

#if DEBUG_ECC_PROCESS_TIME //For Debug
#include "hal_lmac_register.h"
#define TSF     (*(volatile uint32_t*)(MAC_REG_TSF_0_LOWER_READONLY))
static void _wpa_msg_crypto(void *ctx, int level, const char *fmt, ...)
{
	va_list ap;
	if (level >= wpa_debug_level) {
		va_start(ap, fmt);
		system_vprintf(fmt, ap);
		system_printf("\n");
		va_end(ap);
	}
}
#endif //DEBUG_ECC_PROCESS_TIME

#endif //#if defined(CONFIG_ECC)

#ifdef TAG
#undef TAG
#endif
#define TAG "tls: "

#ifndef PUT_UINT32_BE
#define PUT_UINT32_BE(n,b,i)                            \
{                                                       \
    (b)[(i)    ] = (unsigned char) ( (n) >> 24 );       \
    (b)[(i) + 1] = (unsigned char) ( (n) >> 16 );       \
    (b)[(i) + 2] = (unsigned char) ( (n) >>  8 );       \
    (b)[(i) + 3] = (unsigned char) ( (n)       );       \
}
#endif


static int mbedtls_hmac_vector(mbedtls_md_type_t type, const u8 *key,
			size_t key_len, size_t num_elem, const u8 *addr[],
			const size_t *len, u8 *mac)
{
	mbedtls_md_context_t ctx;
	size_t i;
	int res = 0;

	wpa_printf(MSG_ERROR, TAG "%s\n", __func__);
	mbedtls_md_init(&ctx);
	if (mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(type), 1) != 0)
		res = -1;

	if (res == 0 && mbedtls_md_hmac_starts(&ctx, key, key_len) != 0)
		res = -1;

	for (i = 0; res == 0 && i < num_elem; i++)
		res = mbedtls_md_hmac_update(&ctx, addr[i], len[i]);

	if (res == 0)
		res = mbedtls_md_hmac_finish(&ctx, mac);
	mbedtls_md_free(&ctx);

	wpa_printf(MSG_ERROR, TAG "ret - %d\n", res);
	return res == 0 ? 0 : -1;
}

int hmac_sha1_vector(const u8 *key, size_t key_len, size_t num_elem,
		     const u8 *addr[], const size_t *len, u8 *mac)
{
	return mbedtls_hmac_vector(MBEDTLS_MD_SHA1, key, key_len, num_elem, addr,
				len, mac);
}


int hmac_sha1(const u8 *key, size_t key_len, const u8 *data, size_t data_len,
	      u8 *mac)
{
	wpa_printf(MSG_ERROR, TAG "%s\n", __func__);
	return hmac_sha1_vector(key, key_len, 1, &data, &data_len, mac);
}
int pbkdf2_sha1(const char *passphrase, const u8 *ssid, size_t ssid_len,
		int iterations, u8 *buf, size_t buflen)
{
	mbedtls_md_context_t md;
	const mbedtls_md_info_t *info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA1);
	int res = 0;
	uint32_t B_T, A_T;

	wpa_printf(MSG_ERROR, TAG "%s\n", __func__);
	mbedtls_md_init(&md);
	if (mbedtls_md_setup(&md, info, 1) == 0)
	{
		A("[pbkdf2_sha1] Enter TSF : %d\n", B_T=TSF);
		res = mbedtls_pkcs5_pbkdf2_hmac(&md,
				(const unsigned char *) passphrase, os_strlen(passphrase),
				ssid, ssid_len, iterations, buflen, buf);

		A("[pbkdf2_sha1] Exit  TSF : %d\n", A_T=TSF);
		A("[pbkdf2_sha1] op time   : %d, buflen : %d\n", A_T-B_T, buflen);
	}
	mbedtls_md_free(&md);

	return res == 0 ? 0 : -1;
}


int des_encrypt(const u8 *clear, const u8 *key, u8 *cypher)
{
	int ret;
	mbedtls_des_context ctx;
	u8 pkey[8], next, tmp;
	int i;

	/* Add parity bits to the key */
	next = 0;
	for (i = 0; i < 7; i++) {
		tmp = key[i];
		pkey[i] = (tmp >> i) | next | 1;
		next = tmp << (7 - i);
	}
	pkey[i] = next | 1;

	mbedtls_des_init(&ctx);
	ret = mbedtls_des_setkey_enc(&ctx, pkey);
	if (ret < 0) {
		return ret;
	}
	ret = mbedtls_des_crypt_ecb(&ctx, clear, cypher);
	mbedtls_des_free(&ctx);

	return ret;
}

int md5_vector(size_t num_elem, const u8 *addr[], const size_t *len, u8 *mac)
{
	mbedtls_md5_context ctx;
	size_t i;

	mbedtls_md5_init(&ctx);
	mbedtls_md5_starts(&ctx);

	for (i = 0; i < num_elem; ++i)
		mbedtls_md5_update(&ctx, addr[i], len[i]);

	mbedtls_md5_finish(&ctx, mac);
	mbedtls_md5_free(&ctx);

	return 0;
}

int hmac_md5_vector(const u8 *key, size_t key_len, size_t num_elem,
		    const u8 *addr[], const size_t *len, u8 *mac)
{
	return mbedtls_hmac_vector(MBEDTLS_MD_MD5, key, key_len, num_elem, addr,
				len, mac);
}


int hmac_md5(const u8 *key, size_t key_len, const u8 *data, size_t data_len,
	     u8 *mac)
{
	return hmac_md5_vector(key, key_len, 1, &data, &data_len, mac);
}

int sha1_vector(size_t num_elem, const u8 *addr[], const size_t *len, u8 *mac)
{
	mbedtls_sha1_context ctx;
	size_t i;

	mbedtls_sha1_init(&ctx);
	mbedtls_sha1_starts(&ctx);

	for (i = 0; i < num_elem; ++i)
		mbedtls_sha1_update(&ctx, addr[i], len[i]);

	mbedtls_sha1_finish(&ctx, mac);
	mbedtls_sha1_free(&ctx);

	return 0;
}

int sha256_vector(size_t num_elem, const u8 *addr[], const size_t *len, u8 *mac)
{
	mbedtls_sha256_context ctx;
	size_t i;

	mbedtls_sha256_init(&ctx);
	mbedtls_sha256_starts(&ctx, 0 /*use SHA256*/);

	for (i = 0; i < num_elem; ++i)
		mbedtls_sha256_update(&ctx, addr[i], len[i]);

	mbedtls_sha256_finish(&ctx, mac);
	mbedtls_sha256_free(&ctx);

	return 0;
}

int sha512_vector(size_t num_elem, const u8 *addr[], const size_t *len, u8 *mac)
{
	mbedtls_sha512_context ctx;
	size_t i;

	mbedtls_sha512_init(&ctx);
	mbedtls_sha512_starts(&ctx, 0 /*use SHA512*/);

	for (i = 0; i < num_elem; ++i)
		mbedtls_sha512_update(&ctx, addr[i], len[i]);

	mbedtls_sha512_finish(&ctx, mac);
	mbedtls_sha512_free(&ctx);

	return 0;
}

int sha384_vector(size_t num_elem, const u8 *addr[], const size_t *len, u8 *mac)
{
	mbedtls_sha512_context ctx;
	size_t i;

	mbedtls_sha512_init(&ctx);
	mbedtls_sha512_starts(&ctx, 1 /*use SHA384*/);

	for (i = 0; i < num_elem; ++i)
		mbedtls_sha512_update(&ctx, addr[i], len[i]);

	mbedtls_sha512_finish(&ctx, mac);
	mbedtls_sha512_free(&ctx);

	return 0;
}

int md4_vector(size_t num_elem, const u8 *addr[], const size_t *len, u8 *mac)
{
#if (MBEDTLS_VERSION_MAJOR >= 3)
	return -1;
#else
	mbedtls_md4_context ctx;
	size_t i;

	mbedtls_md4_init(&ctx);
	mbedtls_md4_starts(&ctx);

	for (i = 0; i < num_elem; ++i)
		mbedtls_md4_update(&ctx, addr[i], len[i]);

	mbedtls_md4_finish(&ctx, mac);
	mbedtls_md4_free(&ctx);

	return 0;
#endif
}


int hmac_sha384_vector(const u8 *key, size_t key_len, size_t num_elem,
		const u8 *addr[], const size_t *len, u8 *mac)
{
	return mbedtls_hmac_vector(MBEDTLS_MD_SHA384, key, key_len, num_elem, addr,
				   len, mac);
}


int hmac_sha384(const u8 *key, size_t key_len, const u8 *data,
		size_t data_len, u8 *mac)
{
	return hmac_sha384_vector(key, key_len, 1, &data, &data_len, mac);
}

int hmac_sha512_vector(const u8 *key, size_t key_len, size_t num_elem,
		const u8 *addr[], const size_t *len, u8 *mac)
{
	return mbedtls_hmac_vector(MBEDTLS_MD_SHA512, key, key_len, num_elem, addr,
				   len, mac);
}


int hmac_sha512(const u8 *key, size_t key_len, const u8 *data,
		size_t data_len, u8 *mac)
{
	return hmac_sha512_vector(key, key_len, 1, &data, &data_len, mac);
}

void * aes_encrypt_init(const u8 *key, size_t len)
{
	mbedtls_aes_context *ctx = os_zalloc(sizeof(*ctx));

	mbedtls_aes_init(ctx);

	if (mbedtls_aes_setkey_enc(ctx, key, len * 8) == 0)
		return ctx;

	os_free(ctx);

	return NULL;
}


int aes_encrypt(void *ctx, const u8 *plain, u8 *crypt)
{
	if (ctx)
		mbedtls_aes_crypt_ecb(ctx, MBEDTLS_AES_ENCRYPT, plain, crypt);
	else
		return -1;

	return 0;
}


void aes_encrypt_deinit(void *ctx)
{
	if (ctx) {
		mbedtls_aes_free(ctx);
		os_free(ctx);
		ctx = NULL;
	}
}

void * aes_decrypt_init(const u8 *key, size_t len)
{
	mbedtls_aes_context *ctx = os_zalloc(sizeof(*ctx));

	mbedtls_aes_init(ctx);

	if (mbedtls_aes_setkey_dec(ctx, key, len * 8) == 0)
		return ctx;

	os_free(ctx);

	return NULL;
}

int aes_decrypt(void *ctx, const u8 *crypt, u8 *plain)
{
	if (!ctx)
		return -1;

	mbedtls_aes_crypt_ecb(ctx, MBEDTLS_AES_DECRYPT, crypt, plain);
	return 0;
}

void aes_decrypt_deinit(void *ctx)
{
	if (ctx) {
		mbedtls_aes_free(ctx);
		os_free(ctx);
		ctx = NULL;
	}
}

int crypto_mod_exp(const u8 *base, size_t base_len,
		   const u8 *power, size_t power_len,
		   const u8 *modulus, size_t modulus_len,
		   u8 *result, size_t *result_len)
{
	mbedtls_mpi mpi_prime, mpi_gen, key_private, mpi_res;
	// unsigned long flags = system_irq_save();

	mbedtls_mpi_init(&key_private);
	mbedtls_mpi_init(&mpi_prime);      
	mbedtls_mpi_init(&mpi_gen);
	mbedtls_mpi_init(&mpi_res);

	mbedtls_mpi_read_binary(&mpi_gen, base, base_len);				//Generator
	mbedtls_mpi_read_binary(&key_private, power, power_len);		//Private Key
	mbedtls_mpi_read_binary(&mpi_prime, modulus, modulus_len);		//Prime Number

	if(mbedtls_mpi_exp_mod(&mpi_res, &mpi_gen, &key_private, &mpi_prime, NULL) != 0)
		return -1;

	*result_len = mbedtls_mpi_size(&mpi_res);
	if (mbedtls_mpi_write_binary(&mpi_res, result, *result_len) != 0)
		return -1;

	mbedtls_mpi_free(&key_private);
	mbedtls_mpi_free(&mpi_prime);
	mbedtls_mpi_free(&mpi_gen);
	mbedtls_mpi_free(&mpi_res);

	// system_irq_restore(flags);
	return 0;
}

struct crypto_cipher {
	enum crypto_cipher_alg alg;
	union {
#if (MBEDTLS_VERSION_MAJOR < 3)
		mbedtls_arc4_context *arc4_ctx;
#endif
		mbedtls_aes_context *aes_ctx;
		struct _des{
			mbedtls_des_context *dec_ctx;
			mbedtls_des_context *enc_ctx;
		} des;
		struct _des3 {
			mbedtls_des3_context *dec_ctx;
			mbedtls_des3_context *enc_ctx;
		} des3;
		mbedtls_rsa_context *rsa_ctx;
	}u;
};

struct crypto_cipher * crypto_cipher_init(enum crypto_cipher_alg alg,
					  const u8 *iv, const u8 *key,
					  size_t key_len)
{
	struct crypto_cipher *ctx = os_zalloc(sizeof(*ctx));

	if (!ctx)
		return NULL;

	switch (alg) {
#if (MBEDTLS_VERSION_MAJOR < 3)
	case CRYPTO_CIPHER_ALG_RC4:
	ctx->alg = CRYPTO_CIPHER_ALG_RC4;
	ctx->u.arc4_ctx = os_zalloc(sizeof(*ctx->u.arc4_ctx));
	mbedtls_arc4_setup(ctx->u.arc4_ctx, key, key_len);
	break;
#endif
	case CRYPTO_CIPHER_ALG_AES:
	ctx->alg = CRYPTO_CIPHER_ALG_AES;
	ctx->u.aes_ctx = os_zalloc(sizeof(*ctx->u.aes_ctx));
	mbedtls_aes_init(ctx->u.aes_ctx);
	mbedtls_aes_setkey_enc(ctx->u.aes_ctx, key, key_len * 8);
	break;
	case CRYPTO_CIPHER_ALG_3DES:
	ctx->alg = CRYPTO_CIPHER_ALG_3DES;
	ctx->u.des3.enc_ctx = os_zalloc(sizeof(*ctx->u.des3.enc_ctx));
	ctx->u.des3.dec_ctx = os_zalloc(sizeof(*ctx->u.des3.dec_ctx));
	mbedtls_des3_set2key_enc(ctx->u.des3.enc_ctx, key);
	mbedtls_des3_set2key_dec(ctx->u.des3.dec_ctx, key);
	break;
	case CRYPTO_CIPHER_ALG_DES:
	ctx->alg = CRYPTO_CIPHER_ALG_DES;
	ctx->u.des.dec_ctx = os_zalloc(sizeof(*ctx->u.des.dec_ctx));
	ctx->u.des.enc_ctx = os_zalloc(sizeof(*ctx->u.des.enc_ctx));
	mbedtls_des_setkey_enc(ctx->u.des.enc_ctx, key);
	mbedtls_des_setkey_dec(ctx->u.des.dec_ctx, key);
	break;
	case CRYPTO_CIPHER_ALG_RC2:
	ctx->alg = CRYPTO_CIPHER_ALG_RC2;
	return NULL;
	case CRYPTO_CIPHER_NULL:
	ctx->alg = CRYPTO_CIPHER_NULL;
	break;
	default:
		os_free(ctx);
		return NULL;
	}

	return ctx;
}

int crypto_cipher_encrypt(struct crypto_cipher *ctx, const u8 *plain,
			  u8 *crypt, size_t len)
{
	if (!ctx)
		return -1;

	switch (ctx->alg) {
#if (MBEDTLS_VERSION_MAJOR < 3)
		case CRYPTO_CIPHER_ALG_RC4:
		mbedtls_arc4_crypt(ctx->u.arc4_ctx, len, plain, crypt);
		break;
#endif
		case CRYPTO_CIPHER_ALG_AES:
		mbedtls_aes_crypt_ecb(ctx->u.aes_ctx, MBEDTLS_AES_ENCRYPT, plain, crypt);
		break;
		case CRYPTO_CIPHER_ALG_3DES:
		mbedtls_des3_crypt_ecb(ctx->u.des3.enc_ctx, plain, crypt);
		break;
		case CRYPTO_CIPHER_ALG_DES:
		mbedtls_des_crypt_ecb(ctx->u.des.enc_ctx, plain, crypt);
		break;
		case CRYPTO_CIPHER_ALG_RC2:
		break;
		case CRYPTO_CIPHER_NULL:
		break;
		default:
		return -1;
	}

	return 0;
}

int crypto_cipher_decrypt(struct crypto_cipher *ctx, const u8 *crypt,
			  u8 *plain, size_t len)
{
	if (!ctx)
		return -1;

	switch (ctx->alg) {
#if (MBEDTLS_VERSION_MAJOR < 3)
		case CRYPTO_CIPHER_ALG_RC4:
		mbedtls_arc4_crypt(ctx->u.arc4_ctx, len, crypt, plain);
		break;
#endif
		case CRYPTO_CIPHER_ALG_AES:
		mbedtls_aes_crypt_ecb(ctx->u.aes_ctx, MBEDTLS_AES_DECRYPT, crypt, plain);
		break;
		case CRYPTO_CIPHER_ALG_3DES:
		mbedtls_des3_crypt_ecb(ctx->u.des3.dec_ctx, crypt, plain);
		break;
		case CRYPTO_CIPHER_ALG_DES:
		mbedtls_des_crypt_ecb(ctx->u.des.dec_ctx, crypt, plain);
		break;
		case CRYPTO_CIPHER_ALG_RC2:
		break;
		case CRYPTO_CIPHER_NULL:
		break;
		default:
		return -1;
	}

	return 0;
}

void crypto_cipher_deinit(struct crypto_cipher *ctx)
{
	if (!ctx)
		return;

	switch (ctx->alg) {
#if (MBEDTLS_VERSION_MAJOR < 3)
		case CRYPTO_CIPHER_ALG_RC4:
		mbedtls_arc4_free(ctx->u.arc4_ctx);
		os_free(ctx->u.arc4_ctx);
		break;
#endif
		case CRYPTO_CIPHER_ALG_AES:
		mbedtls_aes_free(ctx->u.aes_ctx);
		os_free(ctx->u.aes_ctx);
		break;
		case CRYPTO_CIPHER_ALG_3DES:
		mbedtls_des3_free(ctx->u.des3.enc_ctx);
		mbedtls_des3_free(ctx->u.des3.dec_ctx);
		os_free(ctx->u.des3.dec_ctx);
		os_free(ctx->u.des3.enc_ctx);
		break;
		case CRYPTO_CIPHER_ALG_DES:
		mbedtls_des_free(ctx->u.des.enc_ctx);
		mbedtls_des_free(ctx->u.des.dec_ctx);
		os_free(ctx->u.des.enc_ctx);
		os_free(ctx->u.des.dec_ctx);
		break;
		case CRYPTO_CIPHER_ALG_RC2:
		break;
		case CRYPTO_CIPHER_NULL:
		break;
		default:
		break;
	}
	os_free(ctx);
	ctx = NULL;
}

/**
 * aes_128_cbc_encrypt - AES-128 CBC encryption
 * @key: Encryption key
 * @iv: Encryption IV for CBC mode (16 bytes)
 * @data: Data to encrypt in-place
 * @data_len: Length of data in bytes (must be divisible by 16)
 * Returns: 0 on success, -1 on failure
 */
int aes_128_cbc_encrypt(const u8 *key, const u8 *iv, u8 *data, size_t data_len)
{
	mbedtls_aes_context ctx;
	mbedtls_aes_init(&ctx);
	u8 iv2[16] = {0,};
	os_memcpy(iv2, iv, 16);

	if (mbedtls_aes_setkey_enc(&ctx, key, 128) != 0) {
		wpa_printf(MSG_ERROR, "mbedtls_aes_setkey_enc error! ");
		return -1;
	}
	mbedtls_aes_crypt_cbc(&ctx, MBEDTLS_AES_ENCRYPT, data_len, iv2, data, data);
	mbedtls_aes_free(&ctx);

	return 0;
}

int aes_128_cbc_decrypt(const u8 *key, const u8 *iv, u8 *data, size_t data_len)
{
	mbedtls_aes_context ctx;
	mbedtls_aes_init(&ctx);
	u8 iv2[16] = {0,};
	os_memcpy(iv2, iv, 16);

	if (mbedtls_aes_setkey_dec(&ctx, key, 128) != 0) {
		wpa_printf(MSG_ERROR, "mbedtls_aes_setkey_dec error! ");
		return -1;
	}
	mbedtls_aes_crypt_cbc(&ctx, MBEDTLS_AES_DECRYPT, data_len, iv2, data, data);
	mbedtls_aes_free(&ctx);

	return 0;
}

#define S_SWAP(a,b) do { u8 t = S[a]; S[a] = S[b]; S[b] = t; } while(0)

/**
 * TODO: Could not find any code on mbedtls
 */
int rc4_skip(const u8 *key, size_t keylen, size_t skip,
	     u8 *data, size_t data_len)
{
	u32 i, j, k;
	u8 S[256], *pos;
	size_t kpos;
	wpa_printf(MSG_ERROR, "%s", __func__);

	/* Setup RC4 state */
	for (i = 0; i < 256; i++)
		S[i] = i;
	j = 0;
	kpos = 0;
	for (i = 0; i < 256; i++) {
		j = (j + S[i] + key[kpos]) & 0xff;
		kpos++;
		if (kpos >= keylen)
			kpos = 0;
		S_SWAP(i, j);
	}

	/* Skip the start of the stream */
	i = j = 0;
	for (k = 0; k < skip; k++) {
		i = (i + 1) & 0xff;
		j = (j + S[i]) & 0xff;
		S_SWAP(i, j);
	}

	/* Apply RC4 to data */
	pos = data;
	for (k = 0; k < data_len; k++) {
		i = (i + 1) & 0xff;
		j = (j + S[i]) & 0xff;
		S_SWAP(i, j);
		*pos++ ^= S[(S[i] + S[j]) & 0xff];
	}

	return 0;
}

#if defined(CONFIG_ECC)
struct crypto_ec {
	mbedtls_ecp_group group;
};

struct crypto_ecdh {
	mbedtls_ecdh_context ctx;
	size_t length;
};

static mbedtls_ecp_group_id get_ecp_group_id(int id)
{
	mbedtls_ecp_group_id grp_id = MBEDTLS_ECP_DP_NONE;

	switch (id) {
	case 19:
		grp_id = MBEDTLS_ECP_DP_SECP256R1;
		break;
	case 20:
		grp_id = MBEDTLS_ECP_DP_SECP384R1;
		break;
	case 21:
		grp_id = MBEDTLS_ECP_DP_SECP521R1;
		break;
	case 25:
		grp_id = MBEDTLS_ECP_DP_SECP192R1;
		break;
	case 26:
		grp_id = MBEDTLS_ECP_DP_SECP224R1;
		break;
	case 27:
        ///////////////???
		break;
	case 28:
		grp_id = MBEDTLS_ECP_DP_BP256R1;
		break;
	case 29:
		grp_id = MBEDTLS_ECP_DP_BP384R1;
		break;
	case 30:
		grp_id = MBEDTLS_ECP_DP_BP512R1;
		break;
	default:	
		wpa_msg(0, MSG_ERROR, "ECC : [%s, %d] Selected group is not available.\n", __func__, __LINE__);
	}

	return grp_id;
}

unsigned int crypto_ec_get_mbedtls_to_nist_group_id(int id)
{
	unsigned int nist_grpid = 0;
	switch (id) {
	case MBEDTLS_ECP_DP_SECP256R1:
		nist_grpid = 19;
		break;
	case MBEDTLS_ECP_DP_SECP384R1:
		nist_grpid = 20;
		break;
	case MBEDTLS_ECP_DP_SECP521R1:
		nist_grpid = 21;
		break;
	case MBEDTLS_ECP_DP_SECP192R1:
		nist_grpid = 25;
		break;
	case MBEDTLS_ECP_DP_SECP224R1:
		nist_grpid = 26;
		break;
	case MBEDTLS_ECP_DP_BP256R1:
		nist_grpid = 28;
		break;
	case MBEDTLS_ECP_DP_BP384R1:
		nist_grpid = 29;
		break;
	case MBEDTLS_ECP_DP_BP512R1:
		nist_grpid = 30;
		break;
	default:
		break;
	}

	return nist_grpid;
}

struct crypto_ec *crypto_ec_init(int group)
{
	struct crypto_ec *e;

	mbedtls_ecp_group_id  grp_id;

	/* IANA registry to mbedtls internal mapping*/
	grp_id = get_ecp_group_id(group);

	e = os_zalloc(sizeof(*e));
	if (e == NULL) {
		return NULL;
	}

	mbedtls_ecp_group_init(&e->group);

	if (mbedtls_ecp_group_load(&e->group, grp_id)) {
		crypto_ec_deinit(e);
		e = NULL;
	}

	return e;
}

void crypto_ec_deinit(struct crypto_ec *e)
{
	if (e == NULL) {
		return;
	}

	mbedtls_ecp_group_free(&e->group);
	os_free(e);
}

const struct crypto_bignum *crypto_ec_get_prime(struct crypto_ec *e)
{
	return (const struct crypto_bignum *) &e->group.P;
}

size_t crypto_ec_prime_len(struct crypto_ec *e)
{
	return mbedtls_mpi_size(&e->group.P);
}

size_t crypto_ec_prime_len_bits(struct crypto_ec *e)
{
	return mbedtls_mpi_bitlen(&e->group.P);
}

const struct crypto_bignum *crypto_ec_get_order(struct crypto_ec *e)
{
	return (const struct crypto_bignum *) &e->group.N;
}

size_t crypto_ec_order_len(struct crypto_ec *e)
{
	return mbedtls_mpi_size(&e->group.N);
}

struct crypto_ec_point *crypto_ec_point_init(struct crypto_ec *e)
{
	mbedtls_ecp_point *pt;
	if (e == NULL) {
		return NULL;
	}

	pt = os_zalloc(sizeof(mbedtls_ecp_point));

	if( pt == NULL) {
		return NULL;
	}

	mbedtls_ecp_point_init(pt);

	return (struct crypto_ec_point *) pt;
}

const struct crypto_ec_point *crypto_ec_get_generator(struct crypto_ec *e)
{
	return (const struct crypto_ec_point *) &e->group.G;
}

void crypto_ec_point_deinit(struct crypto_ec_point *p, int clear)
{
	mbedtls_ecp_point_free((mbedtls_ecp_point *) p);
	os_free(p);
}

int crypto_ec_point_x(struct crypto_ec *e, const struct crypto_ec_point *p,
		      struct crypto_bignum *x)
{
	return mbedtls_mpi_copy((mbedtls_mpi*) x, &((mbedtls_ecp_point* )p)->MBEDTLS_PRIVATE(X));
}

int crypto_ec_point_to_bin(struct crypto_ec *e,
		const struct crypto_ec_point *point, u8 *x, u8 *y)
{
	int len = mbedtls_mpi_size(&e->group.P);

	if (x) {
		if(crypto_bignum_to_bin((struct crypto_bignum *) & ((mbedtls_ecp_point *) point)->MBEDTLS_PRIVATE(X),
					x, len, len) < 0) {
			return -1;
		}

	}

	if (y) {
		if(crypto_bignum_to_bin((struct crypto_bignum *) & ((mbedtls_ecp_point *) point)->MBEDTLS_PRIVATE(Y),
					y, len, len) < 0) {
			return -1;
		}
	}

	return 0;
}

struct crypto_ec_point *crypto_ec_point_from_bin(struct crypto_ec *e,
		const u8 *val)
{
	mbedtls_ecp_point *pt;
	int len, ret;

	if (e == NULL) {
		return NULL;
	}

	len = mbedtls_mpi_size(&e->group.P);

	pt = os_zalloc(sizeof(mbedtls_ecp_point));
	mbedtls_ecp_point_init(pt);

	MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&pt->MBEDTLS_PRIVATE(X), val, len));
	MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&pt->MBEDTLS_PRIVATE(Y), val + len, len));
	MBEDTLS_MPI_CHK(mbedtls_mpi_lset((&pt->MBEDTLS_PRIVATE(Z)), 1));

	return (struct crypto_ec_point *) pt;

cleanup:
	mbedtls_ecp_point_free(pt);
	os_free(pt);
	return NULL;
}

int crypto_ec_point_add(struct crypto_ec *e, const struct crypto_ec_point *a,
		const struct crypto_ec_point *b,
		struct crypto_ec_point *c)
{
	int ret;
	mbedtls_mpi one;

	mbedtls_mpi_init(&one);

	MBEDTLS_MPI_CHK(mbedtls_mpi_lset( &one, 1 ));
	MBEDTLS_MPI_CHK(mbedtls_ecp_muladd(&e->group, (mbedtls_ecp_point *) c, &one, (const mbedtls_ecp_point *)a , &one, (const mbedtls_ecp_point *)b));

cleanup:
	mbedtls_mpi_free(&one);
	return ret ? -1 : 0;
}

int crypto_ec_point_mul(struct crypto_ec *e, const struct crypto_ec_point *p,
		const struct crypto_bignum *b,
		struct crypto_ec_point *res)
{
	int ret;
	mbedtls_entropy_context entropy;
	mbedtls_ctr_drbg_context ctr_drbg;

#if DEBUG_ECC_PROCESS_TIME //For Debug
	unsigned int ptime, ctime;
	ptime = TSF;
	_wpa_msg_crypto(NULL, MSG_DEBUG, TAG "[Enter] crypto_ec_point_mul");
#endif

	mbedtls_entropy_init(&entropy);
	mbedtls_ctr_drbg_init(&ctr_drbg);

	MBEDTLS_MPI_CHK(mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy,
				NULL, 0));

	MBEDTLS_MPI_CHK(mbedtls_ecp_mul(&e->group,
				(mbedtls_ecp_point *) res,
				(const mbedtls_mpi *)b,
				(const mbedtls_ecp_point *)p,
				mbedtls_ctr_drbg_random,
				&ctr_drbg));

cleanup:
	mbedtls_ctr_drbg_free(&ctr_drbg);
	mbedtls_entropy_free(&entropy);

#if DEBUG_ECC_PROCESS_TIME //For Debug
	ctime = TSF;
	_wpa_msg_crypto(NULL, MSG_DEBUG, TAG "[Exit ] crypto_ec_point_mul (elapsed time: %u us)",
			(ctime -ptime));
#endif

	return ret ? -1 : 0;
}

/*  Currently mbedtls does not have any function for inverse
 *  This function calculates inverse of a point.
 *  Set R = -P
 */
static int ecp_opp(const mbedtls_ecp_group *grp, mbedtls_ecp_point *R, const mbedtls_ecp_point *P)
{
	int ret = 0;

	/* Copy */
	if (R != P) {
		MBEDTLS_MPI_CHK(mbedtls_ecp_copy(R, P));
	}

	/* In-place opposite */
	if (mbedtls_mpi_cmp_int(&R->MBEDTLS_PRIVATE(Y), 0) != 0) {
		MBEDTLS_MPI_CHK(mbedtls_mpi_sub_mpi(&R->MBEDTLS_PRIVATE(Y), &grp->P, &R->MBEDTLS_PRIVATE(Y)));
	}

cleanup:
	return (ret );
}

int crypto_ec_point_invert(struct crypto_ec *e, struct crypto_ec_point *p)
{
	return ecp_opp(&e->group, (mbedtls_ecp_point *) p, (mbedtls_ecp_point *) p) ? -1 : 0;
}

int crypto_ec_point_cmp(const struct crypto_ec *e,
		const struct crypto_ec_point *a,
		const struct crypto_ec_point *b)
{
	return mbedtls_ecp_point_cmp((const mbedtls_ecp_point *) a,
			(const mbedtls_ecp_point *) b);
}

void crypto_ec_point_debug_print(const struct crypto_ec *e,
				 const struct crypto_ec_point *p,
				 const char *title)
{
	mbedtls_ecp_point *pt = (mbedtls_ecp_point *) p;
	wpa_printf(MSG_DEBUG, "%s", title);
	if (MSG_DEBUG >= wpa_debug_level) {
		bignum_print("X", &pt->MBEDTLS_PRIVATE(X));
		bignum_print("Y", &pt->MBEDTLS_PRIVATE(Y));
	}
}

struct crypto_bignum *crypto_ec_point_compute_y_sqr(struct crypto_ec *e,
		const struct crypto_bignum *x)
{
	int ret = 0;

	mbedtls_mpi *Y = os_zalloc(sizeof(mbedtls_mpi));
	if (Y == NULL) {
		return NULL;
	}

	mbedtls_mpi_init(Y);
	struct crypto_bignum *y_sqr = (struct crypto_bignum *) Y;

	/* Compute X^3 + A X + B as X (X^2 + A) + B */
	MBEDTLS_MPI_CHK(crypto_bignum_mulmod(x, x,
		(const struct crypto_bignum *) &e->group.P,
		y_sqr));

	/* Special case for A = -3 */
	if (e->group.A.MBEDTLS_PRIVATE(p) == NULL) {
		MBEDTLS_MPI_CHK(mbedtls_mpi_sub_int(Y, Y, 3));
		while (Y->MBEDTLS_PRIVATE(s) < 0 && mbedtls_mpi_cmp_int(Y, 0) != 0)
			MBEDTLS_MPI_CHK(mbedtls_mpi_add_mpi(Y, Y, &e->group.P));
	} else {
		MBEDTLS_MPI_CHK(crypto_bignum_addmod(y_sqr,
		(const struct crypto_bignum *) &e->group.A,
		(const struct crypto_bignum *) &e->group.P,
		y_sqr));
	}

	MBEDTLS_MPI_CHK(crypto_bignum_mulmod(y_sqr, x,
		(const struct crypto_bignum *) &e->group.P,
		y_sqr));
	MBEDTLS_MPI_CHK(crypto_bignum_addmod(y_sqr,
		(const struct crypto_bignum *) &e->group.B,
		(const struct crypto_bignum *) &e->group.P,
		y_sqr));

cleanup:
	if (ret) {
		mbedtls_mpi_free(Y);
		os_free(Y);
		return NULL;
	} else {
		return y_sqr;
	}
}

int crypto_ec_point_solve_y_coord(struct crypto_ec *e,
		struct crypto_ec_point *p,
		const struct crypto_bignum *x, int y_bit)
{
	mbedtls_mpi temp;
	mbedtls_mpi *y_sqr, *y;
	mbedtls_mpi_init(&temp);
	int ret = 0;

	y = &((mbedtls_ecp_point *)p)->MBEDTLS_PRIVATE(Y);

	/* Faster way to find sqrt
	 * Works only with curves having prime p
	 * such that p ≡ 3 (mod 4)
	 *  y_ = (y2 ^ ((p+1)/4)) mod p
	 *
	 *  if LSB of both x and y are same: y = y_
	 *   else y = p - y_
	 * y_bit is LSB of x
	 */
	y_bit = (y_bit != 0);

	y_sqr = (mbedtls_mpi *) crypto_ec_point_compute_y_sqr(e, x);

	if (y_sqr) {
		MBEDTLS_MPI_CHK(mbedtls_mpi_add_int(&temp, &e->group.P, 1));
		MBEDTLS_MPI_CHK(mbedtls_mpi_shift_r(&temp, 2));
		MBEDTLS_MPI_CHK(mbedtls_mpi_exp_mod(y, y_sqr, &temp, &e->group.P, NULL));

		if (y_bit != mbedtls_mpi_get_bit(y, 0))
			MBEDTLS_MPI_CHK(mbedtls_mpi_sub_mpi(y, &e->group.P, y));

		MBEDTLS_MPI_CHK(mbedtls_mpi_copy(&((mbedtls_ecp_point* )p)->MBEDTLS_PRIVATE(X), (const mbedtls_mpi*) x));
		MBEDTLS_MPI_CHK(mbedtls_mpi_lset(&((mbedtls_ecp_point *)p)->MBEDTLS_PRIVATE(Z), 1));
	} else {
		ret = 1;
	}
cleanup:
	mbedtls_mpi_free(&temp);
	mbedtls_mpi_free(y_sqr);
	os_free(y_sqr);
	return ret ? -1 : 0;
}

int crypto_ec_point_is_at_infinity(struct crypto_ec *e,
		const struct crypto_ec_point *p)
{
	return mbedtls_ecp_is_zero((mbedtls_ecp_point *) p);
}
        
int crypto_ec_point_is_on_curve(struct crypto_ec *e,
		const struct crypto_ec_point *p)
{
	mbedtls_mpi y_sqr_lhs, *y_sqr_rhs = NULL, two;
	int ret = 0, on_curve = 0;

	mbedtls_mpi_init(&y_sqr_lhs);

	/* Calculate y^2  mod P*/
#if defined(INCLUDE_HW_SECURITY_ACC_BN) && defined(INCLUDE_HW_SECURITY_ACC_BN_MUL_MOD)
	if (e->group.pbits / 8 / sizeof(mbedtls_mpi_uint) >= 16) {
		mbedtls_mpi_init(&two);
		MBEDTLS_MPI_CHK(mbedtls_mpi_lset(&two, 2));
		MBEDTLS_MPI_CHK(mbedtls_mpi_exp_mod(&y_sqr_lhs, &((const mbedtls_ecp_point *)p)->MBEDTLS_PRIVATE(Y), &two, &e->group.P, NULL));
		mbedtls_mpi_free(&two);
	} else {
		MBEDTLS_MPI_CHK(mbedtls_mpi_mul_mpi_mod_mpi(&y_sqr_lhs,
			&((const mbedtls_ecp_point *)p)->MBEDTLS_PRIVATE(Y),
			&((const mbedtls_ecp_point *)p)->MBEDTLS_PRIVATE(Y),
			&e->group.P));
	}
#else
	mbedtls_mpi_init(&two);
	MBEDTLS_MPI_CHK(mbedtls_mpi_lset(&two, 2));
	MBEDTLS_MPI_CHK(mbedtls_mpi_exp_mod(&y_sqr_lhs, &((const mbedtls_ecp_point *)p)->MBEDTLS_PRIVATE(Y), &two, &e->group.P, NULL));
	mbedtls_mpi_free(&two);
#endif /* INCLUDE_HW_SECURITY_ACC_BN && INCLUDE_HW_SECURITY_ACC_BN_MUL_MOD */
	y_sqr_rhs = (mbedtls_mpi *) crypto_ec_point_compute_y_sqr(e, (const struct crypto_bignum *) & ((const mbedtls_ecp_point *)p)->MBEDTLS_PRIVATE(X));

	if (y_sqr_rhs && (mbedtls_mpi_cmp_mpi(y_sqr_rhs, &y_sqr_lhs) == 0)) {
		on_curve = 1;
	}

cleanup:
	mbedtls_mpi_free(&y_sqr_lhs);
	mbedtls_mpi_free(y_sqr_rhs);
	os_free(y_sqr_rhs);
	return (ret == 0) && (on_curve == 1);
}


#if 1 //New functions added since v2.10.
const struct crypto_bignum * crypto_ec_get_a(struct crypto_ec *e)
{
	if (e->group.A.MBEDTLS_PRIVATE(p) == NULL) {
		/* NIST curves are defined A = 0 but need to be set A = -3 */
		mbedtls_mpi_lset(&e->group.A, -3);
		mbedtls_mpi_mod_mpi(&e->group.A, &e->group.A, &e->group.P);
	}
	return (const struct crypto_bignum *) &e->group.A;
}

const struct crypto_bignum * crypto_ec_get_b(struct crypto_ec *e)
{
	return (const struct crypto_bignum *) &e->group.B;
}

struct crypto_bignum * crypto_bignum_init_uint(unsigned int val)
{
	mbedtls_mpi *bn = os_zalloc(sizeof(mbedtls_mpi));
	 if (bn == NULL) {
		 return NULL;
	 }

	 mbedtls_mpi_init(bn);
	 mbedtls_mpi_lset(bn, val);

	 return (struct crypto_bignum *)bn;
}

/**
 * crypto_bignum_sqrmod - c = a^2 (mod b)
 * @a: Bignum
 * @b: Bignum
 * @c: Bignum; used to store the result of a^2 % b
 * Returns: 0 on success, -1 on failure
 */
int crypto_bignum_sqrmod(const struct crypto_bignum *a,
								 const struct crypto_bignum *b,
									 struct crypto_bignum *c)
{
	int res;
	struct crypto_bignum *tmp = crypto_bignum_init();
	if (!tmp) {
		return -1;
	}

	res = mbedtls_mpi_copy((mbedtls_mpi *) tmp,(const mbedtls_mpi *) a);
	res = crypto_bignum_mulmod(a,tmp,b,c);

	crypto_bignum_deinit(tmp, 0);
	return res ? -1 : 0;
}

int crypto_bignum_addmod(const struct crypto_bignum *a,
									 const struct crypto_bignum *b,
									 const struct crypto_bignum *c,
										 struct crypto_bignum *d)
{
	int ret = -1;

	MBEDTLS_MPI_CHK(mbedtls_mpi_add_mpi((mbedtls_mpi *) d,
		(const mbedtls_mpi *) a, (const mbedtls_mpi *) b));
	while (mbedtls_mpi_cmp_mpi((const mbedtls_mpi *) d, (const mbedtls_mpi *) c) >= 0)
		MBEDTLS_MPI_CHK(mbedtls_mpi_sub_abs((mbedtls_mpi *) d,
			(const mbedtls_mpi *) d, (const mbedtls_mpi *) c));

cleanup:
	return ret;
}

/**
 * crypto_bignum_rshift - r = a >> n
 * @a: Bignum
 * @n: Number of bits
 * @r: Bignum; used to store the result of a >> n
 * Returns: 0 on success, -1 on failure
 */
int crypto_bignum_rshift(const struct crypto_bignum *a, int n,
			 struct crypto_bignum *r)
{
	int res;
	res = mbedtls_mpi_copy((mbedtls_mpi *) r,(const mbedtls_mpi *) a);
	if (res) {
		return -1;
	}
	res = mbedtls_mpi_shift_r((mbedtls_mpi *)r, n);
	return res ? -1 : 0;
}

#endif //#if 1 New functions added since v2.10.


struct crypto_bignum *crypto_bignum_init(void)
{
    mbedtls_mpi *bn = os_zalloc(sizeof(mbedtls_mpi));
    if (bn == NULL) {
        return NULL;
    }

    mbedtls_mpi_init(bn);

    return (struct crypto_bignum *)bn;
}

struct crypto_bignum *crypto_bignum_init_set(const u8 *buf, size_t len)
{
	int ret = 0;
	mbedtls_mpi *bn = os_zalloc(sizeof(mbedtls_mpi));
	if (bn == NULL) {
		return NULL;
	}

	MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(bn, buf, len));
	return (struct crypto_bignum *) bn;

cleanup:
	os_free(bn);
	return NULL;
}

void crypto_bignum_deinit(struct crypto_bignum *n, int clear)
{
    mbedtls_mpi_free((mbedtls_mpi *)n);
    os_free((mbedtls_mpi *)n);
}

int crypto_bignum_to_bin(const struct crypto_bignum *a,
                         u8 *buf, size_t buflen, size_t padlen)
{
    int num_bytes, offset;

    if (padlen > buflen) {
        return -1;
    }

    num_bytes = mbedtls_mpi_size((mbedtls_mpi *) a);

    if ((size_t) num_bytes > buflen) {
        return -1;
    }
    if (padlen > (size_t) num_bytes) {
        offset = padlen - num_bytes;
    } else {
        offset = 0;
    }

    os_memset(buf, 0, offset);
    mbedtls_mpi_write_binary((mbedtls_mpi *) a, buf + offset, mbedtls_mpi_size((mbedtls_mpi *)a) );

    return num_bytes + offset;
}

int crypto_bignum_rand(struct crypto_bignum *r, const struct crypto_bignum *m)
{
    return 0;
}

int crypto_bignum_add(const struct crypto_bignum *a,
                      const struct crypto_bignum *b,
                      struct crypto_bignum *c)
{
    return mbedtls_mpi_add_mpi((mbedtls_mpi *) c, (const mbedtls_mpi *) a, (const mbedtls_mpi *) b) ?
           -1 : 0;
}


int crypto_bignum_mod(const struct crypto_bignum *a,
                      const struct crypto_bignum *b,
                      struct crypto_bignum *c)
{
    return mbedtls_mpi_mod_mpi((mbedtls_mpi *) c, (const mbedtls_mpi *) a, (const mbedtls_mpi *) b) ? -1 : 0;
}

int crypto_bignum_sub(const struct crypto_bignum *a,
                      const struct crypto_bignum *b,
                      struct crypto_bignum *c)
{
    return mbedtls_mpi_sub_mpi((mbedtls_mpi *) c, (const mbedtls_mpi *) a, (const mbedtls_mpi *) b) ?
           -1 : 0;
}

int crypto_bignum_div(const struct crypto_bignum *a,
                      const struct crypto_bignum *b,
                      struct crypto_bignum *c)
{
    return mbedtls_mpi_div_mpi((mbedtls_mpi *) c, NULL, (const mbedtls_mpi *) a, (const mbedtls_mpi *) b) ?
           -1 : 0;
}

int crypto_bignum_mulmod(const struct crypto_bignum *a,
                         const struct crypto_bignum *b,
                         const struct crypto_bignum *c,
                         struct crypto_bignum *d)
{
    int res;
#if ALLOW_EVEN_MOD || !CONFIG_MBEDTLS_HARDWARE_MPI // Must enable ALLOW_EVEN_MOD if c is even
#if defined(INCLUDE_HW_SECURITY_ACC_BN) && defined(INCLUDE_HW_SECURITY_ACC_BN_MUL_MOD)
	if (((mbedtls_mpi *) c)->MBEDTLS_PRIVATE(n) >= 16) {
		mbedtls_mpi temp;
		mbedtls_mpi_init(&temp);

		res = mbedtls_mpi_mul_mpi(&temp, (const mbedtls_mpi *) a, (const mbedtls_mpi *) b);
		if (res) {
			return -1;
		}

		res = mbedtls_mpi_mod_mpi((mbedtls_mpi *) d, &temp, (mbedtls_mpi *) c);

		mbedtls_mpi_free(&temp);
	} else {
		res = mbedtls_mpi_mul_mpi_mod_mpi((mbedtls_mpi *) d, (mbedtls_mpi *) a, (mbedtls_mpi *) b, (mbedtls_mpi *) c);
	}
#else
    mbedtls_mpi temp;
    mbedtls_mpi_init(&temp);

    res = mbedtls_mpi_mul_mpi(&temp, (const mbedtls_mpi *) a, (const mbedtls_mpi *) b);
    if (res) {
        return -1;
    }

    res = mbedtls_mpi_mod_mpi((mbedtls_mpi *) d, &temp, (mbedtls_mpi *) c);

    mbedtls_mpi_free(&temp);
#endif /* INCLUDE_HW_SECURITY_ACC_BN && INCLUDE_HW_SECURITY_ACC_BN_MUL_MOD */
#else
    // Works with odd modulus only, but it is faster with HW acceleration
    res = esp_mpi_mul_mpi_mod((mbedtls_mpi *) d, (mbedtls_mpi *) a, (mbedtls_mpi *) b, (mbedtls_mpi *) c);
#endif
    return res ? -1 : 0;
}

int crypto_bignum_cmp(const struct crypto_bignum *a,
                      const struct crypto_bignum *b)
{
    return mbedtls_mpi_cmp_mpi((const mbedtls_mpi *) a, (const mbedtls_mpi *) b);
}

int crypto_bignum_exptmod(const struct crypto_bignum *a,
                          const struct crypto_bignum *b,
                          const struct crypto_bignum *c,
                          struct crypto_bignum *d)
{
    return  mbedtls_mpi_exp_mod((mbedtls_mpi *) d, (const mbedtls_mpi *) a, (const mbedtls_mpi *) b, (const mbedtls_mpi *) c, NULL) ? -1 : 0;

}

int crypto_bignum_legendre(const struct crypto_bignum *a,
                           const struct crypto_bignum *p)
{
    mbedtls_mpi exp, tmp;
    int res = -2, ret;

    mbedtls_mpi_init(&exp);
    mbedtls_mpi_init(&tmp);

    /* exp = (p-1) / 2 */
    MBEDTLS_MPI_CHK(mbedtls_mpi_sub_int(&exp, (const mbedtls_mpi *) p, 1));
    MBEDTLS_MPI_CHK(mbedtls_mpi_shift_r(&exp, 1));
    MBEDTLS_MPI_CHK(mbedtls_mpi_exp_mod(&tmp, (const mbedtls_mpi *) a, &exp, (const mbedtls_mpi *) p, NULL));

    if (mbedtls_mpi_cmp_int(&tmp, 1) == 0) {
        res = 1;
    } else if (mbedtls_mpi_cmp_int(&tmp, 0) == 0
            /* The below check is workaround for the case where HW
             * does not behave properly for X ^ A mod M when X is
             * power of M. Instead of returning value 0, value M is
             * returned.*/
            || mbedtls_mpi_cmp_mpi(&tmp, (const mbedtls_mpi *)p) == 0) {
        res = 0;
    } else {
        res = -1;
    }

cleanup:
    mbedtls_mpi_free(&tmp);
    mbedtls_mpi_free(&exp);
    return res;
}

int crypto_bignum_inverse(const struct crypto_bignum *a,
                          const struct crypto_bignum *b,
                          struct crypto_bignum *c)
{
    return mbedtls_mpi_inv_mod((mbedtls_mpi *) c, (const mbedtls_mpi *) a,
                               (const mbedtls_mpi *) b) ? -1 : 0;
}

int crypto_bignum_is_odd(const struct crypto_bignum *a)
{
    return 1;
}

int crypto_bignum_is_one(const struct crypto_bignum *a)
{
    return (mbedtls_mpi_cmp_int((const mbedtls_mpi *) a, 1) == 0);
}
           
int crypto_bignum_is_zero(const struct crypto_bignum *a)
{
    return (mbedtls_mpi_cmp_int((const mbedtls_mpi *) a, 0) == 0);
}

int crypto_bignum_bits(const struct crypto_bignum *a)
{
    return mbedtls_mpi_bitlen((const mbedtls_mpi *) a);
}

struct crypto_ecdh * crypto_ecdh_init(int group)
{
	struct crypto_ecdh *ecdh;
	unsigned char buf[1000];
	size_t olen;

	mbedtls_ecp_group_id grp_id = MBEDTLS_ECP_DP_NONE;

	mbedtls_entropy_context entropy;
	mbedtls_ctr_drbg_context ctr_drbg;

#if DEBUG_ECC_PROCESS_TIME //For Debug
	unsigned int ptime, ctime;
	ptime = TSF;
	_wpa_msg_crypto(0, MSG_DEBUG, TAG "[Enter] crypto_ecdh_init");
#endif

	//INIT RND
	mbedtls_entropy_init(&entropy);
	mbedtls_ctr_drbg_init(&ctr_drbg);

	mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy, NULL, 0);

	//Set Group ID
	grp_id = get_ecp_group_id(group);

	//INIT ECDH
	ecdh = os_zalloc(sizeof(struct crypto_ecdh));
	mbedtls_ecdh_init(&ecdh->ctx);
#ifndef CONFIG_MBEDTLS_ECDH_LEGACY_CONTEXT
	ecdh->ctx.MBEDTLS_PRIVATE(var) = MBEDTLS_ECDH_VARIANT_MBEDTLS_2_0;
#endif
	if(mbedtls_ecdh_setup(&ecdh->ctx, grp_id) != 0)
	{
		wpa_msg(0, MSG_DEBUG, "ECDH : Fail to setup ECDH\n");
		crypto_ecdh_deinit(ecdh);
		goto clean;
	}

	if(mbedtls_ecdh_make_public( &ecdh->ctx, &olen, buf, 1000,
                                  mbedtls_ctr_drbg_random, &ctr_drbg ) != 0)
	{
		wpa_msg(0, MSG_DEBUG, "ECDH : Fail to make public key\n");
		crypto_ecdh_deinit(ecdh);
		goto clean;
	}

	// wpa_hexdump(MSG_DEBUG, "PUBLIC BUF", buf, olen);
	// bignum_print("PUBLIC RES-X : ", &ecdh->ctx.Q.X);
	// bignum_print("PUBLIC RES-Y : ", &ecdh->ctx.Q.Y);
	// bignum_print("PUBLIC RES-Z : ", &ecdh->ctx.Q.Z);

clean:

#if DEBUG_ECC_PROCESS_TIME //For Debug
	ctime = TSF;
	_wpa_msg_crypto(0, MSG_DEBUG, TAG "[Exit ] crypto_ecdh_init (elapsed time: %u us)",(ctime -ptime));
#endif

	mbedtls_ctr_drbg_free(&ctr_drbg);
	mbedtls_entropy_free(&entropy);

	return ecdh;

}

struct crypto_ecdh * crypto_ecdh_init2(int group, struct crypto_ec_key *own_key)
{
	struct crypto_ecdh *ecdh;
	mbedtls_entropy_context entropy;
	mbedtls_ctr_drbg_context ctr_drbg;
	mbedtls_pk_context *pkey = (mbedtls_pk_context *) own_key;
	struct mbedtls_ecp_keypair *kp = mbedtls_pk_ec(*pkey);

	mbedtls_ecp_group_id grp_id = MBEDTLS_ECP_DP_NONE;
	grp_id = get_ecp_group_id(group);

	ecdh = os_zalloc(sizeof(*ecdh));
	if (ecdh == NULL) {
		wpa_printf(MSG_ERROR, "%s: Fail to alloc ecdh", __func__);
		return NULL;
	}

#if DEBUG_ECC_PROCESS_TIME //For Debug
	unsigned int ptime, ctime;
	ptime = TSF;
	_wpa_msg_crypto(NULL, MSG_DEBUG, TAG "[Enter] %s", __func__);
#endif

	mbedtls_ecdh_init(&ecdh->ctx);
#ifndef CONFIG_MBEDTLS_ECDH_LEGACY_CONTEXT
	ecdh->ctx.MBEDTLS_PRIVATE(var) = MBEDTLS_ECDH_VARIANT_MBEDTLS_2_0;
#endif
	if (mbedtls_ecdh_setup(&ecdh->ctx, grp_id) != 0) {
		wpa_printf(MSG_ERROR, "%s: Fail to setup ECDH", __func__);
		crypto_ecdh_deinit(ecdh);
		return NULL;
	}

	if (mbedtls_ecdh_get_params(&ecdh->ctx, kp, MBEDTLS_ECDH_OURS) != 0) {
		wpa_printf(MSG_ERROR, "%s: Fail to set our ecdh params", __func__);
		crypto_ecdh_deinit(ecdh);
		return NULL;
	}

	if (mbedtls_ecdh_get_params(&ecdh->ctx, kp, MBEDTLS_ECDH_THEIRS) != 0) {
		wpa_printf(MSG_ERROR, "%s: Fail to set peer ecdh params", __func__);
		crypto_ecdh_deinit(ecdh);
		return NULL;
	}

	mbedtls_entropy_init(&entropy);
	mbedtls_ctr_drbg_init(&ctr_drbg);
	mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy, NULL, 0);

	size_t olen;
	unsigned char buf[MBEDTLS_MPI_MAX_SIZE];
	if (mbedtls_ecdh_calc_secret(&ecdh->ctx, &olen, buf, MBEDTLS_MPI_MAX_SIZE,
		mbedtls_ctr_drbg_random, &ctr_drbg) != 0) {
		wpa_printf(MSG_ERROR, "%s: Fail to calc secret", __func__);
		mbedtls_ctr_drbg_free(&ctr_drbg);
		mbedtls_entropy_free(&entropy);
		crypto_ecdh_deinit(ecdh);
		return NULL;
	}
	mbedtls_ctr_drbg_free(&ctr_drbg);
	mbedtls_entropy_free(&entropy);

#if DEBUG_ECC_PROCESS_TIME //For Debug
	ctime = TSF;
	_wpa_msg_crypto(0, MSG_DEBUG, TAG "[Exit ] %s (elapsed time: %u us)", __func__, (ctime - ptime));
#endif

	return ecdh;
}

void crypto_ecdh_deinit(struct crypto_ecdh *ecdh)
{
	mbedtls_ecdh_context *ctx = (mbedtls_ecdh_context *) &ecdh->ctx;

	if(ctx) {
		mbedtls_ecdh_free(&ecdh->ctx);
		os_free(ecdh);
		ecdh = NULL;
	}
}

struct wpabuf * crypto_ecdh_get_pubkey(struct crypto_ecdh *ecdh, int inc_y)
{
	struct wpabuf *buf = NULL;
	mbedtls_ecdh_context *ctx = (mbedtls_ecdh_context *) &ecdh->ctx;
	size_t prime_len = crypto_ec_prime_len((struct crypto_ec *) &ACCESS_ECDH(ctx, grp));
	size_t olen = inc_y ? prime_len * 2 : prime_len;

	buf = wpabuf_alloc(olen);
	if (!buf) {
		wpa_msg(0, MSG_DEBUG, "ECDH : Fail to alloc buffer\n");
		return NULL;
	}

	wpa_msg(0, MSG_DEBUG, "LEN : %d, T_size : %d pbits : %d, nbits :  %d\n", prime_len,
		ACCESS_ECDH(ctx, grp).MBEDTLS_PRIVATE(T_size),
		ACCESS_ECDH(ctx, grp).pbits, ACCESS_ECDH(ctx, grp).nbits);

	if (crypto_bignum_to_bin((struct crypto_bignum *) &ACCESS_ECDH(ctx, Q).MBEDTLS_PRIVATE(X),
			wpabuf_put(buf, prime_len), prime_len, prime_len) != prime_len) {
		wpa_msg(0, MSG_DEBUG, "ECDH : Fail to get pubkey.X\n");
		wpabuf_free(buf);
		return NULL;
	}

	if (inc_y) {
		if (crypto_bignum_to_bin((struct crypto_bignum *) &ACCESS_ECDH(ctx, Q).MBEDTLS_PRIVATE(Y),
				wpabuf_put(buf, prime_len), prime_len, prime_len) != prime_len) {
			wpa_msg(0, MSG_DEBUG, "ECDH : Fail to get pubkey.Y\n");
			wpabuf_free(buf);
			return NULL;
		}
	}

	wpa_msg(0, MSG_DEBUG, "ECDH : ECDH key length : %d\n", olen);
	// bignum_print("Public Bignum", &ACCESS_ECDH(ctx, Q).MBEDTLS_PRIVATE(X));
	wpa_hexdump(MSG_DEBUG, "ECDH : Public Key", wpabuf_head(buf), olen);

    return buf;
}

struct wpabuf * crypto_ecdh_set_peerkey(struct crypto_ecdh *ecdh, int inc_y,
					const u8 *key, size_t len)
{
	struct wpabuf *secret = NULL;
	unsigned char res_buf[1000];
	size_t res_len;
	int res = 0;

	mbedtls_ecdh_context *ctx = (mbedtls_ecdh_context *) &ecdh->ctx;

	mbedtls_entropy_context entropy;
	mbedtls_ctr_drbg_context ctr_drbg;

#if DEBUG_ECC_PROCESS_TIME //For Debug
	unsigned int ptime, ctime;
	ptime = TSF;
	_wpa_msg_crypto(0, MSG_DEBUG, TAG "[Enter] crypto_ecdh_set_peerkey");
#endif

	//INIT RND
	mbedtls_entropy_init(&entropy);
	mbedtls_ctr_drbg_init(&ctr_drbg);

	mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy, NULL, 0);

	mbedtls_ecp_point *peerKey;
	peerKey = &ACCESS_ECDH(ctx, Qp);

	if(mbedtls_mpi_read_binary(&peerKey->MBEDTLS_PRIVATE(X), key, inc_y ? len / 2 : len) != 0)
	{
		wpa_msg(0, MSG_DEBUG, "ECDH : [%s, %d] Fail to read peer public-key(point X)", __func__, __LINE__);
		goto clean;
	}

	if(mbedtls_mpi_lset(&peerKey->MBEDTLS_PRIVATE(Z), 1) != 0)
	{
		wpa_msg(0, MSG_DEBUG, "ECDH : [%s, %d] Fail to Set bit in public-key(point Z)", __func__, __LINE__);
		goto clean;
	}

	if (inc_y)
	{
		if(mbedtls_mpi_read_binary(&peerKey->MBEDTLS_PRIVATE(Y), key + (len / 2), len / 2) != 0)
		{
			wpa_msg(0, MSG_DEBUG, "ECDH : [%s, %d] Fail to read peer public-key(point Y)", __func__, __LINE__);
			goto clean;
		}
	} else {
		if(crypto_ec_point_solve_y_coord((struct crypto_ec *) &ACCESS_ECDH(ctx, grp), (void *) peerKey, (void *) &peerKey->MBEDTLS_PRIVATE(X), 0))
		{
			wpa_msg(0, MSG_DEBUG, "ECDH : [%s, %d] Fail to calc Y using X(y^2 = x^3 + ax + b  mod  P)", __func__, __LINE__);
			goto clean;
		}
	}
	// bignum_print("Public  Key : ", &ecdh->ctx.Q.X);
	// bignum_print("Private Key : ", &ecdh->ctx.d);
	// bignum_print("pr Public X Key : ", &ecdh->ctx.Qp.X);
	// bignum_print("pr Public Y Key : ", &ecdh->ctx.Qp.Y);
	// bignum_print("pr Public Z Key : ", &ecdh->ctx.Qp.Z);

	if(mbedtls_ecdh_calc_secret( &ecdh->ctx, &res_len, res_buf, 1000,
                                           mbedtls_ctr_drbg_random, &ctr_drbg ) != 0)
	{
		wpa_msg(0, MSG_DEBUG, "ECDH : [%s, %d] Fail to calc secret", __func__, __LINE__);
		goto clean;
	}

	wpa_hexdump(MSG_DEBUG, "ECDH : SHARED KEY", res_buf, res_len);

	ecdh->length = res_len;

	secret = wpabuf_alloc(ecdh->length);
	if (secret == NULL) {
		wpa_msg(0, MSG_DEBUG, "ECDH : [%s, %d] Fail to alloc buffer", __func__, __LINE__);
		return NULL;
	}

	// mbedtls_mpi_write_binary(&ecdh->ctx.z, secret->buf, ecdh->length);
	os_memcpy(wpabuf_put(secret, ecdh->length), res_buf, ecdh->length);

clean:

#if DEBUG_ECC_PROCESS_TIME //For Debug
	ctime = TSF;
	_wpa_msg_crypto(0, MSG_DEBUG, TAG "[Exit ] crypto_ecdh_set_peerkey (elapsed time: %u us)",(ctime -ptime));
#endif

	mbedtls_ctr_drbg_free(&ctr_drbg);
	mbedtls_entropy_free(&entropy);

	return secret;
}

#if 0
int omac1_aes_128(const u8 *key, const u8 *data, size_t data_len, u8 *mac)
{
	return 0;
}
#endif

static struct crypto_ec_key *crypto_alloc_key(void)
{
	mbedtls_pk_context *pkey = os_malloc(sizeof(*pkey));

	if (!pkey) {
		wpa_printf(MSG_ERROR, "%s: Fail to alloc key", __func__);
		return NULL;
	}
	mbedtls_pk_init(pkey);

	return (struct crypto_ec_key *) pkey;
}

struct crypto_ec_key *crypto_ec_key_parse_priv(const u8 *der, size_t der_len)
{
	int ret;
	mbedtls_entropy_context entropy;
	mbedtls_ctr_drbg_context ctr_drbg;

	mbedtls_pk_context *pkey = (mbedtls_pk_context *) crypto_alloc_key();
	if (!pkey) {
		return NULL;
	}

#if (MBEDTLS_VERSION_MAJOR >= 3)
	mbedtls_entropy_init(&entropy);
	mbedtls_ctr_drbg_init(&ctr_drbg);
	mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy, NULL, 0);

	ret = mbedtls_pk_parse_key(pkey, der, der_len, NULL, 0, mbedtls_ctr_drbg_random, &ctr_drbg);
	mbedtls_ctr_drbg_free(&ctr_drbg);
	mbedtls_entropy_free(&entropy);
#else
	ret = mbedtls_pk_parse_key(pkey, der, der_len, NULL, 0);
#endif

	if (ret < 0) {
		wpa_printf(MSG_ERROR, "%s: Failed to parse EC Private Key", __func__);
		crypto_ec_key_deinit((struct crypto_ec_key *) pkey);
		return NULL;
	}

	return (struct crypto_ec_key *) pkey;
}

struct crypto_ec_key *crypto_ec_key_parse_pub(const u8 *der, size_t der_len)
{
	int ret;

	mbedtls_pk_context *pkey = (mbedtls_pk_context *) crypto_alloc_key();
	if (!pkey) {
		return NULL;
	}

	ret = mbedtls_pk_parse_public_key(pkey, der, der_len);
	if (ret < 0) {
		wpa_printf(MSG_ERROR, "%s: Failed to parse EC Public Key", __func__);
		crypto_ec_key_deinit((struct crypto_ec_key *) pkey);
		return NULL;
	}

	return (struct crypto_ec_key *) pkey;
}

struct crypto_ec_key *crypto_ec_key_set_pub(int group, const u8 *buf_x,
					     const u8 *buf_y, size_t len)
{
	u8 *buf = NULL;
	mbedtls_pk_context *pkey = NULL;
	struct crypto_ec_point *point = NULL;
	struct crypto_ec *e = crypto_ec_init(group);
	if (!e) {
		wpa_printf(MSG_ERROR, "%s: Fail to init ec", __func__);
		return NULL;
	}

	buf = os_malloc(len * 2);
	if (!buf) {
		wpa_printf(MSG_ERROR, "%s: Fail to alloc buffer(%d)", __func__, len);
		goto fail;
	}
	os_memcpy(buf, buf_x, len);
	os_memcpy(buf + len, buf_y, len);
	point = crypto_ec_point_from_bin(e, buf);
	if (!point) {
		wpa_printf(MSG_ERROR, "%s: Fail to init ec point", __func__);
		goto fail;
	}
	if (crypto_ec_point_is_at_infinity(e, point)) {
		wpa_printf(MSG_ERROR, "%s: Point is at infinity", __func__);
		goto fail;
	}
	if (!crypto_ec_point_is_on_curve(e, point)) {
		wpa_printf(MSG_ERROR, "%s: Point is not on curve", __func__);
		goto fail;
	}
	if (mbedtls_ecp_check_pubkey(&e->group, (mbedtls_ecp_point *) point) != 0) {
		wpa_printf(MSG_ERROR, "%s: Invalid public key", __func__);
		goto fail;
	}

	pkey = (mbedtls_pk_context *) crypto_alloc_key();
	if (!pkey) {
		wpa_printf(MSG_ERROR, "%s: Fail to alloc key", __func__);
		goto fail;
	}
	if (mbedtls_pk_setup(pkey, mbedtls_pk_info_from_type(MBEDTLS_PK_ECKEY)) != 0) {
		wpa_printf(MSG_ERROR, "%s: Fail to setup key", __func__);
		crypto_ec_key_deinit((struct crypto_ec_key *) pkey);
		pkey = NULL;
		goto fail;
	}

	mbedtls_ecp_copy(&mbedtls_pk_ec(*pkey)->MBEDTLS_PRIVATE(Q), (mbedtls_ecp_point *) point);
	mbedtls_ecp_group_load(&mbedtls_pk_ec(*pkey)->MBEDTLS_PRIVATE(grp), e->group.id);

fail:
	os_free(buf);
	crypto_ec_point_deinit(point, 0);
	crypto_ec_deinit(e);
	return (struct crypto_ec_key *) pkey;
}

struct crypto_ec_key *
crypto_ec_key_set_pub_point(struct crypto_ec *ec,
			    const struct crypto_ec_point *pub)
{
	mbedtls_pk_context *pkey = (mbedtls_pk_context *) crypto_alloc_key();
	if (!pkey) {
		wpa_printf(MSG_ERROR, "%s: Fail to alloc key", __func__);
		return NULL;
	}
	if (mbedtls_pk_setup(pkey, mbedtls_pk_info_from_type(MBEDTLS_PK_ECKEY)) != 0) {
		wpa_printf(MSG_ERROR, "%s: Fail to setup key", __func__);
		crypto_ec_key_deinit((struct crypto_ec_key *) pkey);
		return NULL;
	}

	mbedtls_ecp_copy(&mbedtls_pk_ec(*pkey)->MBEDTLS_PRIVATE(Q), (mbedtls_ecp_point *) pub);
	mbedtls_ecp_group_load(&mbedtls_pk_ec(*pkey)->MBEDTLS_PRIVATE(grp), ec->group.id);

	return (struct crypto_ec_key *) pkey;
}

struct crypto_ec_key *crypto_ec_key_gen(int group)
{
	mbedtls_entropy_context entropy;
	mbedtls_ctr_drbg_context ctr_drbg;
	mbedtls_pk_context *pkey = (mbedtls_pk_context *) crypto_alloc_key();
	if (!pkey) {
		return NULL;
	}

#if DEBUG_ECC_PROCESS_TIME //For Debug
	unsigned int ptime, ctime;
	ptime = TSF;
	_wpa_msg_crypto(NULL, MSG_DEBUG, TAG "[Enter] %s", __func__);
#endif

	if (mbedtls_pk_setup(pkey, mbedtls_pk_info_from_type(MBEDTLS_PK_ECKEY)) != 0) {
		crypto_ec_key_deinit((struct crypto_ec_key *) pkey);
		return NULL;
	}

	mbedtls_entropy_init(&entropy);
	mbedtls_ctr_drbg_init(&ctr_drbg);
	mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy, NULL, 0);

	if (mbedtls_ecp_gen_key(get_ecp_group_id(group), mbedtls_pk_ec(*pkey),
					mbedtls_ctr_drbg_random, &ctr_drbg) != 0) {
		wpa_printf(MSG_ERROR, "%s: Fail to generate key", __func__);
		crypto_ec_key_deinit((struct crypto_ec_key *) pkey);
		pkey = NULL;
	}

	mbedtls_ctr_drbg_free(&ctr_drbg);
	mbedtls_entropy_free(&entropy);

#if DEBUG_ECC_PROCESS_TIME //For Debug
	ctime = TSF;
	_wpa_msg_crypto(0, MSG_DEBUG, TAG "[Exit ] %s (elapsed time: %u us)", __func__, (ctime - ptime));
#endif

	return (struct crypto_ec_key *) pkey;
}

void crypto_ec_key_deinit(struct crypto_ec_key *key)
{
	mbedtls_pk_context *pkey = (mbedtls_pk_context *) key;
	mbedtls_pk_free(pkey);
	os_free(pkey);
}

struct wpabuf *crypto_ec_key_get_subject_public_key(struct crypto_ec_key *key)
{
	struct wpabuf *der = NULL;
	unsigned char *end;
	const char *oid = NULL;
	size_t der_len = 0, par_len = 0, oid_len = 0;
	mbedtls_pk_context *pkey = (mbedtls_pk_context *) key;
	mbedtls_ecp_keypair *kp = mbedtls_pk_ec(*pkey);
	unsigned char buf[MBEDTLS_ECP_MAX_PT_LEN];
	unsigned char der_data[ECP_PUB_DER_MAX_BYTES];

	end = der_data + ECP_PUB_DER_MAX_BYTES;
	if (mbedtls_ecp_point_write_binary(&kp->MBEDTLS_PRIVATE(grp), &kp->MBEDTLS_PRIVATE(Q),
		MBEDTLS_ECP_PF_COMPRESSED, &der_len, buf, MBEDTLS_ECP_MAX_PT_LEN) < 0) {
		wpa_printf(MSG_ERROR, "%s: Failed to get pubkey", __func__);
		return NULL;
	}
	if (der_len <= 0) {
		wpa_printf(MSG_ERROR, "%s: invalid pubkey length(%d)", __func__, der_len);
		return NULL;
	}

	end -= der_len;
	os_memcpy(end, buf, der_len);

	*--end = 0;
	der_len += 1;

	der_len += mbedtls_asn1_write_len(&end, der_data, der_len);
	der_len += mbedtls_asn1_write_tag(&end, der_data, MBEDTLS_ASN1_BIT_STRING);

#if defined(MBEDTLS_ECP_C)
    if (mbedtls_pk_get_type(pkey) == MBEDTLS_PK_ECKEY) {
		if (mbedtls_oid_get_oid_by_ec_grp(kp->MBEDTLS_PRIVATE(grp).id, &oid, &oid_len) != 0) {
			wpa_printf(MSG_ERROR, "%s: Failed to get oid by grp", __func__);
			return NULL;
		}
		par_len += mbedtls_asn1_write_oid(&end, der_data, oid, oid_len);
	}
#endif

	if (mbedtls_oid_get_oid_by_pk_alg(mbedtls_pk_get_type(pkey),
		&oid, &oid_len) != 0) {
		wpa_printf(MSG_ERROR, "%s: Failed to get oid by alg", __func__);
		return NULL;
	}

	der_len += mbedtls_asn1_write_algorithm_identifier(&end, der_data, oid, oid_len,
		par_len);

	der_len += mbedtls_asn1_write_len(&end, der_data, der_len);
	der_len += mbedtls_asn1_write_tag(&end, der_data, MBEDTLS_ASN1_CONSTRUCTED |
		MBEDTLS_ASN1_SEQUENCE);

	der = wpabuf_alloc(der_len);
	if (!der) {
		wpa_printf(MSG_ERROR, "%s: Failed to alloc memory for pubkey der(%d)",
					__func__, der_len);
		return NULL;
	}
	wpabuf_put_data(der, der_data + ECP_PUB_DER_MAX_BYTES - der_len, der_len);

	return der;
}

struct wpabuf * crypto_ec_key_get_ecprivate_key(struct crypto_ec_key *key,
						bool include_pub)
{
	struct wpabuf *ret;
	mbedtls_pk_context *pkey = (mbedtls_pk_context *) key;
	int der_len = 0;
	size_t pub_len = 0;
	unsigned char der_data[ECP_PRV_DER_MAX_BYTES];

	der_len = mbedtls_pk_write_key_der(pkey, der_data, ECP_PRV_DER_MAX_BYTES);
	if (der_len <= 0) {
		wpa_printf(MSG_DEBUG, "%s: Failed to get priv der", __func__);
		return NULL;
	}

	if (!include_pub) {
		unsigned char *der_end = der_data + ECP_PRV_DER_MAX_BYTES;
		unsigned char *der_start = der_end - der_len;
		while (der_start < der_end) {
			if (mbedtls_asn1_get_tag(&der_start, der_end, &pub_len,
				MBEDTLS_ASN1_CONTEXT_SPECIFIC | MBEDTLS_ASN1_CONSTRUCTED | 1) != 0) {
				pub_len = 0;
				wpa_printf(MSG_ERROR, "%s: Failed to find pub der", __func__);
				break;
			}
		}
	}
	ret = wpabuf_alloc_copy(der_data + ECP_PRV_DER_MAX_BYTES - der_len, der_len - pub_len);

	return ret;
}

struct wpabuf * crypto_ec_key_get_pubkey_point(struct crypto_ec_key *key,
					       int prefix)
{
	struct wpabuf *kbuf = NULL;
	mbedtls_pk_context *pkey = (mbedtls_pk_context *) key;
	unsigned char buf[MBEDTLS_MPI_MAX_SIZE + 10]; /* tag, length + MPI */
	unsigned char *c = buf + sizeof(buf);
	int pk_len = mbedtls_pk_write_pubkey(&c, buf, pkey);
	if (pk_len <= 0) {
		wpa_printf(MSG_ERROR, "%s: Fail to get public-key", __func__);
		return NULL;
	}

	kbuf = wpabuf_alloc_copy(buf + MBEDTLS_MPI_MAX_SIZE + 10 - pk_len, pk_len);
	if (!kbuf) {
		wpa_printf(MSG_ERROR, "%s: Fail to alloc memory for public-key", __func__);
		return NULL;
	}

	if (!prefix) {
		/* Remove 0x04 prefix if requested */
		u8 *pos = wpabuf_mhead(kbuf);
		os_memmove(pos, pos + 1, pk_len - 1);
		kbuf->used--;
	}

	return kbuf;
}

struct crypto_ec_point *
crypto_ec_key_get_public_key(struct crypto_ec_key *key)
{
	mbedtls_pk_context *pkey = (mbedtls_pk_context *) key;
	struct mbedtls_ecp_point *pt = os_zalloc(sizeof(mbedtls_ecp_point));

	if (pt == NULL) {
		wpa_printf(MSG_ERROR, "%s: Fail to alloc ec point", __func__);
		return NULL;
	}
	mbedtls_ecp_point_init(pt);
	mbedtls_ecp_copy(pt, &mbedtls_pk_ec(*pkey)->MBEDTLS_PRIVATE(Q));
	return (struct crypto_ec_point *) pt;
}

struct crypto_bignum *
crypto_ec_key_get_private_key(struct crypto_ec_key *key)
{
	mbedtls_pk_context *pkey = (mbedtls_pk_context *) key;
	mbedtls_mpi *privkey = os_zalloc(sizeof(mbedtls_mpi));

	if (privkey == NULL) {
		wpa_printf(MSG_ERROR, "%s: Fail to alloc mpi", __func__);
		return NULL;
	}
	mbedtls_mpi_init(privkey);
	mbedtls_mpi_copy(privkey, &mbedtls_pk_ec(*pkey)->MBEDTLS_PRIVATE(d));
	return (struct crypto_bignum *) privkey;
}

struct wpabuf * crypto_ec_key_sign_r_s(struct crypto_ec_key *key,
				       const u8 *data, size_t len)
{
	struct wpabuf *sig = NULL;
	mbedtls_entropy_context entropy;
	mbedtls_ctr_drbg_context ctr_drbg;
	mbedtls_pk_context *pkey = (mbedtls_pk_context *) key;
	mbedtls_ecp_keypair *kp = mbedtls_pk_ec(*pkey);
	mbedtls_mpi r, s;

#if DEBUG_ECC_PROCESS_TIME //For Debug
	unsigned int ptime, ctime;
	ptime = TSF;
	_wpa_msg_crypto(NULL, MSG_DEBUG, TAG "[Enter] %s", __func__);
#endif

	mbedtls_mpi_init(&r);
	mbedtls_mpi_init(&s);
	mbedtls_entropy_init(&entropy);
	mbedtls_ctr_drbg_init(&ctr_drbg);
	mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy, NULL, 0);
	if (mbedtls_ecdsa_sign(&kp->MBEDTLS_PRIVATE(grp), &r, &s, &kp->MBEDTLS_PRIVATE(d),
		data, len, mbedtls_ctr_drbg_random, &ctr_drbg) == 0) {
		u8 r_bin[32], s_bin[32];
		size_t sig_len = 0;
		size_t prime_len = crypto_ec_prime_len((struct crypto_ec *) &kp->MBEDTLS_PRIVATE(grp));
		sig = wpabuf_alloc(prime_len * 2);
		if (sig) {
			sig_len = crypto_bignum_to_bin((struct crypto_bignum *) &r, r_bin,
					prime_len, prime_len);
			wpabuf_put_data(sig, r_bin, sig_len);
			sig_len = crypto_bignum_to_bin((struct crypto_bignum *) &s, s_bin,
					prime_len, prime_len);
			wpabuf_put_data(sig, s_bin, sig_len);
		} else {
			wpa_printf(MSG_ERROR, "%s: Fail to alloc buffer", __func__);
		}
	} else {
		wpa_printf(MSG_ERROR, "%s: Fail to ecdsa sign", __func__);
	}
	mbedtls_ctr_drbg_free(&ctr_drbg);
	mbedtls_entropy_free(&entropy);
	mbedtls_mpi_free(&r);
	mbedtls_mpi_free(&s);

#if DEBUG_ECC_PROCESS_TIME //For Debug
	ctime = TSF;
	_wpa_msg_crypto(0, MSG_DEBUG, TAG "[Exit ] %s (elapsed time: %u us)", __func__, (ctime - ptime));
#endif

	return sig;
}

int crypto_ec_key_verify_signature_r_s(struct crypto_ec_key *key,
				       const u8 *data, size_t len,
				       const u8 *r, size_t r_len,
				       const u8 *s, size_t s_len)
{
	int ret = 1;
	mbedtls_pk_context *pkey = (mbedtls_pk_context *) key;
	mbedtls_ecp_keypair *kp = mbedtls_pk_ec(*pkey);
	mbedtls_mpi *pr, *ps;

#if DEBUG_ECC_PROCESS_TIME //For Debug
	unsigned int ptime, ctime;
	ptime = TSF;
	_wpa_msg_crypto(NULL, MSG_DEBUG, TAG "[Enter] %s", __func__);
#endif

	pr = (mbedtls_mpi *) crypto_bignum_init_set(r, r_len);
	ps = (mbedtls_mpi *) crypto_bignum_init_set(s, s_len);
	if (!pr || !ps) {
		return -1;
	}

	if (mbedtls_ecdsa_verify(&kp->MBEDTLS_PRIVATE(grp), data, len, &kp->MBEDTLS_PRIVATE(Q), pr, ps) != 0) {
		wpa_printf(MSG_ERROR, "%s: Fail to verify ec signature", __func__);
		ret = 0;
		goto cleanup;
	}

#if DEBUG_ECC_PROCESS_TIME //For Debug
	ctime = TSF;
	_wpa_msg_crypto(0, MSG_DEBUG, TAG "[Exit ] %s (elapsed time: %u us)", __func__, (ctime - ptime));
#endif

cleanup:
	crypto_bignum_deinit((struct crypto_bignum *) pr, 0);
	crypto_bignum_deinit((struct crypto_bignum *) ps, 0);
	return ret;
}

int crypto_ec_key_group(struct crypto_ec_key *key)
{
	mbedtls_pk_context *pkey = (mbedtls_pk_context *) key;
	return (int)crypto_ec_get_mbedtls_to_nist_group_id(mbedtls_pk_ec(*pkey)->MBEDTLS_PRIVATE(grp).id);
}

int crypto_ec_key_cmp(struct crypto_ec_key *key1, struct crypto_ec_key *key2)
{
	mbedtls_pk_context *pkey;
	struct mbedtls_ecp_keypair *kp;
	struct mbedtls_ecp_point *A, *B;

	pkey = (mbedtls_pk_context *) key1; kp = mbedtls_pk_ec(*pkey);
	A = (struct mbedtls_ecp_point *) &kp->MBEDTLS_PRIVATE(Q);
	pkey = (mbedtls_pk_context *) key2; kp = mbedtls_pk_ec(*pkey);
	B = (struct mbedtls_ecp_point *) &kp->MBEDTLS_PRIVATE(Q);

	return mbedtls_ecp_point_cmp((const mbedtls_ecp_point *) A,
			(const mbedtls_ecp_point *) B) ? -1 : 0;
}

void crypto_ec_key_debug_print(const struct crypto_ec_key *key,
			       const char *title)
{
	mbedtls_pk_context *pkey = (mbedtls_pk_context *) key;
	struct mbedtls_ecp_keypair *kp = mbedtls_pk_ec(*pkey);
	uint8_t x[32], y[32], d[32];

	wpa_printf(MSG_DEBUG, "curve: %s",
		   mbedtls_ecp_curve_info_from_grp_id(kp->MBEDTLS_PRIVATE(grp).id)->name);

	size_t len = mbedtls_mpi_size((mbedtls_mpi *) &kp->MBEDTLS_PRIVATE(grp).P);
	wpa_printf(MSG_DEBUG, "prime len is %d", len);

	if (crypto_bignum_to_bin((struct crypto_bignum *) &kp->MBEDTLS_PRIVATE(Q).MBEDTLS_PRIVATE(X),
		x, len, len) < 0) {
		return;
	}
	wpa_hexdump(MSG_DEBUG, "Q_x:", x, 32);

	if (crypto_bignum_to_bin((struct crypto_bignum *) &kp->MBEDTLS_PRIVATE(Q).MBEDTLS_PRIVATE(Y),
		y, len, len) < 0) {
		return;
	}
	wpa_hexdump(MSG_DEBUG, "Q_y:", y, 32);

	if (crypto_bignum_to_bin((struct crypto_bignum *) &kp->MBEDTLS_PRIVATE(d),
		d, len, len) < 0) {
		return;
	}
	wpa_hexdump(MSG_DEBUG, "d  :", d, 32);
}

#endif /* CONFIG_ECC */

struct crypto_csr {
	mbedtls_x509_csr ctx;
	mbedtls_x509write_csr write_ctx;
};

struct crypto_csr * crypto_csr_init()
{
	struct crypto_csr *csr = os_malloc(sizeof(*csr));
	if (!csr) {
		wpa_printf(MSG_ERROR, "%s: Fail to alloc csr", __func__);
		return NULL;
	}
	mbedtls_x509_csr_init(&csr->ctx);
	mbedtls_x509write_csr_init(&csr->write_ctx);
	return csr;
}

struct crypto_csr * crypto_csr_verify(const struct wpabuf *req)
{
	struct crypto_csr *csr = crypto_csr_init();
	if (!csr) {
		wpa_printf(MSG_ERROR, "%s: Fail to init csr", __func__);
		return NULL;
	}
	mbedtls_x509_csr_parse(&csr->ctx, (const unsigned char *)wpabuf_head(req),
				   wpabuf_len(req));
	return csr;
}

void crypto_csr_deinit(struct crypto_csr *csr)
{
	if (!csr)
		return;

	mbedtls_x509write_csr_free(&csr->write_ctx);
	mbedtls_x509_csr_free(&csr->ctx);
	os_free(csr);
}

int crypto_csr_set_ec_public_key(struct crypto_csr *csr, struct crypto_ec_key *key)
{
	mbedtls_pk_context *pkey = (mbedtls_pk_context *) key;

	if (!csr || !pkey) {
		wpa_printf(MSG_ERROR, "%s: No csr or key", __func__);
		return -1;
	}

	mbedtls_pk_init(&csr->ctx.pk);
	if (mbedtls_pk_setup(&csr->ctx.pk,
					mbedtls_pk_info_from_type(mbedtls_pk_get_type(pkey))) != 0) {
		wpa_printf(MSG_ERROR, "%s: Fail to setup key", __func__);
		mbedtls_pk_free(&csr->ctx.pk);
		return -1;
	}

	if (mbedtls_ecp_group_copy(&mbedtls_pk_ec(csr->ctx.pk)->MBEDTLS_PRIVATE(grp),
					&mbedtls_pk_ec(*pkey)->MBEDTLS_PRIVATE(grp)) != 0) {
		wpa_printf(MSG_ERROR, "%s: Fail to copy group", __func__);
		mbedtls_pk_free(&csr->ctx.pk);
		return -1;
	}

	if (mbedtls_ecp_copy(&mbedtls_pk_ec(csr->ctx.pk)->MBEDTLS_PRIVATE(Q),
					&mbedtls_pk_ec(*pkey)->MBEDTLS_PRIVATE(Q)) != 0) {
		wpa_printf(MSG_ERROR, "%s: Fail to copy pubkey point", __func__);
		mbedtls_pk_free(&csr->ctx.pk);
		return -1;
	}

	return 0;
}

int crypto_csr_set_name(struct crypto_csr *csr, enum crypto_csr_name type,
			const char *name)
{
	const char *oid = NULL;
	char buf[MBEDTLS_X509_MAX_DN_NAME_SIZE];

	if (!csr) {
		wpa_printf(MSG_ERROR, "%s: No csr", __func__);
		return -1;
	}

	switch (type) {
	case CSR_NAME_CN:
		oid = MBEDTLS_OID_AT_CN;
		break;
	case CSR_NAME_SN:
		oid = MBEDTLS_OID_AT_SUR_NAME;
		break;
	case CSR_NAME_C:
		oid = MBEDTLS_OID_AT_COUNTRY;
		break;
	case CSR_NAME_O:
		oid = MBEDTLS_OID_AT_ORGANIZATION;
		break;
	case CSR_NAME_OU:
		oid = MBEDTLS_OID_AT_ORG_UNIT;
		break;
	default:
		wpa_printf(MSG_ERROR, "%s: invalid csr type:%d", __func__, type);
		return -1;
	}

	os_snprintf(buf, sizeof(buf), "%s=%s", oid, name);
	if (mbedtls_x509write_csr_set_subject_name(&csr->write_ctx, name) != 0) {
		wpa_printf(MSG_ERROR, "%s: Fail to set csr name", __func__);
		return -1;
	}

	return 0;
}

int crypto_csr_set_attribute(struct crypto_csr *csr, enum crypto_csr_attr attr,
			     int attr_type, const u8 *value, size_t len)
{
	const char *oid = NULL;

	if (!csr) {
		wpa_printf(MSG_ERROR, "%s: No csr", __func__);
		return -1;
	}

	switch (attr) {
	case CSR_ATTR_CHALLENGE_PASSWORD:
		oid = MBEDTLS_OID_PKCS9_CSR_CHALLENGE_PASSWORD;
		break;
	default:
		wpa_printf(MSG_ERROR, "%s: Invalid csr attr:%d", __func__, attr);
		return -1;
	}

#if (MBEDTLS_VERSION_MAJOR >= 3)
	if (mbedtls_x509write_csr_set_extension(&csr->write_ctx,
					oid, MBEDTLS_OID_SIZE(oid), 0, value, len) != 0) {
		wpa_printf(MSG_ERROR, "%s: Fail to set csr attr", __func__);
		return -1;
	}
#else
	if (mbedtls_x509write_csr_set_extension(&csr->write_ctx,
					oid, MBEDTLS_OID_SIZE(oid), value, len) != 0) {
		wpa_printf(MSG_ERROR, "%s: Fail to set csr attr", __func__);
		return -1;
	}
#endif

	if (csr->write_ctx.MBEDTLS_PRIVATE(extensions)) {
		csr->write_ctx.MBEDTLS_PRIVATE(extensions)->val.tag = attr_type;
	}

	return 0;
}

const u8 * crypto_csr_get_attribute(struct crypto_csr *csr,
				    enum crypto_csr_attr attr,
				    size_t *len, int *type)
{
	const mbedtls_asn1_named_data *data = NULL;

	if (!csr) {
		wpa_printf(MSG_ERROR, "%s: No csr", __func__);
		return NULL;
	}

	switch (attr) {
	case CSR_ATTR_CHALLENGE_PASSWORD:
		data = mbedtls_asn1_find_named_data(csr->write_ctx.MBEDTLS_PRIVATE(extensions),
				MBEDTLS_OID_PKCS9_CSR_CHALLENGE_PASSWORD,
				MBEDTLS_OID_SIZE(MBEDTLS_OID_PKCS9_CSR_CHALLENGE_PASSWORD));
		break;
	default:
		wpa_printf(MSG_ERROR, "%s: Invalid csr attr:%d", __func__, attr);
		return NULL;
	}

	if (!data) {
		wpa_printf(MSG_ERROR, "%s: Fail to get csr attr", __func__);
		return NULL;
	}

	*len = data->val.len;
	*type = data->val.tag;

	return data->val.p;
}

struct wpabuf * crypto_csr_sign(struct crypto_csr *csr,
				struct crypto_ec_key *key,
				enum crypto_hash_alg algo)
{
	struct wpabuf *buf = NULL;
	unsigned char der[MBEDTLS_ECP_MAX_PT_LEN];
	int der_len = 0;
	mbedtls_md_type_t md_alg = MBEDTLS_MD_NONE;
	mbedtls_entropy_context entropy;
	mbedtls_ctr_drbg_context ctr_drbg;

	if (!csr || !key) {
		wpa_printf(MSG_ERROR, "%s: No csr or key", __func__);
		return NULL;
	}

	switch (algo) {
	case CRYPTO_HASH_ALG_SHA256:
		md_alg = MBEDTLS_MD_SHA256;
		break;
	case CRYPTO_HASH_ALG_SHA384:
		md_alg = MBEDTLS_MD_SHA384;
		break;
	case CRYPTO_HASH_ALG_SHA512:
		md_alg = MBEDTLS_MD_SHA512;
		break;
	default:
		wpa_printf(MSG_ERROR, "%s: Invalid algo:%d", __func__, algo);
		return NULL;
	}
	mbedtls_x509write_csr_set_md_alg(&csr->write_ctx, md_alg);
	mbedtls_x509write_csr_set_key(&csr->write_ctx, (mbedtls_pk_context *) key);

	mbedtls_entropy_init(&entropy);
	mbedtls_ctr_drbg_init(&ctr_drbg);
	mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy, NULL, 0);

	der_len = mbedtls_x509write_csr_der(&csr->write_ctx, der,
					MBEDTLS_ECP_MAX_PT_LEN,
					mbedtls_ctr_drbg_random, &ctr_drbg);
	if (der_len < 0) {
		wpa_printf(MSG_ERROR, "%s: Fail to sign csr", __func__);
		mbedtls_ctr_drbg_free(&ctr_drbg);
		mbedtls_entropy_free(&entropy);
		return NULL;
	}
	mbedtls_ctr_drbg_free(&ctr_drbg);
	mbedtls_entropy_free(&entropy);

	buf = wpabuf_alloc_copy(der, der_len);

	return buf;
}

#define PEM_BEGIN_CRT           "-----BEGIN CERTIFICATE-----\n"
#define PEM_END_CRT             "-----END CERTIFICATE-----\n"
struct wpabuf * crypto_pkcs7_get_certificates(const struct wpabuf *pkcs7)
{
	struct wpabuf *buf = NULL;
	const unsigned char *p = wpabuf_head(pkcs7);
	mbedtls_pkcs7 pkcs7_ctx;
	mbedtls_x509_crt *certs;
	int i, num;
	size_t olen = 0;
	unsigned char output_buf[4096];

	mbedtls_pkcs7_init(&pkcs7_ctx);

	if (mbedtls_pkcs7_parse_der(&pkcs7_ctx, p, wpabuf_len(pkcs7)) != MBEDTLS_PKCS7_SIGNED_DATA) {
		wpa_printf(MSG_ERROR, "Fail to parse pkcs7", __func__);
		mbedtls_pkcs7_free(&pkcs7_ctx);
		return NULL;
	}

	num = pkcs7_ctx.MBEDTLS_PRIVATE(signed_data).MBEDTLS_PRIVATE(no_of_certs);
	certs = &pkcs7_ctx.MBEDTLS_PRIVATE(signed_data).MBEDTLS_PRIVATE(certs);
	for (i = 0; i < num; i++) {
		if (!certs) {
			break;
		}
		if (mbedtls_pem_write_buffer(PEM_BEGIN_CRT, PEM_END_CRT,
							certs->raw.p, certs->raw.len,
							output_buf, sizeof(output_buf), &olen) == 0) {
			if (buf) {
				if (wpabuf_resize(&buf, olen)) {
					wpa_printf(MSG_ERROR, "Fail to resize pem buf(%d)", __func__, olen);
					break;
				}
			} else {
				buf = wpabuf_alloc(olen);
				if (!buf) {
					wpa_printf(MSG_ERROR, "Fail to alloc pem buf(%d)", __func__, olen);
					break;
				}
			}
			wpabuf_put_data(buf, output_buf, olen);
		}
		certs = certs->next;
	}

	mbedtls_pkcs7_free(&pkcs7_ctx);

	return buf;
}