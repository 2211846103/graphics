#version 330 core

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 
uniform Material material;

struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light; 
uniform vec3 cameraPos;

void main() {
    vec3 normal = normalize(Normal);

    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(normal, lightDir), 0);

    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0), material.shininess * 128);

    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));  
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    FragColor = vec4(ambient + diffuse + specular, 1);
}