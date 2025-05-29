#version 430 core

in layout(location = 0) vec3 pos;
in layout(location = 1) vec3 norm;
in layout(location = 2) vec2 texCoords;
in layout(location = 3) vec3 tangent;
in layout(location = 4) vec3 biTangent;

// Model transformation matrix
uniform mat4 M;

// View Projection matrix
uniform mat4 VP;

// Normal matrix
uniform mat3 NM;

out layout(location = 0) vec3 pos_out;
out layout(location = 1) vec3 norm_out;
out layout(location = 2) vec2 texCoords_out;
out layout(location = 3) mat3 TBN;

void main()
{
    // TBN construction
    vec3 modelNorm = normalize(NM * norm);
    vec3 modelTangent = normalize(NM * tangent);
    vec3 modelBiTangent = normalize(NM * biTangent);

    TBN = mat3(
        modelTangent,
        modelBiTangent,
        modelNorm
    );

    // Move position to world space position
    vec4 modelPos = M * vec4(pos, 1.0);
    pos_out = modelPos.xyz;

    // Move normal to world space normal
    norm_out = modelNorm;

    texCoords_out = texCoords;

    // NDC = VP * M * vertex
    gl_Position = VP * M * vec4(pos, 1.0f);
}