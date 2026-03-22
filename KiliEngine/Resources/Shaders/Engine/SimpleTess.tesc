#version 450 core

layout(vertices = 3) out;

in VertOut{
    vec2 texCoord;
} tescIn[];

out TescOut{
    vec2 texCoord;
} tescOut[];

void main(void)
{
    if (gl_InvocationID == 0)
    {
        gl_TessLevelInner[0] = 5.0f;
        gl_TessLevelOuter[0] = 5.0f;
        gl_TessLevelOuter[1] = 5.0f;
        gl_TessLevelOuter[2] = 5.0f;
    }
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    tescOut[gl_InvocationID].texCoord = tescIn[gl_InvocationID].texCoord;
}
