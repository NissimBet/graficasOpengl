//
// Created by nissi on 5/2/2020.
//

#ifndef GRAFICASOPENGL_CUBE_H
#define GRAFICASOPENGL_CUBE_H

#include "GLObject.h"

class Cube : public GLObject {
public:
    Cube();
    ~Cube();

    void bind(GLuint VAO) const override;
    void unbind() const override;
    void draw(GLuint VAO) const override;
private:
    /**
     * function that initializes the vertices array
     */
    void initVertices();
};

#endif //GRAFICASOPENGL_CUBE_H
