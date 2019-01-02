#include "renderer.h"

#include "util.h"
#include "input.h"
#include "model.h"
#include "light.h"

#include <glad/glad.h>
#include <linmath.h>

GLuint programA;
vbo *cube;
GLint locationModel, locationView, locationProjection, locationCameraPosition, locationTime;

static mat4x4 identity = {
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f }
};

static GLuint makeShader(GLenum shaderType, string fileName) {
    NOTICE("Compiling shader '%s'", fileName.str);

    string shaderSource = readFile(fileName);
    if (!shaderSource.str) {
        FAIL("Can't read '%s'", fileName.str);
    }

    GLuint shader = glCreateShader(shaderType);
    const int length = (int) shaderSource.len;
    glShaderSource(shader, 1, &shaderSource.str, &length);
    glCompileShader(shader);

    FREESTR(shaderSource);

    GLint compileStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
    if (!compileStatus) {
        FAIL("Shader '%s' did not compile", fileName.str);
    }

    return shader;
}

static void makeProgram(GLuint program) {
    NOTICE("Linking program");

    glLinkProgram(program);

    GLint linkStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    if (!linkStatus) {
        FAIL("Program did not link");
    }
}

void setupRenderer(uint32_t argc, char *argv[]) {
    // Basic options
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Don't really know what this is needed for yet
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    if (argc < 1) {
        FAIL("No shader name supplied");
    }
    string vertexFileName = strprintf("shader/%s.vert", argv[0]);
    string fragmentFileName = strprintf("shader/%s.frag", argv[0]);

    programA = glCreateProgram();
    glAttachShader(programA, makeShader(GL_VERTEX_SHADER, vertexFileName));
    glAttachShader(programA, makeShader(GL_FRAGMENT_SHADER, fragmentFileName));
    makeProgram(programA);

    FREESTR(fragmentFileName);
    FREESTR(vertexFileName);

    // Get uniform locations in our program, since we don't use GL_ARB_explicit_uniform_location
    locationModel = glGetUniformLocation(programA, "model");
    locationView = glGetUniformLocation(programA, "view");
    locationProjection = glGetUniformLocation(programA, "projection");
    locationCameraPosition = glGetUniformLocation(programA, "cameraPosition");
    locationTime = glGetUniformLocation(programA, "time");

    setupModel(programA);
    setupLight(programA);

    glUseProgram(programA);

    // Upload and describe data
    model *cubeModel = loadModel(STR("model/cube.model"));
    cube = uploadModel(cubeModel);
    freeModel(cubeModel);

    // Light source
    light *li = newLight();
    li->position[0] = 0.0; li->position[1] = 0.0; li->position[2] = 0.0;
    li->ambient[0]  = 1.0; li->ambient[1]  = 1.0; li->ambient[2]  = 1.0;
    li->diffuse[0]  = 1.0; li->diffuse[1]  = 1.0; li->diffuse[2]  = 1.0;
    li->specular[0] = 1.0; li->specular[1] = 1.0; li->specular[2] = 1.0;
    addLight(li);
    freeLight(li);

    li = newLight();
    li->position[0] = 0.0; li->position[1] = 7.0; li->position[2] = 0.0;
    li->ambient[0]  = 1.0; li->ambient[1]  = 1.0; li->ambient[2]  = 1.0;
    li->diffuse[0]  = 1.0; li->diffuse[1]  = 1.0; li->diffuse[2]  = 1.0;
    li->specular[0] = 1.0; li->specular[1] = 1.0; li->specular[2] = 1.0;
    addLight(li);
    freeLight(li);
}

void onViewport(int width, int height) {
    float ratio = width / (float) height;

    // Set up projection matrix
    mat4x4 projection;
    mat4x4_perspective(projection, fieldOfView, ratio, 0.1f, 100.0f);
    glUniformMatrix4fv(locationProjection, 1, GL_FALSE, (const float *) projection);
}

void render(double time) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUniform1f(locationTime, (float) time);

    // Upload view matrix from input
    glUniformMatrix4fv(locationView, 1, GL_FALSE, (const float *) view);
    glUniform3fv(locationCameraPosition, 1, (const float *) cameraPosition);

    // glValidateProgram(programA); ...
    glUseProgram(programA);

    setVBO(cube);

    mat4x4 trans, rotate, scale, temp, model;
    for (int i = 0; i < 8; i++) {
        mat4x4_scale(scale, identity, 0.4 + 0.4 * (cos(i * 3.0) + 1.0));
        scale[3][3] = 1.0;
        mat4x4_translate(trans,
             sin(i / 8.0 * 2.0 * PI) * 4.0,
            -cos(i / 8.0 * 2.0 * PI) * 2.0,
             cos(i / 8.0 * 2.0 * PI) * 6.0);
        mat4x4_rotate_Y(rotate, identity, (time * (i + 1) * 15.0) / 180.0 * PI);
        mat4x4_mul(temp, scale, rotate);
        mat4x4_mul(model, trans, temp);
        glUniformMatrix4fv(locationModel, 1, GL_FALSE, (const float *) model);

        drawVBO();
    }

    resetVBO();
}
