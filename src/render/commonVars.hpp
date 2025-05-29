#ifndef COMMONVARS_HPP
#define COMMONVARS_HPP
#pragma once

#include <glm/glm.hpp>

#include "../classes/sceneNode.hpp"

// Camera
extern glm::vec3 cameraPosition;
extern glm::vec2 cameraAngle;
extern float FOV;
extern float nearPlane;
extern float farPlane;


// Matrices
extern glm::mat4 VP;

// Shaders

// Models
    // 3D
SceneNode::Node* rootNode;

#endif