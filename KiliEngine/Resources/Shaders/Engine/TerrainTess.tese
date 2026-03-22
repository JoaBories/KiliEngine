#version 450 core

layout(quads, fractional_even_spacing, ccw) in;

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

    vec3 p0 = mix(gl_in[0].gl_Position, gl_in[1].gl_Position, u).xyz;   // bottom edge
    vec3 p1 = mix(gl_in[3].gl_Position, gl_in[2].gl_Position, u).xyz;   // top edge
    vec3 worldPos = mix(p0, p1, v);                             // blend bottom→top

    //teTexCoord = worldPos.xz / 64.0;   // scale to UV
    //float height = texture(uHeightmap, teTexCoord).r * 8.0; // scale height
    //worldPos.z += height;
    
    gl_Position = vec4(worldPos, 1.0);
    
    teseOut.texCoord = interpolate2D(
        teseIn[0].texCoord, teseIn[1].texCoord, teseIn[2].texCoord, teseIn[3].texCoord
    );
}