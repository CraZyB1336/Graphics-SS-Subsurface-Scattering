#version 430 core

in layout(location = 0) vec3 pos;

out layout(location = 0) vec3 pos_out;

void main()
{
    pos_out = pos;
    gl_Position = vec4(pos, 1.0f);
}