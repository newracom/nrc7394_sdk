#ifndef __HAL_SSP_NRC7392_H__
#define __HAL_SSP_NRC7392_H__

#include "system.h"

enum spi_mode_e {
	SPI_SLAVE = 0,
	SPI_MASTER = 1
};

enum spi_cpol_e {
	CPOL_LO = 0,
	CPOL_HI = 1
};

enum spi_cpha_e {
	CPHA_LO = 0,
	CPHA_HI = 1
};

enum spi_order_e {
	SPI_LSB = 0,
	SPI_MSB = 1
};

typedef union {
	struct {
		uint32_t dss : 4; 	/* Data Size Select */
		uint32_t frf : 2;	/* Frame Format */
		uint32_t spo : 1;	/* SSPCLKOUT Polarity */
		uint32_t sph : 1;	/* SSPCLKOUT Phase */
		uint32_t scr : 8;	/* Serial Clock Rate */
		uint32_t reserved : 16;
	} bit;
	uint32_t word;
} ssp_cr0_t;

typedef union {
	struct {
		uint32_t lbm : 1; 	/* Loop Back Mode */
		uint32_t sse : 1;	/* Synchronous Serial Port Enable */
		uint32_t ms  : 1;	/* Master Or Slave Mode Select */
		uint32_t sod : 1;	/* Slave Mode Output Disable */
		uint32_t reserved : 28;
	} bit;
	uint32_t word;
} ssp_cr1_t;

typedef union {
	struct {
		uint32_t data : 16;
		uint32_t reserved : 16;
	} bit;
	uint32_t word;
} ssp_dr_t;

typedef union {
	struct {
		uint32_t tfe : 1; 	/* Transmit FIFO Empty */
		uint32_t tnf : 1; 	/* Transmit FIFO Not Full */
		uint32_t rne : 1; 	/* Receive FIFO not Empty */
		uint32_t rff : 1; 	/* Receive FIFO Full */
		uint32_t bsy : 1; 	/* Busy Flag */
		uint32_t reserved : 27;
	} bit;
	uint32_t word;
} ssp_sr_t;

typedef union {
	struct {
		uint32_t cpsdvsr : 8; 	/* Clock Prescale Divisor */
		uint32_t reserved : 24;
	} bit;
	uint32_t word;
} ssp_cpsr_t;


typedef union {
	struct {
		uint32_t rorim : 1; 	/* Receive Overrun Interrupt Mask */
		uint32_t rtim : 1; 		/* Receive Timeout Interrupt Mask */
		uint32_t rxim : 1; 		/* Receive FIFO Interrupt Mask */
		uint32_t txim : 1; 		/* Transmit FIFO Interrupt Mask */
		uint32_t reserved : 28;
	} bit;
	uint32_t word;
} ssp_imsc_t;

typedef union {
	struct {
		uint32_t rorris: 1; 		/* Gives the raw interrupt state (prior to masking) of the SSPTXINTR interrupt */
		uint32_t rtris : 1; 		/* Gives the raw interrupt state (prior to masking) of the SSPRXINTR interrupt */
		uint32_t rxris : 1; 		/* Gives the raw interrupt state (prior to masking) of the SSPRTINTR interrupt */
		uint32_t txris : 1; 		/* Gives the raw interrupt state (prior to masking) of the SSPRORINTR interrupt */
		uint32_t reserved : 28;
	} bit;
	uint32_t word;
} ssp_ris_t;

typedef union {
	struct {
		uint32_t rormis: 1; 		/* Gives the receive over run masked interrupt status (after masking) of the SSPRORINTR interrupt */
		uint32_t rtmis : 1; 		/* Gives the receive timeout masked interrupt state (after masking) of the SSPRTINTR interrupt */
		uint32_t rxmis : 1; 		/* Gives the receive FIFO masked interrupt state (after masking) of the SSPRXINTR interrupt */
		uint32_t txmis : 1; 		/* Gives the transmit FIFO masked interrupt state (after masking) of the SSPTXINTR interrupt  */
		uint32_t reserved : 28;
	} bit;
	uint32_t word;
} ssp_mis_t;

typedef union {
	struct {
		uint32_t roric: 1; 		/*  Clears the SSPRORINTR interrupt */
		uint32_t rtic : 1; 		/*  Clears the SSPRTINTR interrupt */
		uint32_t reserved : 30;
	} bit;
	uint32_t word;
} ssp_icr_t;

typedef union {
	struct {
		uint32_t rxdmae: 1; 		/*  RX DMA Enable */
		uint32_t txdmae : 1; 		/*  TX DMA Enable */
		uint32_t reserved : 30;
	} bit;
	uint32_t word;
} ssp_dmacr_t;

typedef struct {
	volatile ssp_cr0_t cr0;
	volatile ssp_cr1_t cr1;
	volatile ssp_dr_t dr;
	volatile ssp_sr_t sr;
	volatile ssp_cpsr_t cpsr;
	volatile ssp_imsc_t imsc;
	volatile ssp_ris_t ris;
	volatile ssp_mis_t mis;
	volatile ssp_icr_t icr;
	volatile ssp_dmacr_t dmacr;
} ssp_controller_t;

bool nrc_ssp_init(uint8_t ch, enum spi_cpol_e cpol, enum spi_cpha_e cpha, enum spi_order_e order, uint8_t bits, uint32_t freq_hz);
void nrc_ssp(uint8_t ch, bool enable);
void nrc_ssp_deinit(uint8_t ch);
uint32_t nrc_ssp_xfer(uint8_t ch, uint8_t *wbuffer, uint8_t *rbuffer, size_t size);
void nrc_ssp_dma(uint8_t ch, uint32_t id, bool enable);
uint32_t nrc_ssp_int_status(uint8_t ch);
void nrc_ssp_int(uint8_t ch, uint32_t id, bool enable);
void nrc_ssp_int_clr(uint8_t ch, uint32_t id);
void nrc_ssp_lb(uint8_t ch, bool enable);
bool nrc_ssp_rx_filled(uint8_t ch);
bool nrc_ssp_rx_fulled(uint8_t ch);
bool nrc_ssp_tx_fulled(uint8_t ch);
bool nrc_ssp_tx_empty(uint8_t ch);
uint8_t nrc_ssp_rx(uint8_t ch);
void nrc_ssp_tx(uint8_t ch, uint8_t data);
void nrc_ssp_flush(uint8_t ch);
void nrc_ssp_test_xfer();
void nrc_ssp_show();

#endif //__HAL_SSP_NRC7392_H__
