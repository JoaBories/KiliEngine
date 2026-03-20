#version 450 core
//Work better with an already subdivided plane

layout(vertices = 3) out;

in VertOut{
    vec4 color;
    vec2 texCoord;
} tescIn[];

out TescOut{
    vec4 color;
    vec2 texCoord;
} tescOut[];

float maxTessLevel = 128.0f;
float tessLevel = 1024.0f;

float DistanceTessLevel(vec4 v0, vec4 v1, vec4 v2)
{
    vec4 mid = (v0 + v1 + v2) / 3.0;
    return clamp(tessLevel / length(mid), 1.0f, maxTessLevel); // TessLevel by unit of distance
}

void main(void)
{
    if (gl_InvocationID == 0)
    {
        vec4 p0 = gl_in[0].gl_Position;
        vec4 p1 = gl_in[1].gl_Position;
        vec4 p2 = gl_in[2].gl_Position;
        
        float tessLevel = DistanceTessLevel(p0, p1, p2);

        // outer levels = one per edge
        gl_TessLevelOuter[0] = tessLevel;
        gl_TessLevelOuter[1] = tessLevel;
        gl_TessLevelOuter[2] = tessLevel;

        // inner = average of outer
        gl_TessLevelInner[0] = tessLevel;
    }
    
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    tescOut[gl_InvocationID].color = tescIn[gl_InvocationID].color;
    tescOut[gl_InvocationID].texCoord = tescIn[gl_InvocationID].texCoord;
}
