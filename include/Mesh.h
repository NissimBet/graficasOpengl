//
// Created by jcfflores on 5/12/20.
//

#ifndef GRAFICASOPENGL_MESH_H
#define GRAFICASOPENGL_MESH_H

#include <vector>
#include <GL/glew.h>
#include "Vertex.h"
#include "Texture.h"

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> , std::vector<unsigned int> , std::vector<Texture>);
    void draw(GLuint);

private:
    GLuint VAO, VBO, EBO;
    void setupMesh();
};

#endif //GRAFICASOPENGL_MESH_H
