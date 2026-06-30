/*
 * iperf, Copyright (c) 2014, 2015, The Regents of the University of
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
 * This code is distributed under a BSD style license, see the LICENSE file
 * for complete information.
 */

#include "iperf3_port.h"
#include "iperf3_net.h"
#include "iperf3.h"
#include "iperf3_api.h"
#include "iperf3_udp.h"
#include "iperf3_tcp.h"
#include "timers.h"
#include "cJSON.h"
#include "units.h"
#include "tcp_window_size.h"
#include "iperf3_util.h"
#include "iperf3_locale.h"
#include "iperf3_timer.h"
#include <stdio.h>
#include <string.h>

#define IPERF3_CLK32_TICK_TO_MS (32)


static int send_parameters(struct iperf3_test *test);
static int get_parameters(struct iperf3_test *test);
static int send_results(struct iperf3_test *test);
static int get_results(struct iperf3_test *test);
static int JSON_write(int fd, cJSON *json);
static void print_interval_results(struct iperf3_test *test, struct iperf3_stream *sp, cJSON *json_interval_streams);
static cJSON *JSON_read(int fd);


/*************************** Print usage functions ****************************/

void
usage()
{
    fputs(usage_shortstr, stderr);
}

#if 0
void
usage_long()
{
    fprintf(stderr, usage_longstr, UDP_RATE / (1024*1024), DURATION, DEFAULT_TCP_BLKSIZE / 1024, DEFAULT_UDP_BLKSIZE / 1024);
}
#else
void usage_long(void)
{
    fprintf(stderr,
        "Usage: iperf3 [options]\n"
        "  -p <port>         set server port (default: 5201)\n"
        "  -s                run in server mode\n"
        "  -c <host>         run in client mode, connect to <host>\n"
        "  -u                use UDP rather than TCP\n"
        "  -b <bandwidth>    target bandwidth in bits/sec (for UDP)\n"
        "  -t <time>         time in seconds to transmit for\n"
        "  -i <interval>     interval in seconds for report\n"
        "  -n <bytes>        number of bytes to transmit\n"
        "  -k <blocks>       number of blocks to transmit\n"
        "  -l <length>       length of buffer to read or write\n"
        "  -P <streams>      number of parallel client streams\n"
        "  -R                reverse the direction of the test (server–>client)\n"
        "  -w <size>         TCP window size (socket buffer size)\n"
        "  -B <address>      bind to <address>\n"
        "  -M <mss>          set TCP maximum segment size\n"
        "  -N                set TCP no-delay (disable Nagle's algorithm)\n"
        "  -S <tos>          set Type-of-Service (TOS) field\n"
        "  -O <omit>         skip the first <omit> seconds of the test\n"
        "  -d                enable debug mode\n"
        "  -h                display this help and exit\n"
    );
}
#endif

void warning(char *str)
{
    fprintf(stderr, "warning: %s\n", str);
}


/************** Getter routines for some fields inside iperf3_test *************/

int
iperf3_get_verbose(struct iperf3_test *ipt)
{
    return ipt->verbose;
}

int
iperf3_get_control_socket(struct iperf3_test *ipt)
{
    return ipt->ctrl_sck;
}

int
iperf3_get_test_omit(struct iperf3_test *ipt)
{
    return ipt->omit;
}

int
iperf3_get_test_duration(struct iperf3_test *ipt)
{
    return ipt->duration;
}

uint64_t
iperf3_get_test_rate(struct iperf3_test *ipt)
{
    return ipt->settings->rate;
}

int
iperf3_get_test_burst(struct iperf3_test *ipt)
{
    return ipt->settings->burst;
}

char
iperf3_get_test_role(struct iperf3_test *ipt)
{
    return ipt->role;
}

int
iperf3_get_test_reverse(struct iperf3_test *ipt)
{
    return ipt->reverse;
}

int
iperf3_get_test_blksize(struct iperf3_test *ipt)
{
    return ipt->settings->blksize;
}

int
iperf3_get_test_socket_bufsize(struct iperf3_test *ipt)
{
    return ipt->settings->socket_bufsize;
}

double
iperf3_get_test_reporter_interval(struct iperf3_test *ipt)
{
    return ipt->reporter_interval;
}

double
iperf3_get_test_stats_interval(struct iperf3_test *ipt)
{
    return ipt->stats_interval;
}

int
iperf3_get_test_num_streams(struct iperf3_test *ipt)
{
    return ipt->num_streams;
}

int
iperf3_get_test_server_port(struct iperf3_test *ipt)
{
    return ipt->server_port;
}

char*
iperf3_get_test_server_hostname(struct iperf3_test *ipt)
{
    return ipt->server_hostname;
}

int
iperf3_get_test_protocol_id(struct iperf3_test *ipt)
{
    return ipt->protocol->id;
}

int
iperf3_get_test_json_output(struct iperf3_test *ipt)
{
    return ipt->json_output;
}

int
iperf3_get_test_zerocopy(struct iperf3_test *ipt)
{
    return ipt->zerocopy;
}

int
iperf3_get_test_get_server_output(struct iperf3_test *ipt)
{
    return ipt->get_server_output;
}

char
iperf3_get_test_unit_format(struct iperf3_test *ipt)
{
    return ipt->settings->unit_format;
}

char *
iperf3_get_test_bind_address(struct iperf3_test *ipt)
{
    return ipt->bind_address;
}

int
iperf3_get_test_one_off(struct iperf3_test *ipt)
{
    return ipt->one_off;
}

/************** Setter routines for some fields inside iperf3_test *************/

void
iperf3_set_verbose(struct iperf3_test *ipt, int verbose)
{
    ipt->verbose = verbose;
}

void
iperf3_set_control_socket(struct iperf3_test *ipt, int ctrl_sck)
{
    ipt->ctrl_sck = ctrl_sck;
}

void
iperf3_set_test_omit(struct iperf3_test *ipt, int omit)
{
    ipt->omit = omit;
}

void
iperf3_set_test_duration(struct iperf3_test *ipt, int duration)
{
    ipt->duration = duration;
}

void
iperf3_set_test_reporter_interval(struct iperf3_test *ipt, double reporter_interval)
{
    ipt->reporter_interval = reporter_interval;
}

void
iperf3_set_test_stats_interval(struct iperf3_test *ipt, double stats_interval)
{
    ipt->stats_interval = stats_interval;
}

void
iperf3_set_test_state(struct iperf3_test *ipt, signed char state)
{
    ipt->state = state;
}

void
iperf3_set_test_blksize(struct iperf3_test *ipt, int blksize)
{
    ipt->settings->blksize = blksize;
}

void
iperf3_set_test_rate(struct iperf3_test *ipt, uint64_t rate)
{
    ipt->settings->rate = rate;
}

void
iperf3_set_test_burst(struct iperf3_test *ipt, int burst)
{
    ipt->settings->burst = burst;
}

void
iperf3_set_test_server_port(struct iperf3_test *ipt, int server_port)
{
    ipt->server_port = server_port;
}

void
iperf3_set_test_socket_bufsize(struct iperf3_test *ipt, int socket_bufsize)
{
    ipt->settings->socket_bufsize = socket_bufsize;
}

void
iperf3_set_test_num_streams(struct iperf3_test *ipt, int num_streams)
{
    ipt->num_streams = num_streams;
}

static void
check_sender_has_retransmits(struct iperf3_test *ipt)
{
    if (ipt->sender && ipt->protocol->id == Ptcp && has_tcpinfo_retransmits())
	ipt->sender_has_retransmits = 1;
    else
	ipt->sender_has_retransmits = 0;
}

void
iperf3_set_test_role(struct iperf3_test *ipt, char role)
{
    ipt->role = role;
    if (role == 'c')
	ipt->sender = 1;
    else if (role == 's')
	ipt->sender = 0;
    if (ipt->reverse)
        ipt->sender = ! ipt->sender;
    check_sender_has_retransmits(ipt);
}

void
iperf3_set_test_server_hostname(struct iperf3_test *ipt, char *server_hostname)
{
    ipt->server_hostname = strdup(server_hostname);
}

void
iperf3_set_test_reverse(struct iperf3_test *ipt, int reverse)
{
    ipt->reverse = reverse;
    if (ipt->reverse)
        ipt->sender = ! ipt->sender;
    check_sender_has_retransmits(ipt);
}

void
iperf3_set_test_json_output(struct iperf3_test *ipt, int json_output)
{
    ipt->json_output = json_output;
}

void
iperf3_set_test_get_server_output(struct iperf3_test *ipt, int get_server_output)
{
    ipt->get_server_output = get_server_output;
}

void
iperf3_set_test_unit_format(struct iperf3_test *ipt, char unit_format)
{
    ipt->settings->unit_format = unit_format;
}

void
iperf3_set_test_bind_address(struct iperf3_test *ipt, char *bind_address)
{
    ipt->bind_address = strdup(bind_address);
}

void
iperf3_set_test_one_off(struct iperf3_test *ipt, int one_off)
{
    ipt->one_off = one_off;
}

/********************** Get/set test protocol structure ***********************/

struct protocol *
get_protocol(struct iperf3_test *test, int prot_id)
{
    struct protocol *prot;

    SLIST_FOREACH(prot, &test->protocols, protocols) {
        if (prot->id == prot_id)
            break;
    }

    if (prot == NULL)
        i_errno = IEPROTOCOL;

    return prot;
}

int
set_protocol(struct iperf3_test *test, int prot_id)
{
    struct protocol *prot = NULL;

    SLIST_FOREACH(prot, &test->protocols, protocols) {
        if (prot->id == prot_id) {
            test->protocol = prot;
	    check_sender_has_retransmits(test);
            return 0;
        }
    }

    i_errno = IEPROTOCOL;
    return -1;
}


/************************** Iperf callback functions **************************/

void
iperf3_on_new_stream(struct iperf3_stream *sp)
{
    connect_msg(sp);
}

void
iperf3_on_test_start(struct iperf3_test *test)
{
    if (test->json_output) {
	cJSON_AddItemToObject(test->json_start, "test_start", iperf3_json_printf("protocol: %s  num_streams: %d  blksize: %d  omit: %d  duration: %d  bytes: %d  blocks: %d  reverse: %d", test->protocol->name, (int64_t) test->num_streams, (int64_t) test->settings->blksize, (int64_t) test->omit, (int64_t) test->duration, (int64_t) test->settings->bytes, (int64_t) test->settings->blocks, test->reverse?(int64_t)1:(int64_t)0));
    } else {
	if (test->verbose) {
	    if (test->settings->bytes)
		printf(test_start_bytes, test->protocol->name, test->num_streams, test->settings->blksize, test->omit, test->settings->bytes);
	    else if (test->settings->blocks)
		printf(test_start_blocks, test->protocol->name, test->num_streams, test->settings->blksize, test->omit, test->settings->blocks);
	    else
		printf(test_start_time, test->protocol->name, test->num_streams, test->settings->blksize, test->omit, test->duration);
	}
    }
}

/* This converts an IPv6 string address from IPv4-mapped format into regular
** old IPv4 format, which is easier on the eyes of network veterans.
**
** If the v6 address is not v4-mapped it is left alone.
*/
static void
mapped_v4_to_regular_v4(char *str)
{
    char *prefix = "::ffff:";
    int prefix_len;

    prefix_len = strlen(prefix);
    if (strncmp(str, prefix, prefix_len) == 0) {
	int str_len = strlen(str);
	memmove(str, str + prefix_len, str_len - prefix_len + 1);
    }
}

