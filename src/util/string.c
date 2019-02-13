#include "string.h"

#include "print.h"

#include <stdarg.h>
#include <string.h>

string wrapString(const char *str) {
    size_t length = 0;
    if (str) {
        length = strlen(str);
    }

    return (string) { .len = length, .str = str };
}

string copyString(size_t length, const char *str) {
    char *buf = NULL;

    if (!str) {
        length = 0;
    } else {
        buf = (char *) safe_malloc(length + 1);
        memcpy(buf, str, length);
        buf[length] = '\0';
    }

    return (string) { .len = length, .str = buf };
}

string printfString(const char *format, ...) {
    va_list args, argsCopy;
    va_start(args, format);
    va_copy(argsCopy, args);

    int length = vsnprintf(NULL, 0, format, args);
    va_end(args);
    if (length < 0) {
        FAIL("vsnprintf failed (length detection)");
    }

    char *buffer = safe_malloc(length + 1);

    if (vsnprintf(buffer, length, format, argsCopy) < 0) {
        FAIL("vsnprintf failed (printf)");
    }
    va_end(argsCopy);

    return (string) { .len = length, .str = buffer };
}
