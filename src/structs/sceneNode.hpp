#pragma once

#include <glm/glm.hpp>

#include <iostream>
#include <vector>

enum SceneNodeType {
    GEOMETRY, SKYBOX
};

struct SceneNode {
    SceneNode() {
        position    = glm::vec3(0, 0, 0);
        rotation    = glm::vec3(0, 0, 0);
        scale       = glm::vec3(1, 1, 1);
        refPoint    = glm::vec3(0, 0, 0);

        vaoID           = -1;
        vaoIndexCount   = 0;

        type = GEOMETRY;
    }
    
    // Vector of SceneNode children.
    std::vector<SceneNode*> children;

    // Saves the current transformation matrix
    glm::mat4 transMat;

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    glm::vec3 refPoint;

    int vaoID;
    int vaoIndexCount;

    SceneNodeType type;
};


inline void printNode(SceneNode* node)
{
    printf(
        "SceneNode: {\n"
        "   Child Count: %i\n"
        "   Rotation: (%f, %f, %f)\n"
        "   Position: (%f, %f, %f)\n"
        "   Reference Point: (%f, %f, %f)\n"
        "   VAO-ID: %i\n"
        "}\n",
        int(node->children.size()),
        node->rotation.x, node->rotation.y, node->rotation.z,
        node->position.x, node->position.y, node->position.z,
        node->refPoint.x, node->refPoint.y, node->refPoint.z,
        node->vaoID
    );
};