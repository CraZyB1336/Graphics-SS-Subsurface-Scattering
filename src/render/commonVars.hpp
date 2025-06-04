#ifndef COMMONVARS_RENDER_HPP
#define COMMONVARS_RENDER_HPP
#pragma once

#include <glm/glm.hpp>

#include "../classes/mesh.hpp"
#include "../classes/model.hpp"
#include "../classes/shader.hpp"

// Camera
extern glm::vec3 cameraPosition;
extern glm::vec2 cameraAngle;
extern float FOV;
extern float nearPlane;
extern float farPlane;

// Movement
extern bool forward;
extern bool backward;
extern bool right;
extern bool left;
extern float cameraSpeed;
extern float cameraRotateSpeed;


// Matrices
extern glm::mat4 VP;

// Shaders
extern Shader::Shader* mainShader;

// Models
extern Mesh::Mesh* rootNode;
extern Model::Model* plantModel;
extern Model::Model* dragonModel;
extern Model::Model* sceneboxModel;

#endif