// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "nvs.hpp"
#include "nvs_flash.h"
#include "nvs_storage.hpp"
#include "intrusive_list.h"
#include "nvs_platform.hpp"
#include "nvs_partition_manager.hpp"
#include <functional>
#include "nvs_handle_simple.hpp"
#include "aes_ctr_cipher.hpp"

static const char* TAG = "nvs";

static AesCtrCipher *g_aes_cipher = nullptr;

class NVSHandleEntry : public intrusive_list_node<NVSHandleEntry> {
public:
    NVSHandleEntry(nvs::NVSHandleSimple *handle, const char* part_name)
        : nvs_handle(handle),
        mHandle(++s_nvs_next_handle),
        handle_part_name(part_name) { }

    ~NVSHandleEntry() {
        delete nvs_handle;
    }

    nvs::NVSHandleSimple *nvs_handle;
    nvs_handle_t mHandle;
    const char* handle_part_name;
private:
    static uint32_t s_nvs_next_handle;
};

uint32_t NVSHandleEntry::s_nvs_next_handle;

extern "C" void nvs_dump(const char *partName);

#ifndef LINUX_TARGET
SemaphoreHandle_t nvs::Lock::mSemaphore = nullptr;
#endif // ! LINUX_TARGET

using namespace std;
using namespace nvs;

static intrusive_list<NVSHandleEntry> s_nvs_handles;

// Helper function to handle encrypted data convert to hex
static char* bytes_to_hex(const unsigned char *bytes, size_t len)
{
    size_t hex_len = len * 2 + 1;
    char *hex_str = (char *)pvPortMalloc(hex_len);
    if (!hex_str)
        return NULL;
    for (size_t i = 0; i < len; i++) {
        sprintf(&hex_str[i * 2], "%02x", bytes[i]);
    }
    hex_str[hex_len - 1] = '\0';
    return hex_str;
}

static unsigned char* hex_to_bytes(const char* hex_str, size_t* out_len)
{
    if (!hex_str || !out_len)
        return NULL;
    size_t hex_len = strlen(hex_str);
    if (hex_len % 2 != 0)
        return NULL;
    *out_len = hex_len / 2;
    unsigned char* buf = (unsigned char*)pvPortMalloc(*out_len);
    if (!buf)
        return NULL;
    for (size_t i = 0; i < *out_len; i++) {
        unsigned int byte;
        if (sscanf(&hex_str[i * 2], "%02x", &byte) != 1) {
            vPortFree(buf);
            return NULL;
        }
        buf[i] = (unsigned char)byte;
    }
    return buf;
}

static nvs::Storage* lookup_storage_from_name(const char *name)
{
    return NVSPartitionManager::get_instance()->lookup_storage_from_name(name);
}

extern "C" void nvs_dump(const char *partName)
{
    Lock lock;
    nvs::Storage* pStorage = lookup_storage_from_name(partName);
    if (pStorage == nullptr) {
        return;
    }
    pStorage->debugDump();
}

static nvs_err_t close_handles_and_deinit(const char* part_name)
{
    auto belongs_to_part = [=](NVSHandleEntry& e) -> bool {
        return strncmp(e.nvs_handle->get_partition_name(), part_name, NVS_PART_NAME_MAX_SIZE) == 0;
    };

    auto it = find_if(begin(s_nvs_handles), end(s_nvs_handles), belongs_to_part);

    while (it != end(s_nvs_handles)) {
        s_nvs_handles.erase(it);
        it = find_if(begin(s_nvs_handles), end(s_nvs_handles), belongs_to_part);
    }

    // Deinit partition
    return NVSPartitionManager::get_instance()->deinit_partition(part_name);
}

