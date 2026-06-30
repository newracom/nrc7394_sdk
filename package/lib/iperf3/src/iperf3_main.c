/*
 * iperf, Copyright (c) 2014, The Regents of the University of
 * California, through Lawrence Berkeley National Laboratory (subject
 * to receipt of any required approvals from the U.S. Dept. of
 * Energy).  All rights reserved.
 *
 * If you have questions about your rights to use or distribute this
 * software, please contact Berkeley Lab's Technology Transfer
 * Department at TTD@lbl.gov.
 *
 * NOTICE.  This software is owned by the U.S. Department of Energy.
 * As such, the U.S. Government has been granted for itself and others
 * acting on its behalf a paid-up, nonexclusive, irrevocable,
 * worldwide license in the Software to reproduce, prepare derivative
 * works, and perform publicly and display publicly.  Beginning five
 * (5) years after the date permission to assert copyright is obtained
 * from the U.S. Department of Energy, and subject to any subsequent
 * five (5) year renewals, the U.S. Government is granted for itself
 * and others acting on its behalf a paid-up, nonexclusive,
 * irrevocable, worldwide license in the Software to reproduce,
 * prepare derivative works, distribute copies to the public, perform
 * publicly and display publicly, and to permit others to do so.
 *
 * This code is distributed under a BSD style license, see the LICENSE
 * file for complete information.
 */

#include "iperf3_port.h"
#include "iperf3.h"
#include "iperf3_api.h"
#include "units.h"
#include "iperf3_locale.h"
#include "iperf3_list.h"
#include "iperf3_net.h"

#define CONFIG_TASK_STACKSIZE_IPERF3 2048
#define CONFIG_TASK_PRIORITY_IPERF3 LWIP_IPERF_TASK_PRIORITY

#define iperf3_printf(fmt, ...)		fprintf(stderr, fmt, ##__VA_ARGS__)
#define iperf3_log(fmt, ...)		iperf3_printf("iperf3: " fmt, ##__VA_ARGS__)

/**************************************************************************/

static int iperf3_run (struct iperf3_test *test)
{
    int consecutive_errors;

    switch (test->role) {
        case 's':
			if (test->daemon) {
				int rc = 0;//daemon(0, 0);
				if (rc < 0) {
					i_errno = IEDAEMON;
					iperf3_errexit(test, "error - %s", iperf3_strerror(i_errno));
				}
			}
			consecutive_errors = 0;
			for (;;) {
				if (iperf3_run_server(test) < 0) {
					iperf3_err(test, "error - %s", iperf3_strerror(i_errno));
					fprintf(stderr, "\n");
					++consecutive_errors;
					if (consecutive_errors >= 5) {
						fprintf(stderr, "too many errors, exiting\n");
						break;
					}
				} else
					consecutive_errors = 0;
				iperf3_reset_test(test);
				if (iperf3_get_test_one_off(test))
					break;
			}
			break;
        case 'c':
            if (iperf3_run_client(test) < 0)
				iperf3_errexit(test, "error - %s", iperf3_strerror(i_errno));
            break;
        default:
            usage();
            break;
    }

    return 0;
}

/**************************************************************************/

#define iperf3_thread_debug(fmt, ...)	//rtos_debug(fmt "\n", ##__VA_ARGS__)

typedef struct
{
	struct list_head list;
	struct iperf3_test *test;
	TaskHandle_t handle;
	int id;
} iperf3_thread_t;

typedef struct
{
	struct list_head head;
	SemaphoreHandle_t lock;
	int count;
} iperf3_thread_list_t;

static iperf3_thread_list_t *g_iperf3_thread_list = NULL;

static int iperf3_thread_list_add (iperf3_thread_t *thread)
{
	iperf3_thread_list_t *thread_list = g_iperf3_thread_list;

	if (thread_list && thread)
	{
		if (xSemaphoreTake(thread_list->lock, portMAX_DELAY) == pdTRUE) {
			thread->id = thread_list->count++;
			list_add_tail(&thread->list, &thread_list->head);
			xSemaphoreGive(thread_list->lock);
		}

		return 0;
	}

	return -1;
}

static int iperf3_thread_list_del (iperf3_thread_t *thread)
{
	iperf3_thread_list_t *thread_list = g_iperf3_thread_list;

	if (thread_list && thread)
	{
		struct list_head *list_head = &thread_list->head;
		struct list_head *list = &thread->list;
		struct list_head *list_next = list->next;

		if (xSemaphoreTake(thread_list->lock, portMAX_DELAY) == pdTRUE) {
			list_del(list);
			free(thread);

			thread_list->count--;
			for (list = list_next ; list != list_head ; list = list->next)
			{
				thread = (iperf3_thread_t *)list;
				thread->id--;
			}

			xSemaphoreGive(thread_list->lock);
		}
		return 0;
	}

	return -1;
}

