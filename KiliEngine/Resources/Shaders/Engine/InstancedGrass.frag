#version 450

uniform sampler2D uTexture;

out vec4 color;

in VertOut{
    vec2 texCoord;
} frag_in;

void main()
{
    color = texture(uTexture, frag_in.texCoord);
}