extern "C" nvs_err_t nvs_flash_init_partition_ptr(uint32_t address, size_t size)
{
    nvs_err_t lock_result = Lock::init();
    if (lock_result != NVS_OK) {
        return lock_result;
    }
    Lock lock;

    NVSPartition *part = new (std::nothrow) NVSPartition(address, size);
    if (part == nullptr) {
        return NVS_ERR_NO_MEM;
    }

    nvs_err_t init_res = NVSPartitionManager::get_instance()->init_custom(part,
            address / SPI_FLASH_SEC_SIZE,
            size / SPI_FLASH_SEC_SIZE);

    if (init_res != NVS_OK) {
        delete part;
    }

    return init_res;
}

#ifndef LINUX_TARGET
extern "C" nvs_err_t nvs_flash_init_partition(const char *part_name)
{
    nvs_err_t lock_result = Lock::init();
	NVS_LOGD(TAG, "[%s] lock_result = %d\n", __func__, lock_result);
    if (lock_result != NVS_OK) {
        return lock_result;
    }
    Lock lock;
    NVS_LOGD(TAG, "[%s] lock acquired.\n", __func__);
    return NVSPartitionManager::get_instance()->init_partition(part_name);
}

extern "C" nvs_err_t nvs_flash_init(void)
{
    return nvs_flash_init_partition(NVS_DEFAULT_PART_NAME);
}

extern "C" nvs_err_t nvs_set_encrypt(const unsigned char* key, const unsigned char* nonce)
{
    if (!key || !nonce) {
        return NVS_ERR_INVALID_ARG;
    }

    AesCtrCipher* cipher = new AesCtrCipher(key, nonce);
    if (!cipher->is_valid()) {
        delete cipher;
        return NVS_ERR_INVALID_ARG;
    }
    if (g_aes_cipher) {
        delete g_aes_cipher;
    }
    g_aes_cipher = cipher;
    return NVS_OK;
}

extern "C" void nvs_clear_encrypt()
{
    if (g_aes_cipher) {
        delete g_aes_cipher;
        g_aes_cipher = nullptr;
    }
}

extern "C" nvs_err_t nvs_flash_erase_partition(const char *part_name)
{
    nvs_err_t lock_result = Lock::init();
    if (lock_result != NVS_OK) {
        return lock_result;
    }
    Lock lock;

    // if the partition is initialized, uninitialize it first
    if (NVSPartitionManager::get_instance()->lookup_storage_from_name(part_name)) {
        nvs_err_t err = close_handles_and_deinit(part_name);

        // only hypothetical/future case, deinit_partition() only fails if partition is uninitialized
        if (err != NVS_OK) {
            return err;
        }
    }
    uint32_t address;
    if (strcmp(part_name, "USER_CONFIG_1") == 0) {
        address = SF_USER_CONFIG_1;
    } else {
        return NVS_ERR_NVS_PART_NOT_FOUND;
    }
    for (int i = 0; i < MIN_PARTITION_SIZE / 4096; i++) {
        if (nrc_sf_erase(address + (i * 4096), 4096) != true)
            return NVS_FAIL;
    }
    return NVS_OK;
}

extern "C" nvs_err_t nvs_flash_erase_partition_ptr(uint32_t address, size_t size)
{
    nvs_err_t lock_result = Lock::init();
    if (lock_result != NVS_OK) {
        return lock_result;
    }
    Lock lock;
    if (nrc_sf_erase(address, size) == true) {
        return NVS_OK;
    } else {
        return NVS_FAIL;
    }
}

extern "C" nvs_err_t nvs_flash_erase(void)
{
    return nvs_flash_erase_partition(NVS_DEFAULT_PART_NAME);
}
#endif // ! LINUX_TARGET

extern "C" nvs_err_t nvs_flash_deinit_partition(const char* partition_name)
{
    nvs_err_t lock_result = Lock::init();
    if (lock_result != NVS_OK) {
        return lock_result;
    }
    Lock lock;

    return close_handles_and_deinit(partition_name);
}

extern "C" nvs_err_t nvs_flash_deinit(void)
{
    return nvs_flash_deinit_partition(NVS_DEFAULT_PART_NAME);
}

