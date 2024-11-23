#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#ifdef __cplusplus
extern "C"{
#endif

#define DRV_SPI_IOCTL_OPT_GET												0
#define DRV_SPI_IOCTL_OPT_REGISTER_IRQ_HANDLER								1
#define DRV_SPI_IOCTL_OPT_STARTUP											2
#define DRV_SPI_IOCTL_OPT_SHUTDOWN											3

#define DRV_SPI_IOCTL_OPT_TX_IRQ_CTRL										10
#define DRV_SPI_IOCTL_OPT_RX_IRQ_CTRL										11

#define DRV_SPI_IOCTL_OPT_MODE												100
#define DRV_SPI_IOCTL_OPT_MAUNAL_CS											101
#define DRV_SPI_IOCTL_OPT_MASTER_SLAVE										102
#define DRV_SPI_IOCTL_OPT_SPEED_HZ											103
#define DRV_SPI_IOCTL_OPT_TRANSFER_SIZE										104

#define DRV_SPI_IOCTL_OPT_MAUNAL_CS_CTRL									110

#define DRV_SPI_IOCTL_OPT_TXDMA_EN											120
#define DRV_SPI_IOCTL_OPT_RXDMA_EN											121

#define DRV_SPI_IOCTL_OPT_GPIO_CLK											300
#define DRV_SPI_IOCTL_OPT_GPIO_CS											301
#define DRV_SPI_IOCTL_OPT_GPIO_TX											302
#define DRV_SPI_IOCTL_OPT_GPIO_RX											303
/******************************************************************************/
#define DRV_SPI_IOCTL_OPT_MODE_MOTOROLA_MODE0								0
#define DRV_SPI_IOCTL_OPT_MODE_MOTOROLA_MODE1								1
#define DRV_SPI_IOCTL_OPT_MODE_MOTOROLA_MODE2								2
#define DRV_SPI_IOCTL_OPT_MODE_MOTOROLA_MODE3								3
#define DRV_SPI_IOCTL_OPT_MODE_TISYNCHRONOUS								4
#define DRV_SPI_IOCTL_OPT_MODE_NATIONAL_MICROWIRE							5

#define DRV_SPI_IOCTL_OPT_MASTER											0
#define DRV_SPI_IOCTL_OPT_SLAVE												1

#define DRV_SPI_IOCTL_OPT_TRANSFER_SIZE_4BIT								3
#define DRV_SPI_IOCTL_OPT_TRANSFER_SIZE_5BIT								4
#define DRV_SPI_IOCTL_OPT_TRANSFER_SIZE_6BIT								5
#define DRV_SPI_IOCTL_OPT_TRANSFER_SIZE_7BIT								6
#define DRV_SPI_IOCTL_OPT_TRANSFER_SIZE_8BIT								7
#define DRV_SPI_IOCTL_OPT_TRANSFER_SIZE_9BIT								8
#define DRV_SPI_IOCTL_OPT_TRANSFER_SIZE_10BIT								9
#define DRV_SPI_IOCTL_OPT_TRANSFER_SIZE_11BIT								10
#define DRV_SPI_IOCTL_OPT_TRANSFER_SIZE_12BIT								11
#define DRV_SPI_IOCTL_OPT_TRANSFER_SIZE_13BIT								12
#define DRV_SPI_IOCTL_OPT_TRANSFER_SIZE_14BIT								13
#define DRV_SPI_IOCTL_OPT_TRANSFER_SIZE_15BIT								14
#define DRV_SPI_IOCTL_OPT_TRANSFER_SIZE_16BIT								15

#define DRV_SPI_IOCTL_OPT_GPIO_RESET									0xffff
/****************************************************************************/

enum drv_spi_id_t{
	drv_spi_id0,
	drv_spi_id1,
	drv_spi_id_max,
};

typedef struct DRV_SPI_HANDLE_T * drv_spi_handle_t;

struct drv_spi_t;
struct drv_spi_ops_t;
struct drv_spi_ioctl_t;
union drv_spi_ioctl_flag_u;

union drv_spi_ioctl_flag_u{
	uint32_t w;
	struct{
		uint32_t busy				: 1;
		uint32_t rff				: 1;
		uint32_t rne				: 1;
		uint32_t tnf				: 1;
		uint32_t tfe				: 1;
		uint32_t tx_irq				: 1;
		uint32_t rx_irq				: 1;
		uint32_t rt_irq				: 1;
	}b;
};

struct drv_spi_ioctl_t{
	uint8_t enabled;
	uint8_t tx_irq_enable;
	uint8_t rx_irq_enable;
	uint8_t manual_cs;
	uint8_t slave;
	uint8_t transfersize;
	uint8_t mode;
	uint8_t txdma_enable;
	uint8_t rxdma_enable;
	uint32_t clk;
	uint32_t clk_div;
	uint32_t speed_hz;
	uint32_t gp_clk_group 		:16;
	uint32_t gp_clk_pin 		:16;
	uint32_t gp_cs_group 		:16;
	uint32_t gp_cs_pin 			:16;
	uint32_t gp_tx_group 		:16;
	uint32_t gp_tx_pin 			:16;
	uint32_t gp_rx_group 		:16;
	uint32_t gp_rx_pin 			:16;
	union drv_spi_ioctl_flag_u flag;
	
};

struct DRV_SPI_HANDLE_T{
	enum drv_spi_id_t id;
	struct drv_spi_ioctl_t ioctl;
};


struct drv_spi_ops_t{
	int32_t (*close)(struct drv_spi_t *);
	uint32_t (*read)(struct drv_spi_t *);
	void (*write)(struct drv_spi_t*, uint32_t);
	int32_t (*startup)(struct drv_spi_t *);
	void (*shutdown)(struct drv_spi_t *);
	int32_t (*ioctl)(struct drv_spi_t*, uint32_t, unsigned int );
	void (*enable_irq)(struct drv_spi_t *, uint32_t, uint32_t );
};

struct drv_spi_t{
	drv_spi_handle_t handle;
	const struct drv_spi_ops_t *ops;
	void (*handle_irq)(drv_spi_handle_t);
};

/** 
  \brief		spi driver open function
  \details		
  \param [in]	id
  \param [in]	handle
  \return		ret
*/
int32_t drv_spi_open( enum drv_spi_id_t id, drv_spi_handle_t *handle );

/** 
  \brief		spi driver close function
  \details		
  \param [in]	handle
  \return		ret
*/
int32_t drv_spi_close( drv_spi_handle_t handle );

/** 
  \brief		spi driver read function
  \details		
  \param [in]	handle
  \param [in]	dat
  \return		ret
*/
int32_t drv_spi_read( drv_spi_handle_t handle, uint32_t *dat );

/** 
  \brief		spi driver write function
  \details		
  \param [in]	handle
  \param [in]	dat
  \return		ret
*/
int32_t drv_spi_write( drv_spi_handle_t handle, uint32_t dat );

/** 
  \brief		spi driver input output control function
  \details		critical section
  \param [in]	handle
  \param [in]	opt This parameter can be one or multiple of the following values:
				@arg @ref DRV_SPI_IOCTL_OPT_GET						
				@arg @ref DRV_SPI_IOCTL_OPT_REGISTER_IRQ_HANDLER	
				@arg @ref DRV_SPI_IOCTL_OPT_STARTUP					
				@arg @ref DRV_SPI_IOCTL_OPT_SHUTDOWN				
				@arg @ref DRV_SPI_IOCTL_OPT_TX_IRQ_CTRL				
				@arg @ref DRV_SPI_IOCTL_OPT_RX_IRQ_CTRL				
				@arg @ref DRV_SPI_IOCTL_OPT_MODE					
				@arg @ref DRV_SPI_IOCTL_OPT_MAUNAL_CS				
				@arg @ref DRV_SPI_IOCTL_OPT_MASTER_SLAVE			
				@arg @ref DRV_SPI_IOCTL_OPT_SPEED_HZ				
				@arg @ref DRV_SPI_IOCTL_OPT_TRANSFER_SIZE			
				@arg @ref DRV_SPI_IOCTL_OPT_MAUNAL_CS_CTRL			
				@arg @ref DRV_SPI_IOCTL_OPT_TXDMA_EN				
				@arg @ref DRV_SPI_IOCTL_OPT_RXDMA_EN				
				@arg @ref DRV_SPI_IOCTL_OPT_GPIO_CLK				
				@arg @ref DRV_SPI_IOCTL_OPT_GPIO_CS					
				@arg @ref DRV_SPI_IOCTL_OPT_GPIO_TX					
				@arg @ref DRV_SPI_IOCTL_OPT_GPIO_RX					
  \param [in]	val
  \return		ret
*/
int32_t drv_spi_ioctl(    drv_spi_handle_t handle, uint32_t opt, unsigned int val);

/** 
  \brief		spi driver registration function
  \details		
  \param [in]	spi
  \return		ret
*/
int32_t drv_spi_register_driver( struct drv_spi_t *spi );

#ifdef __cplusplus
}
#endif

#endif

