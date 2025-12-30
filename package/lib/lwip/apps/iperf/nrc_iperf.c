/*
 * MIT License
 *
 * Copyright (c) 2021 Newracom, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <string.h>
#include <stdbool.h>

#include "nrc_lwip.h"
#include "nrc_iperf.h"
#include "nrc_iperf_tcp.h"
#include "nrc_iperf_udp.h"

#ifdef SUPPORT_ETHERNET_ACCESSPOINT
#include "nrc_eth_if.h"
#endif /* SUPPORT_ETHERNET_ACCESSPOINT */

#define CONFIG_TASK_PRIORITY_IPERF		LWIP_IPERF_TASK_PRIORITY
#define CONFIG_TASK_STACKSIZE_IPERF		LWIP_IPERF_TASK_STACK_SIZE

#define IPERF_SUPPORT_MULTIPLE_PORT 0

extern void sys_arch_msleep(u32_t delay_ms);

/********************************************************************************/

#define WARN_ON(condition) \
({ \
	 int warn_on = !!(condition); \
	 if(warn_on) \
		 CPA("[WARN] %s at %s:%d\n", __FUNCTION__, __FILE__, __LINE__); \
	 warn_on; \
 })

typedef struct mutex
{
	SemaphoreHandle_t handle;
} spinlock_t;

static void mutex_init (struct mutex *m)
{
	SemaphoreHandle_t handle = xSemaphoreCreateMutex();

	if (!WARN_ON(!m || !handle))
		m->handle = handle;
}

static void mutex_lock (struct mutex *m)
{
	if (!WARN_ON(!m || !m->handle))
		WARN_ON(xSemaphoreTake(m->handle, portMAX_DELAY) !=pdTRUE);
}

static void mutex_unlock (struct mutex *m)
{
	if (!WARN_ON(!m || !m->handle))
		WARN_ON(xSemaphoreGive(m->handle) !=pdTRUE);
}

/********************************************************************************/

struct list_head
{
        struct list_head *next, *prev;
};

static void INIT_LIST_HEAD (struct list_head *list)
{
	list->next = list;
	list->prev = list;
}

