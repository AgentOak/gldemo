#include "gldemo.h"

#include "renderer.h"
#include "input.h"

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define DEBUG_GL_STRING(name) \
    DEBUG(#name ": %s", glGetString(name))

#define RES_DEFAULT_WIDTH 1280
#define RES_DEFAULT_HEIGHT 720

static void onGLFWError(int error, const char *message) {
    WARN("[GLFW #%d] %s", error, message);
}

static void onGLFWFramebufferSize(GLFWwindow *window UNUSED, int width, int height) {
    glViewport(0, 0, width, height);

    onViewport(width, height);
}

void gldemo(gldemo_options *opts) {
    /* GLFW - OpenGL Toolkit */
    DEBUG("Creating context...");
    INFO("GLFW version: %s", glfwGetVersionString());
    DEBUG("Compiled against GLFW version %d.%d.%d", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);

    glfwSetErrorCallback(onGLFWError);

    if (!glfwInit()) {
        FAIL("GLFW initialization failure");
    }

    atexit(glfwTerminate); // Don't care if this fails

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE); // Initially hidden before scene is loaded

    GLFWwindow *window = glfwCreateWindow(RES_DEFAULT_WIDTH, RES_DEFAULT_HEIGHT, GLDEMO_NAME, NULL, NULL);
    if (!window)  {
        FAIL("Window creation failure");
    }

    glfwMakeContextCurrent(window);

    /* GLAD - OpenGL Function Loader */
    DEBUG("Loading OpenGL...");
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        FAIL("OpenGL loader failure");
    }

    INFO("OpenGL version: %s", glGetString(GL_VERSION));
    DEBUG("GLAD: OpenGL version %d.%d", GLVersion.major, GLVersion.minor);
    if (!GLAD_GL_VERSION_3_3) {
        WARN("The loaded OpenGL driver does not support OpenGL 3.3");
    }

    DEBUG_GL_STRING(GL_VENDOR);
    DEBUG_GL_STRING(GL_RENDERER);
    DEBUG_GL_STRING(GL_VERSION);
    DEBUG_GL_STRING(GL_SHADING_LANGUAGE_VERSION);
    DEBUG_GL_STRING(GL_EXTENSIONS);

    // TODO: If debug add GLAD post callback to check for errors

    // Register callbacks
    glfwSetFramebufferSizeCallback(window, onGLFWFramebufferSize);
    glfwSetKeyCallback(window, onKey);

    // Load scene
    INFO("Initializing renderer");
    setupRenderer(opts->argc, opts->argv);

    // Display window late
    glfwSetTime(0.0);
    glfwSwapInterval(opts->swapInterval);
    glfwShowWindow(window);

    /* Main loop */
    INFO("Done! Entering main loop");
    double lastTime = 0.0;
    while (!glfwWindowShouldClose(window)) {
        double currTime = glfwGetTime();
        // TODO: Properly decouple ticks from render calls
        // TODO: Frame limiter
        tick(currTime - lastTime);
        render(currTime);
        lastTime = currTime;

        // TODO: Check opengl errors once every frame

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    INFO("Terminating");

    /* Terminate application */
    glfwDestroyWindow(window);
}
