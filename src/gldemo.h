#ifndef GLDEMO_H
#define GLDEMO_H

#include "master.h"

typedef struct {
    uint8_t swapInterval;
    uint16_t frameLimit;

    uint32_t sceneArgc;
    string *sceneArgv;
} gldemo_options;

void gldemo(gldemo_options *opts);

#endif /* GLDEMO_H */
