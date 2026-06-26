SECTIONS
{
	.text :
	{
		__isr_vector_start = .;
		KEEP(*(.isr_vector))
		__isr_vector_end = .;
		/* *(.text) */
		/* *(.text*) */
		*(EXCLUDE_FILE(
				/* Driver files */
				*driver_nrc.c.o
				*driver_nrc_debug.c.o
				*driver_nrc_event_mgr.c.o
				*driver_nrc_ps.c.o
				*driver_nrc_rx_agg.c.o
				*driver_nrc_rx.c.o
				*driver_nrc_scan.c.o
				*driver_nrc_tx_agg.c.o
				*driver_nrc_tx.c.o
				/* LMAC files */
				*lmac_11ah.c.o
				*lmac_cmd.c.o
				*lmac_common.c.o
				*lmac_config.c.o
				*lmac_debug.c.o
				*lmac_downlink.c.o
				*lmac_drv.c.o
				*lmac_duty_cycle.c.o
				*lmac_lib-rom.c.o
				*lmac_mic_scan.c.o
				*lmac_modem_detection.c.o
				*lmac_modem_recovery.c.o
				*lmac_ps_common.c.o
				*lmac_queue_manager_11ah.c.o
				*lmac_queue_manager.c.o
				*lmac_rate_control.c.o
				*lmac_self_config.c.o
				*lmac_stats.c.o
				*lmac_test.c.o
				*lmac_twt_common.c.o
				*lmac_util.c.o
				*lmac_apf.c.o
				*lmac_apf_ps.c.o
				*lmac_band.c.o
				*util_cmd_lmac_indirect.c.o
				*util_cmd_lmac_indirect-rom.c.o
				/* UMAC files */
				*umac_s1g_agent.c.o
				*umac_s1g_channel.c.o
				*umac_s1g_channel-rom.c.o
				*umac_s1g_config.c.o
				*umac_s1g_elementhook.c.o
				*umac_s1g_framehook.c.o
				*umac_s1g_hookmanager.c.o
				*umac_s1g_ie_manager.c.o
				*umac_s1g_join_handler.c.o
				*umac_s1g_pv1.c.o
				*umac_s1g_scan_handler.c.o
				*umac_s1g_tim_handler.c.o
				*umac_wim_builder.c.o
				*umac_wim_builder-rom.c.o
				/* Bignum files */
				*bignum.c.o
				*bignum_core.c.o
				*bignum_hw.c.o
				*bignum_mod.c.o
				*bignum_mod_raw.c.o
				*drv_sec.c.o
		).text)
		*(EXCLUDE_FILE(
				/* Driver files */
				*driver_nrc.c.o
				*driver_nrc_debug.c.o
				*driver_nrc_event_mgr.c.o
				*driver_nrc_ps.c.o
				*driver_nrc_rx_agg.c.o
				*driver_nrc_rx.c.o
				*driver_nrc_scan.c.o
				*driver_nrc_tx_agg.c.o
				*driver_nrc_tx.c.o
				/* LMAC files */
				*lmac_11ah.c.o
				*lmac_cmd.c.o
				*lmac_common.c.o
				*lmac_config.c.o
				*lmac_debug.c.o
				*lmac_downlink.c.o
				*lmac_drv.c.o
				*lmac_duty_cycle.c.o
				*lmac_lib-rom.c.o
				*lmac_mic_scan.c.o
				*lmac_modem_detection.c.o
				*lmac_modem_recovery.c.o
				*lmac_ps_common.c.o
				*lmac_queue_manager_11ah.c.o
				*lmac_queue_manager.c.o
				*lmac_rate_control.c.o
				*lmac_self_config.c.o
				*lmac_stats.c.o
				*lmac_test.c.o
				*lmac_twt_common.c.o
				*lmac_util.c.o
				*lmac_apf.c.o
				*lmac_apf_ps.c.o
				*lmac_band.c.o
				*util_cmd_lmac_indirect.c.o
				*util_cmd_lmac_indirect-rom.c.o
				/* UMAC files */
				*umac_s1g_agent.c.o
				*umac_s1g_channel.c.o
				*umac_s1g_channel-rom.c.o
				*umac_s1g_config.c.o
				*umac_s1g_elementhook.c.o
				*umac_s1g_framehook.c.o
				*umac_s1g_hookmanager.c.o
				*umac_s1g_ie_manager.c.o
				*umac_s1g_join_handler.c.o
				*umac_s1g_pv1.c.o
				*umac_s1g_scan_handler.c.o
				*umac_s1g_tim_handler.c.o
				*umac_wim_builder.c.o
				*umac_wim_builder-rom.c.o
				/* Bignum files */
				*bignum.c.o
				*bignum_core.c.o
				*bignum_hw.c.o
				*bignum_mod.c.o
				*bignum_mod_raw.c.o
				*drv_sec.c.o
		).text*)

		. = ALIGN(4);
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP(*(.preinit_array))
		PROVIDE_HIDDEN (__preinit_array_end = .);

		. = ALIGN(4);
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP(*(SORT(.init_array.*)))
		KEEP(*(.init_array))
		PROVIDE_HIDDEN (__init_array_end = .);

		. = ALIGN(4);
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP(*(SORT(.fini_array.*)))
		KEEP(*(.fini_array))
		PROVIDE_HIDDEN (__fini_array_end = .);

		KEEP(*(.init))
		KEEP(*(.fini))

		*crtbegin.o(.ctors)
		*crtbegin?.o(.ctors)
		*(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
		*(SORT(.ctors.*))
		*(.ctors)

 		*crtbegin.o(.dtors)
 		*crtbegin?.o(.dtors)
 		*(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
 		*(SORT(.dtors.*))
 		*(.dtors)

		*(.rodata*)
		*(.rodata)
		*(.glue_7)
		*(.glue_7t)
		*(.gnu.linkonce.r.*)
		*(.gnu.linkonce.d.*);
/*
		*(.data.impure_data);
		*(.data._impure_ptr);
*/
		*(.got);
		KEEP(*(.eh_frame*))
		. = ALIGN(4);
		_etext = .;

	} > FLASH

	.ARM.extab :
	{
		*(.ARM.extab* .gnu.linkonce.armextab.*)
	} > FLASH

	__exidx_start = .;
	.ARM.exidx :
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
	} > FLASH
	__exidx_end = .;

	. = ALIGN(4);
	PROVIDE(__etext = .);

	.data :
	{
		__data_load__ = LOADADDR(.data);
		__data_start__ = .;
		*(vtable)
		. = ALIGN(4);

		/* executed on ram (object unit) */
		/* Driver files */
		KEEP(*driver_nrc.c.o(.text* .rodata*))
		KEEP(*driver_nrc_debug.c.o(.text* .rodata*))
		KEEP(*driver_nrc_event_mgr.c.o(.text* .rodata*))
		KEEP(*driver_nrc_ps.c.o(.text* .rodata*))
		KEEP(*driver_nrc_rx_agg.c.o(.text* .rodata*))
		KEEP(*driver_nrc_rx.c.o(.text* .rodata*))
		KEEP(*driver_nrc_scan.c.o(.text* .rodata*))
		KEEP(*driver_nrc_tx_agg.c.o(.text* .rodata*))
		KEEP(*driver_nrc_tx.c.o(.text* .rodata*))
		/* LMAC files */
		KEEP(*lmac_11ah.c.o(.text* .rodata*))
		KEEP(*lmac_cmd.c.o(.text* .rodata*))
		KEEP(*lmac_common.c.o(.text* .rodata*))
		KEEP(*lmac_config.c.o(.text* .rodata*))
		KEEP(*lmac_debug.c.o(.text* .rodata*))
		KEEP(*lmac_downlink.c.o(.text* .rodata*))
		KEEP(*lmac_drv.c.o(.text* .rodata*))
		KEEP(*lmac_duty_cycle.c.o(.text* .rodata*))
		KEEP(*lmac_lib-rom.c.o(.text* .rodata*))
		KEEP(*lmac_mic_scan.c.o(.text* .rodata*))
		KEEP(*lmac_modem_detection.c.o(.text* .rodata*))
		KEEP(*lmac_modem_recovery.c.o(.text* .rodata*))
		KEEP(*lmac_ps_common.c.o(.text* .rodata*))
		KEEP(*lmac_queue_manager_11ah.c.o(.text* .rodata*))
		KEEP(*lmac_queue_manager.c.o(.text* .rodata*))
		KEEP(*lmac_rate_control.c.o(.text* .rodata*))
		KEEP(*lmac_self_config.c.o(.text* .rodata*))
		KEEP(*lmac_stats.c.o(.text* .rodata*))
		KEEP(*lmac_test.c.o(.text* .rodata*))
		KEEP(*lmac_twt_common.c.o(.text* .rodata*))
		KEEP(*lmac_util.c.o(.text* .rodata*))
		KEEP(*lmac_apf.c.o(.text* .rodata*))
		KEEP(*lmac_apf_ps.c.o(.text* .rodata*))
		KEEP(*lmac_band.c.o(.text* .rodata*))
		KEEP(*util_cmd_lmac_indirect.c.o(.text* .rodata*))
		KEEP(*util_cmd_lmac_indirect-rom.c.o(.text* .rodata*))
		/* UMAC files */
		KEEP(*umac_s1g_agent.c.o(.text* .rodata*))
		KEEP(*umac_s1g_channel.c.o(.text* .rodata*))
		KEEP(*umac_s1g_channel-rom.c.o(.text* .rodata*))
		KEEP(*umac_s1g_config.c.o(.text* .rodata*))
		KEEP(*umac_s1g_elementhook.c.o(.text* .rodata*))
		KEEP(*umac_s1g_framehook.c.o(.text* .rodata*))
		KEEP(*umac_s1g_hookmanager.c.o(.text* .rodata*))
		KEEP(*umac_s1g_ie_manager.c.o(.text* .rodata*))
		KEEP(*umac_s1g_join_handler.c.o(.text* .rodata*))
		KEEP(*umac_s1g_pv1.c.o(.text* .rodata*))
		KEEP(*umac_s1g_scan_handler.c.o(.text* .rodata*))
		KEEP(*umac_s1g_tim_handler.c.o(.text* .rodata*))
		KEEP(*umac_wim_builder.c.o(.text* .rodata*))
		KEEP(*umac_wim_builder-rom.c.o(.text* .rodata*))
		/* Bignum files */
		KEEP(*bignum.c.o(.text* .rodata*))
		KEEP(*bignum_core.c.o(.text* .rodata*))
		KEEP(*bignum_hw.c.o(.text* .rodata*))
		KEEP(*bignum_mod.c.o(.text* .rodata*))
		KEEP(*bignum_mod_raw.c.o(.text* .rodata*))
		KEEP(*drv_sec.c.o(.text* .rodata*))
		. = ALIGN(4);

		/* executed on ram (function unit) */
		*(.run_ram*)
		. = ALIGN(4);

		*(.sfc_code_nc*)
		. = ALIGN(4);
		__sfc_code_nc_end__ = .;
		*(.sfc_code_c*)
		. = ALIGN(4);

		*(.data)
		*(.data*)
		. = ALIGN(4);
		__measure_cpu_start = .;
		*(.measure_cpu)
		__measure_cpu_end = .;
		KEEP(*(.jcr*))
		. = ALIGN(4);
		KEEP(*(SORT(.nrc_cmd*)));
		. = ALIGN(4);
		*(.data.impure_data);
		*(.data._impure_ptr);
		. = ALIGN(4);
		PROVIDE(__data_end__ = .);
		_edata = .;
	} > RAM AT>FLASH

	PROVIDE(__dstart__ = __data_start__);

	.bssreloc (NOLOAD)  :
	{
		PROVIDE(__bss_start__ = .);
		. = ALIGN(4);
		*(.bss*)
		. = ALIGN(4);
		*(COMMON)
		. = ALIGN(4);
		PROVIDE(__bss_end__ = .);
	} > RAM

	PROVIDE(__ebss = .);
	. = ALIGN(4);

	.buffer_pool (NOLOAD) :
	{
		PROVIDE(__buffer_pool_start__ = .);
		. = ALIGN(4);
		*(.buffer)
		. = ALIGN(4);
		PROVIDE(__buffer_pool_end__ = .);
	} > RAM

	.pp_buf (NOLOAD) :
	{
		PROVIDE(__pageprog_buf_start__ = .);
		. = ALIGN(4);
		*(.ppbuf)
		. = ALIGN(4);
		PROVIDE(__pageprog_buf_end__ = .);
	} > PP_BUF

	.retention_info (NOLOAD) :
	{
		PROVIDE(__retention_info_start__ = .);
		*(.retention_info*);
		. = ALIGN(4);
		PROVIDE(__retention_info_end__ = .);
	} > RETENTION_INFO

	.retain :
	{
		__retention_load__ = LOADADDR(.retain);
		PROVIDE(__retention_start__ = .);
		*(.retent);
		. = ALIGN(4);
		PROVIDE(__retention_end__ = .);
	} > RETENTION AT>FLASH

	PROVIDE(end = .);
	PROVIDE(__CODE_START = ORIGIN(FLASH));
	PROVIDE(__DATA_START = ORIGIN(RAM));
	PROVIDE(__DATA_END = ORIGIN(RAM) + LENGTH(RAM));
	PROVIDE(__STACK_TOP = ORIGIN(RAM) + LENGTH(RAM) + STACK_SIZE);
	PROVIDE(__STACK_LIMIT = ORIGIN(RAM) + LENGTH(RAM));
	PROVIDE(__MEASURE_CPU_START = __measure_cpu_start);
	PROVIDE(__MEASURE_CPU_END = __measure_cpu_end);
}