void
iperf3_on_connect(struct iperf3_test *test)
{
    time_t now_secs = {0};
    //const char* rfc1123_fmt = "%a, %d %b %Y %H:%M:%S GMT";
    char now_str[100];
    char ipr[INET6_ADDRSTRLEN];
    int port = 0;
    struct sockaddr_storage sa;
    struct sockaddr_in *sa_inP;
#if LWIP_IPV6
    struct sockaddr_in6 *sa_in6P;
#endif
    socklen_t len;
    int opt = 0;

    //now_secs = time((time_t*) 0);
    //(void) strftime(now_str, sizeof(now_str), rfc1123_fmt, gmtime(&now_secs));
    if (test->json_output)
	cJSON_AddItemToObject(test->json_start, "timestamp", iperf3_json_printf("time: %s  timesecs: %d", now_str, (int64_t) now_secs));
    else if (test->verbose)
	printf(report_time, now_str);

    if (test->role == 'c') {
	if (test->json_output)
	    cJSON_AddItemToObject(test->json_start, "connecting_to", iperf3_json_printf("host: %s  port: %d", test->server_hostname, (int64_t) test->server_port));
	else {
	    printf(report_connecting, test->server_hostname, test->server_port);
	    if (test->reverse)
		printf(report_reverse, test->server_hostname);
	}
    } else {
        len = sizeof(sa);
        getpeername(test->ctrl_sck, (struct sockaddr *) &sa, &len);
        if (getsockdomain(test->ctrl_sck) == AF_INET) {
	    sa_inP = (struct sockaddr_in *) &sa;
            inet_ntop(AF_INET, &sa_inP->sin_addr, ipr, sizeof(ipr));
	    port = ntohs(sa_inP->sin_port);
        } else {
#if LWIP_IPV6
	    sa_in6P = (struct sockaddr_in6 *) &sa;
            inet_ntop(AF_INET6, &sa_in6P->sin6_addr, ipr, sizeof(ipr));
	    port = ntohs(sa_in6P->sin6_port);
#endif
        }
	mapped_v4_to_regular_v4(ipr);
	if (test->json_output)
	    cJSON_AddItemToObject(test->json_start, "accepted_connection", iperf3_json_printf("host: %s  port: %d", ipr, (int64_t) port));
	else
	    printf(report_accepted, ipr, port);
    }
    if (test->json_output) {
	cJSON_AddStringToObject(test->json_start, "cookie", test->cookie);
        if (test->protocol->id == SOCK_STREAM) {
	    if (test->settings->mss)
		cJSON_AddNumberToObject(test->json_start, "tcp_mss", test->settings->mss);
	    else {
		len = sizeof(opt);
		//getsockopt(test->ctrl_sck, IPPROTO_TCP, TCP_MAXSEG, &opt, &len);
		cJSON_AddNumberToObject(test->json_start, "tcp_mss_default", opt);
	    }
	}
    } else if (test->verbose) {
        printf(report_cookie, test->cookie);
        if (test->protocol->id == SOCK_STREAM) {
            if (test->settings->mss)
                printf("      TCP MSS: %d\n", test->settings->mss);
            else {
                len = sizeof(opt);
                //getsockopt(test->ctrl_sck, IPPROTO_TCP, TCP_MAXSEG, &opt, &len);
                printf("      TCP MSS: %d (default)\n", opt);
            }
        }

    }
}

void
iperf3_on_test_finish(struct iperf3_test *test)
{
}


/******************************************************************************/
int iperf3_parse_arguments(struct iperf3_test *test, int argc, char **argv) {
    int i = 1;

    while (i < argc) {
        char *arg = argv[i];

        /* stop on non-option */
        if (arg[0] != '-' || arg[1] == '\0') {
            break;
        }

        /* single dash only */
        char opt = arg[1];
        char *val = NULL;

        /* inline value, e.g. "-p5001" */
        if (arg[2] != '\0') {
            val = &arg[2];
        }
        /* separate value, e.g. "-p 5001" */
        else if (strchr("pcbutinklPwBSOAMST", opt) && (i+1 < argc)) {
            val = argv[++i];
        }

        switch (opt) {
            case 'p':  /* port */
                if (!val) {
                    fprintf(stderr, "Missing argument for -p (port)\n");
                    return -1;
                }
                test->server_port = atoi(val);
                break;

            case 's':  /* server mode */
                iperf3_set_test_role(test, 's');
                break;

            case 'c':  /* client mode + hostname */
                if (!val) {
                    fprintf(stderr, "Missing argument for -c (client)\n");
                    return -1;
                }
                iperf3_set_test_role(test, 'c');
                iperf3_set_test_server_hostname(test, val);
                break;

            case 'u':  /* UDP */
                set_protocol(test, Pudp);
                break;

            case 'b':  /* bandwidth */
                if (!val) {
                    fprintf(stderr, "Missing argument for -b (bandwidth)\n");
                    return -1;
                }
                test->settings->rate = unit_atof_rate(val);
                break;

            case 't':  /* time (seconds) */
                if (!val) {
                    fprintf(stderr, "Missing argument for -t (time)\n");
                    return -1;
                }
                test->duration = atoi(val);
                break;

            case 'i': /* report interval (seconds) */
				if (!val) {
					fprintf(stderr, "Missing argument for -i (interval)\n");
					return -1;
				}
				test->stats_interval = atoi(val);
				test->reporter_interval = atoi(val);
				break;
            case 'n':  /* bytes */
                if (!val) {
                    fprintf(stderr, "Missing argument for -n (bytes)\n");
                    return -1;
                }
                test->settings->bytes = unit_atoi(val);
                break;

            case 'k':  /* blocks */
                if (!val) {
                    fprintf(stderr, "Missing argument for -k (blocks)\n");
                    return -1;
                }
                test->settings->blocks = unit_atoi(val);
                break;

            case 'l':  /* block size */
                if (!val) {
                    fprintf(stderr, "Missing argument for -l (block size)\n");
                    return -1;
                }
                test->settings->blksize = unit_atoi(val);
                break;

            case 'P':  /* parallel streams */
                if (!val) {
                    fprintf(stderr, "Missing argument for -P (parallel streams)\n");
                    return -1;
                }
                test->num_streams = atoi(val);
                break;

            case 'R':  /* reverse */
                iperf3_set_test_reverse(test, 1);
                break;

            case 'w':  /* socket bufsize */
                if (!val) {
                    fprintf(stderr, "Missing argument for -w (socket buffer size)\n");
                    return -1;
                }
                test->settings->socket_bufsize = unit_atof(val);
                break;

            case 'B':  /* bind address */
                if (!val) {
                    fprintf(stderr, "Missing argument for -B (bind address)\n");
                    return -1;
                }
                test->bind_address = strdup(val);
                break;

            case 'M':  /* MSS */
                if (!val) {
                    fprintf(stderr, "Missing argument for -M (MSS)\n");
                    return -1;
                }
                test->settings->mss = atoi(val);
                break;

            case 'N':  /* no-delay */
                test->no_delay = 1;
                break;

            case '4':  /* IPv4 */
                test->settings->domain = AF_INET;
                break;

            case '6':  /* IPv6 */
                test->settings->domain = AF_INET6;
                break;

            case 'S':  /* TOS */
                if (!val) {
                    fprintf(stderr, "Missing argument for -S (TOS)\n");
                    return -1;
                }
                test->settings->tos = strtol(val, NULL, 0);
                break;

            case 'O':  /* omit */
                if (!val) {
                    fprintf(stderr, "Missing argument for -O (omit seconds)\n");
                    return -1;
                }
                test->omit = atoi(val);
                break;

            case 'd':  /* debug */
                test->debug = 1;
                break;

            case 'h':  /* help */
                usage_long();
                return 1;

            default:
                fprintf(stderr, "Unknown option: -%c\n", opt);
                usage_long();
                return -1;
        }

        ++i;
    }

    /* final checks (as in original) */
    if ((test->settings->bytes && test->settings->blocks) ||
        (test->duration && test->settings->bytes) ||
        (test->duration && test->settings->blocks)) {
        i_errno = IEENDCONDITIONS;
        return -1;
    }
    if (test->role != 'c' && test->role != 's') {
        i_errno = IENOROLE;
        return -1;
    }

    return 0;
}

int
iperf3_set_send_state(struct iperf3_test *test, signed char state)
{
    test->state = state;
    if (Nwrite(test->ctrl_sck, (char*) &state, sizeof(state), Ptcp) < 0) {
	i_errno = IESENDMESSAGE;
	return -1;
    }
    return 0;
}

void
iperf3_check_throttle(struct iperf3_stream *sp, struct timeval *nowP)
{
    double seconds;
    uint64_t bits_per_second;

    if (sp->test->done)
        return;
    seconds = timeval_diff(&sp->result->start_time, nowP);
    bits_per_second = sp->result->bytes_sent * 8 / seconds;
    if (bits_per_second < sp->test->settings->rate) {
        sp->green_light = 1;
        FD_SET(sp->socket, &sp->test->write_set);
    } else {
        sp->green_light = 0;
        FD_CLR(sp->socket, &sp->test->write_set);
    }
}

int
iperf3_send(struct iperf3_test *test, fd_set *write_setP)
{
    register int multisend, r, streams_active = 0;
    register struct iperf3_stream *sp;
    struct timeval now;

    /* Can we do multisend mode? */
    if (test->settings->burst != 0)
        multisend = test->settings->burst;
    else if (test->settings->rate == 0)
        multisend = test->multisend;
    else
        multisend = 1;	/* nope */

    for (; multisend > 0; --multisend) {
	if (test->settings->rate != 0 && test->settings->burst == 0)
        iperf3_gettimeofday(&now);
	streams_active = 0;
	SLIST_FOREACH(sp, &test->streams, streams) {
	    if (sp->green_light &&
	        (write_setP == NULL || FD_ISSET(sp->socket, write_setP))) {
		if ((r = sp->snd(sp)) < 0) {
		    if (r == NET_SOFTERROR)
			break;
		    i_errno = IESTREAMWRITE;
		    return r;
		}
		streams_active = 1;
		test->bytes_sent += r;
		++test->blocks_sent;
		if (test->settings->rate != 0 && test->settings->burst == 0)
		    iperf3_check_throttle(sp, &now);
		if (multisend > 1 && test->settings->bytes != 0 && test->bytes_sent >= test->settings->bytes)
		    break;
		if (multisend > 1 && test->settings->blocks != 0 && test->blocks_sent >= test->settings->blocks)
		    break;
	    }
	}
	if (!streams_active)
	    break;
    }
    if (test->settings->burst != 0) {
        iperf3_gettimeofday(&now);
	SLIST_FOREACH(sp, &test->streams, streams)
	    iperf3_check_throttle(sp, &now);
    }
    if (write_setP != NULL)
	SLIST_FOREACH(sp, &test->streams, streams)
	    if (FD_ISSET(sp->socket, write_setP))
		FD_CLR(sp->socket, write_setP);

    return 0;
}

int
iperf3_recv(struct iperf3_test *test, fd_set *read_setP)
{
    int r;
    struct iperf3_stream *sp;

    SLIST_FOREACH(sp, &test->streams, streams) {
	if (FD_ISSET(sp->socket, read_setP)) {
	    if ((r = sp->rcv(sp)) < 0) {
		i_errno = IESTREAMREAD;
		return r;
	    }
	    test->bytes_sent += r;
	    ++test->blocks_sent;
	    FD_CLR(sp->socket, read_setP);
	}
    }

    return 0;
}

