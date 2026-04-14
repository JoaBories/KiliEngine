#version 450 core

layout(triangles, equal_spacing, ccw) in;

uniform mat4 uViewProj;
uniform mat4 uWorldTransform;
uniform float uTime;

float pRotateSpeed = 0.05f; // revolution by second

in TescOut{
    vec2 texCoord;
} tescOut[];

out TeseOut{
    vec2 texCoord;
    vec3 normal;
} teseOut;

float interpolate(float f0, float f1, float f2)
{
    return gl_TessCoord.x * f0 + gl_TessCoord.y * f1 + gl_TessCoord.z * f2;
}

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
    return vec2(interpolate(v0.x, v1.x, v2.x), interpolate(v0.y, v1.y, v2.y));
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)
{
    return vec3(interpolate(v0.x, v1.x, v2.x), interpolate(v0.y, v1.y, v2.y), interpolate(v0.z, v1.z, v2.z));
}

vec4 interpolate4D(vec4 v0, vec4 v1, vec4 v2, float w)
{
    return vec4(interpolate(v0.x, v1.x, v2.x), interpolate(v0.y, v1.y, v2.y), interpolate(v0.z, v1.z, v2.z), w);
}

vec3 mapOnSphere(vec3 vec)
{
    float xx = vec.x * vec.x;
    float yy = vec.y * vec.y;
    float zz = vec.z * vec.z;
    
    float xx05 = xx * 0.5f;
    float yy05 = yy * 0.5f;
    float zz05 = zz * 0.5f;
    
    float x = vec.x * sqrt(1.0f - yy05 - zz05 + (yy * zz / 3));
    float y = vec.y * sqrt(1.0f - zz05 - xx05 + (zz * xx / 3));
    float z = vec.z * sqrt(1.0f - xx05 - yy05 + (xx * yy / 3));
    
    return vec3(x,y,z);
};

vec3 rotateZ(vec3 v, float angle)
{
    float c = cos(angle);
    float s = sin(angle);

    return vec3( v.x * c + v.y * s,
                 v.x * -s + v.y * c,
                 v.z );
}

void main(void)
{
    float rotation = fract(uTime * pRotateSpeed) * 6.2831853f; // 2pi
    vec3 cubePosition = interpolate3D(gl_in[0].gl_Position.xyz, gl_in[1].gl_Position.xyz, gl_in[2].gl_Position.xyz);
    vec3 spherePosition = mapOnSphere(cubePosition);
    
    gl_Position = vec4(rotateZ(spherePosition, rotation), 1.0f) * uWorldTransform * uViewProj;
    
    teseOut.texCoord = interpolate2D(tescOut[0].texCoord, tescOut[1].texCoord, tescOut[2].texCoord);
}
