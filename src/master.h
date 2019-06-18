#ifndef MASTER_H
#define MASTER_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

// TODO: Always include string.h, alloc.h and print.h

#ifndef NDEBUG
    #include <assert.h>
#else
    #define assert(ignore) ((void) 0);
#endif

#define GLDEMO_VERSION "0.1"
#define GLDEMO_NAME "GLDemo v" GLDEMO_VERSION

typedef struct {
    bool debugContext;

    uint16_t swapInterval;
    uint16_t frameLimit;

    uint16_t outputWidth;
    uint16_t outputHeight;

    float mouseSensitivity;

    uint32_t argc;
    char **argv;
} app_options;

extern bool verbose;
extern const app_options *opts;

/*
 * Attributes
 */
#ifndef __has_attribute
    #define __has_attribute(x) 0
#endif

#if __has_attribute(format)
    #define ATTR_FORMAT(m, n) __attribute__((format(printf, (m), (n))))
#else
    #define ATTR_FORMAT(m, n)
#endif

#if __has_attribute(nonnull)
    #define ATTR_NONNULL(...) __attribute__((nonnull(__VA_ARGS__)))
#else
    #define ATTR_NONNULL(...)
#endif

#if __has_attribute(const)
    #define ATTR_SIDEFREE __attribute__((const))
#elif __has_attribute(pure)
    #define ATTR_SIDEFREE __attribute__((pure))
#else
    #define ATTR_SIDEFREE
#endif

#if __has_attribute(unused)
    #define ATTR_UNUSED __attribute__((unused))
#else
    #define ATTR_UNUSED
#endif

#if __has_attribute(packed)
    #define ATTR_PACKED __attribute__((packed))
#else
    #define ATTR_PACKED
#endif

#if __has_attribute(malloc)
    #define ATTR_ALLOC __attribute__((malloc))
#else
    #define ATTR_ALLOC
#endif

#endif /* MASTER_H */