static nvs_err_t nvs_find_ns_handle(nvs_handle_t c_handle, NVSHandleSimple** handle)
{
    auto it = find_if(begin(s_nvs_handles), end(s_nvs_handles), [=](NVSHandleEntry& e) -> bool {
        return e.mHandle == c_handle;
    });
    if (it == end(s_nvs_handles)) {
        return NVS_ERR_NVS_INVALID_HANDLE;
    }
    *handle = it->nvs_handle;
    return NVS_OK;
}

extern "C" nvs_err_t nvs_open_from_partition(const char *part_name, const char* name, nvs_open_mode_t open_mode, nvs_handle_t *out_handle)
{
    Lock lock;
    NVS_LOGD(TAG, "[%s] %s %d", __func__, name, open_mode);

    NVSHandleSimple *handle;
    nvs_err_t result = NVSPartitionManager::get_instance()->open_handle(part_name, name, open_mode, &handle);
    NVS_LOGD(TAG, "[%s]  open_handle result : %d", __func__, result);
    if (result == NVS_ERR_NVS_NOT_INITIALIZED) {
        result = nvs_flash_init();
        if (result == NVS_ERR_NVS_NO_FREE_PAGES || result == NVS_ERR_NVS_NEW_VERSION_FOUND) {
            if ((result = nvs_flash_erase()) == NVS_OK) {
                result = nvs_flash_init();
            }
        }
        result = NVSPartitionManager::get_instance()->open_handle(part_name, name, open_mode, &handle);
    }
    if (result == NVS_OK) {
        NVSHandleEntry *entry = new (std::nothrow) NVSHandleEntry(handle, part_name);
        if (entry) {
            s_nvs_handles.push_back(entry);
            *out_handle = entry->mHandle;
        } else {
            delete handle;
            return NVS_ERR_NO_MEM;
        }
    }

    return result;
}

extern "C" nvs_err_t nvs_open(const char* name, nvs_open_mode_t open_mode, nvs_handle_t *out_handle)
{
    return nvs_open_from_partition(NVS_DEFAULT_PART_NAME, name, open_mode, out_handle);
}

extern "C" void nvs_close(nvs_handle_t handle)
{
    Lock lock;
    NVS_LOGD(TAG, "[%s] %d", __func__, static_cast<int>(handle));
    auto it = find_if(begin(s_nvs_handles), end(s_nvs_handles), [=](NVSHandleEntry& e) -> bool {
        return e.mHandle == handle;
    });
    if (it == end(s_nvs_handles)) {
        return;
    }
    s_nvs_handles.erase(it);
    delete static_cast<NVSHandleEntry*>(it);
}

extern "C" nvs_err_t nvs_erase_key(nvs_handle_t c_handle, const char* key)
{
    Lock lock;
    NVS_LOGD(TAG, "[%s] key: %s\r\n", __func__, key);
    NVSHandleSimple *handle;
    auto err = nvs_find_ns_handle(c_handle, &handle);
    if (err != NVS_OK) {
        return err;
    }

    if (g_aes_cipher != nullptr) {
        // Encrypt the key and convert to a hex string.
        size_t key_len = strlen(key);
        unsigned char *encrypted_key = NULL;
        size_t encrypted_key_len = 0;
        if (g_aes_cipher->encrypt_buffer((const unsigned char *)key, key_len,
                                         &encrypted_key, &encrypted_key_len) != 0) {
            return handle->erase_item(key);
        }
        char *hex_key = bytes_to_hex(encrypted_key, encrypted_key_len);
        vPortFree(encrypted_key);
        if (hex_key == NULL) {
            return handle->erase_item(key);
        }
        // First, try erasing using the encrypted (hex) key.
        err = handle->erase_item(hex_key);
        vPortFree(hex_key);
        if (err != NVS_OK) {
            // If that fails, try erasing using the plain text key.
            err = handle->erase_item(key);
        }
        return err;
    } else {
        return handle->erase_item(key);
    }
}

