/*
 * LittleFS File Utilities with CRC Integrity Check
 *
 * Copyright (c) 2025
 * SPDX-License-Identifier: MIT
 *
 * Provides generic file operations with CRC32-based integrity checking.
 * File structure: [CRC32(4)][LENGTH(4)][DATA(variable)]
 */

#ifndef LFS_FILE_UTILS_H
#define LFS_FILE_UTILS_H

#include "lfs.h"
#include <stdint.h>

/**
 * All primary file exists, CRC is valid.
 */
#define LFS_VERIFY_OK           0

/**
 * Primary file corrupted/missing, but successfully restored
 * from backup and now valid.
 */
#define LFS_VERIFY_RESTORED     1


/**
 * neither primary nor backup exists
 */
#define LFS_VER_NOT_FOUND 2

/**
 * Verification failed — permanent error:
 *   - no valid primary nor backup
 *   - I/O error
 *   - CRC corruption
 *   - other LittleFS error
 *
 * NOTE: negative errors aligned with LittleFS:
 *   LFS_ERR_NOENT, LFS_ERR_IO, LFS_ERR_CORRUPT, etc.
 */
#define LFS_VERIFY_ERROR       (-1)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Write data to file with CRC32 integrity protection
 *
 * File structure created:
 *   [CRC32(4 bytes)][LENGTH(4 bytes)][DATA(length bytes)]
 *   CRC32 covers LENGTH + DATA fields
 *
 * @param lfs Pointer to LittleFS instance
 * @param filename Name of file to create/write
 * @param data Pointer to data buffer
 * @param length Size of data in bytes
 * @return 0 on success, negative error code on failure
 */
int lfs_file_write_with_crc(lfs_t *lfs, const char *filename,
                             const void *data, uint32_t length);

/**
 * @brief Read data from file and verify CRC32 integrity
 *
 * @param lfs Pointer to LittleFS instance
 * @param filename Name of file to read
 * @param data Pointer to buffer to receive data (must be large enough)
 * @param length Pointer to variable to receive actual data length
 * @param max_length Maximum size of data buffer
 * @return 0 on success, negative error code on failure
 */
int lfs_file_read_with_crc(lfs_t *lfs, const char *filename,
                           void *data, uint32_t *length, uint32_t max_length);

/**
 * @brief Verify file CRC32 integrity without reading data
 *
 * @param lfs Pointer to LittleFS instance
 * @param filename Name of file to verify
 * @param out_crc Optional pointer to receive stored CRC value
 * @param out_length Optional pointer to receive data length
 * @return 0 if valid, negative error code if corrupted or error
 */
int lfs_file_verify_crc(lfs_t *lfs, const char *filename,
                        uint32_t *out_crc, uint32_t *out_length);

/**
 * @brief Copy file with CRC verification
 *
 * Copies source file to destination, verifying CRC during copy.
 *
 * @param lfs Pointer to LittleFS instance
 * @param src_filename Source file name
 * @param dst_filename Destination file name
 * @return 0 on success, negative error code on failure
 */
int lfs_file_copy_with_crc(lfs_t *lfs, const char *src_filename,
                           const char *dst_filename);

/**
 * @brief Generate a backup filename by appending ".bak"
 *
 * Example:
 *    "test.dat" -> "test.dat.bak"
 *
 * @param filename     Original filename (null-terminated string)
 * @param backup_name  Output buffer receiving "<filename>.bak"
 * @param buf_size     Size of backup_name buffer including terminator
 *
 * @return 0 on success,
 *         negative error code if buffer too small or invalid parameters
 */
int lfs_file_make_backup_name(const char *filename,
                              char *backup_name,
                              uint32_t buf_size);

/**
 * @brief Verify a CRC-protected file and optionally restore from backup.
 *
 * File layout on storage:
 *   [CRC32(4)][LENGTH(4)][DATA(LENGTH)]
 *
 * This API only exposes the DATA region to the caller. CRC and LENGTH
 * are handled internally.
 *
 * Behavior:
 *   1. Verify primary file:
 *      - If valid (CRC OK), LENGTH is returned via @p output_size (if non-NULL).
 *      - If @p data is non-NULL, the payload is read into @p data.
 *
 *   2. If primary is missing or corrupted, try backup "<filename>.bak":
 *      - If backup is valid, it is copied to the primary.
 *      - If @p data is non-NULL, the restored primary payload is read into @p data.
 *
 *   3. If both primary and backup are invalid, the function fails.
 *
 * Notes:
 *   - When @p data is NULL, no payload is read; only verify/restore is performed.
 *   - When @p data is non-NULL, @p buffer_size must be >= payload size
 *     or LFS_ERR_NOMEM is returned.
 *
 * @param lfs          Pointer to LittleFS instance.
 * @param filename     Name of the primary file.
 * @param data         Optional caller buffer for payload (may be NULL).
 * @param buffer_size  Size of @p data buffer in bytes (ignored if @p data is NULL).
 * @param output_size  Optional pointer to receive the payload size in bytes.
 *
 * @return 0 on success, negative LFS_ERR_xx code on failure.
 */
int lfs_file_verify_or_restore_with_backup(lfs_t *lfs,
                       const char *filename,
                       void *data,
                       uint32_t buffer_size,
                       uint32_t *output_size);

int lfs_file_verify(lfs_t *lfs,
                       const char *filename,
                       void *data,
                       uint32_t buffer_size,
                       uint32_t *output_size,
                       bool restore_with_backup);

/**
 * @brief Update a CRC-protected file and its backup "<filename>.bak".
 *
 * Steps:
 *   1) Write the primary file with CRC header using DATA buffer.
 *   2) Generate the backup name via lfs_file_make_backup_name().
 *   3) Copy the primary to the backup using CRC-aware copy.
 *
 * @param lfs       Pointer to LittleFS instance.
 * @param filename  Primary filename.
 * @param data      Pointer to payload data.
 * @param data_size Size of payload data in bytes.
 *
 * @return 0 on success, negative LFS_ERR_xx code on failure.
 */
int lfs_file_update_with_backup(lfs_t *lfs,
                const char *filename,
                const void *data,
                uint32_t data_size);


int lfs_file_update(lfs_t *lfs,
                const char *filename,
                const void *data,
                uint32_t data_size, bool backup);

/* Print format flags for lfs_file_print_data */
#define LFS_PRINT_HEX       (1 << 0)    /* Print data in hex format */
#define LFS_PRINT_STRING    (1 << 1)    /* Print data as string */

/**
 * @brief Print file contents with CRC/LENGTH header
 *
 * Displays file structure in formatted output:
 * - Always shows: CRC32, LENGTH
 * - Data output controlled by flags:
 *   LFS_PRINT_HEX: Hex dump with address alignment (16 bytes/line)
 *   LFS_PRINT_STRING: String representation (printable ASCII)
 *   Both flags: Hex + String side-by-side
 *
 * @param lfs Pointer to LittleFS instance
 * @param filename Name of file to print
 * @param print_flags Format flags (LFS_PRINT_HEX | LFS_PRINT_STRING)
 * @param offset Byte offset into DATA to start printing (0 = beginning)
 * @param size Number of bytes to print (0 = all data)
 * @return 0 on success, negative error code on failure
 */
int lfs_file_print_data(lfs_t *lfs, const char *filename,
                        uint32_t print_flags, uint32_t offset, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif /* LFS_FILE_UTILS_H */
