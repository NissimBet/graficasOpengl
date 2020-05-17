#ifndef GRAFICASOPENGL_CUBE_H
#define GRAFICASOPENGL_CUBE_H

#include "GLObject.h"

class Cube : public GLObject {
public:
    /**
     * Constructor of the cube, calls the creation of the buffers and sets the vertices and colors of the cube
     * @param r amount of red 0-255
     * @param g amount of green 0-255
     * @param b amount of blue 0-255
     */
    Cube(GLfloat r, GLfloat g, GLfloat b);

    /**
     * Virtual destructor, calls for the destruction of the buffers for the vertices and colors
     */
    ~Cube();

    /**
     * Bind the color and vertices buffers to the given VAO
     * @param VAO Vertex array object to bind the VBOs to
     */
    void bind(GLuint VAO) const override;

    /**
     * Unbind both buffers from opengl context
     */
    void unbind() const override;

    /**
     * Draw the contents of the buffers, first binding the buffers to the VAO
     * @param VAO Vertex array object to bind the buffers to
     */
    void draw(GLuint VAO) const override;

private:
    /**
     * function that initializes the array of vertices
     */
    void initVertices();
};

#endif //GRAFICASOPENGL_CUBE_H