extern "C" nvs_err_t nvs_erase_all(nvs_handle_t c_handle)
{
    Lock lock;
    NVS_LOGD(TAG, "[%s]\r\n", __func__);
    NVSHandleSimple *handle;
    auto err = nvs_find_ns_handle(c_handle, &handle);
    if (err != NVS_OK) {
        return err;
    }

    return handle->erase_all();
}

template<typename T>
static nvs_err_t nvs_set(nvs_handle_t c_handle, const char* key, T value)
{
    Lock lock;
    NVS_LOGD(TAG, "[%s] key: %s, size: %d", __func__, key, static_cast<int>(sizeof(T)));
    NVSHandleSimple *handle;
    nvs_err_t err = nvs_find_ns_handle(c_handle, &handle);
    if (err != NVS_OK)
        return err;

    if (g_aes_cipher != nullptr)
    {
        // Erase any plain-text entry stored with the key.
        handle->erase_item(key);
        // Encrypt the key.
        size_t key_len = strlen(key);
        unsigned char *encrypted_key = NULL;
        size_t encrypted_key_len = 0;
        if (g_aes_cipher->encrypt_buffer((const unsigned char*)key, key_len,
                                         &encrypted_key, &encrypted_key_len) != 0)
        {
            return NVS_FAIL;
        }
        char* hex_key = bytes_to_hex(encrypted_key, encrypted_key_len);
        vPortFree(encrypted_key);
        if (hex_key == NULL)
            return NVS_ERR_NO_MEM;

        // Now, treat the value as a raw binary buffer.
        const unsigned char* plain_buf = reinterpret_cast<const unsigned char*>(&value);
        size_t plain_len = sizeof(T);
        unsigned char* encrypted_value = NULL;
        size_t encrypted_value_len = 0;
        if (g_aes_cipher->encrypt_buffer(plain_buf, plain_len,
                                         &encrypted_value, &encrypted_value_len) != 0)
        {
            vPortFree(hex_key);
            return NVS_FAIL;
        }
        // Convert encrypted binary data to hex string.
        char* hex_value = bytes_to_hex(encrypted_value, encrypted_value_len);
        vPortFree(encrypted_value);
        if (hex_value == NULL)
        {
            vPortFree(hex_key);
            return NVS_ERR_NO_MEM;
        }
        // Store the value using set_blob (the length is the length of the hex string + 1 for null)
        err = handle->set_blob(hex_key, hex_value, strlen(hex_value) + 1);
        vPortFree(hex_key);
        vPortFree(hex_value);
        return err;
    }
    else
    {
        return handle->set_item(key, value);
    }
}

extern "C" nvs_err_t nvs_set_i8  (nvs_handle_t handle, const char* key, int8_t value)
{
    return nvs_set(handle, key, value);
}

extern "C" nvs_err_t nvs_set_u8  (nvs_handle_t handle, const char* key, uint8_t value)
{
    return nvs_set(handle, key, value);
}

extern "C" nvs_err_t nvs_set_i16 (nvs_handle_t handle, const char* key, int16_t value)
{
    return nvs_set(handle, key, value);
}

extern "C" nvs_err_t nvs_set_u16 (nvs_handle_t handle, const char* key, uint16_t value)
{
    return nvs_set(handle, key, value);
}

extern "C" nvs_err_t nvs_set_i32 (nvs_handle_t handle, const char* key, int32_t value)
{
    return nvs_set(handle, key, value);
}

extern "C" nvs_err_t nvs_set_u32 (nvs_handle_t handle, const char* key, uint32_t value)
{
    return nvs_set(handle, key, value);
}

extern "C" nvs_err_t nvs_set_i64 (nvs_handle_t handle, const char* key, int64_t value)
{
    return nvs_set(handle, key, value);
}

extern "C" nvs_err_t nvs_set_u64 (nvs_handle_t handle, const char* key, uint64_t value)
{
    return nvs_set(handle, key, value);
}

