#ifndef LIGHT_H
#define LIGHT_H

#include "master.h"

#include <glad/glad.h>
#include <linmath.h>

typedef struct light_data {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
} light;

void setupLight(GLuint program);
light *newLight();
void freeLight(light *li);

void addLight(light *li);
void resetLights();

#endif /* LIGHT_H */
