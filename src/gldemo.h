#ifndef GLDEMO_H
#define GLDEMO_H

#include "util.h"

typedef struct {
    int swapInterval;

    int sceneArgc;
    string *sceneArgv;
} gldemo_options;

void gldemo(gldemo_options *opts);

#endif /* GLDEMO_H */
