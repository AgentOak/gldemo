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
        printf("[DEBUG %s@%s:%d] ", __func__, __FILE__, __LINE__);\
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
 * String
 */

/**
 * Poor man's immutable string library. See util.h for utility string functions.
 *
 * Character arrays pointed to by str are still NULL-terminated, allowing easy use in standard library.
 *
 * Example usage:
 * @code
 * string fileName = strprintf("foo/%s", argv[0]);
 * string contents = readFile(fileName);
 * if (contents.str) {
 *     printf(contents.str);
 * }
 * FREESTR(contents);
 * FREESTR(fileName);
 * @endcode
 *
 * The @c STR macro can be used to create a string at compile-time,
 * the @c str function to wrap a @c char* into a string at runtime.
 *
 * A null string is represented by @c (.str == NULL), in which case the length has no meaning (but should be @c 0).
 * The @c NULLSTR macro can be used to obtain such a string.
 */
typedef struct immstring {
    const size_t len;
    const char *const str;
} string;

#define STR(x) ((string) { .len = sizeof(x) - 1, .str = (x) })
#define NULLSTR ((string) { .len = 0, .str = NULL })
#define FREESTR(x) free((void*) (x).str);

/**
 * @brief Construct a string from the given NULL-terminated character array.
 *
 * No copy of character data is performed. Characters should not be modified afterwards.
 * If a null pointer is passed, the @c NULLSTR will be returned.
 */
static inline string str(const char *str) {
    size_t length = 0;
    if (str) {
        length = strlen(str);
    }

    return (string) { .len = length, .str = str };
}

#endif /* MASTER_H */
