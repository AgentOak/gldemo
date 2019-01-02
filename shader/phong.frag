#version 330 core

uniform vec3 cameraPosition;

uniform struct light_data {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float linearAttenuation;
    float quadraticAttenuation;
} lights[];

uniform struct material_data {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float shininess;
} material;

in vec3 position;
in vec4 color;
in vec3 normal;

layout(location = 0) out vec4 fragColor;

void main() {
    vec3 dirToCam = normalize(cameraPosition - position);
    vec3 dirToLight = normalize(vec3(0.0, 0.0, 0.0) - position);

    // Ambient = k_a * L_a
    vec3 ambient = material.ambient * vec3(1.0, 1.0, 1.0);

    // Diffuse = k_d * L_p * cos(theta)
    vec3 diffuse = material.diffuse * vec3(1.0, 1.0, 1.0) * clamp(dot(dirToLight, normal), 0.0, 1.0);

    // Specular = k_s * L_p * cos^m(alpha)
    vec3 r = normalize(2.0 * normal * dot(normal, dirToLight) - dirToLight);
    float alpha = max(0.0, dot(dirToCam, r));
    vec3 specular = material.specular * vec3(1.0, 1.0, 1.0) * pow(alpha, material.shininess);

    vec3 light = ambient + diffuse + specular;
    fragColor = vec4(light * color.rgb, color.a);
}
