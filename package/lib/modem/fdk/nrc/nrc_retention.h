#ifndef __NRC_RETENTION_H__
#define __NRC_RETENTION_H__

#include "system.h"
#include "hal.h"
#include "nrc.h"

#define CONFIG_NRC_RETENTION_MAXSLOT        8

typedef struct {
    uint32_t variable_address;
    uint16_t ret_address_offset;
    uint16_t ret_size;
} nrc_ret_info_slot_t;

typedef struct {
	uint32_t sign;
	uint32_t address;
	uint32_t size;
	uint32_t crc32;
} nrc_ucode_header_t;

typedef struct {
    uint32_t                total_size;
    uint32_t                total_empty_size;
    uint32_t                used_size;
    uint32_t                used_slot;
    nrc_ret_info_slot_t     ret_slot[CONFIG_NRC_RETENTION_MAXSLOT];
    /*--------------------------------*/
    hal_modem_ret_info_t    hal_modem_ret_info;
    nrc_config_info_t       nrc_config_info;
    /*--------------------------------*/
    uint32_t                ret_start_address[0];
} nrc_ret_info_t;

extern nrc_ret_info_t *nrc_ret_info;

/*--------------------*/
/*  Retention Memory  */
/*--------------------*/
/* nrc_ret_info_t     */
/* user               */
/* nrc_ucode_header_t */
/*--------------------*/


void nrc_retention_init();
bool nrc_retention_register(void* address, uint16_t size);

#endif