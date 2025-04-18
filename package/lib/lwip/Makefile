include $(CONFIG)

PKG_NAME=lwip

include lwip.make

LWIP_BASE		= $(CURDIR)
LWIP_BASE_INC	= $(LWIP_BASE)/include
LWIP_BASE_APPS	= $(LWIP_BASE)/apps
LWIP_LIB		= $(LWIP_BASE)/lwip

LWIP_LIB_SRC	= $(LWIP_LIB)/src
LWIP_INC		= $(LWIP_LIB_SRC)/include
LWIP_CORE		= $(LWIP_LIB_SRC)/core
LWIP_API		= $(LWIP_LIB_SRC)/api
LWIP_NETIF		= $(LWIP_LIB_SRC)/netif
LWIP_IPV4		= $(LWIP_CORE)/ipv4
LWIP_IPV6		= $(LWIP_CORE)/ipv6

LWIP_COMPAT		= $(LWIP_INC)/compat
LWIP_POSIX		= $(LWIP_COMPAT)/posix

LWIP_PORT			= $(LWIP_BASE)/port
LWIP_PORT_INC		= $(LWIP_PORT)/include
LWIP_PORT_ARCH		= $(LWIP_PORT)/arch
LWIP_PORT_ARCH_INC	= $(LWIP_PORT_INC)/arch
LWIP_PORT_FREERTOS	= $(LWIP_PORT)/freertos
LWIP_PORT_NETIF		= $(LWIP_PORT)/netif
LWIP_PORT_NETIF_INC	= $(LWIP_PORT_INC)/netif
LWIP_PORT_NAT		= $(LWIP_PORT)/lwip-nat
LWIP_PORT_NAT_INC	= $(LWIP_PORT_INC)/lwip-nat

LWIP_APPS_INC	= $(LWIP_BASE_INC)/apps

LWIP_PING		= $(LWIP_BASE_APPS)/ping
LWIP_IPERF		= $(LWIP_BASE_APPS)/iperf
LWIP_DHCPS		= $(LWIP_BASE_APPS)/dhcpserver

LWIP_PING_INC		= $(LWIP_APPS_INC)/ping
LWIP_IPERF_INC		= $(LWIP_APPS_INC)/iperf
LWIP_DHCPS_INC		= $(LWIP_APPS_INC)/dhcpserver

INCLUDE += -I$(LWIP_BASE_INC)
INCLUDE += -I$(LWIP_APPS_INC)
INCLUDE += -I$(LWIP_PING_INC)
INCLUDE += -I$(LWIP_IPERF_INC)
INCLUDE += -I$(LWIP_DHCPS_INC)
INCLUDE += -I$(LWIP_INC)
INCLUDE += -I$(LWIP_PORT_INC)
INCLUDE += -I$(LWIP_PORT_ARCH_INC)
INCLUDE += -I$(LWIP_PORT_NETIF_INC)
INCLUDE += -I$(LWIP_PORT_NAT_INC)
INCLUDE += -I$(LWIP_POSIX)

ifeq ($(CONFIG_ETH_ENC28J60), y)
INCLUDE += -I$(TOPDIR)/lib/ethernet
INCLUDE += -I$(TOPDIR)/lib/eth_enc28j60
INCLUDE += -I$(TOPDIR)/sdk/include

DEFINE += -DLWIP_NAT
DEFINE += -DSUPPORT_ETHERNET_ACCESSPOINT
DEFINE += -DETH_DRIVER_ENC28J60
DEFINE += -DNRC_DHCP_SET_BROADCAST_FLAG
endif

ifeq ($(CONFIG_ETH_W5500), y)
INCLUDE += -I$(TOPDIR)/lib/ethernet
INCLUDE += -I$(TOPDIR)/lib/eth_w5500
INCLUDE += -I$(TOPDIR)/sdk/include

DEFINE += -DLWIP_NAT
DEFINE += -DSUPPORT_ETHERNET_ACCESSPOINT
DEFINE += -DETH_DRIVER_W5500
DEFINE += -DNRC_DHCP_SET_BROADCAST_FLAG
endif

# includes.h wanted by nrc_ping.c
INCLUDE += -I$(TOPDIR)/lib/hostap/src
INCLUDE += -I$(TOPDIR)/lib/hostap/src/utils
INCLUDE += -I$(TOPDIR)/lib/hostap/src/drivers

VPATH	+= $(LWIP_CORE)
VPATH	+= $(LWIP_NETIF)
VPATH	+= $(LWIP_API)
VPATH	+= $(LWIP_IPV4)
VPATH	+= $(LWIP_IPV6)
VPATH	+= $(LWIP_PORT)
VPATH	+= $(LWIP_PORT_ARCH)
VPATH	+= $(LWIP_PORT_FREERTOS)
VPATH	+= $(LWIP_PORT_NETIF)
VPATH	+= $(LWIP_PING)
VPATH	+= $(LWIP_IPERF)
VPATH	+= $(LWIP_DHCPS)
VPATH	+= $(LWIP_PORT_NAT)

DEFINE += -DNRC_LWIP
DEFINE += -DSUPPORT_MBEDTLS

include $(TOPDIR)/make/build-lib.mk
