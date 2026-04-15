#version 450 core

layout (triangles) in;
layout (line_strip, max_vertices = 2) out;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

in TeseOut{
    vec2 texCoord;
    vec3 normal;
    float height;
    float perlin;
    float steepness;
} teseOut[];

out GeomOut{
    vec3 normal;
    float height;
} geomOut;

void main() {
    
    float centerSteepness = (teseOut[0].steepness + teseOut[0].steepness + teseOut[0].steepness) / 3.0f;
    float centerPerlin = (teseOut[0].perlin + teseOut[0].perlin + teseOut[0].perlin) / 3.0f;
    
    if(centerSteepness <= 5.0f && centerPerlin <= 0.5f && centerPerlin > 0.1f)
    {
        vec4 centerPos = (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3.0f;
        vec4 centerNormal = vec4((teseOut[0].normal + teseOut[1].normal + teseOut[2].normal) / 3.0f, 0.0f).xyzw;
        
        gl_Position = centerPos;
        geomOut.normal = (centerNormal * uWorldTransform).xyz;
        geomOut.height = 0.0f;
        EmitVertex();
        gl_Position = centerPos + centerNormal * 0.05f * uWorldTransform * uViewProj;
        geomOut.normal = (centerNormal * uWorldTransform).xyz;
        geomOut.height = 1.0f;
        EmitVertex();
        EndPrimitive();
    }
}