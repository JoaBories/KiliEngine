#version 450 core

out vec4 outColor;

in TeseOut{
    vec2 texCoord;
    vec3 normal;
    float height;
    float perlin;
    float steepness;
} teseOut;

uniform sampler2D uTexture;

//============================================

vec4 pLightBlue = vec4(0.114, 0.635, 0.847, 1.0);
vec4 pDarkBlue = vec4(0.024, 0.259, 0.451, 1.0);

vec4 pLightSand = vec4(0.965, 0.843, 0.69, 1.0);
vec4 pDarkSand = vec4(0.906, 0.769, 0.588, 1.0);
        
vec4 pSteep = vec4(0.455, 0.447, 0.455, 1.0);

vec4 pLightGrass = vec4(0.255, 0.596, 0.039, 1.0);
vec4 pDarkGrass = vec4(0.075, 0.427, 0.082, 1.0);

void main()
{
    //Perlin visualization
    //vec3 color = vec3(teseOut.perlin * 0.5f + 0.5f);
    //outColor = vec4(color, 1.0f);
    
    //Normal visualization
    //outColor = vec4(teseOut.normal * 0.5f + 0.5f, 1.0f);

    //Steep visualization
    //vec3 color = vec3(teseOut.steepness / 10.0f);
    //outColor = vec4(color, 1.0f);
    
    vec4 terrainColor;
    
    if(teseOut.perlin <= -0.1f)
    {
        float t = pow(teseOut.perlin + 1.25f / 1.25f, 2.0f);
        terrainColor = mix(pDarkBlue, pLightBlue, t);
    }
    else if (teseOut.perlin <= 0.0f)
    {
        float t = pow((teseOut.perlin + 0.1f) * 10.0f, 2.0f);
        terrainColor = mix(pDarkSand, pLightSand, t);
    }
    else if (teseOut.steepness >= 3.0f)
    {
        terrainColor = pSteep;
    }
    else
    {
        float t = teseOut.perlin;
        terrainColor = mix(pLightGrass, pDarkGrass, t);
    }
    
    outColor = terrainColor;
}
