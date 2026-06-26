/*
 * LittleFS File Utilities with CRC Integrity Check
 *
 * Copyright (c) 2025
 * SPDX-License-Identifier: MIT
 */

#include "lfs_file_utils.h"
#include "util_crc.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* File structure offsets */
#define LFS_FILE_CRC_OFFSET     0
#define LFS_FILE_LEN_OFFSET     4
#define LFS_FILE_DATA_OFFSET    8
#define LFS_FILE_HEADER_SIZE    8

/* Chunk size for reading/writing large files */
#define LFS_FILE_CHUNK_SIZE     512

/******************************************************************************
 * Public API Implementation
 ******************************************************************************/

#if 0
int lfs_file_write_with_crc(lfs_t *lfs, const char *filename,
                             const void *data, uint32_t length)
{
    lfs_file_t file;
    uint32_t stored_crc, calculated_crc;
    uint8_t buffer[LFS_FILE_CHUNK_SIZE];

    if (!lfs || !filename || !data) {
        return LFS_ERR_INVAL;
    }

    /* Open file for read/write */
    int err = lfs_file_open(lfs, &file, filename,
                            LFS_O_RDWR | LFS_O_CREAT | LFS_O_TRUNC);
    if (err) {
        return err;
    }

    /* Write placeholder CRC */
    stored_crc = 0;
    lfs_ssize_t written = lfs_file_write(lfs, &file, &stored_crc, sizeof(stored_crc));
    if (written != sizeof(stored_crc)) {
        lfs_file_close(lfs, &file);
        return (written < 0) ? written : LFS_ERR_IO;
    }

    /* Write LENGTH */
    written = lfs_file_write(lfs, &file, &length, sizeof(length));
    if (written != sizeof(length)) {
        lfs_file_close(lfs, &file);
        return (written < 0) ? written : LFS_ERR_IO;
    }

    /* Write DATA */
    const uint8_t *data_ptr = (const uint8_t *)data;
    uint32_t total_written = 0;

    while (total_written < length) {
        uint32_t to_write = (length - total_written > LFS_FILE_CHUNK_SIZE) ?
                            LFS_FILE_CHUNK_SIZE : (length - total_written);

        written = lfs_file_write(lfs, &file, data_ptr + total_written, to_write);
        if (written < 0) {
            lfs_file_close(lfs, &file);
            return written;
        }

        total_written += written;
    }

    /* Calculate CRC of LENGTH + DATA */
    /* Allocate buffer for LENGTH + DATA */
    uint8_t *crc_buffer = (uint8_t *)malloc(sizeof(length) + length);
    if (!crc_buffer) {
        lfs_file_close(lfs, &file);
        return LFS_ERR_NOMEM;
    }

    /* Copy LENGTH to buffer */
    memcpy(crc_buffer, &length, sizeof(length));

    /* Seek to data start and read entire data */
    lfs_file_seek(lfs, &file, LFS_FILE_DATA_OFFSET, LFS_SEEK_SET);
    lfs_ssize_t read_size = lfs_file_read(lfs, &file, crc_buffer + sizeof(length), length);
    if (read_size != (lfs_ssize_t)length) {
        free(crc_buffer);
        lfs_file_close(lfs, &file);
        return (read_size < 0) ? read_size : LFS_ERR_IO;
    }

    /* Calculate CRC over entire LENGTH + DATA */
    calculated_crc = util_crc_compute_crc32(crc_buffer, sizeof(length) + length);
    free(crc_buffer);

    /* Write actual CRC */
    lfs_file_seek(lfs, &file, LFS_FILE_CRC_OFFSET, LFS_SEEK_SET);
    written = lfs_file_write(lfs, &file, &calculated_crc, sizeof(calculated_crc));
    if (written != sizeof(calculated_crc)) {
        lfs_file_close(lfs, &file);
        return (written < 0) ? written : LFS_ERR_IO;
    }

    lfs_file_close(lfs, &file);
    return 0;
}
#else
typedef struct
{
    uint32_t crc;
    uint32_t len;
    uint8_t data[0];
} lfs_file_buf_t;

