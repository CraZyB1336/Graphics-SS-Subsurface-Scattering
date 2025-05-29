#include <iostream>
#include <filesystem>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "util/specs.hpp"
#include "util/callbacks.hpp"
#include "program.hpp"


int main(int, char**){
    printf("Current Working Directory: %s\n", std::filesystem::current_path().c_str());

    if (!glfwInit())
    {
        fprintf(stderr, "Could not initialize GLFW\n");
    }

    // Set core window options. Adjust versions if needed.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback(glfwErrorCallback);

    glfwWindowHint(GLFW_RESIZABLE, windowResizable);
    glfwWindowHint(GLFW_SAMPLES, windowSamples); // In terms of MSAA

    // Create the window object
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), nullptr, nullptr);

    if (window == nullptr)
    {
        fprintf(stderr, "Failed to create GLFW window");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    // Initialize glad
    gladLoadGL();

    printf("OpenGL Specifications:\n");
    printf("%s: %s\n", glGetString(GL_VENDOR), glGetString(GL_RENDERER));
    printf("GLFW:\t %s\n", glfwGetVersionString());
    printf("OpenGL:\t %s\n", glGetString(GL_VERSION));
    printf("GLSL:\t %s\n\n\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    // Run the OpenGL program
    runProgram(window);

    return 0;
}
