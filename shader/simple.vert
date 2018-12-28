#version 330 core

uniform mat4 modelViewProjection;
uniform float time;

in vec3 vPosition;
in vec3 vColor;

out vec4 color;

void main() {
    float pulse = (0.5 * (sin(time * 1.2) + 1.0));

    gl_Position = modelViewProjection * vec4(vPosition.xy, 4.0 * pulse - 5.0, 1.0);

    color = vec4(pulse * pulse * vColor, 1.0);
}
