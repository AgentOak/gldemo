#include "scene.h"

#include "message.h"
#include "util.h"

#include <glad/glad.h>
#include <linmath.h>

#include <math.h>

void setup(int argc, char *argv[]) {
    string vsh = readFile("shader/phong.vert");
    if (vsh.str) {
        DEBUG(vsh.str);
    }
    
    string fsh = readFile("shader/phong.frag");
    if (fsh.str) {
        DEBUG(fsh.str);
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
