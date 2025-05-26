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
    int totalTextures = 3;

    struct Textures
    {
        int albedoTextureID     = -1;
        int normalTextureID     = -1;
        int diffuseTextureID    = -1;
    };

    class Mesh
    {
        public:
            std::vector<glm::vec3>      position;
            std::vector<glm::vec3>      normals;
            std::vector<glm::vec2>      texCoords;
            std::vector<unsigned int>   indices;
            Textures textures;

            // SceneNode type
            SceneNode::Node* node;

            Mesh(std::vector<glm::vec3> position, std::vector<glm::vec3> normals, std::vector<glm::vec2> texCoords, 
                 std::vector<unsigned int> indices, Textures textures)
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

            void Draw(Shader::Shader& shader)
            {
                // Iterate over textures
                for (unsigned int i = 0; i < totalTextures; i++)
                {
                    if (checkHasTexture(i, shader))
                    {
                        glActiveTexture(GL_TEXTURE0 + i);
                        glBindTexture(GL_TEXTURE_2D, retrieveTextureID(i));
                    }
                }

                glBindVertexArray(node->vaoID);
                glDrawElements(GL_TRIANGLES, node->vaoIndexCount, GL_UNSIGNED_INT, 0);
                // Unbind
                glBindVertexArray(0);
            }
        
        private:
            bool checkHasTexture(int i, Shader::Shader& shader)
            {   
                switch (i)
                {
                case 0:
                    if (this->textures.albedoTextureID != -1) 
                    {
                        glUniform1i(shader.getUniformFromName("hasAlbedoTexture"), 1);
                        return true;
                    }
                    glUniform1i(shader.getUniformFromName("hasAlbedoTexture"), 0);
                    break;
                case 1:
                    if (this->textures.normalTextureID != -1) 
                    {
                        glUniform1i(shader.getUniformFromName("hasNormalTexture"), 1);
                        return true;
                    }
                    glUniform1i(shader.getUniformFromName("hasNormalTexture"), 0);
                    break;
                case 2:
                    if (this->textures.diffuseTextureID != -1)
                    {
                        glUniform1i(shader.getUniformFromName("hasDiffuseTexture"), 1);
                        return true;
                    }
                    glUniform1i(shader.getUniformFromName("hasDiffuseTexture"), 0);
                    break;
                default:
                    break;
                }

                return false;
            }

            int retrieveTextureID(int i)
            {
                switch (i)
                {
                case 0:
                    return this->textures.albedoTextureID;
                    break;
                case 1:
                    return this->textures.normalTextureID;
                    break;
                case 2:
                    return this->textures.diffuseTextureID;
                    break;
                default:
                    break;
                }
            }
    };
}

#endif