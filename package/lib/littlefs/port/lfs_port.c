/*
 * LittleFS Port for NRC7394 Internal Flash
 *
 * Copyright (c) 2025
 * SPDX-License-Identifier: MIT
 */

#include "lfs_port.h"
#include "nrc_sdk.h"
#include "hal_sfc.h"
#include <string.h>
#include <stdbool.h>

#include "lfs_config.h"  /* Tunable LittleFS port configuration */

/* LittleFS instance and configuration managed by port layer */
static lfs_t lfs_instance;
static struct lfs_config lfs_config;

/* Backing buffers for cache and lookahead.
 * Sizes are controlled by lfs_config.h macros.
 */
static uint8_t read_buffer[LFS_PORT_READ_BUFFER_SIZE];
static uint8_t prog_buffer[LFS_PORT_PROG_BUFFER_SIZE];
static uint8_t lookahead_buffer[LFS_PORT_LOOKAHEAD_BUFFER_SIZE];

static bool lfs_initialized = false;

/* Read a region in a block */
int lfs_port_read(const struct lfs_config *lfsc,
                  lfs_block_t block,
                  lfs_off_t off,
                  void *buffer,
                  lfs_size_t size)
{
    uint32_t start_address;
    uint32_t block_size;
    uint32_t flash_addr;

    assert(lfsc);

    if (size == 0)
        return LFS_ERR_OK;

    if (!buffer)
        return LFS_ERR_IO;

    start_address = (uint32_t)lfsc->context;
    block_size    = lfsc->block_size;

    if (block >= lfsc->block_count)
        return LFS_ERR_IO;

    if (size > block_size || off > (lfs_off_t)(block_size - size))
        return LFS_ERR_IO;

    flash_addr = start_address + (uint32_t)block * block_size + (uint32_t)off;

    if (flash_addr < start_address)
        return LFS_ERR_IO;

    if (!nrc_sf_read(flash_addr, buffer, size))
        return LFS_ERR_IO;

    return LFS_ERR_OK;
}

/* Program a region in a block */
int lfs_port_prog(const struct lfs_config *lfsc,
                  lfs_block_t block,
                  lfs_off_t off,
                  const void *buffer,
                  lfs_size_t size)
{
    uint32_t start_address;
    uint32_t block_size;
    uint32_t flash_addr;

    assert(lfsc);

    start_address = (uint32_t)lfsc->context;
    block_size    = lfsc->block_size;

    if (block >= lfsc->block_count)
        return LFS_ERR_IO;

    if (size == 0)
        return LFS_ERR_OK;

    if (!buffer)
        return LFS_ERR_IO;

    if (size > block_size || off > (lfs_off_t)(block_size - size))
        return LFS_ERR_IO;

    if ((off % lfsc->prog_size) != 0 || (size % lfsc->prog_size) != 0)
        return LFS_ERR_IO;

    flash_addr = start_address
               + (uint32_t)block * block_size
               + (uint32_t)off;

    if (flash_addr < start_address)
        return LFS_ERR_IO;

    if (!nrc_sf_write(flash_addr, (void *)buffer, size))
        return LFS_ERR_IO;

    return LFS_ERR_OK;
}

/* Erase a block */
int lfs_port_erase(const struct lfs_config *lfsc, lfs_block_t block)
{
    uint32_t start_address;
    uint32_t flash_addr;
    uint32_t block_size;

    assert(lfsc);

    start_address = (uint32_t)lfsc->context;
    block_size    = lfsc->block_size;

    if (block >= lfsc->block_count)
        return LFS_ERR_IO;

    flash_addr = start_address + (uint32_t)block * block_size;

    if (flash_addr < start_address)
        return LFS_ERR_IO;

    if (!nrc_sf_erase(flash_addr, block_size))
        return LFS_ERR_IO;

    return LFS_ERR_OK;
}

/* Sync the underlying device (unused for synchronous NOR flash) */
int lfs_port_sync(const struct lfs_config *lfsc)
{
    (void)lfsc;
    return LFS_ERR_OK;
}


lfs_t *lfs_port_get_instance(void)
{
    return lfs_initialized ? &lfs_instance : NULL;
}


#ifdef LFS_THREADSAFE

SemaphoreHandle_t xlfsSemaphore;
StaticSemaphore_t xlfsMutexSystemBuffer;

/* NOTE: mutex is created in lfs_port_init() */
int lfs_lock(const struct lfs_config *cfg)
{
    (void)cfg;

    if (!xlfsSemaphore) {
        printf("lfs_lock: semaphore not initialized\n");
        return LFS_ERR_IO;
    }

    ASSERT(!xPortIsInsideInterrupt());

    if (xSemaphoreTakeRecursive(xlfsSemaphore, portMAX_DELAY) == pdTRUE) {
        return LFS_ERR_OK;
    }

    printf("lfs_lock: failed to take mutex\n");
    return LFS_ERR_IO;
}

