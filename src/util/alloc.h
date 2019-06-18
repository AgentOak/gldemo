#ifndef UTIL_ALLOC_H
#define UTIL_ALLOC_H

#include "../master.h"

#include "print.h"

#include <stdlib.h>

ATTR_ALLOC static inline void *safe_malloc(size_t length) {
    void *ptr = malloc(length);

    if (!ptr) {
        FAIL("malloc of %lu bytes failed", length);
    }

    return ptr;
}

static inline void *safe_realloc(void *ptr, size_t length) {
    void *newptr = realloc(ptr, length);

    if (!newptr) {
        FAIL("realloc %p of %lu bytes failed", ptr, length);
    }

    return newptr;
}

ATTR_ALLOC static inline void *safe_calloc(size_t num, size_t length) {
    void *ptr = calloc(num, length);

    if (!ptr) {
        FAIL("calloc of %lux%lu bytes failed", num, length);
    }

    return ptr;
}

static inline void safe_free(void *ptr) {
    if (!ptr) {
        WARN("freeing null pointer");
    }

    free(ptr);
}

#endif /* UTIL_ALLOC_H */