extern "C" nvs_err_t nvs_commit(nvs_handle_t c_handle)
{
    Lock lock;
    NVSHandleSimple *handle;
    auto err = nvs_find_ns_handle(c_handle, &handle);
    if (err != NVS_OK) {
        return err;
    }
    return handle->commit();
}

extern "C" nvs_err_t nvs_set_str(nvs_handle_t c_handle, const char* key, const char* value)
{
    Lock lock;
    NVS_LOGD(TAG, "[%s] key: %s, value: %s", __func__, key, value);
    NVSHandleSimple *handle;
    auto err = nvs_find_ns_handle(c_handle, &handle);
    if (err != NVS_OK) {
        return err;
    }

    if (g_aes_cipher != nullptr) {
        // Erase any plain-text entry stored with the key.
        handle->erase_item(key);
        size_t key_len = strlen(key);
        size_t value_len = strlen(value);
        unsigned char *encrypted_key = NULL;
        unsigned char *encrypted_value = NULL;
        size_t encrypted_key_len = 0;
        size_t encrypted_value_len = 0;
        if (g_aes_cipher->encrypt_buffer((const unsigned char*)key, key_len,
                                         &encrypted_key, &encrypted_key_len) != 0) {
            return NVS_FAIL;
        }
        if (g_aes_cipher->encrypt_buffer((const unsigned char*)value, value_len,
                                         &encrypted_value, &encrypted_value_len) != 0) {
            vPortFree(encrypted_key);
            return NVS_FAIL;
        }
        char* hex_key = bytes_to_hex(encrypted_key, encrypted_key_len);
        char* hex_value = bytes_to_hex(encrypted_value, encrypted_value_len);
        vPortFree(encrypted_key);
        vPortFree(encrypted_value);
        if (hex_key == NULL || hex_value == NULL) {
            vPortFree(hex_key);
            vPortFree(hex_value);
            return NVS_ERR_NO_MEM;
        }
        // Store encrypted string as a blob.
        err = handle->set_blob(hex_key, hex_value, strlen(hex_value) + 1);
        vPortFree(hex_key);
        vPortFree(hex_value);
        return err;
    } else {
        return handle->set_string(key, value);
    }
}

extern "C" nvs_err_t nvs_set_blob(nvs_handle_t c_handle, const char* key, const void* value, size_t length)
{
    Lock lock;
    NVS_LOGD(TAG, "[%s] key: %s, size: %d", __func__, key, static_cast<int>(length));
    NVSHandleSimple *handle;
    auto err = nvs_find_ns_handle(c_handle, &handle);
    if (err != NVS_OK) {
        return err;
    }
    if (g_aes_cipher != nullptr) {
        // Erase any plain-text entry stored with the key.
        handle->erase_item(key);
        size_t key_len = strlen(key);
        unsigned char *encrypted_key = NULL;
        size_t encrypted_key_len = 0;
        if (g_aes_cipher->encrypt_buffer((const unsigned char *)key, key_len,
                                         &encrypted_key, &encrypted_key_len) != 0) {
            return NVS_FAIL;
        }
        char *hex_key = bytes_to_hex(encrypted_key, encrypted_key_len);
        vPortFree(encrypted_key);
        if (hex_key == NULL) {
            return NVS_ERR_NO_MEM;
        }
        unsigned char *encrypted_value = NULL;
        size_t encrypted_value_len = 0;
        if (g_aes_cipher->encrypt_buffer((const unsigned char *)value, length,
                                         &encrypted_value, &encrypted_value_len) != 0) {
            vPortFree(hex_key);
            return NVS_FAIL;
        }
        char *hex_value = bytes_to_hex(encrypted_value, encrypted_value_len);
        vPortFree(encrypted_value);
        if (hex_value == NULL) {
            vPortFree(hex_key);
            return NVS_ERR_NO_MEM;
        }
        err = handle->set_blob(hex_key, hex_value, strlen(hex_value) + 1);
        vPortFree(hex_key);
        vPortFree(hex_value);
        return err;
    } else {
        return handle->set_blob(key, value, length);
    }
}

