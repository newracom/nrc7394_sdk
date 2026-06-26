#ifndef __DRV_PWM_H__
#define __DRV_PWM_H__

#ifdef __cplusplus
extern "C"{
#endif

#define DRV_PWM_IOCTL_OPT_GET												0
#define DRV_PWM_IOCTL_OPT_RESET												1

#define DRV_PWM_IOCTL_OPT_CH0_STARTUP										10
#define DRV_PWM_IOCTL_OPT_CH1_STARTUP										11
#define DRV_PWM_IOCTL_OPT_CH2_STARTUP										12
#define DRV_PWM_IOCTL_OPT_CH3_STARTUP										13

#define DRV_PWM_IOCTL_OPT_CH0_SHUTDOWN										20
#define DRV_PWM_IOCTL_OPT_CH1_SHUTDOWN										21
#define DRV_PWM_IOCTL_OPT_CH2_SHUTDOWN										22
#define DRV_PWM_IOCTL_OPT_CH3_SHUTDOWN										23

#define DRV_PWM_IOCTL_OPT_CH0_APPLY											30
#define DRV_PWM_IOCTL_OPT_CH1_APPLY											31
#define DRV_PWM_IOCTL_OPT_CH2_APPLY											32
#define DRV_PWM_IOCTL_OPT_CH3_APPLY											33

#define DRV_PWM_IOCTL_OPT_CH0_INVERSION										40
#define DRV_PWM_IOCTL_OPT_CH1_INVERSION										41
#define DRV_PWM_IOCTL_OPT_CH2_INVERSION										42
#define DRV_PWM_IOCTL_OPT_CH3_INVERSION										43

#define DRV_PWM_IOCTL_OPT_CH0_MODE											50
#define DRV_PWM_IOCTL_OPT_CH1_MODE											51
#define DRV_PWM_IOCTL_OPT_CH2_MODE											52
#define DRV_PWM_IOCTL_OPT_CH3_MODE											53

#define DRV_PWM_IOCTL_OPT_CH0_LOOP											60
#define DRV_PWM_IOCTL_OPT_CH1_LOOP											61
#define DRV_PWM_IOCTL_OPT_CH2_LOOP											62
#define DRV_PWM_IOCTL_OPT_CH3_LOOP											63

#define DRV_PWM_IOCTL_OPT_CH0_DUTY0											70
#define DRV_PWM_IOCTL_OPT_CH1_DUTY0											71
#define DRV_PWM_IOCTL_OPT_CH2_DUTY0											72
#define DRV_PWM_IOCTL_OPT_CH3_DUTY0											73

#define DRV_PWM_IOCTL_OPT_CH0_FREQUENCY0									80
#define DRV_PWM_IOCTL_OPT_CH1_FREQUENCY0									81
#define DRV_PWM_IOCTL_OPT_CH2_FREQUENCY0									82
#define DRV_PWM_IOCTL_OPT_CH3_FREQUENCY0									83

#define DRV_PWM_IOCTL_OPT_CH0_DUTY1											90
#define DRV_PWM_IOCTL_OPT_CH1_DUTY1											91
#define DRV_PWM_IOCTL_OPT_CH2_DUTY1											92
#define DRV_PWM_IOCTL_OPT_CH3_DUTY1											93

#define DRV_PWM_IOCTL_OPT_CH0_FREQUENCY1									100
#define DRV_PWM_IOCTL_OPT_CH1_FREQUENCY1									101
#define DRV_PWM_IOCTL_OPT_CH2_FREQUENCY1									102
#define DRV_PWM_IOCTL_OPT_CH3_FREQUENCY1									103

#define DRV_PWM_IOCTL_OPT_CH0_SET_GPIO										110
#define DRV_PWM_IOCTL_OPT_CH1_SET_GPIO										111
#define DRV_PWM_IOCTL_OPT_CH2_SET_GPIO										112
#define DRV_PWM_IOCTL_OPT_CH3_SET_GPIO										113

#define DRV_PWM_IOCTL_OPT_CH0_OUT_REG_PATTERN0								120
#define DRV_PWM_IOCTL_OPT_CH0_OUT_REG_PATTERN1								121
#define DRV_PWM_IOCTL_OPT_CH0_OUT_REG_PATTERN2								122
#define DRV_PWM_IOCTL_OPT_CH0_OUT_REG_PATTERN3								123

#define DRV_PWM_IOCTL_OPT_CH1_OUT_REG_PATTERN0								130
#define DRV_PWM_IOCTL_OPT_CH1_OUT_REG_PATTERN1								131
#define DRV_PWM_IOCTL_OPT_CH1_OUT_REG_PATTERN2								132
#define DRV_PWM_IOCTL_OPT_CH1_OUT_REG_PATTERN3								133

#define DRV_PWM_IOCTL_OPT_CH2_OUT_REG_PATTERN0								140
#define DRV_PWM_IOCTL_OPT_CH2_OUT_REG_PATTERN1								141
#define DRV_PWM_IOCTL_OPT_CH2_OUT_REG_PATTERN2								142
#define DRV_PWM_IOCTL_OPT_CH2_OUT_REG_PATTERN3								143

#define DRV_PWM_IOCTL_OPT_CH3_OUT_REG_PATTERN0								150
#define DRV_PWM_IOCTL_OPT_CH3_OUT_REG_PATTERN1								151
#define DRV_PWM_IOCTL_OPT_CH3_OUT_REG_PATTERN2								152
#define DRV_PWM_IOCTL_OPT_CH3_OUT_REG_PATTERN3								153

#define DRV_PWM_IOCTL_OPT_CH0_TRIGGER										160
#define DRV_PWM_IOCTL_OPT_CH1_TRIGGER										161
#define DRV_PWM_IOCTL_OPT_CH2_TRIGGER										162
#define DRV_PWM_IOCTL_OPT_CH3_TRIGGER										163

#define DRV_PWM_IOCTL_OPT_CH0_CLOCK_DIV										170
#define DRV_PWM_IOCTL_OPT_CH1_CLOCK_DIV										171
#define DRV_PWM_IOCTL_OPT_CH2_CLOCK_DIV										172
#define DRV_PWM_IOCTL_OPT_CH3_CLOCK_DIV										173

/******************************************************************************/
#define DRV_PWM_IOCTL_OPT_MODE_PHASE										1
#define DRV_PWM_IOCTL_OPT_MODE_PHASE2										9
#define DRV_PWM_IOCTL_OPT_MODE_REGISTER_OUT									2
#define DRV_PWM_IOCTL_OPT_MODE_REGISTER_OUT2								4

#define DRV_PWM_IOCTL_OPT_INVERSION_DISABLE									0
#define DRV_PWM_IOCTL_OPT_INVERSION_ENABLE									1

#define DRV_PWM_IOCTL_OPT_CLOCK_DIV_2										0
#define DRV_PWM_IOCTL_OPT_CLOCK_DIV_4										1
#define DRV_PWM_IOCTL_OPT_CLOCK_DIV_8										2
#define DRV_PWM_IOCTL_OPT_CLOCK_DIV_16										3

#define DRV_PWM_IOCTL_OPT_LOOP_ENABLE										0
#define DRV_PWM_IOCTL_OPT_LOOP_DISABLE										1

#define DRV_PWM_IOCTL_OPT_CH0_SET_GPIO_RESET							0xffff
/****************************************************************************/

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


typedef struct DRV_PWM_HANDLE_T * drv_pwm_handle_t;

struct drv_pwm_t;
struct drv_pwm_ioctl_t;
struct drv_pwm_state_t;
struct drv_pwm_ops_t;
struct drv_pwm_gpio_t;


struct drv_pwm_gpio_t{
	uint32_t group : 16;
	uint32_t pin : 16;
};

struct drv_pwm_state_t{
	int8_t trigger;
	uint8_t inversion;
	uint8_t mode;
	uint8_t loop;
	uint32_t clk_div;
	uint32_t duty0;
	uint32_t frequency0;
	uint32_t duty1;
	uint32_t frequency1;
	uint32_t pattern0;
	uint32_t pattern1;
	uint32_t pattern2;
	uint32_t pattern3;
};

union drv_pwm_ioctl_flag_u{
	uint32_t w;
	struct{
	uint32_t busy_ch0 : 1;
	uint32_t busy_ch1 : 1;
	uint32_t busy_ch2 : 1;
	uint32_t busy_ch3 : 1;
	}b;
};

struct drv_pwm_ioctl_t{
	uint32_t clk;
	uint32_t clk_div;
	int8_t enable[drv_pwm_channel_max];
	struct drv_pwm_gpio_t gpio[drv_pwm_channel_max];
	struct drv_pwm_state_t state[drv_pwm_channel_max];
	struct drv_pwm_state_t last[drv_pwm_channel_max];
	union drv_pwm_ioctl_flag_u flag;
};

struct DRV_PWM_HANDLE_T{
	enum drv_pwm_id_t id;
	struct drv_pwm_ioctl_t ioctl;
};

struct drv_pwm_ops_t{
	int32_t (*close)(struct drv_pwm_t *);
	int32_t (*reset)(struct drv_pwm_t *);
	int32_t (*ioctl)( struct drv_pwm_t *, uint32_t, unsigned int );
	int32_t (*apply)( struct drv_pwm_t * , uint32_t );
	int32_t (*startup)(struct drv_pwm_t *, uint32_t );
	void (*shutdown)(struct drv_pwm_t *, uint32_t );
};


struct drv_pwm_t{
	drv_pwm_handle_t handle;
	const struct drv_pwm_ops_t *ops;
};

/**
  \brief		pwm driver open function
  \details
  \param [in]	id
  \param [in]	handle
  \return		ret
*/
int32_t drv_pwm_open( enum drv_pwm_id_t id , drv_pwm_handle_t *handle);

/**
  \brief		pwm driver close function
  \details
  \param [in]	handle
  \return		ret
*/
int32_t drv_pwm_close( drv_pwm_handle_t handle );

/**
  \brief		pwm driver input output control function
  \details		critical section
  \param [in]	handle
  \param [in]	opt This parameter can be one or multiple of the following values:
				@arg @ref DRV_PWM_IOCTL_OPT_GET												0
				@arg @ref DRV_PWM_IOCTL_OPT_CH0_STARTUP										10
				@arg @ref DRV_PWM_IOCTL_OPT_CH1_STARTUP										11
				@arg @ref DRV_PWM_IOCTL_OPT_CH2_STARTUP										12
				@arg @ref DRV_PWM_IOCTL_OPT_CH3_STARTUP										13
				@arg @ref DRV_PWM_IOCTL_OPT_CH0_SHUTDOWN										20
				@arg @ref DRV_PWM_IOCTL_OPT_CH1_SHUTDOWN										21
				@arg @ref DRV_PWM_IOCTL_OPT_CH2_SHUTDOWN										22
				@arg @ref DRV_PWM_IOCTL_OPT_CH3_SHUTDOWN										23
				@arg @ref DRV_PWM_IOCTL_OPT_CH0_APPLY											30
				@arg @ref DRV_PWM_IOCTL_OPT_CH1_APPLY											31
				@arg @ref DRV_PWM_IOCTL_OPT_CH2_APPLY											32
				@arg @ref DRV_PWM_IOCTL_OPT_CH3_APPLY											33
				@arg @ref DRV_PWM_IOCTL_OPT_CH0_INVERSION										40
				@arg @ref DRV_PWM_IOCTL_OPT_CH1_INVERSION										41
				@arg @ref DRV_PWM_IOCTL_OPT_CH2_INVERSION										42
				@arg @ref DRV_PWM_IOCTL_OPT_CH3_INVERSION										43
				@arg @ref DRV_PWM_IOCTL_OPT_CH0_MODE											50
				@arg @ref DRV_PWM_IOCTL_OPT_CH1_MODE											51
				@arg @ref DRV_PWM_IOCTL_OPT_CH2_MODE											52
				@arg @ref DRV_PWM_IOCTL_OPT_CH3_MODE											53
				@arg @ref DRV_PWM_IOCTL_OPT_CH0_LOOP											60
				@arg @ref DRV_PWM_IOCTL_OPT_CH1_LOOP											61
				@arg @ref DRV_PWM_IOCTL_OPT_CH2_LOOP											62
				@arg @ref DRV_PWM_IOCTL_OPT_CH3_LOOP											63
				@arg @ref DRV_PWM_IOCTL_OPT_CH0_DUTY0											70
				@arg @ref DRV_PWM_IOCTL_OPT_CH1_DUTY0											71
				@arg @ref DRV_PWM_IOCTL_OPT_CH2_DUTY0											72
				@arg @ref DRV_PWM_IOCTL_OPT_CH3_DUTY0											73
				@arg @ref DRV_PWM_IOCTL_OPT_CH0_FREQUENCY0									80
				@arg @ref DRV_PWM_IOCTL_OPT_CH1_FREQUENCY0									81
				@arg @ref DRV_PWM_IOCTL_OPT_CH2_FREQUENCY0									82
				@arg @ref DRV_PWM_IOCTL_OPT_CH3_FREQUENCY0									83
				@arg @ref DRV_PWM_IOCTL_OPT_CH0_DUTY1											90
				@arg @ref DRV_PWM_IOCTL_OPT_CH1_DUTY1											91
				@arg @ref DRV_PWM_IOCTL_OPT_CH2_DUTY1											92
				@arg @ref DRV_PWM_IOCTL_OPT_CH3_DUTY1											93
				@arg @ref DRV_PWM_IOCTL_OPT_CH0_FREQUENCY1									100
				@arg @ref DRV_PWM_IOCTL_OPT_CH1_FREQUENCY1									101
				@arg @ref DRV_PWM_IOCTL_OPT_CH2_FREQUENCY1									102
				@arg @ref DRV_PWM_IOCTL_OPT_CH3_FREQUENCY1									103
				@arg @ref DRV_PWM_IOCTL_OPT_CH0_SET_GPIO										110
				@arg @ref DRV_PWM_IOCTL_OPT_CH1_SET_GPIO										111
				@arg @ref DRV_PWM_IOCTL_OPT_CH2_SET_GPIO										112
				@arg @ref DRV_PWM_IOCTL_OPT_CH3_SET_GPIO										113
				@arg @ref DRV_PWM_IOCTL_OPT_CH0_OUT_REG_PATTERN0								120
				@arg @ref DRV_PWM_IOCTL_OPT_CH0_OUT_REG_PATTERN1								121
				@arg @ref DRV_PWM_IOCTL_OPT_CH0_OUT_REG_PATTERN2								122
				@arg @ref DRV_PWM_IOCTL_OPT_CH0_OUT_REG_PATTERN3								123
				@arg @ref DRV_PWM_IOCTL_OPT_CH1_OUT_REG_PATTERN0								130
				@arg @ref DRV_PWM_IOCTL_OPT_CH1_OUT_REG_PATTERN1								131
				@arg @ref DRV_PWM_IOCTL_OPT_CH1_OUT_REG_PATTERN2								132
				@arg @ref DRV_PWM_IOCTL_OPT_CH1_OUT_REG_PATTERN3								133
				@arg @ref DRV_PWM_IOCTL_OPT_CH2_OUT_REG_PATTERN0								140
				@arg @ref DRV_PWM_IOCTL_OPT_CH2_OUT_REG_PATTERN1								141
				@arg @ref DRV_PWM_IOCTL_OPT_CH2_OUT_REG_PATTERN2								142
				@arg @ref DRV_PWM_IOCTL_OPT_CH2_OUT_REG_PATTERN3								143
				@arg @ref DRV_PWM_IOCTL_OPT_CH3_OUT_REG_PATTERN0								150
				@arg @ref DRV_PWM_IOCTL_OPT_CH3_OUT_REG_PATTERN1								151
				@arg @ref DRV_PWM_IOCTL_OPT_CH3_OUT_REG_PATTERN2								152
				@arg @ref DRV_PWM_IOCTL_OPT_CH3_OUT_REG_PATTERN3								153
				@arg @ref DRV_PWM_IOCTL_OPT_CH0_TRIGGER										160
				@arg @ref DRV_PWM_IOCTL_OPT_CH1_TRIGGER										161
				@arg @ref DRV_PWM_IOCTL_OPT_CH2_TRIGGER										162
				@arg @ref DRV_PWM_IOCTL_OPT_CH3_TRIGGER										163
				@arg @ref DRV_PWM_IOCTL_OPT_CH0_CLOCK_DIV										170
				@arg @ref DRV_PWM_IOCTL_OPT_CH1_CLOCK_DIV										171
				@arg @ref DRV_PWM_IOCTL_OPT_CH2_CLOCK_DIV										172
				@arg @ref DRV_PWM_IOCTL_OPT_CH3_CLOCK_DIV										173
   \param [in]	val
  \return		ret
*/
int32_t drv_pwm_ioctl( drv_pwm_handle_t handle, uint32_t ops, unsigned int val);

/**
  \brief		pwm driver registration function
  \details
  \param [in]	pwm
  \return		ret
*/
int32_t drv_pwm_register_driver( struct drv_pwm_t *pwm );


#ifdef __cplusplus
}
#endif

#endif

