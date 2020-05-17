#ifndef GRAFICASOPENGL_MESH_H
#define GRAFICASOPENGL_MESH_H

#include <vector>
#include <GL/glew.h>
#include "Vertex.h"

class Mesh {
public:
    // vector of vertices corresponding to the mesh
    std::vector<Vertex> vertices;
    // indices of the faces corresponding to the vertices that create each triangle of the mesh
    std::vector<unsigned int> indices;

    /**
     * Constructor of the mesh, indicating the vertices that create it and the order of the vertices that create each face
     * @param vertices vector of vertices that make up the mesh
     * @param indices indices that indicate the order of drawing of the vertices to crete the mesh
     */
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    /**
     * Draw the mesh
     */
    void draw() const;

private:
    // VAO, VBO and EBO corresponding to the mesh
    GLuint VAO, VBO, EBO;
    GLuint VERTEX_ATTRIB = 0;
    GLuint COLOR_ATTRIB = 1;

    /**
     * setup the mesh by binding the EBO and VBO buffers to the VAO and the filling the data of the buffers
     */
    inline void setupMesh();
};

#endif //GRAFICASOPENGL_MESH_H
