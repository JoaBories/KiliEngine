#version 450 core

layout(vertices = 3) out;

in VertOut{
    vec2 texCoord;
    vec3 worldPos;
    vec3 normal;
} vertOut[];

out TescOut{
    vec2 texCoord;
    vec3 worldPos;
    vec3 normal;
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
    
    tescOut[gl_InvocationID].texCoord = vertOut[gl_InvocationID].texCoord;
    tescOut[gl_InvocationID].worldPos = vertOut[gl_InvocationID].worldPos;
    tescOut[gl_InvocationID].normal = vertOut[gl_InvocationID].normal;
}
