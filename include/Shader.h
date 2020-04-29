//
// Created by nissim on 4/28/2020.
//

#ifndef GRAFICASOPENGL_SHADER_H
#define GRAFICASOPENGL_SHADER_H

#include <GL/glew.h>

class Shader {
public:
    static GLuint LoadShaders(const char * vertexFilePath, const char * fragmentFilePath);
};


#endif //GRAFICASOPENGL_SHADER_H
