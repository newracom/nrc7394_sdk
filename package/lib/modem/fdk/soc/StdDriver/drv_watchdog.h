#ifndef __DRV_WATCHDOG_H__
#define __DRV_WATCHDOG_H__

#ifdef __cplusplus
extern "C"{
#endif

#define DRV_WATCHDOG_IOCTL_OPT_GET								0
#define DRV_WATCHDOG_IOCTL_OPT_START							1
#define DRV_WATCHDOG_IOCTL_OPT_STOP								2
#define DRV_WATCHDOG_IOCTL_OPT_PING								3
#define DRV_WATCHDOG_IOCTL_OPT_SET_TIMEOUT						4
#define DRV_WATCHDOG_IOCTL_OPT_REGISTER_IRQ						5
#define DRV_WATCHDOG_IOCTL_OPT_GET_TIMELEFT						6
#define DRV_WATCHDOG_IOCTL_OPT_IRQ_CTRL							7
#define DRV_WATCHDOG_IOCTL_OPT_IRQ_FLAG							8
#define DRV_WATCHDOG_IOCTL_OPT_LOCK								9
#define DRV_WATCHDOG_IOCTL_OPT_UNLOCK							10
#define DRV_WATCHDOG_IOCTL_OPT_RESET							11

/*****************************************************************************/
#define DRV_WATCHDOG_IOCTL_OPT_IRQ_FLAG_RESET					1


enum drv_watchdog_id_t{
	drv_watchdog_id0,
	drv_watchdog_id_max,
};

struct drv_watchdog_ops_t;
struct drv_watchdog_t;
struct drv_watchdog_ioctl_t;


struct drv_watchdog_ops_t{
	uint32_t (*close)(struct drv_watchdog_t *);
	int32_t (*start)(struct drv_watchdog_t *);
	int32_t (*stop)(struct drv_watchdog_t *);
	int32_t (*ping)(struct drv_watchdog_t *);
	int32_t (*set_timeout)(struct drv_watchdog_t *, uint32_t );
	uint32_t (*get_timeleft)(struct drv_watchdog_t *);
	uint32_t (*ioctl)(struct drv_watchdog_t *, uint32_t, unsigned int);
	int32_t (*irq_enable)(struct drv_watchdog_t *, uint32_t );
};

struct drv_watchdog_ioctl_t{
	uint32_t enable;
	uint32_t irq_enable;
	uint32_t reset_enable;
	uint32_t timeout;
	uint32_t timeleft;
	uint32_t lock;
	uint32_t irq_flag	:1;
};


struct drv_watchdog_t{
	int32_t id;
	struct drv_watchdog_ioctl_t ioctl;
	const struct drv_watchdog_ops_t *ops;
	void (*handle_irq)(void);
};

/** 
  \brief		watchdog driver open function
  \details		
  \param [in]	id
  \return		ret
*/
uint32_t drv_watchdog_open(enum drv_watchdog_id_t id);

/** 
  \brief		watchdog driver close function
  \details		
  \param [in]	id
  \return		ret
*/
uint32_t drv_watchdog_close(enum drv_watchdog_id_t id);

/** 
  \brief		watchdog driver input output control function
  \details		critical section
  \param [in]	id
  \param [in]	opt This parameter can be one or multiple of the following values:
				@arg @ref DRV_WATCHDOG_IOCTL_OPT_GET
				@arg @ref DRV_WATCHDOG_IOCTL_OPT_START
				@arg @ref DRV_WATCHDOG_IOCTL_OPT_STOP
				@arg @ref DRV_WATCHDOG_IOCTL_OPT_PING
				@arg @ref DRV_WATCHDOG_IOCTL_OPT_SET_TIMEOUT
				@arg @ref DRV_WATCHDOG_IOCTL_OPT_REGISTER_IRQ
				@arg @ref DRV_WATCHDOG_IOCTL_OPT_GET_TIMELEFT
				@arg @ref DRV_WATCHDOG_IOCTL_OPT_IRQ_CTRL
				@arg @ref DRV_WATCHDOG_IOCTL_OPT_IRQ_FLAG
 				@arg @ref DRV_WATCHDOG_IOCTL_OPT_LOCK
 				@arg @ref DRV_WATCHDOG_IOCTL_OPT_UNLOCK
 				@arg @ref DRV_WATCHDOG_IOCTL_OPT_RESET
   \param [in]	val
  \return		ret
*/
struct drv_watchdog_ioctl_t drv_watchdog_ioctl(enum drv_watchdog_id_t id, uint32_t opt, unsigned int val);

/** 
  \brief		watchdog driver registration function
  \details		
  \param [in]	watchdog
  \return		ret
*/
uint32_t drv_watchdog_register_driver(struct drv_watchdog_t *watchdog);

#ifdef __cplusplus
}
#endif

#endif

