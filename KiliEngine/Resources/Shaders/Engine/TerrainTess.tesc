#version 450 core
//Work better with an already subdivided plane

layout(vertices = 4) out;

in VertOut{
    vec2 texCoord;
} tescIn[];

out TescOut{
    vec2 texCoord;
} tescOut[];

float uMinDist = 4.0;      // distance at which max tessellation kicks in  (e.g. 4.0)
float uMaxDist = 100.0;      // distance at which min tessellation kicks in  (e.g. 40.0)
float uMinTess = 1.0;      // minimum tessellation level (e.g. 1.0)
float uMaxTess = 16.0;      // maximum tessellation level (e.g. 16.0)

float tessLevel(float dist) {
    float t = 1.0 - smoothstep(uMinDist, uMaxDist, dist);
    return max(1.0, mix(uMinTess, uMaxTess, t));
}

// Distance from the camera to the midpoint of an edge defined by
// two control point indices.
float edgeDist(int i0, int i1) {
    vec3 mid = (gl_in[i0].gl_Position + gl_in[i1].gl_Position).xyz * 0.5;
    return length(mid);
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
}