static void __list_add (struct list_head *new, struct list_head *prev, struct list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

static void list_add (struct list_head *new, struct list_head *head)
{
	__list_add(new, head, head->next);
}

static void list_add_tail(struct list_head *new, struct list_head *head)
{
	__list_add(new, head->prev, head);
}

static void __list_del (struct list_head * prev, struct list_head * next)
{
	next->prev = prev;
	prev->next = next;
}

static void __list_del_entry (struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
}

static void list_del (struct list_head *entry)
{
	__list_del_entry(entry);
	entry->next = entry;
	entry->prev = entry;
}

static inline bool list_empty(const struct list_head *head)
{
	return head->next == head;
}

#define list_entry(ptr, type, member)		container_of(ptr, type, member)
#define list_first_entry(ptr, type, member) list_entry((ptr)->next, type, member)
#define list_next_entry(pos, member) 		list_entry((pos)->member.next, typeof(*(pos)), member)
#define list_for_each_entry_safe(pos, n, head, member)       \
	for (pos = list_first_entry(head, typeof(*pos), member), \
			n = list_next_entry(pos, member);                \
			&pos->member != (head);                          \
			pos = n, n = list_next_entry(n, member))

/********************************************************************************/
#if !defined(DISABLE_IPERF_APP)
#if defined(LWIP_IPERF) && (LWIP_IPERF == 1)

static spinlock_t iperf_lock = {
	.handle = NULL
};

static struct list_head iperf_head = {
	.next = NULL,
	.prev = NULL
};

struct iperf_task {
	iperf_opt_t* option;
	struct list_head list;
};

extern struct netif* nrc_netif[MAX_IF];
#if LWIP_BRIDGE
extern struct netif br_netif;
#endif /* LWIP_BRIDGE */
#ifdef SUPPORT_ETHERNET_ACCESSPOINT
extern struct netif eth_netif;
#endif /* SUPPORT_ETHERNET_ACCESSPOINT */

static const char *module_name()
{
	return "iperf : ";
}

static const struct {
	const char *name;
	int value;
} ipqos[] = {
	{ "af11", IPTOS_DSCP_AF11 },
	{ "af12", IPTOS_DSCP_AF12 },
	{ "af13", IPTOS_DSCP_AF13 },
	{ "af21", IPTOS_DSCP_AF21 },
	{ "af22", IPTOS_DSCP_AF22 },
	{ "af23", IPTOS_DSCP_AF23 },
	{ "af31", IPTOS_DSCP_AF31 },
	{ "af32", IPTOS_DSCP_AF32 },
	{ "af33", IPTOS_DSCP_AF33 },
	{ "af41", IPTOS_DSCP_AF41 },
	{ "af42", IPTOS_DSCP_AF42 },
	{ "af43", IPTOS_DSCP_AF43 },
	{ "cs0", IPTOS_DSCP_CS0 },
	{ "cs1", IPTOS_DSCP_CS1 },
	{ "cs2", IPTOS_DSCP_CS2 },
	{ "cs3", IPTOS_DSCP_CS3 },
	{ "cs4", IPTOS_DSCP_CS4 },
	{ "cs5", IPTOS_DSCP_CS5 },
	{ "cs6", IPTOS_DSCP_CS6 },
	{ "cs7", IPTOS_DSCP_CS7 },
	{ "ef", IPTOS_DSCP_EF },
	{ "lowdelay", IPTOS_LOWDELAY },
	{ "throughput", IPTOS_THROUGHPUT },
	{ "reliability", IPTOS_RELIABILITY },
	{ NULL, -1 }
};

static const char* tos_to_string(int tos)
{
	for (int i = 0; ipqos[i].value != -1; i++) {
		if (ipqos[i].value == tos) {
			return ipqos[i].name;
		}
	}
	return "Unknown";
}

static int parse_qos(const char *cp)
{
	unsigned int i;
	char *ep = NULL;
	long val;

	if (cp == NULL)
		return -1;
	for (i = 0; ipqos[i].name != NULL; i++) {
		if (strcasecmp(cp, ipqos[i].name) == 0)
			return ipqos[i].value;
	}
	/* Try parsing as an integer */
	val = strtol(cp, &ep, 0);
	if (*cp == '\0' || *ep != '\0' || val < 0 || val > 255)
		return -1;
	return val;
}

int iperf_get_time (iperf_time_t *time)
{
	*time = system_get_time() / 1000.0;

	return 0;
}

bool iperf_time_expried(iperf_time_t start_time, iperf_time_t duration)
{
	iperf_time_t now;
	iperf_get_time(&now);

	if(now >= start_time+duration)
		return true;
	else
		return false;
}

uint32_t byte_to_bps (iperf_time_t time, uint32_t byte)
{
	if (time <= 0.0) {
		return 0;
	}
	return (uint32_t)((8.0 * byte) / time);
}

char *byte_to_string (uint32_t byte)
{
	static char buf[20];

	if (byte < 1000)
		snprintf(buf, sizeof(buf), "%lu ", (unsigned long)byte);
	else if (byte < (1000 * 1000))
		snprintf(buf, sizeof(buf), "%4.2f K", byte / 1000.0);
	else
		snprintf(buf, sizeof(buf), "%4.2f M", byte / 1000000.0);

	return buf;
}

char *bps_to_string (uint32_t bps)
{
	static char buf[20];

	if (bps < 1000)
		snprintf(buf, sizeof(buf), "%lu ", bps);
	else if (bps < (1000 * 1000))
		snprintf(buf, sizeof(buf), "%4.2f K", bps / 1000.0);
	else
		snprintf(buf, sizeof(buf), "%4.2f M", (bps / 1000.0) / 1000.0);

	return buf;
}

void iperf_format_output(uint64_t bytes, uint32_t bps, char format,
                         float *byte_disp, float *bps_disp,
                         char *byte_unit_str, size_t byte_unit_len,
                         char *bps_unit_str, size_t bps_unit_len)
{
	char unit_byte = 'B', unit_bps = 'b';

	switch (format) {
		case 'M':
		case 'm':
			*byte_disp = bytes / 1000000.0f;
			*bps_disp  = bps / 1000000.0f;
			unit_byte = unit_bps = 'M';
			break;

		case 'K':
		case 'k':
			*byte_disp = bytes / 1000.0f;
			*bps_disp  = bps / 1000.0f;
			unit_byte = unit_bps = 'K';
			break;

		case 'B':
		case 'b':
			*byte_disp = (float)bytes;
			*bps_disp  = (float)bps;
			unit_byte = 'B';
			unit_bps  = 'b';
			break;

		default:
		case 'a':
		case 'A':
			if (bytes >= 1000000) {
				*byte_disp = bytes / 1000000.0f;
				unit_byte = 'M';
			} else if (bytes >= 1000) {
				*byte_disp = bytes / 1000.0f;
				unit_byte = 'K';
			} else {
				*byte_disp = (float)bytes;
				unit_byte = 'B';
			}

			if (bps >= 1000000) {
				*bps_disp = bps / 1000000.0f;
				unit_bps = 'M';
			} else if (bps >= 1000) {
				*bps_disp = bps / 1000.0f;
				unit_bps = 'K';
			} else {
				*bps_disp = (float)bps;
				unit_bps = 'b';
			}
			break;
	}

	// Write formatted strings
	snprintf(byte_unit_str, byte_unit_len,
	         (unit_byte == 'B') ? "Bytes" : "%cB", unit_byte);

	snprintf(bps_unit_str, bps_unit_len,
	         (unit_bps == 'b') ? "bps" : "%cbps", unit_bps);
}


static void iperf_option_help (char *cmd)
{
	CPA("Usage: %s <-s|-c host> [options]\n", cmd);
	CPA("\r\n");
	CPA("Client/Server:\n");
	CPA("  -b, --bandwidth #[kmKM] bandwidth to send at in bits/sec\n");
	CPA("  -p, --port #              server port to listen/connect (default: %d)\n", IPERF_DEFAULT_SERVER_PORT);
	CPA("  -u, --udp                 use UDP instead of TCP\n");
	CPA("  -S, --tos #               set socket IP_TOS\n");
	CPA("  -i, --interval #          report interval in seconds\n");
	CPA("  -g, --sendInterval #      TCP send interval (ms)\n");
	CPA("  -N, --nodelay             set TCP_NODELAY (disable Nagle)\n");
	CPA("  -B, --bind <host>         bind to <host>, an interface or multicast address\n");
	CPA("  -l, --len #[kmKM]         length of buffer in bytes to read or write\n");
	CPA("  -f, --format [kmKM]       format to report\n");
	CPA("\r\n");
	CPA("Server specific:\n");
	CPA("  -s, --server              run in server mode\n");
	CPA("\r\n");
	CPA("Client specific:\n");
	CPA("  -c, --client <host>       run in client mode, connecting to <host>\n");
	CPA("  -t, --time #              transmit duration (seconds, default: %d)\n", IPERF_DEFAULT_SEND_TIME);
	CPA("\r\n");
	CPA("Miscellaneous:\n");
	CPA("  -h, --help                show help message\n");
	CPA("\r\n");
}

#if 0
static void iperf_option_print(iperf_opt_t *option)
{
	CPA("[ IPERF OPTION ]\n");

	CPA(" - Role               : %s\n",
		(option->mThreadMode == kMode_Server) ? "Server" :
		(option->mThreadMode == kMode_Client) ? "Client" : "Unknown");

	CPA(" - Protocol           : %s\n", option->mUDP ? "UDP" : "TCP");
	CPA(" - Port               : %d\n", option->mPort);
	CPA(" - Remote IP          : %s\n", ip4addr_ntoa((const ip4_addr_t*)ip_2_ip4(&option->addr)));

	if (!ip_addr_isany(&option->bindAddr)) {
		CPA(" - Bind Address (-B)  : %s\n", ip4addr_ntoa((const ip4_addr_t*)ip_2_ip4(&option->bindAddr)));
	} else {
		CPA(" - Bind Address (-B)  : N/A\n");
	}

	CPA(" - Duration (Time)    : %ld sec\n", option->mAmount / 100);
	CPA(" - TOS (DSCP)         : 0x%02X (%s)\n", option->mTOS, tos_to_string(option->mTOS));
	CPA(" - Interval           : %ld ms\n", option->mInterval);
	CPA(" - Buffer Length      : %ld bytes\n", option->mBufLen);
	CPA(" - TCP no delay       : %s\n", option->mNodelay ? "Enabled" : "Disabled");

	char fmt = option->mFormat ? option->mFormat : 'b';
	const char *fmt_desc = NULL;

	switch (fmt) {
		case 'k': case 'K': fmt_desc = "kilobyte (10^3)"; break;
		case 'm': case 'M': fmt_desc = "megabyte (10^6)"; break;
		case 'a': case 'A': fmt_desc = "Auto"; break;
		case 'b': case 'B': default:
			fmt_desc = "byte";
			break;
	}

	CPA(" - Format to report   : %c (%s)\n", fmt, fmt_desc);

	if (option->mUDP && option->mThreadMode == kMode_Client) {
		CPA(" - Data Rate (UDP)    : %ld bps\n", option->mAppRate);
		CPA(" - Send Interval (UDP): %ld usec\n", option->mSendInterval);
	}

	CPA("\n");
}
#endif

iperf_opt_t * iperf_option_alloc(void)
{
	iperf_opt_t* option = NULL;
	int i = 0;

	while(1) {
		option = (iperf_opt_t *)mem_malloc(sizeof(iperf_opt_t));
		if(option)
			break;

		if(i == 50){
			CPA("%s memory allocation fail!\n", module_name());
			return NULL;
		} else {
			sys_arch_msleep(100);
			i++;
		}
	}
	memset(option, 0x0, sizeof(iperf_opt_t));
	return option;
}

void iperf_option_free(iperf_opt_t* option)
{
	if (option != NULL)
		mem_free(option);
}

void nrc_iperf_spin_lock_init(void)
{
	mutex_init(&iperf_lock);
}

void nrc_iperf_spin_lock(void)
{
	mutex_lock(&iperf_lock);
}

void nrc_iperf_spin_unlock(void)
{
	mutex_unlock(&iperf_lock);
}

int nrc_iperf_list_init(void)
{
	nrc_iperf_spin_lock_init();
	INIT_LIST_HEAD(&iperf_head);
	return 0;
}

void nrc_iperf_list_deinit(void)
{
	struct iperf_task *cur, *next;

	nrc_iperf_spin_lock();
	list_for_each_entry_safe(cur, next, &iperf_head, list) {
		list_del(&cur->list);
		if(cur) mem_free(cur);
	}
	nrc_iperf_spin_unlock();
}

static void nrc_iperf_list_print(void)
{
	struct iperf_task *cur, *next;

	list_for_each_entry_safe(cur, next, &iperf_head, list) {
		CPA("%s ", (cur->option->mUDP == 1) ?  "UDP" : "TCP");
		CPA("%s :", (cur->option->mThreadMode == kMode_Server) ?  "Server" : "Client");
		CPA("%s:%d\n", ip4addr_ntoa((const ip4_addr_t*)ip_2_ip4(&cur->option->addr)),cur->option->mPort);
	}
}

int nrc_iperf_task_list_add(iperf_opt_t* option)
{
	struct iperf_task *task;
	struct iperf_task *cur, *next;
	int i = 0;

	nrc_iperf_spin_lock();
	list_for_each_entry_safe(cur, next, &iperf_head, list) {
		if ((option->mThreadMode == cur->option->mThreadMode) &&
#if IPERF_SUPPORT_MULTIPLE_PORT
				(option->mPort == cur->option->mPort) &&
#endif
				(option->mUDP == cur->option->mUDP) &&
				(ip_addr_cmp(&cur->option->addr,&option->addr))) {
			nrc_iperf_spin_unlock();
			return -1;
		}
	}
	nrc_iperf_spin_unlock();

	while(1) {
		task = mem_malloc(sizeof(struct iperf_task));
		if(task)
			break;

		if(i == 50){
			CPA("%s memory allocation fail!\n", module_name());
			return -1;
		} else {
			sys_arch_msleep(100);
			i++;
		}
	}
	task->option = option;
	INIT_LIST_HEAD(&task->list);

	nrc_iperf_spin_lock();
	list_add_tail(&task->list, &iperf_head);
	nrc_iperf_spin_unlock();

	return 0;
}

int nrc_iperf_task_list_del(iperf_opt_t* option)
{
	struct iperf_task *cur, *next;
	int ret = -1;

	nrc_iperf_spin_lock();
	list_for_each_entry_safe(cur, next, &iperf_head, list) {
		if ((option->mThreadMode == cur->option->mThreadMode) &&
#if IPERF_SUPPORT_MULTIPLE_PORT
				(option->mPort == cur->option->mPort) &&
#endif
				(option->mUDP == cur->option->mUDP) &&
				(ip_addr_cmp(&cur->option->addr,&option->addr))) {
			list_del(&cur->list);
			if(cur) mem_free(cur);
			ret = 0;
			break;
		}
	}
	nrc_iperf_spin_unlock();

	return ret;
}

void nrc_iperf_periodic_report(void *pvParameters)
{
	iperf_opt_t *option = (iperf_opt_t *) pvParameters;
	iperf_time_t last_report = 0.0;
	uint64_t last_byte_count_reported = 0;
	uint64_t processing_start_time = 0;
	uint64_t processing_end_time = 0;
	uint64_t processing_time = 0;
	uint64_t processing_sleep_duration = 0;

	char peer_addr[INET_ADDRSTRLEN];

	while (1) {
		uint64_t byte = 0;
		uint32_t bps = 0;
		float byte_disp = 0.0f, bps_disp = 0.0f;
		char byte_unit_str[8];
		char bps_unit_str[8];
		char format;
		iperf_time_t interval;

		processing_start_time = system_get_time();

		if (last_report > 0.0) {
			iperf_time_t current_time = 0;

			if (option->mThreadMode == kMode_Server) {
				inet_ntop(AF_INET, &option->server_info.clientaddr.s2_data2, peer_addr, INET_ADDRSTRLEN);

				if (option->mUDP && option->server_info.last_id < 0) {
					break;
				}

				byte = option->server_info.recv_byte - last_byte_count_reported;
				last_byte_count_reported = option->server_info.recv_byte;

			} else if (option->mThreadMode == kMode_Client) {
				inet_ntop(AF_INET, (struct sockaddr_in *)&option->addr, peer_addr, INET_ADDRSTRLEN);

				if (option->mUDP) {
					byte = (option->client_info.datagram_cnt * option->mBufLen) - last_byte_count_reported;
					last_byte_count_reported = option->client_info.datagram_cnt * option->mBufLen;
				} else {
					byte = option->client_info.send_byte - last_byte_count_reported;
					last_byte_count_reported = option->client_info.send_byte;
				}
			} else {
				break;
			}

			interval = (option->mInterval / 1000.0);
			bps = byte_to_bps(interval, byte);
			format = option->mFormat;

			iperf_format_output(byte, bps, format,
							&byte_disp, &bps_disp,
							byte_unit_str, sizeof(byte_unit_str),
							bps_unit_str, sizeof(bps_unit_str));

			// Print report
			nrc_iperf_spin_lock();
			CPA("[%15s][%c]  %4.1f - %4.1f sec	%7.2f %6s  %7.2f %6s\n",
				peer_addr, (option->mThreadMode == kMode_Server) ? 'S' : 'C',
				(last_report - option->mInterval) / 1000.0,
				last_report / 1000.0,
				byte_disp, byte_unit_str,
				bps_disp, bps_unit_str);
			nrc_iperf_spin_unlock();

			// Exit condition check for server mode
			if (option->mThreadMode == kMode_Server) {
				if (option->server_info.send_time) {
					iperf_get_time(&current_time);
					if ((current_time - option->server_info.start_time) >= option->server_info.send_time)
						break;
				}
				if (option->server_info.send_byte &&
					option->server_info.recv_byte >= option->server_info.send_byte)
					break;
			}
		}

		// Sleep adjustment to align with mInterval
		processing_end_time = system_get_time();
		processing_time = processing_end_time - processing_start_time;
		processing_sleep_duration = (option->mInterval > processing_time) ?
			(option->mInterval - processing_time) : 1;

		last_report += option->mInterval;

		if (ulTaskNotifyTake(pdTRUE, processing_sleep_duration) == pdTRUE)
			break;
	}

	xTaskNotifyGive(option->task_handle);
	vTaskDelete(NULL);
}

static iperf_opt_t* nrc_iperf_task_get(iperf_opt_t* option)
{
	struct iperf_task *cur, *next;
	iperf_opt_t* ret_opt = NULL;

	nrc_iperf_spin_lock();
	list_for_each_entry_safe(cur, next, &iperf_head, list) {
		if ((option->mThreadMode == cur->option->mThreadMode) &&
#if IPERF_SUPPORT_MULTIPLE_PORT
				(option->mPort == cur->option->mPort) &&
#endif
				(option->mUDP == cur->option->mUDP) &&
				(ip_addr_cmp(&cur->option->addr,&option->addr))) {
			ret_opt = cur->option;
			break;
		}
	}
	nrc_iperf_spin_unlock();
	return ret_opt;
}

static int check_destination_address(iperf_opt_t* option)
{
	int i=0;

	if(option->mThreadMode == kMode_Client){
#if LWIP_BRIDGE
		if(netif_is_up(&br_netif)) {
			if (ip_addr_cmp(&br_netif.ip_addr, &option->addr)) {
				return -1;
			}
		} else
#endif /* LWIP_BRIDGE */
#ifdef SUPPORT_ETHERNET_ACCESSPOINT
		if (ip4_addr_cmp(&eth_netif.ip_addr, &option->addr)) {
			return -1;
		}
#else
		for(i=0; i<MAX_IF; i++){
			if(ip_addr_cmp(&nrc_netif[i]->ip_addr,&option->addr)){
				return -1;
			}
		}
#endif /* SUPPORT_ETHERNET_ACCESSPOINT */
	}
	return 0;
}

static int iperf_start_session(iperf_opt_t* option, void *report_cb)
{
	BaseType_t task_ret;

	if(check_destination_address(option) < 0){
		CPA("%s Destination address is own address\n",	module_name());
		return -1;
	}

	if(nrc_iperf_task_get(option)){
		CPA("Failed : %s %s : %s\n", (option->mUDP == 1) ?  "UDP" : "TCP",
				(option->mThreadMode == kMode_Server) ?  "Server" : "Client",
				(ip4addr_ntoa((const ip4_addr_t*)ip_2_ip4(&option->addr))));
		return -1;
	}

	if(option->mThreadMode == kMode_Server){
		if(option->mUDP){
			task_ret = xTaskCreate(iperf_udp_server, "iperf_udp_server_task",
				CONFIG_TASK_STACKSIZE_IPERF, (void*)option, CONFIG_TASK_PRIORITY_IPERF, &option->task_handle);
		}else{
			task_ret = xTaskCreate(iperf_tcp_server, "iperf_tcp_server_task",
				CONFIG_TASK_STACKSIZE_IPERF, (void*)option, CONFIG_TASK_PRIORITY_IPERF, &option->task_handle);
		}
	}else{
		if(option->mUDP){
			task_ret = xTaskCreate(iperf_udp_client, "iperf_udp_client_task",
				CONFIG_TASK_STACKSIZE_IPERF, (void*)option, CONFIG_TASK_PRIORITY_IPERF, &option->task_handle);
		}else{
			task_ret = xTaskCreate(iperf_tcp_client, "iperf_tcp_client_task",
				CONFIG_TASK_STACKSIZE_IPERF, (void*)option, CONFIG_TASK_PRIORITY_IPERF, &option->task_handle);
		}
	}

	nrc_iperf_spin_lock();
	CPA("%s %s %s : %s", __func__,(option->mUDP) ? "udp":"tcp",
		(option->mThreadMode == kMode_Server)?"server":"client" ,
		(task_ret == pdFAIL) ? "Failed!\n" : "Started!\n" );
	nrc_iperf_spin_unlock();

	return (task_ret == pdFAIL) ? -1: 0;
}

static int iperf_stop_session(iperf_opt_t* option)
{
	iperf_opt_t* del_task = NULL;
	del_task = nrc_iperf_task_get(option);
	if(del_task){
		del_task->mForceStop = true;
	}
	return true;
}

static double parse_with_suffix(const char *arg, char opt)
{
	double value = 0.0;
	int len = strlen(arg);
	char suffix = '\0';
	char buf[32];

	if (len == 1 && (arg[0] == 'k' || arg[0] == 'K' || arg[0] == 'm' || arg[0] == 'M')) {
		value = (opt == 'b') ? MAX_IPERF_THROUGHPUT : 1.0;
		suffix = arg[0];
	} else if (len > 1 && (arg[len - 1] == 'k' || arg[len - 1] == 'K' || arg[len - 1] == 'm' || arg[len - 1] == 'M')) {
		suffix = arg[len - 1];
		strncpy(buf, arg, len - 1);
		buf[len - 1] = '\0';
		value = atof(buf);
	} else {
		value = atof(arg);
	}

	switch (suffix) {
		case 'k': case 'K': return value * 1000.0;
		case 'm': case 'M': return value * 1000000.0;
		default: return value;
	}
}

static int iperf_option_parse(int argc, char *argv[], iperf_opt_t *option)
{
	int i;
	char *str = NULL;

	for (i = 1; i < argc; i++) {
		str = argv[i];

		if (str == NULL) continue;

		// Handle special keyword commands (not options)
		if (strcmp(str, "stop") == 0) {
			option->mForceStop = true;
			return 0;
		}
		else if (strcmp(str, "-st") == 0) {
			nrc_iperf_list_print(); // Print current iperf session list
			return -2;
		}
		else if (strcmp(str, "-h") == 0 || strcmp(str, "-help") == 0) {
			iperf_option_help(argv[0]); // Show help
			return -2;
		}

		// Skip if not an option
		if (str[0] != '-') continue;
		int len = strlen(str);
		if (len < 2) continue;

		// Handle grouped short options like -suB
		for (int j = 1; j < len; ++j) {
			char opt = str[j];
			char *arg = NULL;
			bool has_arg = false;

			// Options without arguments
			switch (opt) {
				case 's':
					option->mThreadMode = kMode_Server;
					break;
				case 'u':
					option->mUDP = true;
					break;
				case 'N':
					option->mNodelay = true;
					break;
				// Options that require arguments
				case 'c': case 'B': case 't': case 'i':
				case 'b': case 'p': case 'S': case 'l':
				case 'g': case 'f':
					has_arg = true;
					break;
				default:
					CPA("%s unknown short option: -%c\n", module_name(), opt);
					return -1;
			}

			// If the option requires an argument
			if (has_arg) {
				// It must be the last in a group like -suB
				if (j != len - 1) {
					CPA("%s option -%c must be the last in the group\n", module_name(), opt);
					return -1;
				}
				// Ensure there's a following argument
				if (i + 1 >= argc) {
					CPA("%s missing argument for option -%c\n", module_name(), opt);
					return -1;
				}
				arg = argv[++i];

				switch (opt) {
					case 'c':
						if (!ipaddr_aton(arg, &option->addr)) {
							E(TT_NET, "Invalid client IP address\n");
							return -2;
						}
						option->mThreadMode = kMode_Client;
						break;
					case 'B':
						if (!ipaddr_aton(arg, &option->bindAddr)) {
							E(TT_NET, "Invalid bind address\n");
							return -2;
						}
						break;
					case 't':
						option->mAmount = atoi(arg) * 100;
						break;
					case 'i':
						option->mInterval = atoi(arg) * 1000;
						break;
					case 'b':
						option->mAppRate = parse_with_suffix(arg, opt);
						break;
					case 'l':
						option->mBufLen = parse_with_suffix(arg, opt);
						break;
					case 'p':
						option->mPort = atoi(arg);
						break;
					case 'S':
						option->mTOS = parse_qos(arg);
						break;
					case 'g':
						option->mSendInterval = atoi(arg);
						break;
					case 'f':
						option->mFormat = arg[0];
						break;
				}
			}
		}
	}

	return 0;
}

static void iperf_init_parameters(iperf_opt_t *option)
{
	option->mSock           = -1;
	option->mBufLen         = IPERF_DEFAULT_DATA_BUF_LEN; // -l, buffer length
	option->mPort           = 5001;                       // -p, default port
	option->mThreadMode     = kMode_Unknown;              // -s or -c, not set
	option->mAmount         = IPERF_DEFAULT_SEND_TIME * 100; // -t, duration in 0.01s
	option->mTOS            = 0;                          // -S, no TOS by default
	option->mAppRate        = 1000 * 1000;                // -b, 1 Mbps
	option->mSendInterval   = 0;                          // -g, send delay
	option->mNodelay        = false;                      // -N, nodelay off
	option->mUDP            = false;                      // -u, default TCP
	option->mForceStop      = false;                      // 'stop' not triggered
	option->mFormat         = 'a';                        // -f, format to report
	option->task_handle     = NULL;                       // task not assigned

	memset(&option->addr, 0, sizeof(ip_addr_t));          // -c, target IP
	memset(&option->bindAddr, 0, sizeof(ip_addr_t));      // -B, bind IP
}

int iperf_stop(iperf_opt_t* option)
{
	int i;
	if(option->mThreadMode == kMode_Server){
#ifdef SUPPORT_ETHERNET_ACCESSPOINT
#if LWIP_BRIDGE
		if(netif_is_up(&br_netif)){
			if(!ip4_addr_isany_val(*netif_ip4_addr(&br_netif))){
				ip_addr_copy(option->addr, br_netif.ip_addr);
				iperf_stop_session(option);
			}
		} else
#endif /* LWIP_BRIDGE */
		if(!ip4_addr_isany_val(eth_netif.ip_addr)){
				ip4_addr_copy(option->addr, eth_netif.ip_addr);
				iperf_stop_session(option);
		}
#else
		for(i=0; i<MAX_IF; i++){
			if(!ip4_addr_isany_val(*netif_ip4_addr(nrc_netif[i]))) {
				ip_addr_copy(option->addr, nrc_netif[i]->ip_addr);
				iperf_stop_session(option);
			}
		}
#endif /* SUPPORT_ETHERNET_ACCESSPOINT */
	}else{
		iperf_stop_session(option);
	}
	return 0;
}

int  iperf_run(int argc, char *argv[], void *report_cb)
{
	iperf_opt_t* option = NULL;
	int server_started = false;
	int ret = true;
	int i;

	if (!iperf_lock.handle && !iperf_head.next && !iperf_head.prev)
		nrc_iperf_list_init();

	// Make thread info structure & set default value
	option = iperf_option_alloc();
	if(option == NULL){
		CPA("iperf parameter init fail!!\n");
		return false;
	}
	iperf_init_parameters(option);

	ret = iperf_option_parse(argc, argv, option);
	if(ret <0){
		iperf_option_free(option);
		if(ret == -2) // '-st', '-h'
			return true;
		else
			return false;
	}

	if(option->mForceStop == true){
		iperf_stop(option);
		iperf_option_free(option);
		return true;
	}

	if(option->mThreadMode == kMode_Client){
		ret = iperf_start_session(option, report_cb);
		if(ret <0){
			iperf_option_free(option);
			return false;
		}
	}else {
		struct netif *target_if;
		for(i=0; i<END_INTERFACE; i++){
			target_if = nrc_netif_get_by_idx(i);
			if (!ip4_addr_isany_val(*netif_ip4_addr(target_if))) {
				if(server_started == true){
					iperf_opt_t* option2 =  iperf_option_alloc();
					memcpy(option2, option, sizeof(iperf_opt_t));
					option = option2;
				}
				ip_addr_copy(option->addr, target_if->ip_addr);
				ret = iperf_start_session(option, report_cb);
				if(ret < 0){
					if(server_started == true){
						iperf_option_free(option);
						return false;
					}
				}else {
					server_started = true;
				}
			}
		}
	}
	return true;
}

int iperf_send(int fd, const char *buf, int count,
	const struct sockaddr *to, socklen_t tolen)
{
	int r;
	int nleft = count;
	int flags = 0;
	int err_retry = 0;

	while (nleft > 0) {
		r = sendto(fd, buf, nleft, flags, to, tolen);
		if(r < 0){
			if (r == ERR_TIMEOUT || r == ERR_WOULDBLOCK) {
				if(err_retry++ < 3) {
					sys_arch_msleep(100);
				} else {
					return -1;
				}
			}
		} else {
			err_retry = 0;
			nleft -= r;
			buf += r;
		}
	}
	return count;
}

void iperf_report_log_append(char *buf, size_t *offset, size_t max_len, const char *fmt, ...)
{
	if (!buf || !offset || *offset >= max_len)
		return;

	va_list args;
	char tmp[256];
	int len;

	va_start(args, fmt);
	len = vsnprintf(tmp, sizeof(tmp), fmt, args);
	va_end(args);

	if (len > 0) {
		size_t space_left = max_len - *offset - 1;
		if ((size_t)len > space_left)
			len = space_left;

		memcpy(&buf[*offset], tmp, len);
		*offset += len;

		if (*offset >= max_len)
			*offset = max_len - 1;

		buf[*offset] = '\0';
	}
}

void iperf_reset_report_log(char *buf, size_t *offset)
{
	if (!buf || !offset)
		return;

	*offset = 0;
	buf[0] = '\0';
}

#endif /* LWIP_IPERF */
#endif /*!defined(DISABLE_IPERF_APP) */
