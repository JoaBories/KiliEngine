#version 450 core

layout(vertices = 3) out;

void main(void)
{
    if (gl_InvocationID == 0)
    {
        gl_TessLevelInner[0] = 64.0f;
        gl_TessLevelOuter[0] = 64.0f;
        gl_TessLevelOuter[1] = 64.0f;
        gl_TessLevelOuter[2] = 64.0f;
    }
    
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}
