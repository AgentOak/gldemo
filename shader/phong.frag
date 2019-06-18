#version 150 core

// TODO: Somehow broken, both variants. sucks
#define SPECULAR 0

#define BLINN_PHONG 0
#define BLINN_PHONG_FACTOR 4.0

#define MAX_LIGHTS 10

uniform vec3 cameraPosition;

uniform vec3 ambientLight;

uniform uint numPointLights;
uniform struct pointlight {
    vec3 position;
    vec3 attenuation;
    vec3 intensity;
} pointlights[MAX_LIGHTS];

uniform struct material_data {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float shininess;
} material;

in vec3 position;
in vec4 color;
in vec3 normal;

out vec4 fragColor;

void main() {
    vec3 dirToCam = normalize(cameraPosition - position);

    // Ambient
    vec3 illum = material.ambient * ambientLight;

    // Point light sources
    for (uint l = 0u; l < numPointLights; l++) {
        pointlight light = pointlights[l];
        vec3 posToLight = light.position - position;
        vec3 dirToLight = normalize(posToLight);

        // Diffuse
        float cosTheta = max(dot(dirToLight, normal), 0.0);
        vec3 diffuse = material.diffuse * cosTheta;

        // Specular
        vec3 specular = vec3(0.0);
        #if SPECULAR
        #if BLINN_PHONG
        float cosHalfway = max(dot(normal, normalize(dirToLight + dirToCam)), 0.0);
        specular = material.specular * pow(cosHalfway, material.shininess * BLINN_PHONG_FACTOR);
        #else
        float cosAlpha = max(dot(dirToCam, reflect(-dirToLight, normal)), 0.0);
        specular = material.specular * pow(cosAlpha, material.shininess);
        #endif
        #endif

        // Attenuation
        float lightDistance = length(posToLight);
        float attenuation = 1.0 / (light.attenuation[0]
                 + light.attenuation[1] * lightDistance
                 + light.attenuation[2] * lightDistance * lightDistance);

        // Phong
        illum += attenuation * light.intensity * (diffuse + specular);
    }

    // TODO: Directional lights

    // TODO: Gamma correction
    // TODO: logarithmic above 1.0
    fragColor = vec4(min(illum, 1.0) * color.rgb, color.a);
}
