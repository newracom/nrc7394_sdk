#ifndef __DRV_TIMER_H__
#define __DRV_TIMER_H__

#ifdef __cplusplus
extern "C"{
#endif

#define DRV_TIMER_IOCTL_OPT_GET												0
#define DRV_TIMER_IOCTL_OPT_RESUME											1
#define DRV_TIMER_IOCTL_OPT_SUSPEND											2
#define DRV_TIMER_IOCTL_OPT_SHUTDOWN										3

#define DRV_TIMER_IOCTL_OPT_REGISTER_HANLDE_IRQ							0x10
#define DRV_TIMER_IOCTL_OPT_IRQ_CTRL									0x11

#define DRV_TIMER_IOCTL_OPT_SET_NEXT_EVENT									0x20
#define DRV_TIMER_IOCTL_OPT_SET_STATE_PERIODIC								0x21
#define DRV_TIMER_IOCTL_OPT_SET_STATE_ONESHOT								0x22
/*****************************************************************************/
#define DRV_TIMER_IOCTL_OPT_MODE_PERIODIC									0
#define DRV_TIMER_IOCTL_OPT_MODE_ONESHOT									1
/****************************************************************************/


enum drv_timer_id_t{
	drv_timer_id0,
	drv_timer_id1,
	drv_timer_id2,
	drv_timer_id3,
	drv_timer_id_max,
};

typedef struct DRV_TIMER_HANDLE_T * drv_timer_handle_t;

struct drv_timer_t;
struct drv_timer_ioctl_t;


struct drv_timer_ioctl_t{
	int8_t enable;
	int8_t irq_enable;
	uint8_t mode;
	uint64_t next_event;
	uint64_t raw_count;
	uint32_t tick;
};

struct drv_timer_event_t{
	void (*irq_enable)(struct drv_timer_t*, uint32_t);
	void (*resume)( struct drv_timer_t*);
	void (*suspend)( struct drv_timer_t*);
	int32_t (*set_next_event)( struct drv_timer_t*, uint64_t);
	int32_t (*set_state_periodic)( struct drv_timer_t*);
	int32_t (*set_state_oneshot)( struct drv_timer_t*);
	void (*set_state_shutdown)( struct drv_timer_t*);
	int32_t (*close)( struct drv_timer_t*);
	int32_t (*ioctl)( struct drv_timer_t*, uint32_t, unsigned int);
};

struct DRV_TIMER_HANDLE_T{
	enum drv_timer_id_t id;
	struct drv_timer_ioctl_t ioctl;
};


struct drv_timer_t{
	drv_timer_handle_t handle;
	const struct drv_timer_event_t *event;
	void (*handle_irq)(void);
};

/** 
  \brief		timer driver open function
  \details		
  \param [in]	id
  \param [in]	handle
  \return		ret
*/
int32_t drv_timer_open( enum drv_timer_id_t id, drv_timer_handle_t *handle);

/** 
  \brief		timer driver close function
  \details		
  \param [in]	handle
  \return		ret
*/
int32_t drv_timer_close( drv_timer_handle_t handle );

/** 
  \brief		timer driver input output control function
  \details		critical section
  \param [in]	handle
  \param [in]	opt This parameter can be one or multiple of the following values:
				@arg @ref DRV_TIMER_IOCTL_OPT_GET					
				@arg @ref DRV_TIMER_IOCTL_OPT_RESUME				
				@arg @ref DRV_TIMER_IOCTL_OPT_SUSPEND				
				@arg @ref DRV_TIMER_IOCTL_OPT_SHUTDOWN				
				@arg @ref DRV_TIMER_IOCTL_OPT_REGISTER_HANLDE_IRQ	
				@arg @ref DRV_TIMER_IOCTL_OPT_IRQ_CTRL				
				@arg @ref DRV_TIMER_IOCTL_OPT_SET_NEXT_EVENT		
				@arg @ref DRV_TIMER_IOCTL_OPT_SET_STATE_PERIODIC	
				@arg @ref DRV_TIMER_IOCTL_OPT_SET_STATE_ONESHOT		
  \param [in]	val
  \return		ret
*/
int32_t drv_timer_ioctl( drv_timer_handle_t handle, uint32_t opt, unsigned int val);

/** 
  \brief		timer driver registration function
  \details		
  \param [in]	timer
  \return		ret
*/
int32_t drv_timer_register_driver( struct drv_timer_t *timer );

#ifdef __cplusplus
}
#endif

#endif

