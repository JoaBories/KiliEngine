#version 330 core

in vec2 fragTexCoord;
out vec4 outColor;

uniform sampler2D uTexture;

vec4 color;

void main()
{
    color = texture(uTexture, fragTexCoord);
    outColor = vec4(color.r, color.g, color.b, color.a);
}

