#include "model.h"

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

model *loadModel(string fileName UNUSED) {
    model *mod = malloc(sizeof(*mod));
    if (!mod) {
        FAIL("Couldn't allocate memory for model");
    }

    mod->vertexCount = VERTICES_CUBE;
    mod->vertices = malloc(sizeof(vertex) * mod->vertexCount);
    if (!mod->vertices) {
        FAIL("Couldn't allocate memory for model vertices");
    }
    memcpy(mod->vertices, &dataCube, sizeof(dataCube));

    return mod;
}

vbo *uploadModel(model *mod) {
    vbo *object = malloc(sizeof(*object));
    object->vertexCount = mod->vertexCount;

    glGenBuffers(1, &object->bufferName);
    glBindBuffer(GL_ARRAY_BUFFER, object->bufferName);
    glBufferData(GL_ARRAY_BUFFER, mod->vertexCount * sizeof(vertex), mod->vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(LOCATION_VPOSITION, 3, GL_FLOAT, GL_FALSE,
                          sizeof(float) * 6, (void*) 0);
    
    glVertexAttribPointer(LOCATION_VCOLOR, 3, GL_FLOAT, GL_FALSE,
                          sizeof(float) * 6, (void*) (sizeof(float) * 3));

    return object;
}

void freeModel(model *mod) {
    free(mod->vertices);
    free(mod);
}

void drawVBO(vbo *object) {
    glBindBuffer(GL_ARRAY_BUFFER, object->bufferName);

    glEnableVertexAttribArray(LOCATION_VPOSITION);
    glEnableVertexAttribArray(LOCATION_VCOLOR);

    glDrawArrays(GL_TRIANGLES, 0, object->vertexCount);
}