int
iperf3_init_test(struct iperf3_test *test)
{
    struct timeval now = {0};
    struct iperf3_stream *sp;

    if (test->protocol->_init) {
        if (test->protocol->_init(test) < 0)
            return -1;
    }

    /* Init each stream. */
	iperf3_gettimeofday(&now);
    SLIST_FOREACH(sp, &test->streams, streams) {
	sp->result->start_time = now;
    }

    if (test->on_test_start)
        test->on_test_start(test);

    return 0;
}

static void
send_timer_proc(TimerClientData client_data, struct timeval *nowP)
{
    struct iperf3_stream *sp = client_data.p;

    /* All we do here is set or clear the flag saying that this stream may
    ** be sent to.  The actual sending gets done in the send proc, after
    ** checking the flag.
    */
    iperf3_check_throttle(sp, nowP);
}

int
iperf3_create_send_timers(struct iperf3_test * test)
{
    struct timeval now;
    struct iperf3_stream *sp;
    TimerClientData cd;

    iperf3_gettimeofday(&now);
    SLIST_FOREACH(sp, &test->streams, streams) {
        sp->green_light = 1;
	if (test->settings->rate != 0) {
	    cd.p = sp;
	    sp->send_timer = tmr_create((struct timeval*) 0, send_timer_proc, cd, 100000L, 1);
	    /* (Repeat every tenth second - arbitrary often value.) */
	    if (sp->send_timer == NULL) {
		i_errno = IEINITTEST;
		return -1;
	    }
	}
    }
    return 0;
}

/**
 * iperf3_exchange_parameters - handles the param_Exchange part for client
 *
 */

int
iperf3_exchange_parameters(struct iperf3_test *test)
{
    int s;
    int32_t err;

    if (test->role == 'c') {

        if (send_parameters(test) < 0)
            return -1;

    } else {

        if (get_parameters(test) < 0)
            return -1;

        if ((s = test->protocol->_listen(test)) < 0) {
	    if (iperf3_set_send_state(test, SERVER_ERROR) != 0)
                return -1;
            err = htonl(i_errno);
            if (Nwrite(test->ctrl_sck, (char*) &err, sizeof(err), Ptcp) < 0) {
                i_errno = IECTRLWRITE;
                return -1;
            }
            err = htonl(errno);
            if (Nwrite(test->ctrl_sck, (char*) &err, sizeof(err), Ptcp) < 0) {
                i_errno = IECTRLWRITE;
                return -1;
            }
            return -1;
        }
        FD_SET(s, &test->read_set);
        test->max_fd = (s > test->max_fd) ? s : test->max_fd;
        test->prot_listener = s;

        // Send the control message to create streams and start the test
	if (iperf3_set_send_state(test, CREATE_STREAMS) != 0)
            return -1;

    }

    return 0;
}

/*************************************************************/

int
iperf3_exchange_results(struct iperf3_test *test)
{
    if (test->role == 'c') {
        /* Send results to server. */
	if (send_results(test) < 0)
            return -1;
        /* Get server results. */
        if (get_results(test) < 0)
            return -1;
    } else {
        /* Get client results. */
        if (get_results(test) < 0)
            return -1;
        /* Send results to client. */
	if (send_results(test) < 0)
            return -1;
    }
    return 0;
}

/*************************************************************/

static int
send_parameters(struct iperf3_test *test)
{
    int r = 0;
    cJSON *j;

    j = cJSON_CreateObject();
    if (j == NULL) {
	i_errno = IESENDPARAMS;
	r = -1;
    } else {
	if (test->protocol->id == Ptcp)
	    cJSON_AddTrueToObject(j, "tcp");
	else if (test->protocol->id == Pudp)
	    cJSON_AddTrueToObject(j, "udp");
	cJSON_AddNumberToObject(j, "omit", test->omit);
	if (test->server_affinity != -1)
	    cJSON_AddNumberToObject(j, "server_affinity", test->server_affinity);
	if (test->duration)
	    cJSON_AddNumberToObject(j, "time", test->duration);
	if (test->settings->bytes)
	    cJSON_AddNumberToObject(j, "num", test->settings->bytes);
	if (test->settings->blocks)
	    cJSON_AddNumberToObject(j, "blockcount", test->settings->blocks);
	if (test->settings->mss)
	    cJSON_AddNumberToObject(j, "MSS", test->settings->mss);
	if (test->no_delay)
	    cJSON_AddTrueToObject(j, "nodelay");
	cJSON_AddNumberToObject(j, "parallel", test->num_streams);
	if (test->reverse)
	    cJSON_AddTrueToObject(j, "reverse");
	if (test->settings->socket_bufsize)
	    cJSON_AddNumberToObject(j, "window", test->settings->socket_bufsize);
	if (test->settings->blksize)
	    cJSON_AddNumberToObject(j, "len", test->settings->blksize);
	if (test->settings->rate)
	    cJSON_AddNumberToObject(j, "bandwidth", test->settings->rate);
	if (test->settings->burst)
	    cJSON_AddNumberToObject(j, "burst", test->settings->burst);
	if (test->settings->tos)
	    cJSON_AddNumberToObject(j, "TOS", test->settings->tos);
	if (test->settings->flowlabel)
	    cJSON_AddNumberToObject(j, "flowlabel", test->settings->flowlabel);
	if (test->title)
	    cJSON_AddStringToObject(j, "title", test->title);
	if (test->congestion)
	    cJSON_AddStringToObject(j, "congestion", test->congestion);
	if (test->get_server_output)
	    cJSON_AddNumberToObject(j, "get_server_output", iperf3_get_test_get_server_output(test));

	if (test->debug) {
	    printf("send_parameters:\n%s\n", cJSON_Print(j));
	}

	if (JSON_write(test->ctrl_sck, j) < 0) {
	    i_errno = IESENDPARAMS;
	    r = -1;
	}
	cJSON_Delete(j);
    }
    return r;
}

/*************************************************************/

static int
get_parameters(struct iperf3_test *test)
{
    int r = 0;
    cJSON *j;
    cJSON *j_p;

    j = JSON_read(test->ctrl_sck);
    if (j == NULL) {
	i_errno = IERECVPARAMS;
        r = -1;
    } else {
	if (test->debug) {
	    printf("get_parameters:\n%s\n", cJSON_Print(j));
	}

	if ((j_p = cJSON_GetObjectItem(j, "tcp")) != NULL)
	    set_protocol(test, Ptcp);
	if ((j_p = cJSON_GetObjectItem(j, "udp")) != NULL)
	    set_protocol(test, Pudp);
	if ((j_p = cJSON_GetObjectItem(j, "omit")) != NULL)
	    test->omit = j_p->valueint;
	if ((j_p = cJSON_GetObjectItem(j, "server_affinity")) != NULL)
	    test->server_affinity = j_p->valueint;
	if ((j_p = cJSON_GetObjectItem(j, "time")) != NULL)
	    test->duration = j_p->valueint;
	if ((j_p = cJSON_GetObjectItem(j, "num")) != NULL)
	    test->settings->bytes = j_p->valueint;
	if ((j_p = cJSON_GetObjectItem(j, "blockcount")) != NULL)
	    test->settings->blocks = j_p->valueint;
	if ((j_p = cJSON_GetObjectItem(j, "MSS")) != NULL)
	    test->settings->mss = j_p->valueint;
	if ((j_p = cJSON_GetObjectItem(j, "nodelay")) != NULL)
	    test->no_delay = 1;
	if ((j_p = cJSON_GetObjectItem(j, "parallel")) != NULL)
	    test->num_streams = j_p->valueint;
	if ((j_p = cJSON_GetObjectItem(j, "reverse")) != NULL)
	    iperf3_set_test_reverse(test, 1);
	if ((j_p = cJSON_GetObjectItem(j, "window")) != NULL)
	    test->settings->socket_bufsize = j_p->valueint;
	if ((j_p = cJSON_GetObjectItem(j, "len")) != NULL){
		const float heap_margin = 0.7; /* percent */
	    int blksize_max = xPortGetMinimumEverFreeHeapSize() * heap_margin;

	    if(j_p->valueint >  blksize_max)
	        test->settings->blksize = blksize_max;
	    else
			test->settings->blksize = j_p->valueint;

		printf("blksize=%d/%d\n", test->settings->blksize, j_p->valueint);
	}
	if ((j_p = cJSON_GetObjectItem(j, "bandwidth")) != NULL)
	    test->settings->rate = j_p->valueint;
	if ((j_p = cJSON_GetObjectItem(j, "burst")) != NULL)
	    test->settings->burst = j_p->valueint;
	if ((j_p = cJSON_GetObjectItem(j, "TOS")) != NULL)
	    test->settings->tos = j_p->valueint;
	if ((j_p = cJSON_GetObjectItem(j, "flowlabel")) != NULL)
	    test->settings->flowlabel = j_p->valueint;
	if ((j_p = cJSON_GetObjectItem(j, "title")) != NULL)
	    test->title = strdup(j_p->valuestring);
	if ((j_p = cJSON_GetObjectItem(j, "congestion")) != NULL)
	    test->congestion = strdup(j_p->valuestring);
	if ((j_p = cJSON_GetObjectItem(j, "get_server_output")) != NULL)
	    iperf3_set_test_get_server_output(test, 1);
	if (test->sender && test->protocol->id == Ptcp && has_tcpinfo_retransmits())
	    test->sender_has_retransmits = 1;
	cJSON_Delete(j);
    }
    return r;
}

/*************************************************************/

static int
send_results(struct iperf3_test *test)
{
    int r = 0;
    cJSON *j;
    cJSON *j_streams;
    struct iperf3_stream *sp;
    cJSON *j_stream;
    int sender_has_retransmits;
    iperf3_size_t bytes_transferred;
    int retransmits;

    j = cJSON_CreateObject();
    if (j == NULL) {
	i_errno = IEPACKAGERESULTS;
	r = -1;
    } else {
	cJSON_AddNumberToObject(j, "cpu_util_total", test->cpu_util[0]);
	cJSON_AddNumberToObject(j, "cpu_util_user", test->cpu_util[1]);
	cJSON_AddNumberToObject(j, "cpu_util_system", test->cpu_util[2]);
	if ( ! test->sender )
	    sender_has_retransmits = -1;
	else
	    sender_has_retransmits = test->sender_has_retransmits;
	cJSON_AddNumberToObject(j, "sender_has_retransmits", sender_has_retransmits);

	/* If on the server and sending server output, then do this */
	if (test->role == 's' && test->get_server_output) {
	    if (test->json_output) {
		/* Add JSON output */
		cJSON_AddItemReferenceToObject(j, "server_output_json", test->json_top);
	    }
	    else {
		/* Add textual output */
		size_t buflen = 0;

		/* Figure out how much room we need to hold the complete output string */
		struct iperf3_textline *t;
		TAILQ_FOREACH(t, &(test->server_output_list), textlineentries) {
		    buflen += strlen(t->line);
		}

		/* Allocate and build it up from the component lines */
		char *output = calloc(buflen + 1, 1);
		TAILQ_FOREACH(t, &(test->server_output_list), textlineentries) {
		    strncat(output, t->line, buflen);
		    buflen -= strlen(t->line);
		}

		cJSON_AddStringToObject(j, "server_output_text", output);
	    }
	}

	j_streams = cJSON_CreateArray();
	if (j_streams == NULL) {
	    i_errno = IEPACKAGERESULTS;
	    r = -1;
	} else {
	    cJSON_AddItemToObject(j, "streams", j_streams);
	    SLIST_FOREACH(sp, &test->streams, streams) {
		j_stream = cJSON_CreateObject();
		if (j_stream == NULL) {
		    i_errno = IEPACKAGERESULTS;
		    r = -1;
		} else {
		    cJSON_AddItemToArray(j_streams, j_stream);
		    bytes_transferred = test->sender ? sp->result->bytes_sent : sp->result->bytes_received;
		    retransmits = (test->sender && test->sender_has_retransmits) ? sp->result->stream_retrans : -1;
		    cJSON_AddNumberToObject(j_stream, "id", sp->id);
		    cJSON_AddNumberToObject(j_stream, "bytes", bytes_transferred);
		    cJSON_AddNumberToObject(j_stream, "retransmits", retransmits);
		    cJSON_AddNumberToObject(j_stream, "jitter", sp->jitter);
		    cJSON_AddNumberToObject(j_stream, "errors", sp->cnt_error);
		    cJSON_AddNumberToObject(j_stream, "packets", sp->packet_count);
		}
	    }
	    if (r == 0 && test->debug) {
		printf("send_results\n%s\n", cJSON_Print(j));
	    }
	    if (r == 0 && JSON_write(test->ctrl_sck, j) < 0) {
		i_errno = IESENDRESULTS;
		r = -1;
	    }
	}
	cJSON_Delete(j);
    }
    return r;
}

