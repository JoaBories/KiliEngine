#version 450

in TeseOut{
    vec2 texCoord;
    float perlin;
} fragIn;

out vec4 FragColor;

uniform sampler2D uTexture;

void main()
{
    FragColor = texture(uTexture, fragIn.texCoord) * clamp(fragIn.perlin + 1, 0, 1);
    //FragColor = vec4(clamp(fragIn.perlin + 1, 0, 1));
}