#pragma once

#define APM_PSRAM_REG_READ         0x03
#define APM_PSRAM_REG_FAST_READ    0x0B
#define APM_PSRAM_REG_WRITE        0x02
#define APM_PSRAM_REG_RESET_ENABLE 0x66
#define APM_PSRAM_REG_RESET        0x99
#define APM_PSRAM_REG_WRAP_TOGGLE  0xC0
#define APM_PSRAM_REG_READ_ID      0x9F

int psram_init();
bool psram_read_id();
int psram_read(uint32_t addr, uint8_t *buffer, uint32_t size);
int psram_write(uint32_t addr, uint8_t *buffer, uint32_t size);
