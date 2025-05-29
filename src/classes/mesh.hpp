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

            std::vector<Mesh*> children;
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

                setTextureBool(shader, "textureAlbedoBool", false);
                setTextureBool(shader, "textureDiffuseBool", false);
                setTextureBool(shader, "textureSpecularBool", false);
                setTextureBool(shader, "textureNormalBool", false);
                setTextureBool(shader, "textureRoughBool", false);
        
                // Iterate over textures
                for (unsigned int i = 0; i < textures.size(); i++)
                {
                    setTextureBool(shader, textures[i].type + "Bool", true);

                    glActiveTexture(GL_TEXTURE0 + i);
                    glUniform1i(shader.getUniformFromName(textures[i].type), i);
                    glBindTexture(GL_TEXTURE_2D, textures[i].id);
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