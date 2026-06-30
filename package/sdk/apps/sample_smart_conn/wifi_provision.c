#include <stdio.h>
#include <string.h>
#include "lwip/sockets.h"
#include "lwip/inet.h"
#include "dhcpserver.h"
#include <sys/select.h>
#include "util_crc.h"
#include "api_wifi.h"
#include "multi_role_config.h"
#include "nvs.h"

#include "wifi_provision.h"
#include "app_debug.h"

#ifdef SUPPORT_TCP_FOTA
#include "multi_role_directory.h"
#endif

#define MAX_ACK_CHECK 100

extern struct netif br_netif;
extern struct netif *nrc_netif[];

extern nvs_handle_t nvs_handle;

static device_info_t device_list[MAX_DEVICES];
static int device_count = 0;

static char g_ssid[MAX_SSID_LENGTH] = {0};
static char g_password[MAX_PW_LENGTH] = {0};
static int config_initialized = 0;

static uint32_t softap_ip = 0;

static int ack_sock = -1;

static bool is_valid_sa(const uint8_t *sa)
{
	static const uint8_t all_zero[SA_LEN] = {0x00, 0x00, 0x00};
	static const uint8_t all_ff[SA_LEN]   = {0xFF, 0xFF, 0xFF};

	if (!sa) return false;
	if (memcmp(sa, all_zero, SA_LEN) == 0) return false;
	if (memcmp(sa, all_ff, SA_LEN) == 0) return false;

	uint8_t high = sa[0];
	uint8_t mid  = sa[1];
	uint8_t low  = sa[2];

	if ((high & 0xF0) == 0xB0) return false;
	if (mid == 0xFF && low == 0xFF) return false;
	// if (low == 0xFF) return false;

	return true;
}

uint32_t get_softap_ip()
{
	if (softap_ip == 0) {
		nvs_get_u32(nvs_handle, "ap_ip", &softap_ip);
	}
	return softap_ip;
}

device_info_t* get_device_list(void)
{
	return device_list;
}

int get_device_count(void)
{
	return device_count;
}

void print_device_list(int idx)
{
	int max_idx;

	if (idx >= 0)
		max_idx = idx;
	else
	{
		idx = 0;
		max_idx = device_count - 1;
	}

	app_log(DEBUG_LEVEL_ALWAYS, NULL, "[AP] Registered Devices (%d):\n", device_count);

	for ( ; idx <= max_idx ; idx++) {
		app_log(DEBUG_LEVEL_ALWAYS, NULL,
#ifdef DEVICE_EXT_SA
			"[%d] MAC %02X:%02X:%02X:%02X:%02X:%02X | SA %02X:%02X:%02X | SA(EXT) %02X:%02X:%02X | IP %s | Active:%d | Config:%d | Reboot:%d\n",
#else
			"[%d] MAC %02X:%02X:%02X:%02X:%02X:%02X | SA %02X:%02X:%02X | IP %s | Active:%d | Config:%d | Reboot:%d\n",
#endif
			idx,
			device_list[idx].mac[0], device_list[idx].mac[1], device_list[idx].mac[2],
			device_list[idx].mac[3], device_list[idx].mac[4], device_list[idx].mac[5],
			device_list[idx].sa[0], device_list[idx].sa[1], device_list[idx].sa[2],
#ifdef DEVICE_EXT_SA
			device_list[idx].ext_sa[0], device_list[idx].ext_sa[1], device_list[idx].ext_sa[2],
#endif
			ip4addr_ntoa(&device_list[idx].ip),
			device_list[idx].active,
			device_list[idx].config_updated,
			device_list[idx].reboot_acknowledged);
	}
}

/* populate device_list based on fastconnect cache */
void prepare_device_list()
{
	uint8_t bssid_list[MAX_DEVICES][6];

	memset(bssid_list, 0, sizeof(bssid_list));
	uint16_t count = nrc_wifi_child_node_list(0, bssid_list, get_max_device());

	if (count <= 0) {
		return;
	}

	for (int i = 0; i < count; i++) {
		if (device_count >= get_max_device()) {
			continue;
		}

		if (dhcps_get_ip(bssid_list[i], &device_list[i].ip)) {
			memcpy(device_list[i].mac, bssid_list[i], 6);
			memset(device_list[device_count].sa, 0xFF, 3);
#ifdef DEVICE_EXT_SA
			memset(device_list[device_count].ext_sa, 0xFF, 3);
#endif
			device_list[i].config_updated = 0;
			device_list[i].reboot_acknowledged = 0;
			device_list[i].factoryreset_acknowledged = 0;
			device_list[i].active = 0;
			device_list[i].timestamp = xTaskGetTickCount();
			device_count++;
		}
	}
}