template<typename T>
static nvs_err_t nvs_get(nvs_handle_t c_handle, const char* key, T* out_value)
{
    Lock lock;
    NVS_LOGD(TAG, "[%s] key: %s, expected size: %d", __func__, key, static_cast<int>(sizeof(T)));
    NVSHandleSimple *handle;
    nvs_err_t err = nvs_find_ns_handle(c_handle, &handle);
    if (err != NVS_OK)
        return err;
    if (g_aes_cipher != nullptr) {
        size_t key_len = strlen(key);
        unsigned char *encrypted_key = NULL;
        size_t encrypted_key_len = 0;
        if (g_aes_cipher->encrypt_buffer((const unsigned char*)key, key_len,
                                         &encrypted_key, &encrypted_key_len) != 0)
        {
            return NVS_FAIL;
        }
        char* hex_key = bytes_to_hex(encrypted_key, encrypted_key_len);
        vPortFree(encrypted_key);
        if (hex_key == NULL)
            return NVS_ERR_NO_MEM;
        size_t storedSize = 0;
        err = handle->get_item_size(nvs::ItemType::BLOB, hex_key, storedSize);
        if (err != NVS_OK)
        {
            vPortFree(hex_key);
            return err;
        }
        char* stored_hex = (char*)pvPortMalloc(storedSize);
        if (!stored_hex)
        {
            vPortFree(hex_key);
            return NVS_ERR_NO_MEM;
        }
        err = handle->get_typed_item(nvs::ItemType::BLOB, hex_key, stored_hex, storedSize);
        vPortFree(hex_key);
        if (err != NVS_OK)
        {
            vPortFree(stored_hex);
            return err;
        }
        size_t encrypted_value_len = 0;
        unsigned char* encrypted_value = hex_to_bytes(stored_hex, &encrypted_value_len);
        vPortFree(stored_hex);
        if (!encrypted_value)
            return NVS_FAIL;
        unsigned char* decrypted_value = NULL;
        size_t decrypted_value_len = 0;
        if (g_aes_cipher->decrypt_buffer(encrypted_value, encrypted_value_len,
                                         &decrypted_value, &decrypted_value_len) != 0)
        {
            vPortFree(encrypted_value);
            return NVS_FAIL;
        }
        vPortFree(encrypted_value);
        if (decrypted_value_len != sizeof(T))
        {
            vPortFree(decrypted_value);
            return NVS_ERR_NVS_INVALID_LENGTH;
        }
        memcpy(out_value, decrypted_value, sizeof(T));
        vPortFree(decrypted_value);
        return NVS_OK;
    }
    else
    {
        return handle->get_item(key, *out_value);
    }
}

extern "C" nvs_err_t nvs_get_i8  (nvs_handle_t c_handle, const char* key, int8_t* out_value)
{
    return nvs_get(c_handle, key, out_value);
}

extern "C" nvs_err_t nvs_get_u8  (nvs_handle_t c_handle, const char* key, uint8_t* out_value)
{
    return nvs_get(c_handle, key, out_value);
}

extern "C" nvs_err_t nvs_get_i16 (nvs_handle_t c_handle, const char* key, int16_t* out_value)
{
    return nvs_get(c_handle, key, out_value);
}

extern "C" nvs_err_t nvs_get_u16 (nvs_handle_t c_handle, const char* key, uint16_t* out_value)
{
    return nvs_get(c_handle, key, out_value);
}

extern "C" nvs_err_t nvs_get_i32 (nvs_handle_t c_handle, const char* key, int32_t* out_value)
{
    return nvs_get(c_handle, key, out_value);
}

extern "C" nvs_err_t nvs_get_u32 (nvs_handle_t c_handle, const char* key, uint32_t* out_value)
{
    return nvs_get(c_handle, key, out_value);
}

