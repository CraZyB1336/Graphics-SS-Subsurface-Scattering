#include "commonVars.hpp"

// Camera
glm::vec3 cameraPosition = {0.0, 5.0, -20.0};
glm::vec2 cameraAngle = {0.0, 90.0};
float FOV = 60.0f;
float nearPlane = 0.1f;
float farPlane = 1000.0f;
float cameraSpeed = 5;

// Matrices
glm::mat4 VP;

// Shaders
Shader::Shader* mainShader;

// Models
Mesh::Mesh* rootNode;
Model::Model* plantModel;
Model::Model* dragonModel;
Model::Model* sceneboxModel;