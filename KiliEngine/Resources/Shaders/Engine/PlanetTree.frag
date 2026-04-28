#version 450 core

out vec4 outColor;

in GeomOut{
    vec3 normal;
    float height;
} geomOut;

uniform vec3 uDirectionalLight;

vec4 pStump = vec4(0.349, 0.227, 0.055, 1.0);
vec4 pLeaf = vec4(0.145, 0.349, 0.122, 1.0);

void main()
{
    vec4 treeColor = mix(pStump, pLeaf, pow(geomOut.height, 0.5f));
    outColor = treeColor * dot(uDirectionalLight, geomOut.normal);
}
