#version 450 core

layout(triangles, equal_spacing, ccw) in;

uniform mat4 uViewProj;
uniform mat4 uWorldTransform;
uniform float uTime;

float PI  = 3.14159265358979f;
float TAU = 6.28318530717959f;

float pRotateSpeed = 0.05f; // revolution by second

in TescOut{
    vec2 texCoord;
} tescOut[];

out TeseOut{
    vec2 texCoord;
    vec3 normal;
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

//Perlin noise ==================

vec2 rand2dTo2d(vec2 p)
{
    vec2 result = vec2( dot(p, vec2(127.1f, 311.7f)), dot(p, vec2(269.5f, 183.3f)) );
    result = fract(sin(result) * 43758.5453f) * 2.0f - 1.0f;
    return result;
}

float easeIn(float interpolator)
{
    return interpolator * interpolator;
}

float easeOut(float interpolator)
{
    return 1 - easeIn(1 - interpolator);
}

float easeInOut(float interpolator)
{
    float easeInValue = easeIn(interpolator);
    float easeOutValue = easeOut(interpolator);
    return mix(easeInValue, easeOutValue, interpolator);
}

float perlinNoise(vec2 coordinates)
{
    vec2 fraction = fract(coordinates);
    float interpolatorX = easeInOut(fraction.x);
    float interpolatorY = easeInOut(fraction.y);

    vec2 lowerLeftDirection = rand2dTo2d(vec2(floor(coordinates.x),         floor(coordinates.y)));
    vec2 lowerRightDirection = rand2dTo2d(vec2(floor(coordinates.x) + 1.0f, floor(coordinates.y)));
    vec2 upperLeftDirection = rand2dTo2d(vec2(floor(coordinates.x),         floor(coordinates.y) + 1.0f));
    vec2 upperRightDirection = rand2dTo2d(vec2(floor(coordinates.x) + 1.0f, floor(coordinates.y) + 1.0f));

    float lowerLeftFunctionValue = dot(lowerLeftDirection, fraction - vec2(0, 0));
    float lowerRightFunctionValue = dot(lowerRightDirection, fraction - vec2(1, 0));
    float upperLeftFunctionValue = dot(upperLeftDirection, fraction - vec2(0, 1));
    float upperRightFunctionValue = dot(upperRightDirection, fraction - vec2(1, 1));

    float lowerCells = mix(lowerLeftFunctionValue, lowerRightFunctionValue, interpolatorX);
    float upperCells = mix(upperLeftFunctionValue, upperRightFunctionValue, interpolatorX);

    float noise = mix(lowerCells, upperCells, interpolatorY);

    return noise;
}

float perlinNoiseOctave(vec2 coordinates, int octaves, float persistence, float lacunarity)
{
    float value = 0;
    float ttAmplitude = 0;

    float amplitude = 1;
    float frequency = 1;

    for (int i = 0; i < 8; i++)
    {
        if (i >= octaves)
        break;

        value += perlinNoise(coordinates * frequency) * amplitude;
        ttAmplitude += amplitude;
        amplitude *= persistence;
        frequency *= lacunarity;
    }

    return value / ttAmplitude;
}

float triplanarNoise(vec3 p, int octaves, float persistence, float lacunarity) {
    vec3 w = abs(p);           // always positive
    w /= (w.x + w.y + w.z);   // sum to 1
    
    float nx = perlinNoiseOctave(p.yz, octaves, persistence, lacunarity);
    float ny = perlinNoiseOctave(p.xz, octaves, persistence, lacunarity);
    float nz = perlinNoiseOctave(p.xy, octaves, persistence, lacunarity);

    return nx + ny + nz / 3.0f;
}

// ==============================

void main(void)
{
    float rotation = fract(uTime * pRotateSpeed) * 6.2831853f; // 2pi
    vec3 cubePosition = interpolate3D(gl_in[0].gl_Position.xyz, gl_in[1].gl_Position.xyz, gl_in[2].gl_Position.xyz);
    vec3 spherePosition = mapOnSphere(cubePosition);
    
    vec3 rotatedSpherePosition = rotateZ(spherePosition, rotation);
    teseOut.normal = normalize(rotatedSpherePosition);
    
    float perlin = triplanarNoise(spherePosition, 4, 0.75f, 1.8f);
    
    gl_Position = vec4(rotatedSpherePosition + teseOut.normal * perlin * 0.1f, 1.0f) * uWorldTransform * uViewProj;
    
    teseOut.texCoord = interpolate2D(tescOut[0].texCoord, tescOut[1].texCoord, tescOut[2].texCoord);
    teseOut.perlin = perlin;
}
