#include "util.h"

#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

// TODO: Proper error handling

string strprintf(const char *format, ...) {
    va_list args, argsCopy;
    va_start(args, format);
    va_copy(argsCopy, args);

    int length = vsnprintf(NULL, 0, format, args);
    va_end(args);
    if (length < 0) {
        return NULLSTR;
    }

    char *buffer = malloc(length + 1);
    if (!buffer) {
        return NULLSTR;
    }

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
        FILE *f = fopen(fileName.str , "r");
        if (!f || !fread(buffer, length, 1, f)) {
            free(buffer);
            return NULLSTR;
        }
        fclose(f);
    }

    buffer[length] = '\0';

    return (string) { .len = length, .str = buffer };
}

mapping mapFile(string fileName) {
    struct stat st;
    if (stat(fileName.str, &st)) {
        FAIL("Could not stat file '%s'", fileName.str);
    }
    off_t length = st.st_size;

    int fd = open(fileName.str, O_RDONLY);
    if (fd < 0) {
        FAIL("Could not open file '%s'", fileName.str);
    }

    void *addr = mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0);

    close(fd);

    return (mapping) { .len = length, .addr = addr };
}

void unmapFile(mapping map) {
    munmap((void *) map.addr, map.len);
}
