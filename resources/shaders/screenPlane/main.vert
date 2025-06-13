#version 430 core

in layout(location = 0) vec3 pos;
in layout(location = 2) vec2 texCoords;

out layout(location = 2) vec2 texCoords_out;

void main()
{

    texCoords_out = texCoords;

    gl_Position = vec4(pos, 1.0f);
}