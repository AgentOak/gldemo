#ifndef GLDEMO_H
#define GLDEMO_H

#include "master.h"

typedef struct {
    uint16_t swapInterval;
    uint16_t frameLimit;
    // TODO: Add fullscreen/monitor mode options

    uint32_t argc;
    char **argv;
} gldemo_options;

void gldemo(gldemo_options *opts);

#endif /* GLDEMO_H */
