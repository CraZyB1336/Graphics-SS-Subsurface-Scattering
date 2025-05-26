#pragma once

#include <vector>
#include <glm/glm.hpp>

unsigned int generateBuffer(const std::vector<glm::vec3>& vertices, 
                            const std::vector<glm::vec3>& normals, 
                            const std::vector<glm::vec2>& texCoords, 
                            const std::vector<unsigned int>& indices);