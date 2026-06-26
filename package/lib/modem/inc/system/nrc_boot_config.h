#ifndef __NRC_BOOT_CONFIG_H__
#define __NRC_BOOT_CONFIG_H__

#include <stdint.h>
#include <stdbool.h>

typedef struct {
	uint8_t  wdt_disable;
	uint8_t  crc_check_skip;
	uint8_t  jlink_enable;
	uint8_t resolved;
} nrc_boot_cfg_t;

bool nrc_read_boot_config(nrc_boot_cfg_t *out);

#endif /* __NRC_BOOT_CONFIG_H__ */