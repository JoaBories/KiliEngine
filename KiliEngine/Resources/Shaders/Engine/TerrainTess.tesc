#version 450 core
//Work better with an already subdivided plane

layout(vertices = 4) out;

in VertOut{
    vec2 texCoord;
    vec3 worldPos;
    vec3 normal;
} tescIn[];

out TescOut{
    vec2 texCoord;
    vec3 worldPos;
    vec3 normal;
} tescOut[];

uniform vec3 uCamPos;

float MinTess = 1.0;        // minimum tessellation level
float MaxTess = 64.0;      // maximum tessellation level 
float MinDist = 25.0;        // distance at which max tessellation kicks in
float MaxDist = 150.0;       // distance at which min tessellation kicks in 

float tessLevel(float dist) {
    float t = 1.0 - smoothstep(MinDist, MaxDist, dist);
    return max(1.0, mix(MinTess, MaxTess, t));
}

float edgeDist(int index1, int index2) {
    vec3 mid = (gl_in[index1].gl_Position + gl_in[index2].gl_Position).xyz * 0.5;
    return distance(mid, uCamPos);
}

void main(void)
{
    if (gl_InvocationID == 0)
    {
        gl_TessLevelOuter[0] = tessLevel(edgeDist(0, 3)); // left edge
        gl_TessLevelOuter[1] = tessLevel(edgeDist(0, 1)); // bottom edge
        gl_TessLevelOuter[2] = tessLevel(edgeDist(1, 2)); // right edge
        gl_TessLevelOuter[3] = tessLevel(edgeDist(2, 3)); // top edge

        // Inner levels control the interior subdivision.
        // Average the opposite outer edges so the interior is consistent.
        gl_TessLevelInner[0] = 0.5 * (gl_TessLevelOuter[1] + gl_TessLevelOuter[3]);
        gl_TessLevelInner[1] = 0.5 * (gl_TessLevelOuter[0] + gl_TessLevelOuter[2]);
    }

    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    tescOut[gl_InvocationID].texCoord = tescIn[gl_InvocationID].texCoord;
    tescOut[gl_InvocationID].worldPos = tescIn[gl_InvocationID].worldPos;
    tescOut[gl_InvocationID].normal = tescIn[gl_InvocationID].normal;
}