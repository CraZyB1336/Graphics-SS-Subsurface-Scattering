#ifndef RADCAS_COMMONVARS_HPP
#define RADCAS_COMMONVARS_HPP
#pragma once

#include <glm/glm.hpp>

#include "../classes/shader.hpp"

extern Shader::Shader* cascadeShader;

extern unsigned int cascadeAmount;
extern int cascade0Range;
extern int cascade0Spacing;
extern unsigned int cascadeWidth;
extern unsigned int cascadeHeight;
extern std::vector<unsigned int> cascadeTextures;
extern glm::vec2 renderResolution2D; // Resolution to render 

#endif