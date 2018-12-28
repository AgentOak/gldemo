#include "input.h"

void onKey(GLFWwindow *window, int key UNUSED, int scancode UNUSED, int action UNUSED, int mods UNUSED) {
    if (action == GLFW_PRESS && (key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q)) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        return;
    }
}
