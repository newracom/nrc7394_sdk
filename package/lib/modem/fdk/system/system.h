#ifndef __COMMON_H__
#define __COMMON_H__

#ifdef __cplusplus
extern "C"{
#endif

#include "csp.h"
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <float.h>
#include <math.h>

#include "system_new_printf.h"
#include "system_console.h"
#if defined(EXCLUDE_FDK_MAC) && !defined(UCODE)
#include "system_sflash_.h"
#else
#include "system_sflash.h"
#endif
#include "system_efuse.h"
#include "system_pmsspi.h"
#include "system_eeprom.h"

#if defined(EXCLUDE_FDK_MAC)
#if defined(UCODE) && defined(INCLUDE_UCODE_DEBUG)
#define system_printf	ucode_printf
#else
#define system_printf	hal_uart_printf
#endif
#endif

typedef enum {
    BW_1M   		= 0,
    BW_2M   		= 1,
    BW_4M   		= 2,
    BW_MAX          = 3,
    BW_UNDEFINED    = -1
} bw_t;
typedef enum {
    AC_BK,
    AC_BE,
    AC_VI,
    AC_VO,
    AC_PIFS,
    AC_SIFS,
    AC_MAX
} ac_t;

extern const char* string_bw_to_str[BW_MAX];
#define bw_to_str(A) string_bw_to_str[A]
bw_t str_to_bw(const char *str);

#define MHz *1000000

#if defined(RELEASE)
#define RELEASE_CONST const
#else
#define RELEASE_CONST
#endif

#define REG_BEGIN(A,B) { A ##_##B reg = A->B .b;
#define REG_END(A,B) A->B.b = reg; }

void        system_init();
void        system_hsuart_init();
void        system_modem_init();
void        system_retention_init();
uint32_t    system_get_retention_memory();

void        system_irq_enable(void);
void        system_irq_disable(void);

void        system_printf(const char *f, ...);
void        system_count_delay(uint32_t delay);
void        system_show_chip_version();
void        system_show_boot_info();

uint32_t    system_pms_spi_read(uint32_t );
void        system_pms_spi_write(uint32_t , uint32_t);

void        system_set_deepsleep_gpio(uint32_t output_dir_mask , uint32_t data_mask , uint32_t pullup_mask);
// HSUART API
uint8_t     DeUartRXQueue(uint8_t uID);
uint8_t     CheckUartsRxQueue(uint8_t uID);
extern uint8_t HSUARTChannel;

#if defined(SBR_RX)
    #define NOW	    (MAC->TSF_0_LOWER_READONLY.w)
    #define PMU_NOW (PMU->TSF_TIMER_L.w)
#else
    #define NOW	    (MAC->TSF_0_LOWER_READONLY.w)
    #define PMU_NOW (MAC->TSF_0_LOWER_READONLY.w)
#endif
// DEBUG
#if defined(RELEASE)
	#define DBG
	void system_printf_rel(const char *f, ...);
	#define REL_DBG system_printf_rel
#else
	#define DBG system_printf
	#define REL_DBG system_printf
#endif


#if defined(MFGT)
#define DBG_NON_MFGT
#else
#define DBG_NON_MFGT DBG
#endif

#define A system_printf
#define CPA system_printf

#define STR(s) #s
#if defined(RELEASE)
    #define P(FUNC) FUNC
#else
    #define P(FUNC) {       \
        PROFILE_START();    \
        FUNC;               \
        PROFILE_END(FUNC);  \
    }
#endif
#define PROFILE_START() { uint32_t now ,  line = __LINE__; \
                        now = NOW;

#define PROFILE_END(A) now = NOW - now; \
                        DBG("                                                     " STR(A) "\n"); \
                        DBG("%30s()" , __FUNCTION__);\
                        DBG(" line %4d - %4d : %10d us\n" , line , __LINE__ , now); }

#ifdef __cplusplus
}
#endif

#endif



