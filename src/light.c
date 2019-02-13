#include "light.h"

#include "util/alloc.h"
#include "util/print.h"

#define MAX_LIGHTS 10

static uint32_t numLights = 0;
static GLint locationNumLights;
static GLint locationLightsPosition[MAX_LIGHTS], locationLightsAmbient[MAX_LIGHTS],
    locationLightsDiffuse[MAX_LIGHTS], locationLightsSpecular[MAX_LIGHTS],
    locationLightsLinearAttenuation[MAX_LIGHTS], locationLightsQuadraticAttenuation[MAX_LIGHTS];

// TODO: Look into using UBOs for lights

void setupLight(GLuint program) {
    locationNumLights = glGetUniformLocation(program, "numLights");

    char strPosition[] = "lights[0].position";
    char strAmbient[] = "lights[0].ambient";
    char strDiffuse[] = "lights[0].diffuse";
    char strSpecular[] = "lights[0].specular";
    char strLinearAttenuation[] = "lights[0].linearAttenuation";
    char strQuadraticAttenuation[] = "lights[0].quadraticAttenuation";

    for (uint32_t i = 0; i < MAX_LIGHTS; i++) {
        strPosition[7] = strAmbient[7] = strDiffuse[7] = strSpecular[7] =
            strLinearAttenuation[7] = strQuadraticAttenuation[7] = '0' + i;

        locationLightsPosition[i] = glGetUniformLocation(program, strPosition);
        locationLightsAmbient[i] = glGetUniformLocation(program, strAmbient);
        locationLightsDiffuse[i] = glGetUniformLocation(program, strDiffuse);
        locationLightsSpecular[i] = glGetUniformLocation(program, strSpecular);
        locationLightsLinearAttenuation[i] = glGetUniformLocation(program, strLinearAttenuation);
        locationLightsQuadraticAttenuation[i] = glGetUniformLocation(program, strQuadraticAttenuation);
    }
}

light *newLight() {
    light *li = safe_calloc(1, sizeof(*li));
    return li;
}

void freeLight(light *li) {
    safe_free(li);
}

void addLight(light *li) {
    if (numLights >= MAX_LIGHTS) {
        WARN("Maximum number of lights reached; ignoring additional light");
        return;
    }

    glUniform3fv(locationLightsPosition[numLights], 1, li->position);
    glUniform3fv(locationLightsAmbient[numLights], 1, li->ambient);
    glUniform3fv(locationLightsDiffuse[numLights], 1, li->diffuse);
    glUniform3fv(locationLightsSpecular[numLights], 1, li->specular);
    glUniform1f(locationLightsLinearAttenuation[numLights], li->linearAttenuation);
    glUniform1f(locationLightsQuadraticAttenuation[numLights], li->quadraticAttenuation);

    numLights++;
    glUniform1ui(locationNumLights, numLights);
}

void resetLights() {
    numLights = 0;
    glUniform1ui(locationNumLights, numLights);
}
