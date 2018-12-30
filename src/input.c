#include "input.h"

vec3 cameraPosition = { 0.0, 1.5, 9.5 };
mat4x4 view;

static bool mouseActive = false;
static double horizontalAngle = DEGREES(180.0), verticalAngle = DEGREES(20.0);
static double lastX = 0.0, lastY = 0.0;

static GLFWwindow *window;

static void catchMouse() {
    if (!mouseActive && glfwGetWindowAttrib(window, GLFW_FOCUSED)) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPos(window, lastX, lastY);
        mouseActive = true;
    }
}

static void releaseMouse() {
    if (mouseActive) {
        mouseActive = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

static void onKey(GLFWwindow *w UNUSED, int key, int scancode UNUSED, int action, int mods UNUSED) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_Q) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        } else if (key == GLFW_KEY_ESCAPE) {
            releaseMouse();
        }
    }
}

static void onWindowFocus(GLFWwindow *w UNUSED, int focused) {
    if (focused) {
        catchMouse();
    } else {
        releaseMouse();
    }
}

static void onMouseButton(GLFWwindow* w UNUSED, int button UNUSED, int action, int mods UNUSED) {
    if (action == GLFW_PRESS) {
        catchMouse();
    }
}

void setupInput(GLFWwindow *w) {
    window = w;

    mat4x4_identity(view);

    glfwSetKeyCallback(window, onKey);
    glfwSetWindowFocusCallback(window, onWindowFocus);
    glfwSetMouseButtonCallback(window, onMouseButton);
}

#define PRESSED(key) (glfwGetKey(window, GLFW_KEY_## key) == GLFW_PRESS)

void tick(double delta) {
    double movSpeed = 12.0;
    double mouseSpeed = 0.002;

    if (mouseActive) {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        mouseY = -mouseY; // Convert window coordinates to OpenGL coordinates

        // TODO: Fix rolling over
        horizontalAngle += mouseSpeed * (lastX - mouseX);
        verticalAngle += mouseSpeed * (lastY - mouseY);

        lastX = mouseX;
        lastY = mouseY;
    }

    vec3 direction = {
        cos(verticalAngle) * sin(horizontalAngle),
        -sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
    };

    vec3 right = {
        sin(horizontalAngle - PI / 2.0),
        0,
        cos(horizontalAngle - PI / 2.0)
    };

    vec3 up = { 0.0, 1.0, 0.0 };
    //vec3_mul_cross(up, right, direction);

    // TODO: Normalize
    vec3 scaled;
    if (PRESSED(A) || PRESSED(LEFT)) {
        vec3_scale(scaled, right, -movSpeed * delta);
        vec3_add(cameraPosition, cameraPosition, scaled);
    }
    if (PRESSED(D) || PRESSED(RIGHT)) {
        vec3_scale(scaled, right, movSpeed * delta);
        vec3_add(cameraPosition, cameraPosition, scaled);
    }
    if (PRESSED(W) || PRESSED(UP)) {
        vec3_scale(scaled, direction, movSpeed * delta);
        vec3_add(cameraPosition, cameraPosition, scaled);
    }
    if (PRESSED(S) || PRESSED(DOWN)) {
        vec3_scale(scaled, direction, -movSpeed * delta);
        vec3_add(cameraPosition, cameraPosition, scaled);
    }
    if (PRESSED(R) || PRESSED(SPACE)) {
        vec3_scale(scaled, up, movSpeed * delta);
        vec3_add(cameraPosition, cameraPosition, scaled);
    }
    if (PRESSED(F) || PRESSED(LEFT_SHIFT)) {
        vec3_scale(scaled, up, -movSpeed * delta);
        vec3_add(cameraPosition, cameraPosition, scaled);
    }

    vec3 lookAt;
    vec3_add(lookAt, cameraPosition, direction);
    mat4x4_look_at(view, cameraPosition, lookAt, up);
}