void init_device_list (system_role_t role)
{
	if (role == ROLE_SOFTAP && nrc_wifi_get_recovered_by_fast_connect(0))
	{
		uint8_t bssid_list[MAX_DEVICES][6];
		uint16_t n_child_node;
		int i;

		memset(bssid_list, 0, sizeof(bssid_list));

		n_child_node = nrc_wifi_child_node_list(0, bssid_list, get_max_device());

		for (i = 0 ; i < n_child_node ; i++)
		{
			if (dhcps_get_ip(bssid_list[i], &device_list[i].ip)) {
				memcpy(device_list[i].mac, bssid_list[i], 6);
				memset(device_list[i].sa, 0xFF, 3);
#ifdef DEVICE_EXT_SA
				memset(device_list[i].ext_sa, 0xFF, 3);
#endif
				device_list[i].config_updated = 0;
				device_list[i].reboot_acknowledged = 0;
				device_list[i].active = 1;
				device_list[i].timestamp = xTaskGetTickCount();
			}
		}

		device_count = n_child_node;

#ifdef SUPPORT_TCP_FOTA
		/* Seed directory so LED/host queries reflect fast-connect children immediately. */
		for (i = 0; i < device_count; i++) {
			directory_on_keepalive(device_list[i].mac, device_list[i].ip.addr);
		}
#endif

		if (0)
		{
			STA_LIST info;

			if (nrc_wifi_softap_get_sta_list(0, &info, sizeof(STA_LIST)) == WIFI_SUCCESS)
			{
				app_log(DEBUG_LEVEL_INFO, NULL, "STA_LIST: %u\n", info.total_num);

				for (i = 0 ; i < info.total_num ; i++)
				{
					app_log(DEBUG_LEVEL_INFO, NULL, " [%d] aid=%u mac=%02X:%02X:%02X:%02X:%02X:%02X\n",
							i, info.sta[i].aid,
							info.sta[i].addr[0], info.sta[i].addr[1], info.sta[i].addr[2],
							info.sta[i].addr[3], info.sta[i].addr[4], info.sta[i].addr[5]);
				}
			}
		}
	}
	else
	{
		memset(device_list, 0, sizeof(device_list));
		device_count = 0;
	}

	print_device_list_all();
}

void prepare_config_message(config_message_t* msg, const char* ssid, const char* pw, int request_ack)
{
	memset(msg, 0, sizeof(config_message_t));
	msg->magic = CONFIG_MSG_MAGIC;
	msg->msg_type = CONFIG_MSG_TYPE_UPDATE;
	msg->flags = request_ack ? CONFIG_FLAG_ACK_REQUEST : 0;
	strncpy(msg->payload.config.ssid, ssid, sizeof(msg->payload.config.ssid));
	strncpy(msg->payload.config.password, pw, sizeof(msg->payload.config.password));
	memcpy(msg->payload.config.sender_mac, lmac_get_mac_address(0), 6);
	msg->payload.config.timestamp = xTaskGetTickCount();
	msg->length = sizeof(msg->payload);
	msg->crc32 = util_crc_compute_crc32((uint8_t*)msg, sizeof(config_message_t) - sizeof(uint32_t));
}

void prepare_reboot_message(config_message_t* msg, int request_ack)
{
	memset(msg, 0, sizeof(config_message_t));
	msg->magic = CONFIG_MSG_MAGIC;
	msg->msg_type = CONFIG_MSG_TYPE_REBOOT;
	msg->flags = request_ack ? CONFIG_FLAG_ACK_REQUEST : 0;
	memcpy(msg->payload.config.sender_mac, lmac_get_mac_address(0), 6);
	msg->payload.config.timestamp = xTaskGetTickCount();
	msg->length = 0;
	msg->crc32 = util_crc_compute_crc32((uint8_t*)msg, sizeof(config_message_t) - sizeof(uint32_t));
}

void prepare_factoryreset_message(config_message_t* msg, int request_ack)
{
	memset(msg, 0, sizeof(config_message_t));
	msg->magic = CONFIG_MSG_MAGIC;
	msg->msg_type = CONFIG_MSG_TYPE_FACTORYRESET;
	msg->flags = request_ack ? CONFIG_FLAG_ACK_REQUEST : 0;
	memcpy(msg->payload.config.sender_mac, lmac_get_mac_address(0), 6);
	msg->payload.config.timestamp = xTaskGetTickCount();
	msg->length = 0;
	msg->crc32 = util_crc_compute_crc32((uint8_t*)msg, sizeof(config_message_t) - sizeof(uint32_t));
}

void send_message_unicast(const ip4_addr_t* ip, const config_message_t* msg)
{
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) return;

	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(COMM_PORT);
	addr.sin_addr.s_addr = ip->addr;

	sendto(sock, msg, sizeof(config_message_t), 0,
		(struct sockaddr*)&addr, sizeof(addr));
	close(sock);
	app_log(DEBUG_LEVEL_INFO, NULL, "[AP] Sent unicast message (type %d) to %s\n", msg->msg_type, ip4addr_ntoa(ip));
}

void send_message_multicast(const config_message_t* msg)
{
    int sock;
    struct sockaddr_in mcast_addr;
    struct in_addr group_in;
	int ttl = 2;
    unsigned char loop = 0;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        app_log(DEBUG_LEVEL_ERROR, NULL, "[AP] Failed to create multicast socket: %d (%s)\n", errno, strerror(errno));
        return;
    }

	if (setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl)) < 0) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "[AP] Warning: cannot set IP_MULTICAST_TTL: %d (%s)\n",
			   errno, strerror(errno));
	}

	if (setsockopt(sock, IPPROTO_IP, IP_MULTICAST_LOOP, &loop, sizeof(loop)) < 0) {
		app_log(DEBUG_LEVEL_WARN, NULL, "[AP] Warning: cannot set IP_MULTICAST_LOOP: %d (%s)\n", errno, strerror(errno));
	}

	memset(&mcast_addr, 0, sizeof(mcast_addr));
	mcast_addr.sin_family = AF_INET;
	mcast_addr.sin_port   = htons(COMM_PORT);

	if (inet_aton(MULTICAST_GROUP, &group_in) == 0) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "[AP] Invalid multicast address: %s\n", MULTICAST_GROUP);
		close(sock);
		return;
	}
	mcast_addr.sin_addr = group_in;

	if (sendto(sock,
			   msg,
			   sizeof(config_message_t),
			   0,
			   (struct sockaddr*)&mcast_addr,
			   sizeof(mcast_addr)) < 0) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "[AP] sendto(multicast) failed: %d (%s)\n", errno, strerror(errno));
	} else {
		app_log(DEBUG_LEVEL_INFO, NULL, "[AP] Sent multicast message (type %d) to %s:%d\n",
			   msg->msg_type,
			   MULTICAST_GROUP,
			   COMM_PORT);
	}

	close(sock);
}

