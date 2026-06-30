#include "nrc_sdk.h"
#include "nrc_iperf.h"

static int str_to_argc_argv(const char* str, int* argc, char*** argv) {
	int i, j, len, n;
	char** res, * p;

	/* count the number of arguments */
	len = strlen(str);
	for (i = n = 0; i < len; ) {
		while (i < len && str[i] == ' ')
			i++;
		if (i == len)
			break;
		n++;
		while (i < len && str[i] != ' ')
			i++;
	}

	/* allocate space for argv */
	res = (char**)nrc_mem_malloc((n + 1) * sizeof(char*));
	if (!res)
		return -1;

	/* fill argv with pointers to arguments */
	p = (char*)nrc_mem_malloc(len + 1);
	if (!p) {
		nrc_mem_free(res);
		return -1;
	}
	strcpy(p, str);
	for (i = j = 0; i < len; ) {
		while (i < len && p[i] == ' ')
			p[i++] = '\0';
		if (i == len)
			break;
		res[j++] = p + i;
		while (i < len && p[i] != ' ')
			i++;
	}
	res[j] = NULL;

	/* set argc and argv */
	*argc = n;
	*argv = res;

	return 0;
}

void start_iperf_server()
{
		char str[200];
	int argc = 0;
	char** argv = 0;
	_delay_ms(100);

	memset(str, 0x0, sizeof(str));
//	sprintf(str, "iperf -s -u -i 1");
	sprintf(str, "iperf -s -i 1");
	A("iperf %s\r\n", str);
	if (str_to_argc_argv(str, &argc, &argv) == -1) {
	   A("Failed to convert string to argc and argv\n");
//	   return 0;
	}
	iperf_run(argc, argv, NULL);
	nrc_mem_free(argv[0]);
	nrc_mem_free(argv);

	_delay_ms(1000);

	memset(str, 0x0, sizeof(str));
	sprintf(str, "iperf -s -u -i 1");
//	sprintf(str, "iperf -s -i 1");
	A("iperf %s\r\n", str);
	if (str_to_argc_argv(str, &argc, &argv) == -1) {
	   A("Failed to convert string to argc and argv\n");
//	   return 0;
	}
	iperf_run(argc, argv, NULL);
	nrc_mem_free(argv[0]);
	nrc_mem_free(argv);

	_delay_ms(1000);
}
