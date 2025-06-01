#include <string>

#include "render/commonVars.hpp"
#include "inputHandler.hpp"

/**
 * @brief Handles user keyboard input not during update loop.
 * Movement logic here will be quite robotic feeling and not natural.
 */
void processKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Escape key closes OpenGL program. (Debug)
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void processKeyInputLogic(GLFWwindow* window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) { cameraPosition.y += cameraSpeed * deltaTime; }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) { cameraPosition.y -= cameraSpeed * deltaTime; }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { cameraPosition.z += cameraSpeed * deltaTime; }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { cameraPosition.x += cameraSpeed * deltaTime; }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { cameraPosition.x -= cameraSpeed * deltaTime; }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { cameraPosition.z -= cameraSpeed * deltaTime; }
}