INCLUDE += -I$(IPERF3_ROOT) -I$(IPERF3_ROOT)/inc
VPATH += $(IPERF3_ROOT)/src

CSRCS += iperf3_api.c \
         iperf3_client_api.c \
         iperf3_error.c \
         iperf3_locale.c \
         iperf3_server_api.c \
         iperf3_tcp.c \
         iperf3_udp.c \
         iperf3_util.c \
         iperf3_main.c \
         iperf3_net.c \
         tcp_info.c \
         tcp_window_size.c \
         timer.c \
         units.c