/*************************************************************/

static int
get_results(struct iperf3_test *test)
{
    int r = 0;
    cJSON *j;
    cJSON *j_cpu_util_total;
    cJSON *j_cpu_util_user;
    cJSON *j_cpu_util_system;
    cJSON *j_sender_has_retransmits;
    int result_has_retransmits;
    cJSON *j_streams;
    int n, i;
    cJSON *j_stream;
    cJSON *j_id;
    cJSON *j_bytes;
    cJSON *j_retransmits;
    cJSON *j_jitter;
    cJSON *j_errors;
    cJSON *j_packets;
    cJSON *j_server_output;
    int sid, cerror, pcount;
    double jitter;
    iperf3_size_t bytes_transferred;
    int retransmits;
    struct iperf3_stream *sp;

    j = JSON_read(test->ctrl_sck);
    if (j == NULL) {
	i_errno = IERECVRESULTS;
        r = -1;
    } else {
	j_cpu_util_total = cJSON_GetObjectItem(j, "cpu_util_total");
	j_cpu_util_user = cJSON_GetObjectItem(j, "cpu_util_user");
	j_cpu_util_system = cJSON_GetObjectItem(j, "cpu_util_system");
	j_sender_has_retransmits = cJSON_GetObjectItem(j, "sender_has_retransmits");
	if (j_cpu_util_total == NULL || j_cpu_util_user == NULL || j_cpu_util_system == NULL || j_sender_has_retransmits == NULL) {
	    i_errno = IERECVRESULTS;
	    r = -1;
	} else {
	    if (test->debug) {
		printf("get_results\n%s\n", cJSON_Print(j));
	    }

	    test->remote_cpu_util[0] = j_cpu_util_total->valuedouble;
	    test->remote_cpu_util[1] = j_cpu_util_user->valuedouble;
	    test->remote_cpu_util[2] = j_cpu_util_system->valuedouble;
	    result_has_retransmits = j_sender_has_retransmits->valueint;
	    if (! test->sender)
		test->sender_has_retransmits = result_has_retransmits;
	    j_streams = cJSON_GetObjectItem(j, "streams");
	    if (j_streams == NULL) {
		i_errno = IERECVRESULTS;
		r = -1;
	    } else {
	        n = cJSON_GetArraySize(j_streams);
		for (i=0; i<n; ++i) {
		    j_stream = cJSON_GetArrayItem(j_streams, i);
		    if (j_stream == NULL) {
			i_errno = IERECVRESULTS;
			r = -1;
		    } else {
			j_id = cJSON_GetObjectItem(j_stream, "id");
			j_bytes = cJSON_GetObjectItem(j_stream, "bytes");
			j_retransmits = cJSON_GetObjectItem(j_stream, "retransmits");
			j_jitter = cJSON_GetObjectItem(j_stream, "jitter");
			j_errors = cJSON_GetObjectItem(j_stream, "errors");
			j_packets = cJSON_GetObjectItem(j_stream, "packets");
			if (j_id == NULL || j_bytes == NULL || j_retransmits == NULL || j_jitter == NULL || j_errors == NULL || j_packets == NULL) {
			    i_errno = IERECVRESULTS;
			    r = -1;
			} else {
			    sid = j_id->valueint;
			    bytes_transferred = j_bytes->valueint;
			    retransmits = j_retransmits->valueint;
			    jitter = j_jitter->valuedouble;
			    cerror = j_errors->valueint;
			    pcount = j_packets->valueint;
			    SLIST_FOREACH(sp, &test->streams, streams)
				if (sp->id == sid) break;
			    if (sp == NULL) {
				i_errno = IESTREAMID;
				r = -1;
			    } else {
				if (test->sender) {
				    sp->jitter = jitter;
				    sp->cnt_error = cerror;
				    sp->packet_count = pcount;
				    sp->result->bytes_received = bytes_transferred;
				} else {
				    sp->result->bytes_sent = bytes_transferred;
				    sp->result->stream_retrans = retransmits;
				}
			    }
			}
		    }
		}
		/*
		 * If we're the client and we're supposed to get remote results,
		 * look them up and process accordingly.
		 */
		if (test->role == 'c' && iperf3_get_test_get_server_output(test)) {
		    /* Look for JSON.  If we find it, grab the object so it doesn't get deleted. */
		    j_server_output = cJSON_DetachItemFromObject(j, "server_output_json");
		    if (j_server_output != NULL) {
			test->json_server_output = j_server_output;
		    }
		    else {
			/* No JSON, look for textual output.  Make a copy of the text for later. */
			j_server_output = cJSON_GetObjectItem(j, "server_output_text");
			if (j_server_output != NULL) {
			    test->server_output_text = strdup(j_server_output->valuestring);
			}
		    }
		}
	    }
	}
	cJSON_Delete(j);
    }
    return r;
}

/*************************************************************/

static int
JSON_write(int fd, cJSON *json)
{
    uint32_t hsize, nsize;
    char *str;
    int r = 0;

    str = cJSON_PrintUnformatted(json);
    if (str == NULL)
	r = -1;
    else {
	hsize = strlen(str);
	nsize = htonl(hsize);
	if (Nwrite(fd, (char*) &nsize, sizeof(nsize), Ptcp) < 0)
	    r = -1;
	else {
	    if (Nwrite(fd, str, hsize, Ptcp) < 0)
		r = -1;
	}
	free(str);
    }
    return r;
}

/*************************************************************/

static cJSON *
JSON_read(int fd)
{
    uint32_t hsize = 0, nsize = 0;
    char *str;
    cJSON *json = NULL;

    if (Nread(fd, (char*) &nsize, sizeof(nsize), Ptcp) >= 0) {
	hsize = ntohl(nsize);
	str = (char *) malloc(hsize+1);	/* +1 for EOS */
	if (str != NULL) {
	    if (Nread(fd, str, hsize, Ptcp) >= 0) {
		str[hsize] = '\0';	/* add the EOS */
		json = cJSON_Parse(str);
	    }
	}
	free(str);
    }
    return json;
}

/*************************************************************/
/**
 * add_to_interval_list -- adds new interval to the interval_list
 */

void
add_to_interval_list(struct iperf3_stream_result * rp, struct iperf3_interval_results * new)
{
    struct iperf3_interval_results *irp;

    irp = (struct iperf3_interval_results *) malloc(sizeof(struct iperf3_interval_results));
    memcpy(irp, new, sizeof(struct iperf3_interval_results));
    TAILQ_INSERT_TAIL(&rp->interval_results, irp, irlistentries);
}


/************************************************************/

/**
 * connect_msg -- displays connection message
 * denoting sender/receiver details
 *
 */

void
connect_msg(struct iperf3_stream *sp)
{
    char ipl[INET6_ADDRSTRLEN], ipr[INET6_ADDRSTRLEN];
    int lport = 0, rport = 0;

    if (getsockdomain(sp->socket) == AF_INET) {
        inet_ntop(AF_INET, (void *) &((struct sockaddr_in *) &sp->local_addr)->sin_addr, ipl, sizeof(ipl));
	mapped_v4_to_regular_v4(ipl);
        inet_ntop(AF_INET, (void *) &((struct sockaddr_in *) &sp->remote_addr)->sin_addr, ipr, sizeof(ipr));
	mapped_v4_to_regular_v4(ipr);
        lport = ntohs(((struct sockaddr_in *) &sp->local_addr)->sin_port);
        rport = ntohs(((struct sockaddr_in *) &sp->remote_addr)->sin_port);
    } else {
#if LWIP_IPV6
        inet_ntop(AF_INET6, (void *) &((struct sockaddr_in6 *) &sp->local_addr)->sin6_addr, ipl, sizeof(ipl));
	mapped_v4_to_regular_v4(ipl);
        inet_ntop(AF_INET6, (void *) &((struct sockaddr_in6 *) &sp->remote_addr)->sin6_addr, ipr, sizeof(ipr));
	mapped_v4_to_regular_v4(ipr);
        lport = ntohs(((struct sockaddr_in6 *) &sp->local_addr)->sin6_port);
        rport = ntohs(((struct sockaddr_in6 *) &sp->remote_addr)->sin6_port);
#endif
    }

    if (sp->test->json_output)
        cJSON_AddItemToArray(sp->test->json_connected, iperf3_json_printf("socket: %d  local_host: %s  local_port: %d  remote_host: %s  remote_port: %d", (int64_t) sp->socket, ipl, (int64_t) lport, ipr, (int64_t) rport));
    else
	iperf3_printf(sp->test, report_connected, sp->socket, ipl, lport, ipr, rport);


}


/**************************************************************************/

struct iperf3_test *
iperf3_new_test()
{
    struct iperf3_test *test;

    test = (struct iperf3_test *) malloc(sizeof(struct iperf3_test));
    if (!test) {
        i_errno = IENEWTEST;
        return NULL;
    }
    /* initialize everything to zero */
    memset(test, 0, sizeof(struct iperf3_test));

    test->settings = (struct iperf3_settings *) malloc(sizeof(struct iperf3_settings));
    if (!test->settings) {
        free(test);
	i_errno = IENEWTEST;
	return NULL;
    }
    memset(test->settings, 0, sizeof(struct iperf3_settings));

    return test;
}

