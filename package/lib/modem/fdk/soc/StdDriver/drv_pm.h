#ifndef __DRV_PM_H__
#define __DRV_PM_H__

#ifdef __cplusplus
extern "C"{
#endif

#define DRV_PM_IOCTL_OPT_GET									0
#define DRV_PM_IOCTL_OPT_PREPARE								1
#define DRV_PM_IOCTL_OPT_ENTER									2
#define DRV_PM_IOCTL_OPT_SLEEP_MODE								3
#define DRV_PM_IOCTL_OPT_CTRL_MODE								4
#define DRV_PM_IOCTL_OPT_REGISTER_IRQ_HANDLER					5
#define DRV_PM_IOCTL_OPT_IRQ_CTRL								6

#define DRV_PM_IOCTL_OPT_PWR_STATUS_SRAM0						0x100
#define DRV_PM_IOCTL_OPT_PWR_STATUS_SRAM1						0x101
#define DRV_PM_IOCTL_OPT_PWR_STATUS_SRAM2						0x102

#define DRV_PM_IOCTL_OPT_PWR_STATUS_RET_MEM0					0x200
#define DRV_PM_IOCTL_OPT_PWR_STATUS_RET_MEM1					0x201
#define DRV_PM_IOCTL_OPT_PWR_STATUS_RET_MEM2					0x202
#define DRV_PM_IOCTL_OPT_PWR_STATUS_RET_MEM3					0x203

#define DRV_PM_IOCTL_OPT_WKSRC_RTC								0x300

#define DRV_PM_IOCTL_OPT_WKSRC_EINT0							0x301
#define DRV_PM_IOCTL_OPT_WKSRC_EINT1							0x302
#define DRV_PM_IOCTL_OPT_WKSRC_EINT2							0x303
#define DRV_PM_IOCTL_OPT_WKSRC_EINT3							0x304

#define DRV_PM_IOCTL_OPT_WKSRC_EINT0_POLARITY					0x400
#define DRV_PM_IOCTL_OPT_WKSRC_EINT1_POLARITY					0x401
#define DRV_PM_IOCTL_OPT_WKSRC_EINT2_POLARITY					0x402
#define DRV_PM_IOCTL_OPT_WKSRC_EINT3_POLARITY					0x403

#define DRV_PM_IOCTL_OPT_FLAG_PMU_IRQ							0x500

#define DRV_PM_IOCTL_OPT_FLAG_WK_SRC_RTC						0x510

#define DRV_PM_IOCTL_OPT_FLAG_WK_SRC_EXT_INT0					0x520
#define DRV_PM_IOCTL_OPT_FLAG_WK_SRC_EXT_INT1					0x521
#define DRV_PM_IOCTL_OPT_FLAG_WK_SRC_EXT_INT2					0x522
#define DRV_PM_IOCTL_OPT_FLAG_WK_SRC_EXT_INT3					0x523

#define DRV_PM_IOCTL_OPT_FLAG_WK_SRC_SBR						0x530

/** 
  \brief		wait time calculate
  \details		Caculation to wait time 500 usec :
     - 500 / 31.25  = 16 -> Set register value 0x10 
     - Default value 0x10 -> 16 x 31.25 usec = 500 usec
*/
#define DRV_PM_IOCTL_OPT_DCDC2PSW_WAIT_TIME						0x600
#define DRV_PM_IOCTL_OPT_MXTAL_WAIT_TIME						0x601
#define DRV_PM_IOCTL_OPT_SXTAL_WAIT_TIME						0x602

#define DRV_PM_IOCTL_OPT_RFOFF									0x603
#define DRV_PM_IOCTL_OPT_LPO16MOFF								0x604
#define DRV_PM_IOCTL_OPT_SXTALOFF								0x605
#define DRV_PM_IOCTL_OPT_RF_ISO_EN								0x606

#define DRV_PM_IOCTL_OPT_GET_XTAL32K_FOK						0x607

/******************************************************************************/

#define DRV_PM_IOCTL_OPT_SLEEPMODE_NULL							0
#define DRV_PM_IOCTL_OPT_SLEEPMODE_SLEEP0						1
#define DRV_PM_IOCTL_OPT_SLEEPMODE_SLEEP1						2
#define DRV_PM_IOCTL_OPT_SLEEPMODE_SLEEP2						3
#define DRV_PM_IOCTL_OPT_SLEEPMODE_DEEPSLEEP0					4
#define DRV_PM_IOCTL_OPT_SLEEPMODE_DEEPSLEEP1					5

#define DRV_PM_IOCTL_OPT_CTRL_MODE_AUTO							0
#define DRV_PM_IOCTL_OPT_CTRL_MODE_MANUAL						1

#define DRV_PM_IOCTL_OPT_PWR_STATUS_RETENTION					1
#define DRV_PM_IOCTL_OPT_PWR_STATUS_DOWN						2
#define DRV_PM_IOCTL_OPT_PWR_STATUS_NORMAL						3

#define DRV_PM_IOCTL_OPT_WKSRC_DISABLE							1
#define DRV_PM_IOCTL_OPT_WKSRC_ENABLE							0

#define DRV_PM_IOCTL_OPT_WK_SRC_FLAG_RESET						1

#define DRV_PM_IOCTL_OPT_WKSRC_EINT_POLARITY_ACT_LOW			0
#define DRV_PM_IOCTL_OPT_WKSRC_EINT_POLARITY_ACT_HIGH			1

enum drv_pm_id_t{
	drv_pm_id0,
	drv_pm_id_max,
};

struct drv_pm_t;
struct drv_pm_ops_t;
struct drv_pm_ioctl_t;

enum drv_pm_wakeup_gpio_t{
	drv_pm_wksrc_ext_int0,
	drv_pm_wksrc_ext_int1,
	drv_pm_wksrc_ext_int2,
	drv_pm_wksrc_ext_int3,
	drv_pm_wksrc_ext_int_max,
};

struct drv_pm_pswitch_t{
	uint32_t sram0;
	uint32_t sram1;
	uint32_t retention_mem0;
	uint32_t retention_mem1;
	uint32_t retention_mem2;
	uint32_t sbr_mac_mem;
};

struct drv_pm_wksrc_t{
	uint32_t hspi;
	uint32_t rtc;
	uint32_t timeout;
	uint32_t ext_int[drv_pm_wksrc_ext_int_max];
	uint32_t ext_int_polarity[drv_pm_wksrc_ext_int_max];
};

struct drv_pm_ioctl_t{
	uint32_t enable;
	uint32_t irq_enable;
	uint32_t sleepmode;
	uint32_t ctrl_mode;
	uint32_t rfoff;
	uint32_t lpo16moff;
	uint32_t sxtaloff;
	uint32_t rf_iso_en;
	uint32_t dcdc2psw_wait_time;
	uint32_t mxtal_wait_time;
	uint32_t sxtal_wait_time;
	struct drv_pm_wksrc_t wksrc;
	struct drv_pm_pswitch_t pswitch;
	uint32_t sleepmode_log;	
	uint32_t xtal32k_fok : 1;
	uint32_t wksrc_flag_rtc		: 1;
	uint32_t wksrc_flag_ext_int0	: 1;
	uint32_t wksrc_flag_ext_int1	: 1;
	uint32_t wksrc_flag_ext_int2	: 1;
	uint32_t wksrc_flag_ext_int3	: 1;
	uint32_t wksrc_flag_host : 1;
	uint32_t wksrc_flag_sbr : 1;
	uint32_t irq_flag		: 1;
};

struct drv_pm_ops_t{
	uint32_t (*close)(struct drv_pm_t *);
	void (*irq_enable)(struct drv_pm_t *, uint32_t );
	void (*prepare)(struct drv_pm_t * );
	void (*enter)(struct drv_pm_t * );
	void (*ioctl)(struct drv_pm_t * , uint32_t, unsigned int );
};

struct drv_pm_t{
	int32_t id;
	struct drv_pm_ioctl_t ioctl;
	const struct drv_pm_ops_t *ops;
	void (*handle_irq)(void);
};

/** 
  \brief		power management driver open function
  \details		
  \param [in]	id
  \return		ret
*/
uint32_t drv_pm_open(enum drv_pm_id_t id);

/** 
  \brief		power management driver close function
  \details		
  \param [in]	id
  \return		ret
*/
uint32_t drv_pm_close(enum drv_pm_id_t id);

/** 
  \brief		power management driver input output control function
  \details		critical section
  \param [in]	id
  \param [in]	opt This parameter can be one or multiple of the following values:
				@arg @ref DRV_PM_IOCTL_OPT_GET				
				@arg @ref DRV_PM_IOCTL_OPT_PREPARE			
				@arg @ref DRV_PM_IOCTL_OPT_ENTER				
				@arg @ref DRV_PM_IOCTL_OPT_SLEEP_MODE			
				@arg @ref DRV_PM_IOCTL_OPT_CTRL_MODE			
				@arg @ref DRV_PM_IOCTL_OPT_REGISTER_IRQ_HANDLER
				@arg @ref DRV_PM_IOCTL_OPT_IRQ_CTRL			
				@arg @ref DRV_PM_IOCTL_OPT_PWR_STATUS_SRAM0	
				@arg @ref DRV_PM_IOCTL_OPT_PWR_STATUS_SRAM1	
 				@arg @ref DRV_PM_IOCTL_OPT_PWR_STATUS_SRAM2	
 				@arg @ref DRV_PM_IOCTL_OPT_PWR_STATUS_RET_MEM0
 				@arg @ref DRV_PM_IOCTL_OPT_PWR_STATUS_RET_MEM1
 				@arg @ref DRV_PM_IOCTL_OPT_PWR_STATUS_RET_MEM2
 				@arg @ref DRV_PM_IOCTL_OPT_PWR_STATUS_RET_MEM3
 				@arg @ref DRV_PM_IOCTL_OPT_WKSRC_RTC			
 				@arg @ref DRV_PM_IOCTL_OPT_WKSRC_EINT0		
 				@arg @ref DRV_PM_IOCTL_OPT_WKSRC_EINT1		
 				@arg @ref DRV_PM_IOCTL_OPT_WKSRC_EINT2		
 				@arg @ref DRV_PM_IOCTL_OPT_WKSRC_EINT3		
 				@arg @ref DRV_PM_IOCTL_OPT_WKSRC_EINT0_POLARITY
 				@arg @ref DRV_PM_IOCTL_OPT_WKSRC_EINT1_POLARITY
 				@arg @ref DRV_PM_IOCTL_OPT_WKSRC_EINT2_POLARITY
 				@arg @ref DRV_PM_IOCTL_OPT_WKSRC_EINT3_POLARITY
 				@arg @ref DRV_PM_IOCTL_OPT_FLAG_PMU_IRQ						
 				@arg @ref DRV_PM_IOCTL_OPT_FLAG_WK_SRC_RTC	
 				@arg @ref DRV_PM_IOCTL_OPT_FLAG_WK_SRC_EXT_INT0
 				@arg @ref DRV_PM_IOCTL_OPT_FLAG_WK_SRC_EXT_INT1
 				@arg @ref DRV_PM_IOCTL_OPT_FLAG_WK_SRC_EXT_INT2
 				@arg @ref DRV_PM_IOCTL_OPT_FLAG_WK_SRC_EXT_INT3
 				@arg @ref DRV_PM_IOCTL_OPT_DCDC2PSW_WAIT_TIME	
   \param [in]	val
  \return		ret
*/
struct drv_pm_ioctl_t drv_pm_ioctl(enum drv_pm_id_t id, uint32_t opt, unsigned int val);

/** 
  \brief		power management driver registration function
  \details		
  \param [in]	pm
  \return		ret
*/
uint32_t drv_pm_register_driver( struct drv_pm_t *pm );


#ifdef __cplusplus
}
#endif

#endif

