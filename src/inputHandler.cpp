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
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { forward = true; } else { forward = false; }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { left = true; } else { left = false; }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { right = true;  } else { right = false; }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { backward = true; } else { backward = false; }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) { cameraAngle.y -= cameraRotateSpeed * deltaTime; }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) { cameraAngle.y += cameraRotateSpeed * deltaTime; }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && cameraAngle.x <= 89.0) { cameraAngle.x += cameraRotateSpeed * deltaTime; }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && cameraAngle.x >= -89.0) { cameraAngle.x -= cameraRotateSpeed * deltaTime; }
}

void processMouseInputLogic(GLFWwindow* window, float deltaTime)
{
    
}