int lfs_unlock(const struct lfs_config *cfg)
{
    (void)cfg;

    if (!xlfsSemaphore) {
        printf("lfs_unlock: semaphore not initialized\n");
        return LFS_ERR_IO;
    }

    ASSERT(!xPortIsInsideInterrupt());

    if (xSemaphoreGiveRecursive(xlfsSemaphore) == pdTRUE) {
        return LFS_ERR_OK;
    }

    printf("lfs_unlock: failed to give mutex\n");
    return LFS_ERR_IO;
}

#endif /* LFS_THREADSAFE */


/* Initialize LittleFS port (create mutex and mount filesystem) */
int lfs_port_init(void)
{
    int ret;
    
    if (lfs_initialized) {
        printf("[INFO] LFS already intialized.\n");
        return 0;
    }

#ifdef LFS_THREADSAFE
    xlfsSemaphore = xSemaphoreCreateRecursiveMutexStatic(&xlfsMutexSystemBuffer);
    if (!xlfsSemaphore) {
        printf("ERROR: LFS lock/unlock mutex creation failed\n");
        return -1;
    }
#endif

    /* Initialize configuration */
    lfs_port_init_config(&lfs_config);

    /* Attach static buffers */
    lfs_config.read_buffer      = read_buffer;
    lfs_config.prog_buffer      = prog_buffer;
    lfs_config.lookahead_buffer = lookahead_buffer;

    /* Try to mount existing filesystem */
    ret = lfs_mount(&lfs_instance, &lfs_config);
    if (ret != LFS_ERR_OK) {
        /* Format if mount fails (first time or corrupted) */
        printf("[INFO] Formatting LittleFS...\n");
        ret = lfs_format(&lfs_instance, &lfs_config);
        if (ret != LFS_ERR_OK) {
            printf("[ERROR] Format failed: %d\n", ret);
            return -1;
        }
        ret = lfs_mount(&lfs_instance, &lfs_config);
        if (ret != LFS_ERR_OK) {
            printf("[ERROR] Mount after format failed: %d\n", ret);
            return -1;
        }
    }

    printf("[INFO] LFS intialized.\n");
    lfs_initialized = true;
    return 0;
}

int lfs_port_format(void)
{
    int ret;

    if (!lfs_initialized) {
        ret = lfs_port_init();
        if (ret != 0)
            return ret;
    }

    ret = lfs_unmount(&lfs_instance);
    lfs_initialized = false;
    if (ret != LFS_ERR_OK) {
        printf("[ERROR] LFS unmount before format failed: %d\n", ret);
        return -1;
    }

    ret = lfs_format(&lfs_instance, &lfs_config);
    if (ret != LFS_ERR_OK) {
        printf("[ERROR] LFS format failed: %d\n", ret);
        return -1;
    }

    ret = lfs_mount(&lfs_instance, &lfs_config);
    if (ret != LFS_ERR_OK) {
        printf("[ERROR] LFS mount after format failed: %d\n", ret);
        return -1;
    }

    lfs_initialized = true;
    printf("[INFO] LFS formatted and remounted.\n");
    return 0;
}


/* Initialize LittleFS configuration for NRC7394 */
void lfs_port_init_config(struct lfs_config *cfg)
{
    memset(cfg, 0, sizeof(*cfg));

    /* Block device operations */
    cfg->read  = lfs_port_read;
    cfg->prog  = lfs_port_prog;
    cfg->erase = lfs_port_erase;
    cfg->sync  = lfs_port_sync;

    /* Block device configuration (tunable via lfs_config.h) */
    cfg->read_size      = LFS_PORT_READ_SIZE;
    cfg->prog_size      = LFS_PORT_PROG_SIZE;
    cfg->block_size     = LFS_PORT_BLOCK_SIZE;
    cfg->block_count    = LFS_PORT_BLOCK_COUNT;
    cfg->cache_size     = LFS_PORT_CACHE_SIZE;
    cfg->lookahead_size = LFS_PORT_LOOKAHEAD_SIZE;
    cfg->block_cycles   = LFS_PORT_BLOCK_CYCLES;

    /* Base address for the flash region used by LittleFS */
    cfg->context = (void *)LFS_FLASH_START_ADDRESS;

#ifdef LFS_THREADSAFE
    cfg->lock = lfs_lock;
    cfg->unlock = lfs_unlock;
#endif
    /* Buffers are assigned separately in lfs_port_init() */
}
