/*
 * LittleFS Port for NRC7394
 *
 * Copyright (c) 2025
 * SPDX-License-Identifier: MIT
 */

#ifndef LFS_PORT_H
#define LFS_PORT_H

#include "lfs.h"
#include <stdint.h>

/* Flash configuration for NRC7394 */
#define LFS_FLASH_START_ADDRESS     0x3DA000    /* SF_USER_DATA_4MB */
#define LFS_FLASH_SIZE      (100 * 1024) /* 100KB */
#define LFS_BLOCK_SIZE      4096         /* 4KB erase block */
#define LFS_PAGE_SIZE      256         /* 256B  */
#define LFS_BLOCK_COUNT     (LFS_FLASH_SIZE / LFS_BLOCK_SIZE)  /* 25 blocks */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the LittleFS porting layer
 *
 * Performs platform-specific initialization required for LittleFS operation,
 * such as allocating work buffers, preparing the block device driver, and
 * optionally creating thread-safety primitives when enabled.
 *
 * If the filesystem has not been formatted yet, this function typically
 * detects it and either formats automatically or reports an error,
 * depending on implementation policy.
 *
 * @return 0 on success
 * @return Negative error code on failure
 *
 * @note Must be called once before any LittleFS operation is used.
 * @note When @ref LFS_THREAD_SAFE_ENABLE is enabled, this function may
 *       create mutex/semaphore resources used during filesystem operations.
 */
int lfs_port_init(void);

/**
 * @brief Format and remount the LittleFS volume managed by the port layer
 *
 * This is destructive and removes every file in the LittleFS partition.
 * The filesystem is remounted before returning so subsequent file APIs can
 * be used without another explicit init call.
 *
 * @return 0 on success
 * @return Negative error code on failure
 */
int lfs_port_format(void);


/**
 * @brief Get the LittleFS instance managed by the port layer
 *
 * Returns a pointer to a global/static LittleFS context (`lfs_t`) that is
 * internally managed by the porting layer. The returned instance is already
 * initialized, mounted, and ready for file system operations.
 *
 * @return Pointer to valid `lfs_t` instance
 * @return NULL if LittleFS has not been initialized or mount failed
 *
 * @note Caller must treat the returned pointer as non-owning and should not
 *       directly free or reset the instance.
 */
lfs_t* lfs_port_get_instance(void);


/**
 * @brief Read data from the underlying block device
 *
 * Called by LittleFS whenever it needs to read raw data from storage.
 * Reads `size` bytes from block `block` at offset `off` into `buffer`,
 * according to the layout specified by @ref lfs_config.
 *
 * @param c      Pointer to LittleFS configuration
 * @param block  Block index to read from
 * @param off    Offset within block (in bytes)
 * @param buffer Destination buffer for data
 * @param size   Number of bytes to read
 *
 * @return 0 on success
 * @return Negative error code on failure
 *
 * @warning Must return data exactly as stored; any bit-flip/dedup logic must
 *          be done below this layer or disabled entirely.
 */
int lfs_port_read(const struct lfs_config *c, lfs_block_t block,
                  lfs_off_t off, void *buffer, lfs_size_t size);


/**
 * @brief Program (write) data to the underlying block device
 *
 * Writes `size` bytes from `buffer` into block `block` at offset `off`,
 * using the storage backend defined by the platform.
 *
 * Implementations must obey LittleFS program constraints, such as:
 * - Writes are idempotent and bit-wise AND operations
 * - Writes may not exceed block boundaries
 *
 * @param c       Pointer to LittleFS configuration
 * @param block   Block index to write to
 * @param off     Offset within block (in bytes)
 * @param buffer  Source buffer containing data
 * @param size    Number of bytes to write
 *
 * @return 0 on success
 * @return Negative error code on failure
 *
 * @note Some hardware requires write alignment; caller must handle padding.
 * @note Many flash devices cannot change 0 → 1 without erase.
 */
int lfs_port_prog(const struct lfs_config *c, lfs_block_t block,
                  lfs_off_t off, const void *buffer, lfs_size_t size);


/**
 * @brief Erase a block on the underlying storage device
 *
 * Erases a single block, resetting it to the default erased state
 * (typically all bits set to 1). This operation is destructive and must
 * ensure that all previous data is removed.
 *
 * @param c     Pointer to LittleFS configuration
 * @param block Block index to erase
 *
 * @return 0 on success
 * @return Negative error code on failure
 *
 * @warning Erase operations are slow and cause wear; implementations should
 *          use wear-leveling techniques where applicable.
 */
int lfs_port_erase(const struct lfs_config *c, lfs_block_t block);


/**
 * @brief Synchronize block device state with storage
 *
 * Ensures that all programmed and erased data is physically committed
 * to non-volatile storage. Some systems may flush caches, commit write
 * buffers, or schedule deferred operations.
 *
 * @param c Pointer to LittleFS configuration
 *
 * @return 0 on success
 * @return Negative error code on failure
 *
 * @note On NOR/NAND flash without caching, this function may be a no-op.
 * @note On buffered storage layers, failure here can cause data loss.
 */
int lfs_port_sync(const struct lfs_config *c);

/**
 * @brief Initialize LittleFS configuration structure
 *
 * Fills the provided @ref lfs_config structure with platform-specific
 * parameters and block device callbacks required by LittleFS.
 *
 * Typical setup includes:
 * - Block size, block count, read/prog/erase sizes
 * - Function pointers (read/prog/erase/sync)
 * - Cache and lookahead buffers
 * - Optional context pointer
 *
 * @param cfg Pointer to allocated config structure to initialize
 *
 * @note Must be called before @ref lfs_mount or @ref lfs_format.
 * @note Caller owns the memory but must not modify fields after mount.
 */
void lfs_port_init_config(struct lfs_config *cfg);

#ifdef __cplusplus
}
#endif

#endif /* LFS_PORT_H */
