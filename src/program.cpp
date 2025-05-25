#include "util/specs.hpp"
#include "util/callbacks.hpp"
#include "program.hpp"
#include "inputHandler.hpp"

GLFWwindow* currentWindow;

void runProgram(GLFWwindow* window)
{
    currentWindow = window;

    if (currentWindow == NULL) {
        fprintf(stderr, "OpenGL window is NULL. Aborting");
        return;
    }

    initialize();
    mainLoop();

    glfwTerminate();
}

/**
 * @breif Initializes the OpenGL program. Setting handlers where necessary.
 */
void initialize()
{
    glViewport(0, 0, windowWidth, windowHeight);
    glfwSetFramebufferSizeCallback(currentWindow, viewportResizeCallback);
}

/**
 * @brief Handles the main rendering loop
 */
void mainLoop()
{
    while(!glfwWindowShouldClose(currentWindow))
    {
        // Input part of the loop
        processInput(currentWindow);

        // Rendering goes here
        // ...

        // Swaps the color buffers (to not flicker)
        glfwSwapBuffers(currentWindow);
        glfwPollEvents();
    }
}

