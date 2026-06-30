#ifndef __LINK_STATUS_PUSH_CLIENT_TASK_H__
#define __LINK_STATUS_PUSH_CLIENT_TASK_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Start Link status push client task
 *
 * - Creates a FreeRTOS task
 * - Sends link_status JSON to the configured server
 *
 * Requirements:
 * - lwIP sockets initialized
 * - Network interface is up
 */
void link_status_push_client_start(void);

#ifdef __cplusplus
}
#endif

#endif /* __LINK_STATUS_PUSH_CLIENT_TASK_H__ */
