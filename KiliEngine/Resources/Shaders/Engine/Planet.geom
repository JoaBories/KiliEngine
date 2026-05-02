#version 450 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;
uniform vec3 uCamPos;

in TeseOut{
    vec3 normal;
    vec3 spherePos;
    float height;
    float discardVert;
} teseOut[];

out GeomOut{
    vec3 normal;
    vec3 spherePos;
    vec3 worldPos;
    float height;
} geomOut;

void main() {

    if (teseOut[0].discardVert > 0.5f || teseOut[1].discardVert > 0.5f || teseOut[2].discardVert > 0.5f) return;

    vec4 pos1 = gl_in[0].gl_Position * uWorldTransform;
    vec4 pos2 = gl_in[1].gl_Position * uWorldTransform;
    vec4 pos3 = gl_in[2].gl_Position * uWorldTransform;

    vec3 Edge1 = pos1.xyz - pos2.xyz;
    vec3 Edge2 = pos1.xyz - pos3.xyz;

    vec3 triangleNormal = normalize(cross(Edge1, Edge2));
    
    gl_Position = pos1 * uViewProj;
    geomOut.normal = mix(triangleNormal, teseOut[0].normal, 0.5f);
    geomOut.spherePos = teseOut[0].spherePos;
    geomOut.worldPos = pos1.xyz;
    geomOut.height = teseOut[0].height;
    EmitVertex();

    gl_Position = pos2 * uViewProj;
    geomOut.normal = mix(triangleNormal, teseOut[1].normal, 0.5f);
    geomOut.spherePos = teseOut[1].spherePos;
    geomOut.worldPos = pos2.xyz;
    geomOut.height = teseOut[1].height;
    EmitVertex();

    gl_Position = pos3 * uViewProj;
    geomOut.normal = mix(triangleNormal, teseOut[2].normal, 0.5f);
    geomOut.spherePos = teseOut[2].spherePos;
    geomOut.worldPos = pos3.xyz;
    geomOut.height = teseOut[2].height;
    EmitVertex();

    EndPrimitive();
}