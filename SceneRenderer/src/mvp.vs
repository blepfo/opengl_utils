#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNormal;

uniform mat4 modelView;
uniform mat4 modelViewProjection;
uniform mat3 normalMatrix;
uniform mat4 view;

out vec3 fragPosView;
out vec3 fragNormalView;

void main() {
    // Fragment position in view space used for lighting
    vec4 fragPosViewH = modelView * vec4(inPos, 1.0);
 
    fragPosView = fragPosViewH.xyz / fragPosViewH.w;
    // Normal in view space for lighting
    fragNormalView = normalMatrix * normalize(inNormal);

    gl_Position = modelViewProjection * vec4(inPos, 1.0);
}
