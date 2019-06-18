#include "shader.h"

#include "../util/file.h"
#include "../util/print.h"

GLuint makeShader(GLenum shaderType, string fileName) {
    INFO("Compiling shader '%s'", fileName.str);

    string shaderSource = readFile(fileName);
    if (!shaderSource.str) {
        FAIL("Can't read '%s'", fileName.str);
    }

    GLuint shader = glCreateShader(shaderType);
    const int length = (int) shaderSource.len;
    glShaderSource(shader, 1, &shaderSource.str, &length);
    glCompileShader(shader);

    FREESTRING(shaderSource);

    GLint compileStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
    if (!compileStatus) {
        FAIL("Shader '%s' did not compile", fileName.str);
    }

    return shader;
}

void makeProgram(GLuint program) {
    NOTICE("Linking program");

    glLinkProgram(program);

    GLint linkStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    if (!linkStatus) {
        FAIL("Program did not link");
    }
}

GLint getUniformLocation(GLuint program, const char *nameFormat, ...) {
    va_list args;
    va_start(args, nameFormat);
    string name = vprintfString(nameFormat, args);
    va_end(args);

    GLint location = glGetUniformLocation(program, name.str);

    if (location < 0) {
        WARN("Can't find uniform location for '%s'", name.str);
    }

    FREESTRING(name);

    return location;
}
