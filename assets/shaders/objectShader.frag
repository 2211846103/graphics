#version 330 core

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;

void main() {
    vec3 normal = normalize(Normal);

    float ambientStrength = 0.1;
    vec3 ambientLight = ambientStrength * lightColor;

    vec3 lightDir = normalize(lightPos - FragPos);
    float diffusion = max(dot(normal, lightDir), 0);
    vec3 diffuseLight = diffusion * lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float specular = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec3 specularLight = specular * specularStrength * lightColor;

    FragColor = vec4((ambientLight + diffuseLight + specularLight) * objectColor, 1);
}