void softap_update_ssid_password(uint8_t seed)
{
	uint64_t rtc_time;
	char mac[6];
	nrc_get_rtc(&rtc_time);

	srand((unsigned int)rtc_time + seed);

	int rnd1 = rand();
	int rnd2 = rand();

	memcpy(mac, lmac_get_mac_address(0), 6);

	snprintf(g_ssid, sizeof(g_ssid), "S-%08X%02X%02X", rnd1 & 0xFFFFFFFF, mac[4], mac[5]);
	snprintf(g_password, sizeof(g_password), "%08X%02X%02X", rnd2 &0xFFFFFFFF, mac[4], mac[5]);

	app_log(DEBUG_LEVEL_INFO, NULL, "[AP] SSID/PASSWORD updated to: %s / %s\n", g_ssid, g_password);
	config_initialized = 1;
}

void softap_save_ssid_password(nvs_handle_t nvs_handle)
{
	nvs_set_str(nvs_handle, "ssid", g_ssid);
	nvs_set_str(nvs_handle, "wifi_password", g_password);
}

static void relay_save_config(nvs_handle_t nvs_handle)
{
	nvs_set_u32(nvs_handle, "ap_ip", softap_ip);
	nvs_set_str(nvs_handle, "ssid", g_ssid);
	nvs_set_str(nvs_handle, "relay_ssid", g_ssid);
	nvs_set_str(nvs_handle, "wifi_password", g_password);
}

static int create_ack_socket()
{
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {
		printf("[%s] socket open failed\n", __func__);
		return -1;
	}
	struct sockaddr_in addr = {
		.sin_family = AF_INET,
		.sin_port = htons(ACK_PORT),
		.sin_addr.s_addr = INADDR_ANY
	};

	if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		printf("[%s] bind failed\n", __func__);
		close(sock);
		return -1;
	}

	struct timeval timeout = {
		.tv_sec = 2,
		.tv_usec = 0
	};
	if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
		printf("[%s] socket option setting failed\n", __func__);
		close(sock);
		return -1;
	}

	return sock;
}

void send_reboot_sequence()
{
	int cnt = get_device_count();
	if (cnt <= 0) {
		return;
	}

	device_info_t *devs = get_device_list();
	int effective_device_count = 0;

	for (int i = 0; i < cnt; i++) {
		devs[i].reboot_acknowledged = 0;
		if (devs[i].ip.addr != 0) {
			effective_device_count++;
		}
	}

	if (ack_sock < 0) {
		ack_sock = create_ack_socket();
		if (ack_sock < 0) {
			app_log(DEBUG_LEVEL_ERROR, NULL, "[%s] Cannot create ACK socket\n", __func__);
			return;
		}
	}

	config_message_t msg;
	uint8_t send_multi = 0;
	nvs_get_u8(nvs_handle, "reboot_multi", &send_multi);
	prepare_reboot_message(&msg, 1);

	for (int cycle = 0; cycle < MAX_ACK_CHECK; cycle++) {
		if (device_list_get_reboot_ack_count() >= cnt) {
			break;
		}

		if (send_multi) {
			send_message_multicast(&msg);
		} else {
			for (int i = 0; i < cnt; i++) {
				if (!devs[i].reboot_acknowledged) {
					if (device_list[i].ip.addr != 0) {
						send_message_unicast(&devs[i].ip, &msg);
					}
					_delay_ms(10);
				}
			}
		}

		config_message_t ack;
		struct sockaddr_in src;
		socklen_t src_len = sizeof(src);
		int rem = 1000;

		while (rem > 0 && device_list_get_reboot_ack_count() < effective_device_count) {
			int r = recvfrom(ack_sock, &ack, sizeof(ack), 0,
							 (struct sockaddr*)&src, &src_len);
			if (r > 0
				&& ack.magic == CONFIG_MSG_MAGIC
				&& (ack.flags & CONFIG_FLAG_ACK_REPLY)
				&& ack.msg_type == CONFIG_MSG_TYPE_REBOOT) {
				// stamp local time and mark alive & ACK’d
				for (int i = 0; i < cnt; i++) {
					if (memcmp(devs[i].mac,
							   ack.payload.config.sender_mac, 6) == 0) {
						devs[i].timestamp = xTaskGetTickCount();
						devs[i].active = 1;
						devs[i].reboot_acknowledged = 1;
						app_log(DEBUG_LEVEL_INFO, NULL, "[%s] dev %d : %s reboot_acknowledged %d\n", __func__, i, ip4addr_ntoa(&devs[i].ip), devs[i].reboot_acknowledged);
					}
				}
			}

			if (r < 0) {
				break;
			}
			_delay_ms(100);
			rem -= 100;
		}
	}
}