static int _lfs_file_write_with_crc(lfs_t *lfs, const char *filename,
                             const void *data, uint32_t length, bool verify)
{
    lfs_file_t file;
    lfs_file_buf_t *file_buf = NULL;
    uint32_t file_size;
    int ret;
    int i;

    if (!lfs || !filename || !data) {
        return LFS_ERR_INVAL;
    }

    file_size = sizeof(lfs_file_buf_t) + length;
    file_buf = (lfs_file_buf_t *)malloc(file_size);
    if (!file_buf) {
        printf("[%s] malloc() failed\n", __func__);
        return LFS_ERR_NOMEM;
    }

    memcpy(file_buf->data, data, length);
    file_buf->len = length;
    file_buf->crc = util_crc_compute_crc32((uint8_t *)&file_buf->len, sizeof(file_buf->len) + length);

    /* Open file for read/write */
    ret = lfs_file_open(lfs, &file, filename, LFS_O_RDWR | LFS_O_CREAT | LFS_O_TRUNC);
    if (ret) {
        printf("[%s] lfs_file_open() failed, ret=%d\n", __func__, ret);
        free(file_buf);
        return ret;
    }

    /* Write file */
    for (i = 0 ; i < file_size ; i += ret) {
        ret = lfs_file_write(lfs, &file, (uint8_t *)file_buf + i, 
                ((file_size - i) < LFS_FILE_CHUNK_SIZE) ? (file_size - i) : LFS_FILE_CHUNK_SIZE);
        if (ret < 0) {
            printf("[%s] lfs_file_write() failed, ret=%d\n", __func__, ret);
            goto failed;
        }
    }

    /* Verify file */
    if (verify)
    {
        uint32_t crc;

        memset(file_buf, 0, file_size);
        
        lfs_file_seek(lfs, &file, 0, LFS_SEEK_SET);
        ret = lfs_file_read(lfs, &file, file_buf, file_size);
        if (ret < 0) {
            printf("[%s] lfs_file_read() failed, ret=%d\n", __func__, ret);
            goto failed;
        } else if (ret != file_size || file_buf->len != length) {
            printf("[%s] corrupt, file_size=%d/%lu data_len=%lu/%lu\n", __func__, 
                    ret, file_size, file_buf->len, length);
            ret = LFS_ERR_CORRUPT;
            goto failed;
        }

        /* Compare stored CRC and computed CRC */
        crc = util_crc_compute_crc32((uint8_t *)&file_buf->len, sizeof(file_buf->len) + file_buf->len);
        if (crc != file_buf->crc) {
            printf("[%s] crc mismatch, 0x%08lX -> 0x%08lX\n", __func__, file_buf->crc, crc);
            ret = LFS_ERR_CORRUPT;
            goto failed;
        }
    }

    ret = 0;

failed:

    lfs_file_close(lfs, &file);
    free(file_buf);

    return ret;
}

int lfs_file_write_with_crc(lfs_t *lfs, const char *filename,
                             const void *data, uint32_t length)
{
    return _lfs_file_write_with_crc(lfs, filename, data, length, false);
}
#endif

int lfs_file_read_with_crc(lfs_t *lfs, const char *filename,
                           void *data, uint32_t *length, uint32_t max_length)
{
    lfs_file_t file;
    uint32_t stored_crc, file_length, calculated_crc;
    uint8_t buffer[LFS_FILE_CHUNK_SIZE];

    if (!lfs || !filename || !data || !length) {
        return LFS_ERR_INVAL;
    }

    /* Open file */
    int err = lfs_file_open(lfs, &file, filename, LFS_O_RDONLY);
    if (err) {
        return err;
    }

    /* Read CRC */
    lfs_ssize_t read_size = lfs_file_read(lfs, &file, &stored_crc, sizeof(stored_crc));
    if (read_size != sizeof(stored_crc)) {
        lfs_file_close(lfs, &file);
        return (read_size < 0) ? read_size : LFS_ERR_IO;
    }

    /* Read LENGTH */
    read_size = lfs_file_read(lfs, &file, &file_length, sizeof(file_length));
    if (read_size != sizeof(file_length)) {
        lfs_file_close(lfs, &file);
        return (read_size < 0) ? read_size : LFS_ERR_IO;
    }

    /* Check buffer size */
    if (file_length > max_length) {
        lfs_file_close(lfs, &file);
        return LFS_ERR_NOSPC;
    }

    /* Read data */
    uint32_t total_read = 0;
    uint8_t *data_ptr = (uint8_t *)data;

    while (total_read < file_length) {
        uint32_t to_read = (file_length - total_read > LFS_FILE_CHUNK_SIZE) ?
                          LFS_FILE_CHUNK_SIZE : (file_length - total_read);

        read_size = lfs_file_read(lfs, &file, data_ptr + total_read, to_read);
        if (read_size < 0) {
            lfs_file_close(lfs, &file);
            return read_size;
        }
        if (read_size == 0) {
            lfs_file_close(lfs, &file);
            return LFS_ERR_CORRUPT;
        }

        total_read += read_size;
    }

    lfs_file_close(lfs, &file);

    /* Calculate CRC of LENGTH + DATA */
    uint8_t *crc_buffer = (uint8_t *)malloc(sizeof(file_length) + file_length);
    if (!crc_buffer) {
        return LFS_ERR_NOMEM;
    }

    memcpy(crc_buffer, &file_length, sizeof(file_length));
    memcpy(crc_buffer + sizeof(file_length), data, file_length);

    calculated_crc = util_crc_compute_crc32(crc_buffer, sizeof(file_length) + file_length);
    free(crc_buffer);

    /* Verify CRC */
    if (stored_crc != calculated_crc) {
        return LFS_ERR_CORRUPT;
    }

    *length = file_length;
    return 0;
}

