#version 330 core

in vec2 fragTexCoord;
in vec3 fragNormal;
out vec4 outColor;

uniform sampler2D uTexture;
uniform vec3 uDirectionalLight;

void main()
{
    float difuseFactor = (dot(uDirectionalLight, normalize(fragNormal)) + 1.0f) / 2.0f;
    vec4 diffuseColor = vec4(0,0,0,1);
    
    vec4 textureColor = texture(uTexture, fragTexCoord);
    
    if  (difuseFactor > 0) {
        diffuseColor = textureColor * difuseFactor;
    }
    
    outColor = diffuseColor;
}

