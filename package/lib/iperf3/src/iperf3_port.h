// iperf3_port.h

#ifndef IPERF3_PORT_H
#define IPERF3_PORT_H

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "lwip/sockets.h"
#include "lwip/netdb.h"
#include <stdint.h>

#include "util_trace.h"

#define calloc		pvPortCalloc
#define malloc		pvPortMalloc
#define realloc		pvPortRealloc
#define free		vPortFree

/* Replace Linux gettimeofday() */
int iperf3_gettimeofday(struct timeval *tv);

/* A raw port‐level printf that goes to your HAL console */
#define port_printf(...)    system_printf(__VA_ARGS__)

/* A tiny prefix for port logs */
#define port_log(...)       port_printf("iperf3: " __VA_ARGS__)

/* Mutex type */
typedef SemaphoreHandle_t iperf3_mutex_t;
static inline void iperf3_mutex_init(iperf3_mutex_t *m)   { *m = xSemaphoreCreateMutex(); }
static inline void iperf3_mutex_lock(iperf3_mutex_t *m)   { xSemaphoreTake(*m, portMAX_DELAY); }
static inline void iperf3_mutex_unlock(iperf3_mutex_t *m) { xSemaphoreGive(*m); }

/* Memory */
#define iperf3_malloc   pvPortMalloc
#define iperf3_free     vPortFree

/* Sleep */
static inline void iperf3_sleep_ms(uint32_t ms) { vTaskDelay(pdMS_TO_TICKS(ms)); }

#endif /* IPERF3_PORT_H */
