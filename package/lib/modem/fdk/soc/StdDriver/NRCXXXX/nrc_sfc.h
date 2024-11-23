#ifndef __NRC_SFC_H__
#define __NRC_SFC_H__

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_type.h"

__RAM_FUNC void nrc_sfc_write_pgm(struct drv_sfc_t *sfc, uint32_t addr, uint8_t *buf, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif
