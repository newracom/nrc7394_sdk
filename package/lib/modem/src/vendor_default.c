#include <stdio.h>
#include <stdint.h>
#include "system_macro.h"
#include "nrc_ps_api.h"
#if defined(UCODE)
#include "drv_cspi.h"
#if defined(NRC7292)
#include "drv_gpio.h"
#else
#include "drv_gpio_.h"
#endif
#include "driver_sys.h"
#include "nrc-wim-types.h"
#else
#include "hal_gpio.h"
#include "system_common.h"
#include "drv_pmc.h"
#endif /* defined(UCODE) */
#if defined(USE_TEMP_SENSOR)
#define I2C_0 0
#include "drv_temp_sensor.h"
#endif /* defined(USE_TEMP_SENSOR) */
#if defined(NRC7394)
#include "hal_rf.h"
#endif
#include "nrc_ps_type.h"

#define DEBUG_ALT2_MASK   ((1U << 10) | (1U << 11) | (1U << 12) | (1U << 13))

void nrc_gpio_init_alt2(void)
{
#if defined(NRC7394)
	gpio_io_t gpio_t;
	gpio_io_t cur_alt2;
	uint32_t base_alt2;
	uint32_t debug_alt2;

	nrc_gpio_get_alt2(&cur_alt2);

#if defined(INCLUDE_STANDALONE)
	base_alt2 = 0x0000003F;     /* XIP pins */
#else
	base_alt2 = 0x700000FF;     /* HSPI pins */
#endif
	/* Preserve only GPIO10~13 ALT2 setting from current register */
	debug_alt2 = cur_alt2.word & DEBUG_ALT2_MASK;
	gpio_t.word = base_alt2 | debug_alt2;

	nrc_gpio_set_alt2(&gpio_t);
#endif /* NRC7394 */
}

static void ps_gpio_init(enum sys_operation operation)
{
	struct retention_info *ret_info = nrc_ps_get_retention_info();
	int brd_rev = (int)ret_info->drv_info.brd_rev;
	gpio_io_t gpio_t;
	gpio_io_t cur;

	(void)operation;

	bool power_pin_enable = false;
	int power_pin_number;
	nrc_ps_get_power_indication_pin(&power_pin_enable, &power_pin_number);

	const uint32_t power_bit = (power_pin_enable ? BIT(power_pin_number) : 0);
	const uint32_t preserve_mask_ret = ret_info->sleep_gpio_preserve_mask;
	const uint32_t preserve_mask = preserve_mask_ret | power_bit;

#if defined(NRC7292)
	/* Rev A: GP00-GP03, GP06-GP07,  - input
	 * Rev B,C,F: GP00-GP03, GP06-GP07,GP27-GP31 - input */
	uint32_t gpio_mask = (brd_rev == NRC7292_B || brd_rev == NRC7292_C|| brd_rev == NRC7292_F) ? 0x07FFFF30 : 0xFFFFFF30;
#else
	/* NRC7394 EVB - Active
	 * Standalone Mode: GP06-07, 10-14, 17-18, 20, 25-30 output 0
	 * Host Mode: GP10-11, 17-18, 25 output 0
	 */
	/* Todo: check N module (no external PA) - GP24 output low. */
#if defined(INCLUDE_STANDALONE)
	uint32_t gpio_mask = 0x72147CC0;
#else
	uint32_t gpio_mask = 0x02040C00;
#endif
#endif

	/* -------- DIR -------- */
	const uint32_t base_dir = gpio_mask;
	nrc_gpio_get_dir(&cur);
	gpio_t.word = gpio_merge_preserve_mask(base_dir, cur.word, preserve_mask);
	nrc_gpio_config_dir(&gpio_t);

	/* -------- OUT -------- */
	const uint32_t base_out = 0x0; /* force low for non-preserved pins */
	nrc_gpio_in(&cur);
	gpio_t.word = gpio_merge_preserve_mask(base_out, cur.word, preserve_mask);
	nrc_gpio_out(&gpio_t);

	/* -------- ALT -------- */
	gpio_io_t cur_alt;
	nrc_gpio_get_alt(&cur_alt);
	const uint32_t clear_mask = gpio_mask | power_bit;
	const uint32_t base_alt = cur_alt.word & ~clear_mask;
	gpio_t.word = gpio_merge_preserve_mask(base_alt, cur.word, preserve_mask);
	nrc_gpio_set_alt(&gpio_t);

	/* -------- ALT2 -------- */
	nrc_gpio_init_alt2();
	ps_gpio_config_wakeup_pin();
}

static void event_fw(enum ps_event event)
{
	struct retention_info *ret_info = nrc_ps_get_retention_info();
	int brd_rev = (int)ret_info->drv_info.brd_rev;
	uint32_t gpio_dir_mask = 0, gpio_out_mask = 0, gpio_pullup_mask = 0, gpio_preserv_mask = 0;

	switch (event) {
	case PS_EVT_COLDBOOT:
		ps_gpio_init(SYS_OPER_FW);
		break;
	case PS_EVT_BEFORE_DEEPSLEEP:
		gpio_dir_mask = ret_info->sleep_gpio_dir_mask;
		gpio_out_mask = ret_info->sleep_gpio_out_mask;
		gpio_pullup_mask = ret_info->sleep_gpio_pullup_mask;
		gpio_preserv_mask = ret_info->sleep_gpio_preserve_mask;
		ps_gpio_set_deepsleep(gpio_pullup_mask, gpio_out_mask, gpio_dir_mask, gpio_preserv_mask);

#if defined(NRC7394)
		nrf_pms_spi_write(0x09, 0x0);
#endif
		break;
	case PS_EVT_WAKEUP_DEEPSLEEP:
		nrc_gpio_init_alt2();
		break;
	case PS_EVT_BEFORE_MODEMSLEEP:
		break;
	case PS_EVT_WAKEUP_MODEMSLEEP:
		break;
	default:
		break;
	}
}

static void event_ucode(enum ps_event event)
{
	struct retention_info *ret_info = nrc_ps_get_retention_info();
	int brd_rev = (int)ret_info->drv_info.brd_rev;
	uint32_t gpio_dir_mask = 0, gpio_out_mask = 0, gpio_pullup_mask = 0, gpio_preserv_mask = 0;
	bool power_pin_enable = false;
	int power_pin_number;
	nrc_ps_get_power_indication_pin(&power_pin_enable, &power_pin_number);

	switch (event) {
	case PS_EVT_BEFORE_DEEPSLEEP:
		gpio_dir_mask = ret_info->sleep_gpio_dir_mask;
		gpio_out_mask = ret_info->sleep_gpio_out_mask;
		gpio_pullup_mask = ret_info->sleep_gpio_pullup_mask;
		gpio_preserv_mask = ret_info->sleep_gpio_preserve_mask;
		ps_gpio_set_deepsleep(gpio_pullup_mask, gpio_out_mask, gpio_dir_mask, gpio_preserv_mask);

#if defined(NRC7394)
		nrf_pms_spi_write(0x09, 0x0);
#endif
		break;
	case PS_EVT_WAKEUP_DEEPSLEEP:
		break;
	case PS_EVT_BEFORE_WAKEUP:
		ps_gpio_init(SYS_OPER_UCODE);
		if (power_pin_enable) {
			nrc_gpio_outb(power_pin_number, 1);
		}
		break;
	default:
		break;
	}
}

static void event(enum ps_event event, enum sys_operation operation)
{
	switch(operation) {
	case SYS_OPER_FW:
		event_fw(event);
		break;
	case SYS_OPER_UCODE:
		event_ucode(event);
		break;
	default:
		break;
	}
}

static struct nrc_ps_ops ops = {
	.cb = event,
};

struct nrc_ps_ops *nrc_ps_get_vendor(void)
{
	return &ops;
}
