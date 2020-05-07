//
// Created by nissi on 5/3/2020.
//

#include <math.h>
#include "Cylinder.h"

Cylinder::Cylinder() : GLObject(3, 3)   {
    this->colors = std::vector<GLfloat>();
    this->initVertices();

    // unbind any VAO, to prevent unwanted behavior when generating the VBOs
    glBindVertexArray(0);

    glGenBuffers(1, &this->verticesVBO);
    glGenBuffers(1, &this->colorsVBO);
}

Cylinder::~Cylinder() {
    glDeleteBuffers(GL_ARRAY_BUFFER, &(this->verticesVBO));
    glDeleteBuffers(GL_ARRAY_BUFFER, &(this->colorsVBO));
}

void Cylinder::bind(GLuint VAO) const {
    glBindVertexArray(VAO);

    // bind buffer to VAO
    glBindBuffer(GL_ARRAY_BUFFER, this->verticesVBO);
    // set buffer data
    glBufferData(
            GL_ARRAY_BUFFER,                                    // buffer type
            this->vertices.size() * sizeof(this->vertices[0]),  // size in bytes of data
            &this->vertices.front(),                            // pointer of beginning of data
            GL_STATIC_DRAW);                                    // method of drawing

    // define array of vertex attribute data
    glVertexAttribPointer(
            this->VERTEX_ATTRIB,                            // attribute VERTEX_ATTRIB
            this->POINTS_PER_VERTEX,                        // number of components per vertex attribute
            GL_FLOAT,                                       // type of each component
            GL_FALSE,                                       // should be normalized
            this->POINTS_PER_VERTEX * sizeof(GLfloat),      // stride between components
            nullptr                                         // offset to first component
    );
    // enable the defined attribute
    glEnableVertexAttribArray(this->VERTEX_ATTRIB);

    if (!this->colors.empty()) {
        glBindBuffer(GL_ARRAY_BUFFER, this->colorsVBO);
        glBufferData(GL_ARRAY_BUFFER, this->colors.size() * sizeof(this->colors[0]), &this->colors.front(), GL_STATIC_DRAW);
        glVertexAttribPointer(this->COLOR_ATTRIB, this->POINTS_PER_COLOR, GL_FLOAT, GL_FALSE, this->POINTS_PER_COLOR * sizeof(GLfloat), nullptr);
        glEnableVertexAttribArray(this->COLOR_ATTRIB);
    }

    // unbind all buffers and vertex array
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Cylinder::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Cylinder::draw(GLuint VAO) const {
    // bind necessary buffers
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->verticesVBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->colorsVBO);

    // draw data stored in VAO
    glDrawArrays(GL_TRIANGLES, 0, this->vertices.size() / this->POINTS_PER_VERTEX);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Cylinder::initVertices() {
    int sides = 10;
    float theta = 2 * M_PI / (float) sides;

    
}