#version 450 core

out vec4 outColor;

in GeomOut{
    vec2 texCoord;
    vec3 normal;
    float height;
    float perlin;
    float steepness;
} geomOut;

uniform sampler2D uTexture;
uniform vec3 uDirectionalLight;

//================Colors======================

vec4 pLightBlue = vec4(0.114, 0.635, 0.847, 1.0);
vec4 pDarkBlue = vec4(0.024, 0.259, 0.451, 1.0);

vec4 pLightSand = vec4(0.965, 0.843, 0.69, 1.0);
vec4 pDarkSand = vec4(0.906, 0.769, 0.588, 1.0);
        
vec4 pSteep = vec4(0.455, 0.447, 0.455, 1.0);

vec4 pLightGrass = vec4(0.255, 0.596, 0.039, 1.0);
vec4 pDarkGrass = vec4(0.025, 0.2, 0.025, 1.0);

//============================================

void main()
{
    //Perlin visualization
    //vec3 color = vec3(geomOut.perlin * 0.5f + 0.5f);
    //outColor = vec4(color, 1.0f);
    
    //Normal visualization
    //outColor = vec4(geomOut.normal * 0.5f + 0.5f, 1.0f);

    //Steep visualization
    //vec3 color = vec3(geomOut.steepness / 10.0f);
    //outColor = vec4(color, 1.0f);
    
    vec4 terrainColor;
    
    if(geomOut.perlin <= -0.1f)
    {
        float t = pow(geomOut.perlin + 1.25f / 1.25f, 3.0f);
        terrainColor = mix(pDarkBlue, pLightBlue, t);
    }
    else if (geomOut.perlin <= 0.0f)
    {
        float t = pow((geomOut.perlin + 0.1f) * 10.0f, 1.0f);
        terrainColor = mix(pDarkSand, pLightSand, t);
    }
    else if (geomOut.steepness >= 3.0f)
    {
        terrainColor = pSteep;
    }
    else
    {
        float t = geomOut.perlin;
        terrainColor = mix(pLightGrass, pDarkGrass, t);
    }
    
    outColor = terrainColor * dot(uDirectionalLight, geomOut.normal);
}
