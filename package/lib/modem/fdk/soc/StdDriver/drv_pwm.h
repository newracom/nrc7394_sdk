#ifndef __DRV_PWM_H__
#define __DRV_PWM_H__

#ifdef __cplusplus
extern "C"{
#endif

enum drv_pwm_id_t{
	drv_pwm_id0,
	drv_pwm_id_max,
};

enum drv_pwm_channel_t{
	drv_pwm_channel0,
	drv_pwm_channel1,
	drv_pwm_channel2,
	drv_pwm_channel3,
	drv_pwm_channel_max,
};

struct drv_pwm_t;
struct drv_pwm_ioctl_t;
struct drv_pwm_ops_t;
struct drv_pwm_gpio_t;


struct drv_pwm_gpio_t{
	uint32_t group : 16;
	uint32_t pin : 16;
};


struct drv_pwm_ioctl_t{
	int32_t enable[drv_pwm_channel_max];
	int32_t triger[drv_pwm_channel_max];
	uint32_t inversion[drv_pwm_channel_max];
	uint32_t clk_div[drv_pwm_channel_max];
	uint32_t mode[drv_pwm_channel_max];
	uint32_t loop[drv_pwm_channel_max];
	uint32_t duty[drv_pwm_channel_max];
	uint32_t frequency[drv_pwm_channel_max];
	uint32_t pattern0[drv_pwm_channel_max];
	uint32_t pattern1[drv_pwm_channel_max];
	uint32_t pattern2[drv_pwm_channel_max];
	uint32_t pattern3[drv_pwm_channel_max];
	struct drv_pwm_gpio_t gpio[drv_pwm_channel_max];

	uint32_t busy_ch0 : 1;
	uint32_t busy_ch1 : 1;
	uint32_t busy_ch2 : 1;
	uint32_t busy_ch3 : 1;
};


struct drv_pwm_ops_t{
	void (*ioctl)( struct drv_pwm_t *, uint32_t, unsigned int );
};


struct drv_pwm_t{
	int32_t id;
	const struct drv_pwm_ops_t *ops;
	struct drv_pwm_ioctl_t ioctl;
};

uint32_t drv_pwm_open( enum drv_pwm_id_t id );
struct drv_pwm_ioctl_t drv_pwm_ioctl( enum drv_pwm_id_t id, uint32_t ops, unsigned int val);

uint32_t drv_pwm_register_driver( struct drv_pwm_t *pwm );


#ifdef __cplusplus
}
#endif

#endif

