/*
 * MIT License
 *
 * LittleFS <-> FATFS Bridge Implementation
 */

#include "lfs_fatfs_bridge.h"
#include <string.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "nrc_sdk.h"

#define BRIDGE_BUFFER_SIZE 512
#define MAX_FILENAME_LEN 256  /* Increased to handle full FATFS filename length */

/* Copy file implementation */
int bridge_copy_file(lfs_t *lfs, FATFS *fatfs, const char *filename, bridge_direction_t direction)
{
    lfs_file_t lfs_file;
    FIL fat_file;
    uint8_t *buffer;
    int result = BRIDGE_OK;
    char lfs_path[MAX_FILENAME_LEN];
    char fat_path[MAX_FILENAME_LEN];

    if (!lfs || !fatfs || !filename) {
        return BRIDGE_ERR_INVALID_PARAM;
    }

    /* Allocate transfer buffer */
    buffer = (uint8_t *)malloc(BRIDGE_BUFFER_SIZE);
    if (!buffer) {
        LFS_ERROR("[Bridge] Failed to allocate buffer (size=%d)", BRIDGE_BUFFER_SIZE);
        return BRIDGE_ERR_MALLOC;
    }

    /* Build paths - use snprintf safely */
    int lfs_path_len = snprintf(lfs_path, sizeof(lfs_path), "/%s", filename);
    int fat_path_len = snprintf(fat_path, sizeof(fat_path), "/%s", filename);

    if (lfs_path_len < 0 || lfs_path_len >= (int)sizeof(lfs_path) ||
        fat_path_len < 0 || fat_path_len >= (int)sizeof(fat_path)) {
        LFS_ERROR("[Bridge] Filename too long: %s", filename);
        free(buffer);
        return BRIDGE_ERR_INVALID_PARAM;
    }

    if (direction == BRIDGE_LFS_TO_FATFS) {
        /* LittleFS -> FATFS */

        /* Open source file (LittleFS) for reading */
        int lfs_err = lfs_file_open(lfs, &lfs_file, lfs_path, LFS_O_RDONLY);
        if (lfs_err < 0) {
            LFS_ERROR("[Bridge] Failed to open LFS file %s: %d", lfs_path, lfs_err);
            free(buffer);
            return BRIDGE_ERR_SRC_OPEN;
        }

        /* Open destination file (FATFS) for writing */
        FRESULT fat_res = f_open(&fat_file, fat_path, FA_CREATE_ALWAYS | FA_WRITE);
        if (fat_res != FR_OK) {
            LFS_ERROR("[Bridge] Failed to open FAT file %s: %d", fat_path, fat_res);
            lfs_file_close(lfs, &lfs_file);
            free(buffer);
            return BRIDGE_ERR_DST_OPEN;
        }

        /* Copy data */
        while (1) {
            lfs_ssize_t bytes_read = lfs_file_read(lfs, &lfs_file, buffer, BRIDGE_BUFFER_SIZE);
            if (bytes_read < 0) {
                LFS_ERROR("[Bridge] LFS read error: %d", (int)bytes_read);
                result = BRIDGE_ERR_READ;
                break;
            }
            if (bytes_read == 0) {
                break; /* EOF */
            }

            UINT bytes_written;
            fat_res = f_write(&fat_file, buffer, bytes_read, &bytes_written);
            if (fat_res != FR_OK || bytes_written != (UINT)bytes_read) {
                LFS_ERROR("[Bridge] FAT write error: res=%d, written=%u, expected=%d",
                    fat_res, (unsigned int)bytes_written, (int)bytes_read);
                result = BRIDGE_ERR_WRITE;
                break;
            }
        }

        /* Close files */
        lfs_file_close(lfs, &lfs_file);
        f_close(&fat_file);

    } else {
        /* FATFS -> LittleFS */

        /* Open source file (FATFS) for reading */
        FRESULT fat_res = f_open(&fat_file, fat_path, FA_READ);
        if (fat_res != FR_OK) {
            LFS_ERROR("[Bridge] Failed to open FAT file %s: %d", fat_path, fat_res);
            free(buffer);
            return BRIDGE_ERR_SRC_OPEN;
        }

        /* Open destination file (LittleFS) for writing */
        int lfs_err = lfs_file_open(lfs, &lfs_file, lfs_path,
                        LFS_O_WRONLY | LFS_O_CREAT | LFS_O_TRUNC);
        if (lfs_err < 0) {
            LFS_ERROR("[Bridge] Failed to open LFS file %s: %d", lfs_path, lfs_err);
            f_close(&fat_file);
            free(buffer);
            return BRIDGE_ERR_DST_OPEN;
        }

        /* Copy data */
        while (1) {
            UINT bytes_read;
            fat_res = f_read(&fat_file, buffer, BRIDGE_BUFFER_SIZE, &bytes_read);
            if (fat_res != FR_OK) {
                LFS_ERROR("[Bridge] FAT read error: %d", fat_res);
                result = BRIDGE_ERR_READ;
                break;
            }
            if (bytes_read == 0) {
                break; /* EOF */
            }

            lfs_ssize_t bytes_written = lfs_file_write(lfs, &lfs_file, buffer, bytes_read);
            if (bytes_written < 0 || (UINT)bytes_written != bytes_read) {
                LFS_ERROR("[Bridge] LFS write error: %d", (int)bytes_written);
                result = BRIDGE_ERR_WRITE;
                break;
            }
        }

        /* Close files */
        f_close(&fat_file);
        lfs_file_close(lfs, &lfs_file);
    }

    free(buffer);

    if (result == BRIDGE_OK) {
        LFS_DEBUG("[Bridge] Copied %s: %s -> %s",
            filename,
            (direction == BRIDGE_LFS_TO_FATFS) ? "LFS" : "FAT",
            (direction == BRIDGE_LFS_TO_FATFS) ? "FAT" : "LFS");
    }

    return result;
}

