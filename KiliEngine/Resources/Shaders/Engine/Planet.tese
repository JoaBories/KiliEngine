#version 450 core

layout(triangles, equal_spacing, ccw) in;

uniform mat4 uViewProj;
uniform mat4 uWorldTransform;
uniform float uTime;

float PI  = 3.14159265358979f;
float TAU = 6.28318530717959f;
float EPSILON = 0.000001f;

float pRotateSpeed = 0.005f; // revolution by second
float pPerlinScale = 0.05f;
float pPerlinFrequency = 2.0f;
float pSeaLevel = -0.1f;

in TescOut{
    vec2 texCoord;
} tescOut[];

out TeseOut{
    vec2 texCoord;
    float height;
    float perlin;
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

// ================Perlin Noise==================
//
// GLSL textureless classic 3D noise "cnoise",
// with an RSL-style periodic variant "pnoise".
// Author:  Stefan Gustavson (stefan.gustavson@gmail.com)
// Version: 2024-11-07
//
// Many thanks to Ian McEwan of Ashima Arts for the
// ideas for permutation and gradient selection.
//
// Copyright (c) 2011 Stefan Gustavson. All rights reserved.
// Distributed under the MIT license. See LICENSE file.
// https://github.com/stegu/webgl-noise
//

vec3 mod289(vec3 x)
{
    return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec4 mod289(vec4 x)
{
    return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec4 permute(vec4 x)
{
    return mod289(((x*34.0)+10.0)*x);
}

vec4 taylorInvSqrt(vec4 r)
{
    return 1.79284291400159 - 0.85373472095314 * r;
}

vec3 fade(vec3 t) {
    return t*t*t*(t*(t*6.0-15.0)+10.0);
}

// Classic Perlin noise
float cnoise(vec3 P)
{
    vec3 Pi0 = floor(P); // Integer part for indexing
    vec3 Pi1 = Pi0 + vec3(1.0); // Integer part + 1
    Pi0 = mod289(Pi0);
    Pi1 = mod289(Pi1);
    vec3 Pf0 = fract(P); // Fractional part for interpolation
    vec3 Pf1 = Pf0 - vec3(1.0); // Fractional part - 1.0
    vec4 ix = vec4(Pi0.x, Pi1.x, Pi0.x, Pi1.x);
    vec4 iy = vec4(Pi0.yy, Pi1.yy);
    vec4 iz0 = Pi0.zzzz;
    vec4 iz1 = Pi1.zzzz;

    vec4 ixy = permute(permute(ix) + iy);
    vec4 ixy0 = permute(ixy + iz0);
    vec4 ixy1 = permute(ixy + iz1);

    vec4 gx0 = ixy0 * (1.0 / 7.0);
    vec4 gy0 = fract(floor(gx0) * (1.0 / 7.0)) - 0.5;
    gx0 = fract(gx0);
    vec4 gz0 = vec4(0.5) - abs(gx0) - abs(gy0);
    vec4 sz0 = step(gz0, vec4(0.0));
    gx0 -= sz0 * (step(0.0, gx0) - 0.5);
    gy0 -= sz0 * (step(0.0, gy0) - 0.5);

    vec4 gx1 = ixy1 * (1.0 / 7.0);
    vec4 gy1 = fract(floor(gx1) * (1.0 / 7.0)) - 0.5;
    gx1 = fract(gx1);
    vec4 gz1 = vec4(0.5) - abs(gx1) - abs(gy1);
    vec4 sz1 = step(gz1, vec4(0.0));
    gx1 -= sz1 * (step(0.0, gx1) - 0.5);
    gy1 -= sz1 * (step(0.0, gy1) - 0.5);

    vec3 g000 = vec3(gx0.x,gy0.x,gz0.x);
    vec3 g100 = vec3(gx0.y,gy0.y,gz0.y);
    vec3 g010 = vec3(gx0.z,gy0.z,gz0.z);
    vec3 g110 = vec3(gx0.w,gy0.w,gz0.w);
    vec3 g001 = vec3(gx1.x,gy1.x,gz1.x);
    vec3 g101 = vec3(gx1.y,gy1.y,gz1.y);
    vec3 g011 = vec3(gx1.z,gy1.z,gz1.z);
    vec3 g111 = vec3(gx1.w,gy1.w,gz1.w);

    vec4 norm0 = taylorInvSqrt(vec4(dot(g000, g000), dot(g010, g010), dot(g100, g100), dot(g110, g110)));
    vec4 norm1 = taylorInvSqrt(vec4(dot(g001, g001), dot(g011, g011), dot(g101, g101), dot(g111, g111)));

    float n000 = norm0.x * dot(g000, Pf0);
    float n010 = norm0.y * dot(g010, vec3(Pf0.x, Pf1.y, Pf0.z));
    float n100 = norm0.z * dot(g100, vec3(Pf1.x, Pf0.yz));
    float n110 = norm0.w * dot(g110, vec3(Pf1.xy, Pf0.z));
    float n001 = norm1.x * dot(g001, vec3(Pf0.xy, Pf1.z));
    float n011 = norm1.y * dot(g011, vec3(Pf0.x, Pf1.yz));
    float n101 = norm1.z * dot(g101, vec3(Pf1.x, Pf0.y, Pf1.z));
    float n111 = norm1.w * dot(g111, Pf1);

    vec3 fade_xyz = fade(Pf0);
    vec4 n_z = mix(vec4(n000, n100, n010, n110), vec4(n001, n101, n011, n111), fade_xyz.z);
    vec2 n_yz = mix(n_z.xy, n_z.zw, fade_xyz.y);
    float n_xyz = mix(n_yz.x, n_yz.y, fade_xyz.x);
    return 2.2 * n_xyz;
}

int octaves = 6;
float persistence = 0.75f;
float lacunarity = 1.8f;

float perlinOctave(vec3 spherePos)
{
    float value = 0;
    float ttAmplitude = 0;

    float amplitude = 1;
    float frequency = 1;

    for (int i = 0; i < octaves; i++)
    {
        value += cnoise(spherePos * frequency) * amplitude;
        ttAmplitude += amplitude;
        amplitude *= persistence;
        frequency *= lacunarity;
    }

    return value / ttAmplitude;
}

// ==============================================

void main(void)
{
    float rotation = fract(uTime * pRotateSpeed) * TAU;
    vec3 cubePosition = interpolate3D(gl_in[0].gl_Position.xyz, gl_in[1].gl_Position.xyz, gl_in[2].gl_Position.xyz);
    vec3 spherePosition = mapOnSphere(cubePosition);

    vec3 normal = normalize(spherePosition);
    vec3 perpX = cross(normal, vec3(1,0,0));
    vec3 perpY = cross(normal, vec3(0,1,0));
    vec3 perpZ = cross(normal, vec3(0,0,1));
    normal = rotateZ(normal, rotation);

    float perlin = perlinOctave(spherePosition * pPerlinFrequency);
    teseOut.perlin = perlin;
    perlin = clamp(perlin, pSeaLevel, 1.0f);
    teseOut.height = perlin;
    
    vec3 rotatedSpherePosition = rotateZ(spherePosition, rotation);
    vec3 displacedSpherePosition = normalize(rotatedSpherePosition) * (1.0f + perlin * pPerlinScale);
    gl_Position = vec4(displacedSpherePosition, 1.0f);
    
    teseOut.texCoord = interpolate2D(tescOut[0].texCoord, tescOut[1].texCoord, tescOut[2].texCoord);
}
