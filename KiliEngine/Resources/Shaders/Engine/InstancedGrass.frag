#version 450

uniform sampler2D uTexture;
uniform vec3 uDirectionalLight;

out vec4 color;

in VertOut{
    vec2 texCoord;
    vec3 normal;
    float brightness;
} frag_in;

void main()
{
    color = texture(uTexture, frag_in.texCoord) * vec4(frag_in.brightness);
}