#version 330 core

uniform mat4 model;
uniform mat4 normalMatrix;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 viewProjection;
uniform float time;

in vec3 vPosition;
in vec3 vColor;
in vec3 vNormal;

out vec3 position;
out vec4 color;
out vec3 normal;

void main() {
    color = vec4(vColor, 1.0);

    normal = vec3(normalize(normalMatrix * vec4(vNormal, 1.0)));

    vec4 worldPos = (model * vec4(vPosition, 1.0));
    position = worldPos.xyz;
    gl_Position = viewProjection * worldPos;
}
