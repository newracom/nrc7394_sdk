#ifndef __HAL_SFC_H__
#define __HAL_SFC_H__

void hal_sfc_init();
void hal_sfc_deinit();
void hal_sfc_ps();
void hal_sfc_reinit();

void hal_sfc_write(uint32_t offset, uint8_t* source, uint32_t size);
uint32_t hal_sfc_read(uint32_t offset, uint8_t *rbuffer, uint32_t size);
void hal_sfc_erase(uint32_t address, uint32_t size);
void hal_sfc_erase_all();
uint32_t hal_sfc_get_size();
uint32_t hal_sfc_get_jedecid();
void hal_sfc_power_down(bool enable);

#endif /*__HAL_SFLASH_H__*/
