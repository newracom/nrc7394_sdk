#ifndef __UTIL_TRACE_STACK_H__
#define __UTIL_TRACE_STACK_H__

#include "system.h"
#include "system_common.h"

int util_trace_stack_add_task( TaskHandle_t handle );
int util_trace_stack_remove_task( TaskHandle_t handle );
int util_trace_stack_display(bool dump);
void _util_trace_stack_dump(TaskHandle_t handle, const char *caller, uint32_t line);
#define util_trace_stack_dump(handle)	_util_trace_stack_dump(handle, __func__, __LINE__)

#endif    /* __UTIL_TRACE_STACK_H__ */
