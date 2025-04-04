#include "aes_ctr_cipher.hpp"
#include "aes_ctr_cipher.hpp"
#include "FreeRTOS.h"

AesCtrCipher::AesCtrCipher(const unsigned char* key_input, const unsigned char* nonce_input)
    : valid(false)
{
    if (key_input == nullptr || nonce_input == nullptr) {
        return;
    }
    memcpy(key, key_input, 16);
    memcpy(nonce_counter, nonce_input, 16);
    valid = true;
}

bool AesCtrCipher::is_valid() const {
    return valid;
}

int AesCtrCipher::encrypt_buffer(const unsigned char* input, size_t input_len,
                                   unsigned char** output, size_t* output_len)
{
    if (!valid || input == nullptr || output == nullptr || output_len == nullptr) {
        return -1;
    }
    int ret;
    mbedtls_cipher_context_t ctx;
    const mbedtls_cipher_info_t *cipher_info;

    mbedtls_cipher_init(&ctx);
    cipher_info = mbedtls_cipher_info_from_type(MBEDTLS_CIPHER_AES_128_CTR);
    if (cipher_info == nullptr) {
        mbedtls_cipher_free(&ctx);
        return -2;
    }

    ret = mbedtls_cipher_setup(&ctx, cipher_info);
    if (ret != 0) {
        mbedtls_cipher_free(&ctx);
        return ret;
    }

    ret = mbedtls_cipher_setkey(&ctx, key, 128, MBEDTLS_ENCRYPT);
    if (ret != 0) {
        mbedtls_cipher_free(&ctx);
        return ret;
    }

    ret = mbedtls_cipher_set_iv(&ctx, nonce_counter, sizeof(nonce_counter));
    if (ret != 0) {
        mbedtls_cipher_free(&ctx);
        return ret;
    }

    ret = mbedtls_cipher_reset(&ctx);
    if (ret != 0) {
        mbedtls_cipher_free(&ctx);
        return ret;
    }

    // In CTR mode, output length equals input length.
    *output = (unsigned char*)pvPortMalloc(input_len);
    if (*output == nullptr) {
        mbedtls_cipher_free(&ctx);
        return -3;
    }

    size_t olen = 0;
    ret = mbedtls_cipher_update(&ctx, input, input_len, *output, &olen);
    if (ret != 0) {
        vPortFree(*output);
        mbedtls_cipher_free(&ctx);
        return ret;
    }

    size_t finish_olen = 0;
    ret = mbedtls_cipher_finish(&ctx, *output + olen, &finish_olen);
    if (ret != 0) {
        vPortFree(*output);
        mbedtls_cipher_free(&ctx);
        return ret;
    }
    mbedtls_cipher_free(&ctx);
    *output_len = olen + finish_olen;
    return 0;
}
