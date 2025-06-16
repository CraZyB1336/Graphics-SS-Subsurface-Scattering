#include <glm/gtc/type_ptr.hpp>

#include "commonVars.hpp"
#include "render.hpp"
#include "../radianceCascades/render.hpp"
#include "../radianceCascades/commonVars.hpp"

void renderNodes(Mesh::Mesh* node, Shader::Shader &shader);

/**
 * @brief Initializes and renders each frame.
 */
void renderFrame()
{
    // Have to render each mesh's draw function.
    // For now just manually activate
    // mainShader->activate();
    renderCascade();

    screenShader->activate();

    // Visualize cascade texture
    glBindImageTexture(0, cascadeTextures[0], 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA32F);
    // Pass in VP
    glUniformMatrix4fv(mainShader->getUniformFromName("VP"), 1, GL_FALSE, glm::value_ptr(VP));

    renderNodes(rootNode, *mainShader);
}

void renderNodes(Mesh::Mesh* node, Shader::Shader &shader)
{
    node->Draw(shader);

    for (Mesh::Mesh* child : node->children)
    {
        renderNodes(child, shader);
    }
}