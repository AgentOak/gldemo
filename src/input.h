#ifndef INPUT_H
#define INPUT_H

#include "master.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <linmath.h>

extern float fieldOfView;
extern vec3 cameraPosition;
extern mat4x4 view;

void setupInput(GLFWwindow* w) ATTR_NONNULL();
void tick(double delta);

#endif /* INPUT_H */
