#include "input.h"

vec3 cameraPosition = { 0.0, 4.0, 8.0 };

static GLFWwindow *window;

static void onKey(GLFWwindow *w UNUSED, int key, int scancode UNUSED, int action, int mods UNUSED) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }
}

void setupInput(GLFWwindow *w) {
    window = w;

    glfwSetKeyCallback(window, onKey);
}

#define PRESSED(key) (glfwGetKey(window, GLFW_KEY_## key) == GLFW_PRESS)

void tick(double delta) {
    double mod = 12.0;

    if (PRESSED(A) || PRESSED(LEFT)) {
        cameraPosition[0] -= mod * delta;
    }
    if (PRESSED(D) || PRESSED(RIGHT)) {
        cameraPosition[0] += mod * delta;
    }

    if (PRESSED(W) || PRESSED(UP)) {
        cameraPosition[2] -= mod * delta;
    }
    if (PRESSED(S) || PRESSED(DOWN)) {
        cameraPosition[2] += mod * delta;
    }

    if (PRESSED(R) || PRESSED(SPACE)) {
        cameraPosition[1] += mod * delta;
    }
    if (PRESSED(F) || PRESSED(LEFT_SHIFT)) {
        cameraPosition[1] -= mod * delta;
    }
}
