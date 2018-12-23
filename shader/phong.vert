#version 330

in vec4 gl_Vertex;
in vec3 gl_Normal;
in vec4 gl_MultiTexCoord0;

out vec3 position;
out vec3 normal;
out vec4 texCoord;

void main() {
    gl_TexCoord[0] = gl_MultiTexCoord0;
    texCoord = gl_MultiTexCoord0;
    position = (gl_ModelViewMatrix * gl_Vertex).xyz;
    normal = normalize(gl_NormalMatrix * gl_Normal);

    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
