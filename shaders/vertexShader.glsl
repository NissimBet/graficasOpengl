#version 330 core

layout(location = 0) in vec3 worldPosition;

void main() {
  gl_Position.xyz = worldPosition;
  gl_Position.w = 1.0;
}