/* Compare file implementation */
int bridge_compare_file(lfs_t *lfs, FATFS *fatfs, const char *filename)
{
    lfs_file_t lfs_file;
    FIL fat_file;
    uint8_t *lfs_buffer;
    uint8_t *fat_buffer;
    int result = BRIDGE_OK;
    char lfs_path[MAX_FILENAME_LEN];
    char fat_path[MAX_FILENAME_LEN];

    if (!lfs || !fatfs || !filename) {
        return BRIDGE_ERR_INVALID_PARAM;
    }

    /* Allocate buffers */
    lfs_buffer = (uint8_t *)malloc(BRIDGE_BUFFER_SIZE);
    fat_buffer = (uint8_t *)malloc(BRIDGE_BUFFER_SIZE);
    if (!lfs_buffer || !fat_buffer) {
        if (lfs_buffer) {
            free(lfs_buffer);
        }
        if (fat_buffer) {
            free(fat_buffer);
        }
        LFS_ERROR("[Bridge] Failed to allocate compare buffers");
        return BRIDGE_ERR_MALLOC;
    }

    /* Build paths */
    int lfs_path_len = snprintf(lfs_path, sizeof(lfs_path), "/%s", filename);
    int fat_path_len = snprintf(fat_path, sizeof(fat_path), "/%s", filename);

    if (lfs_path_len < 0 || lfs_path_len >= (int)sizeof(lfs_path) ||
        fat_path_len < 0 || fat_path_len >= (int)sizeof(fat_path)) {
        LFS_ERROR("[Bridge] Filename too long for compare: %s", filename);
        free(lfs_buffer);
        free(fat_buffer);
        return BRIDGE_ERR_INVALID_PARAM;
    }

    /* Open LittleFS file */
    int lfs_err = lfs_file_open(lfs, &lfs_file, lfs_path, LFS_O_RDONLY);
    if (lfs_err < 0) {
        LFS_ERROR("[Bridge] Failed to open LFS file for compare: %s (err=%d)",
            lfs_path, lfs_err);
        free(lfs_buffer);
        free(fat_buffer);
        return BRIDGE_ERR_SRC_OPEN;
    }

    /* Open FATFS file */
    FRESULT fat_res = f_open(&fat_file, fat_path, FA_READ);
    if (fat_res != FR_OK) {
        LFS_ERROR("[Bridge] Failed to open FAT file for compare: %s (res=%d)",
            fat_path, fat_res);
        lfs_file_close(lfs, &lfs_file);
        free(lfs_buffer);
        free(fat_buffer);
        return BRIDGE_ERR_SRC_OPEN;
    }

    /* Compare contents */
    while (1) {
        lfs_ssize_t lfs_read = lfs_file_read(lfs, &lfs_file, lfs_buffer, BRIDGE_BUFFER_SIZE);
        UINT fat_read = 0;
        fat_res = f_read(&fat_file, fat_buffer, BRIDGE_BUFFER_SIZE, &fat_read);

        if (lfs_read < 0 || fat_res != FR_OK) {
            LFS_ERROR("[Bridge] Read error while comparing: lfs=%d, fat=%d",
                (int)lfs_read, fat_res);
            result = BRIDGE_ERR_READ;
            break;
        }

        if (lfs_read != (lfs_ssize_t)fat_read) {
            LFS_WARN("[Bridge] File size mismatch while comparing: %s", filename);
            result = BRIDGE_ERR_VERIFY;
            break;
        }

        if (lfs_read == 0) {
            /* EOF - files match */
            break;
        }

        if (memcmp(lfs_buffer, fat_buffer, lfs_read) != 0) {
            LFS_WARN("[Bridge] File content mismatch: %s", filename);
            result = BRIDGE_ERR_VERIFY;
            break;
        }
    }

    /* Close files */
    lfs_file_close(lfs, &lfs_file);
    f_close(&fat_file);
    free(lfs_buffer);
    free(fat_buffer);

    if (result == BRIDGE_OK) {
        LFS_DEBUG("[Bridge] Files match: %s", filename);
    }

    return result;
}

