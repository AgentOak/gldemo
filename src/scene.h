#ifndef SCENE_H
#define SCENE_H

void setup(int argc, char *argv[]);
void onViewport(int width, int height);
void tick(double delta);
void render(double time);
void onKey(int key, int action, int mods);

#endif /* SCENE_H */
