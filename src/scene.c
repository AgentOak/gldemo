#include "scene.h"

#include "message.h"
#include "util.h"

#include <glad/glad.h>
#include <linmath.h>

#include <math.h>

void setup(int argc, char* argv[]) {
    char* vsh = readFile("shader/phong.vert");
    if (vsh) {
        DEBUG(vsh);
    }
    
    char* fsh = readFile("shader/phong.frag");
    if (fsh) {
        DEBUG(fsh);
    }
}

void onViewport(int width, int height) {
    
}

void tick(double delta) {

}

void render(double time) {
    glClearColor(0.0f, 0.5f, (float) sin(time), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); 
}

void onKey(int key, int action, int mods) {

}
