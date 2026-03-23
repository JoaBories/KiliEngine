#version 450 core

layout(quads, equal_spacing, ccw) in;

uniform sampler2D uTexture;

in TescOut{
    vec2 texCoord;
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

    vec4 p0 = gl_in[0].gl_Position;
    vec4 p1 = gl_in[1].gl_Position;
    vec4 p2 = gl_in[2].gl_Position;
    vec4 p3 = gl_in[3].gl_Position;
    
    vec4 p = p0 * (1.0 - u) * (1.0 - v) +
             p1 * u * (1.0 - v) +
             p3 * v * (1.0 - u) +
             p2 * u * v;
    
    vec2 texCoord = interpolate2D(
        teseIn[0].texCoord, teseIn[1].texCoord, teseIn[2].texCoord, teseIn[3].texCoord
    );

    float zDisplacement = texture(uTexture, texCoord).r * 4.0;
    p.z += zDisplacement;
    
    gl_Position = p;
    
    teseOut.texCoord = texCoord;
}