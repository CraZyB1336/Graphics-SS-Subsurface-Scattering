#version 430 core

in layout(location = 0) vec3 pos;
in layout(location = 1) vec3 norm;
in layout(location = 2) vec2 texCoords;

// Model transformation matrix
uniform mat4 M;

// View Projection matrix
uniform mat4 VP;

// Normal matrix
uniform mat3 NM;

out layout(location = 0) vec3 pos_out;
out layout(location = 1) vec3 norm_out;
out layout(location = 2) vec2 texCoords_out;

void main()
{
    // Move position to world space position
    vec4 modelPos = M * vec4(pos, 1.0);
    pos_out = modelPos.xyz;

    // Move normal to world space normal
    vec3 modelNorm = NM * normalize(norm);
    norm_out = modelNorm;

    texCoords_out = texCoords;

    // NDC = VP * M * vertex
    gl_Position = VP * M * vec4(pos, 1.0f);
}