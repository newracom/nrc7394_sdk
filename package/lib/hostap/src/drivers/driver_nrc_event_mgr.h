#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * driver_nrc_event_mgr.h
 *
 * NRC driver event manager (single dispatcher + handler list):
 *  - Receives driver/vendor events
 *  - Dispatches them into a central queue
 *  - Iterates handler list in one dispatcher task
 *  - Frees payload after all handlers are called (if destructor is provided)
 *
 * Handlers must be non-blocking in this model.
 */

#include "nrc_types.h"

/* ===== Tunables ===== */
#ifndef NRC_EVENT_MGR_MAX_VIF
#define NRC_EVENT_MGR_MAX_VIF					2
#endif

#ifndef NRC_EVENT_MGR_DISPATCH_QUEUE_LEN
#define NRC_EVENT_MGR_DISPATCH_QUEUE_LEN		512
#endif

#ifndef NRC_EVENT_MGR_PRIO_DISPATCHER
#define NRC_EVENT_MGR_PRIO_DISPATCHER			28
#endif

#ifndef NRC_EVENT_MGR_DISPATCHER_STACK
#define NRC_EVENT_MGR_DISPATCHER_STACK			2560
#endif

#ifndef NRC_EVENT_MGR_VENDOR_IE_SIZE
#define NRC_EVENT_MGR_VENDOR_IE_SIZE			252		/* CMD(1) + DATA(<=251) */
#endif

#ifndef NRC_EVENT_MGR_CMD_PREFIX_LEN
#define NRC_EVENT_MGR_CMD_PREFIX_LEN			1		/* 1 byte sub-command */
#endif

/* ===== Event model ===== */
typedef struct {
	int			vif;
	int			event_id;
	uint32_t	data_len;
	void		*data;
	uint32_t	attempt_id;
	uint64_t	ts_us;
	uint8_t		subcmd;		/* 0 if not applicable */
	uint8_t		_pad[3];	/* keep 32-bit alignment */
} nrc_event_mgr_evt_t;

/* Destructor for payload (called after all handlers) */
typedef void (*nrc_event_mgr_dtor_t)(void *ptr, uint32_t len);

/* Opaque handle */
typedef struct nrc_event_mgr_handler*	nrc_event_mgr_handle_t;

/* ===== Core API ===== */
void nrc_event_mgr_init(void);


/* Epoch helpers */
void nrc_event_mgr_start_connect_attempt(int vif);
void nrc_event_mgr_set_attempt_id(int vif, uint32_t attempt_id);
uint32_t nrc_event_mgr_get_attempt_id(int vif);

/* Registration */
nrc_event_mgr_handle_t nrc_event_mgr_register(event_callback_fn fn);
void nrc_event_mgr_unregister(nrc_event_mgr_handle_t h);

/* ===== Legacy wrappers (multi-register) ===== */
void wpa_driver_register_event_cb(event_callback_fn fn);
void wpa_driver_unregister_event_cb(event_callback_fn fn);
void wpa_driver_unregister_all_event_cb(void);

/* ===== Enqueue helpers ===== */
void wpa_driver_notify_event_to_app(int vif, int event_id, uint32_t data_len, void *data);
void wpa_driver_notify_vevent_to_app(int vif, int subcmd, uint32_t data_len, uint8_t* data, void* v);

#ifdef __cplusplus
}
#endif
