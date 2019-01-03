#version 330 core

#define MAX_LIGHTS 10

uniform vec3 cameraPosition;

uniform uint numLights;
uniform struct light_data {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
} lights[MAX_LIGHTS];

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

    vec3 maxLight = vec3(0.0);
    for (uint l = 0u; l < numLights; l++) {
        vec3 dirToLight = normalize(lights[l].position - position);

        // Ambient = k_a * L_a
        vec3 ambient = material.ambient * lights[l].ambient;

        // Diffuse = k_d * L_p * cos(theta)
        vec3 diffuse = material.diffuse * lights[l].diffuse * clamp(dot(dirToLight, normal), 0.0, 1.0);

        // Specular = k_s * L_p * cos^m(alpha)
        vec3 r = normalize(2.0 * normal * dot(normal, dirToLight) - dirToLight);
        float alpha = max(0.0, dot(dirToCam, r));
        vec3 specular = material.specular * lights[l].specular * pow(alpha, material.shininess);

        vec3 light = ambient + diffuse + specular;
        maxLight.r = max(maxLight.r, light.r);
        maxLight.g = max(maxLight.g, light.g);
        maxLight.b = max(maxLight.b, light.b);

        // TODO: Attenuation
    }

    // TODO: Gamma correction
    fragColor = vec4(maxLight * color.rgb, color.a);
}
