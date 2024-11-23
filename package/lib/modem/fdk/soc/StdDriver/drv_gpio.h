#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#ifdef __cplusplus
extern "C"{
#endif

#define DRV_GPIO_IOCTL_OPT_GET_MODE_DIRECTION								1
#define DRV_GPIO_IOCTL_OPT_SET_MODE_DIRECTION_INPUT							2
#define DRV_GPIO_IOCTL_OPT_SET_MODE_DIRECTION_OUTPUT						3

#define DRV_GPIO_IOCTL_OPT_GET_PIN											11
#define DRV_GPIO_IOCTL_OPT_GET_MULTIPLE_PIN									12

#define DRV_GPIO_IOCTL_OPT_SET_POUT_HIGH									21
#define DRV_GPIO_IOCTL_OPT_SET_POUT_LOW										22

#define DRV_GPIO_IOCTL_OPT_SET_POUT_MULTIPLE								31

#define DRV_GPIO_IOCTL_OPT_SET_CONFIG_NO_PULL								41
#define DRV_GPIO_IOCTL_OPT_SET_CONFIG_PULLUP								42
#define DRV_GPIO_IOCTL_OPT_SET_CONFIG_PULLDOWN								43
/******************************************************************************/


/******************************************************************************/


enum drv_gpio_id_t{
	drv_gpio_id0,
	drv_gpio_id_max,
};

typedef struct DRV_GPIO_HANDLE_T*	drv_gpio_handle_t;
struct drv_gpio_t;
struct drv_gpio_ioctl_t;
struct drv_gpio_ops_t;

union drv_gpio_ioctl_bit_u{
	uint32_t w;
	struct{
	uint32_t gp0		: 1;
	uint32_t gp1		: 1;
	uint32_t gp2		: 1;
	uint32_t gp3		: 1;
	uint32_t gp4		: 1;
	uint32_t gp5		: 1;
	uint32_t gp6		: 1;
	uint32_t gp7		: 1;
	uint32_t gp8		: 1;
	uint32_t gp9		: 1;
	uint32_t gp10		: 1;
	uint32_t gp11		: 1;
	uint32_t gp12		: 1;
	uint32_t gp13		: 1;
	uint32_t gp14		: 1;
	uint32_t gp15		: 1;
	uint32_t gp16		: 1;
	uint32_t gp17		: 1;
	uint32_t gp18		: 1;
	uint32_t gp19		: 1;
	uint32_t gp20		: 1;
	uint32_t gp21		: 1;
	uint32_t gp22		: 1;
	uint32_t gp23		: 1;
	uint32_t gp24		: 1;
	uint32_t gp25		: 1;
	uint32_t gp26		: 1;
	uint32_t gp27		: 1;
	uint32_t gp28		: 1;
	uint32_t gp29		: 1;
	uint32_t gp30		: 1;
	uint32_t gp31		: 1;
	}b;
};

union drv_gpio_ioctl_l2bit_u{
	uint32_t w;
	struct{
	uint32_t gp0		: 2;
	uint32_t gp1		: 2;
	uint32_t gp2		: 2;
	uint32_t gp3		: 2;
	uint32_t gp4		: 2;
	uint32_t gp5		: 2;
	uint32_t gp6		: 2;
	uint32_t gp7		: 2;
	uint32_t gp8		: 2;
	uint32_t gp9		: 2;
	uint32_t gp10		: 2;
	uint32_t gp11		: 2;
	uint32_t gp12		: 2;
	uint32_t gp13		: 2;
	uint32_t gp14		: 2;
	uint32_t gp15		: 2;
	}b;
};

union drv_gpio_ioctl_h2bit_u{
	uint32_t w;
	struct{
	uint32_t gp16		: 2;
	uint32_t gp17		: 2;
	uint32_t gp18		: 2;
	uint32_t gp19		: 2;
	uint32_t gp20		: 2;
	uint32_t gp21		: 2;
	uint32_t gp22		: 2;
	uint32_t gp23		: 2;
	uint32_t gp24		: 2;
	uint32_t gp25		: 2;
	uint32_t gp26		: 2;
	uint32_t gp27		: 2;
	uint32_t gp28		: 2;
	uint32_t gp29		: 2;
	uint32_t gp30		: 2;
	uint32_t gp31		: 2;
	}b;
};


struct drv_gpio_ioctl_status_t{
	union drv_gpio_ioctl_bit_u data;
	union drv_gpio_ioctl_l2bit_u lmode;
	union drv_gpio_ioctl_h2bit_u hmode;
	union drv_gpio_ioctl_l2bit_u lpull;
	union drv_gpio_ioctl_h2bit_u hpull;
};

struct drv_gpio_ioctl_t{
	struct drv_gpio_ioctl_status_t status;
};

struct DRV_GPIO_HANDLE_T{
	enum drv_gpio_id_t id;
	struct drv_gpio_ioctl_t ioctl;
};

struct drv_gpio_ops_t{
	int32_t (*close)(struct drv_gpio_t*);
	int32_t (*set_config)(struct drv_gpio_t*, unsigned int, unsigned int);
	int32_t (*get_direction)(struct drv_gpio_t *, unsigned int );
	int32_t (*direction_input)(struct drv_gpio_t *, unsigned int, unsigned int );
	int32_t (*direction_output)(struct drv_gpio_t *, unsigned int, unsigned int );
	int32_t (*get)(struct drv_gpio_t *, unsigned int );
	int32_t (*get_multiple)(struct drv_gpio_t *, unsigned int*, unsigned int *);
	void (*set)(struct drv_gpio_t *, unsigned int, unsigned int);
	void (*set_multiple)(struct drv_gpio_t *, unsigned int*, unsigned int *);
};

struct drv_gpio_t{
	drv_gpio_handle_t handle;
	const struct drv_gpio_ops_t *ops;
};

/** 
  \brief		gpio driver open function
  \details		
  \param [in]	id
  \param [in]	handle
  \return		ret
*/
int32_t drv_gpio_open( enum drv_gpio_id_t id, drv_gpio_handle_t *handle);

/** 
  \brief		gpio driver close function
  \details		
  \param [in]	handle
  \return		ret
*/
int32_t drv_gpio_close( drv_gpio_handle_t handle );

/** 
  \brief		gpio driver input output control function
  \details		critical section
  \param [in]	handle
  \param [in]	opt This parameter can be one or multiple of the following values:
				@arg @ref DRV_EXTINT_IOCTL_OPT_GET
				@arg @ref DRV_GPIO_IOCTL_OPT_GET_MODE_DIRECTION				
				@arg @ref DRV_GPIO_IOCTL_OPT_SET_MODE_DIRECTION_INPUT		
				@arg @ref DRV_GPIO_IOCTL_OPT_SET_MODE_DIRECTION_OUTPUT		
				@arg @ref DRV_GPIO_IOCTL_OPT_GET_PIN						
				@arg @ref DRV_GPIO_IOCTL_OPT_GET_MULTIPLE_PIN				
				@arg @ref DRV_GPIO_IOCTL_OPT_SET_POUT_HIGH					
				@arg @ref DRV_GPIO_IOCTL_OPT_SET_POUT_LOW					
				@arg @ref DRV_GPIO_IOCTL_OPT_SET_POUT_MULTIPLE				
				@arg @ref DRV_GPIO_IOCTL_OPT_SET_CONFIG_NO_PULL				
				@arg @ref DRV_GPIO_IOCTL_OPT_SET_CONFIG_PULLUP				
				@arg @ref DRV_GPIO_IOCTL_OPT_SET_CONFIG_PULLDOWN			
  \param [in]	val
  \return		ret
*/
int32_t drv_gpio_ioctl( drv_gpio_handle_t handle, uint32_t opt, unsigned int val );

/** 
  \brief		gpio driver registration function
  \details		
  \param [in]	gpio
  \return		ret
*/
int32_t drv_gpio_register_driver( struct drv_gpio_t *gpio );

#ifdef __cplusplus
}
#endif

#endif

