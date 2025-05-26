#pragma once

#include <glm/glm.hpp>

#include <iostream>
#include <vector>

namespace SceneNode
{
    enum Type {
        GEOMETRY, SKYBOX
    };

    class Node
    {
        public:
            // Generic Information
            glm::vec3 position  = glm::vec3(0, 0, 0);
            glm::vec3 rotation  = glm::vec3(0, 0, 0);
            glm::vec3 scale     = glm::vec3(1, 1, 1);
            glm::vec3 refPoint  = glm::vec3(0, 0, 0);

            // VAO
            int vaoID           = -1;
            int vaoIndexCount   = 0;

            Type type = GEOMETRY;

            // Node hierarchy and relative transformation matrix.
            std::vector<Node*> children;
            glm::mat4 transMat;

            /**
             * @brief Print information about the node.
             */
            void printNode()
            {
                printf(
                    "SceneNode: {\n"
                    "   Child Count: %i\n"
                    "   Rotation: (%f, %f, %f)\n"
                    "   Position: (%f, %f, %f)\n"
                    "   Reference Point: (%f, %f, %f)\n"
                    "   VAO-ID: %i\n"
                    "}\n",
                    int(this->children.size()),
                    this->rotation.x, this->rotation.y, this->rotation.z,
                    this->position.x, this->position.y, this->position.z,
                    this->refPoint.x, this->refPoint.y, this->refPoint.z,
                    this->vaoID
                );
            };
    };
};