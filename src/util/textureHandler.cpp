#include "stb_image/stb_image.h"
#include <glad/glad.h>
#include <string>
#include <fstream>

#include "textureHandler.hpp"


/**
 * @brief Generate a textureID from a given file path.
 *        Assumes that the file path is local or absolute.
 * @param filePath The file path for the texture.
 */
unsigned int generateTextureFromFile(std::string filePath)
{
    std::ifstream file(filePath);
    if (!file.good())
    {
        fprintf(stderr, "ERROR: File does not exist or cannot be accessed: %s\n", filePath.c_str());
        return 0;
    }

    int width, height, channels;
    unsigned char *data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);

    if (!data)
    {
        fprintf(stderr, "Texture was not found: %s\n", filePath.c_str());
    }

    // Generate the textureBuffer
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Wrapping filters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    // Release the image    \0/ - "i am free"
    stbi_image_free(data);
    return textureID;
}