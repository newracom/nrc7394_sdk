/*
 * link_status.h
 *
 * Link status snapshot provider for OLED display and TCP JSON push server.
 *
 * - FreeRTOS safe (uses mutex internally)
 * - No UI/log side effects
 * - Provides local MAC and parent (AP BSSID) MAC when connected
 */

#ifndef __PING_ON_WIFI_CONNECT_H__
#define __PING_ON_WIFI_CONNECT_H__


#ifdef __cplusplus
extern "C" {
#endif

void ping_on_wifi_connect_init(void);
void ping_on_wifi_connect_start(void);
void ping_on_wifi_connected_notify(void);
void ping_on_wifi_disconnected_notify(void);

#endif /* __PING_ON_WIFI_CONNECT_H__ */
