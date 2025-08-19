#include "../util/specs.hpp"
#include "commonVars.hpp"

Shader::Shader* cascadeShader;

unsigned int cascadeAmount;
int cascade0Range = 1; // Range is the ray length
int cascade0Spacing = 2; // Spacing is how many pixels it takes in x and y respectively
unsigned int cascadeWidth;
unsigned int cascadeHeight;
std::vector<unsigned int> cascadeTextures;
glm::vec2 renderResolution2D = {windowWidth, windowHeight};
