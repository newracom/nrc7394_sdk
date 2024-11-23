#ifndef __DRV_TRX_GAIN_TABLE_H__
#define __DRV_TRX_GAIN_TABLE_H__
#include "system.h"

#define TX_GAIN_TABLE_MAX 50
#define TX_GAIN_TABLE_SIZE	32

#define RX_GAIN_TABLE_MAX 128
#define RX_GAIN_TABLE_SIZE 128

#define SBR_TX_TABLE_SIZE 96

extern const uint16_t tx_gain_table[TX_GAIN_TABLE_SIZE];
extern const uint16_t rx_gain_table[RX_GAIN_TABLE_SIZE];
extern const uint32_t sbr_tx_2m[SBR_TX_TABLE_SIZE];
extern const uint32_t sbr_tx_1m[SBR_TX_TABLE_SIZE];

#endif
