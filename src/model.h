#ifndef MODEL_H
#define MODEL_H

#include "master.h"
#include "util/string.h"

#include <glad/glad.h>
#include <linmath.h>
#include <tinyobj_loader_c.h>

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
vbo *uploadModel(model *mod) ATTR_NONNULL();
void freeModel(model *mod) ATTR_NONNULL();

void setVBO(vbo *object) ATTR_NONNULL();
void drawVBO(void);
void resetVBO(void);
void freeVBO(vbo *object) ATTR_NONNULL();

#endif /* MODEL_H */
