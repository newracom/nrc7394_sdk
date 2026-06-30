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
#include "iperf3_util.h"
#include "iperf3_locale.h"
#include "iperf3_net.h"
#include "iperf3_timer.h"
#include "timers.h"

int iperf3_create_streams(struct iperf3_test *test)
{
    int i, s;
    struct iperf3_stream *sp = NULL;

    for (i = 0; i < test->num_streams; ++i) {
        if ((s = test->protocol->_connect(test)) < 0)
            return -1;

		if (test->sender)
			FD_SET(s, &test->write_set);
		else
			FD_SET(s, &test->read_set);
		if (s > test->max_fd)
			test->max_fd = s;

        sp = iperf3_new_stream(test, s);
        if (!sp)
            return -1;

        /* Perform the new stream callback */
        if (test->on_new_stream)
            test->on_new_stream(sp);
    }
    return 0;
}

static void test_timer_proc(TimerClientData client_data, struct timeval *nowP)
{
    struct iperf3_test *test = client_data.p;

    test->timer = NULL;
    test->done = 1;
}

static void client_stats_timer_proc(TimerClientData client_data, struct timeval *nowP)
{
    struct iperf3_test *test = client_data.p;

    if (!test->done && test->stats_callback)
		test->stats_callback(test);
}

static void client_reporter_timer_proc(TimerClientData client_data, struct timeval *nowP)
{
    struct iperf3_test *test = client_data.p;

    if (!test->done && test->reporter_callback)
		test->reporter_callback(test);
}

static int create_client_timers(struct iperf3_test * test)
{
    struct timeval now;
    TimerClientData cd = { .p = test};

	iperf3_gettimeofday(&now);
    test->timer = test->stats_timer = test->reporter_timer = NULL;

    if (test->duration > 0) {
		test->done = 0;
        test->timer = tmr_create(&now, test_timer_proc, cd, ( test->duration + test->omit ) * SEC_TO_US, 0);
        if (test->timer == NULL) {
            i_errno = IEINITTEST;
            return -1;
	}
    }
    if (test->stats_interval != 0) {
        test->stats_timer = tmr_create(&now, client_stats_timer_proc, cd, test->stats_interval * SEC_TO_US, 1);
        if (test->stats_timer == NULL) {
            i_errno = IEINITTEST;
            return -1;
	}
    }
    if (test->reporter_interval != 0) {
        test->reporter_timer = tmr_create(&now, client_reporter_timer_proc, cd, test->reporter_interval * SEC_TO_US, 1);
        if (test->reporter_timer == NULL) {
            i_errno = IEINITTEST;
            return -1;
	}
    }
    return 0;
}

static void client_omit_timer_proc(TimerClientData client_data, struct timeval *nowP)
{
    struct iperf3_test *test = client_data.p;

    test->omit_timer = NULL;
    test->omitting = 0;
    iperf3_reset_stats(test);
    if (test->verbose && !test->json_output && test->reporter_interval == 0)
        iperf3_printf(test, "%s", report_omit_done);

    /* Reset the timers. */
    if (test->stats_timer != NULL)
        tmr_reset(nowP, test->stats_timer);
    if (test->reporter_timer != NULL)
        tmr_reset(nowP, test->reporter_timer);
}

static int create_client_omit_timer(struct iperf3_test * test)
{
    struct timeval now;
    TimerClientData cd = { .p = test };;

    if (test->omit <= 0) {
		test->omit_timer = NULL;
        test->omitting = 0;
		return 0;
	}
	iperf3_gettimeofday(&now);
	test->omitting = 1;
	test->omit_timer = tmr_create(&now, client_omit_timer_proc, cd, test->omit * SEC_TO_US, 0);
	if (test->omit_timer == NULL) {
	    i_errno = IEINITTEST;
	    return -1;
	}
    return 0;
}

int iperf3_handle_message_client(struct iperf3_test *test)
{
	signed char state;
    int32_t err;

    if (Nread(test->ctrl_sck, (char*) &state, sizeof(state), Ptcp) <= 0) {
		i_errno = (state = 0) ? IECTRLCLOSE : IERECVMESSAGE;
		return -1;
    }

	test->state = state;
    switch (test->state) {
        case PARAM_EXCHANGE:
            if (iperf3_exchange_parameters(test) < 0) {
				return -1;
			}
            if (test->on_connect)
                test->on_connect(test);
            break;
        case CREATE_STREAMS:
            if (iperf3_create_streams(test) < 0) {
				return -1;
			}
            break;
        case TEST_START:
            if (iperf3_init_test(test) < 0) {
				return -1;
			}
            if (create_client_timers(test) < 0) {
				return -1;
			}
            if (create_client_omit_timer(test) < 0) {
				return -1;
			}
			if (!test->reverse && iperf3_create_send_timers(test) < 0) {
				return -1;
			}
            break;
        case TEST_RUNNING:
            break;
        case EXCHANGE_RESULTS:
            if (iperf3_exchange_results(test) < 0) {
				return -1;
			}
            break;
        case DISPLAY_RESULTS:
            if (test->on_test_finish)
                test->on_test_finish(test);
            iperf3_client_end(test);
            break;
        case IPERF3_DONE:
            break;
        case SERVER_TERMINATE:
            i_errno = IESERVERTERM;
			/*
			 * Temporarily be in DISPLAY_RESULTS phase so we can get
			 * ending summary statistics.
			 */
			signed char oldstate = test->state;
			cpu_util(test->cpu_util);
			test->state = DISPLAY_RESULTS;
			test->reporter_callback(test);
			test->state = oldstate;
            return -1;
        case ACCESS_DENIED:
            i_errno = IEACCESSDENIED;
            return -1;
        case SERVER_ERROR:
            if (Nread(test->ctrl_sck, (char*) &err, sizeof(err), Ptcp) < 0) {
                i_errno = IECTRLREAD;
                return -1;
            }
			i_errno = ntohl(err);
            if (Nread(test->ctrl_sck, (char*) &err, sizeof(err), Ptcp) < 0) {
                i_errno = IECTRLREAD;
                return -1;
            }
            errno = ntohl(err);
            return -1;
        default:
            i_errno = IEMESSAGE;
            return -1;
    }

    return 0;
}

