#version 330 core

in vec2 fragTexCoord;
out vec4 outColor;

void main()
{
    outColor = vec4(fragTexCoord.x, fragTexCoord.y, 0, 1);
}

