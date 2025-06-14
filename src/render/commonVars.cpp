#include "commonVars.hpp"

// Camera
glm::vec3 cameraPosition = {0.0, 5.0, -20.0};
glm::vec2 cameraAngle = {0.0, 90.0};
float FOV = 60.0f;
float nearPlane = 0.1f;
float farPlane = 1000.0f;

// Movement
bool forward;
bool backward;
bool right;
bool left;
float cameraSpeed = 5;
float cameraRotateSpeed = 25;
float cameraSensitivity = 0.2;

// Matrices
glm::mat4 VP;

// Shaders
Shader::Shader* mainShader;
Shader::Shader* screenShader;

// Models
Mesh::Mesh* rootNode;
Model::Model* plantModel;
Model::Model* dragonModel;
Model::Model* sceneboxModel;
Mesh::Mesh* screenPlaneMesh;