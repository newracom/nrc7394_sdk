#ifndef __SYSTEM_PMSSPI_H__
#define __SYSTEM_PMSSPI_H__

#ifdef __cplusplus
extern "C"{
#endif

void system_pmsspi_init(void);
uint32_t system_pmsspi_read(uint32_t offset, uint32_t *rbuffer);
uint32_t system_pmsspi_write(uint32_t offset, uint32_t *wbuffer);
#endif
