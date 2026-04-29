#version 450 core

layout (triangles) in;
layout (line_strip, max_vertices = 2) out;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

in TeseOut{
    vec3 normal;
    vec3 spherePos;
    float height;
} teseOut[];

out GeomOut{
    vec3 normal;
    float height;
} geomOut;

void main() {
    float centerHeight = (teseOut[0].height + teseOut[0].height + teseOut[0].height) / 3.0f;

    vec4 pos1 = gl_in[0].gl_Position.xyzw * uWorldTransform;
    vec4 pos2 = gl_in[1].gl_Position.xyzw * uWorldTransform;
    vec4 pos3 = gl_in[2].gl_Position.xyzw * uWorldTransform;

    vec3 Edge1 = pos1.xyz - pos2.xyz;
    vec3 Edge2 = pos1.xyz - pos3.xyz;

    geomOut.normal = normalize(cross(Edge1, Edge2));
    
    if(centerHeight <= 0.5f && centerHeight > 0.1f && !(centerHeight < 0.0f))
    {
        vec4 basePos = (pos1 + pos2 + pos3) / 3.0f;
        vec4 topPos = basePos + vec4(geomOut.normal * -0.1f, 0.0f);
        
        gl_Position = basePos * uViewProj;
        geomOut.height = 0.0f;
        EmitVertex();
        
        gl_Position = topPos * uViewProj;
        geomOut.height = 1.0f;
        EmitVertex();
        
        EndPrimitive();
    }
}