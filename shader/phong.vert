#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec3 vNormal;

out vec3 position;
out vec4 color;
out vec3 normal;

void main() {
    color = vec4(vColor, 1.0);

    mat3 normalMatrix = transpose(inverse(mat3(model)));
    normal = normalize(normalMatrix * vNormal);

    vec4 worldPos = (model * vec4(vPosition, 1.0));
    position = worldPos.xyz;
    gl_Position = projection * view * worldPos;
}
