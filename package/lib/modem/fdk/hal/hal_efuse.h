#ifndef __HAL_EFUSE_H__
#define __HAL_EFUSE_H__

void hal_efuse_init();
void hal_efuse_deinit();
void hal_efuse_ps();
void hal_efuse_reinit();
uint32_t hal_efuse_read(uint32_t offset, uint32_t *rbuffer);

#endif /*__HAL_EFUSE_H__*/