void send_factoryreset_sequence()
{
	if (ack_sock < 0) {
		ack_sock = create_ack_socket();
		if (ack_sock < 0) {
			vTaskDelete(NULL);
			return;
		}
	}

	config_message_t msg;
	uint8_t send_multi = 0;
	nvs_get_u8(nvs_handle, "reboot_multi", &send_multi);

	prepare_device_list();

	prepare_factoryreset_message(&msg, 1);

	for (int cycle = 0; cycle < MAX_ACK_CHECK; cycle++) {
		if (device_list_get_factoryreset_ack_count() >= device_count) {
			app_log(DEBUG_LEVEL_INFO, NULL, "factoryreset_ack_count : %d, device_count : %d\n", device_list_get_factoryreset_ack_count(), device_count);
			break;
		}

		int effective_device_count = 0;

		if (send_multi) {
			send_message_multicast(&msg);
		} else {
			for (int i = 0; i < device_count; i++) {
				if (!device_list[i].factoryreset_acknowledged) {
					if (device_list[i].ip.addr != 0) {
						send_message_unicast(&device_list[i].ip, &msg);
						effective_device_count++;
					}
					_delay_ms(10);
				}
			}
		}

		config_message_t ack;
		struct sockaddr_in src;
		socklen_t src_len = sizeof(src);
		int rem = 1000;

		app_log(DEBUG_LEVEL_INFO, NULL, "[%s] WAIT FOR ACK...\n", __func__);
		while (rem > 0 && device_list_get_factoryreset_ack_count() < effective_device_count) {
			int r = recvfrom(ack_sock, &ack, sizeof(ack), 0,
							 (struct sockaddr*)&src, &src_len);
			if (r > 0
				&& ack.magic == CONFIG_MSG_MAGIC
				&& (ack.flags & CONFIG_FLAG_ACK_REPLY)
				&& ack.msg_type == CONFIG_MSG_TYPE_FACTORYRESET) {
				// stamp local time and mark alive & ACK’d
				for (int i = 0; i < device_count; i++) {
					if (memcmp(device_list[i].mac,
							   ack.payload.config.sender_mac, 6) == 0) {
						device_list[i].timestamp = xTaskGetTickCount();
						device_list[i].active = 1;
						device_list[i].factoryreset_acknowledged = 1;
						app_log(DEBUG_LEVEL_INFO, NULL, "[%s] dev %d : %s factoryreset_acknowledged %d\n",
								__func__, i, ip4addr_ntoa(&device_list[i].ip), device_list[i].factoryreset_acknowledged);
					}
				}
			}

			if (r < 0) {
				break;
			}
			_delay_ms(100);
			rem -= 100;
		}
	}
}

void ap_config_msg_task(void *pvParameters)
{
	uint8_t bssid_list[MAX_DEVICES][6];
	const uint8_t vif_id = 0;
	config_message_t msg;

	if (ack_sock < 0) {
		ack_sock = create_ack_socket();
		if (ack_sock < 0) {
			vTaskDelete(NULL);
			return;
		}
	}

	while (1) {
		int message_sent = 0;

		if(!config_initialized) {
			prepare_config_message(&msg, g_ssid, g_password, 1);
		}

		memset(bssid_list, 0, sizeof(bssid_list));
		uint16_t num = nrc_wifi_child_node_list(vif_id, bssid_list, get_max_device());

		for (int i = 0; i < num; i++) {
			int exists = 0;
			for (int j = 0; j < device_count; j++) {
				if (memcmp(bssid_list[i], device_list[j].mac, 6) == 0) {
					exists = 1;
					break;
				}
			}
			if (exists || device_count >= get_max_device()) {
				continue;
			}

			if (dhcps_get_ip(bssid_list[i], &device_list[device_count].ip)) {
				memcpy(device_list[device_count].mac, bssid_list[i], 6);
				device_list[device_count].config_updated = 0;
				device_list[device_count].reboot_acknowledged = 0;
				device_list[device_count].factoryreset_acknowledged = 0;
				device_list[device_count].active = 0;
				device_list[device_count].timestamp = xTaskGetTickCount();
				device_count++;
			}
		}

		if (device_count <= 0) {
			_delay_ms(1000);
			continue;
		}

		for (int i = 0; i < device_count; i++) {
			if (!device_list[i].config_updated) {
				if (device_list[i].ip.addr != 0) {
					send_message_unicast(&device_list[i].ip, &msg);
					message_sent++;
				}
			}
		}

		if (!message_sent) {
			_delay_ms(1000);
			continue;
		}

		for ( ; message_sent > 0 ; message_sent--) {
			config_message_t ack_msg;
			struct sockaddr_in src;
			socklen_t src_len = sizeof(src);

			int rcv = recvfrom(ack_sock,
							   &ack_msg,
							   sizeof(ack_msg),
							   0,
							   (struct sockaddr *) &src,
							   &src_len);

			if (rcv < 0) {
				if (errno != EAGAIN)
					app_log(DEBUG_LEVEL_ERROR, NULL, "[%s] recvfrom(), %s (%d)\n", __func__, strerror(errno), errno);
				continue;
			}

			if (ack_msg.magic != CONFIG_MSG_MAGIC) {
				app_log(DEBUG_LEVEL_ERROR, NULL, "[%s] invalid message\n", __func__);
				continue;
			}

			if ((ack_msg.flags & CONFIG_FLAG_ACK_REPLY) == 0) {
				continue;
			}

			for (int i = 0; i < device_count; i++) {
				if (memcmp(device_list[i].mac, ack_msg.payload.config.sender_mac, 6) != 0) {
					continue;
				}

				device_list[i].timestamp = xTaskGetTickCount();
				device_list[i].active = 1;

				if (ack_msg.msg_type == CONFIG_MSG_TYPE_UPDATE) {
					device_list[i].config_updated = 1;
					app_log(DEBUG_LEVEL_INFO, NULL, "[%s] dev %d : %s config_updated %d, active %d\n", __func__, i, ip4addr_ntoa(&device_list[i].ip), device_list[i].config_updated, device_list[i].active);
				}
			}
		}
	}

	close(ack_sock);
	vTaskDelete(NULL);
}

