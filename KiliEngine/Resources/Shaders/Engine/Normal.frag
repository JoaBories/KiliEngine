#version 450 core

in vec3 fragNormal;
out vec4 outColor;

void main()
{
    outColor = vec4((fragNormal + 1) / 2, 1);
}

