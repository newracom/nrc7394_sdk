/*
 * MIT License
 *
 * Copyright (c) 2022 Newracom, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "nrc_sdk.h"
#include "nvs_flash.h"       // For nvs_flash_init(), etc.
#include "nvs.h"             // For nvs_open(), nvs_set_xxx(), nvs_get_xxx(), etc.

// -----------------------------------------------------------------------------
// Test function for plain (unencrypted) NVS operations for all data types.
// -----------------------------------------------------------------------------
nvs_err_t run_nvs_test_all_plain()
{
    nvs_err_t err = NVS_OK;
    nvs_handle_t handle;

    err = nvs_open(NVS_DEFAULT_NAMESPACE, NVS_READWRITE, &handle);
    if (err != NVS_OK) {
        nrc_usr_print("[PLAIN] nvs_open failed (0x%x).\n", err);
        return NRC_FAIL;
    }

    // Test int8_t
    int8_t test_i8 = -123;
    nrc_usr_print("[PLAIN] Setting int8_t key 'i8key' = %d\n", test_i8);
    err = nvs_set_i8(handle, "i8key", test_i8);
    if (err != NVS_OK) {
        nrc_usr_print("[PLAIN] nvs_set_i8 failed (0x%x).\n", err);
        goto exit;
    }
    int8_t read_i8 = 0;
    err = nvs_get_i8(handle, "i8key", &read_i8);
    nrc_usr_print("[PLAIN] Retrieved int8_t 'i8key' = %d (expected %d)\n", read_i8, test_i8);
    if (err != NVS_OK || read_i8 != test_i8) {
        nrc_usr_print("[PLAIN] nvs_get_i8 failed or mismatch (0x%x, read %d).\n", err, read_i8);
        goto exit;
    }

    // Test uint8_t
    uint8_t test_u8 = 250;
    nrc_usr_print("[PLAIN] Setting uint8_t key 'u8key' = %d\n", test_u8);
    err = nvs_set_u8(handle, "u8key", test_u8);
    if (err != NVS_OK) {
        nrc_usr_print("[PLAIN] nvs_set_u8 failed (0x%x).\n", err);
        goto exit;
    }
    uint8_t read_u8 = 0;
    err = nvs_get_u8(handle, "u8key", &read_u8);
    nrc_usr_print("[PLAIN] Retrieved uint8_t 'u8key' = %d (expected %d)\n", read_u8, test_u8);
    if (err != NVS_OK || read_u8 != test_u8) {
        nrc_usr_print("[PLAIN] nvs_get_u8 failed or mismatch (0x%x, read %d).\n", err, read_u8);
        goto exit;
    }

    // Test int16_t
    int16_t test_i16 = -12345;
    nrc_usr_print("[PLAIN] Setting int16_t key 'i16key' = %d\n", test_i16);
    err = nvs_set_i16(handle, "i16key", test_i16);
    if (err != NVS_OK) {
        nrc_usr_print("[PLAIN] nvs_set_i16 failed (0x%x).\n", err);
        goto exit;
    }
    int16_t read_i16 = 0;
    err = nvs_get_i16(handle, "i16key", &read_i16);
    nrc_usr_print("[PLAIN] Retrieved int16_t 'i16key' = %d (expected %d)\n", read_i16, test_i16);
    if (err != NVS_OK || read_i16 != test_i16) {
        nrc_usr_print("[PLAIN] nvs_get_i16 failed or mismatch (0x%x, read %d).\n", err, read_i16);
        goto exit;
    }

    // Test uint16_t
    uint16_t test_u16 = 54321;
    nrc_usr_print("[PLAIN] Setting uint16_t key 'u16key' = %d\n", test_u16);
    err = nvs_set_u16(handle, "u16key", test_u16);
    if (err != NVS_OK) {
        nrc_usr_print("[PLAIN] nvs_set_u16 failed (0x%x).\n", err);
        goto exit;
    }
    uint16_t read_u16 = 0;
    err = nvs_get_u16(handle, "u16key", &read_u16);
    nrc_usr_print("[PLAIN] Retrieved uint16_t 'u16key' = %d (expected %d)\n", read_u16, test_u16);
    if (err != NVS_OK || read_u16 != test_u16) {
        nrc_usr_print("[PLAIN] nvs_get_u16 failed or mismatch (0x%x, read %d).\n", err, read_u16);
        goto exit;
    }

    // Test int32_t
    int32_t test_i32 = -0x12345678;
    nrc_usr_print("[PLAIN] Setting int32_t key 'i32key' = 0x%x\n", test_i32);
    err = nvs_set_i32(handle, "i32key", test_i32);
    if (err != NVS_OK) {
        nrc_usr_print("[PLAIN] nvs_set_i32 failed (0x%x).\n", err);
        goto exit;
    }
    int32_t read_i32 = 0;
    err = nvs_get_i32(handle, "i32key", &read_i32);
    nrc_usr_print("[PLAIN] Retrieved int32_t 'i32key' = 0x%x (expected 0x%x)\n", read_i32, test_i32);
    if (err != NVS_OK || read_i32 != test_i32) {
        nrc_usr_print("[PLAIN] nvs_get_i32 failed or mismatch (0x%x, read 0x%x).\n", err, read_i32);
        goto exit;
    }

    // Test uint32_t
    uint32_t test_u32 = 0x12345678;
    nrc_usr_print("[PLAIN] Setting uint32_t key 'u32key' = 0x%x\n", test_u32);
    err = nvs_set_u32(handle, "u32key", test_u32);
    if (err != NVS_OK) {
        nrc_usr_print("[PLAIN] nvs_set_u32 failed (0x%x).\n", err);
        goto exit;
    }
    uint32_t read_u32 = 0;
    err = nvs_get_u32(handle, "u32key", &read_u32);
    nrc_usr_print("[PLAIN] Retrieved uint32_t 'u32key' = 0x%x (expected 0x%x)\n", read_u32, test_u32);
    if (err != NVS_OK || read_u32 != test_u32) {
        nrc_usr_print("[PLAIN] nvs_get_u32 failed or mismatch (0x%x, read 0x%x).\n", err, read_u32);
        goto exit;
    }

    // Test int64_t
    int64_t test_i64 = -0x1234567890ABCDEFLL;
    nrc_usr_print("[PLAIN] Setting int64_t key 'i64key' = 0x%llx\n", test_i64);
    err = nvs_set_i64(handle, "i64key", test_i64);
    if (err != NVS_OK) {
        nrc_usr_print("[PLAIN] nvs_set_i64 failed (0x%x).\n", err);
        goto exit;
    }
    int64_t read_i64 = 0;
    err = nvs_get_i64(handle, "i64key", &read_i64);
    nrc_usr_print("[PLAIN] Retrieved int64_t 'i64key' = 0x%llx (expected 0x%llx)\n", read_i64, test_i64);
    if (err != NVS_OK || read_i64 != test_i64) {
        nrc_usr_print("[PLAIN] nvs_get_i64 failed or mismatch (0x%x, read 0x%llx).\n", err, read_i64);
        goto exit;
    }

    // Test uint64_t
    uint64_t test_u64 = 0x1234567890ABCDEFULL;
    nrc_usr_print("[PLAIN] Setting uint64_t key 'u64key' = 0x%llx\n", test_u64);
    err = nvs_set_u64(handle, "u64key", test_u64);
    if (err != NVS_OK) {
        nrc_usr_print("[PLAIN] nvs_set_u64 failed (0x%x).\n", err);
        goto exit;
    }
    uint64_t read_u64 = 0;
    err = nvs_get_u64(handle, "u64key", &read_u64);
    nrc_usr_print("[PLAIN] Retrieved uint64_t 'u64key' = 0x%llx (expected 0x%llx)\n", read_u64, test_u64);
    if (err != NVS_OK || read_u64 != test_u64) {
        nrc_usr_print("[PLAIN] nvs_get_u64 failed or mismatch (0x%x, read 0x%llx).\n", err, read_u64);
        goto exit;
    }

    // Test string
    const char* test_str = "Hello, plain world!";
    nrc_usr_print("[PLAIN] Setting string key 'strkey' = %s\n", test_str);
    err = nvs_set_str(handle, "strkey", test_str);
    if (err != NVS_OK) {
        nrc_usr_print("[PLAIN] nvs_set_str failed (0x%x).\n", err);
        goto exit;
    }
    char str_buf[64] = {0};
    size_t str_buf_len = sizeof(str_buf);
    err = nvs_get_str(handle, "strkey", str_buf, &str_buf_len);
    nrc_usr_print("[PLAIN] Retrieved string 'strkey' = %s (expected %s)\n", str_buf, test_str);
    if (err != NVS_OK || strcmp(test_str, str_buf) != 0) {
        nrc_usr_print("[PLAIN] nvs_get_str failed or mismatch (0x%x, got %s).\n", err, str_buf);
        goto exit;
    }

    // Test blob
    const char blob_data[] = "Plain blob data";
    nrc_usr_print("[PLAIN] Setting blob key 'blobkey' = %s\n", blob_data);
    err = nvs_set_blob(handle, "blobkey", blob_data, sizeof(blob_data));
    if (err != NVS_OK) {
        nrc_usr_print("[PLAIN] nvs_set_blob failed (0x%x).\n", err);
        goto exit;
    }
    char blob_buf[128] = {0};
    size_t blob_buf_len = sizeof(blob_buf);
    err = nvs_get_blob(handle, "blobkey", blob_buf, &blob_buf_len);
    nrc_usr_print("[PLAIN] Retrieved blob 'blobkey' = %s (expected %s)\n", blob_buf, blob_data);
    if (err != NVS_OK || strcmp(blob_data, blob_buf) != 0) {
        nrc_usr_print("[PLAIN] nvs_get_blob failed or mismatch (0x%x, got %s).\n", err, blob_buf);
        goto exit;
    }

exit:
    nvs_close(handle);
    return (err == NVS_OK) ? NRC_SUCCESS : NRC_FAIL;
}

// -----------------------------------------------------------------------------
// Test function for encryption-enabled NVS operations for all data types.
// -----------------------------------------------------------------------------
nvs_err_t run_nvs_test_all_encrypt()
{
    nvs_err_t err = NVS_OK;
    nvs_handle_t handle;

    // Set up encryption using a 16-byte key and 16-byte nonce.
    const unsigned char encryption_key[16] = {
        0x01, 0x02, 0x03, 0x04,
        0x05, 0x06, 0x07, 0x08,
        0x09, 0x0A, 0x0B, 0x0C,
        0x0D, 0x0E, 0x0F, 0x10
    };
    const unsigned char encryption_nonce[16] = {
        0x10, 0x0F, 0x0E, 0x0D,
        0x0C, 0x0B, 0x0A, 0x09,
        0x08, 0x07, 0x06, 0x05,
        0x04, 0x03, 0x02, 0x01
    };

    nrc_usr_print("[ENCRYPT] Enabling encryption...\n");
    err = nvs_set_encrypt(encryption_key, encryption_nonce);
    if (err != NVS_OK) {
        nrc_usr_print("[ENCRYPT] nvs_set_encrypt failed (0x%x).\n", err);
        return NRC_FAIL;
    }

    err = nvs_open(NVS_DEFAULT_NAMESPACE, NVS_READWRITE, &handle);
    if (err != NVS_OK) {
        nrc_usr_print("[ENCRYPT] nvs_open failed (0x%x).\n", err);
        nvs_clear_encrypt();
        return NRC_FAIL;
    }

    // Numeric values (all types) will be encrypted via our template functions.

    // Test int8_t
    int8_t test_i8 = -123;
    nrc_usr_print("[ENCRYPT] Setting int8_t key 'i8key' = %d\n", test_i8);
    err = nvs_set_i8(handle, "i8key", test_i8);
    if (err != NVS_OK) {
        nrc_usr_print("[ENCRYPT] nvs_set_i8 failed (0x%x).\n", err);
        goto exit;
    }
    int8_t read_i8 = 0;
    err = nvs_get_i8(handle, "i8key", &read_i8);
    nrc_usr_print("[ENCRYPT] Retrieved int8_t 'i8key' = %d (expected %d)\n", read_i8, test_i8);
    if (err != NVS_OK || read_i8 != test_i8) {
        nrc_usr_print("[ENCRYPT] nvs_get_i8 failed or mismatch (0x%x, read %d).\n", err, read_i8);
        goto exit;
    }

    // Test uint8_t
    uint8_t test_u8 = 250;
    nrc_usr_print("[ENCRYPT] Setting uint8_t key 'u8key' = %d\n", test_u8);
    err = nvs_set_u8(handle, "u8key", test_u8);
    if (err != NVS_OK) {
        nrc_usr_print("[ENCRYPT] nvs_set_u8 failed (0x%x).\n", err);
        goto exit;
    }
    uint8_t read_u8 = 0;
    err = nvs_get_u8(handle, "u8key", &read_u8);
    nrc_usr_print("[ENCRYPT] Retrieved uint8_t 'u8key' = %d (expected %d)\n", read_u8, test_u8);
    if (err != NVS_OK || read_u8 != test_u8) {
        nrc_usr_print("[ENCRYPT] nvs_get_u8 failed or mismatch (0x%x, read %d).\n", err, read_u8);
        goto exit;
    }

    // Test int16_t
    int16_t test_i16 = -12345;
    nrc_usr_print("[ENCRYPT] Setting int16_t key 'i16key' = %d\n", test_i16);
    err = nvs_set_i16(handle, "i16key", test_i16);
    if (err != NVS_OK) {
        nrc_usr_print("[ENCRYPT] nvs_set_i16 failed (0x%x).\n", err);
        goto exit;
    }
    int16_t read_i16 = 0;
    err = nvs_get_i16(handle, "i16key", &read_i16);
    nrc_usr_print("[ENCRYPT] Retrieved int16_t 'i16key' = %d (expected %d)\n", read_i16, test_i16);
    if (err != NVS_OK || read_i16 != test_i16) {
        nrc_usr_print("[ENCRYPT] nvs_get_i16 failed or mismatch (0x%x, read %d).\n", err, read_i16);
        goto exit;
    }

    // Test uint16_t
    uint16_t test_u16 = 54321;
    nrc_usr_print("[ENCRYPT] Setting uint16_t key 'u16key' = %d\n", test_u16);
    err = nvs_set_u16(handle, "u16key", test_u16);
    if (err != NVS_OK) {
        nrc_usr_print("[ENCRYPT] nvs_set_u16 failed (0x%x).\n", err);
        goto exit;
    }
    uint16_t read_u16 = 0;
    err = nvs_get_u16(handle, "u16key", &read_u16);
    nrc_usr_print("[ENCRYPT] Retrieved uint16_t 'u16key' = %d (expected %d)\n", read_u16, test_u16);
    if (err != NVS_OK || read_u16 != test_u16) {
        nrc_usr_print("[ENCRYPT] nvs_get_u16 failed or mismatch (0x%x, read %d).\n", err, read_u16);
        goto exit;
    }

    // Test int32_t
    int32_t test_i32 = -0x12345678;
    nrc_usr_print("[ENCRYPT] Setting int32_t key 'i32key' = 0x%x\n", test_i32);
    err = nvs_set_i32(handle, "i32key", test_i32);
    if (err != NVS_OK) {
        nrc_usr_print("[ENCRYPT] nvs_set_i32 failed (0x%x).\n", err);
        goto exit;
    }
    int32_t read_i32 = 0;
    err = nvs_get_i32(handle, "i32key", &read_i32);
    nrc_usr_print("[ENCRYPT] Retrieved int32_t 'i32key' = 0x%x (expected 0x%x)\n", read_i32, test_i32);
    if (err != NVS_OK || read_i32 != test_i32) {
        nrc_usr_print("[ENCRYPT] nvs_get_i32 failed or mismatch (0x%x, read 0x%x).\n", err, read_i32);
        goto exit;
    }

    // Test uint32_t
    uint32_t test_u32 = 0x12345678;
    nrc_usr_print("[ENCRYPT] Setting uint32_t key 'u32key' = 0x%x\n", test_u32);
    err = nvs_set_u32(handle, "u32key", test_u32);
    if (err != NVS_OK) {
        nrc_usr_print("[ENCRYPT] nvs_set_u32 failed (0x%x).\n", err);
        goto exit;
    }
    uint32_t read_u32 = 0;
    err = nvs_get_u32(handle, "u32key", &read_u32);
    nrc_usr_print("[ENCRYPT] Retrieved uint32_t 'u32key' = 0x%x (expected 0x%x)\n", read_u32, test_u32);
    if (err != NVS_OK || read_u32 != test_u32) {
        nrc_usr_print("[ENCRYPT] nvs_get_u32 failed or mismatch (0x%x, read 0x%x).\n", err, read_u32);
        goto exit;
    }

    // Test int64_t
    int64_t test_i64 = -0x1234567890ABCDEFLL;
    nrc_usr_print("[ENCRYPT] Setting int64_t key 'i64key' = 0x%llx\n", test_i64);
    err = nvs_set_i64(handle, "i64key", test_i64);
    if (err != NVS_OK) {
        nrc_usr_print("[ENCRYPT] nvs_set_i64 failed (0x%x).\n", err);
        goto exit;
    }
    int64_t read_i64 = 0;
    err = nvs_get_i64(handle, "i64key", &read_i64);
    nrc_usr_print("[ENCRYPT] Retrieved int64_t 'i64key' = 0x%llx (expected 0x%llx)\n", read_i64, test_i64);
    if (err != NVS_OK || read_i64 != test_i64) {
        nrc_usr_print("[ENCRYPT] nvs_get_i64 failed or mismatch (0x%x, read 0x%llx).\n", err, read_i64);
        goto exit;
    }

    // Test uint64_t
    uint64_t test_u64 = 0x1234567890ABCDEFULL;
    nrc_usr_print("[ENCRYPT] Setting uint64_t key 'u64key' = 0x%llx\n", test_u64);
    err = nvs_set_u64(handle, "u64key", test_u64);
    if (err != NVS_OK) {
        nrc_usr_print("[ENCRYPT] nvs_set_u64 failed (0x%x).\n", err);
        goto exit;
    }
    uint64_t read_u64 = 0;
    err = nvs_get_u64(handle, "u64key", &read_u64);
    nrc_usr_print("[ENCRYPT] Retrieved uint64_t 'u64key' = 0x%llx (expected 0x%llx)\n", read_u64, test_u64);
    if (err != NVS_OK || read_u64 != test_u64) {
        nrc_usr_print("[ENCRYPT] nvs_get_u64 failed or mismatch (0x%x, read 0x%llx).\n", err, read_u64);
        goto exit;
    }

    // Test string
    const char* test_str = "Hello, encrypted world!";
    nrc_usr_print("[ENCRYPT] Setting string key 'strkey' = %s\n", test_str);
    err = nvs_set_str(handle, "strkey", test_str);
    if (err != NVS_OK) {
        nrc_usr_print("[ENCRYPT] nvs_set_str failed (0x%x).\n", err);
        goto exit;
    }
    char str_buf[64] = {0};
    size_t str_buf_len = sizeof(str_buf);
    err = nvs_get_str(handle, "strkey", str_buf, &str_buf_len);
    nrc_usr_print("[ENCRYPT] Retrieved string 'strkey' = %s (expected %s)\n", str_buf, test_str);
    if (err != NVS_OK || strcmp(test_str, str_buf) != 0) {
        nrc_usr_print("[ENCRYPT] nvs_get_str failed or mismatch (0x%x, got %s).\n", err, str_buf);
        goto exit;
    }

    // Test blob
    const char blob_data[] = "Encrypted blob data";
    nrc_usr_print("[ENCRYPT] Setting blob key 'blobkey' = %s\n", blob_data);
    err = nvs_set_blob(handle, "blobkey", blob_data, sizeof(blob_data));
    if (err != NVS_OK) {
        nrc_usr_print("[ENCRYPT] nvs_set_blob failed (0x%x).\n", err);
        goto exit;
    }
    char blob_buf[128] = {0};
    size_t blob_buf_len = sizeof(blob_buf);
    err = nvs_get_blob(handle, "blobkey", blob_buf, &blob_buf_len);
    nrc_usr_print("[ENCRYPT] Retrieved blob 'blobkey' = %s (expected %s)\n", blob_buf, blob_data);
    if (err != NVS_OK || strcmp(blob_data, blob_buf) != 0) {
        nrc_usr_print("[ENCRYPT] nvs_get_blob failed or mismatch (0x%x, got %s).\n", err, blob_buf);
        goto exit;
    }

exit:
    nvs_close(handle);
    nvs_clear_encrypt();
    return (err == NVS_OK) ? NRC_SUCCESS : NRC_FAIL;
}

// -----------------------------------------------------------------------------
// Entry point: Demonstrates both plain and encryption-enabled NVS operations for all data types.
// -----------------------------------------------------------------------------
void user_init(void)
{
    nrc_usr_print("Starting NVS Test in Plain Mode (all data types)...\n");
    if (run_nvs_test_all_plain() != NRC_SUCCESS) {
        nrc_usr_print("Plain Mode test FAILED!\n");
    } else {
        nrc_usr_print("Plain Mode test succeeded.\n");
    }

    nrc_usr_print("Starting NVS Test in Encryption Mode (all data types)...\n");
    if (run_nvs_test_all_encrypt() != NRC_SUCCESS) {
        nrc_usr_print("Encryption Mode test FAILED!\n");
    } else {
        nrc_usr_print("Encryption Mode test succeeded.\n");
    }
}
