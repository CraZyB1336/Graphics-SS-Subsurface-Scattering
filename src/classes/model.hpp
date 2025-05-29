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
#include "../util/textureHandler.hpp"

namespace Model
{
    class Model
    {
        public:
            Mesh::Mesh* root;

            Model(char *path)
            {
                loadModel(path);
                printf("Successfully loaded: %s\n", path);
            }
        private:
            std::vector<Mesh::Mesh*> meshes;
            std::string directory;
            std::vector<Mesh::Texture> textures_loaded;

            void loadModel(std::string path)
            {
                Assimp::Importer import;
                const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

                if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
                {
                    fprintf(stderr, "Error Reading file: %s", import.GetErrorString());
                    return;
                }

                root = new Mesh::Mesh();
                root->type = Mesh::NO_GEOMETRY;

                directory = path.substr(0, path.find_last_of('/'));

                processNode(scene->mRootNode, scene);
            }

            void processNode(aiNode *node, const aiScene *scene)
            {
                // Process all the meshes for this node
                printf("Mesh name: %s\n", node->mName.C_Str());
                for (unsigned int i = 0; i < node->mNumMeshes; i++)
                {
                    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
                    meshes.push_back(processMesh(mesh, scene));
                    printf("\n");
                }

                // Process all the children nodes for this node
                for (unsigned int i = 0; i < node->mNumChildren; i++)
                {
                    processNode(node->mChildren[i], scene);
                }
            }

            Mesh::Mesh* processMesh(aiMesh *mesh, const aiScene *scene)
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
                    Mesh::Texture diffuse = loadMaterialTexture(material, aiTextureType_DIFFUSE, "textureDiffuse");
                    Mesh::Texture specular = loadMaterialTexture(material, aiTextureType_SPECULAR, "textureSpecular");
                    Mesh::Texture normal = loadMaterialTexture(material, aiTextureType_HEIGHT, "textureNormal");
                    Mesh::Texture rough = loadMaterialTexture(material, aiTextureType_DIFFUSE_ROUGHNESS, "textureRough");

                    if (diffuse.id != 0) textures.push_back(diffuse);
                    if (specular.id != 0) textures.push_back(specular);
                    if (normal.id != 0) textures.push_back(normal);
                    if (rough.id != 0) textures.push_back(rough);
                }

                Mesh::Mesh* processedMesh = new Mesh::Mesh(positions, normals, texCoords, indices, textures);
                root->children.push_back(processedMesh);

                return processedMesh;
            }
            
            Mesh::Texture loadMaterialTexture(aiMaterial *mat, aiTextureType type, std::string typeName)
            {
                if (mat->GetTextureCount(type) > 1)
                {
                    throw std::invalid_argument("Texture type has multiple textures. Please only use one for this program.");
                }

                if (mat->GetTextureCount(type) == 0)
                {
                    Mesh::Texture texture;
                    texture.id = 0;
                    texture.type = "NONE";

                    printf("Found zero textures for: %s\n", typeName.c_str());

                    return texture;
                }

                aiString str;
                mat->GetTexture(type, 0, &str);
                if (type == aiTextureType_HEIGHT)
                {
                    printf("Texture Loaded for normals: %s\n", str.C_Str());
                }
                else if (type == aiTextureType_DIFFUSE)
                {
                    printf("Texture Loaded for diffuse: %s\n", str.C_Str());
                }
                else if (type == aiTextureType_SPECULAR)
                {
                    printf("Texture Loaded for specular: %s\n", str.C_Str());
                }
                if (type == aiTextureType_DIFFUSE_ROUGHNESS)
                {
                    printf("Texture Loaded for diffuse roughness: %s\n", str.C_Str());
                }


                for (unsigned int i = 0; i < textures_loaded.size(); i++)
                {
                    if (std::strcmp(textures_loaded[i].path.data(), str.C_Str()) == 0)
                    {
                        return textures_loaded[i];
                    }
                }
                
                Mesh::Texture texture;
                texture.id = generateTextureFromFile(directory + '/' + str.C_Str());
                texture.type = typeName;
                texture.path = str.C_Str();
                textures_loaded.push_back(texture);
                return texture;
            }
    };
}

#endif