int lfs_file_verify_crc(lfs_t *lfs, const char *filename,
                        uint32_t *out_crc, uint32_t *out_length)
{
    lfs_file_t file;
    uint32_t stored_crc, length, calculated_crc;

    /* Validate input */
    if (!lfs || !filename) {
        return LFS_ERR_INVAL;
    }

    /* Try opening file (may return LFS_ERR_NOENT) */
    int err = lfs_file_open(lfs, &file, filename, LFS_O_RDONLY);
    if (err) {
        return err;
    }

    /* Read stored CRC */
    lfs_ssize_t read_size = lfs_file_read(lfs, &file, &stored_crc, sizeof(stored_crc));
    if (read_size < 0) {
        lfs_file_close(lfs, &file);
        return (int)read_size;     /* LittleFS I/O error code */
    }
    if (read_size != (lfs_ssize_t)sizeof(stored_crc)) {
        /* Header truncated → treat as corruption */
        lfs_file_close(lfs, &file);
        return LFS_ERR_CORRUPT;
    }

    /* Read LENGTH field */
    read_size = lfs_file_read(lfs, &file, &length, sizeof(length));
    if (read_size < 0) {
        lfs_file_close(lfs, &file);
        return (int)read_size;
    }
    if (read_size != (lfs_ssize_t)sizeof(length)) {
        /* Header truncated → corruption */
        lfs_file_close(lfs, &file);
        return LFS_ERR_CORRUPT;
    }

    /* Allocate buffer for LENGTH + DATA */
    uint8_t *crc_buffer = (uint8_t *)malloc(sizeof(length) + length);
    if (!crc_buffer) {
        lfs_file_close(lfs, &file);
        return LFS_ERR_NOMEM;
    }

    /* Prepare CRC calculation buffer:
     * The CRC covers LENGTH + DATA fields.
     */
    memcpy(crc_buffer, &length, sizeof(length));

    /* Read DATA section */
    lfs_ssize_t data_read = lfs_file_read(lfs, &file,
                                          crc_buffer + sizeof(length),
                                          length);

    lfs_file_close(lfs, &file);

    if (data_read < 0) {
        free(crc_buffer);
        return (int)data_read;
    }
    if (data_read != (lfs_ssize_t)length) {
        /* Data truncated */
        free(crc_buffer);
        return LFS_ERR_CORRUPT;
    }

    /* Compute CRC over LENGTH + DATA */
    calculated_crc = util_crc_compute_crc32(crc_buffer,
                                            sizeof(length) + length);
    free(crc_buffer);

    /* Compare stored CRC and computed CRC */
    if (stored_crc != calculated_crc) {
        return LFS_ERR_CORRUPT;
    }

    /* Output fields on success */
    if (out_crc) {
        *out_crc = stored_crc;
    }
    if (out_length) {
        *out_length = length;
    }

    return 0;
}

