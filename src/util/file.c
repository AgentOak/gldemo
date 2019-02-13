#include "file.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

string readFile(string fileName) {
    struct stat st;
    if (stat(fileName.str, &st)) {
        FAIL("Could not stat file '%s'", fileName.str);
    }
    off_t length = st.st_size;

    char *buffer = safe_malloc(length + 1);

    if (length > 0) {
        FILE *f = fopen(fileName.str , "r");
        if (!f) {
            FAIL("Could not open file '%s'", fileName.str);
        }

        if (!fread(buffer, length, 1, f)) {
            FAIL("Could not read from file '%s'", fileName.str);
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
