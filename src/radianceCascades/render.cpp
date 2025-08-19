#include <glm/glm.hpp>

#include "commonVars.hpp"
#include "render.hpp"

void renderCascade()
{
    cascadeShader->activate();

    // Iterate through each cascade
    // Naive approach, iterate through it each frame.
    const unsigned int WORK_GROUP_SIZE_XY = 16;
    int dispatchX = (cascadeWidth + WORK_GROUP_SIZE_XY - 1) / WORK_GROUP_SIZE_XY;
    int dispatchY = (cascadeHeight + WORK_GROUP_SIZE_XY - 1) / WORK_GROUP_SIZE_XY;

    glUniform2i(cascadeShader->getUniformFromName("renderResolution"), renderResolution2D.x, renderResolution2D.y);
    glUniform2i(cascadeShader->getUniformFromName("cascadeTextureDimensions"), cascadeWidth, cascadeHeight);

    for (unsigned int i = 0; i < cascadeAmount; i++)
    {
        glUniform1ui(cascadeShader->getUniformFromName("cascadeIndex"), i);

        int probeSpacing = pow(cascade0Spacing, i + 1);
        int probeRayAmount = probeSpacing * probeSpacing;
        float probeRayStart = (cascade0Range * (1 - pow(4, i))) / (1 - 4);
        float probeRayEnd = cascade0Range * pow(4, i);

        glUniform1i(cascadeShader->getUniformFromName("probeSpacing"), probeSpacing);
        glUniform1i(cascadeShader->getUniformFromName("probeRayAmount"), probeRayAmount);
        glUniform2f(cascadeShader->getUniformFromName("probeRayRange"), probeRayStart, probeRayEnd);
        
        glBindImageTexture(0, cascadeTextures[0], 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

        glDispatchCompute(dispatchX, dispatchY, 1);

        // Ensures this one completes before the next one starts.
        glMemoryBarrier(GL_TEXTURE_FETCH_BARRIER_BIT);
    }
}