#ifndef __CSP_FLASH_H__
#define __CSP_FLASH_H__

#ifdef __cplusplus
extern "C"{
#endif


void __csp_ssp_flash_Init(void);

void __csp_ssp_flash_dma_Init(void);

void __csp_ssp_flash_eraseBlock32k(uint32_t addr);
void __csp_ssp_flash_eraseBlock64k(uint32_t addr);
void __csp_ssp_flash_eraseSector(uint32_t addr);
void __csp_ssp_flash_eraseChip(void);

void __csp_ssp_flash_readJedec(uint32_t * Jedec);

void __csp_ssp_flash_write(uint32_t addr, uint8_t * data, uint32_t length);
void __csp_ssp_flash_read(uint32_t addr, uint8_t * data, uint32_t length);

void __csp_ssp_flash_dma_read(uint32_t addr, uint8_t * data, uint32_t length);


#ifdef __cplusplus
}
#endif

#endif

