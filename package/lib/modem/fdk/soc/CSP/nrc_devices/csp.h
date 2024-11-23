#ifndef __CSP_H__
#define __CSP_H__

#ifdef __cplusplus
extern "C"{
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/* SWRST 32Mhz : 8us, 16Mhz : 16us...
RTC, PMU: 8us + 32k sync min 68 = 76us, 16Mhz : 16us + 68us = 84us */
#define __CSP_SWRST_WATING_TIME_US				100

#if defined ( __GNUC__ )
#define __RAM_FUNC	__attribute__((section(".ramfunc")))
#elif defined (__ICCARM__)
#define __RAM_FUNC __ramfunc 
#endif


#if defined (NRC7292)
#include "nrc7292.h"

#elif defined(NRC7394)
#include "nrc7394.h"
#define __CSP_GPIO_ALT_MAX							5

#elif defined(NRC5291)
#include "nrc5291.h"
#define __CSP_GPIO_ALT_MAX							4

#elif defined(NRC5292)
#include "nrc5292.h"
#define __CSP_GPIO_ALT_MAX							4

#elif defined(NRC5293)
#include "nrc5293.h"
#define __CSP_GPIO_ALT_MAX							4


#elif defined(NRC4792)
#include "nrc4792.h"
#define __CSP_GPIO_ALT_MAX							4


#else
#error Not supported Model
#endif

#include "type.h"

//#include "drv.h"

//#include "csp_efuse.h"
#include "csp_scu.h"
#include "csp_sfc.h"
#include "csp_pms.h"
#include "csp_scfg.h"
#include "csp_hsuart.h"
#include "csp_ssp.h"
#include "csp_flash.h"


void __csp_delay_Init(void);
void __csp_delay(uint32_t ulDelay);
void __csp_delay_ms(uint32_t ulms);
__RAM_FUNC void __csp_delay_us(uint32_t ulus);



#ifdef __cplusplus
}
#endif

#endif

