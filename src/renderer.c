#include "renderer.h"

#include "util.h"

#include <glad/glad.h>
#include <linmath.h>
#include <math.h>

typedef struct vertex_data {
    float x, y, z;
    float r, g, b;
} vertex;

#define FIELD_OF_VIEW 65.0

#define LOCATION_VPOSITION 0
#define LOCATION_VCOLOR 1

#define VERTICES_CUBE 36
static const vertex dataCube[VERTICES_CUBE] = {
    // Front
    { -1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f },
    {  1.0f, -1.0f,  1.0f, 0.0f, 1.0f, 0.0f },
    { -1.0f,  1.0f,  1.0f, 0.0f, 0.0f, 1.0f },

    {  1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f },
    {  1.0f, -1.0f,  1.0f, 0.0f, 1.0f, 0.0f },
    { -1.0f,  1.0f,  1.0f, 0.0f, 0.0f, 1.0f },

    // Back
    { -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f },
    {  1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f },
    { -1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 1.0f },

    {  1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f },
    {  1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f },
    { -1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 1.0f },

    // Left
    { -1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f },
    { -1.0f, -1.0f,  1.0f, 0.0f, 1.0f, 0.0f },
    { -1.0f,  1.0f,  1.0f, 0.0f, 0.0f, 1.0f },

    { -1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f },
    { -1.0f, -1.0f,  1.0f, 0.0f, 1.0f, 0.0f },
    { -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f },

    // Right
    {  1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f },
    {  1.0f, -1.0f,  1.0f, 0.0f, 1.0f, 0.0f },
    {  1.0f,  1.0f,  1.0f, 0.0f, 0.0f, 1.0f },

    {  1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f },
    {  1.0f, -1.0f,  1.0f, 0.0f, 1.0f, 0.0f },
    {  1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f },

    // Top
    { -1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f },
    {  1.0f,  1.0f,  1.0f, 0.0f, 1.0f, 0.0f },
    {  1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 1.0f },

    { -1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f },
    { -1.0f,  1.0f, -1.0f, 0.0f, 1.0f, 0.0f },
    {  1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 1.0f },

    // Bottom
    { -1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f },
    {  1.0f, -1.0f,  1.0f, 0.0f, 1.0f, 0.0f },
    {  1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f },

    { -1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f },
    { -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f },
    {  1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f }
};

GLuint programA;
GLuint bufferCube;
GLint locationModel, locationView, locationProjection, locationTime;

static GLuint makeShader(GLenum shaderType, string fileName) {
    DEBUG("Compiling shader '%s'", fileName.str);

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
        //if (!GLAD_GL_VERSION_4_3) {
        //    GLint shaderLogLength;
        //    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &shaderLogLength);
        //
        //    if (shaderLogLength > 0) {
        //        char *shaderLog = malloc(shaderLogLength);
        //        if (!shaderLog) {
        //            FAIL("Couldn't allocate memory for shader info log");
        //        }
        //        glGetShaderInfoLog(shader, shaderLogLength, NULL, shaderLog);
        //
        //        WARN("[GLSL] Shader '%s' log: %s", fileName.str, shaderLog);
        //
        //        free(shaderLog);
        //    }
        //}

        FAIL("Shader '%s' did not compile", fileName.str);
    }

    return shader;
}

static void makeProgram(GLuint program) {
    DEBUG("Linking program");

    glLinkProgram(program);

    GLint linkStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

    if (!linkStatus) {
        //if (!GLAD_GL_VERSION_4_3) {
        //    GLint programLogLength;
        //    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &programLogLength);
        //
        //    if (programLogLength > 0) {
        //        char *programLog = malloc(programLogLength);
        //        if (!programLog) {
        //            FAIL("Couldn't allocate memory for program info log");
        //        }
        //        glGetProgramInfoLog(program, programLogLength, NULL, programLog);
        //
        //        WARN("[GLSL] Program log: %s", programLog);
        //
        //        free(programLog);
        //    }
        //}

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
    locationTime = glGetUniformLocation(programA, "time");

    // Upload and describe data
    glGenBuffers(1, &bufferCube);
    glBindBuffer(GL_ARRAY_BUFFER, bufferCube);
    glBufferData(GL_ARRAY_BUFFER, sizeof(dataCube), dataCube, GL_STATIC_DRAW);

    glEnableVertexAttribArray(LOCATION_VPOSITION);
    glVertexAttribPointer(LOCATION_VPOSITION, 3, GL_FLOAT, GL_FALSE,
                          sizeof(float) * 6, (void*) 0);
    glEnableVertexAttribArray(LOCATION_VCOLOR);
    glVertexAttribPointer(LOCATION_VCOLOR, 3, GL_FLOAT, GL_FALSE,
                          sizeof(float) * 6, (void*) (sizeof(float) * 3));

    glUseProgram(programA);

    // Set up view matrix
    mat4x4 view;
    mat4x4_look_at(view,
        (float[]) { 8.0, 6.0, 0.0 }, // eye
        (float[]) { 0.0, -1.0, 0.0 }, // center
        (float[]) { 0.0, 1.0, 0.0 }); // up
    glUniformMatrix4fv(locationView, 1, GL_FALSE, (const float *) view);
}

void onViewport(int width, int height) {
    float ratio = width / (float) height;

    // Set up projection matrix
    mat4x4 projection;
    mat4x4_perspective(projection, FIELD_OF_VIEW / 180.0 * PI, ratio, 1.0f, 100.0f);
    glUniformMatrix4fv(locationProjection, 1, GL_FALSE, (const float *) projection);
}

void tick(double delta UNUSED) {

}

void drawCube(float x, float y, float z, float yDegrees) {
    glBindBuffer(GL_ARRAY_BUFFER, bufferCube);

    mat4x4 temp, model;
    mat4x4_translate(temp, x, y, z);
    mat4x4_rotate_Y(model, temp, yDegrees / 180.0 * PI);
    glUniformMatrix4fv(locationModel, 1, GL_FALSE, (const float *) model);

    glDrawArrays(GL_TRIANGLES, 0, VERTICES_CUBE);
}

void render(double time) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUniform1f(locationTime, (float) time);

    // glValidateProgram(programA); ...
    glUseProgram(programA);

    for (int i = 0; i < 8; i++) {
        drawCube(sin(i / 8.0 * 2.0 * PI) * 4.0, 0.0, cos(i / 8.0 * 2.0 * PI) * 4.0, time * (i + 1) * 15.0);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
