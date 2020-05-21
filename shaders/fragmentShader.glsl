#version 330 core

in vec3 Color;
in vec2 TexCoord;

out vec4 FragColor;

uniform float selected;
uniform vec3 highlight;

uniform sampler2D meshTexture;

void main() {
    FragColor = texture(meshTexture,TexCoord);
}