#ifndef _AES_CTR_CIPHER_HPP_
#define _AES_CTR_CIPHER_HPP_

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "mbedtls/cipher.h"

class AesCtrCipher {
public:
    // Constructor requires that key_input and nonce_input have exactly 16 bytes.
    // If not, valid is set to false.
    AesCtrCipher(const unsigned char* key_input, const unsigned char* nonce_input);
    
    // Returns true if the cipher was initialized properly.
    bool is_valid() const;
    
    // encrypts input buffer and allocates output buffer.
    // On success, returns 0, allocates *output (caller must free it), and sets *output_len.
    // On failure, returns nonzero and *output is undefined.
    int encrypt_buffer(const unsigned char* input, size_t input_len,
                       unsigned char** output, size_t* output_len);

    // In CTR mode, decryption is identical to encryption.
    int decrypt_buffer(const unsigned char* input, size_t input_len,
                       unsigned char** output, size_t* output_len) {
        return encrypt_buffer(input, input_len, output, output_len);
    }

private:
    unsigned char key[16];
    unsigned char nonce_counter[16];
    bool valid;
};

#endif // _AES_CTR_CIPHER_HPP_
