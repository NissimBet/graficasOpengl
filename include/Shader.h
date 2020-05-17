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

    /**
     * bind the shader to opengl context
     */
    void use() const;

    // id of the program of the compiled shader
    GLuint ID;

    /**
     * set a boolean uniform of the shader to a value
     * @param name of the uniform
     * @param value of the uniform
     */
    void setBool(const std::string &name, bool value) const;

    /**
     * set an int uniform of the shader to a value
     * @param name of the uniform
     * @param value of the uniform
     */
    void setInt(const std::string &name, int value) const;

    /**
     * set a float uniform of the shader to a value
     * @param name of the uniform
     * @param value of the uniform
     */
    void setFloat(const std::string &name, float value) const;

    /**
     * set a 4x4 matrix uniform of the shader to a value
     * @param name of the uniform
     * @param value of the uniform
     */
    void setMat4(const std::string &name, glm::mat4 value) const;

    /**
     * set a 3 value vector uniform of the shader to a value
     * @param name of the uniform
     * @param value of the uniform
     */
    void setVec3(const std::string &name, glm::vec3 value) const;
};


#endif //GRAFICASOPENGL_SHADER_H