/* Copy all files implementation */
int bridge_copy_all(lfs_t *lfs, FATFS *fatfs, bridge_direction_t direction)
{
    int count = 0;
    char lfs_path[MAX_FILENAME_LEN];
    char fat_path[MAX_FILENAME_LEN];

    if (!lfs || !fatfs) {
        return BRIDGE_ERR_INVALID_PARAM;
    }

    if (direction == BRIDGE_LFS_TO_FATFS) {
        /* Copy all from LittleFS to FATFS */
        lfs_dir_t dir;
        struct lfs_info info;

        int err = lfs_dir_open(lfs, &dir, "/");
        if (err < 0) {
            LFS_ERROR("[Bridge] Failed to open LFS root directory (err=%d)", err);
            return err;
        }

        while (lfs_dir_read(lfs, &dir, &info) > 0) {
            if (info.type == LFS_TYPE_REG) {
                /* Check filename length before using it */
                size_t name_len = strlen(info.name);
                if (name_len == 0 || name_len >= (MAX_FILENAME_LEN - 2)) {
                    LFS_WARN("[Bridge] Skipping file with invalid name length: %zu",
                        name_len);
                    continue;
                }

                int lfs_path_len = snprintf(lfs_path, sizeof(lfs_path), "/%s", info.name);
                int fat_path_len = snprintf(fat_path, sizeof(fat_path), "/%s", info.name);

                if (lfs_path_len < 0 || lfs_path_len >= (int)sizeof(lfs_path) ||
                    fat_path_len < 0 || fat_path_len >= (int)sizeof(fat_path)) {
                    LFS_WARN("[Bridge] Path too long, skipping: %s", info.name);
                    continue;
                }

                if (bridge_copy_file(lfs, fatfs, info.name, direction) == BRIDGE_OK) {
                    count++;
                }
            }
        }

        lfs_dir_close(lfs, &dir);

    } else {
        /* Copy all from FATFS to LittleFS */
        DIR dir;
        FILINFO finfo;

        FRESULT res = f_opendir(&dir, "/");
        if (res != FR_OK) {
            LFS_ERROR("[Bridge] Failed to open FAT root directory (res=%d)", res);
            return res;
        }

        while (1) {
            res = f_readdir(&dir, &finfo);
            if (res != FR_OK || finfo.fname[0] == 0) {
                break; /* Error or end of dir */
            }

            if (!(finfo.fattrib & AM_DIR)) {
                /* Check filename length */
                size_t name_len = strlen(finfo.fname);
                if (name_len == 0 || name_len >= (MAX_FILENAME_LEN - 2)) {
                    LFS_WARN("[Bridge] Skipping file with invalid name length: %zu",
                        name_len);
                    continue;
                }

                int lfs_path_len = snprintf(lfs_path, sizeof(lfs_path), "/%s", finfo.fname);
                int fat_path_len = snprintf(fat_path, sizeof(fat_path), "/%s", finfo.fname);

                if (lfs_path_len < 0 || lfs_path_len >= (int)sizeof(lfs_path) ||
                    fat_path_len < 0 || fat_path_len >= (int)sizeof(fat_path)) {
                    LFS_WARN("[Bridge] Path too long, skipping: %s", finfo.fname);
                    continue;
                }

                if (bridge_copy_file(lfs, fatfs, finfo.fname, direction) == BRIDGE_OK) {
                    count++;
                }
            }
        }

        f_closedir(&dir);
    }

    LFS_DEBUG("[Bridge] Copied %d files (%s -> %s)",
        count,
        (direction == BRIDGE_LFS_TO_FATFS) ? "LFS" : "FAT",
        (direction == BRIDGE_LFS_TO_FATFS) ? "FAT" : "LFS");

    return count;
}

