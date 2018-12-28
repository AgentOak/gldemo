#ifndef MASTER_H
#define MASTER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define GLDEMO_VERSION "0.1"
#define GLDEMO_NAME "GLDemo v" GLDEMO_VERSION

extern bool debug;

/*
 * Print macros
 */
#define INFO(...) \
    printf(__VA_ARGS__);\
    printf("\n");

#define DEBUG(...) \
    if (debug) {\
        printf("[DEBUG] ");\
        printf(__VA_ARGS__);\
        printf("\n");\
    }

#define WARN(...) \
    fprintf(stderr, "[WARN] ");\
    fprintf(stderr, __VA_ARGS__);\
    fprintf(stderr, "\n");

#define ERROR(...) \
    fprintf(stderr, "[ERROR] ");\
    fprintf(stderr, __VA_ARGS__);\
    fprintf(stderr, "\n");

#define FAIL(...) \
    ERROR(__VA_ARGS__);\
    exit(EXIT_FAILURE);

/*
 * Attributes
 */
#ifndef __has_attribute
    #define __has_attribute(x) 0
#endif

#if __has_attribute(format)
    #define FORMAT(m, n) __attribute__((format(printf, (m), (n))))
#else
    #define FORMAT(m, n)
#endif

#if __has_attribute(nonnull)
    #define NONNULL(...) __attribute__((nonnull(__VA_ARGS__)))
#else
    #define NONNULL(...)
#endif

#if __has_attribute(const)
    #define SIDEFREE __attribute__((const))
#elif __has_attribute(pure)
    #define SIDEFREE __attribute__((pure))
#else
    #define SIDEFREE
#endif

#if __has_attribute(unused)
    #define UNUSED __attribute__((unused))
#else
    #define UNUSED
#endif

/*
 * Constants
 */
#define PI 3.14159265358979323846

#endif /* MASTER_H */