/**************************************************************************/
int
iperf3_defaults(struct iperf3_test *testp)
{
    struct protocol *tcp, *udp;

#if defined(CONFIG_SUPPORT_RTOS)
	testp->print_thread_list = 0;
	testp->exit_thread_id = -1;
#endif	

    testp->omit = OMIT;
    testp->duration = DURATION;
    testp->affinity = -1;
    testp->server_affinity = -1;
    testp->title = NULL;
    testp->congestion = NULL;
    testp->server_port = PORT;
    testp->ctrl_sck = -1;
    testp->prot_listener = -1;

    testp->stats_callback = iperf3_stats_callback;
    testp->reporter_callback = iperf3_reporter_callback;

    testp->stats_interval = testp->reporter_interval = 0;
    testp->num_streams = 1;

    testp->settings->domain = AF_UNSPEC;
    testp->settings->unit_format = 'a';
    testp->settings->socket_bufsize = 0;    /* use autotuning */
    testp->settings->blksize = DEFAULT_TCP_BLKSIZE;
    testp->settings->rate = 0;
    testp->settings->burst = 0;
    testp->settings->mss = 0;
    testp->settings->bytes = 0;
    testp->settings->blocks = 0;
    memset(testp->cookie, 0, COOKIE_SIZE);

    testp->multisend = 10;	/* arbitrary */

    /* Set up protocol list */
    SLIST_INIT(&testp->streams);
    SLIST_INIT(&testp->protocols);

    tcp = (struct protocol *) malloc(sizeof(struct protocol));
    if (!tcp)
        return -1;
    memset(tcp, 0, sizeof(struct protocol));
    udp = (struct protocol *) malloc(sizeof(struct protocol));
    if (!udp) {
        free(tcp);
        return -1;
    }
    memset(udp, 0, sizeof(struct protocol));

    tcp->id = Ptcp;
    tcp->name = "TCP";
    tcp->_accept = iperf3_tcp_accept;
    tcp->_listen = iperf3_tcp_listen;
    tcp->_connect = iperf3_tcp_connect;
    tcp->_send = iperf3_tcp_send;
    tcp->_recv = iperf3_tcp_recv;
    tcp->_init = NULL;
    SLIST_INSERT_HEAD(&testp->protocols, tcp, protocols);

    udp->id = Pudp;
    udp->name = "UDP";
    udp->_accept = iperf3_udp_accept;
    udp->_listen = iperf3_udp_listen;
    udp->_connect = iperf3_udp_connect;
    udp->_send = iperf3_udp_send;
    udp->_recv = iperf3_udp_recv;
    udp->_init = iperf3_udp_init;
    SLIST_INSERT_AFTER(tcp, udp, protocols);

    set_protocol(testp, Ptcp);

    testp->on_new_stream = iperf3_on_new_stream;
    testp->on_test_start = iperf3_on_test_start;
    testp->on_connect = iperf3_on_connect;
    testp->on_test_finish = iperf3_on_test_finish;

    TAILQ_INIT(&testp->server_output_list);

    return 0;
}


/**************************************************************************/
void
iperf3_free_test(struct iperf3_test *test)
{
    struct protocol *prot;
    struct iperf3_stream *sp;

    /* Free streams */
    while (!SLIST_EMPTY(&test->streams)) {
        sp = SLIST_FIRST(&test->streams);
        SLIST_REMOVE_HEAD(&test->streams, streams);
        iperf3_free_stream(sp);
    }

    if (test->server_hostname)
	free(test->server_hostname);
    if (test->bind_address)
	free(test->bind_address);
    free(test->settings);
    if (test->title)
	free(test->title);
    if (test->congestion)
	free(test->congestion);
    if (test->omit_timer != NULL)
	tmr_cancel(test->omit_timer);
    if (test->timer != NULL)
	tmr_cancel(test->timer);
    if (test->stats_timer != NULL)
	tmr_cancel(test->stats_timer);
    if (test->reporter_timer != NULL)
	tmr_cancel(test->reporter_timer);

    /* Free protocol list */
    while (!SLIST_EMPTY(&test->protocols)) {
        prot = SLIST_FIRST(&test->protocols);
        SLIST_REMOVE_HEAD(&test->protocols, protocols);
        free(prot);
    }

    if (test->server_output_text) {
	free(test->server_output_text);
	test->server_output_text = NULL;
    }

    /* Free output line buffers, if any (on the server only) */
    struct iperf3_textline *t;
    while (!TAILQ_EMPTY(&test->server_output_list)) {
	t = TAILQ_FIRST(&test->server_output_list);
	TAILQ_REMOVE(&test->server_output_list, t, textlineentries);
	free(t->line);
	free(t);
    }

    /* XXX: Why are we setting these values to NULL? */
    // test->streams = NULL;
    test->stats_callback = NULL;
    test->reporter_callback = NULL;
    free(test);
}


void
iperf3_reset_test(struct iperf3_test *test)
{
    struct iperf3_stream *sp;

    close(test->listener);
    close(test->ctrl_sck);

    /* Free streams */
    while (!SLIST_EMPTY(&test->streams)) {
        sp = SLIST_FIRST(&test->streams);
        SLIST_REMOVE_HEAD(&test->streams, streams);
        iperf3_free_stream(sp);
    }
    if (test->omit_timer != NULL) {
	tmr_cancel(test->omit_timer);
	test->omit_timer = NULL;
    }
    if (test->timer != NULL) {
	tmr_cancel(test->timer);
	test->timer = NULL;
    }
    if (test->stats_timer != NULL) {
	tmr_cancel(test->stats_timer);
	test->stats_timer = NULL;
    }
    if (test->reporter_timer != NULL) {
	tmr_cancel(test->reporter_timer);
	test->reporter_timer = NULL;
    }
    test->done = 0;

    SLIST_INIT(&test->streams);

    test->role = 's';
    test->sender = 0;
    test->sender_has_retransmits = 0;
    set_protocol(test, Ptcp);
    test->omit = OMIT;
    test->duration = DURATION;
    test->server_affinity = -1;
    test->state = 0;

    test->ctrl_sck = -1;
    test->prot_listener = -1;

    test->bytes_sent = 0;
    test->blocks_sent = 0;

    test->reverse = 0;
    test->no_delay = 0;

    FD_ZERO(&test->read_set);
    FD_ZERO(&test->write_set);

    test->num_streams = 1;
    test->settings->socket_bufsize = 0;
    test->settings->blksize = DEFAULT_TCP_BLKSIZE;
    test->settings->rate = 0;
    test->settings->burst = 0;
    test->settings->mss = 0;
    memset(test->cookie, 0, COOKIE_SIZE);
    test->multisend = 10;	/* arbitrary */

    /* Free output line buffers, if any (on the server only) */
    struct iperf3_textline *t;
    while (!TAILQ_EMPTY(&test->server_output_list)) {
	t = TAILQ_FIRST(&test->server_output_list);
	TAILQ_REMOVE(&test->server_output_list, t, textlineentries);
	free(t->line);
	free(t);
    }
}


/* Reset all of a test's stats back to zero.  Called when the omitting
** period is over.
*/
void
iperf3_reset_stats(struct iperf3_test *test)
{
    struct timeval now = {0};
    struct iperf3_stream *sp;
    struct iperf3_stream_result *rp;

    test->bytes_sent = 0;
    test->blocks_sent = 0;
    iperf3_gettimeofday(&now);
    SLIST_FOREACH(sp, &test->streams, streams) {
	sp->omitted_packet_count = sp->packet_count;
	sp->jitter = 0;
	sp->outoforder_packets = 0;
	sp->cnt_error = 0;
	rp = sp->result;
        rp->bytes_sent = rp->bytes_received = 0;
        rp->bytes_sent_this_interval = rp->bytes_received_this_interval = 0;
	if (test->sender && test->sender_has_retransmits) {
	    struct iperf3_interval_results ir; /* temporary results structure */
	    save_tcpinfo(sp, &ir);
	    rp->stream_prev_total_retrans = get_total_retransmits(&ir);
	}
	rp->stream_retrans = 0;
	rp->start_time = now;
    }
}


/**************************************************************************/

/**
 * iperf3_stats_callback -- handles the statistic gathering for both the client and server
 *
 * XXX: This function needs to be updated to reflect the new code
 */


void
iperf3_stats_callback(struct iperf3_test *test)
{
    struct iperf3_stream *sp;
    struct iperf3_stream_result *rp = NULL;
    struct iperf3_interval_results *irp, temp;

    temp.omitted = test->omitting;
    SLIST_FOREACH(sp, &test->streams, streams) {
        rp = sp->result;

	temp.bytes_transferred = test->sender ? rp->bytes_sent_this_interval : rp->bytes_received_this_interval;

	irp = TAILQ_LAST(&rp->interval_results, irlisthead);
        /* result->end_time contains timestamp of previous interval */
        if ( irp != NULL ) /* not the 1st interval */
            memcpy(&temp.interval_start_time, &rp->end_time, sizeof(struct timeval));
        else /* or use timestamp from beginning */
            memcpy(&temp.interval_start_time, &rp->start_time, sizeof(struct timeval));
        /* now save time of end of this interval */
        iperf3_gettimeofday(&rp->end_time);
        memcpy(&temp.interval_end_time, &rp->end_time, sizeof(struct timeval));
        temp.interval_duration = timeval_diff(&temp.interval_start_time, &temp.interval_end_time);
        //temp.interval_duration = timeval_diff(&temp.interval_start_time, &temp.interval_end_time);
	if (test->protocol->id == Ptcp) {
	    if ( has_tcpinfo()) {
		save_tcpinfo(sp, &temp);
		if (test->sender && test->sender_has_retransmits) {
		    long total_retrans = get_total_retransmits(&temp);
		    temp.interval_retrans = total_retrans - rp->stream_prev_total_retrans;
		    rp->stream_retrans += temp.interval_retrans;
		    rp->stream_prev_total_retrans = total_retrans;

		    temp.snd_cwnd = get_snd_cwnd(&temp);
		}
	    }
	} else {
	    if (irp == NULL) {
		temp.interval_packet_count = sp->packet_count;
		temp.interval_outoforder_packets = sp->outoforder_packets;
		temp.interval_cnt_error = sp->cnt_error;
	    } else {
		temp.interval_packet_count = sp->packet_count - irp->packet_count;
		temp.interval_outoforder_packets = sp->outoforder_packets - irp->outoforder_packets;
		temp.interval_cnt_error = sp->cnt_error - irp->cnt_error;
	    }
	    temp.packet_count = sp->packet_count;
	    temp.jitter = sp->jitter;
	    temp.outoforder_packets = sp->outoforder_packets;
	    temp.cnt_error = sp->cnt_error;
	}
        add_to_interval_list(rp, &temp);
        rp->bytes_sent_this_interval = rp->bytes_received_this_interval = 0;
    }
}

