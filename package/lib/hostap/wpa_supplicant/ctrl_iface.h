/*
 * WPA Supplicant / UNIX domain socket -based control interface
 * Copyright (c) 2004-2020, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#ifndef CTRL_IFACE_H
#define CTRL_IFACE_H

#ifdef CONFIG_CTRL_IFACE

#ifndef CTRL_IFACE_MAX_LEN
#define CTRL_IFACE_MAX_LEN 8192
#endif /* CTRL_IFACE_MAX_LEN */

/* Shared functions from ctrl_iface.c; to be called by ctrl_iface backends */

/**
 * wpa_supplicant_ctrl_iface_process - Process ctrl_iface command
 * @wpa_s: Pointer to wpa_supplicant data
 * @buf: Received command buffer (nul terminated string)
 * @resp_len: Variable to be set to the response length
 * Returns: Response (*resp_len bytes) or %NULL on failure
 *
 * Control interface backends call this function when receiving a message that
 * they do not process internally, i.e., anything else than ATTACH, DETACH,
 * and LEVEL. The return response value is then sent to the external program
 * that sent the command. Caller is responsible for freeing the buffer after
 * this. If %NULL is returned, *resp_len can be set to two special values:
 * 1 = send "FAIL\n" response, 2 = send "OK\n" response. If *resp_len has any
 * other value, no response is sent.
 */
char * wpa_supplicant_ctrl_iface_process(struct wpa_supplicant *wpa_s,
					 char *buf, size_t *resp_len);

/**
 * wpa_supplicant_global_ctrl_iface_process - Process global ctrl_iface command
 * @global: Pointer to global data from wpa_supplicant_init()
 * @buf: Received command buffer (nul terminated string)
 * @resp_len: Variable to be set to the response length
 * Returns: Response (*resp_len bytes) or %NULL on failure
 *
 * Control interface backends call this function when receiving a message from
 * the global ctrl_iface connection. The return response value is then sent to
 * the external program that sent the command. Caller is responsible for
 * freeing the buffer after this. If %NULL is returned, *resp_len can be set to
 * two special values: 1 = send "FAIL\n" response, 2 = send "OK\n" response. If
 * *resp_len has any other value, no response is sent.
 */
char * wpa_supplicant_global_ctrl_iface_process(struct wpa_global *global,
						char *buf, size_t *resp_len);


/* Functions that each ctrl_iface backend must implement */

/**
 * wpa_supplicant_ctrl_iface_init - Initialize control interface
 * @wpa_s: Pointer to wpa_supplicant data
 * Returns: Pointer to private data on success, %NULL on failure
 *
 * Initialize the control interface and start receiving commands from external
 * programs.
 *
 * Required to be implemented in each control interface backend.
 */
struct ctrl_iface_priv *
wpa_supplicant_ctrl_iface_init(struct wpa_supplicant *wpa_s);

/**
 * wpa_supplicant_ctrl_iface_deinit - Deinitialize control interface
 * @wpa_s: Pointer to wpa_supplicant data
 * @priv: Pointer to private data from wpa_supplicant_ctrl_iface_init()
 *
 * Deinitialize the control interface that was initialized with
 * wpa_supplicant_ctrl_iface_init() and any data related to the wpa_s instance.
 * @priv may be %NULL if the control interface has not yet been initialized.
 *
 * Required to be implemented in each control interface backend.
 */
void wpa_supplicant_ctrl_iface_deinit(struct wpa_supplicant *wpa_s,
				      struct ctrl_iface_priv *priv);

/**
 * wpa_supplicant_ctrl_iface_wait - Wait for ctrl_iface monitor
 * @priv: Pointer to private data from wpa_supplicant_ctrl_iface_init()
 *
 * Wait until the first message from an external program using the control
 * interface is received. This function can be used to delay normal startup
 * processing to allow control interface programs to attach with
 * %wpa_supplicant before normal operations are started.
 *
 * Required to be implemented in each control interface backend.
 */
void wpa_supplicant_ctrl_iface_wait(struct ctrl_iface_priv *priv);

/**
 * wpa_supplicant_global_ctrl_iface_init - Initialize global control interface
 * @global: Pointer to global data from wpa_supplicant_init()
 * Returns: Pointer to private data on success, %NULL on failure
 *
 * Initialize the global control interface and start receiving commands from
 * external programs.
 *
 * Required to be implemented in each control interface backend.
 */
struct ctrl_iface_global_priv *
wpa_supplicant_global_ctrl_iface_init(struct wpa_global *global);

/**
 * wpa_supplicant_global_ctrl_iface_deinit - Deinitialize global ctrl interface
 * @priv: Pointer to private data from wpa_supplicant_global_ctrl_iface_init()
 *
 * Deinitialize the global control interface that was initialized with
 * wpa_supplicant_global_ctrl_iface_init().
 *
 * Required to be implemented in each control interface backend.
 */
void wpa_supplicant_global_ctrl_iface_deinit(
	struct ctrl_iface_global_priv *priv);

void wpas_ctrl_radio_work_flush(struct wpa_supplicant *wpa_s);

#else /* CONFIG_CTRL_IFACE */

static inline struct ctrl_iface_priv *
wpa_supplicant_ctrl_iface_init(struct wpa_supplicant *wpa_s)
{
	return (void *) -1;
}

static inline void
wpa_supplicant_ctrl_iface_deinit(struct wpa_supplicant *wpa_s,
				 struct ctrl_iface_priv *priv)
{
}

static inline void
wpa_supplicant_ctrl_iface_send(struct ctrl_iface_priv *priv, int level,
			       char *buf, size_t len)
{
}

static inline void
wpa_supplicant_ctrl_iface_wait(struct ctrl_iface_priv *priv)
{
}

static inline struct ctrl_iface_global_priv *
wpa_supplicant_global_ctrl_iface_init(struct wpa_global *global)
{
	return (void *) 1;
}

static inline void
wpa_supplicant_global_ctrl_iface_deinit(struct ctrl_iface_global_priv *priv)
{
}

static inline void wpas_ctrl_radio_work_flush(struct wpa_supplicant *wpa_s)
{
}

#endif /* CONFIG_CTRL_IFACE */

#ifdef CONFIG_TESTING_OPTIONS
#ifndef _FREERTOS
#else
struct ip {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    unsigned int ip_hl:4;
    unsigned int ip_v:4;
#else
    unsigned int ip_v:4;
    unsigned int ip_hl:4;
#endif
    uint8_t ip_tos;
    uint16_t ip_len;
    uint16_t ip_id;
    uint16_t ip_off;
    uint8_t ip_ttl;
    uint8_t ip_p;
    uint16_t ip_sum;
    uint32_t ip_src;
    uint32_t ip_dst;
};

struct ether_header {
    uint8_t  ether_dhost[6];  // Destination MAC
    uint8_t  ether_shost[6];  // Source MAC
    uint16_t ether_type;      // Protocol type
};
#define	ETHERTYPE_IP		0x0800		/* IP */
#endif
#endif /* CONFIG_TESTING_OPTIONS */
#endif /* CTRL_IFACE_H */
