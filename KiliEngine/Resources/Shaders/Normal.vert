#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

out vec3 fragNormal;
void main()
{
    gl_Position = vec4(pos, 1.0) * uWorldTransform * uViewProj;
    fragNormal = (normal + 1) / 2;
}