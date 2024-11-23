#ifndef __API_SFLASH_H__
#define __API_SFLASH_H__

void		api_sflash_write(uint32_t offset, uint8_t* source, uint32_t size);
uint32_t	api_sflash_read(uint32_t offset, uint8_t *rbuffer, uint32_t size);
void		api_sflash_erase(uint32_t address, uint32_t size);

#endif //__API_SFLASH_H__
