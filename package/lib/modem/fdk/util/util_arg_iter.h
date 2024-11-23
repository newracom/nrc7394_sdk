#if !defined(UTIL_ARG_ITER_H)
#define UTIL_ARG_ITER_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
	int    argi;
	int    argc;
	char **argv;
} arg_iterator_t;

void  arg_iterator_initialize(arg_iterator_t *iter, int argi, int argc, char **argv);
char *arg_iterator_next(arg_iterator_t *iter);
bool  arg_iterator_read_int32s(arg_iterator_t *iter, int n, int32_t *buf);

#endif
