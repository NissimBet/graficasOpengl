//
// Created by jcfflores on 5/12/20.
//

#ifndef GRAFICASOPENGL_VERTEX_H
#define GRAFICASOPENGL_VERTEX_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TextCoords;
};

#endif //GRAFICASOPENGL_VERTEX_H
