#version 330 core

uniform float time;

in vec4 color;

void main() {
    gl_FragColor = color;
}