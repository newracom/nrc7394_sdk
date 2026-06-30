INCLUDE += -I$(NANOPB_BASE)/src
DEFINE  += -DSUPPORT_NANOPB
VPATH   += $(NANOPB_BASE)/src

CSRCS += \
	pb_common.c \
	pb_decode.c \
	pb_encode.c

