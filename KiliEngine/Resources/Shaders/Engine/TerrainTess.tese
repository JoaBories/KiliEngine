#version 450 core

layout(quads, fractional_even_spacing, ccw) in;

uniform sampler2D uTexture;
uniform mat4 uViewProj;

uniform float uHeightScale;

in TescOut{
    vec2 texCoord;
    vec3 worldPos;
    vec3 normal;
} teseIn[];

out TeseOut{
    vec2 texCoord;
    float perlin;
} teseOut;

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2, vec2 v3)
{
    vec2 bottom = mix(v0, v1, gl_TessCoord.x);
    vec2 top    = mix(v3, v2, gl_TessCoord.x);
    return mix(bottom, top, gl_TessCoord.y);
}

vec2 rand2dTo2d(vec2 p)
{
    vec2 result = vec2( dot(p, vec2(127.1, 311.7)), dot(p, vec2(269.5, 183.3)) );
    result = fract(sin(result) * 43758.5453);
    
    if (result != vec2(0,0)) {
        return normalize(result);
    }
    else return result;
}

float rand2dTo1d(vec2 p)
{
    return fract(sin(dot(p, vec2(12.9898, 78.233))) * 43758.5453);
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

    vec2 lowerLeftDirection = rand2dTo2d(vec2(floor(coordinates.x), floor(coordinates.y))) * 2 - 1;
    vec2 lowerRightDirection = rand2dTo2d(vec2(ceil(coordinates.x), floor(coordinates.y))) * 2 - 1;
    vec2 upperLeftDirection = rand2dTo2d(vec2(floor(coordinates.x), ceil(coordinates.y))) * 2 - 1;
    vec2 upperRightDirection = rand2dTo2d(vec2(ceil(coordinates.x), ceil(coordinates.y))) * 2 - 1;

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

void main(void)
{
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;

    vec3 p0 = teseIn[0].worldPos;
    vec3 p1 = teseIn[1].worldPos;
    vec3 p2 = teseIn[2].worldPos;
    vec3 p3 = teseIn[3].worldPos;
    
    vec3 p = p0 * (1.0 - u) * (1.0 - v) +
             p1 * u * (1.0 - v) +
             p3 * v * (1.0 - u) +
             p2 * u * v;
    
    vec2 texCoord = interpolate2D(
        teseIn[0].texCoord, teseIn[1].texCoord, teseIn[2].texCoord, teseIn[3].texCoord
    );
    
    teseOut.texCoord = texCoord;
    teseOut.perlin = perlinNoiseOctave(texCoord, 8, 0.75, 1.8);
        
    p += (teseOut.perlin + texture(uTexture, texCoord).r) * uHeightScale * teseIn[0].normal;
    
    gl_Position = vec4(p , 1.0) * uViewProj;
}