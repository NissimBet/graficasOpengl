//
// Created by nissim on 4/28/2020.
//

#ifndef GRAFICASOPENGL_SHADER_H
#define GRAFICASOPENGL_SHADER_H

#include <GL/glew.h>

class Shader {
public:
    /**
     * function that loads and compiles a vertex and fragment shader
     * @param vertexFilePath path of the vertex shader
     * @param fragmentFilePath path of the fragment shader
     * @return the identifier of the compiled program that executes the shaders
     */
    static GLuint LoadShaders(const char * vertexFilePath, const char * fragmentFilePath);
};


#endif //GRAFICASOPENGL_SHADER_H
