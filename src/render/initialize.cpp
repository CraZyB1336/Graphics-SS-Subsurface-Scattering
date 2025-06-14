
#include "commonVars.hpp"
#include "initialize.hpp"
#include "../inputHandler.hpp"

#include "../data/plane.hpp"

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
    // plantModel = new Model::Model("../resources/models/plant/plant_fixed.obj");
    // plantModel->root->position = {-6.0, 0.0, 4};
    // rootNode->children.push_back(plantModel->root);

    // dragonModel = new Model::Model("../resources/models/dragon/dragon.obj");
    // dragonModel->root->position = {7.0, 0.0, -3};
    // dragonModel->root->rotation = {0.0, 32.5, 0.0};
    // rootNode->children.push_back(dragonModel->root);

    // sceneboxModel = new Model::Model("../resources/models/scenebox/scenebox.obj");
    // rootNode->children.push_back(sceneboxModel->root);
    std::vector<Mesh::Texture> emptyTexture;
    screenPlaneMesh = new Mesh::Mesh(PlaneData::vertices, PlaneData::normals, PlaneData::texCoords, PlaneData::indices, emptyTexture);
    rootNode->children.push_back(screenPlaneMesh);
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

    screenShader = new Shader::Shader;
    screenShader->attach("../resources/shaders/screenPlane/main.vert");
    screenShader->attach("../resources/shaders/screenPlane/main.frag");
    screenShader->link();
}