/* iperf3_connect -- client to server connection function */
int iperf3_connect(struct iperf3_test *test)
{
    FD_ZERO(&test->read_set);
    FD_ZERO(&test->write_set);

    make_cookie(test->cookie);

    /* Create and connect the control channel */
    if (test->ctrl_sck < 0)
        test->ctrl_sck = netdial(test->settings->domain, Ptcp, test->bind_address, test->server_hostname, test->server_port);
    if (test->ctrl_sck < 0) {
        i_errno = IECONNECT;
        return -1;
    }

    if (Nwrite(test->ctrl_sck, test->cookie, COOKIE_SIZE, Ptcp) < 0) {
        i_errno = IESENDCOOKIE;
        return -1;
    }

    FD_SET(test->ctrl_sck, &test->read_set);
    if (test->ctrl_sck > test->max_fd)
		test->max_fd = test->ctrl_sck;

    return 0;
}

int iperf3_client_end(struct iperf3_test *test)
{
    struct iperf3_stream *sp;

    /* Close all stream sockets */
    SLIST_FOREACH(sp, &test->streams, streams) {
        close(sp->socket);
    }

    /* show final summary */
    test->reporter_callback(test);

    if (iperf3_set_send_state(test, IPERF3_DONE) != 0)
        return -1;

    /* Close control socket */
    if (test->ctrl_sck)
        close(test->ctrl_sck);

    return 0;
}

int iperf3_run_client(struct iperf3_test * test)
{
    int result = 0;
    int startup = 1;;
    fd_set read_set, write_set;
    struct timeval now;
    struct timeval* timeout = NULL;
    struct iperf3_stream *sp;

    if (test->affinity != -1)
		if (iperf3_setaffinity(test->affinity) != 0)
			return -1;

    if (test->json_output)
		if (iperf3_json_start(test) < 0)
			return -1;

    /* Start the client and connect to the server */
    if (iperf3_connect(test) < 0)
        return -1;

    /* Begin calculating CPU utilization */
    cpu_util(NULL);

    while (test->state != IPERF3_DONE) {
        memcpy(&read_set, &test->read_set, sizeof(fd_set));
        memcpy(&write_set, &test->write_set, sizeof(fd_set));

        iperf3_gettimeofday(&now);
        timeout = tmr_timeout(&now);
        result = select(test->max_fd + 1, &read_set, &write_set, NULL, timeout);
        if (result < 0 && errno != EINTR) {
            i_errno = IESELECT;
			goto error;
        }
		if (result == 0 && timeout) {
			iperf3_gettimeofday(&now);
			tmr_run(&now);
		}
        if (result > 0) {
            if (FD_ISSET(test->ctrl_sck, &read_set)) {
                if (iperf3_handle_message_client(test) < 0) {
					goto error;
                }
                FD_CLR(test->ctrl_sck, &read_set);
            }
			if (test->state == TEST_RUNNING) {
				/* Is this our first time really running? */
				if (startup) {
					startup = 0;
					// Set non-blocking for non-UDP tests
					if (test->protocol->id != Pudp) {
						SLIST_FOREACH(sp, &test->streams, streams) {
							setnonblocking(sp->socket, 1);
						}
					}
				}

				if (test->reverse) {
					// Reverse mode. Client receives.
					if (iperf3_recv(test, &read_set) < 0)
						goto error;
				} else {
					// Regular mode. Client sends.
					if (iperf3_send(test, &write_set) < 0)
						goto error;
				}

				/* Run the timers. */
				iperf3_gettimeofday(&now);
				tmr_run(&now);

				/* Is the test done yet? */
				if ((!test->omitting) &&
					((test->duration && test->done) ||
					 (test->settings->bytes && test->bytes_sent >= test->settings->bytes) ||
					 (test->settings->blocks && test->blocks_sent >= test->settings->blocks))) {
					SLIST_FOREACH(sp, &test->streams, streams) {
						setnonblocking(sp->socket, 0);
					}

					/* Yes, done!  Send TEST_END. */
					test->done = 1;
					cpu_util(test->cpu_util);
					test->stats_callback(test);
					if (iperf3_set_send_state(test, TEST_END) != 0)
						goto error;
				}
			}
		}
	}

    if (test->json_output) {
        if (iperf3_json_finish(test) < 0)
            return -1;
    }

	return 0;

error:
	iperf3_client_end(test);
    return -1;
}
