#include "light.h"

#include "util/alloc.h"
#include "util/print.h"
#include "glutil/shader.h"

#define MAX_LIGHTS 10

static uint32_t numLights = 0;
static GLint locationNumPointLights, locationAmbientLight;

// TODO: Look into using UBOs for lights

void setupLight(GLuint program) {
    locationNumPointLights = getUniformLocation(program, "numPointLights");
    locationAmbientLight = getUniformLocation(program, "ambientLight");
}

void setAmbientLight(vec3 intensity) {
    glUniform3fv(locationAmbientLight, 1, intensity);
}

light *newLight() {
    light *li = safe_calloc(1, sizeof(*li));
    return li;
}

void freeLight(light *li) {
    safe_free(li);
}

void addLight(GLuint program, light *li) {
    if (numLights >= MAX_LIGHTS) {
        WARN("Maximum number of lights reached; ignoring additional light");
        return;
    }

    glUniform3fv(getUniformLocation(program, "pointlights[%u].position", numLights), 1, li->position);
    glUniform3fv(getUniformLocation(program, "pointlights[%u].attenuation", numLights), 1, li->attenuation);
    glUniform3fv(getUniformLocation(program, "pointlights[%u].intensity", numLights), 1, li->intensity);

    numLights++;
    glUniform1ui(locationNumPointLights, numLights);
}

void resetLights() {
    numLights = 0;
    glUniform1ui(locationNumPointLights, numLights);
}
