#version 450

in TeseOut{
    vec4 color;
    vec2 texCoord;
} fragIn;

out vec4 FragColor;

uniform sampler2D uTexture;

void main()
{
    FragColor = fragIn.color * texture(uTexture, fragIn.texCoord);
}
