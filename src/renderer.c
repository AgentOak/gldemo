#include "renderer.h"

#include "util.h"

#include <glad/glad.h>
#include <linmath.h>
#include <math.h>

typedef struct vertex_data {
    float x, y, z;
    float r, g, b;
} vertex;

static const vertex vertices[3] = {
    { -0.6f, -0.4f, -1.0f, 1.0f, 0.0f, 0.0f },
    {  0.6f, -0.4f, -1.0f, 0.0f, 1.0f, 0.0f },
    {   0.f,  0.6f, -1.0f, 0.0f, 0.0f, 1.0f }
};

static GLuint makeShader(GLenum shaderType, string fileName) {
    string shaderSource = readFile(fileName);
    if (!shaderSource.str) {
        FAIL("Can't read '%s'", fileName.str);
    }

    GLuint shader = glCreateShader(shaderType);
    const int length = (int) shaderSource.len;
    glShaderSource(shader, 1, &shaderSource.str, &length);
    glCompileShader(shader);

    FREESTR(shaderSource);
    return shader;
}

void setupRenderer(uint32_t argc, char *argv[]) {
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    if (argc < 1) {
        FAIL("No shader name supplied");
    }

    string vertexFileName = strprintf("shader/%s.vert", argv[0]);
    string fragmentFileName = strprintf("shader/%s.frag", argv[0]);

    GLuint program = glCreateProgram();
    glAttachShader(program, makeShader(GL_VERTEX_SHADER, vertexFileName));
    glAttachShader(program, makeShader(GL_FRAGMENT_SHADER, fragmentFileName));
    glLinkProgram(program);

    FREESTR(vertexFileName);
    FREESTR(fragmentFileName);
}

void onViewport(int width UNUSED, int height UNUSED) {
    
}

void tick(double delta UNUSED) {

}

void render(double time) {
    glClearColor(0.0f, 0.5f, (float) sin(time) * 0.5f + 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); 
}
