#version 330 core

layout(location = 0) in vec3 pos;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

void main()
{
    gl_Position = vec4(pos, 1.0) * uWorldTransform * uViewProj;
}