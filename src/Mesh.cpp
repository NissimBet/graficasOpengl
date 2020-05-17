#include "Mesh.h"
#include <utility>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) : vertices(
        std::move(vertices)), indices(std::move(indices)) {
    // generate buffers and VAO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // setup the mesh data
    setupMesh();
}

void Mesh::setupMesh() {
    // bind VAO and the buffers to the VAO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // set the buffer data
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    // bind the EBO to VAO and set its data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // set VAO attribute locations
    // vertex positions
    glEnableVertexAttribArray(VERTEX_ATTRIB);
    glVertexAttribPointer(VERTEX_ATTRIB, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    // vertex color color coord
    glEnableVertexAttribArray(COLOR_ATTRIB);
    glVertexAttribPointer(COLOR_ATTRIB, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Color));

    // unbind VAO
    glBindVertexArray(0);
}

void Mesh::draw() const {
    // draw VAO contents
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}