#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

string str(char *str) {
    return (string) { .len = strlen(str), .str = str };
}

string readFile(char *fileName) {
    FILE *f = fopen(fileName, "rb");
    if (!f) {
        return (string) { .len = 0, .str = NULL };
    }

    struct stat st;
    stat(fileName, &st);

    char *target = malloc(st.st_size + 1);
    if (!fread(target, st.st_size, 1, f)) {
        return (string) { .len = 0, .str = NULL };
    }
    fclose(f);

    target[st.st_size] = '\0';

    return (string) { .len = st.st_size, .str = target };
}