void sta_config_msg_task(void *pvParameters)
{
	system_role_t role = get_system_type();
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(COMM_PORT);
	addr.sin_addr.s_addr = INADDR_ANY;
	bind(sock, (struct sockaddr*)&addr, sizeof(addr));

	struct ip_mreq mreq;
	mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_GROUP);
	if (get_system_type() == ROLE_RELAY) {
		mreq.imr_interface.s_addr = htonl(br_netif.ip_addr.addr);
	} else {
		mreq.imr_interface.s_addr = htonl(nrc_netif[0]->ip_addr.addr);
	}

	if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "[STA] IP_ADD_MEMBERSHIP failed\n");
	}

	while (1) {
		fd_set read_fds;
		FD_ZERO(&read_fds);
		FD_SET(sock, &read_fds);
		struct timeval timeout = {1, 0};

		if (select(sock + 1, &read_fds, NULL, NULL, &timeout) > 0) {
			config_message_t msg;
			struct sockaddr_in src;
			socklen_t len = sizeof(src);
			int rcv_len = recvfrom(sock, &msg, sizeof(msg), 0, (struct sockaddr*)&src, &len);

			if (rcv_len < sizeof(uint32_t)) continue;
			if (msg.magic != CONFIG_MSG_MAGIC) continue;

			switch (msg.msg_type) {
				case CONFIG_MSG_TYPE_UPDATE:
					app_log(DEBUG_LEVEL_INFO, NULL, "[STA] Received SSID: %s\n", msg.payload.config.ssid);
					app_log(DEBUG_LEVEL_INFO, NULL, "[STA] Received PASSWORD: %s\n", msg.payload.config.password);
					if (msg.flags & CONFIG_FLAG_ACK_REQUEST) {
						if (role == ROLE_RELAY) {
							memcpy(msg.payload.config.sender_mac, br_netif.hwaddr, 6);
						} else {
							memcpy(msg.payload.config.sender_mac, lmac_get_mac_address(0), 6);
						}
						msg.flags = CONFIG_FLAG_ACK_REPLY;
						msg.length = 0;
						msg.crc32 = util_crc_compute_crc32((uint8_t*)&msg, sizeof(msg) - sizeof(uint32_t));
						src.sin_port = htons(ACK_PORT);
						msg.payload.config.timestamp = xTaskGetTickCount();
#ifndef FEATURE_EXTENDER
						sendto(sock, &msg, sizeof(msg), 0, (struct sockaddr*)&src, sizeof(src));
#endif
						app_log(DEBUG_LEVEL_INFO, NULL, "[STA] Sent ACK for CONFIG\n");
						softap_ip = src.sin_addr.s_addr;
						strcpy(g_ssid, msg.payload.config.ssid);
						strcpy(g_password, msg.payload.config.password);
						relay_save_config(nvs_handle);
					}
					break;
				case CONFIG_MSG_TYPE_REBOOT:
					app_log(DEBUG_LEVEL_INFO, NULL, "[STA] Received REBOOT command\n");
					if (msg.flags & CONFIG_FLAG_ACK_REQUEST) {
						if (role == ROLE_RELAY) {
							memcpy(msg.payload.config.sender_mac, br_netif.hwaddr, 6);
						} else {
							memcpy(msg.payload.config.sender_mac, lmac_get_mac_address(0), 6);
						}
						msg.flags = CONFIG_FLAG_ACK_REPLY;
						msg.length = 0;
						msg.crc32 = util_crc_compute_crc32((uint8_t*)&msg, sizeof(msg) - sizeof(uint32_t));
						src.sin_port = htons(ACK_PORT);
						msg.payload.config.timestamp = xTaskGetTickCount();
						sendto(sock, &msg, sizeof(msg), 0, (struct sockaddr*)&src, sizeof(src));
						app_log(DEBUG_LEVEL_INFO, NULL, "[STA] Sent ACK for REBOOT\n");
					}

					// Wait for stations connected to this relay is all removed.
					while (nrc_wifi_softap_get_sta_num(0)) {
						_delay_ms(1000);
					}

					_delay_ms(3000);
					wifi_set_provisioned(nvs_handle, 1);
					system_modem_api_remove_fc();
					if (role == ROLE_RELAY) {
						nrc_wifi_disconnect(1, 3000);
					} else {
						nrc_wifi_disconnect(0, 3000);
					}
					nrc_sw_reset();
					break;
				case CONFIG_MSG_TYPE_FACTORYRESET:
					app_log(DEBUG_LEVEL_INFO, NULL, "[STA] Received FACTORYRESET command\n");
					if (msg.flags & CONFIG_FLAG_ACK_REQUEST) {
						if (role == ROLE_RELAY) {
							memcpy(msg.payload.config.sender_mac, br_netif.hwaddr, 6);
						} else {
							memcpy(msg.payload.config.sender_mac, lmac_get_mac_address(0), 6);
						}
						msg.flags = CONFIG_FLAG_ACK_REPLY;
						msg.length = 0;
						msg.crc32 = util_crc_compute_crc32((uint8_t*)&msg, sizeof(msg) - sizeof(uint32_t));
						src.sin_port = htons(ACK_PORT);
						msg.payload.config.timestamp = xTaskGetTickCount();
						sendto(sock, &msg, sizeof(msg), 0, (struct sockaddr*)&src, sizeof(src));
						app_log(DEBUG_LEVEL_INFO, NULL, "[STA] Sent ACK for FACTORYRESET\n");
					}

					// Wait for stations connected to this relay is all removed.
					while (nrc_wifi_softap_get_sta_num(0)) {
						_delay_ms(1000);
					}

					_delay_ms(3000);
					if (role == ROLE_RELAY) {
						nrc_wifi_disconnect(1, 3000);
					} else {
						nrc_wifi_disconnect(0, 3000);
					}
					// Factory reset by erase nvs contents
					nvs_erase_all(nvs_handle);
					system_modem_api_remove_fc();
					nrc_sw_reset();
					break;
				default:
					app_log(DEBUG_LEVEL_ALWAYS, NULL, "[STA] Unknown message type: %d\n", msg.msg_type);
					break;
			}
		}
	}
}

