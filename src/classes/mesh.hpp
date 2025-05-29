#ifndef MESH_HPP
#define MESH_HPP
#pragma once

#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include "shader.hpp"
#include "../util/modelBuffer.hpp"

namespace Mesh
{
    static std::map<std::string, int> textureUnitMap = {
        {"textureDiffuse", 0},
        {"textureSpecular", 1},
        {"textureNormal", 2},
        {"textureRough", 3}
    };

    enum Type {
        NO_GEOMETRY, GEOMETRY, SKYBOX
    };

    struct Texture
    {
        unsigned int id = 0;
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
                if (this->type == NO_GEOMETRY) return;
                // Textures look like this:
                /*
                 *  uniform sampler2D textureDiffuse; // Actual base color
                 *  uniform sampler2D textureSpecular; // If it has some specular precalculated or weight
                 *  uniform sampler2D textureNormal; // Normal lighting
                 *  uniform sampler2D textureRough; // Controls specular blurring.
                 */

                setTextureBool(shader, "textureDiffuseBool", false);
                setTextureBool(shader, "textureSpecularBool", false);
                setTextureBool(shader, "textureNormalBool", false);
                setTextureBool(shader, "textureRoughBool", false);
        
                // Iterate over textures
                for (unsigned int i = 0; i < textures.size(); i++)
                {
                    if (textures[i].id != 0 || textures[i].type != "NONE")
                    {
                        int unit = textureUnitMap.find(textures[i].type)->second;

                        setTextureBool(shader, textures[i].type + "Bool", true);
                        
                        glActiveTexture(GL_TEXTURE0 + unit);
                        glUniform1i(shader.getUniformFromName(textures[i].type), unit);
                        glBindTexture(GL_TEXTURE_2D, textures[i].id);
                    }
                }

                // Pass in model matrix
                glUniformMatrix4fv(shader.getUniformFromName("M"), 1, GL_FALSE, glm::value_ptr(this->transMat));

                // Construct Normal Matrix
                glm::mat3 NM = glm::transpose(glm::inverse(glm::mat3(this->transMat)));
                glUniformMatrix3fv(shader.getUniformFromName("NM"), 1, GL_FALSE, glm::value_ptr(NM));

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