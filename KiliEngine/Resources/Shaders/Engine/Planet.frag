#version 450 core

out vec4 outColor;

in TeseOut{
    vec2 texCoord;
    vec3 normal;
} teseOut;

uniform sampler2D uTexture;

void main()
{
    outColor = texture(uTexture, teseOut.texCoord);
}