int lfs_file_copy_with_crc(lfs_t *lfs, const char *src_filename,
                           const char *dst_filename)
{
    lfs_file_t src, dst;
    uint8_t buffer[LFS_FILE_CHUNK_SIZE];

    if (!lfs || !src_filename || !dst_filename) {
        return LFS_ERR_INVAL;
    }

    /* Verify source file first */
    int err = lfs_file_verify_crc(lfs, src_filename, NULL, NULL);
    if (err) {
        return err;
    }

    /* Open source */
    err = lfs_file_open(lfs, &src, src_filename, LFS_O_RDONLY);
    if (err) {
        return err;
    }

    /* Open destination */
    err = lfs_file_open(lfs, &dst, dst_filename,
                        LFS_O_WRONLY | LFS_O_CREAT | LFS_O_TRUNC);
    if (err) {
        lfs_file_close(lfs, &src);
        return err;
    }

    /* Copy file */
    while (1) {
        lfs_ssize_t read_size = lfs_file_read(lfs, &src, buffer, LFS_FILE_CHUNK_SIZE);
        if (read_size < 0) {
            lfs_file_close(lfs, &src);
            lfs_file_close(lfs, &dst);
            return read_size;
        }
        if (read_size == 0) break;

        lfs_ssize_t written = lfs_file_write(lfs, &dst, buffer, read_size);
        if (written != read_size) {
            lfs_file_close(lfs, &src);
            lfs_file_close(lfs, &dst);
            return (written < 0) ? written : LFS_ERR_IO;
        }
    }

    lfs_file_close(lfs, &src);
    lfs_file_close(lfs, &dst);

    /* Verify destination */
    return lfs_file_verify_crc(lfs, dst_filename, NULL, NULL);
}

int lfs_file_make_backup_name(const char *filename,
                              char *backup_name,
                              uint32_t buf_size)
{
    if (!filename || !backup_name || buf_size == 0) return -1;
    int n = snprintf(backup_name, buf_size, "%s.bak", filename);
    if (n <= 0 || (uint32_t)n >= buf_size) return -1;
    return 0;
}

int lfs_file_verify(lfs_t *lfs,
                       const char *filename,
                       void *data,
                       uint32_t buffer_size,
                       uint32_t *output_size,
                       bool restore_with_backup)
{
    if (!lfs || !filename) {
        LFS_ERROR("verify_or_restore: invalid args\n");
        return LFS_ERR_INVAL;
    }

    uint32_t crc = 0;
    uint32_t len = 0;
    int ret;

    /* --------------------------------------------------------
     * Step 1: verify primary
     * -------------------------------------------------------- */
    ret = lfs_file_verify_crc(lfs, filename, &crc, &len);

    if (ret == 0) {
        /* primary valid */
        if (output_size) {
            *output_size = len;
        }

        if (data) {
            if (len > buffer_size) {
                LFS_ERROR("verify_or_restore: buffer too small (%lu < %lu)\n",
                    (unsigned long)buffer_size,
                    (unsigned long)len);
                return LFS_ERR_NOMEM;
            }

            uint32_t actual = 0;
            ret = lfs_file_read_with_crc(lfs, filename, data,
                                 &actual, buffer_size);
            if (ret != 0 || actual != len) {
                LFS_ERROR("verify_or_restore: read primary failed (%s)\n",
                    filename);
                return (ret != 0) ? ret : LFS_ERR_IO;
            }
	}
	/* success */
	return LFS_VERIFY_OK;
    }

    if (!restore_with_backup)
        return LFS_VERIFY_ERROR;

    /* remember primary error (NOENT / CORRUPT / IO, ...) */
    int primary_ret = ret;

    /* --------------------------------------------------------
     * Step 2: verify backup "<filename>.bak"
     * -------------------------------------------------------- */
    char bak[64];

    ret = lfs_file_make_backup_name(filename, bak, sizeof(bak));
    if (ret != 0) {
        LFS_ERROR("verify_or_restore: make_backup_name failed (%s)\n",
            filename);
        return ret;
    }

    uint32_t bak_crc = 0;
    uint32_t bak_len = 0;
    int bak_ret = lfs_file_verify_crc(lfs, bak, &bak_crc, &bak_len);

    if (bak_ret == 0) {
        /* backup valid - restore */
        if (output_size) {
            *output_size = bak_len;
        }

        if (data && bak_len > buffer_size) {
            LFS_ERROR("verify_or_restore: buffer too small for backup (%lu < %lu)\n",
                (unsigned long)buffer_size,
                (unsigned long)bak_len);
            return LFS_ERR_NOMEM;
        }

        LFS_WARN("verify_or_restore: restoring '%s' from '%s'\n",
            filename, bak);

        /* backup -> primary */
        ret = lfs_file_copy_with_crc(lfs, bak, filename);
        if (ret != 0) {
            LFS_ERROR("verify_or_restore: restore copy failed (%s <- %s)\n",
                filename, bak);
            return ret;
        }

        if (data) {
            uint32_t actual = 0;
            ret = lfs_file_read_with_crc(lfs, filename, data,
                             &actual, buffer_size);
            if (ret != 0 || actual != bak_len) {
                LFS_ERROR("verify_or_restore: read after restore failed (%s)\n",
                    filename);
                return (ret != 0) ? ret : LFS_ERR_IO;
            }
        }

        return LFS_VERIFY_RESTORED;
    }

    /* --------------------------------------------------------
     * Step 3: no valid primary nor backup
     *
     *  - both missing (NOENT + NOENT)  -> treat as "not found"
     *  - any other combination         -> error
     *
     * This means:
     *   primary corrupted + backup missing      -> ERROR
     *   primary missing   + backup corrupted    -> ERROR
     *   primary corrupted + backup corrupted    -> ERROR
     *   primary IO error  + backup missing/...  -> ERROR
     * -------------------------------------------------------- */

    if (primary_ret == LFS_ERR_NOENT && bak_ret == LFS_ERR_NOENT) {
        LFS_WARN("verify_or_restore: neither primary nor backup found (%s)\n",
            filename);
        if (output_size) {
            *output_size = 0;
        }
        return LFS_VER_NOT_FOUND;   /* caller can treat as "need init" */
    }

    LFS_ERROR("verify_or_restore: no valid data (file:%s, backup:%s) "
        "(primary=%d, backup=%d)\n",
        filename, bak, primary_ret, bak_ret);

    return LFS_VERIFY_ERROR;
}

