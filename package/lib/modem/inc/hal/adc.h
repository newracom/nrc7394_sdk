#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
extern "C"{
#endif

#define ADC_IOCTL_OPT_GET_SETUP							0
#define ADC_IOCTL_OPT_SHUTDOWN							1
#define ADC_IOCTL_OPT_STARTUP							2
#define ADC_IOCTL_OPT_TRIGGER							3

#define ADC_IOCTL_OPT_SET_CHANNEL						0x100
#define ADC_IOCTL_OPT_SET_AVERAGE						0x101
#define ADC_IOCTL_OPT_SET_CLK_INVERSION					0x102
#define ADC_IOCTL_OPT_SET_CLK							0x103
#define ADC_IOCTL_OPT_SET_CLK_DIV						0x104

#define ADC_IOCTL_OPT_SET_GPIO_PIN						0x200

/******************************************************************************/
#define ADC_IOCTL_OPT_SET_CLK_INVERSION_DISABLE			0
#define ADC_IOCTL_OPT_SET_CLK_INVERSION_ENABLE			1


enum adc_ch_t{
	adc_ch0,
	adc_ch1,
	adc_ch2,
	adc_ch3,
	adc_ch_max,
};

enum adc_id_t{
	adc_id0,
	adc_id_max,
};

struct adc_t;
struct adc_ops_t;
struct adc_ioctl_t;
struct adc_gpio_t;

struct adc_gpio_t{
	uint32_t group : 16;
	uint32_t pin : 16;
};

struct adc_ioctl_t{
	uint32_t channel;
	uint32_t average;
	uint32_t clk_inversion;
	uint32_t clk;
	uint32_t clk_div;
	struct adc_gpio_t gpio[adc_ch_max];
};

struct adc_t{
	uint32_t id;
	struct adc_ioctl_t ioctl;
	const struct adc_ops_t *ops;
};

struct adc_ops_t{
	void (*startup)(struct adc_t * );
	void (*shutdown)(struct adc_t *);
	void (*trigger)(struct adc_t * );
	uint32_t (*read)(struct adc_t *, uint32_t *dat);
	void (*ioctl)(struct adc_t *, uint32_t opt, uint32_t val);
};


uint32_t adc_open(enum adc_id_t id);
uint32_t adc_read(enum adc_id_t id, uint32_t *dat);
struct adc_ioctl_t adc_ioctl(enum adc_id_t id, uint32_t opt, uint32_t val);

uint32_t adc_register_driver( struct adc_t *adc );

#ifdef __cplusplus
}
#endif

#endif

