#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>

string strprintf(const char *format, ...) {
    va_list args, argsCopy;
    va_start(args, format);
    va_copy(argsCopy, args);

    int length = vsnprintf(NULL, 0, format, args);
    if (length < 0) {
        return NULLSTR;
    }

    char *buffer = malloc(length + 1);
    if (!buffer) {
        return NULLSTR;
    }
    va_end(args);

    if (vsprintf(buffer, format, argsCopy) < 0) {
        return NULLSTR;
    }
    va_end(argsCopy);

    return (string) { .len = length, .str = buffer };
}

string readFile(string fileName) {
    struct stat st;
    if (stat(fileName.str, &st)) {
        return NULLSTR;
    }
    off_t length = st.st_size;

    char *buffer = malloc(length + 1);
    if (!buffer) {
        return NULLSTR;
    }

    if (length > 0) {
        FILE *f = fopen(fileName.str , "rb");
        if (!f || !fread(buffer, length, 1, f)) {
            free(buffer);
            return NULLSTR;
        }
        fclose(f);
    }

    buffer[length] = '\0';

    return (string) { .len = length, .str = buffer };
}
