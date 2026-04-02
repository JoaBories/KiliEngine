#version 450

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;
uniform vec2 uSize;
uniform int uInstanceCount;

out VertOut{
    vec2 texCoord;
} vert_out;

void main() {
    int sqrInstance = int(sqrt(float(uInstanceCount)));
    
    vec4 offset = vec4(float(gl_InstanceID / sqrInstance), float(gl_InstanceID % sqrInstance), 0.0f, 0.0f);
    offset = (offset / sqrInstance) * vec4(uSize, 0.0f, 0.0f) - vec4(uSize, 0.0f, 0.0f) / 2.0f;
    gl_Position = (vec4(pos, 1.0f) + offset) * uWorldTransform * uViewProj;
    vert_out.texCoord = texCoord;
}