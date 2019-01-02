#ifndef MODEL_H
#define MODEL_H

#include "master.h"
#include "util.h"

#include <glad/glad.h>
#include <linmath.h>

typedef struct vertex_data {
    float x, y, z;
    float r, g, b;
    float nX, nY, nZ;
} vertex;

typedef struct material_data {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float shininess;
} material;

typedef struct model_data {
    uint32_t vertexCount;
    material mat;
    vertex *vertices;
} model;

typedef struct vbo_data {
    GLsizei vertexCount;
    GLuint bufferName;
    material mat;
} vbo;

void setupModel(GLuint program);
model *loadModel(string fileName);
vbo *uploadModel(model *mod);
void freeModel(model *mod);

void setVBO(vbo *object);
void drawVBO();
void resetVBO();
// TODO: Unload VBO

#endif /* MODEL_H */
