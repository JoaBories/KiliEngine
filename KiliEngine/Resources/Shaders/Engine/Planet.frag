#version 450 core

out vec4 outColor;

in TeseOut{
    vec2 texCoord;
    vec3 normal;
} teseOut;

void main()
{
    outColor = vec4(1,1,1,1);
}