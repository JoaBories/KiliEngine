#version 450

in TeseOut{
    vec2 texCoord;
} fragIn;

out vec4 FragColor;

uniform sampler2D uTexture;

void main()
{
    FragColor = texture(uTexture, fragIn.texCoord);
}
