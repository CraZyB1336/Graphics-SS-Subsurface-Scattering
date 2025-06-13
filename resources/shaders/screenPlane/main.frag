#version 430 core

in layout(location = 0) vec3 pos;
in layout(location = 2) vec2 texCoords;

out vec4 color;

void main()
{
    ivec2 pixel = ivec2(gl_FragCoord.xy);

    if (((pixel.x / 100) + (pixel.y / 100)) % 2 == 0)
    {
        color = vec4(1.0, 0.0, 1.0, 1.0);   
    }
    else
    {
        color = vec4(0.0, 0.5, 1.0, 1.0);
    }
}