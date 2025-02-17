#version 330 core

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light; 
uniform vec3 cameraPos;

void main() {
    vec3 normal = normalize(Normal);

    vec3 ambientLight = material.ambient * light.ambient;

    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(normal, lightDir), 0);
    vec3 diffuseLight = diff * material.diffuse * light.diffuse;

    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0), material.shininess * 128);
    vec3 specularLight = material.specular * spec * light.specular;

    FragColor = vec4(ambientLight + diffuseLight + specularLight, 1);
}