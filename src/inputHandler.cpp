

#include "inputHandler.hpp"

/**
 * @brief Handles user keyboard input.
 */
void processInput(GLFWwindow* window)
{
    // Escape key closes OpenGL program. (Debug)
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}