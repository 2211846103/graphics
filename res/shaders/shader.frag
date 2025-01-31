#version 330 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main() {
    FragColor = mix(texture(tex1, TexCoords), texture(tex2, TexCoords), 0.4);
}