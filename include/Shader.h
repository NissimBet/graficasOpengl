//
// Created by nissim on 4/28/2020.
//

#ifndef GRAFICASOPENGL_SHADER_H
#define GRAFICASOPENGL_SHADER_H

#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>

class Shader {
public:
    /**
     * function that loads and compiles a vertex and fragment shader
     * @param vertexFilePath path of the vertex shader
     * @param fragmentFilePath path of the fragment shader
     * @return the identifier of the compiled program that executes the shaders
     */
    GLuint LoadShaders(const char * vertexFilePath, const char * fragmentFilePath);

    void use() const {
        glUseProgram(this->ID);
    };

    GLuint ID;

    void setBool( const std::string &, bool ) const;
    void setInt( const std::string &, int ) const;
    void setFloat( const std::string &, float ) const;
    void setMat4( const std::string &, glm::mat4 ) const;
    void setVec3( const std::string &, glm::vec3 ) const;
};


#endif //GRAFICASOPENGL_SHADER_H
