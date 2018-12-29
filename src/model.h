#ifndef MODEL_H
#define MODEL_H

#include "master.h"
#include "util.h"

#include <GLAD/glad.h>
#include <linmath.h>

typedef struct vertex_data {
    float x, y, z;
    float r, g, b;
} vertex;

typedef struct model_data {
    uint32_t vertexCount;
    vertex *vertices;
} model;

typedef struct vbo_data {
    GLsizei vertexCount;
    GLuint bufferName;
} vbo;

model *loadModel(string fileName);
vbo *uploadModel(model *mod);
void freeModel(model *mod);
void drawVBO(vbo *object);

#endif /* MODEL_H */