static void
iperf3_print_intermediate(struct iperf3_test *test)
{
    char ubuf[UNIT_LEN];
    char nbuf[UNIT_LEN];
    struct iperf3_stream *sp = NULL;
    struct iperf3_interval_results *irp;
    iperf3_size_t bytes = 0;
    double bandwidth;
    int retransmits = 0;
    double start_time, end_time;
    cJSON *json_interval;
    cJSON *json_interval_streams;
    int total_packets = 0, lost_packets = 0;
    double avg_jitter = 0.0, lost_percent;
    char stbuf[20] = {0};
    char edbuf[20] = {0};
    char sumbuf[20] = {0};
    char lostbuf[20] = {0};

    if (test->json_output) {
        json_interval = cJSON_CreateObject();
	if (json_interval == NULL)
	    return;
	cJSON_AddItemToArray(test->json_intervals, json_interval);
        json_interval_streams = cJSON_CreateArray();
	if (json_interval_streams == NULL)
	    return;
	cJSON_AddItemToObject(json_interval, "streams", json_interval_streams);
    } else {
        json_interval = NULL;
        json_interval_streams = NULL;
    }

    SLIST_FOREACH(sp, &test->streams, streams) {
        print_interval_results(test, sp, json_interval_streams);
	/* sum up all streams */
	irp = TAILQ_LAST(&sp->result->interval_results, irlisthead);
	if (irp == NULL) {
	    iperf3_err(test, "iperf3_print_intermediate error: interval_results is NULL");
	    return;
	}
        bytes += irp->bytes_transferred;
	if (test->protocol->id == Ptcp) {
	    if (test->sender && test->sender_has_retransmits) {
		retransmits += irp->interval_retrans;
	    }
	} else {
            total_packets += irp->interval_packet_count;
            lost_packets += irp->interval_cnt_error;
            avg_jitter += irp->jitter;
	}
    }

    /* next build string with sum of all streams */
    if (test->num_streams > 1 || test->json_output) {
        sp = SLIST_FIRST(&test->streams); /* reset back to 1st stream */
	/* Only do this of course if there was a first stream */
	if (sp) {
        irp = TAILQ_LAST(&sp->result->interval_results, irlisthead);    /* use 1st stream for timing info */

        unit_snprintf(ubuf, UNIT_LEN, (double) bytes, 'A');
	bandwidth = (double) bytes / (double) irp->interval_duration;
        unit_snprintf(nbuf, UNIT_LEN, bandwidth, test->settings->unit_format);

        start_time = timeval_diff(&sp->result->start_time,&irp->interval_start_time);
        end_time = timeval_diff(&sp->result->start_time,&irp->interval_end_time);
	if (test->protocol->id == Ptcp) {
	    if (test->sender && test->sender_has_retransmits) {
		/* Interval sum, TCP with retransmits. */
		if (test->json_output)
		    cJSON_AddItemToObject(json_interval, "sum", iperf3_json_printf("start: %f  end: %f  seconds: %f  bytes: %d  bits_per_second: %f  retransmits: %d  omitted: %b", (double) start_time, (double) end_time, (double) irp->interval_duration, (int64_t) bytes, bandwidth * 8, (int64_t) retransmits, irp->omitted)); /* XXX irp->omitted or test->omitting? */
		else {
                iperf3_num2char(stbuf, start_time, 6, 2);
                iperf3_num2char(edbuf, end_time, 6, 2);
		        printf(report_sum_bw_retrans_format, stbuf, edbuf, ubuf, nbuf, retransmits, irp->omitted?report_omitted:""); /* XXX irp->omitted or test->omitting? */
             }
	    } else {
		/* Interval sum, TCP without retransmits. */
		if (test->json_output)
		    cJSON_AddItemToObject(json_interval, "sum", iperf3_json_printf("start: %f  end: %f  seconds: %f  bytes: %d  bits_per_second: %f  omitted: %b", (double) start_time, (double) end_time, (double) irp->interval_duration, (int64_t) bytes, bandwidth * 8, test->omitting));
		else {
                iperf3_num2char(stbuf, start_time, 6, 2);
                iperf3_num2char(edbuf, end_time, 6, 2);
		        printf(report_sum_bw_format, stbuf, edbuf, ubuf, nbuf, test->omitting?report_omitted:"");
             }
	    }
	} else {
	    /* Interval sum, UDP. */
	    if (test->sender) {
		if (test->json_output)
		    cJSON_AddItemToObject(json_interval, "sum", iperf3_json_printf("start: %f  end: %f  seconds: %f  bytes: %d  bits_per_second: %f  packets: %d  omitted: %b", (double) start_time, (double) end_time, (double) irp->interval_duration, (int64_t) bytes, bandwidth * 8, (int64_t) total_packets, test->omitting));
		else
		    printf(report_sum_bw_udp_sender_format, start_time, end_time, ubuf, nbuf, total_packets, test->omitting?report_omitted:"");
	    } else {
		avg_jitter /= test->num_streams;
		lost_percent = 100.0 * lost_packets / total_packets;
		if (test->json_output)
		    cJSON_AddItemToObject(json_interval, "sum", iperf3_json_printf("start: %f  end: %f  seconds: %f  bytes: %d  bits_per_second: %f  jitter_ms: %f  lost_packets: %d  packets: %d  lost_percent: %f  omitted: %b", (double) start_time, (double) end_time, (double) irp->interval_duration, (int64_t) bytes, bandwidth * 8, (double) (avg_jitter * (double)1000.0), (int64_t) lost_packets, (int64_t) total_packets, (double) lost_percent, test->omitting));
		else {
                iperf3_num2char(stbuf, start_time, 6, 2);
                iperf3_num2char(edbuf, end_time, 6, 2);
                iperf3_num2char(sumbuf, (double)(avg_jitter * (double)1000.0), 5, 3);
                iperf3_num2char(lostbuf, lost_percent, 3, 2);
		        printf(report_sum_bw_udp_format, stbuf, edbuf, ubuf, nbuf, sumbuf, lost_packets, total_packets, lostbuf, test->omitting?report_omitted:"");
             }
	    }
	}
	}
    }
}

static void
iperf3_print_results(struct iperf3_test *test)
{
    cJSON *json_summary_streams = NULL;
    cJSON *json_summary_stream = NULL;
    int total_retransmits = 0;
    int total_packets = 0, lost_packets = 0;
    char ubuf[UNIT_LEN];
    char nbuf[UNIT_LEN];

    char sbuf[UNIT_LEN];
    struct iperf3_stream *sp = NULL;
    iperf3_size_t bytes_sent, total_sent = 0;
    iperf3_size_t bytes_received, total_received = 0;
    double start_time, end_time = 0.0, avg_jitter = 0.0, lost_percent;
    double bandwidth;
    char stbuf[20] = {0};
    char edbuf[20] = {0};
    char sumbuf[20] = {0};
    char lostbuf[20] = {0};

    /* print final summary for all intervals */
    if (test->json_output) {
        json_summary_streams = cJSON_CreateArray();
		if (json_summary_streams == NULL)
			return;
		cJSON_AddItemToObject(test->json_end, "streams", json_summary_streams);
    } else {
		printf("%s", report_bw_separator);
		if (test->verbose)
			printf("%s", report_summary);
		if (test->protocol->id == Ptcp) {
			if (test->sender_has_retransmits)
				printf("%s", report_bw_retrans_header);
			else
				printf("%s", report_bw_header);
		} else
			printf("%s", report_bw_udp_header);
    }

    start_time = 0.;
    sp = SLIST_FIRST(&test->streams);
    /*
     * If there is at least one stream, then figure out the length of time
     * we were running the tests and print out some statistics about
     * the streams.  It's possible to not have any streams at all
     * if the client got interrupted before it got to do anything.
     */
    if (sp) {
		end_time = timeval_diff(&sp->result->start_time, &sp->result->end_time);
		SLIST_FOREACH(sp, &test->streams, streams) {
			if (test->json_output) {
				json_summary_stream = cJSON_CreateObject();
				if (json_summary_stream == NULL)
					return;
				cJSON_AddItemToArray(json_summary_streams, json_summary_stream);
			}

			bytes_sent = sp->result->bytes_sent;
			bytes_received = sp->result->bytes_received;
			total_sent += bytes_sent;
			total_received += bytes_received;

			if (test->protocol->id == Ptcp) {
				if (test->sender_has_retransmits) {
					total_retransmits += sp->result->stream_retrans;
				}
			} else {
				total_packets += (sp->packet_count - sp->omitted_packet_count);
				lost_packets += sp->cnt_error;
				avg_jitter += sp->jitter;
			}

			unit_snprintf(ubuf, UNIT_LEN, (double) bytes_sent, 'A');
			bandwidth = (double) bytes_sent / (double) end_time;
			unit_snprintf(nbuf, UNIT_LEN, bandwidth, test->settings->unit_format);
			if (test->protocol->id == Ptcp) {
				if (test->sender_has_retransmits) {
					/* Summary, TCP with retransmits. */
					if (test->json_output)
						cJSON_AddItemToObject(json_summary_stream, "sender", iperf3_json_printf("socket: %d  start: %f  end: %f  seconds: %f  bytes: %d  bits_per_second: %f  retransmits: %d", (int64_t) sp->socket, (double) start_time, (double) end_time, (double) end_time, (int64_t) bytes_sent, bandwidth * 8, (int64_t) sp->result->stream_retrans));
					else {
						iperf3_num2char(stbuf, start_time, 6, 2);
						iperf3_num2char(edbuf, end_time, 6, 2);
						printf(report_bw_retrans_format, sp->socket, stbuf, edbuf, ubuf, nbuf, sp->result->stream_retrans, report_sender);
					}
				} else {
					/* Summary, TCP without retransmits. */
					if (test->json_output)
						cJSON_AddItemToObject(json_summary_stream, "sender", iperf3_json_printf("socket: %d  start: %f  end: %f  seconds: %f  bytes: %d  bits_per_second: %f", (int64_t) sp->socket, (double) start_time, (double) end_time, (double) end_time, (int64_t) bytes_sent, bandwidth * 8));
					else {
						iperf3_num2char(stbuf, start_time, 6, 2);
						iperf3_num2char(edbuf, end_time, 6, 2);
						printf(report_bw_format, sp->socket, stbuf, edbuf, ubuf, nbuf, report_sender);
					}
				}
			} else {
				/* Summary, UDP. */
				lost_percent = 100.0 * sp->cnt_error / (sp->packet_count - sp->omitted_packet_count);
				if (test->json_output)
					cJSON_AddItemToObject(json_summary_stream, "udp", iperf3_json_printf("socket: %d  start: %f  end: %f  seconds: %f  bytes: %d  bits_per_second: %f  jitter_ms: %f  lost_packets: %d  packets: %d  lost_percent: %f", (int64_t) sp->socket, (double) start_time, (double) end_time, (double) end_time, (int64_t) bytes_sent, bandwidth * 8, (double) sp->jitter * (double)1000.0, (int64_t) sp->cnt_error, (int64_t) (sp->packet_count - sp->omitted_packet_count), (double) lost_percent));
				else {
					iperf3_num2char(stbuf, start_time, 6, 2);
					iperf3_num2char(edbuf, end_time, 6, 2);
					iperf3_num2char(sumbuf, (double)(sp->jitter * (double)1000.0), 5, 3);
					iperf3_num2char(lostbuf, lost_percent, 3, 2);
					printf(report_bw_udp_format, sp->socket, stbuf, edbuf, ubuf, nbuf, sumbuf, sp->cnt_error, (sp->packet_count - sp->omitted_packet_count), lostbuf, "");
					if (test->role == 'c')
						printf(report_datagrams, sp->socket, (sp->packet_count - sp->omitted_packet_count));
					if (sp->outoforder_packets > 0)
					{
						iperf3_num2char(stbuf, start_time, 4, 1);
						iperf3_num2char(edbuf, end_time, 4, 1);
						printf(report_sum_outoforder, stbuf, edbuf, sp->cnt_error);
					}
				}
			}

			unit_snprintf(ubuf, UNIT_LEN, (double) bytes_received, 'A');
			bandwidth = (double) bytes_received / (double) end_time;
			unit_snprintf(nbuf, UNIT_LEN, bandwidth, test->settings->unit_format);
			if (test->protocol->id == Ptcp) {
				if (test->json_output)
					cJSON_AddItemToObject(json_summary_stream, "receiver", iperf3_json_printf("socket: %d  start: %f  end: %f  seconds: %f  bytes: %d  bits_per_second: %f", (int64_t) sp->socket, (double) start_time, (double) end_time, (double) end_time, (int64_t) bytes_received, bandwidth * 8));
				else {
					iperf3_num2char(stbuf, start_time, 6, 2);
					iperf3_num2char(edbuf, end_time, 6, 2);
					printf(report_bw_format, sp->socket, stbuf, edbuf, ubuf, nbuf, report_receiver);
				}
			}
		}
    }

    if (test->num_streams > 1 || test->json_output) {
        unit_snprintf(ubuf, UNIT_LEN, (double) total_sent, 'A');
		/* If no tests were run, arbitrariliy set bandwidth to 0. */
		if (end_time > (double)0.0) {
			bandwidth = (double) total_sent / (double) end_time;
		}
		else {
			bandwidth = (double)0.0;
		}
        unit_snprintf(nbuf, UNIT_LEN, bandwidth, test->settings->unit_format);
        if (test->protocol->id == Ptcp) {
			if (test->sender_has_retransmits) {
				/* Summary sum, TCP with retransmits. */
				if (test->json_output)
					cJSON_AddItemToObject(test->json_end, "sum_sent", iperf3_json_printf("start: %f  end: %f  seconds: %f  bytes: %d  bits_per_second: %f  retransmits: %d", (double) start_time, (double) end_time, (double) end_time, (int64_t) total_sent, bandwidth * 8, (int64_t) total_retransmits));
				else {
					iperf3_num2char(stbuf, start_time, 6, 2);
					iperf3_num2char(edbuf, end_time, 6, 2);
					printf(report_sum_bw_retrans_format, stbuf, edbuf, ubuf, nbuf, total_retransmits, report_sender);
				}
			} else {
				/* Summary sum, TCP without retransmits. */
				if (test->json_output)
					cJSON_AddItemToObject(test->json_end, "sum_sent", iperf3_json_printf("start: %f  end: %f  seconds: %f  bytes: %d  bits_per_second: %f", (double) start_time, (double) end_time, (double) end_time, (int64_t) total_sent, bandwidth * 8));
				else {
					iperf3_num2char(stbuf, start_time, 6, 2);
					iperf3_num2char(edbuf, end_time, 6, 2);
					printf(report_sum_bw_format, stbuf, edbuf, ubuf, nbuf, report_sender);
				}
			}
            unit_snprintf(ubuf, UNIT_LEN, (double) total_received, 'A');
			/* If no tests were run, set received bandwidth to 0 */
			if (end_time > (double)0.0) {
				bandwidth = (double) total_received / (double) end_time;
			}
			else {
				bandwidth = (double)0.0;
			}
            unit_snprintf(nbuf, UNIT_LEN, bandwidth, test->settings->unit_format);
			if (test->json_output)
				cJSON_AddItemToObject(test->json_end, "sum_received", iperf3_json_printf("start: %f  end: %f  seconds: %f  bytes: %d  bits_per_second: %f", (double) start_time, (double) end_time, (double) end_time, (int64_t) total_received, bandwidth * 8));
			else {
                iperf3_num2char(stbuf, start_time, 6, 2);
                iperf3_num2char(edbuf, end_time, 6, 2);
		        printf(report_sum_bw_format, stbuf, edbuf, ubuf, nbuf, report_receiver);
			}
        } else {
			/* Summary sum, UDP. */
            avg_jitter /= test->num_streams;
			/* If no packets were sent, arbitrarily set loss percentage to 100. */
			if (total_packets > 0) {
				lost_percent = 100.0 * lost_packets / total_packets;
			}
			else {
				lost_percent = 100.0;
			}
			if (test->json_output)
				cJSON_AddItemToObject(test->json_end, "sum", iperf3_json_printf("start: %f  end: %f  seconds: %f  bytes: %d  bits_per_second: %f  jitter_ms: %f  lost_packets: %d  packets: %d  lost_percent: %f", (double) start_time, (double) end_time, (double) end_time, (int64_t) total_sent, bandwidth * 8, (double) avg_jitter * (double)1000.0, (int64_t) lost_packets, (int64_t) total_packets, (double) lost_percent));
			else {
                iperf3_num2char(stbuf, start_time, 6, 2);
                iperf3_num2char(edbuf, end_time, 6, 2);
                iperf3_num2char(sumbuf, (double)(avg_jitter * (double)1000.0), 5, 3);
                iperf3_num2char(lostbuf, lost_percent, 3, 2);
		        printf(report_sum_bw_udp_format, stbuf, edbuf, ubuf, nbuf, sumbuf, lost_packets, total_packets, lostbuf, "");
			}
        }
    }

    if (test->json_output)
		cJSON_AddItemToObject(test->json_end, "cpu_utilization_percent", iperf3_json_printf("host_total: %f  host_user: %f  host_system: %f  remote_total: %f  remote_user: %f  remote_system: %f", (double) test->cpu_util[0], (double) test->cpu_util[1], (double) test->cpu_util[2], (double) test->remote_cpu_util[0], (double) test->remote_cpu_util[1], (double) test->remote_cpu_util[2]));
    else {
		if (test->verbose) {
			printf(report_cpu, report_local, test->sender?report_sender:report_receiver, test->cpu_util[0], test->cpu_util[1], test->cpu_util[2], report_remote, test->sender?report_receiver:report_sender, test->remote_cpu_util[0], test->remote_cpu_util[1], test->remote_cpu_util[2]);
		}

		/* Print server output if we're on the client and it was requested/provided */
		if (test->role == 'c' && iperf3_get_test_get_server_output(test)) {
			if (test->json_server_output) {
				printf("\nServer JSON output:\n%s\n", cJSON_Print(test->json_server_output));
				cJSON_Delete(test->json_server_output);
				test->json_server_output = NULL;
			}
			if (test->server_output_text) {
				printf("\nServer output:\n%s\n", test->server_output_text);
				test->server_output_text = NULL;
			}
		}
    }
}

