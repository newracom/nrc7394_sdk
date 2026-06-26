LITTLEFS_SRC  = $(LITTLEFS_BASE)
LITTLEFS_PORT = $(LITTLEFS_BASE)/port

INCLUDE += -I$(LITTLEFS_SRC) -I$(LITTLEFS_PORT)

VPATH += $(LITTLEFS_SRC) $(LITTLEFS_PORT)

CSRCS += \
	lfs.c \
	lfs_util.c \
	lfs_port.c \
	lfs_file_utils.c \
	lfs_cli_utils.c \
	lfs_file_set.c

# Bridge utility (only when FATFS + DISKIO are enabled)
ifeq ($(CONFIG_FATFS),y)
ifeq ($(CONFIG_DISKIO),y)
CSRCS += lfs_fatfs_bridge.c
endif
endif
