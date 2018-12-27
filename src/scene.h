#ifndef SCENE_H
#define SCENE_H

#include "master.h"

void setup(uint32_t argc, string argv[]);
void onViewport(int width, int height);
void tick(double delta);
void render(double time);
void onKey(int key, int action, int mods);

#endif /* SCENE_H */
