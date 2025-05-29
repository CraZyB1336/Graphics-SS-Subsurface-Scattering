#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "update.hpp"
#include "commonVars.hpp"
#include "../util/specs.hpp"

// void updateNodeTransforms

/**
 * @brief Updates the logic for the current frame.
 * Including camera transforms, and geometric transforms along with switches and etc.
 * @param deltaTime Delta time for calculating physics / time dependent based operations (if needed).
 */
void updateFrame(float deltaTime)
{
    glm::mat4 perspectiveProjection = glm::perspective(glm::radians(FOV), float(windowWidth) / float(windowHeight), nearPlane, farPlane);
    glm::mat4 cameraTransform = glm::lookAt(cameraPosition, cameraPosition * glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));

    VP = perspectiveProjection * cameraTransform;
}

