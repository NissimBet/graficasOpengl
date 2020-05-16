#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 3) in vec3 vertexColor;

out vec3 Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position =  projection * view * model * vec4(vertexPosition, 1);
    Color = vertexColor;
}