#version 450 core

out vec4 outColor;

in GeomOut{
    vec3 normal;
    float height;
} geomOut;

uniform sampler2D uTexture;

vec4 pStump = vec4(0.349, 0.227, 0.055, 1.0);
vec4 pLeaf = vec4(0.145, 0.349, 0.122, 1.0);

void main()
{
    //Perlin visualization
    //vec3 color = vec3(geom.perlin * 0.5f + 0.5f);
    //outColor = vec4(color, 1.0f);
    
    //Normal visualization
    outColor = mix(pStump, pLeaf, pow(geomOut.height, 0.5f));

    //Steep visualization
    //vec3 color = vec3(geom.steepness / 10.0f);
    //outColor = vec4(color, 1.0f);
}
