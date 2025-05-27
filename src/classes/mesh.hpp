#ifndef MESH_HPP
#define MESH_HPP
#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

#include "sceneNode.hpp"
#include "shader.hpp"
#include "../util/modelBuffer.hpp"

namespace Mesh
{
    int totalTextures = 5;
    std::string textureStrings[5]       = {"textureAlbedo", "textureDiffuse", "textureSpecular", "textureNormal", "textureRough"};
    std::string hasTextureStrings[5]    = {"hasAlbedoTex", "hasDiffuseTex", "hasSpecularTex", "hasNormalTex", "hasRoughTex"};

    struct Texture
    {
        unsigned int id;
        std::string type;
        std::string path;
    };

    class Mesh
    {
        public:
            std::vector<glm::vec3>      position;
            std::vector<glm::vec3>      normals;
            std::vector<glm::vec2>      texCoords;
            std::vector<unsigned int>   indices;
            std::vector<Texture> textures;

            // SceneNode type
            SceneNode::Node* node;

            Mesh(std::vector<glm::vec3> position, std::vector<glm::vec3> normals, std::vector<glm::vec2> texCoords, 
                 std::vector<unsigned int> indices, std::vector<Texture> textures)
            {
                this->position  = position;
                this->normals   = normals;
                this->texCoords = texCoords;
                this->indices   = indices;
                this->textures  = textures;

                node = new SceneNode::Node;

                node->vaoID = generateBuffer(this->position, this->normals, this->texCoords, this->indices);
                node->vaoIndexCount = this->indices.size();
            }

            /**
             * @brief Draw the mesh at a given shader.
             * @param shader The shader program to draw to.
             */
            void Draw(Shader::Shader& shader)
            {
                // Textures look like this:
                /*
                 *  uniform sampler2D textureAlbedo; // Used for the actual texture
                 *  uniform sampler2D textureDiffuse; // If it has some diffuse precalcuated or weight
                 *  uniform sampler2D textureSpecular; // If it has some specular precalculated or weight
                 *  uniform sampler2D textureNormal; // Normal lighting
                 *  uniform sampler2D textureRough; // Controls specular blurring.
                 */
        
                // Iterate over textures
                for (unsigned int i = 0; i < totalTextures; i++)
                {
                    glActiveTexture(GL_TEXTURE0 + i);
                    if (textures[i].type == textureStrings[i]) {
                        setTextureBool(shader, hasTextureStrings[i], true);
                        glBindTexture(GL_TEXTURE_2D, textures[i].id);
                    } else {
                        setTextureBool(shader, hasTextureStrings[i], false);
                    }
                }

                glBindVertexArray(node->vaoID);
                glDrawElements(GL_TRIANGLES, node->vaoIndexCount, GL_UNSIGNED_INT, 0);
                // Unbind
                glBindVertexArray(0);
            }
        
        private:
            void setTextureBool(Shader::Shader& shader, std::string uniformName, bool hasTexture)
            {
                glUniform1i(shader.getUniformFromName(uniformName), hasTexture);
            }
    };
}

#endif