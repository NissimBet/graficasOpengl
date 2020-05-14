#version 330 core

in vec3 Color;
out vec3 FragColor;

uniform float selected;
uniform vec3 highlight;

void main() {
  FragColor = selected * highlight * Color;
}