#ifndef MODEL_HPP
#define MODEL
#pragma once

#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <stdexcept>

#include "shader.hpp"
#include "mesh.hpp"

namespace Model
{
    class Model
    {
        public:
            Model(char *path)
            {
                loadModel(path);
            }

            /**
             * @brief Draw the Model.
             * @param shader The shader program to draw to.
             */
            void Draw(Shader::Shader& shader)
            {
                for (unsigned int i = 0; i < meshes.size(); i++)
                {
                    meshes[i].Draw(shader);
                }
            }

        private:
            std::vector<Mesh::Mesh> meshes;
            std::string directory;

            void loadModel(std::string path)
            {
                Assimp::Importer import;
                const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

                if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
                {
                    fprintf(stderr, "Error Reading file: %s", import.GetErrorString());
                    return;
                }

                directory = path.substr(0, path.find_last_of('/'));
            }

            void processNode(aiNode *node, const aiScene *scene)
            {
                // Process all the meshes for this node
                for (unsigned int i = 0; i < node->mNumMeshes; i++)
                {
                    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
                    meshes.push_back(processMesh(mesh, scene));
                }

                // Process all the children nodes for this node
                for (unsigned int i = 0; i < node->mNumChildren; i++)
                {
                    processNode(node->mChildren[i], scene);
                }
            }

            Mesh::Mesh processMesh(aiMesh *mesh, const aiScene *scene)
            {
                std::vector<glm::vec3> positions;
                std::vector<glm::vec3> normals;
                std::vector<glm::vec2> texCoords;
                std::vector<unsigned int> indices;

                std::vector<Mesh::Texture> textures;

                // Process vertices
                for (unsigned int i = 0; i < mesh->mNumVertices; i++)
                {
                    // Set in mesh vertex position
                    positions.push_back(glm::vec3(
                        mesh->mVertices[i].x,
                        mesh->mVertices[i].y,
                        mesh->mVertices[i].z
                    ));

                    // Set in mesh normals
                    normals.push_back(glm::vec3(
                        mesh->mNormals[i].x,
                        mesh->mNormals[i].y,
                        mesh->mNormals[i].z
                    ));

                    // Set in mesh texCoords
                    texCoords.push_back(glm::vec2(
                        mesh->mTextureCoords[0][i].x,
                        mesh->mTextureCoords[0][i].y
                    ));
                }

                for (unsigned int i = 0; i < mesh->mNumFaces; i++)
                {
                    aiFace face = mesh->mFaces[i];
                    for (unsigned int j = 0; j < face.mNumIndices; j++)
                    {
                        indices.push_back(face.mIndices[j]);
                    }
                }

                // Check if there are materials
                if (mesh->mMaterialIndex >= 0)
                {
                    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
                    Mesh::Texture albedo;
                    Mesh::Texture diffuse;
                    Mesh::Texture specular;
                    Mesh::Texture normal;
                    Mesh::Texture rough;
                }
            }
            
            Mesh::Texture loadMaterialTexture(aiMaterial *mat, aiTextureType type, std::string typeName)
            {
                if (mat->GetTextureCount(type) > 1)
                {
                    throw std::invalid_argument("Texture type has multiple textures. Please only use one for this program.");
                }
                
                Mesh::Texture texture;

                aiString str;
                mat->GetTexture(type, 0, &str);
            }
    };
}

#endif
