#include "util.h"

#include <stdio.h>
#include <stdlib.h>

char *readFile(char *fileName) {
    FILE *f = fopen(fileName, "rb");
    if (!f) {
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    char *target = malloc(length + 1);
    if (!fread(target, length, 1, f)) {
        return NULL;
    }
    fclose(f);

    target[length] = '\0';

    return target;
}
