#ifndef LIGHT_H
#define LIGHT_H

#include "master.h"

#include <glad/glad.h>
#include <linmath.h>

typedef struct light_data {
    vec3 position;
    vec3 attenuation;
    vec3 intensity;
} light;

void setupLight(GLuint program);
void setAmbientLight(vec3 intensity);

light *newLight(void);
void freeLight(light *li) ATTR_NONNULL();

void addLight(GLuint program, light *li) ATTR_NONNULL();
void resetLights(void);

#endif /* LIGHT_H */
