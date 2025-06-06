#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "update.hpp"
#include "commonVars.hpp"
#include "../util/specs.hpp"

void updateNodeTransforms(Mesh::Mesh* node, glm::mat4 currentTransformation);
void handleMovement(glm::vec3 direction, float deltaTime);

/**
 * @brief Updates the logic for the current frame.
 * Including camera transforms, and geometric transforms along with switches and etc.
 * @param deltaTime Delta time for calculating physics / time dependent based operations (if needed).
 */
void updateFrame(float deltaTime)
{
    glm::mat4 perspectiveProjection = glm::perspective(glm::radians(FOV), float(windowWidth) / float(windowHeight), nearPlane, farPlane);

    // Calculate first person camera direction vector
    glm::vec3 lookingDirection;
    lookingDirection.x = cos(glm::radians(cameraAngle.y)) * cos(glm::radians(cameraAngle.x));
    lookingDirection.y = sin(glm::radians(cameraAngle.x));
    lookingDirection.z = sin(glm::radians(cameraAngle.y)) * cos(glm::radians(cameraAngle.x));

    handleMovement(lookingDirection, deltaTime);

    glm::mat4 cameraTransform = glm::lookAt(cameraPosition, cameraPosition + lookingDirection, glm::vec3(0, 1, 0));

    VP = perspectiveProjection * cameraTransform;
    // Pass in the identity matrix
    // All transforms are still relative to world space here
    // We translate to NDC in the shader.
    updateNodeTransforms(rootNode, glm::mat4(1.0));
}

void updateNodeTransforms(Mesh::Mesh* node, glm::mat4 currentTransformation)
{
    // We're assuming local scaling. So we don't scale around the reference point.

    // The redeclarations are left-multiplying
    glm::mat4 modelMat = glm::mat4(1.0);
    modelMat = glm::scale(modelMat, node->scale);
    // Move to the reference point for rotation.
    modelMat = glm::translate(modelMat, node->refPoint);
    modelMat = glm::rotate(modelMat, glm::radians(node->rotation.z), {0.0, 0.0, 1.0});
    modelMat = glm::rotate(modelMat, glm::radians(node->rotation.y), {0.0, 1.0, 0.0});
    modelMat = glm::rotate(modelMat, glm::radians(node->rotation.x), {1.0, 0.0, 0.0});
    // Go back to origo
    modelMat = glm::translate(modelMat, -node->refPoint);
    modelMat = glm::translate(modelMat, node->position);
    
    node->transMat = currentTransformation * modelMat;

    // TODO Switch case for handling different types
    for (Mesh::Mesh* child : node->children)
    {
        updateNodeTransforms(child, node->transMat);
    }
}

void handleMovement(glm::vec3 direction, float deltaTime)
{
    if (forward)
    {
        cameraPosition += direction * cameraSpeed * deltaTime;
    }

    if (backward)
    {
        cameraPosition -= direction * cameraSpeed * deltaTime;
    }

    if (left)
    {
        glm::vec3 leftDir = {direction.z, direction.y, -direction.x};
        cameraPosition += leftDir * cameraSpeed * deltaTime;
    }

    if (right)
    {
        glm::vec3 rightDir = {-direction.z, direction.y, direction.x};
        cameraPosition += rightDir * cameraSpeed * deltaTime;
    }
}