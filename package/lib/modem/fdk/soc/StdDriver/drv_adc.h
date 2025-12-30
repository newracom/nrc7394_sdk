#ifndef __DRV_ADC_H__
#define __DRV_ADC_H__

#ifdef __cplusplus
extern "C"{
#endif

#define DRV_ADC_IOCTL_OPT_GET_SETUP							0
#define DRV_ADC_IOCTL_OPT_SHUTDOWN							1
#define DRV_ADC_IOCTL_OPT_STARTUP							2
#define DRV_ADC_IOCTL_OPT_TRIGGER							3

#define DRV_ADC_IOCTL_OPT_SET_CHANNEL						0x100
#define DRV_ADC_IOCTL_OPT_SET_AVERAGE						0x101
#define DRV_ADC_IOCTL_OPT_SET_CLK_INVERSION					0x102
#define DRV_ADC_IOCTL_OPT_SET_CLK							0x103
#define DRV_ADC_IOCTL_OPT_SET_CLK_DIV						0x104

#define DRV_ADC_IOCTL_OPT_SET_GPIO_PIN						0x200

/******************************************************************************/
#define DRV_ADC_IOCTL_OPT_SET_CLK_INVERSION_DISABLE			0
#define DRV_ADC_IOCTL_OPT_SET_CLK_INVERSION_ENABLE			1

#define DRV_ADC_IOCTL_OPT_SET_NO_AVERAGE			0
#define DRV_ADC_IOCTL_OPT_SET_2_AVERAGE			1
#define DRV_ADC_IOCTL_OPT_SET_4_AVERAGE			2
#define DRV_ADC_IOCTL_OPT_SET_8_AVERAGE			3
#define DRV_ADC_IOCTL_OPT_SET_16_AVERAGE			4
#define DRV_ADC_IOCTL_OPT_SET_32_AVERAGE			5
#define DRV_ADC_IOCTL_OPT_SET_64_AVERAGE			6
#define DRV_ADC_IOCTL_OPT_SET_128_AVERAGE			7


#define DRV_ADC_IOCTL_OPT_SET_CLK_MAIN_CRYSTAL_OSC_CLOCK_EXTERNAL			4
#define DRV_ADC_IOCTL_OPT_SET_CLK_SUB_32KHZ_CLOCK_EXTERNAL_INTERNAL			6

enum drv_adc_id_t{
	drv_adc_id0,
	drv_adc_id_max,
};

enum drv_adc_ch_t{
	drv_adc_ch0,
	drv_adc_ch1,
	drv_adc_ch2,
	drv_adc_ch3,
	drv_adc_ch_max,
};

struct drv_adc_t;
struct drv_adc_ops_t;
struct drv_adc_ioctl_t;
struct drv_adc_gpio_t;

struct drv_adc_gpio_t{
	uint32_t group : 16;
	uint32_t pin : 16;
};

struct drv_adc_ioctl_t{
	uint32_t channel;
	uint32_t average;
	uint32_t clk_inversion;
	uint32_t clk;
	uint32_t clk_div;
	struct drv_adc_gpio_t gpio[drv_adc_ch_max];
};

struct drv_adc_t{
	uint32_t id;
	struct drv_adc_ioctl_t ioctl;
	const struct drv_adc_ops_t *ops;
};

struct drv_adc_ops_t{
	uint32_t (*close)(struct drv_adc_t *);
	void (*startup)(struct drv_adc_t * );
	void (*shutdown)(struct drv_adc_t *);
	void (*trigger)(struct drv_adc_t * );
	uint32_t (*read)(struct drv_adc_t *, uint32_t *);
	void (*ioctl)(struct drv_adc_t *, uint32_t , unsigned int );
};

/**
  \brief		adc driver open function
  \details
  \param [in]	id
  \return		ret
*/
uint32_t drv_adc_open(enum drv_adc_id_t id);

/**
  \brief		adc driver close function
  \details
  \param [in]	id
  \return		ret
*/
uint32_t drv_adc_close(enum drv_adc_id_t id);

/**
  \brief		adc driver read function
  \details
  \param [in]	id
  \param [in]	dat
  \return		ret
*/
uint32_t drv_adc_read(enum drv_adc_id_t id, uint32_t *dat);

/**
  \brief		adc driver input output control function
  \details		critical section
  \param [in]	id
  \param [in]	opt This parameter can be one or multiple of the following values:
				@arg @ref DRV_ADC_IOCTL_OPT_GET_SETUP
				@arg @ref DRV_ADC_IOCTL_OPT_SHUTDOWN
				@arg @ref DRV_ADC_IOCTL_OPT_STARTUP
				@arg @ref DRV_ADC_IOCTL_OPT_TRIGGER
				@arg @ref DRV_ADC_IOCTL_OPT_SET_CHANNEL
				@arg @ref DRV_ADC_IOCTL_OPT_SET_AVERAGE
				@arg @ref DRV_ADC_IOCTL_OPT_SET_CLK_INVERSION
				@arg @ref DRV_ADC_IOCTL_OPT_SET_CLK
				@arg @ref DRV_ADC_IOCTL_OPT_SET_CLK_DIV
				@arg @ref DRV_ADC_IOCTL_OPT_SET_GPIO_PIN
  \param [in]	val
  \return		ret
*/
struct drv_adc_ioctl_t drv_adc_ioctl(enum drv_adc_id_t id, uint32_t opt, unsigned int val);

/**
  \brief		adc driver registration function
  \details
  \param [in]	adc
  \return		ret
*/
uint32_t drv_adc_register_driver( struct drv_adc_t * adc);

#ifdef __cplusplus
}
#endif

#endif
