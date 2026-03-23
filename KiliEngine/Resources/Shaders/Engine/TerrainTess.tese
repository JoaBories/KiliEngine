#version 450 core

layout(quads, equal_spacing, ccw) in;

uniform sampler2D uTexture;
uniform mat4 uViewProj;

uniform float uHeightScale;

in TescOut{
    vec2 texCoord;
    vec3 worldPos;
    vec3 normal;
} teseIn[];

out TeseOut{
    vec2 texCoord;
} teseOut;

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2, vec2 v3)
{
    vec2 bottom = mix(v0, v1, gl_TessCoord.x);
    vec2 top    = mix(v3, v2, gl_TessCoord.x);
    return mix(bottom, top, gl_TessCoord.y);
}

void main(void)
{
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;

    vec3 p0 = teseIn[0].worldPos;
    vec3 p1 = teseIn[1].worldPos;
    vec3 p2 = teseIn[2].worldPos;
    vec3 p3 = teseIn[3].worldPos;
    
    vec3 p = p0 * (1.0 - u) * (1.0 - v) +
             p1 * u * (1.0 - v) +
             p3 * v * (1.0 - u) +
             p2 * u * v;
    
    vec2 texCoord = interpolate2D(
        teseIn[0].texCoord, teseIn[1].texCoord, teseIn[2].texCoord, teseIn[3].texCoord
    );
    
    teseOut.texCoord = texCoord;

    p += texture(uTexture, texCoord).r * uHeightScale * teseIn[0].normal;
    
    gl_Position = vec4(p , 1.0) * uViewProj;
}