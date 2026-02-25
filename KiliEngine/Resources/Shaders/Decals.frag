#version 330 core

in vec2 fragTexCoord;
out vec4 outColor;

uniform sampler2D uTexture;

vec4 color;

void main()
{
    color = texture(uTexture, fragTexCoord);
    if(color.a < 0.25)
        discard;
    outColor = color;
}