extern "C" nvs_err_t nvs_get_i64 (nvs_handle_t c_handle, const char* key, int64_t* out_value)
{
    return nvs_get(c_handle, key, out_value);
}

extern "C" nvs_err_t nvs_get_u64 (nvs_handle_t c_handle, const char* key, uint64_t* out_value)
{
    return nvs_get(c_handle, key, out_value);
}

static nvs_err_t nvs_get_str_or_blob(nvs_handle_t c_handle, nvs::ItemType type, const char* key, void* out_value, size_t* length)
{
    Lock lock;
    NVS_LOGD(TAG, "[%s] key: %s", __func__, key);
    NVSHandleSimple *handle;
    nvs_err_t err = nvs_find_ns_handle(c_handle, &handle);
    if (err != NVS_OK) {
        return err;
    }

    if (g_aes_cipher != nullptr) {
        // Encrypt the key to obtain the lookup key.
        size_t key_len = strlen(key);
        unsigned char *encrypted_key = NULL;
        size_t encrypted_key_len = 0;
        if (g_aes_cipher->encrypt_buffer((const unsigned char *)key, key_len,
                                         &encrypted_key, &encrypted_key_len) != 0) {
            return NVS_FAIL;
        }
        char *hex_key = bytes_to_hex(encrypted_key, encrypted_key_len);
        vPortFree(encrypted_key);
        if (hex_key == NULL) {
            return NVS_ERR_NO_MEM;
        }

        // For retrieval, if a string was requested, use BLOB type.
        nvs::ItemType effectiveType = (type == nvs::ItemType::SZ) ? nvs::ItemType::BLOB : type;

        size_t storedSize = 0;
        err = handle->get_item_size(effectiveType, hex_key, storedSize);
        if (err != NVS_OK) {
            vPortFree(hex_key);
            return err;
        }
        NVS_LOGD(TAG, "[%s] storedSize: %d", __func__, (int)storedSize);

        // Allocate buffer for the stored hex string.
        char *stored_hex = (char *)pvPortMalloc(storedSize);
        if (!stored_hex) {
            vPortFree(hex_key);
            return NVS_ERR_NO_MEM;
        }
        err = handle->get_typed_item(effectiveType, hex_key, stored_hex, storedSize);
        vPortFree(hex_key);
        if (err != NVS_OK) {
            vPortFree(stored_hex);
            return err;
        }

        // Convert the stored hex string back to binary.
        size_t encryptedValueLen = 0;
        unsigned char *encrypted_value = hex_to_bytes(stored_hex, &encryptedValueLen);
        vPortFree(stored_hex);
        if (!encrypted_value) {
            return NVS_FAIL;
        }

        // Decrypt the binary data.
        unsigned char *decrypted_value = NULL;
        size_t decrypted_value_len = 0;
        if (g_aes_cipher->decrypt_buffer(encrypted_value, encryptedValueLen,
                                         &decrypted_value, &decrypted_value_len) != 0) {
            vPortFree(encrypted_value);
            return NVS_FAIL;
        }
        vPortFree(encrypted_value);
        NVS_LOGD(TAG, "[%s] decrypted length: %d", __func__, (int)decrypted_value_len);

        // For a string, we expect a null-terminated result.
        size_t reqLen = decrypted_value_len + 1; // include null terminator
        if (out_value == NULL) {
            *length = reqLen;
            vPortFree(decrypted_value);
            return NVS_OK;
        }
        if (*length < reqLen) {
            *length = reqLen;
            vPortFree(decrypted_value);
            return NVS_ERR_NVS_INVALID_LENGTH;
        }
        memcpy(out_value, decrypted_value, decrypted_value_len);
        ((char *)out_value)[decrypted_value_len] = '\0';
        *length = reqLen;
        vPortFree(decrypted_value);
        return NVS_OK;
    } else {
        // Plain mode: retrieve using the provided key and type.
        size_t dataSize;
        err = handle->get_item_size(type, key, dataSize);
        if (err != NVS_OK) {
            return err;
        }

        if (length == nullptr) {
            return NVS_ERR_NVS_INVALID_LENGTH;
        } else if (out_value == nullptr) {
            *length = dataSize;
            return NVS_OK;
        } else if (*length < dataSize) {
            *length = dataSize;
            return NVS_ERR_NVS_INVALID_LENGTH;
        }

        *length = dataSize;
        return handle->get_typed_item(type, key, out_value, dataSize);
    }
}

