#include "model.h"

#include "glutil/shader.h"

#include <string.h>

#define LOCATION_VPOSITION 0
#define LOCATION_VCOLOR 1
#define LOCATION_VNORMAL 2

#define VERTICES_CUBE 36
static const material materialCube = {
    .ambient = { 0.2, 0.2, 0.2 },
    .diffuse = { 0.5, 0.5, 0.5 },
    .specular = { 0.8, 0.8, 0.8 },
    .shininess = 6.0
};
static const vertex dataCube[VERTICES_CUBE] = {
    // Front
    { -1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f },
    {  1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f },
    { -1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f },

    {  1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f },
    {  1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f },
    { -1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f },

    // Back
    { -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f },
    {  1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f },
    { -1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f },

    {  1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f },
    {  1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f },
    { -1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f },

    // Left
    { -1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f },
    { -1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f },
    { -1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f },

    { -1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f },
    { -1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f },
    { -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f },

    // Right
    {  1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f,  1.0f,  0.0f,  0.0f },
    {  1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f,  1.0f,  0.0f,  0.0f },
    {  1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f,  1.0f,  0.0f,  0.0f },

    {  1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f,  1.0f,  0.0f,  0.0f },
    {  1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f,  1.0f,  0.0f,  0.0f },
    {  1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f,  1.0f,  0.0f,  0.0f },

    // Top
    { -1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f },
    {  1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f },
    {  1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f },

    { -1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f },
    { -1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f },
    {  1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f },

    // Bottom
    { -1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f,  0.0f, -1.0f,  0.0f },
    {  1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f,  0.0f, -1.0f,  0.0f },
    {  1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f,  0.0f, -1.0f,  0.0f },

    { -1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f,  0.0f, -1.0f,  0.0f },
    { -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f,  0.0f, -1.0f,  0.0f },
    {  1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f,  0.0f, -1.0f,  0.0f }
};

static vbo *currentObject = NULL;
static GLint locationMaterialAmbient;
static GLint locationMaterialDiffuse;
static GLint locationMaterialSpecular;
static GLint locationMaterialShininess;

void setupModel(GLuint program) {
    locationMaterialAmbient = getUniformLocation(program, "material.ambient");
    locationMaterialDiffuse = getUniformLocation(program, "material.diffuse");
    locationMaterialSpecular = getUniformLocation(program, "material.specular");
    locationMaterialShininess = getUniformLocation(program, "material.shininess");
}

model *loadModel(string fileName ATTR_UNUSED) {
    // TODO: Add obj model loader

    model *mod = safe_malloc(sizeof(*mod));
    mod->vertexCount = VERTICES_CUBE;
    mod->mat = materialCube;
    mod->vertices = safe_malloc(sizeof(vertex) * mod->vertexCount);
    memcpy(mod->vertices, &dataCube, sizeof(dataCube));

    return mod;
}

vbo *uploadModel(model *mod) {
    vbo *object = safe_malloc(sizeof(*object));
    object->vertexCount = mod->vertexCount;
    object->mat = mod->mat;

    glGenBuffers(1, &object->bufferName);
    glBindBuffer(GL_ARRAY_BUFFER, object->bufferName);
    glBufferData(GL_ARRAY_BUFFER, mod->vertexCount * sizeof(vertex), mod->vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(LOCATION_VPOSITION, 3, GL_FLOAT, GL_FALSE,
                          sizeof(float) * 9, (void*) (sizeof(float) * 0));

    glVertexAttribPointer(LOCATION_VCOLOR, 3, GL_FLOAT, GL_FALSE,
                          sizeof(float) * 9, (void*) (sizeof(float) * 3));

    glVertexAttribPointer(LOCATION_VNORMAL, 3, GL_FLOAT, GL_FALSE,
                          sizeof(float) * 9, (void*) (sizeof(float) * 6));

    return object;
}

void freeModel(model *mod) {
    safe_free(mod->vertices);
    safe_free(mod);
}

void setVBO(vbo *object) {
    currentObject = object;

    glBindBuffer(GL_ARRAY_BUFFER, object->bufferName);

    glEnableVertexAttribArray(LOCATION_VPOSITION);
    glEnableVertexAttribArray(LOCATION_VCOLOR);
    glEnableVertexAttribArray(LOCATION_VNORMAL);

    glUniform3fv(locationMaterialAmbient, 1, object->mat.ambient);
    glUniform3fv(locationMaterialDiffuse, 1, object->mat.diffuse);
    glUniform3fv(locationMaterialSpecular, 1, object->mat.specular);
    glUniform1f(locationMaterialShininess, object->mat.shininess);
}

void drawVBO() {
    assert(currentObject != NULL);

    glDrawArrays(GL_TRIANGLES, 0, currentObject->vertexCount);
}

void resetVBO() {
    glDisableVertexAttribArray(LOCATION_VPOSITION);
    glDisableVertexAttribArray(LOCATION_VCOLOR);
    glDisableVertexAttribArray(LOCATION_VNORMAL);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    currentObject = NULL;
}

void freeVBO(vbo *object) {
    assert(currentObject != object);

    glDeleteBuffers(1, &object->bufferName);

    safe_free(object);
}
