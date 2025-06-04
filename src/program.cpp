#include "util/specs.hpp"
#include "util/callbacks.hpp"
#include "program.hpp"

#include "render/initialize.hpp"
#include "render/update.hpp"
#include "render/render.hpp"
#include "inputHandler.hpp"

void runProgram(GLFWwindow* window)
{
    if (window == NULL) {
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

    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);

    glViewport(0, 0, windowWidth, windowHeight);
    glfwSetFramebufferSizeCallback(window, viewportResizeCallback);
    glfwSetCursorPosCallback(window, processMouseMovementLogic);

    // Cursor Options:
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Init models and such
    initScene(window);
    
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    /* Main Loop */
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Calculate delta time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Handle looped input logic
        processKeyInputLogic(window, deltaTime);

        // Update logic
        updateFrame(deltaTime);
        renderFrame();

        // Swaps the color buffers (to not flicker)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}

