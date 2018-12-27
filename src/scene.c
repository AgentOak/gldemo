#include "scene.h"

#include "util.h"

#include <glad/glad.h>
#include <linmath.h>
#include <math.h>

void setup(uint32_t argc, string argv[]) {
    for (uint32_t i = 0; i < argc; i++) {
        string fileName = strprintf("shader/%s", argv[i].str);
        string sh = readFile(fileName);
        if (sh.str) {
            DEBUG("%s", sh.str);
        }
        FREESTR(sh);
        FREESTR(fileName);
    }
}

void onViewport(int width UNUSED, int height UNUSED) {
    
}

void tick(double delta UNUSED) {

}

void render(double time) {
    glClearColor(0.0f, 0.5f, (float) sin(time) * 0.5f + 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); 
}

void onKey(int key UNUSED, int action UNUSED, int mods UNUSED) {

}
