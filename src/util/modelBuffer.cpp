#include <glad/glad.h>

#include "modelBuffer.hpp"

/**
 * @brief Create an attribute for a given buffer object.
 * @param id The attribute ID for the buffer.
 * @param elementsPerEntry How many elements per data entry.
 * @param data
 * @param normalize Normalize the data entries (Most used for normals and such).
 * @returns The buffer ID.
 */
template <class T>
unsigned int generateAttribute(int id, int elementsPerEntry, std::vector<T> data, bool normalize)
{
    unsigned int bufferID;
    glGenBuffers(1, &bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(id, elementsPerEntry, GL_FLOAT, normalize ? GL_TRUE : GL_FALSE, sizeof(T), 0);
    glEnableVertexAttribArray(id);
    return bufferID;
}

/**
 * @brief Create a vertex array object.
 * @param vertices All the positional data of the vertices.
 * @param normals All the normal data for the vertices.
 * @param texCoords All the textureCoordinate data for the vertices.
 * @returns The vertex array object ID. 
 */
unsigned int generateBuffer(const std::vector<glm::vec3>& vertices, 
                            const std::vector<glm::vec3>& normals, 
                            const std::vector<glm::vec2>& texCoords, 
                            const std::vector<unsigned int>& indices)
{
    unsigned vaoID;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    // Create the vertex position, normal, and uv attributes.
                                generateAttribute(0, 3, vertices, false); // Location = 0 in shader.
    if (normals.size() > 0)   { generateAttribute(1, 3, normals, true); } // Location = 1 in shader.
    if (texCoords.size() > 0) { generateAttribute(2, 3, texCoords, false);} // Location = 2 in shader.

    // Create the indexBufferObject (IBO) to store face data.
    unsigned int iboID;
    glGenBuffers(1, &iboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    return vaoID;
}