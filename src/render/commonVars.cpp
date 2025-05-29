#include "commonVars.hpp"

// Camera
glm::vec3 cameraPosition = {0.0, 0.0, 0.0};
glm::vec2 cameraAngle = {0.0, 0.0};
float FOV = 90.0f;
float nearPlane = 0.1f;
float farPlane = 1000.0f;

// Matrices
glm::mat4 VP;

// Shaders