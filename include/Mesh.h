//
// Created by jcfflores on 5/12/20.
//

#ifndef GRAFICASOPENGL_MESH_H
#define GRAFICASOPENGL_MESH_H

#include <vector>
#include <GL/glew.h>
#include "Vertex.h"

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    Mesh(std::vector<Vertex>, std::vector<unsigned int>);
    void draw() const;

private:
    GLuint VAO, VBO, EBO;
    GLuint VERTEX_ATTRIB = 0;
    GLuint COLOR_ATTRIB = 1;

    inline void setupMesh();
};

#endif //GRAFICASOPENGL_MESH_H
