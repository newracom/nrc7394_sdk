#ifndef __SYSTEM_EEPROM_H__
#define __SYSTEM_EEPROM_H__

#ifdef __cplusplus
extern "C"{
#endif

typedef struct {
	uint32_t signature; /*'nrct'*/
	uint32_t crc32; /*computed by util_crc_compute_crc32() in util_crc.c*/
	uint32_t length; /*actual data length*/
} eeprom_slot_t;

void system_eeprom_init(void);
void system_eeprom_deinit(void);
int system_eeprom_read(uint32_t addr, uint8_t *rbuffer, uint16_t length);
int system_eeprom_write(uint32_t addr, uint8_t *wbuffer, uint16_t length);
int system_eeprom_clear_data(uint32_t addr, uint16_t length);
void system_eeprom_set_config(uint8_t channel, uint8_t scl, uint8_t sda, uint32_t clk,
	uint16_t dev_addr, int wp_pin, uint8_t write_page_size);
bool system_eeprom_check_slot_sig(uint32_t* signature);
bool system_eeprom_read_slot_info(uint32_t address, eeprom_slot_t *data);
void system_eeprom_set_slot_sig(uint32_t* signature);
bool system_eeprom_read_slot_data(uint32_t address, int size, uint8_t *buffer);
bool system_eeprom_update_slot(uint32_t address, uint8_t *data, int size);
bool system_eeprom_get_sector_data(uint32_t address, uint8_t *buffer, int size);

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_EEPROM_H__ */
