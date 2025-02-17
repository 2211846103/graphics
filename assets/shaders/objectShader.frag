#version 330 core

in vec2 TexCoords;
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main() {
    FragColor = vec4(objectColor, 1);
}