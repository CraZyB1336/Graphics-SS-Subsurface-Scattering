#version 430 core

in layout(location = 0) vec3 pos;
in layout(location = 1) vec3 norm;
in layout(location = 2) vec2 texCoords;
in layout(location = 3) mat3 TBN;

uniform bool textureDiffuseBool;
uniform bool textureSpecularBool;
uniform bool textureNormalBool;
uniform bool textureRoughBool;

uniform sampler2D textureDiffuse; // Actual base color
uniform sampler2D textureSpecular;
uniform sampler2D textureNormal;
uniform sampler2D textureRough;

out vec4 color;

void main()
{
    vec4 textureColor = texture(textureDiffuse, texCoords);
    vec3 textureNormal = TBN * (texture(textureNormal, texCoords).xyz * 2.0 - 1.0);

    color = vec4(textureNormal, 1.0);
}