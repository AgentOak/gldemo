#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;

out vec4 color;
out vec4 position;

void main() {
    position = projection * view * model * vec4(vPosition.xyz, 1.0);
    gl_Position = position;
    color = vec4(vColor, 1.0);
}
