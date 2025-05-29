#include <glad/glad.h>
#include <string>

#include "modelBuffer.hpp"

void calculateTangentAndBiTangent(std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs, std::vector<unsigned int> indices);

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
    if (texCoords.size() > 0) { generateAttribute(2, 3, texCoords, false); // Location = 2 in shader.
                                calculateTangentAndBiTangent(vertices, texCoords, indices); } // Location = 3, and Location = 4

    // Create the indexBufferObject (IBO) to store face data.
    unsigned int iboID;
    glGenBuffers(1, &iboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    return vaoID;
}

/**
 * @brief Calculates the tangent and bitanget to construct the TBN matrix.
 * @param vertices The vertices to calculate for the tangent and bitangent.
 * @param uvs The texture coordinates to calculate for the tangent and bitangent.
 */
void calculateTangentAndBiTangent(std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs, std::vector<unsigned int> indices)
{
    std::vector<glm::vec3> tangents(vertices.size(), glm::vec3(0.0));
    std::vector<glm::vec3> biTangents(vertices.size(), glm::vec3(0.0));

    // Grab two edges; have to iterate through the indices
    for (unsigned int i = 0; i < indices.size(); i += 3)
    {
        // Grab 3 indicies forming a triangle
        unsigned int ind0 = indices[i + 0];
        unsigned int ind1 = indices[i + 1];
        unsigned int ind2 = indices[i + 2];

        // Vertices related to this face
        glm::vec3 v0 = vertices[ind0];
        glm::vec3 v1 = vertices[ind1];
        glm::vec3 v2 = vertices[ind2];

        // UVS related to this face
        glm::vec2 uv0 = uvs[ind0];
        glm::vec2 uv1 = uvs[ind1];
        glm::vec2 uv2 = uvs[ind2];

        // Calculate tangent and bitangentd
        glm::vec3 deltaPos1 = v1 - v0;
        glm::vec3 deltaPos2 = v2 - v0;

        glm::vec2 deltaUV1 = uv1 - uv0;
        glm::vec2 deltaUV2 = uv2 - uv0;

        float r = 1.0 / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
        glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
        glm::vec3 biTangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

        tangents[ind0] += tangent;
        tangents[ind1] += tangent;
        tangents[ind2] += tangent;

        biTangents[ind0] += biTangent;
        biTangents[ind1] += biTangent;
        biTangents[ind2] += biTangent;
    }

    // Normalize the tangents and bitangents.
    for (unsigned int i = 0; i < tangents.size(); i++)
    {
        if (glm::length(tangents[i]) > 0.0) tangents[i] = glm::normalize(tangents[i]);
        if (glm::length(biTangents[i]) > 0.0) biTangents[i] = glm::normalize(biTangents[i]);
    }

    generateAttribute(3, 3, tangents, true);
    generateAttribute(4, 3, biTangents, true);
}