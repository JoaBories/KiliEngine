#version 450 core

out vec4 outColor;

in TeseOut{
    vec2 texCoord;
    vec3 normal;
    float perlin;
} teseOut;

uniform sampler2D uTexture;

void main()
{
    vec3 perlinColor = vec3(teseOut.perlin * 0.5f + 0.5f);
    outColor = vec4(perlinColor, 1.0f);
}
