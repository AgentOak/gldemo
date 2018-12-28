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

GLuint program;
GLint locationModelViewProjection, locationTime;
mat4x4 modelViewProjection;

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
    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    if (argc < 1) {
        FAIL("No shader name supplied");
    }

    string vertexFileName = strprintf("shader/%s.vert", argv[0]);
    string fragmentFileName = strprintf("shader/%s.frag", argv[0]);

    program = glCreateProgram();
    glAttachShader(program, makeShader(GL_VERTEX_SHADER, vertexFileName));
    glAttachShader(program, makeShader(GL_FRAGMENT_SHADER, fragmentFileName));
    glLinkProgram(program);

    FREESTR(fragmentFileName);
    FREESTR(vertexFileName);

    locationModelViewProjection = glGetUniformLocation(program, "modelViewProjection");
    locationTime = glGetUniformLocation(program, "time");

    GLint locationVPosition = glGetAttribLocation(program, "vPosition");
    GLint locationVColor = glGetAttribLocation(program, "vColor");

    glEnableVertexAttribArray(locationVPosition);
    glVertexAttribPointer(locationVPosition, 3, GL_FLOAT, GL_FALSE,
                          sizeof(float) * 6, (void*) 0);
    glEnableVertexAttribArray(locationVColor);
    glVertexAttribPointer(locationVColor, 3, GL_FLOAT, GL_FALSE,
                          sizeof(float) * 6, (void*) (sizeof(float) * 3));

    glUseProgram(program);
}

void onViewport(int width, int height) {
    float ratio = width / (float) height;

    mat4x4_perspective(modelViewProjection, 60.0 / 180.0 * PI, ratio, 0.0f, -100.0f);
    glUniformMatrix4fv(locationModelViewProjection, 1, GL_FALSE, (const float *) modelViewProjection);
}

void tick(double delta UNUSED) {

}

void render(double time) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUniform1f(locationTime, (float) time);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
