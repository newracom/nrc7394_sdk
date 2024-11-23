#ifndef __DRV_SYSCFG_H__
#define __DRV_SYSCFG_H__

#ifdef __cplusplus
extern "C"{
#endif

#define DRV_SYSCFG_IOCTL_OPT_GET											0
#define DRV_SYSCFG_IOCTL_OPT_DEBUG											100
#define DRV_SYSCFG_IOCTL_OPT_TEST_CLOCK_OUTPUT_DIVIDER						102
#define DRV_SYSCFG_IOCTL_OPT_SELECT_32K										103
#define DRV_SYSCFG_IOCTL_OPT_RF_CONTROL										104
#define DRV_SYSCFG_IOCTL_OPT_BOOT_SOURCE									105
#define DRV_SYSCFG_IOCTL_OPT_TESTOUT										106

#define DRV_SYSCFG_IOCTL_OPT_REMAP											201
#define DRV_SYSCFG_IOCTL_OPT_REMAP_AFTER_RESET								202

#define DRV_SYSCFG_IOCTL_OPT_MEMORY_CONFIG_SRAM0							300
#define DRV_SYSCFG_IOCTL_OPT_MEMORY_CONFIG_SRAM1							301
#define DRV_SYSCFG_IOCTL_OPT_MEMORY_CONFIG_SRAM2							302
#define DRV_SYSCFG_IOCTL_OPT_MEMORY_CONFIG_SRAM3							303
#define DRV_SYSCFG_IOCTL_OPT_MEMORY_CONFIG_SRAM4							304
/****************************************************************************/
#define DRV_SYSCFG_IOCTL_OPT_DEBUG_NONE										0
#define DRV_SYSCFG_IOCTL_OPT_DEBUG_JTAG										1
#define DRV_SYSCFG_IOCTL_OPT_DEBUG_SWD										2

#define DRV_SYSCFG_IOCTL_OPT_SELECT_32K_EXTERNAL_XTAL						0
#define DRV_SYSCFG_IOCTL_OPT_SELECT_32K_INTERNAL_LPO						1

#define DRV_SYSCFG_IOCTL_OPT_RF_CONTROL_PHY_SPI								0
#define DRV_SYSCFG_IOCTL_OPT_RF_CONTROL_APB_BUS								1

#define DRV_SYSCFG_IOCTL_OPT_BOOT_SOURCE_CLEAR								0x1F

#define DRV_SYSCFG_IOCTL_OPT_TESTOUT_CLOCK									0
#define DRV_SYSCFG_IOCTL_OPT_TESTOUT_PMU_STATUS								1
#define DRV_SYSCFG_IOCTL_OPT_TESTOUT_PMS_PG									2
#define DRV_SYSCFG_IOCTL_OPT_TESTOUT_MAC_DEBUG0								3
#define DRV_SYSCFG_IOCTL_OPT_TESTOUT_MAC_DEBUG1								4
#define DRV_SYSCFG_IOCTL_OPT_TESTOUT_MAC_DEBUG2								5
#define DRV_SYSCFG_IOCTL_OPT_TESTOUT_GPIO_RESET							0xffff

#define DRV_SYSCFG_IOCTL_OPT_REMAP_XIP										0
#define DRV_SYSCFG_IOCTL_OPT_REMAP_BOOTROM									2
#define DRV_SYSCFG_IOCTL_OPT_REMAP_SRAM										3

/****************************************************************************/

typedef struct DRV_SYSCFG_HANDLE_T*	drv_syscfg_handle_t;
struct drv_syscfg_t;
struct drv_syscfg_ioctl_t;


enum drv_syscfg_id_t{
	drv_syscfg_id0,
	drv_syscfg_id_max,
};

struct drv_syscfg_ops_t{
	int32_t (*close)(struct drv_syscfg_t *);
	int32_t (*ioctl)(struct drv_syscfg_t*, uint32_t, unsigned int);
};

struct drv_syscfg_ioctl_t{
	uint8_t debug;
//	uint8_t sram0;
//	uint8_t sram1;
	uint8_t sram2;
	uint8_t sram3;
	uint8_t remap;
	uint8_t sel_32k;
	uint8_t testout;
	uint8_t remap_after_reset;
	uint8_t rf_control;
	uint8_t testclockdivider_enable;
	uint32_t vendorid;
	uint32_t chipid;
	uint32_t revnr;
	uint32_t bootsrc_por   	: 1;
	uint32_t bootsrc_wdt	: 1;
	uint32_t bootsrc_pmc	: 1;
	uint32_t bootsrc_host	: 1;
	uint32_t bootsrc_cpu	: 1;
};

struct DRV_SYSCFG_HANDLE_T{
	enum drv_syscfg_id_t id;
	struct drv_syscfg_ioctl_t ioctl;
};

struct drv_syscfg_t{
	drv_syscfg_handle_t handle;	
	const struct drv_syscfg_ops_t *ops;
};

/** 
  \brief		syscfg driver open function
  \details		
  \param [in]	id
  \param [in]	handle
  \return		ret
*/
int32_t drv_syscfg_open( enum drv_syscfg_id_t id, drv_syscfg_handle_t *handle );

/** 
  \brief		syscfg driver close function
  \details		
  \param [in]	handle
  \return		ret
*/
int32_t drv_syscfg_close( drv_syscfg_handle_t handle );

/** 
  \brief		syscfg driver input output control function
  \details		critical section
  \param [in]	handle
  \param [in]	opt This parameter can be one or multiple of the following values:
				@arg @ref DRV_SYSCFG_IOCTL_OPT_DEBUG					
				@arg @ref DRV_SYSCFG_IOCTL_OPT_TEST_CLOCK_OUTPUT_DIVIDER
				@arg @ref DRV_SYSCFG_IOCTL_OPT_SELECT_32K				
				@arg @ref DRV_SYSCFG_IOCTL_OPT_RF_CONTROL				
				@arg @ref DRV_SYSCFG_IOCTL_OPT_BOOT_SOURCE				
				@arg @ref DRV_SYSCFG_IOCTL_OPT_TESTOUT					
				@arg @ref DRV_SYSCFG_IOCTL_OPT_REMAP					
				@arg @ref DRV_SYSCFG_IOCTL_OPT_REMAP_AFTER_RESET		
				@arg @ref DRV_SYSCFG_IOCTL_OPT_MEMORY_CONFIG_SRAM0		
				@arg @ref DRV_SYSCFG_IOCTL_OPT_MEMORY_CONFIG_SRAM1		
				@arg @ref DRV_SYSCFG_IOCTL_OPT_MEMORY_CONFIG_SRAM2		
				@arg @ref DRV_SYSCFG_IOCTL_OPT_MEMORY_CONFIG_SRAM3		
				@arg @ref DRV_SYSCFG_IOCTL_OPT_MEMORY_CONFIG_SRAM4		
  \param [in]	val
  \return		ret
*/
int32_t drv_syscfg_ioctl( drv_syscfg_handle_t handle, uint32_t opt, unsigned int val);

/** 
  \brief		syscfg driver registration function
  \details		
  \param [in]	syscfg
  \return		ret
*/
int32_t drv_syscfg_register_driver( struct drv_syscfg_t *syscfg );

#ifdef __cplusplus
}
#endif

#endif