static int find_device_with_macaddr(const uint8_t mac[])
{
	for (int i = 0; i < device_count; i++) {
		if (memcmp(device_list[i].mac, mac, 6) == 0)
			return i;
	}
	return -1;
}

static int find_device_with_ipaddr(const ip4_addr_t *ip)
{
	for (int i = 0; i < device_count; i++) {
		if (ip4_addr_cmp(&device_list[i].ip, ip))
			return i;
	}
	return -1;
}

int device_list_get_active_count(void)
{
    int count = 0;
    for (int i = 0; i < device_count; i++) {
        if (device_list[i].active) {
			count++;
		}
	}
    return count;
}

int device_list_get_reboot_ack_count(void)
{
	int count = 0;
	for (int i = 0; i < device_count; i++) {
		if (device_list[i].reboot_acknowledged) {
			count++;
		}
	}
	return count;
}

int device_list_get_factoryreset_ack_count(void)
{
	int count = 0;
	for (int i = 0; i < device_count; i++) {
		if (device_list[i].factoryreset_acknowledged) {
			count++;
		}
	}
	return count;
}

int device_list_update_active (const char *str_ip, const uint8_t mac[], const uint8_t sa[])
{
	ip4_addr_t ip;
	uint8_t _mac[6];
	int idx;

	if (!str_ip || !ip4addr_aton(str_ip, &ip) || ip4_addr_isany(&ip))
	{
		app_log(DEBUG_LEVEL_ERROR, NULL, "invalid ip address, %s\n", str_ip);
		return -EINVAL;
	}

	if (!mac)
	{
		if (!dhcps_get_mac(&ip, _mac))
		{
			app_log(DEBUG_LEVEL_ERROR, NULL, "dhcps_get_mac() failed, ip=%s\n", str_ip);
			return -1;
		}

		mac = _mac;
	}

	idx = find_device_with_macaddr(mac);
	if (idx < 0)
	{
		if (device_count < get_max_device())
		{
			idx = device_count;
			device_count++;
		}
		else
		{
			uint8_t zero_mac[6];

			memset(zero_mac, 0x00, 6);

			app_log(DEBUG_LEVEL_ERROR, NULL, "device_count (%d) >= max_device (%d)\n",
					device_count, get_max_device());

			for (idx = 0; idx < device_count ; idx++)
			{
				if (memcmp(device_list[idx].mac, zero_mac, 6) == 0 || ip4_addr_isany(&device_list[idx].ip))
				{
					app_log(DEBUG_LEVEL_ERROR, NULL, "[%s] invalid device list, idx=%d\n", __func__, idx);
					print_device_list(idx);
					break;
				}
			}

			if (idx >= device_count)
				return -1;
		}
	}

	device_list[idx].timestamp = xTaskGetTickCount();

/*	nrc_usr_print("[%s] %s, idx=%d active=%d timestamp=%u\n", __func__,
		str_ip, idx, device_list[idx].active, device_list[idx].timestamp); */
	if (is_valid_sa(sa)) {
#ifdef DEVICE_EXT_SA
		if (sa[0] != 0x20)
			memcpy(device_list[idx].ext_sa, sa, SA_LEN);
		else
#endif
		memcpy(device_list[idx].sa, sa, SA_LEN);
	}

	if (!device_list[idx].active)
	{
		device_list[idx].active = 1;
		ip4_addr_set(&device_list[idx].ip, &ip);
		if (mac)
			memcpy(device_list[idx].mac, mac, 6);
		else //if (!dhcps_get_mac(&ip, device_list[idx].mac))
			memset(device_list[idx].mac, 0, 6);

		app_log(DEBUG_LEVEL_ALWAYS, NULL, "[AP] ACTIVE : idx=%d mac=%02X:%02X:%02X:%02X:%02X:%02X ip=%s sa=%02X:%02X:%02X\n",
				idx, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], str_ip, sa[0], sa[1], sa[2]);
		print_device_list(idx);
	}

	return 0;
}