/**************************************************************************/

/**
 * iperf3_reporter_callback -- handles the report printing
 *
 */

void
iperf3_reporter_callback(struct iperf3_test *test)
{
    switch (test->state) {
        case TEST_RUNNING:
        case STREAM_RUNNING:
            /* print interval results for each stream */
            iperf3_print_intermediate(test);
            break;
        case DISPLAY_RESULTS:
            iperf3_print_intermediate(test);
            iperf3_print_results(test);
            break;
    }

}

/**************************************************************************/
static void
print_interval_results(struct iperf3_test *test, struct iperf3_stream *sp, cJSON *json_interval_streams)
{
    char ubuf[UNIT_LEN];
    char nbuf[UNIT_LEN];
    char cbuf[UNIT_LEN];
    char stbuf[20] = {0};
    char edbuf[20] = {0};
    char sumbuf[20] = {0};
    char lostbuf[20] = {0};
    double st = 0., et = 0.;
    struct iperf3_interval_results *irp = NULL;
    double bandwidth, lost_percent;

    irp = TAILQ_LAST(&sp->result->interval_results, irlisthead); /* get last entry in linked list */
    if (irp == NULL) {
	iperf3_err(test, "print_interval_results error: interval_results is NULL");
        return;
    }
    if (!test->json_output) {
	/* First stream? */
	if (sp == SLIST_FIRST(&test->streams)) {
	    /* It it's the first interval, print the header;
	    ** else if there's more than one stream, print the separator;
	    ** else nothing.
	    */
	    if (timeval_equals(&sp->result->start_time, &irp->interval_start_time)) {
		if (test->protocol->id == Ptcp) {
		    if (test->sender && test->sender_has_retransmits)
			printf("%s", report_bw_retrans_cwnd_header);
		    else
			printf("%s", report_bw_header);
		} else {
		    if (test->sender)
			printf("%s", report_bw_udp_sender_header);
		    else
			printf("%s", report_bw_udp_header);
		}
	    } else if (test->num_streams > 1)
		printf("%s", report_bw_separator);
	}
    }

    unit_snprintf(ubuf, UNIT_LEN, (double) (irp->bytes_transferred), 'A');
    bandwidth = (double) irp->bytes_transferred / (double) irp->interval_duration;
    unit_snprintf(nbuf, UNIT_LEN, bandwidth, test->settings->unit_format);

    st = timeval_diff(&sp->result->start_time, &irp->interval_start_time);
    et = timeval_diff(&sp->result->start_time, &irp->interval_end_time);

    if (test->protocol->id == Ptcp) {
	if (test->sender && test->sender_has_retransmits) {
	    /* Interval, TCP with retransmits. */
	    if (test->json_output)
		cJSON_AddItemToArray(json_interval_streams, iperf3_json_printf("socket: %d  start: %f  end: %f  seconds: %f  bytes: %d  bits_per_second: %f  retransmits: %d  snd_cwnd:  %d  omitted: %b", (int64_t) sp->socket, (double) st, (double) et, (double) irp->interval_duration, (int64_t) irp->bytes_transferred, bandwidth * 8, (int64_t) irp->interval_retrans, (int64_t) irp->snd_cwnd, irp->omitted));
	    else {
		unit_snprintf(cbuf, UNIT_LEN, irp->snd_cwnd, 'A');
        iperf3_num2char(stbuf, st, 6, 2);
        iperf3_num2char(edbuf, et, 6, 2);
		printf(report_bw_retrans_cwnd_format, sp->socket, stbuf, edbuf, ubuf, nbuf, irp->interval_retrans, cbuf, irp->omitted?report_omitted:"");
	    }
	} else {
	    /* Interval, TCP without retransmits. */
	    if (test->json_output)
		cJSON_AddItemToArray(json_interval_streams, iperf3_json_printf("socket: %d  start: %f  end: %f  seconds: %f  bytes: %d  bits_per_second: %f  omitted: %b", (int64_t) sp->socket, (double) st, (double) et, (double) irp->interval_duration, (int64_t) irp->bytes_transferred, bandwidth * 8, irp->omitted));
	    else {
        iperf3_num2char(stbuf, st, 6, 2);
        iperf3_num2char(edbuf, et, 6, 2);
		printf(report_bw_format, sp->socket, stbuf, edbuf, ubuf, nbuf, irp->omitted?report_omitted:"");
        }
	}
    } else {
	/* Interval, UDP. */
	if (test->sender) {
	    if (test->json_output)
		cJSON_AddItemToArray(json_interval_streams, iperf3_json_printf("socket: %d  start: %f  end: %f  seconds: %f  bytes: %d  bits_per_second: %f  packets: %d  omitted: %b", (int64_t) sp->socket, (double) st, (double) et, (double) irp->interval_duration, (int64_t) irp->bytes_transferred, bandwidth * 8, (int64_t) irp->interval_packet_count, irp->omitted));
	    else {
        iperf3_num2char(stbuf, st, 6, 2);
        iperf3_num2char(edbuf, et, 6, 2);
		printf(report_bw_udp_sender_format, sp->socket, stbuf, edbuf, ubuf, nbuf, irp->interval_packet_count, irp->omitted?report_omitted:"");
        }
	} else {
	    lost_percent = 100.0 * irp->interval_cnt_error / irp->interval_packet_count;
	    if (test->json_output)
		cJSON_AddItemToArray(json_interval_streams, iperf3_json_printf("socket: %d  start: %f  end: %f  seconds: %f  bytes: %d  bits_per_second: %f  jitter_ms: %f  lost_packets: %d  packets: %d  lost_percent: %f  omitted: %b", (int64_t) sp->socket, (double) st, (double) et, (double) irp->interval_duration, (int64_t) irp->bytes_transferred, bandwidth * 8, (double) irp->jitter * (double)1000.0, (int64_t) irp->interval_cnt_error, (int64_t) irp->interval_packet_count, (double) lost_percent, irp->omitted));
	    else {
        iperf3_num2char(stbuf, st, 6, 2);
        iperf3_num2char(edbuf, et, 6, 2);
        iperf3_num2char(sumbuf, (double)irp->jitter * (double)1000.0, 5, 3);
        iperf3_num2char(lostbuf, lost_percent, 3, 2);
		printf(report_bw_udp_format, sp->socket, stbuf, edbuf, ubuf, nbuf, sumbuf, irp->interval_cnt_error, irp->interval_packet_count, lostbuf, irp->omitted?report_omitted:"");
        }
	}
    }
}

/**************************************************************************/
void
iperf3_free_stream(struct iperf3_stream *sp)
{
    struct iperf3_interval_results *irp, *nirp;

    /* XXX: need to free interval list too! */
    //munmap(sp->buffer, sp->test->settings->blksize);
    free(sp->buffer);

    for (irp = TAILQ_FIRST(&sp->result->interval_results); irp != TAILQ_END(sp->result->interval_results); irp = nirp) {
        nirp = TAILQ_NEXT(irp, irlistentries);
        free(irp);
    }
    free(sp->result);
    if (sp->send_timer != NULL)
		tmr_cancel(sp->send_timer);
    free(sp);
}

