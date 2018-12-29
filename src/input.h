#ifndef INPUT_H
#define INPUT_H

#include "master.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <linmath.h>

extern vec3 cameraPosition;

void setupInput(GLFWwindow* w);
void tick(double delta);

#endif /* INPUT_H */
