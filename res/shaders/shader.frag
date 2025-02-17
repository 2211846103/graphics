#version 330 core

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform float shininess;

uniform vec3 lightColor;
uniform vec3 lightPos;

uniform vec3 cameraPos;

void main() {
    vec3 normal = normalize(Normal);

    vec3 ambientLight = ambient * lightColor;

    vec3 lightDir = normalize(lightPos - FragPos);
    float diffusion = max(dot(normal, lightDir), 0);
    vec3 diffuseLight = diffusion * diffuse * lightColor;

    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float speculation = pow(max(dot(viewDir, reflectDir), 0), shininess * 128);
    vec3 specularLight = specular * speculation * lightColor;

    FragColor = vec4(ambientLight + diffuseLight + specularLight, 1);
}