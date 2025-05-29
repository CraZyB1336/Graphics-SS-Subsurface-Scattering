

#include "inputHandler.hpp"

/**
 * @brief Handles user keyboard input.
 */
void processKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Escape key closes OpenGL program. (Debug)
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}