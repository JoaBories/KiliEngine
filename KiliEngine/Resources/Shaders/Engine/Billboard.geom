#version 330

layout(points) in;
layout(triangle_strip) out;
layout(max_vertices = 4) out;

uniform mat4 uViewProj;
uniform vec3 uCamPos;
uniform vec3 uPosition;
uniform vec3 uScale;

out vec2 fragTexCoord;

void main() {
    vec3 pos = gl_in[0].gl_Position.xyz + uPosition;
    vec3 camToPoint = normalize(pos - uCamPos);
    vec3 up = vec3(0.0f, 0.0f, 1.0f);
    vec3 right = cross(up, camToPoint);

    vec3 halfRight = right * uScale.x;
    vec3 halfUp    = up    * uScale.z;

    gl_Position = vec4(pos - halfRight - halfUp, 1.0f) * uViewProj;
    fragTexCoord = vec2(0.0, 1.0);
    EmitVertex();

    gl_Position = vec4(pos + halfRight - halfUp, 1.0f) * uViewProj;
    fragTexCoord = vec2(1.0, 1.0);
    EmitVertex();

    gl_Position = vec4(pos - halfRight + halfUp, 1.0f) * uViewProj;
    fragTexCoord = vec2(0.0, 0.0);
    EmitVertex();

    gl_Position = vec4(pos + halfRight + halfUp, 1.0f) * uViewProj;
    fragTexCoord = vec2(1.0, 0.0);
    EmitVertex();
    
    EndPrimitive();
}