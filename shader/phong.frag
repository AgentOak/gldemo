#version 330 core

uniform sampler2D gl_Texture0;

in vec3 normal;
in vec3 position;

void main() {
    vec3 dirToCam = -normalize(position);

    /* begin edit here */
    vec3 ndirToLight = normalize(gl_LightSource[0].position.xyz - position);

    // L_ra = k_a * L_a */
    vec4 ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;

    // L_d = k_d * L_p * cos(theta) */
    vec4 diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse * dot(ndirToLight, normal);

    // L_s = k_s * L_p * cos^m(alpha)
    vec3 r = normalize(2.0 * normal * dot(normal, ndirToLight) - ndirToLight);
    float alpha = max(0, dot(dirToCam, r));
    vec4 specular = gl_FrontMaterial.specular * gl_LightSource[0].specular *
                    pow(alpha, gl_FrontMaterial.shininess);

    // L = L_ra + L_d + L_s
    vec4 color = ambient + diffuse + specular;
    /* end edit here */

    gl_FragColor = color * texture2D(gl_Texture0, gl_TexCoord[0].xy);
}
