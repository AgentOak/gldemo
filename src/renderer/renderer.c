#include "renderer.h"

#include "../util/math.h"
#include "../util/print.h"
#include "../input.h"
#include "shader.h"
#include "model.h"
#include "light.h"

#include <glad/glad.h>
#include <linmath.h>

static GLuint programA;
static vbo *cube;
static GLint locationModel, locationNormalMatrix, locationView, locationProjection,
    locationViewProjection, locationTime, locationCameraPosition;
static mat4x4 projection;

static mat4x4 identity = {
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f }
};

void setupRenderer() {
    // Basic options
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_FRONT); // TODO: Fix model in model.c to not mix CCW and CW

    // Don't really know what this is needed for yet
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    programA = glCreateProgram();
    glAttachShader(programA, makeShader(GL_VERTEX_SHADER, STRING("shader/project.vert")));
    glAttachShader(programA, makeShader(GL_FRAGMENT_SHADER, STRING("shader/phong.frag")));
    makeProgram(programA);

    // Get uniform locations in our program, since we don't use GL_ARB_explicit_uniform_location
    locationModel = getUniformLocation(programA, "model");
    locationNormalMatrix = getUniformLocation(programA, "normalMatrix");
    locationView = getUniformLocation(programA, "view");
    locationProjection = getUniformLocation(programA, "projection");
    locationViewProjection = getUniformLocation(programA, "viewProjection");
    locationTime = getUniformLocation(programA, "time");
    locationCameraPosition = getUniformLocation(programA, "cameraPosition");

    setupModel(programA);
    setupLight(programA);

    glUseProgram(programA);

    // Upload and describe data
    model *cubeModel = loadModel(STRING("model/cube.model"));
    cube = uploadModel(cubeModel);
    freeModel(cubeModel);

    // Light source
    vec3 ambient = { 0.3, 0.3, 0.3 };
    setAmbientLight(ambient);

    light *li = newLight();
    li->position[0]    = 0.0; li->position[1]    = 0.0;  li->position[2]    = 0.0;
    li->intensity[0]   = 1.0; li->intensity[1]   = 1.0;  li->intensity[2]   = 1.0;
    li->attenuation[0] = 0.0; li->attenuation[1] = 0.015; li->attenuation[2] = 0.015;
    addLight(programA, li);

    li->position[0]    = 0.0; li->position[1]    = 7.0;  li->position[2]    = 0.0;
    li->intensity[0]   = 0.1; li->intensity[1]   = 0.1;  li->intensity[2]   = 0.9;
    li->attenuation[0] = 0.1; li->attenuation[1] = 0.025; li->attenuation[2] = 0.020;
    addLight(programA, li);
    freeLight(li);
}

void onViewport(int width, int height) {
    float ratio = width / (float) height;

    // Set up projection matrix
    mat4x4_perspective(projection, fieldOfView, ratio, 0.1f, 100.0f);
    glUniformMatrix4fv(locationProjection, 1, GL_FALSE, (const float *) projection);
}

void render(double time) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUniform1f(locationTime, (float) time);

    // Upload view matrix from input
    glUniformMatrix4fv(locationView, 1, GL_FALSE, (const float *) view);
    mat4x4 viewProjection;
    mat4x4_mul(viewProjection, projection, view);
    glUniformMatrix4fv(locationViewProjection, 1, GL_FALSE, (const float *) viewProjection);
    glUniform3fv(locationCameraPosition, 1, (const float *) cameraPosition);

    // glValidateProgram(programA); ...
    glUseProgram(programA);

    setVBO(cube);

    mat4x4 trans, rotate, scale, temp, modelMatrix, normalMatrix;
    for (int i = 0; i < 8; i++) {
        mat4x4_scale(scale, identity, 0.4 + 0.4 * (cos(i * 3.0) + 1.0));
        scale[3][3] = 1.0;
        mat4x4_translate(trans,
             sin(i / 8.0 * 2.0 * PI) * 4.0,
            -cos(i / 8.0 * 2.0 * PI) * 2.0,
             cos(i / 8.0 * 2.0 * PI) * 6.0);
        mat4x4_rotate_Y(rotate, identity, (time * (i + 1) * 15.0) / 180.0 * PI);
        mat4x4_mul(temp, scale, rotate);
        mat4x4_mul(modelMatrix, trans, temp);
        glUniformMatrix4fv(locationModel, 1, GL_FALSE, (const float *) modelMatrix);
        mat4x4_invert(temp, modelMatrix);
        mat4x4_transpose(normalMatrix, temp);

        glUniformMatrix4fv(locationNormalMatrix, 1, GL_FALSE, (const float *) normalMatrix);

        drawVBO();
    }

    resetVBO();
}
