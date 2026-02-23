#version 330 core

in vec3 fragNormal;
out vec4 outColor;

void main()
{
    outColor = vec4(fragNormal.x, fragNormal.y, fragNormal.z, 1);
}

