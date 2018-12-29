#ifndef RENDERER_H
#define RENDERER_H

#include "master.h"

void setupRenderer(uint32_t argc, char *argv[]);
void onViewport(int width, int height);
void render(double time);

#endif /* RENDERER_H */
