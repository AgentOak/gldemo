#version 330 core

uniform float time;

in vec4 position;
in vec4 color;

layout(location = 0) out vec4 fragColor;

void main() {
    float brightness = 1.0 - position.z / 18.0;
    fragColor = vec4((brightness * brightness * color).xyz, 1.0);
}
