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
extern float cameraSpeed;


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