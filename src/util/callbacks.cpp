#include <iostream>
#include <glad/glad.h>

#include "callbacks.hpp"

/**
 * @brief Callback for OpenGL errors.
 */
void glfwErrorCallback(int error, const char* description)
{
    fprintf(stderr, "GLFW returned an error:\n\t%s (%i)\n", description, error);
}

/**
 * @brief Callback for window resizing.
 */
void viewportResizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}