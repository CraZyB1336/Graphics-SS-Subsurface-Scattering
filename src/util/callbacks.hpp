#ifndef CALLBACKS_HPP
#define CALLBACKS_HPP
#pragma once

#include <GLFW/glfw3.h>

void glfwErrorCallback(int error, const char* description);

void viewportResizeCallback(GLFWwindow* window, int width, int height);

#endif