/*
 * LittleFS configuration for NRC7394 (tunable)
 *
 * Copyright (c) 2025
 * SPDX-License-Identifier: MIT
 */

#ifndef LFS_CONFIG_PORT_H
#define LFS_CONFIG_PORT_H

#include "lfs.h"
#include "lfs_port.h"  /* for LFS_BLOCK_SIZE, LFS_BLOCK_COUNT, etc. */

/*
 * Tunable parameters for the LittleFS port.
 *
 * These can be overridden at compile-time by defining them
 * before including this header, or via build system -D flags.
 */

/* Minimum read size (must be a power-of-two, aligned with HW) */
#ifndef LFS_PORT_READ_SIZE
#define LFS_PORT_READ_SIZE           256
#endif

/* Minimum program size (must be a power-of-two, aligned with HW) */
#ifndef LFS_PORT_PROG_SIZE
#define LFS_PORT_PROG_SIZE           256
#endif

/* Erase block size and count (typically provided by board config) */
#ifndef LFS_PORT_BLOCK_SIZE
#define LFS_PORT_BLOCK_SIZE          LFS_BLOCK_SIZE
#endif

#ifndef LFS_PORT_BLOCK_COUNT
#define LFS_PORT_BLOCK_COUNT         LFS_BLOCK_COUNT
#endif

/* Cache size per file (>= read_size, prog_size) */
#ifndef LFS_PORT_CACHE_SIZE
#define LFS_PORT_CACHE_SIZE          1024
#endif

/* Lookahead buffer size in bytes (multiple of 4, 8, or 32 bits) */
#ifndef LFS_PORT_LOOKAHEAD_SIZE
#define LFS_PORT_LOOKAHEAD_SIZE      64
#endif

/* Number of erase cycles before metadata areas are relocated */
#ifndef LFS_PORT_BLOCK_CYCLES
#define LFS_PORT_BLOCK_CYCLES        1000
#endif

/*
 * Backing buffers for cache and lookahead.
 * These define the actual static array sizes.
 */
#ifndef LFS_PORT_READ_BUFFER_SIZE
#define LFS_PORT_READ_BUFFER_SIZE    LFS_PORT_CACHE_SIZE
#endif

#ifndef LFS_PORT_PROG_BUFFER_SIZE
#define LFS_PORT_PROG_BUFFER_SIZE    LFS_PORT_CACHE_SIZE
#endif

#ifndef LFS_PORT_LOOKAHEAD_BUFFER_SIZE
#define LFS_PORT_LOOKAHEAD_BUFFER_SIZE  LFS_PORT_LOOKAHEAD_SIZE
#endif

#endif /* LFS_CONFIG_PORT_H */