int lfs_file_verify_or_restore_with_backup(lfs_t *lfs,
                       const char *filename,
                       void *data,
                       uint32_t buffer_size,
                       uint32_t *output_size)
{
    return lfs_file_verify(lfs, filename, data, buffer_size, output_size, true);
}

#if 0
int lfs_file_update_with_backup(lfs_t *lfs,
                const char *filename,
                const void *data,
                uint32_t data_size)
{
    int ret;
    char bak[64];

    if (!lfs || !filename || !data || data_size == 0) {
        LFS_ERROR("update_with_backup: invalid args\n");
        return LFS_ERR_INVAL;
    }

    /* 1) write primary with CRC header */
    ret = lfs_file_write_with_crc(lfs, filename, data, data_size);
    if (ret != 0) {
        LFS_ERROR("update_with_backup: primary update failed (%s)\n",
            filename);
        return ret;
    }

    /* 2) build backup name "<filename>.bak" */
    ret = lfs_file_make_backup_name(filename, bak, sizeof(bak));
    if (ret != 0) {
        LFS_ERROR("update_with_backup: make_backup_name failed (%s)\n",
            filename);
        return ret;
    }

    /* 3) primary -> backup with CRC verification */
    ret = lfs_file_copy_with_crc(lfs, filename, bak);
    if (ret != 0) {
        LFS_ERROR("update_with_backup: backup update failed (%s -> %s)\n",
            filename, bak);
        return ret;
    }

    return 0;
}
#else
int lfs_file_update(lfs_t *lfs,
                const char *filename,
                const void *data,
                uint32_t data_size, bool backup)
{
    int ret;

    if (!lfs || !filename || !data || data_size == 0) {
        LFS_ERROR("update_with_backup: invalid args\n");
        return LFS_ERR_INVAL;
    }

    /* 1) write primary with CRC */
    ret = _lfs_file_write_with_crc(lfs, filename, data, data_size, true);
    if (ret != 0) {
        LFS_ERROR("update_with_backup: primary update failed (%s)\n", filename);
        return ret;
    } 

    if (backup) {
        char filename_bak[64];

        /* 2) build backup name "<filename>.bak" */
        ret = lfs_file_make_backup_name(filename, filename_bak, sizeof(filename_bak));
        if (ret != 0) {
            LFS_ERROR("update_with_backup: make_backup_name failed (%s)\n",
                    filename);
            return ret;
        }

        /* 3) write backup with CRC */
        ret = _lfs_file_write_with_crc(lfs, filename_bak, data, data_size, true);
        if (ret != 0) {
            LFS_ERROR("update_with_backup: backup update failed (%s -> %s)\n",
                    filename, filename_bak);
            return ret;
        }
    }
    
    return 0;
}

int lfs_file_update_with_backup(lfs_t *lfs,
                const char *filename,
                const void *data,
                uint32_t data_size)
{
    return lfs_file_update(lfs, filename, data, data_size, true);
}
#endif

