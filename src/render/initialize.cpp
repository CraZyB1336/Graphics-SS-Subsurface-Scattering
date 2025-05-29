
#include "commonVars.hpp"
#include "initialize.hpp"
#include "../inputHandler.hpp"

#include "../data/cube.hpp"

void initShaders();
void initModels();

/**
 * @brief initialize the scene before rendering.
 * @param window The window to render on.
 */
void initScene(GLFWwindow* window)
{
    // Set input callbacks
    glfwSetKeyCallback(window, processKeyInput);

    initShaders();
    initModels();
}

/**
 * @brief Initialize models.
 */
void initModels()
{
    rootNode = new Mesh::Mesh();
    // Initialize the plant model and add it to root.
    plantModel = new Model::Model("../resources/models/plant/plant_fixed.obj");
    rootNode->children.push_back(plantModel->root);
}

/**
 * @brief Initialize shaders.
 */
void initShaders()
{
    mainShader = new Shader::Shader;
    mainShader->attach("../resources/shaders/main.vert");
    mainShader->attach("../resources/shaders/main.frag");
    mainShader->link();
}