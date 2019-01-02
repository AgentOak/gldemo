#ifndef WINDOW_H
#define WINDOW_H

#include "master.h"

typedef struct {
    uint16_t swapInterval;
    uint16_t frameLimit;

    uint32_t argc;
    char **argv;
} app_options;

void window(app_options *opts);

#endif /* WINDOW_H */
