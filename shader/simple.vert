#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;

out vec4 color;

void main() {
    float pulse = (0.5 * (sin(time * 1.2) + 1.0));

    vec4 worldPos = model * vec4(vPosition.xyz, 1.0);
    worldPos.z += 5.0 * pulse - 5.0;

    gl_Position = projection * view * worldPos;
    color = vec4(pulse * pulse * vColor, 1.0);
}
