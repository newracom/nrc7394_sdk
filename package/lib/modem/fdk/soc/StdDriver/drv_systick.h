#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#ifdef __cplusplus
extern "C"{
#endif

#define DRV_SYSTICK_IOCTL_OPT_GET										0
#define DRV_SYSTICK_IOCTL_OPT_REGISTER_IRQ_HANDLER						1
//#define DRV_SYSTICK_IOCTL_OPT_IRQ_CTRL									2
#define DRV_SYSTICK_IOCTL_OPT_STARTUP									3
#define DRV_SYSTICK_IOCTL_OPT_SHUTDOWN									4
#define DRV_SYSTICK_IOCTL_OPT_CLOCK										5

struct drv_systick_ops_t;
struct drv_systick_t;
struct drv_systick_ioctl_t;

enum drv_systick_id_t{
	drv_systick_id0,
	drv_systick_max,
};

struct drv_systick_ioctl_t{
	uint32_t enable;
//	uint32_t irq_enable;
	uint32_t period;
	uint32_t current_value;
};


struct drv_systick_ops_t{
	//void (*irq_enable)(struct drv_systick_t *, uint32_t );
	uint32_t (*close)(struct drv_systick_t *);
	void (*startup)(struct drv_systick_t *);
	void (*shutdown)(struct drv_systick_t *);
	void (*ioctl)(struct drv_systick_t *, uint32_t, unsigned int);
};

struct drv_systick_t{
	int32_t id;
	struct drv_systick_ioctl_t ioctl;
	const struct drv_systick_ops_t *ops;
	void	(*handle_irq)(void);
};

uint32_t drv_systick_open( enum drv_systick_id_t id );
uint32_t drv_systick_close( enum drv_systick_id_t id );
struct drv_systick_ioctl_t drv_systick_ioctl( enum drv_systick_id_t id, uint32_t opt, unsigned int val );

uint32_t drv_systick_register_driver( struct drv_systick_t *systick );


#ifdef __cplusplus
}
#endif

#endif

