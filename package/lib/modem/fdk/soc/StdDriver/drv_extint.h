#ifndef __DRV_EXTINT_H__
#define __DRV_EXTINT_H__

#ifdef __cplusplus
extern "C"{
#endif

#define DRV_EXTINT_IOCTL_OPT_GET										0
#define DRV_EXTINT_IOCTL_OPT_REGISTER_IRQ_HANDLER						1
#define DRV_EXTINT_IOCTL_OPT_IRQ_CTRL									2
#define DRV_EXTINT_IOCTL_OPT_TRIGGER									3
#define DRV_EXTINT_IOCTL_OPT_SENSE										4
#define DRV_EXTINT_IOCTL_OPT_DEBOUNCE									5
#define DRV_EXTINT_IOCTL_OPT_DEBOUNCE_TIME								6
#define DRV_EXTINT_IOCTL_OPT_IRQ_FLAG									7
#define DRV_EXTINT_IOCTL_OPT_WKSRC										8

#define DRV_EXTINT_IOCTL_OPT_GPIO										0x300

/****************************************************************************/
#define DRV_EXTINT_IOCTL_OPT_TRIGGER_RISING								0
#define DRV_EXTINT_IOCTL_OPT_TRIGGER_FALLING							1
#define DRV_EXTINT_IOCTL_OPT_TRIGGER_RISING_FALLING						2

#define DRV_EXTINT_IOCTL_OPT_SENSE_EDGE									0
#define DRV_EXTINT_IOCTL_OPT_SENSE_LEVEL								1

#define DRV_EXTINT_IOCTL_OPT_IRQ_FLAG_RESET								1

#define DRV_EXTINT_IOCTL_OPT_WKSRC_DISABLE								0
#define DRV_EXTINT_IOCTL_OPT_WKSRC_WKSRC0								1
#define DRV_EXTINT_IOCTL_OPT_WKSRC_WKSRC1								2


enum drv_extint_id_t{
	drv_extint_id0,
	drv_extint_id1,
	drv_extint_id2,
	drv_extint_id3,
	drv_extint_id_max,
};

struct drv_extint_ops_t;
struct drv_extint_t;

struct drv_extint_ops_t{
	uint32_t (*close)(struct drv_extint_t *);
	void (*ioctl)(struct drv_extint_t *, uint32_t, unsigned int);
	void (*irq_enable)(struct drv_extint_t *, uint32_t );
};

struct drv_extint_ioctl_t{
	uint32_t irq_enable;
	uint32_t trigger;
	uint32_t sense;
	uint32_t debounce_enable;
	uint32_t debounce_timing;
	uint32_t wksrc;
	uint32_t gp_group :16;
	uint32_t gp_pin :16;
	uint32_t irq_flag : 1;
};

struct drv_extint_t{
	uint32_t id;
	struct drv_extint_ioctl_t ioctl;
	const struct drv_extint_ops_t *ops;
	void (*handle_irq)(void);
};

/** 
  \brief		external interrupt driver open function
  \details		
  \param [in]	id
  \return		ret
*/
uint32_t drv_extint_open( enum drv_extint_id_t id );

/** 
  \brief		external interrupt driver close function
  \details		
  \param [in]	id
  \return		ret
*/
uint32_t drv_extint_close( enum drv_extint_id_t id );

/** 
  \brief		external interrupt driver input output control function
  \details		critical section
  \param [in]	id
  \param [in]	opt This parameter can be one or multiple of the following values:
				@arg @ref DRV_EXTINT_IOCTL_OPT_GET
				@arg @ref DRV_EXTINT_IOCTL_OPT_REGISTER_IRQ_HANDLER
				@arg @ref DRV_EXTINT_IOCTL_OPT_IRQ_CTRL
				@arg @ref DRV_EXTINT_IOCTL_OPT_TRIGGER
				@arg @ref DRV_EXTINT_IOCTL_OPT_SENSE
				@arg @ref DRV_EXTINT_IOCTL_OPT_DEBOUNCE
				@arg @ref DRV_EXTINT_IOCTL_OPT_DEBOUNCE_TIME
				@arg @ref DRV_EXTINT_IOCTL_OPT_IRQ_FLAG
				@arg @ref DRV_EXTINT_IOCTL_OPT_WKSRC
				@arg @ref DRV_EXTINT_IOCTL_OPT_GPIO
  \param [in]	val
  \return		ret
*/
struct drv_extint_ioctl_t drv_extint_ioctl( enum drv_extint_id_t id, uint32_t opt, unsigned int val);

/** 
  \brief		external interrupt driver registration function
  \details		
  \param [in]	extint
  \return		ret
*/
uint32_t drv_extint_register_driver(struct drv_extint_t *extint);

#ifdef __cplusplus
}
#endif

#endif

