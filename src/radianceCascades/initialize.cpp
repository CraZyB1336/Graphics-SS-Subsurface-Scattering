#include "commonVars.hpp"
#include "initialize.hpp"

#include "../util/textureHandler.hpp"

void initCascade()
{
    cascadeShader = new Shader::Shader();
    cascadeShader->attach("../resources/shaders/radianceCascades/cascade.comp");
    cascadeShader->link();

    cascadeAmount = calculateCascadeCount(renderResolution2D.x, renderResolution2D.y, cascade0Range);

    // Ensure enough pixels to store every probe
    // Texture size is equal for ease of merging
    float ratio = (float) renderResolution2D.x / (float) renderResolution2D.y;

    cascadeWidth = 512 * ratio;
    cascadeHeight = 512;

    for (unsigned int i = 0; i < cascadeAmount; i++)
    {
        unsigned int texture = generateEmptyTexture(cascadeWidth, cascadeHeight);
        cascadeTextures.push_back(texture);
    }
}

unsigned int calculateCascadeCount(unsigned int width, unsigned int height, float startingInterval)
{
    float diagonal = sqrt(pow(width, 2) + pow(height, 2));
    int factor = ceil(log(diagonal/startingInterval) / log(4.0));

    float intervalStart = (startingInterval * (1.0 - pow(4.0, factor))) / (1.0 - 4.0);

    return ceil(log(intervalStart) / log(4));
}