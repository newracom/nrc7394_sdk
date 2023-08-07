#ifndef __HAL_GDMA_NRC7392_H__
#define __HAL_GDMA_NRC7392_H__

#include "system.h"


//======================================================================================================================
// GDMA
//======================================================================================================================
#define DMA_BASE_ADDR (0x40091000)

#define DMA_CH_MAX (8)

#define RegDMA_INT_STATUS       (*((volatile uint32_t *)(DMA_BASE_ADDR + 0x00)))
#define RegDMA_INT_TCSTATUS     (*((volatile uint32_t *)(DMA_BASE_ADDR + 0x04)))
#define RegDMA_INT_TCCLR        (*((volatile uint32_t *)(DMA_BASE_ADDR + 0x08)))
#define RegDMA_INT_ERRSTATUS    (*((volatile uint32_t *)(DMA_BASE_ADDR + 0x0C)))
#define RegDMA_INT_ERRCLR       (*((volatile uint32_t *)(DMA_BASE_ADDR + 0x10)))
#define RegDMA_RAW_TCSTATUS     (*((volatile uint32_t *)(DMA_BASE_ADDR + 0x14)))
#define RegDMA_RAW_ERRTATUS     (*((volatile uint32_t *)(DMA_BASE_ADDR + 0x18)))
#define RegDMA_ENABLED_CH       (*((volatile uint32_t *)(DMA_BASE_ADDR + 0x1C)))
#define RegDMA_SOFTB_REQ        (*((volatile uint32_t *)(DMA_BASE_ADDR + 0x20)))
#define RegDMA_SOFTS_REQ        (*((volatile uint32_t *)(DMA_BASE_ADDR + 0x24)))
#define RegDMA_SOFTLB_REQ       (*((volatile uint32_t *)(DMA_BASE_ADDR + 0x28)))
#define RegDMA_SOFTLS_REQ       (*((volatile uint32_t *)(DMA_BASE_ADDR + 0x2C)))
#define RegDMA_CONFIG           (*((volatile uint32_t *)(DMA_BASE_ADDR + 0x30)))
#define RegDMA_SYNC             (*((volatile uint32_t *)(DMA_BASE_ADDR + 0x34)))

#define RegDMA_CH(x)            (*((volatile uint32_t *)(DMA_BASE_ADDR + 0x100 + 0x20*x)))

#define DMA_BURST1  (0)
#define DMA_BURST4  (1)
#define DMA_BURST8  (2)
#define DMA_BURST16 (3)
#define DMA_BURST32 (4)
#define DMA_BURST64 (5)
#define DMA_BURST128 (6)
#define DMA_BURST256 (7)


#define DMA_WIDTH1  (0)
#define DMA_WIDTH2  (1)
#define DMA_WIDTH4  (2)


#define DMA_MEM2MEM             (0)
#define DMA_MEM2PERI            (1)
#define DMA_PERI2MEM            (2)
#define DMA_SRCPERI2DSTPERI     (3)
#define DPERI_SRCPERI2DSTPERI   (4)
#define PERI_MEM2PERI           (5)
#define PERI_PERI2MEM           (6)
#define SPERI_SRCPERI2DSTPERI   (7)

#define SSP0_DMA_SREQ_RX (0)
#define SSP0_DMA_SREQ_TX (1)
#define SSP1_DMA_SREQ_RX (2)
#define SSP1_DMA_SREQ_TX (3)
#define HSUART0_DMA_SREQ_RX (4)
#define HSUART0_DMA_SREQ_TX (5)
#define HSUART1_DMA_SREQ_RX (6)
#define HSUART1_DMA_SREQ_TX (7)

typedef union {
	struct {
		uint32_t ch0 : 1;
		uint32_t ch1 : 1;
		uint32_t ch2 : 1;
		uint32_t ch3 : 1;
		uint32_t ch4 : 1;
		uint32_t ch5 : 1;
		uint32_t ch6 : 1;
		uint32_t ch7 : 1;
		uint32_t reserved : 24;
	} bit;
	uint32_t word;
} dma_channel_t;

typedef union {
	struct {
		uint32_t req0 : 1;
		uint32_t req1 : 1;
		uint32_t req2 : 1;
		uint32_t req3 : 1;
		uint32_t req4 : 1;
		uint32_t req5 : 1;
		uint32_t req6 : 1;
		uint32_t req7 : 1;
		uint32_t req8 : 1;
		uint32_t req9 : 1;
		uint32_t req10 : 1;
		uint32_t req11 : 1;
		uint32_t req12 : 1;
		uint32_t req13 : 1;
		uint32_t req14 : 1;
		uint32_t req15 : 1;
		uint32_t reserved : 16;
	} bit;
	uint32_t word;
} dma_request_t;

