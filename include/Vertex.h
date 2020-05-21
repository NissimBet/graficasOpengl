#ifndef GRAFICASOPENGL_VERTEX_H
#define GRAFICASOPENGL_VERTEX_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Color;
    glm::vec2 TextureCoords;
};

#endif //GRAFICASOPENGL_VERTEX_H
