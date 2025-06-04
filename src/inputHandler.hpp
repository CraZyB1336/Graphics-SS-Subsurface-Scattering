#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP
#pragma once

#include <GLFW/glfw3.h>

void processKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
void processKeyInputLogic(GLFWwindow* window, float deltaTime);
void processMouseInputLogic(GLFWwindow* window, float deltaTime);

#endif