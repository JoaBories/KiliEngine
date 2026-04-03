#version 450 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 uWorldTransform;
uniform vec3 uScale;
uniform float uTime;

float pRotateSpeed = 0.05f; // revolution by second

out VertOut{
    vec2 texCoord;
    vec3 worldPos;
    vec3 normal;
} vertOut;

vec3 rotateZ(vec3 v, float angle)
{
    float c = cos(angle);
    float s = sin(angle);

    return vec3( v.x * c + v.y * s,
    v.x * -s + v.y * c,
    v.z );
}

void main()
{
    float rotation = fract(uTime * pRotateSpeed) * 6.2831853f;

    gl_Position = vec4(rotateZ(pos, rotation), 1.0f) * uWorldTransform;
    vertOut.worldPos = gl_Position.xyz;
    vertOut.texCoord = texCoord * uScale.xy;
    vertOut.normal = rotateZ(normal, rotation);
}