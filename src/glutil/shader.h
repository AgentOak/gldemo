#include "../master.h"

#include "../util/string.h"

#include <glad/glad.h>

GLuint makeShader(GLenum shaderType, string fileName);
void makeProgram(GLuint program);
GLint getUniformLocation(GLuint program, const char *nameFormat, ...) ATTR_FORMAT(2, 3) ATTR_NONNULL(2);
