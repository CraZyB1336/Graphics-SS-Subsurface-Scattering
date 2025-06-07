#ifndef COMMONVARS_RADCAS_HPP
#define COMMONVARS_RADCAS_HPP
#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace RadCas {
    const unsigned int CASCADE_0_DIM = 2; // This is to define the space between each cascade 0 probe, you can consider this pixels in pixel space.
    const unsigned int CASCADE_0_RAY_LEN = 1;
    const unsigned int CASCADE_0_RAY_AMOUNT = 4;

    const unsigned int CASCADE_LEVELS = 3;
    const unsigned int CASCADE_LEVEL_FACTOR = 2.0;
    const unsigned int CASCADE_RAY_FACTOR = 4.0;

    struct RadianceProbe {
        glm::vec3 worldPosition; // Where in the world this probe is
        glm::ivec3 gridCoordinate; // Where in terms of the probe grid this probe is, useful for neighbour detection.
    };

    struct CascadeLevel {
        unsigned int level;
        float probeSpacing; // The space between each probe. This is equal in all distances for simplicity sake.
        float rayStartDistance; // Defines the radius for where the ray should start. Basically defining the inner hemisphere for each probe.
        float rayEndDistance; // Defines the radius for where the ray should end its ray. The outer hemisphere for each probe.

        glm::vec3 gridDimensions; // Defines the world size to place probes. In 2D a similar approach would be to use the screen size.
        unsigned int totalProbes;

        std::vector<RadianceProbe> probes;
    };
}

extern std::vector<RadCas::CascadeLevel> cascades;
extern glm::vec3 worldBounds;

#endif