/**************************************************************************/
struct iperf3_stream *
iperf3_new_stream(struct iperf3_test *test, int s)
{
    int i;
    struct iperf3_stream *sp;
    //char template[] = "/tmp/iperf3.XXXXXX";
    struct timeval now = {0};

    h_errno = 0;

    sp = (struct iperf3_stream *) malloc(sizeof(struct iperf3_stream));
    if (!sp) {
        i_errno = IECREATESTREAM;
        return NULL;
    }

    memset(sp, 0, sizeof(struct iperf3_stream));

    sp->test = test;
    sp->settings = test->settings;
    sp->result = (struct iperf3_stream_result *) malloc(sizeof(struct iperf3_stream_result));
    if (!sp->result) {
        free(sp);
        i_errno = IECREATESTREAM;
        return NULL;
    }

    memset(sp->result, 0, sizeof(struct iperf3_stream_result));
    TAILQ_INIT(&sp->result->interval_results);

    /* Create and randomize the buffer */
/*
    sp->buffer_fd = mkstemp(template);
    if (sp->buffer_fd == -1) {
        i_errno = IECREATESTREAM;
        free(sp->result);
        free(sp);
        return NULL;
    }
    if (unlink(template) < 0) {
        i_errno = IECREATESTREAM;
        free(sp->result);
        free(sp);
        return NULL;
    }
    if (ftruncate(sp->buffer_fd, test->settings->blksize) < 0) {
        i_errno = IECREATESTREAM;
        free(sp->result);
        free(sp);
        return NULL;
    }
    sp->buffer = (char *) mmap(NULL, test->settings->blksize, PROT_READ|PROT_WRITE, MAP_PRIVATE, sp->buffer_fd, 0);
    if (sp->buffer == MAP_FAILED) {
        i_errno = IECREATESTREAM;
        free(sp->result);
        free(sp);
        return NULL;
    }
*/
    sp->buffer = NULL;
    sp->buffer = (char *) malloc(test->settings->blksize);
    if (sp->buffer == NULL) {
        i_errno = IECREATESTREAM;
        free(sp->result);
        free(sp);
        return NULL;
    }

    //srand(time(NULL));
    iperf3_gettimeofday(&now);
    srand(now.tv_usec);

    for (i = 0; i < test->settings->blksize; ++i)
        sp->buffer[i] = rand();

    sp->buffer[i-1]='\0';
    /* Set socket */
    sp->socket = s;

    sp->snd = test->protocol->_send;
    sp->rcv = test->protocol->_recv;

    /* Initialize stream */
    if (iperf3_init_stream(sp, test) < 0) {
        //close(sp->buffer_fd);
        //munmap(sp->buffer, sp->test->settings->blksize);
        free(sp->buffer);
        free(sp->result);
        free(sp);
        return NULL;
    }
    iperf3_add_stream(test, sp);

    return sp;
}

/**************************************************************************/
int
iperf3_init_stream(struct iperf3_stream *sp, struct iperf3_test *test)
{
    socklen_t len;
    int opt;

    len = sizeof(struct sockaddr_storage);
    if (getsockname(sp->socket, (struct sockaddr *) &sp->local_addr, &len) < 0) {
        i_errno = IEINITSTREAM;
        return -1;
    }
    len = sizeof(struct sockaddr_storage);
    if (getpeername(sp->socket, (struct sockaddr *) &sp->remote_addr, &len) < 0) {
        i_errno = IEINITSTREAM;
        return -1;
    }

    /* Set IP TOS */
    if ((opt = test->settings->tos)) {
        if (getsockdomain(sp->socket) == AF_INET6) {
#ifdef IPV6_TCLASS
            if (setsockopt(sp->socket, IPPROTO_IPV6, IPV6_TCLASS, &opt, sizeof(opt)) < 0) {
                i_errno = IESETCOS;
                return -1;
            }
#else
            i_errno = IESETCOS;
            return -1;
#endif
        } else {
            if (setsockopt(sp->socket, IPPROTO_IP, IP_TOS, &opt, sizeof(opt)) < 0) {
                i_errno = IESETTOS;
                return -1;
            }
        }
    }

    return 0;
}

/**************************************************************************/
void
iperf3_add_stream(struct iperf3_test *test, struct iperf3_stream *sp)
{
    int i;
    struct iperf3_stream *n, *prev;

    if (SLIST_EMPTY(&test->streams)) {
        SLIST_INSERT_HEAD(&test->streams, sp, streams);
        sp->id = 1;
    } else {
        // for (n = test->streams, i = 2; n->next; n = n->next, ++i);
        i = 2;
        SLIST_FOREACH(n, &test->streams, streams) {
            prev = n;
            ++i;
        }
        SLIST_INSERT_AFTER(prev, sp, streams);
        sp->id = i;
    }
}

void
iperf3_got_sigend(struct iperf3_test *test)
{
    /*
     * If we're the client, or if we're a server and running a test,
     * then dump out the accumulated stats so far.
     */
    if (test->role == 'c' ||
      (test->role == 's' && test->state == TEST_RUNNING)) {

	test->done = 1;
	cpu_util(test->cpu_util);
	test->stats_callback(test);
	test->state = DISPLAY_RESULTS; /* change local state only */
	if (test->on_test_finish)
	    test->on_test_finish(test);
	test->reporter_callback(test);
    }

    if (test->ctrl_sck >= 0) {
	test->state = (test->role == 'c') ? CLIENT_TERMINATE : SERVER_TERMINATE;
	(void) Nwrite(test->ctrl_sck, (char*) &test->state, sizeof(signed char), Ptcp);
    }
    i_errno = (test->role == 'c') ? IECLIENTTERM : IESERVERTERM;
    iperf3_errexit(test, "interrupt - %s", iperf3_strerror(i_errno));
}


int
iperf3_json_start(struct iperf3_test *test)
{
    test->json_top = cJSON_CreateObject();
    if (test->json_top == NULL)
        return -1;
    if (test->title)
	cJSON_AddStringToObject(test->json_top, "title", test->title);
    test->json_start = cJSON_CreateObject();
    if (test->json_start == NULL)
        return -1;
    cJSON_AddItemToObject(test->json_top, "start", test->json_start);
    test->json_connected = cJSON_CreateArray();
    if (test->json_connected == NULL)
        return -1;
    cJSON_AddItemToObject(test->json_start, "connected", test->json_connected);
    test->json_intervals = cJSON_CreateArray();
    if (test->json_intervals == NULL)
        return -1;
    cJSON_AddItemToObject(test->json_top, "intervals", test->json_intervals);
    test->json_end = cJSON_CreateObject();
    if (test->json_end == NULL)
        return -1;
    cJSON_AddItemToObject(test->json_top, "end", test->json_end);
    return 0;
}

int
iperf3_json_finish(struct iperf3_test *test)
{
    char *str;

    /* Include server output */
    if (test->json_server_output) {
	cJSON_AddItemToObject(test->json_top, "server_output_json", test->json_server_output);
    }
    if (test->server_output_text) {
	cJSON_AddStringToObject(test->json_top, "server_output_text", test->server_output_text);
    }
    str = cJSON_Print(test->json_top);
    if (str == NULL)
        return -1;
    fputs(str, stdout);
    putchar('\n');
    fflush(stdout);
    free(str);
    cJSON_Delete(test->json_top);
    test->json_top = test->json_start = test->json_connected = test->json_intervals = test->json_server_output = test->json_end = NULL;
    return 0;
}


/* CPU affinity stuff - linux only. */

int
iperf3_setaffinity(int affinity)
{
#ifdef linux
    cpu_set_t cpu_set;

    CPU_ZERO(&cpu_set);
    CPU_SET(affinity, &cpu_set);
    if (sched_setaffinity(0, sizeof(cpu_set_t), &cpu_set) != 0) {
	i_errno = IEAFFINITY;
        return -1;
    }
    return 0;
#else /*linux*/
    i_errno = IEAFFINITY;
    return -1;
#endif /*linux*/
}

int
iperf3_clearaffinity(void)
{
#ifdef linux
    cpu_set_t cpu_set;
    int i;

    CPU_ZERO(&cpu_set);
    for (i = 0; i < CPU_SETSIZE; ++i)
	CPU_SET(i, &cpu_set);
    if (sched_setaffinity(0, sizeof(cpu_set_t), &cpu_set) != 0) {
	i_errno = IEAFFINITY;
        return -1;
    }
    return 0;
#else /*linux*/
    i_errno = IEAFFINITY;
    return -1;
#endif /*linux*/
}

int
iperf3_printf(struct iperf3_test *test, const char* format, ...)
{
    va_list argp;
    int r = -1;

    /*
     * There are roughly two use cases here.  If we're the client,
     * want to print stuff directly to the output stream.
     * If we're the sender we might need to buffer up output to send
     * to the client.
     *
     * This doesn't make a whole lot of difference except there are
     * some chunks of output on the client (on particular the whole
     * of the server output with --get-server-output) that could
     * easily exceed the size of the line buffer, but which don't need
     * to be buffered up anyway.
     */
    if (test->role == 'c') {
	if (test->title)
	    printf("%s:  ", test->title);
	va_start(argp, format);
	r = vprintf(format, argp);
	va_end(argp);
    }
    else if (test->role == 's') {
	char linebuffer[1024];
	va_start(argp, format);
	r = vsnprintf(linebuffer, sizeof(linebuffer), format, argp);
	va_end(argp);
	printf("%s", linebuffer);

	if (test->role == 's' && iperf3_get_test_get_server_output(test)) {
	    struct iperf3_textline *l = (struct iperf3_textline *) malloc(sizeof(struct iperf3_textline));
	    l->line = strdup(linebuffer);
	    TAILQ_INSERT_TAIL(&(test->server_output_list), l, textlineentries);
	}
    }
    return r;
}

int
iperf3_gettimeofday(struct timeval *tv)
{
    unsigned int current_ms = 0;

	int unit = 1000/configTICK_RATE_HZ;
	TickType_t cur = xTaskGetTickCount()*unit;

	tv->tv_sec = (cur + 1) / (unit*configTICK_RATE_HZ);
	tv->tv_usec = (cur % unit*configTICK_RATE_HZ)*1000;

	current_ms = (tv->tv_sec * 1000) + (tv->tv_usec / 1000);
    return 0;
}

char *					/* O - New string pointer */
iperf3_strdup(const char *s)		/* I - String to duplicate */
{
  char	*t;				/* New string pointer */

  if (s == NULL)
    return (NULL);

  if ((t = malloc(strlen(s) + 1)) == NULL)
    return (NULL);

  return (strcpy(t, s));
}


static const char iperf3_table[]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

void iperf3_num2char(char *str, double number, unsigned g, unsigned l)
{
    unsigned i;
    int temp = number/1;
    double t2 = 0.0;
    for (i = 1; i<=g; i++)
    {
        if (temp==0)
            str[g-i] = iperf3_table[0];
        else
            str[g-i] = iperf3_table[temp%10];
        temp = temp/10;
    }
    *(str+g) = '.';
    temp = 0;
    t2 = number;
    for(i=1; i<=l; i++)
    {
        temp = t2*10;
        str[g+i] = iperf3_table[temp%10];
        t2 = t2*10;
    }
    *(str+g+l+1) = '\0';

    i = 0;
    while(*(str + i) == '0' && *(str + i + 1) != '.')
    {
        *(str + i) = ' ';
        i++;
    }
}
