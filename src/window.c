#include "window.h"

#include "renderer.h"
#include "input.h"

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define NOTICE_GL_STRING(name) \
    NOTICE(#name ": %s", glGetString(name));
#define NOTICE_GL_EXTENSION(name) \
    NOTICE(#name ": %s", GLAD_GL_##name ? "Supported" : "Not supported");

static void onGLFWError(int error, const char *message) {
    WARN("[GLFW #%d] %s", error, message);
}

static void GLAPIENTRY onGLError(GLenum source, GLenum type, GLuint id,
    GLenum severity, GLsizei length UNUSED, const GLchar* message, const void* userParam UNUSED) {

    WARN("[%s] source=0x%x, severity=0x%x, type=0x%x, id=%d\n\t%s",
        (type == GL_DEBUG_TYPE_ERROR ? "GL ERROR" : "GL DEBUG"), source, severity, type, id, message);
}

static void onGLFWFramebufferSize(GLFWwindow *window UNUSED, int width, int height) {
    glViewport(0, 0, width, height);

    onViewport(width, height);
}

void window() {
    /* GLFW - OpenGL Toolkit */
    NOTICE("Initializing GLFW");
    INFO("GLFW version: %s", glfwGetVersionString());
    NOTICE("Compiled against GLFW version %d.%d.%d", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);

    glfwSetErrorCallback(onGLFWError);

    if (!glfwInit()) {
        FAIL("GLFW initialization failure");
    }

    atexit(glfwTerminate); // Don't care if this fails

    NOTICE("Creating context");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (opts->debug) {
        INFO("Requesting debug context");
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    }
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE); // Initially hidden before scene is loaded

    // TODO: Fullscreen/Window/Monitor options support
    GLFWwindow *window = glfwCreateWindow(opts->outputWidth, opts->outputHeight, GLDEMO_NAME, NULL, NULL);
    if (!window)  {
        FAIL("Window creation failure");
    }

    glfwMakeContextCurrent(window);

    /* GLAD - OpenGL Function Loader */
    NOTICE("Loading OpenGL");
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        FAIL("OpenGL loader failure");
    }

    INFO("OpenGL version: %s", glGetString(GL_VERSION));
    NOTICE("GLAD: OpenGL version %d.%d", GLVersion.major, GLVersion.minor);
    if (!GLAD_GL_VERSION_3_3) {
        WARN("The loaded OpenGL driver does not support OpenGL 3.3");
    }

    NOTICE_GL_STRING(GL_VENDOR);
    NOTICE_GL_STRING(GL_RENDERER);
    NOTICE_GL_STRING(GL_SHADING_LANGUAGE_VERSION);

    NOTICE_GL_EXTENSION(KHR_debug); // Core in 4.3
    NOTICE_GL_EXTENSION(ARB_debug_output); // Deprecated by KHR_debug
    NOTICE_GL_EXTENSION(ARB_explicit_uniform_location); // Core in 4.3

    // Register callbacks
    glfwSetFramebufferSizeCallback(window, onGLFWFramebufferSize);

    // Input
    setupInput(window);

    /*
     * Enable OpenGL's debug callbacks; polling errors is dumb.
     *
     * Since OpenGL 4.3 drivers are required to support KHR_debug in any case.
     * However, the amount of messages reported is up to the driver.
     * In debug contexts more messages might be provided.
     *
     * ARB_debug_output is a deprecated extension that provides the same functionality,
     * but in debug contexts only. Fallback to that if we can.
     */
    if (GLAD_GL_VERSION_4_3) {
        NOTICE("Enabling message callbacks via native KHR_debug");
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(onGLError, NULL);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
    } else if (GLAD_GL_KHR_debug) {
        NOTICE("Enabling message callbacks via extension KHR_debug");
        glEnable(GL_DEBUG_OUTPUT_KHR);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_KHR);
        glDebugMessageCallbackKHR(onGLError, NULL);
        glDebugMessageControlKHR(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
    } else if (opts->debug && GLAD_GL_ARB_debug_output) {
        NOTICE("Enabling message callbacks via extension ARB_debug_output");
        // ARB_debug_output is available if (and only if) we have a debug context; no glEnable() call is necessary
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
        glDebugMessageCallbackARB(onGLError, NULL);
        glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
    } else {
        WARN("No OpenGL debug mechanisms are supported. Error messages will not be reported.");
    }

    // Load scene
    INFO("Initializing renderer");
    setupRenderer(opts->argc, opts->argv);
    onViewport(opts->outputWidth, opts->outputHeight);

    // Display window late
    glfwSwapInterval(opts->swapInterval);
    glfwShowWindow(window);
    glfwSetTime(0.0);

    /* Main loop */
    INFO("Entering main loop");
    double lastTime = 0.0;
    while (!glfwWindowShouldClose(window)) {
        double currTime = glfwGetTime();
        // TODO: Properly decouple ticks from render calls & arbitrary frame limit, get execution order right
        tick(currTime - lastTime);

        render(currTime);
        glfwSwapBuffers(window);

        lastTime = currTime;

        glfwPollEvents();
    }

    INFO("Terminating");

    /* Terminate application */
    glfwDestroyWindow(window);
}
