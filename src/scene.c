#include "scene.h"

#include "message.h"
#include "util.h"

#include <glad/glad.h>
#include <linmath.h>

#include <math.h>

void setup(int argc, string argv[]) {
    for (int i = 0; i < argc; i++) {
        string fileName = strprintf("shader/%s", argv[i].str);
        string sh = readFile(fileName);
        if (sh.str) {
            DEBUG(sh.str);
        }
        FREESTR(sh);
        FREESTR(fileName);
    }
}

void onViewport(int width, int height) {
    
}

void tick(double delta) {

}

void render(double time) {
    glClearColor(0.0f, 0.5f, (float) sin(time) * 0.5f + 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); 
}

void onKey(int key, int action, int mods) {

}
