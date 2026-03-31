#version 450

in TeseOut{
    vec2 texCoord;
    float perlin;
} fragIn;

out vec4 FragColor;

uniform sampler2D uTexture;

void main()
{
    FragColor = vec4(vec3(fragIn.perlin), 1.0); //texture(uTexture, fragIn.texCoord);
}
