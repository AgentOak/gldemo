#ifndef SCENE_H
#define SCENE_H

extern void setup(int argc, char *argv[]);
extern void onViewport(int width, int height);
extern void tick(double delta);
extern void render(double time);
extern void onKey(int key, int action, int mods);

#endif /* SCENE_H */
