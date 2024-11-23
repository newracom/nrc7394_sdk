#ifndef __DRV_RTC_H__
#define __DRV_RTC_H__

#ifdef __cplusplus
extern "C"{
#endif

#define DRV_RTC_IOCTL_OPT_GET								0
#define DRV_RTC_IOCTL_OPT_READ_TIME							1
#define DRV_RTC_IOCTL_OPT_SET_TIME							2
#define DRV_RTC_IOCTL_OPT_READ_ALARM						3
#define DRV_RTC_IOCTL_OPT_SET_ALARM							4
#define DRV_RTC_IOCTL_OPT_IRQ_CTRL							5
#define DRV_RTC_IOCTL_OPT_REGISTER_IRQ_HANDLER				6
#define DRV_RTC_IOCTL_OPT_IRQ_FLAG							7
#define DRV_RTC_IOCTL_OPT_READ_OFFSET						8
#define DRV_RTC_IOCTL_OPT_SET_OFFSET						9

#define DRV_RTC_IOCTL_OPT_SET_START_TIME					11
#define DRV_RTC_IOCTL_OPT_SET_START_SECS					12
#define DRV_RTC_IOCTL_OPT_TIMER_MODE						13

/** 
  \brief		RTC timer calculate 1sec = 32768
  				ex) 3sec = 3 * 32768 = 98304
*/
#define DRV_RTC_IOCTL_OPT_TIMER_PERIOD						14
#define DRV_RTC_IOCTL_OPT_SET_TIMER							15
#define DRV_RTC_IOCTL_OPT_STOP_TIMER						16

#define DRV_RTC_IOCTL_OPT_CALIB_START						20
#define DRV_RTC_IOCTL_OPT_CALIB_SET_DURATION				21
#define DRV_RTC_IOCTL_OPT_CALIB_SET_REFCOUNT				22

#define DRV_RTC_IOCTL_OPT_CALIB_IRQ_CTRL					23
#define DRV_RTC_IOCTL_OPT_CALIB_REGISTER_IRQ_HANDLER		24
#define DRV_RTC_IOCTL_OPT_CALIB_IRQ_FLAG					25

#define DRV_RTC_IOCTL_OPT_CALIB_GET_RESULT					30

/******************************************************************************/
#define DRV_RTC_IOCTL_OPT_IRQ_FLAG_RESET					1

#define DRV_RTC_IOCTL_OPT_TIMER_MODE_PERIODIC				0
#define DRV_RTC_IOCTL_OPT_TIMER_MODE_ONESHOT				1

#define DRV_RTC_IOCTL_OPT_CALIB_IRQ_FLAG_RESET				1

enum drv_rtc_id_t{
	drv_rtc_id0,
	drv_rtc_id_max,
};

struct drv_rtc_t;
struct drv_rtc_ops_t;
struct drv_rtc_ioctl_t;
struct drv_rtc_timer_t;

struct drv_rtc_time_t{
	int32_t tm_sec;
	int32_t tm_min;
	int32_t tm_hour;
	int32_t tm_mday;
	int32_t tm_mon;
	int32_t tm_year;
	int32_t tm_wday;
	int32_t tm_yday;
	int32_t tm_isdst;
};

struct drv_rtc_wkalrm_t {
	uint32_t enabled;
	uint32_t pending;
	struct drv_rtc_time_t time;
};

struct drv_rtc_calib_t{
	uint32_t duration;
	uint32_t refcount;
	uint32_t result;
	uint32_t irq_enabled;
};

struct drv_rtc_timer_t{
	uint32_t enabled;
	uint32_t mode;
	uint64_t period;
	void (*func)(struct drv_rtc_t *);
};

struct drv_rtc_ioctl_t{
	struct drv_rtc_timer_t timer;
	struct drv_rtc_calib_t calib;
	uint32_t offset;
	uint32_t irq_enabled;
	uint32_t set_start_time;
	uint64_t start_secs;
	uint64_t raw_current_count;
	uint64_t raw_current_alarm;
	uint32_t irq_flag			: 1;
	uint32_t busy				: 1;
	uint32_t calib_irq_flag		: 1;
	uint32_t calib_busy			: 1;
};


struct drv_rtc_ops_t{
	uint32_t (*close)(struct drv_rtc_t *);
	void (*ioctl)(struct drv_rtc_t *, uint32_t, unsigned int );
	int32_t (*read_time)(struct drv_rtc_t *, struct drv_rtc_time_t *);
	int32_t (*set_time)(struct drv_rtc_t *, struct drv_rtc_time_t *);
	int32_t (*read_alarm)(struct drv_rtc_t *, struct drv_rtc_wkalrm_t *);
	int32_t (*set_alarm)(struct drv_rtc_t *, struct drv_rtc_wkalrm_t *);
	int32_t (*alarm_irq_enable)(struct drv_rtc_t *, uint32_t enabled);
	int32_t (*read_offset)(struct drv_rtc_t *, uint32_t *offset);
	int32_t (*set_offset)(struct drv_rtc_t *, uint32_t offset);
	int32_t (*calib_irq_enable)(struct drv_rtc_t *, uint32_t enabled);
};

struct drv_rtc_t{
	uint32_t id;
	struct drv_rtc_ioctl_t ioctl;
	void (*handle_irq)(void);
	void (*calib_handle_irq)(void);
	const struct drv_rtc_ops_t *ops;
};

/** 
  \brief		rtc driver open function
  \details		
  \param [in]	id
  \return		ret
*/
uint32_t drv_rtc_open(enum drv_rtc_id_t id);


/** 
  \brief		rtc driver close function
  \details		
  \param [in]	id
  \return		ret
*/
uint32_t drv_rtc_close(enum drv_rtc_id_t id);


/** 
  \brief		rtc driver input output control function
  \details		critical section
  \param [in]	id
  \param [in]	opt This parameter can be one or multiple of the following values:
				@arg @ref DRV_RTC_IOCTL_OPT_GET					
				@arg @ref DRV_RTC_IOCTL_OPT_READ_TIME				
				@arg @ref DRV_RTC_IOCTL_OPT_SET_TIME				
				@arg @ref DRV_RTC_IOCTL_OPT_READ_ALARM			
				@arg @ref DRV_RTC_IOCTL_OPT_SET_ALARM				
				@arg @ref DRV_RTC_IOCTL_OPT_IRQ_CTRL				
				@arg @ref DRV_RTC_IOCTL_OPT_REGISTER_IRQ_HANDLER
				@arg @ref DRV_RTC_IOCTL_OPT_IRQ_FLAG				
				@arg @ref DRV_RTC_IOCTL_OPT_READ_OFFSET			
 				@arg @ref DRV_RTC_IOCTL_OPT_SET_OFFSET			
 				@arg @ref DRV_RTC_IOCTL_OPT_CALIBRATION			
 				@arg @ref DRV_RTC_IOCTL_OPT_SET_START_TIME		
 				@arg @ref DRV_RTC_IOCTL_OPT_SET_START_SECS		
 				@arg @ref DRV_RTC_IOCTL_OPT_TIMER_MODE			
 				@arg @ref DRV_RTC_IOCTL_OPT_TIMER_PERIOD			
 				@arg @ref DRV_RTC_IOCTL_OPT_SET_TIMER				
 				@arg @ref DRV_RTC_IOCTL_OPT_STOP_TIMER			
   \param [in]	val
  \return		ret
*/
struct drv_rtc_ioctl_t drv_rtc_ioctl(enum drv_rtc_id_t id, uint32_t opt, unsigned int val);

/** 
  \brief		rtc driver registration function
  \details		
  \param [in]	sfc
  \return		ret
*/
uint32_t drv_rtc_register_driver(struct drv_rtc_t *rtc);

#ifdef __cplusplus
}
#endif

#endif

