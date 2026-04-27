#version 450 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;
uniform vec3 uScale;

out VertOut{
    vec2 texCoord;
} vert_out;

void main()
{
    gl_Position = vec4(pos, 1.0) * uWorldTransform * uViewProj;
    vert_out.texCoord = texCoord * uScale.xy;
}