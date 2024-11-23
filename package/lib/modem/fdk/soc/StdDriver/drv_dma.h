#ifndef __DRV_DMA_H__
#define __DRV_DMA_H__

#ifdef __cplusplus
extern "C"{
#endif

#define DRV_DMA_IOCTL_OPT_GET											0
#define DRV_DMA_IOCTL_OPT_STARTUP										1
#define DRV_DMA_IOCTL_OPT_SHUTDOWN										2
#define DRV_DMA_IOCTL_OPT_REGISTER_IRQ_HANDLER							3
#define DRV_DMA_IOCTL_OPT_REGISTER_ERR_IRQ_HANDLER						4

#define DRV_DMA_IOCTL_OPT_GET_CH0										10
#define DRV_DMA_IOCTL_OPT_GET_CH1										11
#define DRV_DMA_IOCTL_OPT_GET_CH2										12
#define DRV_DMA_IOCTL_OPT_GET_CH3										13
#define DRV_DMA_IOCTL_OPT_GET_CH4										14
#define DRV_DMA_IOCTL_OPT_GET_CH5										15
#define DRV_DMA_IOCTL_OPT_GET_CH6										16
#define DRV_DMA_IOCTL_OPT_GET_CH7										17
	
#define DRV_DMA_IOCTL_OPT_TC_IRQ_CTRL_CH0								100
#define DRV_DMA_IOCTL_OPT_TC_IRQ_CTRL_CH1								101
#define DRV_DMA_IOCTL_OPT_TC_IRQ_CTRL_CH2								102
#define DRV_DMA_IOCTL_OPT_TC_IRQ_CTRL_CH3								103
#define DRV_DMA_IOCTL_OPT_TC_IRQ_CTRL_CH4								104
#define DRV_DMA_IOCTL_OPT_TC_IRQ_CTRL_CH5								105
#define DRV_DMA_IOCTL_OPT_TC_IRQ_CTRL_CH6								106
#define DRV_DMA_IOCTL_OPT_TC_IRQ_CTRL_CH7								107

#define DRV_DMA_IOCTL_OPT_TC_IRQ_RESET_CH0								110
#define DRV_DMA_IOCTL_OPT_TC_IRQ_RESET_CH1								111
#define DRV_DMA_IOCTL_OPT_TC_IRQ_RESET_CH2								112
#define DRV_DMA_IOCTL_OPT_TC_IRQ_RESET_CH3								113
#define DRV_DMA_IOCTL_OPT_TC_IRQ_RESET_CH4								114
#define DRV_DMA_IOCTL_OPT_TC_IRQ_RESET_CH5								115
#define DRV_DMA_IOCTL_OPT_TC_IRQ_RESET_CH6								116
#define DRV_DMA_IOCTL_OPT_TC_IRQ_RESET_CH7								117

#define DRV_DMA_IOCTL_OPT_ERR_IRQ_MASK_CH0								120
#define DRV_DMA_IOCTL_OPT_ERR_IRQ_MASK_CH1								121
#define DRV_DMA_IOCTL_OPT_ERR_IRQ_MASK_CH2								122
#define DRV_DMA_IOCTL_OPT_ERR_IRQ_MASK_CH3								123
#define DRV_DMA_IOCTL_OPT_ERR_IRQ_MASK_CH4								124
#define DRV_DMA_IOCTL_OPT_ERR_IRQ_MASK_CH5								125
#define DRV_DMA_IOCTL_OPT_ERR_IRQ_MASK_CH6								126
#define DRV_DMA_IOCTL_OPT_ERR_IRQ_MASK_CH7								127

#define DRV_DMA_IOCTL_OPT_ERR_IRQ_RESET_CH0								130
#define DRV_DMA_IOCTL_OPT_ERR_IRQ_RESET_CH1								131
#define DRV_DMA_IOCTL_OPT_ERR_IRQ_RESET_CH2								132
#define DRV_DMA_IOCTL_OPT_ERR_IRQ_RESET_CH3								133
#define DRV_DMA_IOCTL_OPT_ERR_IRQ_RESET_CH4								134
#define DRV_DMA_IOCTL_OPT_ERR_IRQ_RESET_CH5								135
#define DRV_DMA_IOCTL_OPT_ERR_IRQ_RESET_CH6								136
#define DRV_DMA_IOCTL_OPT_ERR_IRQ_RESET_CH7								137

#define DRV_DMA_IOCTL_OPT_BUS_CH0_SOURCE							140
#define DRV_DMA_IOCTL_OPT_BUS_CH1_SOURCE							141
#define DRV_DMA_IOCTL_OPT_BUS_CH2_SOURCE							142
#define DRV_DMA_IOCTL_OPT_BUS_CH3_SOURCE							143
#define DRV_DMA_IOCTL_OPT_BUS_CH4_SOURCE							144
#define DRV_DMA_IOCTL_OPT_BUS_CH5_SOURCE							145
#define DRV_DMA_IOCTL_OPT_BUS_CH6_SOURCE							146
#define DRV_DMA_IOCTL_OPT_BUS_CH7_SOURCE							147

#define DRV_DMA_IOCTL_OPT_BUS_CH0_DESTINATION						150
#define DRV_DMA_IOCTL_OPT_BUS_CH1_DESTINATION						151
#define DRV_DMA_IOCTL_OPT_BUS_CH2_DESTINATION						152
#define DRV_DMA_IOCTL_OPT_BUS_CH3_DESTINATION						153
#define DRV_DMA_IOCTL_OPT_BUS_CH4_DESTINATION						154
#define DRV_DMA_IOCTL_OPT_BUS_CH5_DESTINATION						155
#define DRV_DMA_IOCTL_OPT_BUS_CH6_DESTINATION						156
#define DRV_DMA_IOCTL_OPT_BUS_CH7_DESTINATION						157

#define DRV_DMA_IOCTL_OPT_DATA_SIZE_CH0_SOURCE							160
#define DRV_DMA_IOCTL_OPT_DATA_SIZE_CH1_SOURCE							161
#define DRV_DMA_IOCTL_OPT_DATA_SIZE_CH2_SOURCE							162
#define DRV_DMA_IOCTL_OPT_DATA_SIZE_CH3_SOURCE							163
#define DRV_DMA_IOCTL_OPT_DATA_SIZE_CH4_SOURCE							164
#define DRV_DMA_IOCTL_OPT_DATA_SIZE_CH5_SOURCE							165
#define DRV_DMA_IOCTL_OPT_DATA_SIZE_CH6_SOURCE							166
#define DRV_DMA_IOCTL_OPT_DATA_SIZE_CH7_SOURCE							167

#define DRV_DMA_IOCTL_OPT_DATA_SIZE_CH0_DESTINATION						170
#define DRV_DMA_IOCTL_OPT_DATA_SIZE_CH1_DESTINATION						171
#define DRV_DMA_IOCTL_OPT_DATA_SIZE_CH2_DESTINATION						172
#define DRV_DMA_IOCTL_OPT_DATA_SIZE_CH3_DESTINATION						173
#define DRV_DMA_IOCTL_OPT_DATA_SIZE_CH4_DESTINATION						174
#define DRV_DMA_IOCTL_OPT_DATA_SIZE_CH5_DESTINATION						175
#define DRV_DMA_IOCTL_OPT_DATA_SIZE_CH6_DESTINATION						176
#define DRV_DMA_IOCTL_OPT_DATA_SIZE_CH7_DESTINATION						177

#define DRV_DMA_IOCTL_OPT_TRANSFER_SIZE_CH0								180
#define DRV_DMA_IOCTL_OPT_TRANSFER_SIZE_CH1								181
#define DRV_DMA_IOCTL_OPT_TRANSFER_SIZE_CH2								182
#define DRV_DMA_IOCTL_OPT_TRANSFER_SIZE_CH3								183
#define DRV_DMA_IOCTL_OPT_TRANSFER_SIZE_CH4								184
#define DRV_DMA_IOCTL_OPT_TRANSFER_SIZE_CH5								185
#define DRV_DMA_IOCTL_OPT_TRANSFER_SIZE_CH6								186
#define DRV_DMA_IOCTL_OPT_TRANSFER_SIZE_CH7								187

#define DRV_DMA_IOCTL_OPT_ENABLE_CH0									190
#define DRV_DMA_IOCTL_OPT_ENABLE_CH1									191
#define DRV_DMA_IOCTL_OPT_ENABLE_CH2									192
#define DRV_DMA_IOCTL_OPT_ENABLE_CH3									193
#define DRV_DMA_IOCTL_OPT_ENABLE_CH4									194
#define DRV_DMA_IOCTL_OPT_ENABLE_CH5									195
#define DRV_DMA_IOCTL_OPT_ENABLE_CH6									196
#define DRV_DMA_IOCTL_OPT_ENABLE_CH7									197

#define DRV_DMA_IOCTL_OPT_INCREASE_CH0_DESTINATION						200
#define DRV_DMA_IOCTL_OPT_INCREASE_CH1_DESTINATION						201
#define DRV_DMA_IOCTL_OPT_INCREASE_CH2_DESTINATION						202
#define DRV_DMA_IOCTL_OPT_INCREASE_CH3_DESTINATION						203
#define DRV_DMA_IOCTL_OPT_INCREASE_CH4_DESTINATION						204
#define DRV_DMA_IOCTL_OPT_INCREASE_CH5_DESTINATION						205
#define DRV_DMA_IOCTL_OPT_INCREASE_CH6_DESTINATION						206
#define DRV_DMA_IOCTL_OPT_INCREASE_CH7_DESTINATION						207

#define DRV_DMA_IOCTL_OPT_INCREASE_CH0_SOURCE							220
#define DRV_DMA_IOCTL_OPT_INCREASE_CH1_SOURCE							221
#define DRV_DMA_IOCTL_OPT_INCREASE_CH2_SOURCE							222
#define DRV_DMA_IOCTL_OPT_INCREASE_CH3_SOURCE							223
#define DRV_DMA_IOCTL_OPT_INCREASE_CH4_SOURCE							224
#define DRV_DMA_IOCTL_OPT_INCREASE_CH5_SOURCE							225
#define DRV_DMA_IOCTL_OPT_INCREASE_CH6_SOURCE							226
#define DRV_DMA_IOCTL_OPT_INCREASE_CH7_SOURCE							227

#define DRV_DMA_IOCTL_OPT_ADDRESS_CH0_SOURCE							300
#define DRV_DMA_IOCTL_OPT_ADDRESS_CH1_SOURCE							301
#define DRV_DMA_IOCTL_OPT_ADDRESS_CH2_SOURCE							302
#define DRV_DMA_IOCTL_OPT_ADDRESS_CH3_SOURCE							303
#define DRV_DMA_IOCTL_OPT_ADDRESS_CH4_SOURCE							304
#define DRV_DMA_IOCTL_OPT_ADDRESS_CH5_SOURCE							305
#define DRV_DMA_IOCTL_OPT_ADDRESS_CH6_SOURCE							306
#define DRV_DMA_IOCTL_OPT_ADDRESS_CH7_SOURCE							307

#define DRV_DMA_IOCTL_OPT_ADDRESS_CH0_DESTINATION						310
#define DRV_DMA_IOCTL_OPT_ADDRESS_CH1_DESTINATION						311
#define DRV_DMA_IOCTL_OPT_ADDRESS_CH2_DESTINATION						312
#define DRV_DMA_IOCTL_OPT_ADDRESS_CH3_DESTINATION						313
#define DRV_DMA_IOCTL_OPT_ADDRESS_CH4_DESTINATION						314
#define DRV_DMA_IOCTL_OPT_ADDRESS_CH5_DESTINATION						315
#define DRV_DMA_IOCTL_OPT_ADDRESS_CH6_DESTINATION						316
#define DRV_DMA_IOCTL_OPT_ADDRESS_CH7_DESTINATION						317

#define DRV_DMA_IOCTL_OPT_PERI_CH0_SOURCE								400
#define DRV_DMA_IOCTL_OPT_PERI_CH1_SOURCE								401
#define DRV_DMA_IOCTL_OPT_PERI_CH2_SOURCE								402
#define DRV_DMA_IOCTL_OPT_PERI_CH3_SOURCE								403
#define DRV_DMA_IOCTL_OPT_PERI_CH4_SOURCE								404
#define DRV_DMA_IOCTL_OPT_PERI_CH5_SOURCE								405
#define DRV_DMA_IOCTL_OPT_PERI_CH6_SOURCE								406
#define DRV_DMA_IOCTL_OPT_PERI_CH7_SOURCE								407

#define DRV_DMA_IOCTL_OPT_PERI_CH0_DESTINATION							410
#define DRV_DMA_IOCTL_OPT_PERI_CH1_DESTINATION							411
#define DRV_DMA_IOCTL_OPT_PERI_CH2_DESTINATION							412
#define DRV_DMA_IOCTL_OPT_PERI_CH3_DESTINATION							413
#define DRV_DMA_IOCTL_OPT_PERI_CH4_DESTINATION							414
#define DRV_DMA_IOCTL_OPT_PERI_CH5_DESTINATION							415
#define DRV_DMA_IOCTL_OPT_PERI_CH6_DESTINATION							416
#define DRV_DMA_IOCTL_OPT_PERI_CH7_DESTINATION							417

#define DRV_DMA_IOCTL_OPT_FLOW_CONTROL_CH0								420
#define DRV_DMA_IOCTL_OPT_FLOW_CONTROL_CH1								421
#define DRV_DMA_IOCTL_OPT_FLOW_CONTROL_CH2								422
#define DRV_DMA_IOCTL_OPT_FLOW_CONTROL_CH3								423
#define DRV_DMA_IOCTL_OPT_FLOW_CONTROL_CH4								424
#define DRV_DMA_IOCTL_OPT_FLOW_CONTROL_CH5								425
#define DRV_DMA_IOCTL_OPT_FLOW_CONTROL_CH6								426
#define DRV_DMA_IOCTL_OPT_FLOW_CONTROL_CH7								427

#define DRV_DMA_IOCTL_OPT_NEXT_LINK_ADDR_CH0							430
#define DRV_DMA_IOCTL_OPT_NEXT_LINK_ADDR_CH1							431
#define DRV_DMA_IOCTL_OPT_NEXT_LINK_ADDR_CH2							432
#define DRV_DMA_IOCTL_OPT_NEXT_LINK_ADDR_CH3							433
#define DRV_DMA_IOCTL_OPT_NEXT_LINK_ADDR_CH4							434
#define DRV_DMA_IOCTL_OPT_NEXT_LINK_ADDR_CH5							435
#define DRV_DMA_IOCTL_OPT_NEXT_LINK_ADDR_CH6							436
#define DRV_DMA_IOCTL_OPT_NEXT_LINK_ADDR_CH7							437
/*******************************************************************************/
#define DRV_DMA_IOCTL_OPT_AHB_BUS_MASTER1									0
#define DRV_DMA_IOCTL_OPT_AHB_BUS_MASTER2									1

#define DRV_DMA_IOCTL_OPT_DATA_SIZE_8BIT									0
#define DRV_DMA_IOCTL_OPT_DATA_SIZE_16BIT									1
#define DRV_DMA_IOCTL_OPT_DATA_SIZE_32BIT									2

#define DRV_DMA_IOCTL_OPT_PERI_SPI0_RX										0
#define DRV_DMA_IOCTL_OPT_PERI_SPI0_TX										1
#define DRV_DMA_IOCTL_OPT_PERI_SPI1_RX										2
#define DRV_DMA_IOCTL_OPT_PERI_SPI1_TX										3
#define DRV_DMA_IOCTL_OPT_PERI_UART0_RX										4
#define DRV_DMA_IOCTL_OPT_PERI_UART0_TX										5
#define DRV_DMA_IOCTL_OPT_PERI_UART1_RX										6
#define DRV_DMA_IOCTL_OPT_PERI_UART1_TX										7

#define DRV_DMA_IOCTL_OPT_FLOW_CONTROL_MEM_TO_MEM 							0
#define DRV_DMA_IOCTL_OPT_FLOW_CONTROL_MEM_TO_PERI							1
#define DRV_DMA_IOCTL_OPT_FLOW_CONTROL_PERI_TO_MEM							2
#define DRV_DMA_IOCTL_OPT_FLOW_CONTROL_PERI_TO_PERI							3
#define DRV_DMA_IOCTL_OPT_FLOW_CONTROL_DST_PERI_CTRL_PERI_TO_PERI			4
#define DRV_DMA_IOCTL_OPT_FLOW_CONTROL_PERI_CTRL_MEM_TO_PERI				5
#define DRV_DMA_IOCTL_OPT_FLOW_CONTROL_PERI_CTRL_AND_PERI_TO_MEM			6
#define DRV_DMA_IOCTL_OPT_FLOW_CONTROL_SRC_PERI_CTRL_PERI_TO_PERI			7

#define DRV_DMA_IOCTL_OPT_ERR_IRQ_MASK_MASKED								0
#define DRV_DMA_IOCTL_OPT_ERR_IRQ_MASK_UNMASKED								1
/****************************************************************************/

enum drv_dma_id_t{
	drv_dma_id0,
	drv_dma_id_max,
};

enum drv_dma_ch_t{
	drv_dma_ch0,
	drv_dma_ch1,
	drv_dma_ch2,
	drv_dma_ch3,
	drv_dma_ch4,
	drv_dma_ch5,
	drv_dma_ch6,
	drv_dma_ch7,
	drv_dma_ch_max,
};

typedef struct DRV_DMA_HANDLE_T * drv_dma_handle_t;

struct drv_dma_t;
struct drv_dma_ops_t;
struct drv_dma_ioctl_t;

struct drv_dma_chstate_t{
	uint8_t enable;
	uint8_t irq_enable;
	uint8_t err_irq_mask;
	uint8_t dst_inc;
	uint8_t src_inc;
	uint8_t dst_bus;
	uint8_t src_bus;
	uint8_t flow_control;
	uint8_t dst_width;
	uint8_t src_width;
	uint8_t src_peri;
	uint8_t dst_peri;
	uint32_t transfer_size;
	uint32_t src_addr;
	uint32_t dst_addr;
	uint32_t lli;
};

union drv_dma_ioctl_flag_u{
	uint32_t w;
	struct{
		uint32_t irq_ch0				: 1;
		uint32_t irq_ch1				: 1;
		uint32_t irq_ch2				: 1;
		uint32_t irq_ch3				: 1;
		uint32_t irq_ch4				: 1;
		uint32_t irq_ch5			 	: 1;
		uint32_t irq_ch6		 		: 1;
		uint32_t irq_ch7		 		: 1;
		uint32_t err_irq_ch0			: 1;
		uint32_t err_irq_ch1			: 1;
		uint32_t err_irq_ch2			: 1;
		uint32_t err_irq_ch3			: 1;
		uint32_t err_irq_ch4			: 1;
		uint32_t err_irq_ch5			: 1;
		uint32_t err_irq_ch6		 	: 1;
		uint32_t err_irq_ch7		 	: 1;
	}b;
};

struct drv_dma_ioctl_t{
	uint32_t enable;
	struct drv_dma_chstate_t state[drv_dma_ch_max];
	union drv_dma_ioctl_flag_u flag;
};

struct DRV_DMA_HANDLE_T{
	enum drv_dma_id_t id;
	struct drv_dma_ioctl_t ioctl;
};


struct drv_dma_ops_t{
	int32_t (*close)(struct drv_dma_t *);
	int32_t (*startup)(struct drv_dma_t *);
	void (*shutdown)(struct drv_dma_t *);
	int32_t (*ioctl)(struct drv_dma_t *, uint32_t, unsigned int );
	void (*irq_enable)(struct drv_dma_t*, uint32_t, uint32_t);
	void (*err_irq_enable)(struct drv_dma_t*, uint32_t, uint32_t);
};

struct drv_dma_t{
	drv_dma_handle_t handle;
	const struct drv_dma_ops_t *ops;
	void (*handle_irq)(void);
	void (*err_handle_irq)(void);
};

/** 
  \brief		dma driver open function
  \details		
  \param [in]	id
  \param [in]	handle
  \return		ret
*/
int32_t drv_dma_open(enum drv_dma_id_t id, drv_dma_handle_t *handle);

/** 
  \brief		dma driver close function
  \details		
  \param [in]	handle
  \return		ret
*/
int32_t drv_dma_close( drv_dma_handle_t handle );

/** 
  \brief		dma driver input output control function
  \details		critical section
  \param [in]	handle
  \param [in]	opt This parameter can be one or multiple of the following values:
				@arg @ref  DRV_DMA_IOCTL_OPT_GET									
				@arg @ref  DRV_DMA_IOCTL_OPT_STARTUP								
				@arg @ref  DRV_DMA_IOCTL_OPT_SHUTDOWN								
				@arg @ref  DRV_DMA_IOCTL_OPT_REGISTER_IRQ_HANDLER					
				@arg @ref  DRV_DMA_IOCTL_OPT_REGISTER_ERR_IRQ_HANDLER				
				@arg @ref  DRV_DMA_IOCTL_OPT_GET_CH0								
				@arg @ref  DRV_DMA_IOCTL_OPT_GET_CH1								
				@arg @ref  DRV_DMA_IOCTL_OPT_GET_CH2								
				@arg @ref  DRV_DMA_IOCTL_OPT_GET_CH3								
				@arg @ref  DRV_DMA_IOCTL_OPT_GET_CH4								
				@arg @ref  DRV_DMA_IOCTL_OPT_GET_CH5								
				@arg @ref  DRV_DMA_IOCTL_OPT_GET_CH6								
				@arg @ref  DRV_DMA_IOCTL_OPT_GET_CH7								
				@arg @ref  DRV_DMA_IOCTL_OPT_TC_IRQ_CTRL_CH0						
				@arg @ref  DRV_DMA_IOCTL_OPT_TC_IRQ_CTRL_CH1						
				@arg @ref  DRV_DMA_IOCTL_OPT_TC_IRQ_CTRL_CH2						
				@arg @ref  DRV_DMA_IOCTL_OPT_TC_IRQ_CTRL_CH3						
				@arg @ref  DRV_DMA_IOCTL_OPT_TC_IRQ_CTRL_CH4						
				@arg @ref  DRV_DMA_IOCTL_OPT_TC_IRQ_CTRL_CH5						
				@arg @ref  DRV_DMA_IOCTL_OPT_TC_IRQ_CTRL_CH6						
				@arg @ref  DRV_DMA_IOCTL_OPT_TC_IRQ_CTRL_CH7						
				@arg @ref  DRV_DMA_IOCTL_OPT_TC_IRQ_RESET_CH0						
				@arg @ref  DRV_DMA_IOCTL_OPT_TC_IRQ_RESET_CH1						
				@arg @ref  DRV_DMA_IOCTL_OPT_TC_IRQ_RESET_CH2						
				@arg @ref  DRV_DMA_IOCTL_OPT_TC_IRQ_RESET_CH3						
				@arg @ref  DRV_DMA_IOCTL_OPT_TC_IRQ_RESET_CH4						
				@arg @ref  DRV_DMA_IOCTL_OPT_TC_IRQ_RESET_CH5						
				@arg @ref  DRV_DMA_IOCTL_OPT_TC_IRQ_RESET_CH6						
				@arg @ref  DRV_DMA_IOCTL_OPT_TC_IRQ_RESET_CH7						
				@arg @ref  DRV_DMA_IOCTL_OPT_ERR_IRQ_MASK_CH0						
				@arg @ref  DRV_DMA_IOCTL_OPT_ERR_IRQ_MASK_CH1						
				@arg @ref  DRV_DMA_IOCTL_OPT_ERR_IRQ_MASK_CH2						
				@arg @ref  DRV_DMA_IOCTL_OPT_ERR_IRQ_MASK_CH3						
				@arg @ref  DRV_DMA_IOCTL_OPT_ERR_IRQ_MASK_CH4						
				@arg @ref  DRV_DMA_IOCTL_OPT_ERR_IRQ_MASK_CH5						
				@arg @ref  DRV_DMA_IOCTL_OPT_ERR_IRQ_MASK_CH6						
				@arg @ref  DRV_DMA_IOCTL_OPT_ERR_IRQ_MASK_CH7						
				@arg @ref  DRV_DMA_IOCTL_OPT_ERR_IRQ_RESET_CH0						
				@arg @ref  DRV_DMA_IOCTL_OPT_ERR_IRQ_RESET_CH1						
				@arg @ref  DRV_DMA_IOCTL_OPT_ERR_IRQ_RESET_CH2						
				@arg @ref  DRV_DMA_IOCTL_OPT_ERR_IRQ_RESET_CH3						
				@arg @ref  DRV_DMA_IOCTL_OPT_ERR_IRQ_RESET_CH4						
				@arg @ref  DRV_DMA_IOCTL_OPT_ERR_IRQ_RESET_CH5						
				@arg @ref  DRV_DMA_IOCTL_OPT_ERR_IRQ_RESET_CH6						
				@arg @ref  DRV_DMA_IOCTL_OPT_ERR_IRQ_RESET_CH7						
				@arg @ref  DRV_DMA_IOCTL_OPT_BUS_CH0_SOURCE							
				@arg @ref  DRV_DMA_IOCTL_OPT_BUS_CH1_SOURCE							
				@arg @ref  DRV_DMA_IOCTL_OPT_BUS_CH2_SOURCE							
				@arg @ref  DRV_DMA_IOCTL_OPT_BUS_CH3_SOURCE							
				@arg @ref  DRV_DMA_IOCTL_OPT_BUS_CH4_SOURCE							
				@arg @ref  DRV_DMA_IOCTL_OPT_BUS_CH5_SOURCE							
				@arg @ref  DRV_DMA_IOCTL_OPT_BUS_CH6_SOURCE							
				@arg @ref  DRV_DMA_IOCTL_OPT_BUS_CH7_SOURCE							
				@arg @ref  DRV_DMA_IOCTL_OPT_BUS_CH0_DESTINATION					
				@arg @ref  DRV_DMA_IOCTL_OPT_BUS_CH1_DESTINATION					
				@arg @ref  DRV_DMA_IOCTL_OPT_BUS_CH2_DESTINATION					
				@arg @ref  DRV_DMA_IOCTL_OPT_BUS_CH3_DESTINATION					
				@arg @ref  DRV_DMA_IOCTL_OPT_BUS_CH4_DESTINATION					
				@arg @ref  DRV_DMA_IOCTL_OPT_BUS_CH5_DESTINATION					
				@arg @ref  DRV_DMA_IOCTL_OPT_BUS_CH6_DESTINATION					
				@arg @ref  DRV_DMA_IOCTL_OPT_BUS_CH7_DESTINATION					
				@arg @ref  DRV_DMA_IOCTL_OPT_DATA_SIZE_CH0_SOURCE					
				@arg @ref  DRV_DMA_IOCTL_OPT_DATA_SIZE_CH1_SOURCE					
				@arg @ref  DRV_DMA_IOCTL_OPT_DATA_SIZE_CH2_SOURCE					
				@arg @ref  DRV_DMA_IOCTL_OPT_DATA_SIZE_CH3_SOURCE					
				@arg @ref  DRV_DMA_IOCTL_OPT_DATA_SIZE_CH4_SOURCE					
				@arg @ref  DRV_DMA_IOCTL_OPT_DATA_SIZE_CH5_SOURCE					
				@arg @ref  DRV_DMA_IOCTL_OPT_DATA_SIZE_CH6_SOURCE					
				@arg @ref  DRV_DMA_IOCTL_OPT_DATA_SIZE_CH7_SOURCE					
				@arg @ref  DRV_DMA_IOCTL_OPT_DATA_SIZE_CH0_DESTINATION				
				@arg @ref  DRV_DMA_IOCTL_OPT_DATA_SIZE_CH1_DESTINATION				
				@arg @ref  DRV_DMA_IOCTL_OPT_DATA_SIZE_CH2_DESTINATION				
				@arg @ref  DRV_DMA_IOCTL_OPT_DATA_SIZE_CH3_DESTINATION				
				@arg @ref  DRV_DMA_IOCTL_OPT_DATA_SIZE_CH4_DESTINATION				
				@arg @ref  DRV_DMA_IOCTL_OPT_DATA_SIZE_CH5_DESTINATION				
				@arg @ref  DRV_DMA_IOCTL_OPT_DATA_SIZE_CH6_DESTINATION				
				@arg @ref  DRV_DMA_IOCTL_OPT_DATA_SIZE_CH7_DESTINATION				
				@arg @ref  DRV_DMA_IOCTL_OPT_TRANSFER_SIZE_CH0						
				@arg @ref  DRV_DMA_IOCTL_OPT_TRANSFER_SIZE_CH1						
				@arg @ref  DRV_DMA_IOCTL_OPT_TRANSFER_SIZE_CH2						
				@arg @ref  DRV_DMA_IOCTL_OPT_TRANSFER_SIZE_CH3						
				@arg @ref  DRV_DMA_IOCTL_OPT_TRANSFER_SIZE_CH4						
				@arg @ref  DRV_DMA_IOCTL_OPT_TRANSFER_SIZE_CH5						
				@arg @ref  DRV_DMA_IOCTL_OPT_TRANSFER_SIZE_CH6						
				@arg @ref  DRV_DMA_IOCTL_OPT_TRANSFER_SIZE_CH7						
				@arg @ref  DRV_DMA_IOCTL_OPT_ENABLE_CH0								
				@arg @ref  DRV_DMA_IOCTL_OPT_ENABLE_CH1								
				@arg @ref  DRV_DMA_IOCTL_OPT_ENABLE_CH2								
				@arg @ref  DRV_DMA_IOCTL_OPT_ENABLE_CH3								
				@arg @ref  DRV_DMA_IOCTL_OPT_ENABLE_CH4								
				@arg @ref  DRV_DMA_IOCTL_OPT_ENABLE_CH5								
				@arg @ref  DRV_DMA_IOCTL_OPT_ENABLE_CH6								
				@arg @ref  DRV_DMA_IOCTL_OPT_ENABLE_CH7								
				@arg @ref  DRV_DMA_IOCTL_OPT_INCREASE_CH0_DESTINATION				
				@arg @ref  DRV_DMA_IOCTL_OPT_INCREASE_CH1_DESTINATION				
				@arg @ref  DRV_DMA_IOCTL_OPT_INCREASE_CH2_DESTINATION				
				@arg @ref  DRV_DMA_IOCTL_OPT_INCREASE_CH3_DESTINATION				
				@arg @ref  DRV_DMA_IOCTL_OPT_INCREASE_CH4_DESTINATION				
				@arg @ref  DRV_DMA_IOCTL_OPT_INCREASE_CH5_DESTINATION				
				@arg @ref  DRV_DMA_IOCTL_OPT_INCREASE_CH6_DESTINATION				
				@arg @ref  DRV_DMA_IOCTL_OPT_INCREASE_CH7_DESTINATION				
				@arg @ref  DRV_DMA_IOCTL_OPT_INCREASE_CH0_SOURCE					
				@arg @ref  DRV_DMA_IOCTL_OPT_INCREASE_CH1_SOURCE					
				@arg @ref  DRV_DMA_IOCTL_OPT_INCREASE_CH2_SOURCE					
				@arg @ref  DRV_DMA_IOCTL_OPT_INCREASE_CH3_SOURCE					
				@arg @ref  DRV_DMA_IOCTL_OPT_INCREASE_CH4_SOURCE					
				@arg @ref  DRV_DMA_IOCTL_OPT_INCREASE_CH5_SOURCE					
				@arg @ref  DRV_DMA_IOCTL_OPT_INCREASE_CH6_SOURCE					
				@arg @ref  DRV_DMA_IOCTL_OPT_INCREASE_CH7_SOURCE					
				@arg @ref  DRV_DMA_IOCTL_OPT_ADDRESS_CH0_SOURCE						
				@arg @ref  DRV_DMA_IOCTL_OPT_ADDRESS_CH1_SOURCE						
				@arg @ref  DRV_DMA_IOCTL_OPT_ADDRESS_CH2_SOURCE						
				@arg @ref  DRV_DMA_IOCTL_OPT_ADDRESS_CH3_SOURCE						
				@arg @ref  DRV_DMA_IOCTL_OPT_ADDRESS_CH4_SOURCE						
				@arg @ref  DRV_DMA_IOCTL_OPT_ADDRESS_CH5_SOURCE						
				@arg @ref  DRV_DMA_IOCTL_OPT_ADDRESS_CH6_SOURCE						
				@arg @ref  DRV_DMA_IOCTL_OPT_ADDRESS_CH7_SOURCE						
				@arg @ref  DRV_DMA_IOCTL_OPT_ADDRESS_CH0_DESTINATION				
				@arg @ref  DRV_DMA_IOCTL_OPT_ADDRESS_CH1_DESTINATION				
				@arg @ref  DRV_DMA_IOCTL_OPT_ADDRESS_CH2_DESTINATION				
				@arg @ref  DRV_DMA_IOCTL_OPT_ADDRESS_CH3_DESTINATION				
				@arg @ref  DRV_DMA_IOCTL_OPT_ADDRESS_CH4_DESTINATION				
				@arg @ref  DRV_DMA_IOCTL_OPT_ADDRESS_CH5_DESTINATION				
				@arg @ref  DRV_DMA_IOCTL_OPT_ADDRESS_CH6_DESTINATION				
				@arg @ref  DRV_DMA_IOCTL_OPT_ADDRESS_CH7_DESTINATION				
				@arg @ref  DRV_DMA_IOCTL_OPT_PERI_CH0_SOURCE						
				@arg @ref  DRV_DMA_IOCTL_OPT_PERI_CH1_SOURCE						
				@arg @ref  DRV_DMA_IOCTL_OPT_PERI_CH2_SOURCE						
				@arg @ref  DRV_DMA_IOCTL_OPT_PERI_CH3_SOURCE						
				@arg @ref  DRV_DMA_IOCTL_OPT_PERI_CH4_SOURCE						
				@arg @ref  DRV_DMA_IOCTL_OPT_PERI_CH5_SOURCE						
				@arg @ref  DRV_DMA_IOCTL_OPT_PERI_CH6_SOURCE						
				@arg @ref  DRV_DMA_IOCTL_OPT_PERI_CH7_SOURCE						
				@arg @ref  DRV_DMA_IOCTL_OPT_PERI_CH0_DESTINATION					
				@arg @ref  DRV_DMA_IOCTL_OPT_PERI_CH1_DESTINATION					
				@arg @ref  DRV_DMA_IOCTL_OPT_PERI_CH2_DESTINATION					
				@arg @ref  DRV_DMA_IOCTL_OPT_PERI_CH3_DESTINATION					
				@arg @ref  DRV_DMA_IOCTL_OPT_PERI_CH4_DESTINATION					
				@arg @ref  DRV_DMA_IOCTL_OPT_PERI_CH5_DESTINATION					
				@arg @ref  DRV_DMA_IOCTL_OPT_PERI_CH6_DESTINATION					
				@arg @ref  DRV_DMA_IOCTL_OPT_PERI_CH7_DESTINATION					
				@arg @ref  DRV_DMA_IOCTL_OPT_FLOW_CONTROL_CH0						
				@arg @ref  DRV_DMA_IOCTL_OPT_FLOW_CONTROL_CH1						
				@arg @ref  DRV_DMA_IOCTL_OPT_FLOW_CONTROL_CH2						
				@arg @ref  DRV_DMA_IOCTL_OPT_FLOW_CONTROL_CH3						
				@arg @ref  DRV_DMA_IOCTL_OPT_FLOW_CONTROL_CH4						
				@arg @ref  DRV_DMA_IOCTL_OPT_FLOW_CONTROL_CH5						
				@arg @ref  DRV_DMA_IOCTL_OPT_FLOW_CONTROL_CH6						
				@arg @ref  DRV_DMA_IOCTL_OPT_FLOW_CONTROL_CH7						
				@arg @ref  DRV_DMA_IOCTL_OPT_NEXT_LINK_ADDR_CH0						
				@arg @ref  DRV_DMA_IOCTL_OPT_NEXT_LINK_ADDR_CH1						
				@arg @ref  DRV_DMA_IOCTL_OPT_NEXT_LINK_ADDR_CH2						
				@arg @ref  DRV_DMA_IOCTL_OPT_NEXT_LINK_ADDR_CH3						
				@arg @ref  DRV_DMA_IOCTL_OPT_NEXT_LINK_ADDR_CH4						
				@arg @ref  DRV_DMA_IOCTL_OPT_NEXT_LINK_ADDR_CH5						
				@arg @ref  DRV_DMA_IOCTL_OPT_NEXT_LINK_ADDR_CH6						
				@arg @ref  DRV_DMA_IOCTL_OPT_NEXT_LINK_ADDR_CH7						
  \param [in]	val
  \return		ret
*/
int32_t drv_dma_ioctl( drv_dma_handle_t handle, uint32_t opt, unsigned int val );

/** 
  \brief		dma driver registration function
  \details		
  \param [in]	dma
  \return		ret
*/
int32_t drv_dma_register_driver( struct drv_dma_t * dma);

#ifdef __cplusplus
}
#endif

#endif

