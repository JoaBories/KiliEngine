#version 450

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;
uniform vec3 uSize;
uniform int uInstanceCount;
uniform float uTime;

const float pRandomOffsetScale = 0.5f;
const float pWindOffsetScale = 0.4f;
const float pRandomScale = 0.5f;
const vec3 pWindDir = normalize(vec3( 1.0f, 4.0f, 0.0f));

out VertOut{
    vec2 texCoord;
    vec3 normal;
    float brightness;
} vert_out;

vec2 rand2(vec2 p) //between 0-1
{ 
    vec2 k = vec2(
    dot(p, vec2(127.1, 311.7)),
    dot(p, vec2(269.5, 183.3))
    );
    return fract(sin(k) * 43758.5453123);
}

float rand1(float p) //between 0-1
{
    return fract(sin(p * 127.1) * 43758.5453123);
}

mat4 rotZ(float angle) {
    float c = cos(angle);
    float s = sin(angle);
    
    return mat4(
        c,    s,    0.0,  0.0,
        -s,   c,    0.0,  0.0,
        0.0,  0.0,  1.0,  0.0,
        0.0,  0.0,  0.0,  1.0
    );
}

void main() {
    int sqrInstance = int(sqrt(float(uInstanceCount)));
    
    vec3 coord = vec3(float(gl_InstanceID / sqrInstance), float(gl_InstanceID % sqrInstance), 0.0f) / sqrInstance; //Coord between 0-1
    
    vec2 random2 = rand2(coord.xy);
    
    vec3 wind = pWindDir * (sin(uTime + rand1(coord.x + coord.y) * 1.5f) + 1) / 2;
    
    vec3 randomOffset = vec3(random2 * 2 - 1, 0.0f) * pRandomOffsetScale;
    vec3 windOffset = wind * pow(1-texCoord.y, 2) * rand1(coord.x - coord.y);
    
    vec3 offset = fract(coord + randomOffset) * uSize - uSize / 2.0f;
    
    vec3 randomScale = vec3(rand1(random2.x) * pRandomScale + 1.0f);
    mat4 randomRotation = rotZ(rand1(random2.y) * 6.2831853);
    
    vec3 localPos = (vec4(pos * randomScale, 1.0f) * randomRotation).xyz + offset + windOffset * pWindOffsetScale;
    
    gl_Position = (vec4(localPos, 1.0f)) * uWorldTransform * uViewProj;
    
    vert_out.brightness = rand1(gl_InstanceID) / 4.0f + 0.75f;
    vert_out.normal = (vec4(normal.xzy, 0.0f) * randomRotation * uWorldTransform).xyz;
    vert_out.texCoord = texCoord;
}