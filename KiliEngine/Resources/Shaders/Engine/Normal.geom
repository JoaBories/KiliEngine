#version 450 core

layout (triangles) in;
layout (line_strip, max_vertices = 2) out;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

in vec3 geomNormal[];
out vec3 fragNormal;

void main() {
    vec4 centerPos = (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3.0f;
    vec4 centerNormal = vec4((geomNormal[0] + geomNormal[1] + geomNormal[2]) / 3.0f, 0.0f).xzyw;
    gl_Position = centerPos;
    fragNormal = (centerNormal * uWorldTransform).xyz;
    EmitVertex();
    gl_Position = centerPos + centerNormal * 0.3f * uWorldTransform * uViewProj;
    fragNormal = (centerNormal * uWorldTransform).xyz;
    EmitVertex();
    EndPrimitive();
}