void device_list_check_active (uint16_t *count)
{
	TickType_t active_timeout = pdMS_TO_TICKS(60 * 1000);
	TickType_t cur_time;
	TickType_t diff_time;
	uint64_t device_timestamp;
	uint16_t cnt;
	int idx;
	uint16_t ka_timeout = 10;
	uint16_t ka_timeout_provisioned = 60;

	nvs_get_u16(nvs_handle, "ka_timeout",  &ka_timeout);
	nvs_get_u16(nvs_handle, "ka_timeout_pr",  &ka_timeout_provisioned);

	if (wifi_is_provisioned() && (ka_timeout_provisioned > 0))
	{
		// if keepalive duration for provisioned state is set, use it as timeout value
		active_timeout = pdMS_TO_TICKS(ka_timeout_provisioned * 1000);
	}
	else if (ka_timeout > 0)
	{
		// if keepalive duration is set, use it as timeout value
		active_timeout = pdMS_TO_TICKS(ka_timeout * 1000);
	}

	for (cnt = idx = 0; idx < device_count; idx++)
	{
		if (device_list[idx].active)
		{
			device_timestamp = device_list[idx].timestamp;
			cur_time = xTaskGetTickCount();
			diff_time = cur_time - device_timestamp;

			if (diff_time <= active_timeout)
				cnt++;
			else
			{
				ip4_addr_t *ip = &device_list[idx].ip;
				uint8_t *mac = device_list[idx].mac;
				uint8_t *sa = device_list[idx].sa;
#ifdef DEVICE_EXT_SA
				uint8_t *ext_sa = device_list[idx].ext_sa;
#endif

				device_list[idx].active = 0;
				device_list[idx].config_updated = 0;

#ifdef DEVICE_EXT_SA
				app_log(DEBUG_LEVEL_ALWAYS, NULL, "[AP] INACTIVE : idx=%d mac=%02X:%02X:%02X:%02X:%02X:%02X ip=%s sa=%02X:%02X:%02X ext_sa=%02X:%02X:%02X\n",
						idx, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], ip4addr_ntoa(ip), sa[0], sa[1], sa[2], ext_sa[0], ext_sa[1], ext_sa[2]);
#else
				app_log(DEBUG_LEVEL_ALWAYS, NULL, "[AP] INACTIVE : idx=%d mac=%02X:%02X:%02X:%02X:%02X:%02X ip=%s sa=%02X:%02X:%02X\n",
						idx, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], ip4addr_ntoa(ip), sa[0], sa[1], sa[2]);
#endif
				print_device_list(idx);
			}
		}
	}

	if (count)
		*count = cnt;
}

static void ap_keepalive_server_task(void *pvParameters)
{
	// Create listen socket for keep alive
	int keepalive_sock = -1;

	keepalive_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (keepalive_sock < 0) {
		vTaskDelete(NULL);
		return;
	}

	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(KEEPALIVE_PORT);
	addr.sin_addr.s_addr = INADDR_ANY;
	bind(keepalive_sock, (struct sockaddr *)&addr, sizeof(addr));

	app_log(DEBUG_LEVEL_ALWAYS, NULL, "[AP] Keepalive listener up on port %d\n", KEEPALIVE_PORT);

	fd_set read_fds;
	struct timeval timeout;

	// update dev list
	while (1) {
		FD_ZERO(&read_fds);
		FD_SET(keepalive_sock, &read_fds);
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;

		int ret = select(keepalive_sock + 1, &read_fds, NULL, NULL, &timeout);
		if (ret > 0 && FD_ISSET(keepalive_sock, &read_fds)) {
			keepalive_pkt_t pkt;
			struct sockaddr_in src;
			socklen_t len = sizeof(src);

			int r = recvfrom(keepalive_sock, &pkt, sizeof(pkt), 0, (struct sockaddr *)&src, &len);
			if (r == sizeof(pkt)) {
#if 0
				int idx = find_device_with_macaddr(pkt.mac);
				int64_t now = xTaskGetTickCount();
				if (idx >= 0) {
					device_list[idx].timestamp = now;
					device_list[idx].ip = pkt.ip;
					device_list[idx].active = 1;
				} else if (device_count < get_max_device()) {
					memcpy(device_list[device_count].mac, pkt.mac, 6);
					device_list[device_count].ip = pkt.ip;
					device_list[device_count].timestamp = now;
					device_list[device_count].active = 1;
					device_count++;
				}
#else
				device_list_update_active(inet_ntoa(src.sin_addr), pkt.mac, NULL);
#endif

				app_log(DEBUG_LEVEL_ALWAYS, NULL, "[AP] Keepalive received from %s. (%02X:%02X:%02X:%02X:%02X:%02X)\n",
						ip4addr_ntoa(&pkt.ip),
						pkt.mac[0], pkt.mac[1], pkt.mac[2], pkt.mac[3], pkt.mac[4], pkt.mac[5]);

				// send ACK back to relay
				// here we simply echo back the same packet as an ACK
				sendto(keepalive_sock,
					&pkt, sizeof(pkt), 0,
					(struct sockaddr *)&src, len);
			}
		}
	}
}

void start_keepalive_server_task()
{
	xTaskCreate(ap_keepalive_server_task, "ap keealive server", 1024, NULL, USER_APP_TASK_PRIORITY, NULL);
}

