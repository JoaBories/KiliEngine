#version 450 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;
uniform vec3 uCamDir;

in TeseOut{
    vec2 texCoord;
    float height;
    float perlin;
} teseOut[];

out GeomOut{
    vec2 texCoord;
    vec3 normal;
    float height;
    float perlin;
    float steepness;
} geomOut;

void main() {
    vec4 pos1 = gl_in[0].gl_Position.xyzw * uWorldTransform;
    vec4 pos2 = gl_in[1].gl_Position.xyzw * uWorldTransform;
    vec4 pos3 = gl_in[2].gl_Position.xyzw * uWorldTransform;
    
    vec3 Edge1 = pos1.xyz - pos2.xyz;
    vec3 Edge2 = pos1.xyz - pos3.xyz;
    
    geomOut.normal = normalize(cross(Edge1, Edge2));
    
    if (dot(geomOut.normal, uCamDir) > -0.0f) {

        geomOut.height = (teseOut[0].height + teseOut[1].height + teseOut[2].height) / 3.0f;
        geomOut.perlin = (teseOut[0].perlin + teseOut[1].perlin + teseOut[2].perlin) / 3.0f;

        gl_Position = pos1 * uViewProj;
        geomOut.texCoord = teseOut[0].texCoord;
        geomOut.height = teseOut[0].height;
        geomOut.perlin = teseOut[0].perlin;
        geomOut.steepness = 0;
        EmitVertex();

        gl_Position = pos2 * uViewProj;
        geomOut.texCoord = teseOut[1].texCoord;
        geomOut.height = teseOut[1].height;
        geomOut.perlin = teseOut[1].perlin;
        geomOut.steepness = 0;
        EmitVertex();

        gl_Position = pos3 * uViewProj;
        geomOut.texCoord = teseOut[2].texCoord;
        geomOut.height = teseOut[2].height;
        geomOut.perlin = teseOut[2].perlin;
        geomOut.steepness = 0;
        EmitVertex();

        EndPrimitive();
    }
}