extern "C" nvs_err_t nvs_get_str(nvs_handle_t c_handle, const char* key, char* out_value, size_t* length)
{
    return nvs_get_str_or_blob(c_handle, nvs::ItemType::SZ, key, out_value, length);
}

extern "C" nvs_err_t nvs_get_blob(nvs_handle_t c_handle, const char* key, void* out_value, size_t* length)
{
    return nvs_get_str_or_blob(c_handle, nvs::ItemType::BLOB, key, out_value, length);
}

extern "C" nvs_err_t nvs_get_stats(const char* part_name, nvs_stats_t* nvs_stats)
{
    Lock lock;
    nvs::Storage* pStorage;

    if (nvs_stats == nullptr) {
        return NVS_ERR_INVALID_ARG;
    }
    nvs_stats->used_entries     = 0;
    nvs_stats->free_entries     = 0;
    nvs_stats->total_entries    = 0;
    nvs_stats->namespace_count  = 0;

    pStorage = lookup_storage_from_name((part_name == nullptr) ? NVS_DEFAULT_PART_NAME : part_name);
    if (pStorage == nullptr) {
        return NVS_ERR_NVS_NOT_INITIALIZED;
    }

    if(!pStorage->isValid()){
        return NVS_ERR_NVS_INVALID_STATE;
    }

    return pStorage->fillStats(*nvs_stats);
}

extern "C" nvs_err_t nvs_get_used_entry_count(nvs_handle_t c_handle, size_t* used_entries)
{
    Lock lock;
    if(used_entries == nullptr){
        return NVS_ERR_INVALID_ARG;
    }
    *used_entries = 0;

    NVSHandleSimple *handle;
    auto err = nvs_find_ns_handle(c_handle, &handle);
    if (err != NVS_OK) {
        return err;
    }

    size_t used_entry_count;
    err = handle->get_used_entry_count(used_entry_count);
    if(err == NVS_OK){
        *used_entries = used_entry_count;
    }
    return err;
}

static nvs_iterator_t create_iterator(nvs::Storage *storage, nvs_type_t type)
{
    nvs_iterator_t it = (nvs_iterator_t)calloc(1, sizeof(nvs_opaque_iterator_t));
    if (it == nullptr) {
        return nullptr;
    }

    it->storage = storage;
    it->type = type;

    return it;
}

extern "C" nvs_iterator_t nvs_entry_find(const char *part_name, const char *namespace_name, nvs_type_t type)
{
    Lock lock;
    nvs::Storage *pStorage;

    pStorage = lookup_storage_from_name(part_name);
    if (pStorage == nullptr) {
        return nullptr;
    }

    nvs_iterator_t it = create_iterator(pStorage, type);
    if (it == nullptr) {
        return nullptr;
    }

    bool entryFound = pStorage->findEntry(it, namespace_name);
    if (!entryFound) {
        free(it);
        return nullptr;
    }

    return it;
}

extern "C" nvs_iterator_t nvs_entry_next(nvs_iterator_t it)
{
    Lock lock;
    assert(it);

    bool entryFound = it->storage->nextEntry(it);
    if (!entryFound) {
        free(it);
        return nullptr;
    }

    return it;
}

extern "C" void nvs_entry_info(nvs_iterator_t it, nvs_entry_info_t *out_info)
{
    *out_info = it->entry_info;
}

extern "C" void nvs_release_iterator(nvs_iterator_t it)
{
    free(it);
}