int lfs_file_print_data(lfs_t *lfs, const char *filename,
                        uint32_t print_flags, uint32_t offset, uint32_t size)
{
    lfs_file_t file;
    uint32_t stored_crc, file_length;
    uint8_t *data = NULL;
    uint32_t print_size, actual_offset;

    if (!lfs || !filename) {
        return LFS_ERR_INVAL;
    }

    /* Open file */
    int err = lfs_file_open(lfs, &file, filename, LFS_O_RDONLY);
    if (err) {
        return err;
    }

    /* Read CRC */
    lfs_ssize_t bytes_read = lfs_file_read(lfs, &file, &stored_crc, sizeof(stored_crc));
    if (bytes_read != sizeof(stored_crc)) {
        lfs_file_close(lfs, &file);
        return (bytes_read < 0) ? bytes_read : LFS_ERR_CORRUPT;
    }

    /* Read LENGTH */
    bytes_read = lfs_file_read(lfs, &file, &file_length, sizeof(file_length));
    if (bytes_read != sizeof(file_length)) {
        lfs_file_close(lfs, &file);
        return (bytes_read < 0) ? bytes_read : LFS_ERR_CORRUPT;
    }

    /* Print header (always shown) */
    printf("\n=== File: %s ===\n", filename);
    printf("CRC32  : 0x%08X\n", (unsigned int)stored_crc);
    printf("LENGTH : %lu bytes\n", (unsigned long)file_length);

    /* Determine print range */
    actual_offset = (offset > file_length) ? file_length : offset;
    if (size == 0 || (actual_offset + size) > file_length) {
        print_size = file_length - actual_offset;
    } else {
        print_size = size;
    }

    /* If no print flags or zero print size, just show header */
    if (print_flags == 0 || print_size == 0) {
        lfs_file_close(lfs, &file);
        return 0;
    }

    /* Allocate buffer for data */
    data = (uint8_t *)malloc(print_size);
    if (!data) {
        lfs_file_close(lfs, &file);
        return LFS_ERR_NOMEM;
    }

    /* Seek to offset and read data */
    err = lfs_file_seek(lfs, &file, LFS_FILE_DATA_OFFSET + actual_offset, LFS_SEEK_SET);
    if (err < 0) {
        free(data);
        lfs_file_close(lfs, &file);
        return err;
    }

    bytes_read = lfs_file_read(lfs, &file, data, print_size);
    lfs_file_close(lfs, &file);

    if (bytes_read != (lfs_ssize_t)print_size) {
        free(data);
        return (bytes_read < 0) ? bytes_read : LFS_ERR_IO;
    }

    /* Print data section header */
    printf("DATA   : Offset=%lu, Size=%lu bytes\n",
                  (unsigned long)actual_offset, (unsigned long)print_size);

    /* Print based on flags */
    if ((print_flags & LFS_PRINT_HEX) && (print_flags & LFS_PRINT_STRING)) {
        /* Both hex and string - side by side format */
        printf("Offset   : 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F | ASCII\n");
        printf("---------|-------------------------------------------------|----------------\n");

        for (uint32_t i = 0; i < print_size; i += 16) {
            /* Print offset */
            printf("%08lX : ", (unsigned long)(actual_offset + i));

            /* Print hex bytes */
            for (uint32_t j = 0; j < 16; j++) {
                if (i + j < print_size) {
                    printf("%02X ", data[i + j]);
                } else {
                    printf("   ");
                }
            }

            /* Print ASCII */
            printf("| ");
            for (uint32_t j = 0; j < 16 && (i + j) < print_size; j++) {
                uint8_t c = data[i + j];
                printf("%c", (c >= 32 && c <= 126) ? c : '.');
            }
            printf("\n");
        }
    } else if (print_flags & LFS_PRINT_HEX) {
        /* Hex only */
        printf("Offset   : 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
        printf("---------|-------------------------------------------------\n");

        for (uint32_t i = 0; i < print_size; i += 16) {
            printf("%08lX : ", (unsigned long)(actual_offset + i));
            for (uint32_t j = 0; j < 16; j++) {
                if (i + j < print_size) {
                    printf("%02X ", data[i + j]);
                } else {
                    printf("   ");
                }
            }
            printf("\n");
        }
    } else if (print_flags & LFS_PRINT_STRING) {
        /* String only */
        printf("---------|----------------\n");
        for (uint32_t i = 0; i < print_size; i++) {
            uint8_t c = data[i];
            printf("%c", (c >= 32 && c <= 126) ? c : '.');
            if ((i + 1) % 64 == 0) {
                printf("\n");
            }
        }
        if (print_size % 64 != 0) {
            printf("\n");
        }
    }

    printf("=== End of file ===\n\n");
    free(data);
    return 0;
}
