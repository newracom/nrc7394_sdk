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
#ifndef nvs_flash_h
#define nvs_flash_h

#ifdef __cplusplus
extern "C" {
#endif

#include "nvs.h"

#define NVS_KEY_SIZE 32 // AES-256

/**
 * @brief Key for encryption and decryption
 */
typedef struct {
    uint8_t eky[NVS_KEY_SIZE]; /*!<  XTS encryption and decryption key*/
    uint8_t tky[NVS_KEY_SIZE]; /*!<  XTS tweak key */
} nvs_sec_cfg_t;

/**
 * @brief Initialize the default NVS partition.
 *
 * This API initialises the default NVS partition. The default NVS partition
 * is the one that is labeled "nvs" in the partition table.
 *
 * Post initialization NVS read/write APIs
 * remain the same irrespective of NVS encryption.
 *
 * @return
 *      - NVS_OK if storage was successfully initialized.
 *      - NVS_ERR_NVS_NO_FREE_PAGES if the NVS storage contains no empty pages
 *        (which may happen if NVS partition was truncated)
 *      - NVS_ERR_NOT_FOUND if no partition with label "nvs" is found in the partition table
 *      - NVS_ERR_NO_MEM in case memory could not be allocated for the internal structures
 *      - one of the error codes from the underlying flash storage driver
 */
nvs_err_t nvs_flash_init(void);

/**
 * @brief Enable NVS encryption.
 *
 * This API configures and enables encryption for NVS operations. When encryption is enabled,
 * subsequent NVS set/get APIs automatically encrypt/decrypt all values (including strings)
 * using AES-CTR mode. All encrypted data is stored as a blob in NVS, regardless of its original type.
 * However, the get functions automatically decrypt the stored blob and return the data in its original type 
 * (for example, a string will be retrieved as a null-terminated string as originally stored).
 *
 * The supplied key and nonce (each must be exactly 16 bytes) are used to initialize the encryption engine.
 *
 * Note: When using plain text keys in NVS, the key is stored as a hexadecimal string in a 15‐byte buffer
 *       (16 bytes minus 1 for the null terminator). Since each raw byte becomes two hex characters during encryption,
 *       only a maximum of 7 raw bytes (14 hex characters) can fit in the available space.
 *
 * The encryption configuration remains active until cleared by calling nvs_clear_encrypt().
 *
 * @param key Pointer to a 16-byte encryption key.
 * @param nonce Pointer to a 16-byte nonce (initialization vector).
 *
 * @return
 *      - NVS_OK if encryption was successfully enabled.
 *      - NVS_ERR_INVALID_ARG if the key or nonce is invalid (e.g. not exactly 16 bytes).
 *      - NVS_ERR_NO_MEM if memory allocation for the encryption structures fails.
 */
nvs_err_t nvs_set_encrypt(const unsigned char* key, const unsigned char* nonce);

/**
 * @brief Disable NVS encryption.
 *
 * This API disables the active encryption for NVS. After calling this function,
 * subsequent NVS read/write operations for all data types will be handled as plain text.
 * This API is useful when encryption is no longer required or before reconfiguring encryption parameters.
 *
 * @return
 *      - None.
 */	
void nvs_clear_encrypt();

/**
 * @brief Initialize NVS flash storage for the specified partition.
 *
 * @param[in]  partition_label   Label of the partition. Must be no longer than 16 characters.
 *
 * @return
 *      - NVS_OK if storage was successfully initialized.
 *      - NVS_ERR_NVS_NO_FREE_PAGES if the NVS storage contains no empty pages
 *        (which may happen if NVS partition was truncated)
 *      - NVS_ERR_NOT_FOUND if specified partition is not found in the partition table
 *      - NVS_ERR_NO_MEM in case memory could not be allocated for the internal structures
 *      - one of the error codes from the underlying flash storage driver
 */
nvs_err_t nvs_flash_init_partition(const char *partition_label);

/**
 * @brief Initialize NVS flash storage for the partition specified by partition pointer.
 *
 * @param[in] address  partition start address.
 * @param[in] size     partition size.
 *
 * @return
 *      - NVS_OK if storage was successfully initialized
 *      - NVS_ERR_NVS_NO_FREE_PAGES if the NVS storage contains no empty pages
 *        (which may happen if NVS partition was truncated)
 *      - NVS_ERR_INVALID_ARG in case partition is NULL
 *      - NVS_ERR_NO_MEM in case memory could not be allocated for the internal structures
 *      - one of the error codes from the underlying flash storage driver
 */
nvs_err_t nvs_flash_init_partition_ptr(uint32_t address, size_t size);

/**
 * @brief Deinitialize NVS storage for the default NVS partition
 *
 * Default NVS partition is the partition with "nvs" label in the partition table.
 *
 * @return
 *      - NVS_OK on success (storage was deinitialized)
 *      - NVS_ERR_NVS_NOT_INITIALIZED if the storage was not initialized prior to this call
 */
nvs_err_t nvs_flash_deinit(void);

/**
 * @brief Deinitialize NVS storage for the given NVS partition
 *
 * @param[in]  partition_label   Label of the partition
 *
 * @return
 *      - NVS_OK on success
 *      - NVS_ERR_NVS_NOT_INITIALIZED if the storage for given partition was not
 *        initialized prior to this call
 */
nvs_err_t nvs_flash_deinit_partition(const char* partition_label);

/**
 * @brief Erase the default NVS partition
 *
 * Erases all contents of the default NVS partition (one with label "nvs").
 *
 * @note If the partition is initialized, this function first de-initializes it. Afterwards, the partition has to
 *       be initialized again to be used.
 *
 * @return
 *      - NVS_OK on success
 *      - NVS_ERR_NOT_FOUND if there is no NVS partition labeled "nvs" in the
 *        partition table
 *      - different error in case de-initialization fails (shouldn't happen)
 */
nvs_err_t nvs_flash_erase(void);

/**
 * @brief Erase specified NVS partition
 *
 * Erase all content of a specified NVS partition
 *
 * @note If the partition is initialized, this function first de-initializes it. Afterwards, the partition has to
 *       be initialized again to be used.
 *
 * @param[in]  part_name    Name (label) of the partition which should be erased
 *
 * @return
 *      - NVS_OK on success
 *      - NVS_ERR_NOT_FOUND if there is no NVS partition with the specified name
 *        in the partition table
 *      - different error in case de-initialization fails (shouldn't happen)
 */
nvs_err_t nvs_flash_erase_partition(const char *part_name);

/**
 * @brief Erase custom partition.
 *
 * Erase all content of specified custom partition.
 *
 * @note
 *  If the partition is initialized, this function first de-initializes it.
 *  Afterwards, the partition has to be initialized again to be used.
 *
 * @param[in] address   partition start address.
 * @param[in] size      partition size.
 *
 * @return
 *      - NVS_OK on success
 *      - NVS_ERR_NOT_FOUND if there is no partition with the specified
 *        parameters in the partition table
 *      - NVS_ERR_INVALID_ARG in case partition is NULL
 *      - one of the error codes from the underlying flash storage driver
 */
nvs_err_t nvs_flash_erase_partition_ptr(uint32_t address, size_t size);

/**
 * @brief Initialize the default NVS partition.
 *
 * This API initialises the default NVS partition. The default NVS partition
 * is the one that is labeled "nvs" in the partition table.
 *
 * @param[in]  cfg Security configuration (keys) to be used for NVS encryption/decryption.
 *                              If cfg is NULL, no encryption is used.
 *
 * @return
 *      - NVS_OK if storage has been initialized successfully.
 *      - NVS_ERR_NVS_NO_FREE_PAGES if the NVS storage contains no empty pages
 *        (which may happen if NVS partition was truncated)
 *      - NVS_ERR_NOT_FOUND if no partition with label "nvs" is found in the partition table
 *      - NVS_ERR_NO_MEM in case memory could not be allocated for the internal structures
 *      - one of the error codes from the underlying flash storage driver
 */
nvs_err_t nvs_flash_secure_init(nvs_sec_cfg_t* cfg);

/**
 * @brief Initialize NVS flash storage for the specified partition.
 *
 * @param[in]  partition_label   Label of the partition. Note that internally, a reference to
 *                               passed value is kept and it should be accessible for future operations
 *
 * @param[in]  cfg Security configuration (keys) to be used for NVS encryption/decryption.
 *                              If cfg is null, no encryption/decryption is used.
 * @return
 *      - NVS_OK if storage has been initialized successfully.
 *      - NVS_ERR_NVS_NO_FREE_PAGES if the NVS storage contains no empty pages
 *        (which may happen if NVS partition was truncated)
 *      - NVS_ERR_NOT_FOUND if specified partition is not found in the partition table
 *      - NVS_ERR_NO_MEM in case memory could not be allocated for the internal structures
 *      - one of the error codes from the underlying flash storage driver
 */
nvs_err_t nvs_flash_secure_init_partition(const char *partition_label, nvs_sec_cfg_t* cfg);

/**
 * @brief Generate and store NVS keys in the provided esp partition
 *
 * @param[in]  address   partition start address.
 * @param[out] cfg       Pointer to nvs security configuration structure.
 *                       Pointer must be non-NULL.
 *                       Generated keys will be populated in this structure.
 *
 *
 * @return
 *      -NVS_OK, if cfg was read successfully;
 *      -NVS_INVALID_ARG, if partition or cfg;
 *      -or error codes from esp_partition_write/erase APIs.
 */

nvs_err_t nvs_flash_generate_keys(uint32_t address, nvs_sec_cfg_t* cfg);


/**
 * @brief Read NVS security configuration from a partition.
 *
 * @param[in]  address   partition start address.
 * @param[out] cfg       Pointer to nvs security configuration structure.
 *                       Pointer must be non-NULL.
 *
 * @note  Provided partition is assumed to be marked 'encrypted'.
 *
 * @return
 *      -NVS_OK, if cfg was read successfully;
 *      -NVS_INVALID_ARG, if partition or cfg;
 *      -NVS_ERR_NVS_KEYS_NOT_INITIALIZED, if the partition is not yet written with keys.
 *      -NVS_ERR_NVS_CORRUPT_KEY_PART, if the partition containing keys is found to be corrupt
 *      -or error codes from esp_partition_read API.
 */

nvs_err_t nvs_flash_read_security_cfg(uint32_t address, nvs_sec_cfg_t* cfg);

#ifdef __cplusplus
}
#endif


#endif /* nvs_flash_h */
