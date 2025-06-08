#version 430 core
// Needed for intellisense to compile.
// It is thrown out when reading the file.
// Version is defined in shader.hpp

uniform int cascade0_dims;
uniform float cascade0_range;
uniform vec3 worldBounds;

struct RadianceProbe {
    vec3 worldPosition; // Where in the world this probe is
    ivec3 gridPosition; // Where in the grid of probes this probe is
};

struct CascadeLevel {
    uint level;
    float probeSpacing;
    float rayStartDistance;
    float rayEndDistance;

    vec3 gridDimensions;
    uint totalProbes;

    
};