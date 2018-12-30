#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform vec3 cameraPosition;

in vec3 position;
in vec4 color;
in vec3 normal;

layout(location = 0) out vec4 fragColor;

void main() {
    vec3 dirToCam = normalize(cameraPosition - position);
    vec3 dirToLight = normalize(vec3(0.0, 0.0, 0.0) - position);

    // Ambient = k_a * L_a
    vec3 ambient = vec3(0.1, 0.1, 0.1) * vec3(1.0, 1.0, 1.0);

    // Diffuse = k_d * L_p * cos(theta)
    vec3 diffuse = vec3(0.5, 0.5, 0.5) * vec3(1.0, 1.0, 1.0) * clamp(dot(dirToLight, normal), 0.0, 1.0);

    // Specular = k_s * L_p * cos^m(alpha)
    vec3 r = normalize(2.0 * normal * dot(normal, dirToLight) - dirToLight);
    float alpha = max(0.0, dot(dirToCam, r));
    vec3 specular = vec3(0.8, 0.8, 0.8) * vec3(1.0, 1.0, 1.0) * pow(alpha, 6.0);

    vec3 light = ambient + diffuse + specular;
    fragColor = vec4(light * color.rgb, color.a);
}
