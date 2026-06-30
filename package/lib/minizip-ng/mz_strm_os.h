/* mz_strm_os.h -- OS file stream stub for embedded port
   part of the minizip-ng project (NRC SDK embedded port)

   OS file streams are not available on embedded targets.
   All functions return NULL / MZ_SUPPORT_ERROR.
   Only mz_strm_mem is used for in-RAM ZIP access.

   SPDX-License-Identifier: Zlib
*/
#ifndef MZ_STREAM_OS_H
#define MZ_STREAM_OS_H

#include "mz.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Returns NULL always — OS file I/O not supported on embedded target */
static inline void *mz_stream_os_create(void) { return NULL; }
static inline void  mz_stream_os_delete(void **stream) { if (stream) *stream = NULL; }

#ifdef __cplusplus
}
#endif

#endif /* MZ_STREAM_OS_H */
