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
 * @param Mesh Mesh struct defining the vertex data.
 * @returns The vertex array object ID. 
 */
unsigned int generateBuffer(Mesh &mesh)
{
    unsigned vaoID;
    glGenBuffers(1, &vaoID);
    glBindVertexArray(vaoID);

    // Create the vertex position, normal, and uv attributes.
                                    generateAttribute(0, 3, mesh.vertices, false); // Location = 0 in shader.
    if (mesh.normals.size() > 0)  { generateAttribute(1, 3, mesh.normals, true); } // Location = 1 in shader.
    if (mesh.uvs.size() > 0)      { generateAttribute(2, 3, mesh.uvs, false);    } // Location = 2 in shader.

    // Create the indexBufferObject (IBO) to store face data.
    unsigned int iboID;
    glGenBuffers(1, &iboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), mesh.indices.data(), GL_STATIC_DRAW);

    return vaoID;
}