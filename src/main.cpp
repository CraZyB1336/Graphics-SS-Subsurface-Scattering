#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Window Const Options
const int           windowWidth     = 1920;
const int           windowHeight    = 1080;
const std::string   windowTitle     = "SSSS";
const GLint         windowResizable = GL_TRUE;
const int           windowSamples   = 4;

static void glfwErrorCallback(int error, const char* description)
{
    fprintf(stderr, "GLFW returned an error:\n\t%s (%i)\n", description, error);
}


int main(int, char**){

    if (!glfwInit())
    {
        fprintf(stderr, "Could not initialize GLFW\n");
    }

    // Set core window options. Adjust versions if needed.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

    glViewport(0, 0, windowWidth, windowHeight);

    while(!glfwWindowShouldClose(window))
    {
        // Swaps the color buffer
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
