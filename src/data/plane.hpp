#include <vector>
#include <glm/glm.hpp>

namespace PlaneData
{
    // Plane vertices
    const std::vector<glm::vec3> vertices = {
        glm::vec3(-1.0f, -1.0f, -0.0f),  // Bottom-left
        glm::vec3( 1.0f, -1.0f, -0.0),  // Bottom-right
        glm::vec3( -1.0f,  1.0f, -0.9f),  // Top-right
        glm::vec3(1.0f,  1.0f, -0.9f)   // Top-left
    };

    // Plane normals
    const std::vector<glm::vec3> normals = {
        glm::vec3(0.0f, 0.0f, 1.0f),    // Bottom-left
        glm::vec3(0.0f, 0.0f, 1.0f),    // Bottom-right
        glm::vec3(0.0f, 0.0f, 1.0f),    // Top-right
        glm::vec3(0.0f, 0.0f, 1.0f)     // Top-left
    };

    // Plane indices
    const std::vector<glm::vec2> texCoords = {
        glm::vec2(1.0f, 0.0f),          // Bottom-left
        glm::vec2(0.0f, 1.0f),          // Bottom-right
        glm::vec2(0.0f, 0.0f),          // Top-right
        glm::vec2(1.0f, 1.0f)           // Top-left
    };

    // Plane texcoords
    const std::vector<unsigned int> indices = {
        1, 2, 0,  // First triangle
        1, 3, 2   // Second triangle
    };
}