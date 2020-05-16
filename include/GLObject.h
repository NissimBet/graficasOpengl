//
// Created by nissi on 5/2/2020.
//

#ifndef GRAFICASOPENGL_GLOBJECT_H
#define GRAFICASOPENGL_GLOBJECT_H

#include <GL/glew.h>
#include <vector>

class GLObject {
public:
    GLObject(GLuint PPV, GLuint PPC) : POINTS_PER_VERTEX(PPV), POINTS_PER_COLOR(PPC), verticesVBO(0), colorsVBO(0) {};

    /**
     * bind the array buffers to the given the vertex array object
     * @param VAO vertex array object to bind data buffers
     */
    virtual void bind(GLuint VAO) const = 0;

    /**
     * unbind the buffers
     */
    virtual void unbind() const = 0;

    /**
     * function that draws the defined object
     * @param VAO vertex array object to bind to before drawing
     */
    virtual void draw(GLuint VAO) const = 0;

    /**
     * set color vertices of object.
     * If number of points per color does not match the number of points per vertex and its size, do not assign to prevent errors
     * @param newColors new colors matrix
     * @returns if the colors could be set
     */
    bool setColors(const std::vector<GLfloat> &newColors) {
        if (newColors.size() / this->POINTS_PER_COLOR == GLObject::vertices.size() / this->POINTS_PER_VERTEX) {
            this->colors = newColors;
            return true;
        } else {
            return false;
        }
    }

    void setColors(const GLfloat r, GLfloat g, GLfloat b) {
        this->colors = std::vector<GLfloat>(this->vertices.size());
        for (int i = 0; i < this->vertices.size() - 2; i += 3) {
            this->colors[i] = r;
            this->colors[i + 1] = g;
            this->colors[i + 2] = b;
        }
    }

protected:
    // vertices VBO identifier
    GLuint verticesVBO;
    // colors VBO identifier
    GLuint colorsVBO;

    // vertices data, static because the object's vertices shouldn't change, every object uses transformation matrices
    std::vector<GLfloat> vertices;

    // colors data
    std::vector<GLfloat> colors;

    // number of points per vertex (x,y,z)
    const GLuint POINTS_PER_VERTEX;
    // number of points per color (r,g,b)
    const GLuint POINTS_PER_COLOR;

    // shader attribute locations for consistency
    const GLuint VERTEX_ATTRIB = 0;
    const GLuint NORMAL_ATTRIB = 1;
    const GLuint TEXTURE_ATTRIB = 2;
    const GLuint COLOR_ATTRIB = 3;
};

#endif //GRAFICASOPENGL_GLOBJECT_H
