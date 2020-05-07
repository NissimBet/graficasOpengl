//
// Created by nissi on 5/3/2020.
//

#ifndef GRAFICASOPENGL_CYLINDER_H
#define GRAFICASOPENGL_CYLINDER_H

#include "GLObject.h"

class Cylinder: public GLObject {
public:
    Cylinder();
    ~Cylinder();

    void bind(GLuint VAO) const override;
    void unbind() const override;
    void draw(GLuint VAO) const override;
private:
    /**
     * function that initializes the vertices array
     */
    void initVertices();
};


#endif //GRAFICASOPENGL_CYLINDER_H