typedef union {
	struct {
		uint32_t enable  : 1;
		uint32_t master1 : 1;
		uint32_t master2 : 1;
		uint32_t reserved : 29;
	} bit;
	uint32_t word;
} dma_configuration_t;


typedef union {
	struct {
		uint32_t master : 1;
		uint32_t reserved : 1;
		uint32_t address  : 30;
	} bit;
	uint32_t word;
} dma_lli_t;

typedef union {
	struct {

		uint32_t transfer_size  : 12;
		uint32_t src_burst      : 3;
		uint32_t dst_burst      : 3;
		uint32_t src_width      : 3;
		uint32_t dst_width      : 3;
		uint32_t src_master     : 1;
		uint32_t dst_master     : 1;
		uint32_t src_inc        : 1;
		uint32_t dst_inc        : 1;
		uint32_t priviledged    : 1;
		uint32_t bufferable     : 1;
		uint32_t cacheable      : 1;
		uint32_t tc_int_enable  : 1;
	} bit;
	uint32_t word;
} dma_channel_control_t;

typedef union {
	struct {
		uint32_t enable     : 1;
		uint32_t src_peri   : 4;
		uint32_t reserved1  : 1;
		uint32_t dst_peri   : 4;
		uint32_t reserved2  : 1;
		uint32_t flow_control   : 3;
		uint32_t int_error_mask : 1;
		uint32_t int_tc_mask    : 1;
		uint32_t lock   : 1;
		uint32_t active : 1;
		uint32_t halt   : 1;
		uint32_t reserved3  : 13;
	} bit;
	uint32_t word;
} dma_channel_config_t;


typedef struct {
	volatile dma_channel_t int_status;
	volatile dma_channel_t int_tc_status;
	volatile dma_channel_t int_tc_clear;
	volatile dma_channel_t int_error_status;
	volatile dma_channel_t int_error_clear;
	volatile dma_channel_t raw_tc_status;
	volatile dma_channel_t raw_error_status;
	volatile dma_channel_t enabled_channel;
	volatile dma_request_t sw_burst_request;
	volatile dma_request_t sw_single_request;
	volatile dma_request_t sw_last_burst_request;
	volatile dma_request_t sw_last_single_request;
	volatile dma_configuration_t config;
	volatile dma_request_t synchronization;
} dma_controller;


typedef struct {
	volatile uint32_t src;
	volatile uint32_t dst;
	volatile dma_lli_t lli;
	volatile dma_channel_control_t control;
	volatile dma_channel_config_t config;
} dma_channel;



enum gdma_flow_e {
	GF_MEM2MEM,
	GF_MEM2PERI,
	GF_PERI2MEM,
};


enum gdma_width_e {
	GW_BYTE,
	GW_HALFWORD,
	GW_WORD,
};

enum {
	GT_SSP0_RX = 0,
	GT_SSP0_TX = 1,
	GT_SSP1_RX = 2,
	GT_SSP1_TX = 3,
	GT_HSUART0_RX = 4,
	GT_HSUART0_TX = 5,
	GT_HSUART1_RX = 6,
	GT_HSUART1_TX = 7,
	GT_MEM_TX = 8,
	GT_MEM_RX = 9,
	GT_PERI_MAX
};

void nrc_gdma_init(void);
void nrc_gdma_deinit(void);
void nrc_gdma_single(int channel_index, void *dst, void *src, size_t len,
		int id, enum gdma_flow_e flow, int dst_inc, int src_inc, enum gdma_width_e width);
void nrc_gdma_setup(volatile dma_channel *ch, void *dst, void *src, size_t len,
		int id, enum gdma_flow_e flow, int dst_inc, int src_inc, enum gdma_width_e width, bool interrupt);
//int id, enum gdma_flow_e flow, int dst_inc, int src_inc, enum gdma_width_e width, bool interrupt = true);
bool nrc_gdma_busy_ch(volatile dma_channel *ch);
bool nrc_gdma_busy_idx(int channel_index);
bool nrc_gdma_start_ch(volatile dma_channel *ch);
bool nrc_gdma_start_idx(int channel_index);
bool nrc_gdma_stop_ch(volatile dma_channel *ch);
bool nrc_gdma_stop_idx(int channel_index);
void nrc_gdma_lli(volatile dma_channel **listch);
dma_channel *nrc_gdma_get_channel(int channel_index);

void nrc_gdma_chint(volatile dma_channel *ch, bool interrupt);
void nrc_gdma_int_clear(int channel_index);
uint32_t nrc_gdma_int_status(void);
uint32_t nrc_gdma_int_tcstatus(void);
uint32_t nrc_gdma_int_errstatus(void);
void nrc_gdma_show(void);
void nrc_gdma_ch_show(int channel_index);
void nrc_gdma_test(void);


#endif //__HAL_GDMA_NRC7392_H__
