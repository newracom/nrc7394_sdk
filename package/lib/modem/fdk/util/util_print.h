#if !defined(UTIL_PRINT_H)
#define UTIL_PRINT_H

#include <stdio.h>

#if defined(UCODE)
    #define SPACE_INDENT(f,x)
#else
    #define SPACE_INDENT(f,x) util_print_add_space_indentation(f,x)
#endif
#define IS_PRINTABLE_ASCII(c) (0x20 <= c && c <= 0x7E)
#define IS_WHITESPACE(c) (c == '\t' || c == ' ' || c == '\n')

typedef void (*print_func)(const char *f, ...);

#if defined(UCODE)
    #define util_print_add_space_indentation(a,b)
    #define util_print_hexdump(a,b,c,d)
#else
    void util_print_add_space_indentation(print_func func, int level);
    void util_print_hexdump(print_func func, void *addr, uint32_t length, uint32_t byte_per_line);
#endif

#endif
