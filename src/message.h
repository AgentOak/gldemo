#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define GLDEMO_VERSION "0.1"
#define GLDEMO_NAME "GLDemo v" GLDEMO_VERSION

extern bool debug;

#define INFO(...) \
    printf(__VA_ARGS__);\
    printf("\n")

#define DEBUG(...) \
    if (debug) {\
        printf("[DEBUG %s@%s:%d] ", __func__, __FILE__, __LINE__);\
        printf(__VA_ARGS__);\
        printf("\n");\
    }

#define WARN(...) \
    fprintf(stderr, "[WARN] ");\
    fprintf(stderr, __VA_ARGS__);\
    fprintf(stderr, "\n")

#define ERROR(...) \
    fprintf(stderr, "[ERROR] ");\
    fprintf(stderr, __VA_ARGS__);\
    fprintf(stderr, "\n");\

#define FAIL(...) \
    ERROR(__VA_ARGS__);\
    exit(EXIT_FAILURE)

#endif /* MESSAGE_H */