/* List LittleFS files */
int bridge_list_lfs(lfs_t *lfs)
{
    lfs_dir_t dir;
    struct lfs_info info;
    int count = 0;

    if (!lfs) {
        return BRIDGE_ERR_INVALID_PARAM;
    }

    int err = lfs_dir_open(lfs, &dir, "/");
    if (err < 0) {
        LFS_ERROR("[Bridge] Failed to open LFS root (err=%d)", err);
        return err;
    }

    LFS_DEBUG("[Bridge] Listing LittleFS files");
    printf("\n[LittleFS Files]\n");
    printf("%-32s %10s\n", "Name", "Size");
    printf("----------------------------------------\n");

    while (lfs_dir_read(lfs, &dir, &info) > 0) {
        if (info.type == LFS_TYPE_REG) {
            printf("%-32s %10d\n", info.name, (int)info.size);
            count++;
        }
    }

    printf("----------------------------------------\n");
    printf("Total: %d files\n\n", count);

    lfs_dir_close(lfs, &dir);

    return count;
}

/* List FATFS files */
int bridge_list_fatfs(FATFS *fatfs)
{
    DIR dir;
    FILINFO finfo;
    int count = 0;

    if (!fatfs) {
        return BRIDGE_ERR_INVALID_PARAM;
    }

    FRESULT res = f_opendir(&dir, "/");
    if (res != FR_OK) {
        LFS_ERROR("[Bridge] Failed to open FAT root (res=%d)", res);
        return res;
    }

    LFS_DEBUG("[Bridge] Listing FATFS files");
    printf("\n[FATFS Files]\n");
    printf("%-32s %10s\n", "Name", "Size");
    printf("----------------------------------------\n");

    while (1) {
        res = f_readdir(&dir, &finfo);
        if (res != FR_OK || finfo.fname[0] == 0) {
            break;
        }

        if (!(finfo.fattrib & AM_DIR)) {
            printf("%-32s %10lu\n", finfo.fname, (unsigned long)finfo.fsize);
            count++;
        }
    }

    printf("----------------------------------------\n");
    printf("Total: %d files\n\n", count);

    f_closedir(&dir);

    return count;
}