static void relay_send_keepalive(int sock)
{
	const int retry_max = 10;
	const int retry_interval = 100;
	keepalive_pkt_t pkt;
	uint32_t ap_ip;
	struct sockaddr_in destaddr;
	int ret;
	int i;

	if (nvs_get_u32(nvs_handle, "ap_ip", &ap_ip) != NVS_OK) {
		if (softap_ip) {
			ap_ip = softap_ip;
		} else {
			return;
		}
	}

	if (get_system_type() == ROLE_RELAY) {
		memcpy(pkt.mac, br_netif.hwaddr, 6);
		memcpy(&pkt.ip, (ip4_addr_t *) &br_netif.ip_addr, sizeof(pkt.ip));
	} else {
		memcpy(pkt.mac, lmac_get_mac_address(0), 6);
		memcpy(&pkt.ip, (ip4_addr_t *) &nrc_netif[0]->ip_addr, sizeof(pkt.ip));
	}
	pkt.timestamp = xTaskGetTickCount();

	memset(&destaddr, 0, sizeof(destaddr));
	destaddr.sin_family = AF_INET;
	destaddr.sin_port = htons(KEEPALIVE_PORT);
	destaddr.sin_addr.s_addr = ap_ip;

	for (i = 0 ; i < retry_max ; i++) {
		ret = sendto(sock, (char *) &pkt, sizeof(pkt), 0, (struct sockaddr *)&destaddr, sizeof(destaddr));
		if (ret > 0) {
			app_log(DEBUG_LEVEL_ALWAYS, NULL, "[STA] Keepalive sent %d, %s (%02X:%02X:%02X:%02X:%02X:%02X)\n",
					i, ip4addr_ntoa(&pkt.ip),
					pkt.mac[0], pkt.mac[1], pkt.mac[2], pkt.mac[3], pkt.mac[4], pkt.mac[5]);
			break;
		}

		if (errno != ENOMEM && errno != EAGAIN)	{
			app_log(DEBUG_LEVEL_ERROR, NULL, "[STA] Keepalive sent, %s (%d)\n", strerror(errno), errno);
			break;
		}

		_delay_ms(retry_interval);
	}
}

static void relay_keepalive_task(void *pvParameters)
{
#if defined(KEEPALIVE_INTERVAL)
	uint16_t ka_interval = KEEPALIVE_INTERVAL;
#else
	uint16_t ka_interval = 2;
#endif
#if defined(KEEPALIVE_DURATION)
	uint16_t ka_duration = KEEPALIVE_DURATION;
#else
	uint16_t ka_duration = 0;
#endif
	uint16_t ka_interval_provisioned = 15;
	uint16_t ka_wait = 2000;

	nvs_get_u16(nvs_handle, "ka_interval", &ka_interval);
	nvs_get_u16(nvs_handle, "ka_interval_pr", &ka_interval_provisioned);
	nvs_get_u16(nvs_handle, "ka_duration",  &ka_duration);
	nvs_get_u16(nvs_handle, "ka_wait", &ka_wait);

	TickType_t start_tick = xTaskGetTickCount();
	int keepalive_sock = -1;
	int ack_received = 0;
	fd_set read_fds;
	struct timeval tv;

	app_log(DEBUG_LEVEL_ALWAYS, NULL, "[STA] Keepalive task started. (interval:%u, duration:%u)\n",
			ka_interval, ka_duration);

	// Create a socket
    if ((keepalive_sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        app_log(DEBUG_LEVEL_ERROR, NULL, "[ERROR] Unable to create socket. Errno: %d\n", errno);
        return;
    }

	while (!ack_received) {
		if (ka_duration > 0 && (xTaskGetTickCount() - start_tick) < pdMS_TO_TICKS(ka_duration * 1000)) {
			app_log(DEBUG_LEVEL_ALWAYS, NULL, "[STA] Keepalive duration expired!\n");
			break;
		}

		relay_send_keepalive(keepalive_sock);

		// wait up to ka_interval seconds for an ACK
		FD_ZERO(&read_fds);
		FD_SET(keepalive_sock, &read_fds);
		tv.tv_sec  = ka_wait / 1000;
		tv.tv_usec = (ka_wait % 1000) * 1000;

		int ret = select(keepalive_sock + 1, &read_fds, NULL, NULL, &tv);
		if (ret > 0 && FD_ISSET(keepalive_sock, &read_fds)) {
			keepalive_pkt_t ack_pkt;
			struct sockaddr_in src;
			socklen_t len = sizeof(src);

			int r = recvfrom(keepalive_sock,
							 &ack_pkt, sizeof(ack_pkt), 0,
							 (struct sockaddr *)&src, &len);
			if (r == sizeof(ack_pkt)) {
				// assume any matching MAC is our ACK
				// ack_received = 1;
				app_log(DEBUG_LEVEL_ALWAYS, NULL, "[STA] Keepalive ACK received from AP\n");
			}
		}
		if (wifi_is_provisioned())
			vTaskDelay(pdMS_TO_TICKS(ka_interval_provisioned * 1000));
		else
			vTaskDelay(pdMS_TO_TICKS(ka_interval * 1000));
	}

	app_log(DEBUG_LEVEL_ALWAYS, NULL, "[STA] Keepalive task stopped\n");

	// either duration expired or ACK received ⇒ stop this task
	vTaskDelete(NULL);
}

void start_keepalive_task()
{
	xTaskCreate(relay_keepalive_task, "Keepalive", 512, NULL, USER_APP_TASK_PRIORITY, NULL);
}
