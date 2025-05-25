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

    /* Initialize */

    // Activate the Z-buffer
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LESS);

    glEnable(GL_CULL_FACE);
    glDisable(GL_DITHER);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glViewport(0, 0, windowWidth, windowHeight);
    glfwSetFramebufferSizeCallback(currentWindow, viewportResizeCallback);


    /* Main Loop */
    while(!glfwWindowShouldClose(currentWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Input part of the loop
        processInput(currentWindow);

        // Rendering goes here
        // ...
        
        // UpdatingFrame (transforms and such)
        // renderFrame (rendering shaders, etc)


        // Swaps the color buffers (to not flicker)
        glfwSwapBuffers(currentWindow);
        glfwPollEvents();
    }

    glfwTerminate();
}

