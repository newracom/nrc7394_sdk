/*
 * lfs utility functions
 *
 * Copyright (c) 2022, The littlefs authors.
 * Copyright (c) 2017, Arm Limited. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This module provides helper abstractions for managing
 * a group of CRC-protected LittleFS files as a logical set.
 * Each file is stored using lfs_file_utils.*, which provides
 * CRC32-based integrity protection and optional size verification.
 */

#include "lfs_file_set.h"
#include "lfs_file_utils.h"
#include "lfs_port.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int lfs_file_set_create_all(const lfs_file_set_t *set,
                            lfs_file_init_cb_t init_cb,
                            void *user_ctx)
{
    if (!set || !set->entries) return -1;
    lfs_t *lfs = lfs_port_get_instance();
    if (!lfs) return -1;

    for (uint32_t i = 0; i < set->count; i++) {
        const lfs_file_entry_t *e = &set->entries[i];

        /* malloc instead of nrc_mem_malloc */
        uint8_t *buf = (uint8_t *)malloc(e->size);
        if (!buf) return -1;

        if (init_cb) {
            init_cb(buf, e->size, user_ctx, i);
        } else {
            memset(buf, 0x00, e->size);
        }

        int ret = lfs_file_write_with_crc(lfs, e->name, buf, e->size);

        /* free instead of nrc_mem_free */
        free(buf);

        if (ret != 0) return ret;
    }
    return 0;
}

int lfs_file_set_verify_all(const lfs_file_set_t *set)
{
    uint32_t valid = 0;
    uint32_t missing = 0;
    uint32_t corrupted = 0;

    if (!set || !set->entries || set->count == 0) {
        return LFS_FILE_SET_VERIFY_ERROR;
    }

    lfs_t *lfs = lfs_port_get_instance();
    if (!lfs) {
        return LFS_FILE_SET_VERIFY_ERROR;
    }

    for (uint32_t i = 0; i < set->count; i++) {
        const lfs_file_entry_t *e = &set->entries[i];
        uint32_t crc = 0;
        uint32_t len = 0;

        int ret = lfs_file_verify_crc(lfs, e->name, &crc, &len);

        if (ret == 0 && len == e->size) {
            /* File exists and is valid */
            valid++;
            continue;
        }

        if (ret == LFS_ERR_NOENT) {
            /* File is missing */
            missing++;
            continue;
        }

        if (ret == LFS_ERR_CORRUPT) {
            /* File is present but corrupted */
            corrupted++;
            continue;
        }

        /* Any other negative value is treated as a filesystem error */
        corrupted++;
        continue;
    }

    /* No valid files but some missing -> first run / fully wiped */
    if (valid == 0 && missing > 0 && corrupted == 0) {
        return LFS_FILE_SET_VERIFY_NOT_FOUND;
    }

    /* Any corruption or FS error → hard ERROR */
    if (corrupted > 0) {
        return LFS_FILE_SET_VERIFY_ERROR;
    }

    /* All files exist and are valid */
    if (valid == set->count && missing == 0 && corrupted == 0) {
        return LFS_FILE_SET_VERIFY_OK;
    }

    /* Fallback (should not normally reach here) */
    return LFS_FILE_SET_VERIFY_ERROR;
}



int lfs_file_set_backup_all(const lfs_file_set_t *set)
{
    if (!set || !set->entries) return -1;
    lfs_t *lfs = lfs_port_get_instance();
    if (!lfs) return -1;

    for (uint32_t i = 0; i < set->count; i++) {
        const lfs_file_entry_t *e = &set->entries[i];
        char bak[64];
        if (lfs_file_make_backup_name(e->name, bak, sizeof(bak)) != 0) return -1;

        int ret = lfs_file_copy_with_crc(lfs, e->name, bak);
        if (ret != 0) return ret;
    }
    return 0;
}

int lfs_file_set_restore_all(const lfs_file_set_t *set)
{
    if (!set || !set->entries) return -1;
    lfs_t *lfs = lfs_port_get_instance();
    if (!lfs) return -1;

    for (uint32_t i = 0; i < set->count; i++) {
        const lfs_file_entry_t *e = &set->entries[i];
        char bak[64];
        if (lfs_file_make_backup_name(e->name, bak, sizeof(bak)) != 0) return -1;

        int ret = lfs_file_copy_with_crc(lfs, bak, e->name);
        if (ret != 0) return ret;

        uint32_t crc, len;
        ret = lfs_file_verify_crc(lfs, e->name, &crc, &len);
        if (ret != 0 || len != e->size) return -1;
    }
    return 0;
}

int lfs_file_set_remove_all(const lfs_file_set_t *set, bool remove_backup)
{
    if (!set || !set->entries) return -1;
    lfs_t *lfs = lfs_port_get_instance();
    if (!lfs) return -1;

    for (uint32_t i = 0; i < set->count; i++) {
        const lfs_file_entry_t *e = &set->entries[i];
        lfs_remove(lfs, e->name);
        if (remove_backup) {
            char bak[64];
            if (lfs_file_make_backup_name(e->name, bak, sizeof(bak)) == 0) {
                lfs_remove(lfs, bak);
            }
        }
    }
    return 0;
}
