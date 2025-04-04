INCLUDE += -I$(NVS_FLASH)/src
INCLUDE += -I$(NVS_FLASH)/include
VPATH   += $(NVS_FLASH)/src
DEFINE	+= -DSUPPORT_NVS_FLASH

SRCS += \
	nvs_partition.cpp \
	nvs_partition_lookup.cpp \
	nvs_partition_manager.cpp \
	nvs_api.cpp \
	nvs_cxx_api.cpp \
	nvs_handle_locked.cpp \
	nvs_handle_simple.cpp \
	nvs_item_hash_list.cpp \
	nvs_page.cpp \
	nvs_pagemanager.cpp \
	nvs_storage.cpp \
	nvs_types.cpp \
	aes_ctr_cipher.cpp

CSRCS += util_cmd_nvs.c

# DEFINE += -DNVS_DEBUG
