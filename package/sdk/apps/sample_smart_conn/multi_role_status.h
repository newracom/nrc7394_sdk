#ifndef __MULTI_ROLE_STATUS_H__
#define __MULTI_ROLE_STATUS_H__

#include "multi_role_config.h"

void device_ready (system_role_t role);
void init_status_check(system_role_t role);

void recover_uart_rx_cnt_clear (void);
void recover_uart_tx_cnt_clear (void);

#endif //  __MULTI_ROLE_STATUS_H__
