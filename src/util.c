#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

string str(char *str) {
    size_t length = 0;
    if (str) {
        length = strlen(str);
    }

    return (string) { .len = length, .str = str };
}

string readFile(char *fileName) {
    struct stat st;
    if (stat(fileName, &st)) {
        return NULLSTR;
    }
    int length = st.st_size;

    char *target = malloc(length + 1);

    if (length > 0) {
        FILE *f = fopen(fileName, "rb");
        if (!f || !fread(target, length, 1, f)) {
            return NULLSTR;
        }
        fclose(f);
    }

    target[length] = '\0';

    return (string) { .len = length, .str = target };
}
