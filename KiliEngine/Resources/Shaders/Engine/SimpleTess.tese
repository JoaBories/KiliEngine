#version 450 core

layout(triangles, fractional_even_spacing, ccw) in;
in TescOut{
    vec4 color;
    vec2 texCoord;
} teseIn[];

out TeseOut{
    vec4 color;
    vec2 texCoord;
} teseOut;

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
    return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

void main(void)
{
    gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position +
    gl_TessCoord.y * gl_in[1].gl_Position +
    gl_TessCoord.z * gl_in[2].gl_Position);
    teseOut.color = mix(teseIn[0].color, teseIn[1].color, gl_TessCoord.x);
    teseOut.texCoord = interpolate2D(teseIn[0].texCoord, teseIn[1].texCoord, teseIn[2].texCoord);
}
