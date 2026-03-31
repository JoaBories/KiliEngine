#version 450

in TeseOut{
    vec2 texCoord;
    float perlin;
} fragIn;

out vec4 FragColor;

uniform sampler2D uTexture;

void main()
{
    FragColor = texture(uTexture, fragIn.texCoord) * (1-fragIn.perlin);
    FragColor = vec4(clamp(fragIn.perlin + 1, 0, 1));
}
