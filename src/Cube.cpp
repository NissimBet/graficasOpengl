#include "Cube.h"

Cube::Cube(GLfloat r, GLfloat g, GLfloat b) : GLObject(3, 3) {
    // initialize the colors vector
    this->colors = std::vector<GLfloat>();
    // initialize the vertices for the cube
    this->initVertices();
    // set the colors to the whole cube
    this->setColors(r, g, b);

    // unbind any VAO, to prevent unwanted behavior when generating the VBOs
    glBindVertexArray(0);

    // generate the VBOs
    glGenBuffers(1, &this->verticesVBO);
    glGenBuffers(1, &this->colorsVBO);
}

Cube::~Cube() {
    // delete the VBOs
    glDeleteBuffers(GL_ARRAY_BUFFER, &(this->verticesVBO));
    glDeleteBuffers(GL_ARRAY_BUFFER, &(this->colorsVBO));
}

void Cube::bind(GLuint VAO) const {
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
        glBufferData(GL_ARRAY_BUFFER, this->colors.size() * sizeof(this->colors[0]), &this->colors.front(),
                     GL_STATIC_DRAW);
        glVertexAttribPointer(this->COLOR_ATTRIB, this->POINTS_PER_COLOR, GL_FLOAT, GL_FALSE,
                              this->POINTS_PER_COLOR * sizeof(GLfloat), nullptr);
        glEnableVertexAttribArray(this->COLOR_ATTRIB);
    }

    // unbind all buffers and vertex array
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Cube::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Cube::draw(GLuint VAO) const {
    // bind necessary buffers
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->verticesVBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->colorsVBO);

    // draw data stored in VAO
    glDrawArrays(GL_TRIANGLES, 0, this->vertices.size() / this->POINTS_PER_VERTEX);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Cube::initVertices() {
    this->vertices = {
            -1.0f, -1.0f, -1.0f,        // triangle 1 : begin
            -1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,        // triangle 1 : end
            1.0f, 1.0f, -1.0f,        // triangle 2 : begin
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,        // triangle 2 : end
            1.0f, -1.0f, 1.0f,        // triangle 3 : begin
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,        // triangle 3 : end
            1.0f, 1.0f, -1.0f,        // triangle 4 : begin
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,        // triangle 4 : end
            -1.0f, -1.0f, -1.0f,        // triangle 5 : begin
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,        // triangle 5 : end
            1.0f, -1.0f, 1.0f,        // triangle 6 : begin
            -1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,        // triangle 6 : end
            -1.0f, 1.0f, 1.0f,        // triangle 7 : begin
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,        // triangle 7 : end
            1.0f, 1.0f, 1.0f,        // triangle 8 : begin
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,        // triangle 8 : end
            1.0f, -1.0f, -1.0f,        // triangle 9 : begin
            1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,        // triangle 9 : end
            1.0f, 1.0f, 1.0f,        // triangle 10 : begin
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,        // triangle 10 : end
            1.0f, 1.0f, 1.0f,        // triangle 11 : begin
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,        // triangle 11 : end
            1.0f, 1.0f, 1.0f,        // triangle 12 : begin
            -1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f         // triangle 12 : end
    };
}

