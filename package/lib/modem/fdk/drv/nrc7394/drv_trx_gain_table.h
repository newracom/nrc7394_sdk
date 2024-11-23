#ifndef __DRV_TRX_GAIN_TABLE_H__
#define __DRV_TRX_GAIN_TABLE_H__
#include "system.h"

#define TX_GAIN_TABLE_MAX 47
#define TX_GAIN_TABLE_SIZE	47
#define RX_GAIN_TABLE_MAX 128
#define RX_GAIN_TABLE_SIZE 103

extern const uint16_t	tx_gain_table[TX_GAIN_TABLE_SIZE];
extern       uint16_t   rx_gain_table[RX_GAIN_TABLE_SIZE];

#endif