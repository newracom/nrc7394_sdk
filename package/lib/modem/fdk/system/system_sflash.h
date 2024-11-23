#ifndef __SYSTEM_SFLASH_H__
#define __SYSTEM_SFLASH_H__

#define SFC_MEM_BASE_ADDR (0x11000000)
#define SF_MEM_MAP 0xF000

#define SF_SYSTEM_CONFIG 		system_sflash_get_sysconfig_address()
#define SF_RF_CAL				system_sflash_get_rf_cal_address()
#define SF_CORE_DUMP			system_sflash_get_core_dump_address()
#define SF_FOTA					system_sflash_get_fota_address()
#define SF_FOTA_INFO			system_sflash_get_fota_info_address()
#define SF_FW					system_sflash_get_fw_address()
#define SF_FW_INFO				system_sflash_get_fw_info_address()

typedef struct {
	uint32_t MAP_VERSION;
	uint32_t FW;
	uint32_t FW_INFO;
	uint32_t CORE_DUMP;
	uint32_t USER_CONFIG_1;
	uint32_t USER_CONFIG_2;
	uint32_t USER_CONFIG_3;
	uint32_t USER_CONFIG_4;
	uint32_t SYS_CONFIG;
	uint32_t RF_CAL;
	uint32_t FOTA;
	uint32_t DEVICE_INFO;
	uint32_t USER_DATA;
	uint32_t FOTA_INFO;
} sf_mem_map_t;

enum sf_store_area_e {
	SF_BOOTLOADER_4MB = 0x0,
	SF_FW_4MB = 0x10000,
	SF_USER_DATA_4MB = 0x3DA000,/*100KB*/
	SF_FW_INFO_4MB = 0x3FE000,
	SF_CORE_DUMP_4MB = 0x3F3000,
	SF_USER_CONFIG_1_4MB = 0x3F7000,/*4KB*/
	SF_USER_CONFIG_2_4MB = 0x3F8000,/*4KB*/
	SF_USER_CONFIG_3_4MB = 0x3F9000,/*4KB*/
	SF_USER_CONFIG_4_4MB = 0x3FA000,/*4KB*/
	SF_DEVICE_INFO_4MB = 0x3FB000,/*4KB*/
	SF_SYSTEM_CONFIG_4MB = 0x3FC000,
	SF_RF_CAL_4MB = 0x3FD000,
	SF_FOTA_4MB = 0x1F5000,
	SF_FOTA_INFO_4MB = 0x3FF000,
	SF_BOOTLOADER_2MB = 0x0,
	SF_FW_2MB = 0x10000,
	SF_FW_INFO_2MB = 0xF5000,
	SF_CORE_DUMP_2MB = 0xF6000,
	SF_USER_CONFIG_1_2MB = 0xFA000,
	SF_USER_CONFIG_2_2MB = 0xFB000,
	SF_USER_CONFIG_3_2MB = 0xFC000,
	SF_USER_CONFIG_4_2MB = 0xFD000,
	SF_SYSTEM_CONFIG_2MB = 0xFE000,
	SF_MAC_ADDR_2MB = 0xFE000,
	SF_MAC_ADDR_MC_2MB = 0xFE008,
	SF_RF_CAL_2MB = 0xFF000,
	SF_FOTA_2MB = 0x100000,
	SF_DEVICE_INFO_2MB = 0x1E5000,
	SF_USER_DATA_2MB = 0x1E6000,
	SF_FOTA_INFO_2MB = 0x1FF000
};

#define SF_SECTOR_SIZE            4096

#define SF_SLOT_DATA_OFFSET 12
#define SF_SLOT_CRC_OFFSET 8
#define SF_SLOT_MAX_LEN 4084 /* 4KB - size of Header */

#define SIZE_OF_TX_PWR_TBL      64
#define SIZE_OF_FREQ_DELTA_TBL  64
typedef struct {
	uint32_t signature; /*'nrct'*/
	uint32_t crc32; /*computed by util_crc_compute_crc32() in util_crc.c*/
	uint32_t length; /*actual data length*/
} sf_slot_t;

typedef struct {
	uint32_t fw_size;
	uint32_t fw_crc;
} sf_fw_info_t;

#define SYS_CONFIG_STRUCTURE_VERSION 2
struct sf_reg_override {
	uint32_t control;
	uint32_t value;
};

__attribute__((section(".sfc_ready"))) void system_sflash_ready(void);
void system_sflash_init(void);
//__RAM_FUNC void system_sflash_init(void);

void		system_sflash_init_memory_map(void);
uint32_t 	system_sflash_get_sysconfig_address(void);
uint32_t 	system_sflash_get_rf_cal_address(void);
uint32_t	system_sflash_get_core_dump_address(void);
uint32_t	system_sflash_get_fota_address(void);
uint32_t	system_sflash_get_fota_info_address(void);
uint32_t	system_sflash_get_fw_address(void);
uint32_t	system_sflash_get_fw_info_address(void);
void 		system_sflash_set_slot_sig(uint32_t* signature);
bool 		system_sflash_check_slot_sig(uint32_t* signature);
bool 		system_sflash_update_slot(uint32_t address, uint8_t *data, size_t size);
bool 		system_sflash_read_slot_info(uint32_t address, sf_slot_t *data);
bool 		system_sflash_read_slot_data(uint32_t address, size_t size, uint8_t *buffer);
bool 		system_sflash_get_flash_sector_data(uint32_t address, uint8_t *buffer, size_t size);
uint16_t	system_sflash_get_hw_version(void);
void		system_sflash_update_hw_version(uint32_t version);
void		system_sflash_update_cal_use(uint8_t cal_use);
bool		system_sflash_get_macaddr(uint8_t* mac, int vif_id);
uint32_t	system_sflash_get_size(void);
bool		system_sflash_fota_support(void);
uint32_t	system_sflash_fota_max_fw_size(void);
void		system_sflash_power_down(bool enable);
uint32_t	system_sflash_get_user_data_area_size(void);
bool		system_sflash_write_user_data(uint32_t user_data_offset, uint8_t* data, uint32_t size);
bool		system_sflash_read_user_data(uint8_t* data, uint32_t user_data_offset, uint32_t size);

bool		system_sflash_write_device_info(uint8_t* data, uint16_t size);
bool		system_sflash_read_device_info(uint8_t* data, uint16_t size);
#endif