static int iperf3_thread_list_print (void)
{
	iperf3_thread_list_t *thread_list = g_iperf3_thread_list;

	if (thread_list)
	{
		struct list_head *list_head = &thread_list->head;
		struct list_head *list;
		struct iperf3_test *test;
		iperf3_thread_t *thread;

		if (xSemaphoreTake(thread_list->lock, portMAX_DELAY) == pdTRUE) {
			printf("-------------------------- iperf3 thread list ----------------------------\n");
			printf(" ID  Protocol  Role\n");

			for (list = list_head->next ; list != list_head ; list = list->next)
			{
				thread = (iperf3_thread_t *)list;
				if (!thread)
					break;

				test = thread->test;

				printf(" %-2d  %-8s  %-6s\n",
					   thread->id,
					   test->protocol->name,
					   (test->role == 'c') ? "CLIENT" : ((test->role == 's') ? "SERVER" : "NONE") );
			}

			printf("--------------------------------------------------------------------------\n");
			xSemaphoreGive(thread_list->lock);
		}

		return 0;
	}

	return -1;
}

static void iperf3_thread (void *pvParameters)
{
	iperf3_thread_t *thread = (iperf3_thread_t *)pvParameters;
    struct iperf3_test *test = thread->test;

	iperf3_thread_debug("run, handle=%p test=%p", thread->handle, thread->test);

    if (iperf3_run(test) < 0)
        iperf3_err(test, "error - %s", iperf3_strerror(i_errno));

	iperf3_thread_debug("done");

	iperf3_free_test(test);
	iperf3_thread_list_del(thread);

	vTaskDelete(NULL);
}

static int iperf3_thread_run (struct iperf3_test *test)
{
	iperf3_thread_t *thread;

	iperf3_thread_debug();

	if (!test)
	{
		iperf3_err(NULL, "test is null");
		goto iperf3_start_error;
	}

	thread = malloc(sizeof(iperf3_thread_t));
	if (!thread)
	{
		iperf3_err(NULL, "malloc() failed");
		goto iperf3_start_error;
	}

	INIT_LIST_HEAD(&thread->list);
	thread->test = test;
	thread->handle = NULL;

	if (xTaskCreate(iperf3_thread, "iperf3", CONFIG_TASK_STACKSIZE_IPERF3,
			thread, CONFIG_TASK_PRIORITY_IPERF3, &thread->handle) == pdPASS)
	{
		iperf3_thread_debug("success, handle=%p test=%p", thread->handle, thread->test);

		iperf3_thread_list_add(thread);
		return 0;
	}

	free(thread);

	iperf3_thread_debug("fail");

iperf3_start_error:

	iperf3_free_test(test);

	return -1;
}

static int iperf3_thread_exit (int id)
{
	iperf3_thread_list_t *thread_list = g_iperf3_thread_list;

	if (thread_list && thread_list->count > 0)
	{
		if (id >= 0 && id < thread_list->count)
		{
			struct list_head *list_head = &thread_list->head;
			struct list_head *list = list_head;
			iperf3_thread_t *thread;
			int i;

			iperf3_thread_debug("id=%d\n", id);

			for (i = 0 ; i <= id ; i++)
				list = list->next;

			thread = (iperf3_thread_t *)list;

			if (id != thread->id)
			{
				thread->test->one_off = 1;
				thread->test->state = IPERF3_DONE;
				return 0;
			}
		}

		iperf3_err(NULL, "invalid id: %d", id);
	}

	iperf3_err(NULL, "no operation");

	return -1;
}

static int iperf3_init (void)
{
	if (!g_iperf3_thread_list)
	{
		iperf3_thread_list_t *thread_list = malloc(sizeof(iperf3_thread_list_t));

		if (!thread_list)
		{
			iperf3_err(NULL, "malloc() failed");
			return -1;
		}

		INIT_LIST_HEAD(&thread_list->head);
		thread_list->lock = xSemaphoreCreateMutex();
		thread_list->count = 0;

		g_iperf3_thread_list = thread_list;
	}

	return 0;
}

/**************************************************************************/
int iperf3_main (int argc, char **argv)
{
	int ret = -1;

	if (iperf3_init() == 0)
	{
    	struct iperf3_test *test = iperf3_new_test();

		if (!test)
		{
			iperf3_err(NULL, "create new test error - %s", iperf3_strerror(i_errno));
			return -1;
		}

		iperf3_defaults(test); /* sets defaults */

		ret = iperf3_parse_arguments(test, argc, argv);
		switch (ret)
		{
			case 0:
				return iperf3_thread_run(test);

			case 1:
				ret = 0;
#if defined(CONFIG_SUPPORT_RTOS)
				if (test->print_thread_list == 1)
					ret = iperf3_thread_list_print();
				else if (test->exit_thread_id >= 0)
					ret = iperf3_thread_exit(test->exit_thread_id);
#endif
				usage_long();
				break;

			default:
				iperf3_err(test, "parameter error - %s", iperf3_strerror(i_errno));
		}

		iperf3_free_test(test);
	}

	return ret;
}

int iperf3_execute(int argc, char *argv[], void *report_cb)
{
	return iperf3_main(argc, argv) == 0;
}
