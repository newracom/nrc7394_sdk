#ifndef __HAL_PMSSPI_H__
#define __HAL_PMSSPI_H__

void hal_pmsspi_init();
void hal_pmsspi_deinit();
void hal_pmsspi_ps();
void hal_pmsspi_reinit();
uint32_t hal_pmsspi_read(uint32_t offset, uint32_t *rbuffer);
uint32_t hal_pmsspi_write(uint32_t offset, uint32_t *wbuffer);

#endif /*__HAL_PMSSPI_H__*/
