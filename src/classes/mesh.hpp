#ifndef MESH_HPP
#define MESH_HPP
#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

#include "shader.hpp"
#include "../util/modelBuffer.hpp"

namespace Mesh
{
    int totalTextures = 5;
    std::string textureStrings[5]       = {"textureAlbedo", "textureDiffuse", "textureSpecular", "textureNormal", "textureRough"};
    std::string hasTextureStrings[5]    = {"hasAlbedoTex", "hasDiffuseTex", "hasSpecularTex", "hasNormalTex", "hasRoughTex"};

    enum Type {
        GEOMETRY, SKYBOX
    };

    struct Texture
    {
        unsigned int id;
        std::string type;
        std::string path;
    };

    class Mesh
    {
        public:
            // Mesh logic data
            glm::vec3 position  = {0.0, 0.0, 0.0};
            glm::vec3 rotation  = {0.0, 0.0, 0.0};
            glm::vec3 scale     = {1.0, 1.0, 1.0};
            glm::vec3 refPoint  = {0.0, 0.0, 0.0};

            glm::mat4 transMat;

            // Informational data
            int vaoID           = -1;
            int vaoIndexCount   = 0;

            Type type = GEOMETRY;

            std::vector<Mesh> children;
            std::vector<Texture> textures;

            Mesh() {return;}

            Mesh(std::vector<glm::vec3> position, std::vector<glm::vec3> normals, std::vector<glm::vec2> texCoords, 
                 std::vector<unsigned int> indices, std::vector<Texture> textures)
            {
                this->textures  = textures;

                vaoID = generateBuffer(position, normals, texCoords, indices);
                vaoIndexCount = indices.size();
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

                glBindVertexArray(vaoID);
                glDrawElements(GL_TRIANGLES, vaoIndexCount, GL_UNSIGNED_INT, 0);
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