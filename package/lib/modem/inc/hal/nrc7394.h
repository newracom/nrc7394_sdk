 /**************************************************************************//**
 * @file     nrc7394.h
 * @brief    CMSIS Core Peripheral Access Layer Header File for
 *           NRC7394 Device
 * @version  V1.0.0
 * @date     03. Dec 2021
 ******************************************************************************/
/*
 * Copyright (c) 2021 Newracom Inc. All rights reserved.
 */

#ifndef __NRC7394_H__
#define __NRC7394_H__

#ifdef __cplusplus
extern "C" {
#endif


/* -------------------------  Interrupt Number Definition  ------------------------ */

typedef enum IRQn
{
/* -------------------  Processor Exceptions Numbers  ----------------------------- */
  NonMaskableInt_IRQn           = -14,     /*  2 Non Maskable Interrupt */
  HardFault_IRQn                = -13,     /*  3 HardFault Interrupt */
  MemoryManagement_IRQn         = -12,     /*  4 Memory Management Interrupt */
  BusFault_IRQn                 = -11,     /*  5 Bus Fault Interrupt */
  UsageFault_IRQn               = -10,     /*  6 Usage Fault Interrupt */
  SVCall_IRQn                   =  -5,     /* 11 SV Call Interrupt */
  DebugMonitor_IRQn             =  -4,     /* 12 Debug Monitor Interrupt */
  PendSV_IRQn                   =  -2,     /* 14 Pend SV Interrupt */
  SysTick_IRQn                  =  -1,     /* 15 System Tick Interrupt */

/* -------------------  Processor Interrupt Numbers  ------------------------------ */
  PMU_IRQn						=   0,      /*!< PMU Interrupt	                    */
  RTC_IRQn		       			=   2,      /*!< RTC Interrupt                      */
  WDT_IRQn		       			=   3,      /*!< WDT Interrupt                      */
  TIMER0_IRQn					=   4,      /*!< TIMER0 Interrupt                   */
  WIFI0_IRQn					=   5,      /*!< WIFI0  Interrupt                   */
  GDMAINTTC_IRQn				=   6,      /*!< DMAINTTC  Interrupt                */
  TIMER1_IRQn					=   8,      /*!< TIMER1 Interrupt	        	    */
  HSUART0_IRQn					=   9,      /*!< HSUART0 Interrupt                  */
  SSP0_IRQn						=  10,      /*!< SSP0 Interrupt                     */
  PWR_IRQn                      =  11,      /*!< PWR Interrupt                      */
  LPO_IRQn                      =  12,      /*!< LPO     Interrupt                  */
  GDMAINTERR_IRQn               =  13,      /*!< DMAINTERR Interrupt                */
  SECIP_IRQn					=  15,		/*!< SECIP Interrupt               		*/
  TIMER2_IRQn                   =  16,      /*!< TIMER2 Interrupt                   */
  HSUART1_IRQn                  =  17,      /*!< HSUART1 Interrupt                  */
  SSP1_IRQn                     =  18,      /*!< SSP1 Interrupt                     */
  I2C_IRQn                      =  19,      /*!< I2C ADC/DAC Interrupt              */
  WIFI1_IRQn                    =  20,      /*!< WIFI1  Interrupt                   */
  WIFI2_IRQn                    =  21,      /*!< WIFI2  Interrupt                   */
  WIFI3_IRQn                    =  22,      /*!< WIFI3  Interrupt                   */
  RTCEST_IRQn			        =  23,      /*!< RTCEST_IRQn Interrupt              */
  TIMER3_IRQn                   =  24,      /*!< TIMER3 Interrupt                   */
  SMC_IRQn						=  25,		/*!< SMC Interrupt   	                */
  RDMA_IRQn						=  26,      /*!< RDMa Interrupt		         	    */
  CNT_IRQn                      =  27,      /*!< MBINT_RX_CM3 Interrupt             */
  EXTINT0_IRQn                  =  28,      /*!< External0 Interrupt                */
  EXTINT1_IRQn                  =  29,      /*!< External1 Interrupt                */
  TXQUE_IRQn                    =  30,      /*!< HOST_INF_TX Interrupt              */
  RXQUE_IRQn                    =  31,      /*!< HOST_INF_RX Interrupt              */
  EXTINT2_IRQn                  =  32,      /*!< External2 Interrupt                */
  EXTINT3_IRQn                  =  33,      /*!< External3 Interrupt                */
} IRQn_Type;


/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* -------  Start of section using anonymous unions and disabling warnings  ------- */
#if   defined (__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined (__ICCARM__)
  #pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wc11-extensions"
  #pragma clang diagnostic ignored "-Wreserved-id-macro"
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning 586
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif


/* --------  Configuration of Core Peripherals  ----------------------------------- */
#define __CM3_REV                 0x0201U   /* Core revision r2p1 */
#define __MPU_PRESENT             1U        /* MPU present */
#define __VTOR_PRESENT            1U        /* VTOR present */
#define __NVIC_PRIO_BITS          4U        /* Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0U        /* Set to 1 if different SysTick Config is used */

//#include "core_cm3.h"                       /* Processor and core peripherals */
#include "system_nrc7394.h"                  /* System Header */


/* =========================================================================================================================== */
/* ================                            Device Specific Peripheral Section                             ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_peripherals
  * @{
  */
#include "reg_hspi.h"
#include "reg_gdma.h"
#include "reg_timer_32bit.h"
#include "reg_timer_64bit.h"
#include "reg_i2c.h"
#include "reg_i2c_cfg.h"
#include "reg_hsuart.h"
#include "reg_ssp.h"
#include "reg_sfc.h"
#include "reg_rtc.h"
#include "reg_rtccal.h"
#include "reg_pwm.h"
#include "reg_wdt.h"
#include "reg_gpio.h"
#include "reg_scfg.h"
#include "reg_scu.h"
#include "reg_pmu.h"
#include "reg_lpocal.h"
#include "reg_auxadc.h"
#include "reg_efuse.h"
#include "reg_pms.h"
#include "reg_pms_spi.h"
#include "reg_nrc_smc.h"
#include "reg_rdma.h"
#include "reg_rf_digtop.h"
#include "reg_mac.h"
#include "reg_phy.h"

/*@}*/ /* end of group NRC7394 Peripherals */



/* --------  End of section using anonymous unions and disabling warnings  -------- */
#if   defined (__CC_ARM)
  #pragma pop
#elif defined (__ICCARM__)
  /* leave anonymous unions enabled */
#elif (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
  #pragma clang diagnostic pop
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning restore
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif


/* =========================================================================================================================== */
/* ================                          Device Specific Peripheral Address Map                           ================ */
/* =========================================================================================================================== */

/* Peripheral and SRAM base address */
#define FLASH_BASE					((     uint32_t)0x00000000)
#define BOOTROM_BASE				((     uint32_t)0x10200000)
#define BOOTROM_BASE_END			((     uint32_t)0x10207FFF)
#define FLASH_MIRROR_BASE			((     uint32_t)0x11000000)

#define SRAM0_BASE					((     uint32_t)0x20000000)
#define SRAM0_BASE_END				((     uint32_t)0x2007FFFF)
#define SRAM1_BASE					((     uint32_t)0x20080000)
#define SRAM1_BASE_END				((     uint32_t)0x200CFFFF)
#define SRAM2_BASE					((     uint32_t)0x200D0000)
#define SRAM2_BASE_END				((     uint32_t)0x200FFFFF)
#define SRAM3_BASE					((     uint32_t)0x20100000)
#define SRAM3_BASE_END				((     uint32_t)0x20103FFF)
#define SRAM4_BASE					((     uint32_t)0x20104000)
#define SRAM4_BASE_END				((     uint32_t)0x2010FFFF)

#define SRAM4_RETENTION_BASE		((     uint32_t)0x20104000)
#define SRAM4_RETENTION_BASE_END	((     uint32_t)0x2010FFFF)

#define SRAM4_RETENTION0_BASE		((     uint32_t)0x20104000)
#define SRAM4_RETENTION0_BASE_END	((     uint32_t)0x20107FFF)
#define SRAM4_RETENTION1_BASE		((     uint32_t)0x20108000)
#define SRAM4_RETENTION1_BASE_END	((     uint32_t)0x2010BFFF)
#define SRAM4_RETENTION2_BASE		((     uint32_t)0x2010C000)
#define SRAM4_RETENTION2_BASE_END	((     uint32_t)0x2010FFFF)

#define APB_BASE					((     uint32_t)0x40000000)
#define AHB_BASE					((     uint32_t)0x40000000)

/* Peripheral memory map */
#define RTC_BASE           			(APB_BASE		+ 0x00000)

#define SCU_BASE      				(APB_BASE		+ 0x01000)

#define PMU_BASE       				(APB_BASE		+ 0x02000)

#define WDT_BASE          			(APB_BASE		+ 0x03000)

#define TIMER0_BASE        			(APB_BASE		+ 0x04000)
#define TIMER1_BASE        			(APB_BASE		+ 0x04100)
#define TIMER2_BASE        			(APB_BASE		+ 0x04200)
#define TIMER3_BASE        			(APB_BASE		+ 0x04300)

#define GPIO_BASE          			(APB_BASE		+ 0x05000)
#define GPIOCLR_BASE       			(APB_BASE		+ 0x05200)
#define GPIOSET_BASE       			(APB_BASE		+ 0x05400)
#define GPIOTGL_BASE       			(APB_BASE		+ 0x05600)
#define GPIOBUS_BASE         		(APB_BASE		+ 0x05800)

#define EINT_BASE          			(APB_BASE		+ 0x05840)

#define I2C0_BASE          			(APB_BASE		+ 0x06000)
#define I2C1_BASE          			(APB_BASE		+ 0x06040)
#define I2CCFG_BASE        			(APB_BASE		+ 0x06200)

#define SSP0_BASE          			(APB_BASE		+ 0x07000)
#define SSP1_BASE          			(APB_BASE		+ 0x08000)

#define HSUART0_BASE       			(APB_BASE		+ 0x09000)
#define HSUART1_BASE       			(APB_BASE		+ 0x0A000)

#define NRC_SMC_BASE        		(APB_BASE		+ 0x0B000)

#define PWM_BASE          			(APB_BASE		+ 0x0D000)

#define SCFG_BASE          			(APB_BASE		+ 0x0F000)

#define RDMA_BASE          			(APB_BASE		+ 0x48000)

#define RTCCAL_BASE        			(APB_BASE		+ 0x4A000)

#define LPOCAL_BASE        			(APB_BASE		+ 0x4B000)

#define AUXADC_BASE        			(APB_BASE		+ 0x4C000)

#define EFUSE_BASE         			(APB_BASE		+ 0x4D000)

#define PMS_SPI_BASE        		(APB_BASE		+ 0x4E000)

#define RF_DIGTOP_BASE     			(APB_BASE		+ 0x4F000)

#define MAC_BASE					(AHB_BASE		+ 0x80000)

#define PHY_BASE	            	(AHB_BASE		+ 0x88000)

#define HSPI_BASE					(AHB_BASE		+ 0x90000)

#define GDMA_BASE					(AHB_BASE		+ 0x91000)

#define SFC_BASE					(AHB_BASE		+ 0x92000)
/** @} */ /* End of group Device_Peripheral_peripheralAddr */


/******************************************************************************/
/*                         Peripheral Definitions                             */
/******************************************************************************/
#define REG_RTC				((volatile RTC_Type		*)(RTC_BASE))

#define SCU				((volatile SCU_Type		*)(SCU_BASE))

#define PMU				((volatile PMU_Type		*)(PMU_BASE))

#define WDT				((volatile WDT_Type		*)(WDT_BASE))

#define TIMER0			((volatile TIMER_32BIT_Type	*)(TIMER0_BASE))
#define TIMER1			((volatile TIMER_32BIT_Type	*)(TIMER1_BASE))
#define TIMER2			((volatile TIMER_32BIT_Type	*)(TIMER2_BASE))
#define TIMER3			((volatile TIMER_64BIT_Type	*)(TIMER3_BASE))

#define GPIO			((volatile GPIO_Type	*)(GPIO_BASE))

#define I2C0			((volatile I2C_Type		*)(I2C0_BASE))
#define I2C1			((volatile I2C_Type		*)(I2C1_BASE))
#define I2C_CFG			((volatile I2C_CFG_Type	*)(I2CCFG_BASE))

#define SSP0			((volatile SSP_Type		*)(SSP0_BASE))
#define SSP1			((volatile SSP_Type		*)(SSP1_BASE))

#define HSUART0			((volatile HSUART_Type	*)(HSUART0_BASE))
#define HSUART1			((volatile HSUART_Type	*)(HSUART1_BASE))

#define NRC_SMC			((volatile NRC_SMC_Type *)(NRC_SMC_BASE))

#define PWM				((volatile PWM_Type		*)(PWM_BASE))

#define SCFG			((volatile SCFG_Type	*)(SCFG_BASE))

#define RDMA			((volatile RDMA_Type	*)(RDMA_BASE))

#define RTCCAL			((volatile RTCCAL_Type	*)(RTCCAL_BASE))

#define LPOCAL			((volatile LPOCAL_Type  *)(LPOCAL_BASE))

#define AUXADC			((volatile AUXADC_Type	*)(AUXADC_BASE))

#define EFUSE			((volatile EFUSE_Type	*)(EFUSE_BASE))

#define PMS_SPI			((volatile PMS_SPI_Type *)(PMS_SPI_BASE))

#define RF_DIGTOP		((volatile RF_DIGTOP_Type *)(RF_DIGTOP_BASE))

#define MAC				((volatile MAC_Type		 *)(MAC_BASE))

#define PHY       		((volatile PHY_Type		*)(PHY_BASE))

#define HSPI			((volatile HSPI_Type	*)(HSPI_BASE))

#define GDMA			((volatile GDMA_Type	*)(GDMA_BASE))

#define SFC				((volatile SFC_Type		*)(SFC_BASE))

#ifdef __cplusplus
}
#endif

#endif  /* __NRC7394_H__ */
