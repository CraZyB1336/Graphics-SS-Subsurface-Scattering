#version 430 core

in layout(location = 0) vec3 pos;
in layout(location = 2) vec2 texCoords;

out vec4 color;

layout(binding = 0, rgba32f) uniform image2D cascadeTexture;

void main()
{
    ivec2 size = imageSize(cascadeTexture);
    ivec2 pixelCoord = ivec2(gl_FragCoord);

    if (pixelCoord.x > size.x || pixelCoord.y > size.y)
    {
        return;
    }

    vec4 cascadeData = imageLoad(cascadeTexture, pixelCoord);

    color = vec4(cascadeData.xyz, 1.0);
}