#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;
uniform vec3 uScale;

out vec2 fragTexCoord;
out vec3 fragNormal;

void main()
{
    gl_Position = vec4(pos, 1.0) * uWorldTransform * uViewProj;
    fragTexCoord = texCoord * uScale.xz * 0.5f;
    vec4 rotatetNormal = vec4(normal, 0.0) * uWorldTransform;
    fragNormal = rotatetNormal.xyz;
}