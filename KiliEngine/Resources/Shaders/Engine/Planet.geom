#version 450 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;
uniform vec3 uCamDir;

in TeseOut{
    vec3 normal;
    vec3 spherePos;
    float height;
} teseOut[];

out GeomOut{
    vec3 normal;
    vec3 spherePos;
    float steepness;
    float height;
} geomOut;

void main() {    
    vec3 centerNormal = normalize(teseOut[0].normal + teseOut[0].normal + teseOut[0].normal);
    
    if (dot(centerNormal, uCamDir) < 0.0f) return; // culling backside of the planet

    vec4 pos1 = gl_in[0].gl_Position.xyzw * uWorldTransform;
    vec4 pos2 = gl_in[1].gl_Position.xyzw * uWorldTransform;
    vec4 pos3 = gl_in[2].gl_Position.xyzw * uWorldTransform;

    vec3 Edge1 = pos1.xyz - pos2.xyz;
    vec3 Edge2 = pos1.xyz - pos3.xyz;

    vec3 triangleNormal = normalize(cross(Edge1, Edge2));
    
    gl_Position = pos1 * uViewProj;
    geomOut.normal = mix(triangleNormal, teseOut[0].normal, 0.2f);
    geomOut.spherePos = teseOut[0].spherePos;
    geomOut.steepness = 0;
    geomOut.height = teseOut[0].height;
    EmitVertex();

    gl_Position = pos2 * uViewProj;
    geomOut.normal = mix(triangleNormal, teseOut[1].normal, 0.2f);
    geomOut.spherePos = teseOut[1].spherePos;
    geomOut.steepness = 0;
    geomOut.height = teseOut[0].height;
    EmitVertex();

    gl_Position = pos3 * uViewProj;
    geomOut.normal = mix(triangleNormal, teseOut[2].normal, 0.2f);
    geomOut.spherePos = teseOut[2].spherePos;
    geomOut.steepness = 0;
    geomOut.height = teseOut[0].height;
    EmitVertex();

    EndPrimitive();
}