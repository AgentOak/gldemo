#ifndef MASTER_H
#define MASTER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#ifndef NDEBUG
    #include <assert.h>
#else
    #define assert(ignore) ((void) 0)
#endif

#define GLDEMO_VERSION "0.1"
#define GLDEMO_NAME "GLDemo v" GLDEMO_VERSION

typedef struct {
    bool verbose;
    bool debug;

    uint16_t swapInterval;
    uint16_t frameLimit;

    uint16_t outputWidth;
    uint16_t outputHeight;

    uint32_t argc;
    char **argv;
} app_options;

extern const app_options *opts;

/*
 * Print macros
 */
#define NOTICE(...) \
    if (opts->verbose) {\
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

#if __has_attribute(packed)
    #define PACKED __attribute__((packed))
#else
    #define PACKED
#endif

/*
 * Mathematics
 */
#define PI 3.14159265358979323846
#define DEG2RAD(degrees) ((PI / 180.0) * (degrees))
#define RAD2DEG(radians) ((180.0 / PI) * (radians))

static inline double clamp(double val, double min, double max) {
    return fmax(min, fmin(max, val));
}

#endif /* MASTER_H */
