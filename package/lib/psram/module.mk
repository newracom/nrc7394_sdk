VPATH   += $(PSRAM_BASE)

INCLUDE += -I$(PSRAM_BASE)
DEFINE	+= -DSUPPORT_PSRAM

CSRCS += \
	nrc_dma.c \
	nrc_psram_impl.c \
	psram.c
