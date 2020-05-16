//
// Created by nissim on 4/28/2020.
//

#ifndef GRAFICASOPENGL_SHADER_H
#define GRAFICASOPENGL_SHADER_H

#include <string>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <GL/glew.h>

class ShaderException : public std::exception {
public:
    explicit ShaderException(std::string);

    const char *what() const noexcept override;

private:
    std::string errorMessage;
};

class Shader {
public:
    /**
     * function that loads and compiles a vertex and fragment shader
     * @param vertexFilePath path of the vertex shader
     * @param fragmentFilePath path of the fragment shader
     * @return the identifier of the compiled program that executes the shaders
     */
    Shader(const std::string &, const std::string &);

    void use() const;

    GLuint ID;

    void setBool(const std::string &, bool) const;

    void setInt(const std::string &, int) const;

    void setFloat(const std::string &, float) const;

    void setMat4(const std::string &, glm::mat4) const;

    void setVec3(const std::string &, glm::vec3) const;
};


#endif //GRAFICASOPENGL_SHADER_H
