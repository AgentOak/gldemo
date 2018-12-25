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
    FILE *f = fopen(fileName, "rb");
    if (!f) {
        return NULLSTR;
    }

    struct stat st;
    stat(fileName, &st);

    char *target = malloc(st.st_size + 1);
    if (!fread(target, st.st_size, 1, f)) {
        return NULLSTR;
    }
    fclose(f);

    target[st.st_size] = '\0';

    return (string) { .len = st.st_size, .str = target };
}
