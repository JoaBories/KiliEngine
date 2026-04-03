#version 450 core

layout(triangles, equal_spacing, ccw) in;

uniform mat4 uViewProj;

in TescOut{
    vec2 texCoord;
    vec3 worldPos;
    vec3 normal;
} tescOut[];

out TeseOut{
    vec2 texCoord;
    vec3 normal;
} teseOut;

float interpolate(float f0, float f1, float f2)
{
    return gl_TessCoord.x * f0 + gl_TessCoord.y * f1 + gl_TessCoord.z * f2;
}

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
    return vec2(interpolate(v0.x, v1.x, v2.x), interpolate(v0.y, v1.y, v2.y));
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)
{
    return vec3(interpolate(v0.x, v1.x, v2.x), interpolate(v0.y, v1.y, v2.y), interpolate(v0.z, v1.z, v2.z));
}

vec4 interpolate4D(vec4 v0, vec4 v1, vec4 v2, float w)
{
    return vec4(interpolate(v0.x, v1.x, v2.x), interpolate(v0.y, v1.y, v2.y), interpolate(v0.z, v1.z, v2.z), w);
}

void main(void)
{
    gl_Position = interpolate4D(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_in[2].gl_Position, 1.0f) * uViewProj;
    teseOut.texCoord = interpolate2D(tescOut[0].texCoord, tescOut[1].texCoord, tescOut[2].texCoord);
    teseOut.normal = interpolate3D(tescOut[0].normal, tescOut[1].normal, tescOut[2].normal);
}
