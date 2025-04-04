#ifndef __DRV_I2C_H__
#define __DRV_I2C_H__

#ifdef __cplusplus
extern "C"{
#endif

#define DRV_I2C_IOCTL_OPT_GET												0
#define DRV_I2C_IOCTL_OPT_REGISTER_IRQ_HANDLER								1
#define DRV_I2C_IOCTL_OPT_STARTUP											2
#define DRV_I2C_IOCTL_OPT_SHUTDOWN											3

#define DRV_I2C_IOCTL_OPT_IRQ_CTRL											10

//#define DRV_I2C_IOCTL_OPT_DATA_WIDTH										50
#define DRV_I2C_IOCTL_OPT_BUS_SPEED											51

#define DRV_I2C_IOCTL_OPT_GPIO_SCL											300
#define DRV_I2C_IOCTL_OPT_GPIO_SDA											301
/****************************************************************************/
#define DRV_I2C_WRITE_MEM_ADDR_SIZE_NONE									0
#define DRV_I2C_WRITE_MEM_ADDR_SIZE_8BIT									1
#define DRV_I2C_WRITE_MEM_ADDR_SIZE_16BIT									2

//#define DRV_I2C_IOCTL_OPT_DATA_WIDTH_8BIT									0
//#define DRV_I2C_IOCTL_OPT_DATA_WIDTH_16BIT								1

#define DRV_I2C_IOCTL_OPT_GPIO_RESET									0xffff
/****************************************************************************/

enum drv_i2c_id_t{
	drv_i2c_id0,
	drv_i2c_id1,
	drv_i2c_id_max,
};

typedef struct DRV_I2C_HANDLE_T * drv_i2c_handle_t;
struct drv_i2c_ioctl_t;
struct drv_i2c_ops_t;
struct drv_i2c_t;

union drv_i2c_ioctl_flag_u{
	uint32_t w;
	struct{
		uint32_t irq_flag		: 1;
		uint32_t busy			: 1;
		uint32_t rxack			: 1;
		uint32_t al				: 1;
		uint32_t tip			: 1;
	}b;
};

struct drv_i2c_ioctl_t{
	int8_t enable;
	int8_t irq_enable;
	uint32_t busspeed;
//	uint8_t data_width;
	uint32_t gp_scl_group	:16;
	uint32_t gp_scl_pin		:16;
	uint32_t gp_sda_group	:16;
	uint32_t gp_sda_pin		:16;
	union drv_i2c_ioctl_flag_u flag;
};

struct DRV_I2C_HANDLE_T{
	enum drv_i2c_id_t id;
	struct drv_i2c_ioctl_t ioctl;
};

struct drv_i2c_ops_t{
	int32_t (*startup)(struct drv_i2c_t *);
	void (*shutdown)(struct drv_i2c_t *);
	int32_t (*irq_enable)(struct drv_i2c_t *, uint32_t);
	int32_t (*close)(struct drv_i2c_t *);
	void (*write)(struct drv_i2c_t *, uint16_t, uint16_t, uint8_t, uint8_t *, uint32_t );
	void (*read)(struct drv_i2c_t *, uint16_t, uint16_t, uint8_t, uint8_t *, uint32_t );
	int32_t (*ioctl)(struct drv_i2c_t *, uint32_t, unsigned int );
};

struct drv_i2c_t{
	drv_i2c_handle_t handle;
	const struct drv_i2c_ops_t *ops;
	void (*handle_irq)(drv_i2c_handle_t);
};

/** 
  \brief		i2c driver open function
  \details		
  \param [in]	id
  \param [in]	handle
  \return		ret
*/
int32_t drv_i2c_open( enum drv_i2c_id_t id, drv_i2c_handle_t *handle );

/** 
  \brief		i2c driver close function
  \details		
  \param [in]	handle
  \return		ret
*/
int32_t drv_i2c_close( drv_i2c_handle_t handle );

/** 
  \brief		i2c driver write function
  \details		
  \param [in]	handle
  \param [in]	dat
  \return		ret
*/
//int32_t drv_i2c_write( drv_i2c_handle_t handle, uint32_t dat );
int32_t drv_i2c_write( drv_i2c_handle_t handle, uint16_t dev_addr, uint16_t mem_addr, uint8_t mem_addr_size, uint8_t *dat, uint32_t size );

/** 
  \brief		i2c driver read function
  \details		
  \param [in]	handle
  \param [in]	dat
  \return		ret
*/
int32_t drv_i2c_read( drv_i2c_handle_t handle, uint16_t dev_addr, uint16_t mem_addr, uint8_t mem_addr_size, uint8_t *dat, uint32_t size );

/** 
  \brief		i2c driver input output control function
  \details		critical section
  \param [in]	handle
  \param [in]	opt This parameter can be one or multiple of the following values:
				@arg @ref  DRV_I2C_IOCTL_OPT_GET					
				@arg @ref  DRV_I2C_IOCTL_OPT_REGISTER_IRQ_HANDLER	
				@arg @ref  DRV_I2C_IOCTL_OPT_STARTUP				
				@arg @ref  DRV_I2C_IOCTL_OPT_SHUTDOWN				
				@arg @ref  DRV_I2C_IOCTL_OPT_IRQ_CTRL				
				@arg @ref  DRV_I2C_IOCTL_OPT_RESET_IRQ_FLAG			
				@arg @ref  DRV_I2C_IOCTL_OPT_DATA_WIDTH				
				@arg @ref  DRV_I2C_IOCTL_OPT_BUS_SPEED				
				@arg @ref  DRV_I2C_IOCTL_OPT_COMMAND				
				@arg @ref  DRV_I2C_IOCTL_OPT_GPIO_SCL				
				@arg @ref  DRV_I2C_IOCTL_OPT_GPIO_SDA				
  \param [in]	val
  \return		ret
*/
int32_t drv_i2c_ioctl( drv_i2c_handle_t handle, uint32_t opt, unsigned int val);

/** 
  \brief		i2c driver registration function
  \details		
  \param [in]	i2c
  \return		ret
*/
int32_t drv_i2c_register_driver( struct drv_i2c_t *i2c );

#ifdef __cplusplus
}
#endif

#endif
