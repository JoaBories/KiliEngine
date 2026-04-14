#version 450 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform vec3 uScale;

out VertOut{
    vec2 texCoord;
} vertOut;

void main()
{
    gl_Position = vec4(pos, 1.0f);
    vertOut.texCoord = texCoord * uScale.xy;
}