#include <glm/gtc/type_ptr.hpp>

#include "commonVars.hpp"
#include "render.hpp"

void renderNodes(Mesh::Mesh* node, Shader::Shader &shader);

/**
 * @brief Initializes and renders each frame.
 */
void renderFrame()
{
    // Have to render each mesh's draw function.
    // For now just manually activate
    mainShader->activate();

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