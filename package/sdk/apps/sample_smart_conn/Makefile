CSRCS += \
	sample_smart_conn.c \
	multi_role_config.c \
	wifi_relay_service.c \
	nrc_udp_comm.c \
	wifi_provision.c \
	multi_role_util.c \
	multi_role_stats.c \
	multi_role_status.c \
	multi_role_iperf.c \
	app_debug.c \
	link_status_push_client.c \
	link_status.c \

ifeq ($(CONFIG_EPAPER),y)
CSRCS += \
	epd_status_display.c
endif

# Smart Connection implementation now lives in the SDK library
# (sdk/api/api_smart_conn.c). The app only calls its public API
# (api_smart_conn.h); CONFIG_SMART_CONNECTION still gates the app-side usage
# via -DSMART_CONNECTION_ENABLE in .config.

ifeq ($(CONFIG_BCAST_FOTA_STA),y)
CSRCS += \
	multi_role_bfota.c
endif

ifeq ($(CONFIG_TCP_FOTA),y)
CSRCS += \
	multi_role_directory.c \
	multi_role_tfota_server.c \
	multi_role_tfota_client.c \
	multi_role_register.c \
	app_feature_cfg.c
endif

ifeq ($(CONFIG_IDLE_POWER_SAVE),y)
CSRCS += \
	multi_role_ps.c
endif


ifeq ($(CONFIG_PING_ON_WIFI_CONNECT),y)
CSRCS += \
	ping_on_wifi_connect.c
endif

ifeq ($(CONFIG_NANOPB),y)
CSRCS += \
	link_status.pb.c
endif

include $(SDK_WIFI_COMMON)/module.mk
