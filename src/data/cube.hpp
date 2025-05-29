#include <vector>
#include <glm/glm.hpp>

namespace CubeData
{
    // Cube vertices (8 unique vertices only)
    const std::vector<glm::vec3> vertices = {
        glm::vec3(-1.0f, -1.0f, -1.0f),  // 0: Bottom-left-back
        glm::vec3( 1.0f, -1.0f, -1.0f),  // 1: Bottom-right-back
        glm::vec3( 1.0f,  1.0f, -1.0f),  // 2: Top-right-back
        glm::vec3(-1.0f,  1.0f, -1.0f),  // 3: Top-left-back
        glm::vec3(-1.0f, -1.0f,  1.0f),  // 4: Bottom-left-front
        glm::vec3( 1.0f, -1.0f,  1.0f),  // 5: Bottom-right-front
        glm::vec3( 1.0f,  1.0f,  1.0f),  // 6: Top-right-front
        glm::vec3(-1.0f,  1.0f,  1.0f)   // 7: Top-left-front
    };

    // Cube normals (8 normals, averaged from adjacent faces)
    const std::vector<glm::vec3> normals = {
        glm::normalize(glm::vec3(-1.0f, -1.0f, -1.0f)),  // 0: Bottom-left-back
        glm::normalize(glm::vec3( 1.0f, -1.0f, -1.0f)),  // 1: Bottom-right-back
        glm::normalize(glm::vec3( 1.0f,  1.0f, -1.0f)),  // 2: Top-right-back
        glm::normalize(glm::vec3(-1.0f,  1.0f, -1.0f)),  // 3: Top-left-back
        glm::normalize(glm::vec3(-1.0f, -1.0f,  1.0f)),  // 4: Bottom-left-front
        glm::normalize(glm::vec3( 1.0f, -1.0f,  1.0f)),  // 5: Bottom-right-front
        glm::normalize(glm::vec3( 1.0f,  1.0f,  1.0f)),  // 6: Top-right-front
        glm::normalize(glm::vec3(-1.0f,  1.0f,  1.0f))   // 7: Top-left-front
    };

    // Cube indices (12 triangles, 2 per face)
    const std::vector<unsigned int> indices = {
        // Back face (Z-)
        0, 1, 2,   2, 3, 0,
        // Front face (Z+)
        4, 5, 6,   6, 7, 4,
        // Left face (X-)
        0, 4, 7,   7, 3, 0,
        // Right face (X+)
        1, 5, 6,   6, 2, 1,
        // Bottom face (Y-)
        0, 1, 5,   5, 4, 0,
        // Top face (Y+)
        3, 2, 6,   6, 7, 3
    };

    // Cube texture coordinates (8 coordinates, simple mapping)
    const std::vector<glm::vec2> texCoords = {
        glm::vec2(0.0f, 0.0f),  // 0: Bottom-left-back
        glm::vec2(1.0f, 0.0f),  // 1: Bottom-right-back
        glm::vec2(1.0f, 1.0f),  // 2: Top-right-back
        glm::vec2(0.0f, 1.0f),  // 3: Top-left-back
        glm::vec2(0.0f, 0.0f),  // 4: Bottom-left-front
        glm::vec2(1.0f, 0.0f),  // 5: Bottom-right-front
        glm::vec2(1.0f, 1.0f),  // 6: Top-right-front
        glm::vec2(0.0f, 1.0f)   // 7: Top-left-front
    };
}