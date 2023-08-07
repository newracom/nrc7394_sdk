#ifndef __DRV_PORT_H__
#define __DRV_PORT_H__

#include "stdint.h"
#include "stdbool.h"
#define __DRV_MAC_H__
#include "system.h"
#include "system_common.h"
#include "nrc7394.h"
#include "drv_phy_common.h"
#include "drv_rf_common.h"
#include "drv_trx_gain_table.h"
#include "hal_rf.h"

#define STR(s) #s

#define PROFILE_START() { uint32_t now ,  line = __LINE__; \
                        now = NOW;

#define PROFILE_END(A) now = NOW - now; \
                        DBG("                                                     " STR(A) "\n"); \
                        DBG("%30s()" , __FUNCTION__);\
                        DBG(" line %4d - %4d : %10d us\n" , line , __LINE__ , now); }

#if defined(RELEASE)
    #define P(FUNC) FUNC
#else
    #define P(FUNC) {       \
        PROFILE_START();    \
        FUNC;               \
        PROFILE_END(FUNC);  \
    }
#endif
#define MHz *1000000
#if defined(RELEASE)
    #define DBG
    #define D
#else
    #define DBG
    #define D system_printf
#endif
#define system_pms_spi_write nrf_pms_spi_write
#ifndef   __WEAK
  #define __WEAK                                 __attribute__((weak))
#endif
#define RELEASE_CONST const

#endif //__DRV_PORT_H__
