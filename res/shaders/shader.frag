#version 330 core

in vec3 vertexPos;
out vec4 FragColor;

uniform vec4 uniColor;

void main() {
    FragColor = uniColor;
}