#version 450 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 uWorldTransform;
uniform vec3 uScale;

out VertOut{
    vec2 texCoord;
    vec3 worldPos;
    vec3 normal;
} vert_out;

void main()
{
    vert_out.worldPos = (vec4(pos, 1.0) * uWorldTransform).xyz;
    vert_out.texCoord = texCoord * uScale.xy;
    vert_out.normal = normal;
    gl_Position = vec4(vert_out.worldPos, 1.0);
}