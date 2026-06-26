/*
 * lfs utility functions
 *
 * Copyright (c) 2022, The littlefs authors.
 * Copyright (c) 2017, Arm Limited. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This module provides helper abstractions for managing
 * a group of CRC-protected LittleFS files as a logical set.
 * It supports creation, verification, backup, restore, and deletion.
 */

#ifndef LFS_FILE_SET_H

#include <stdint.h>
#include <stdbool.h>
#include "lfs.h"

#define LFS_FILE_SET_VERIFY_OK          0    /* All files exist and are valid */
#define LFS_FILE_SET_VERIFY_NOT_FOUND  -1    /* None of the files exist (first run / fully deleted) */
#define LFS_FILE_SET_VERIFY_ERROR      -2    /* At least one file corrupted or fatal FS error */

/* Represents a single CRC-protected file entry. */
typedef struct {
    const char *name;  /* Must be unique within the set */
    uint32_t size;     /* DATA length (excluding CRC/LENGTH header) */
} lfs_file_entry_t;


/* Represents a logical set of related files. */
typedef struct {
    const lfs_file_entry_t *entries; /* Array of entries */
    uint32_t count;                  /* Number of entries */
} lfs_file_set_t;


/* Optional callback to initialize file contents during creation. */
typedef void (*lfs_file_init_cb_t)(
    uint8_t *buf,      /* Writeable buffer of size "size" */
    uint32_t size,     /* Data size requested for the file */
    void *user_ctx,    /* User-provided context */
    uint32_t index     /* Index of file being initialized */
);

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Create all files defined in the file set
 *
 * For each entry in the set, a CRC-protected file is created:
 *   [CRC32][LENGTH][DATA]
 *
 * If an initialization callback is provided, DATA is generated per file.
 * Otherwise, DATA is zero-initialized.
 *
 * Typical usage:
 *   - First boot or after full wipe
 *   - Immediately followed by backup creation
 *
 * @param set       Pointer to file set descriptor
 * @param init_cb   Optional initializer invoked for each file (may be NULL)
 * @param user_ctx  User context forwarded to init_cb
 *
 * @return 0 on success,
 *         negative error code on FS or allocation failure
 */
int lfs_file_set_create_all(const lfs_file_set_t *set,
                            lfs_file_init_cb_t init_cb,
                            void *user_ctx);


/**
 * @brief Verify integrity of all files within a file set
 *
 * The file set is considered valid only if:
 *   - every file exists,
 *   - file length matches expected size, and
 *   - stored CRC matches calculated CRC.
 *
 * Policy:
 *   Partial sets (some missing files) and corrupted files are treated as invalid.
 *
 * @param set Pointer to file set definition
 *
 * @return LFS_FILE_SET_VERIFY_OK
 *           All files exist and are valid
 *         LFS_FILE_SET_VERIFY_NOT_FOUND
 *           None of the files exist (first boot / fully deleted)
 *         LFS_FILE_SET_VERIFY_ERROR
 *           Inconsistency detected: missing or corrupted files
 */
int lfs_file_set_verify_all(const lfs_file_set_t *set);


/**
 * @brief Create backup files for all entries in the file set
 *
 * For each primary file "<name>", a backup "<name>.bak" is written
 * using full CRC protection.
 *
 * Existing backups are overwritten.
 *
 * @param set Pointer to file set descriptor
 *
 * @return 0 on success,
 *         negative error code on failure
 */
int lfs_file_set_backup_all(const lfs_file_set_t *set);


/**
 * @brief Restore invalid or missing files from backup images
 *
 * Behavior per entry:
 *   - If primary exists and is valid → left unchanged
 *   - If primary is missing/corrupt and backup exists/valid → restored
 *   - If primary is invalid AND no valid backup exists → failure
 *
 * Used when verifying integrity during boot or power-cut recovery.
 *
 * @param set Pointer to file set descriptor
 *
 * @return 0 on success (all recoverable files restored),
 *         negative error code if any file cannot be recovered
 */
int lfs_file_set_restore_all(const lfs_file_set_t *set);


/**
 * @brief Remove all primary files in a file set
 *
 * Optionally deletes backup files as well.
 * Missing files do not cause failure.
 *
 * Typical usage:
 *   - Forced re-initialization
 *   - Test cleanup before file set re-creation
 *
 * @param set            Pointer to file set descriptor
 * @param remove_backup  If true, also remove ".bak" backups
 *
 * @return 0 on success,
 *         negative error code if FS error occurs
 */
int lfs_file_set_remove_all(const lfs_file_set_t *set,
                            bool remove_backup);

#ifdef __cplusplus
}
#endif

#endif /* LFS_FILE_SET_H */