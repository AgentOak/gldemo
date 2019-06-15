#ifndef UTIL_PRINT_H
#define UTIL_PRINT_H

#include "../master.h"

#include <stdlib.h>
#include <stdio.h>

// TODO: Change into functions and move to print.c?

/*
 * Print macros
 */
#define NOTICE(...) \
    if (verbose) {\
        printf("[NOTICE] ");\
        printf(__VA_ARGS__);\
        printf("\n");\
    }

#define INFO(...) \
    printf("[ INFO ] ");\
    printf(__VA_ARGS__);\
    printf("\n");

#define WARN(...) \
    fprintf(stderr, "[ WARN ] ");\
    fprintf(stderr, __VA_ARGS__);\
    fprintf(stderr, "\n");

#define ERROR(...) \
    fprintf(stderr, "[ ERROR] ");\
    fprintf(stderr, __VA_ARGS__);\
    fprintf(stderr, "\n");

#define FAIL(...) \
    ERROR(__VA_ARGS__);\
    exit(EXIT_FAILURE);

#endif /* UTIL_PRINT_H */
