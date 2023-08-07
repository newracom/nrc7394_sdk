#ifndef __ROMLIB_H__
#define __ROMLIB_H__

#include "system.h"
#include "system_freertos.h"
#include "hal_host_interface.h"
#include "umac_wim_manager.h"

#define QUE_MAX (2)

struct cspi_priv {
	struct sysbuf_queue hwque[QUE_MAX];
	uint32_t report[QUE_MAX];
	struct sysbuf_queue *to_host_que;
	uint32_t rx_count;
	uint32_t rx_report;
	SYS_BUF *rxf;
	int n_rxf;
} __packed;

struct rlif_cspi_t {
    /* Host Interface */
    bool include_no_delay_uplink;
    bool tx_enable;
    bool loopback_enable;
    struct host_interface_ops hops;

    /* cspi hif device  */
    uint32_t rxque_max;
    uint32_t txque_max;
    uint32_t rx_stream_max;
    bool cspi_loopback_enable;
    bool cspi_loopback_verify;
    struct cspi_priv priv;
};

struct chain_global {
    int create_count;
    struct dl_list chains;
	SemaphoreHandle_t chains_lock;
};

struct chain {
	struct dl_list entry;
	struct dl_list items;
	SemaphoreHandle_t items_lock;
    int id;
};

struct rlif_t {
    /* System */
	unsigned long (*irq_save)(void);
	void (*irq_restore)(unsigned long irq);

    /* freeRTOS */
    bool (*system_schedule_work_queue_from_isr)(sys_task_func func , void* param , sys_task_func_cb cb);
    void *(*pvPortMalloc)(size_t xWantedSize);
    void (*vPortFree)( void *pv );
    SemaphoreHandle_t (*SemaphoreCreateMutex)( void );
    BaseType_t (*SemaphoreTake)( SemaphoreHandle_t xSemaphore, TickType_t xTicksToWait );
    BaseType_t (*SemaphoreGive)( SemaphoreHandle_t xSemaphore );
    void (*SemaphoreDelete)( SemaphoreHandle_t xSemaphore );

    /* Chain */
    struct chain_global *c_global;

    /* System Memory Manager */
    SYS_BUF* (*sm_pool_alloc)(uint8_t pool_id);
    void (*sm_pool_free)(struct _SYS_BUF* buf);
    int (*sm_pool_number_of_link)(struct _SYS_BUF* buf);
    
    /* Helper for Memory Manager */
	SYS_BUF *(*sys_buf_alloc)(uint8_t pool_id , uint16_t hif_len );    
    void (*sys_buf_len_calc_using_hif_len)(SYS_BUF* packet);

    /* Lmac */
    void (*discard)(struct _SYS_BUF* buffer);
    void (*lmac_uplink_request_sysbuf)(struct _SYS_BUF* buf);

    /* Umac */
    void (*umac_wim_manager_run)(int vif_id, uint16_t cmd, struct nrc_tlv **map);

    /* serial flash */
    sf_ops s_sf_op;
    sf_info_t sfi;
    bool cache_xip;

    /* Host Interface */
    void (*host_interface_rx_done)(SYS_BUF *packet);
    int32_t (*wq_packet_process)(void *param);
    struct rlif_cspi_t cspi;
};

void romlib_init();
struct rlif_t* romlib_get_rlifobj();
struct cspi_priv* romlib_get_rlif_cspi_priv_obj();
struct host_interface_ops* romlib_get_rlif_hif_obj();
void romlib_set_cspi_loopback_enable(bool enable);
bool romlib_get_cspi_loopback_enable();
void romlib_set_hif_tx_enable(bool enable);
bool romlib_get_hif_tx_enable();
void romlib_set_hif_loopback_enable(bool enable);
bool romlib_get_hif_loopback_enable();
struct chain_global *romlib_get_c_global();
#endif