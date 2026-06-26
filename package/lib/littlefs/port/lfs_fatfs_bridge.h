/*
 * MIT License
 *
 * LittleFS <-> FATFS Bridge Interface
 *
 * Provides bidirectional file conversion between LittleFS (internal flash)
 * and FATFS (SD card) filesystems.
 */

#ifndef LFS_FATFS_BRIDGE_H
#define LFS_FATFS_BRIDGE_H

#include "lfs.h"
#include "ff.h"

/* Bridge direction */
typedef enum {
    BRIDGE_LFS_TO_FATFS = 0,  /* Copy from LittleFS to FATFS (backup) */
    BRIDGE_FATFS_TO_LFS = 1   /* Copy from FATFS to LittleFS (restore) */
} bridge_direction_t;

/* Bridge result codes */
typedef enum {
    BRIDGE_OK = 0,
    BRIDGE_ERR_SRC_OPEN = -1,
    BRIDGE_ERR_DST_OPEN = -2,
    BRIDGE_ERR_READ = -3,
    BRIDGE_ERR_WRITE = -4,
    BRIDGE_ERR_VERIFY = -5,
    BRIDGE_ERR_MALLOC = -6,
    BRIDGE_ERR_INVALID_PARAM = -7
} bridge_result_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Copy a single file between filesystems
 *
 * @param lfs Pointer to LittleFS instance
 * @param fatfs Pointer to FATFS instance
 * @param filename Name of the file (without path, max 63 chars)
 * @param direction BRIDGE_LFS_TO_FATFS or BRIDGE_FATFS_TO_LFS
 * @return BRIDGE_OK on success, negative error code on failure
 */
int bridge_copy_file(lfs_t *lfs, FATFS *fatfs, const char *filename, bridge_direction_t direction);

/**
 * Copy all files from source to destination filesystem
 *
 * @param lfs Pointer to LittleFS instance
 * @param fatfs Pointer to FATFS instance
 * @param direction BRIDGE_LFS_TO_FATFS or BRIDGE_FATFS_TO_LFS
 * @return Number of files copied, or negative error code
 */
int bridge_copy_all(lfs_t *lfs, FATFS *fatfs, bridge_direction_t direction);

/**
 * Compare a file between two filesystems (verify copy)
 *
 * @param lfs Pointer to LittleFS instance
 * @param fatfs Pointer to FATFS instance
 * @param filename Name of the file to compare
 * @return BRIDGE_OK if files match, negative error code if different or error
 */
int bridge_compare_file(lfs_t *lfs, FATFS *fatfs, const char *filename);

/**
 * List files in LittleFS
 *
 * @param lfs Pointer to LittleFS instance
 * @return Number of files listed, or negative error code
 */
int bridge_list_lfs(lfs_t *lfs);

/**
 * List files in FATFS
 *
 * @param fatfs Pointer to FATFS instance
 * @return Number of files listed, or negative error code
 */
int bridge_list_fatfs(FATFS *fatfs);

#ifdef __cplusplus
}
#endif

#endif /* LFS_FATFS_BRIDGE_H */
