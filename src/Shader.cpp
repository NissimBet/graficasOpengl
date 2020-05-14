//
// Created by nissi on 4/28/2020.
//

#include "Shader.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <glm/ext.hpp>

GLuint Shader::LoadShaders(const char *vertexFilePath, const char *fragmentFilePath) {
    // create shaders
    GLuint VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    // load the code of the vertex shader from file and store in string
    std::string vertexShaderCode;
    std::ifstream vertexShaderFileStream(vertexFilePath, std::ios::in);
    if (vertexShaderFileStream.is_open()) {
        std::stringstream sstr;
        sstr << vertexShaderFileStream.rdbuf();
        vertexShaderCode = sstr.str();
        vertexShaderFileStream.close();
    }
    else {
        std::cerr << "Error, could not open vertex shader at "  <<  vertexFilePath << std::endl;
        return 0;
    }

    // load the code of the vertex shader from file and store in string
    std::string fragmentShaderCode;
    std::ifstream fragmentShaderFileStream(fragmentFilePath, std::ios::in);
    if(fragmentShaderFileStream.is_open()) {
        std::stringstream sstr;
        sstr << fragmentShaderFileStream.rdbuf();
        fragmentShaderCode = sstr.str();
        fragmentShaderFileStream.close();
    }
    else {
        std::cerr << "Error, could not open vertex shader at "  <<  fragmentFilePath << std::endl;
        return 0;
    }

    GLint result = GL_FALSE;
    int infoLogLength;

    // compile vertex shader
    std::cout << "Compiling shader "  <<  vertexFilePath << std::endl;
    char const * vertexSourcePointer = vertexShaderCode.c_str();
    glShaderSource(VertexShaderId, 1, &vertexSourcePointer, nullptr);
    glCompileShader(VertexShaderId);

    // check vertex shader compilation status
    glGetShaderiv(VertexShaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(VertexShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if(infoLogLength > 0) {
        std::vector<char> vertexShaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(VertexShaderId, infoLogLength, nullptr, &vertexShaderErrorMessage.at(0));
        std::cout << &vertexShaderErrorMessage.at(0) << std::endl;
    }

    // compile fragment shader
    std::cout << "Compiling shader "  <<  fragmentFilePath << std::endl;
    char const * fragmentSourcePointer = fragmentShaderCode.c_str();
    glShaderSource(FragmentShaderId, 1, &fragmentSourcePointer, nullptr);
    glCompileShader(FragmentShaderId);

    // check fragment shader compilation status
    glGetShaderiv(FragmentShaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(FragmentShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if(infoLogLength > 0) {
        std::vector<char> fragmentShaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(FragmentShaderId, infoLogLength, nullptr, &fragmentShaderErrorMessage.at(0));
        std::cout << &fragmentShaderErrorMessage.at(0) << std::endl;
    }

    std::cout << "Linking Program " << std::endl;

    // link shaders to program
    GLuint programId = glCreateProgram();
    glAttachShader(programId, VertexShaderId);
    glAttachShader(programId, FragmentShaderId);
    glLinkProgram(programId);

    // chek link status
    glGetProgramiv(programId, GL_LINK_STATUS, &result);
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength < 0) {
        std::vector<char> ProgramErrorMessage(infoLogLength+1);
        glGetProgramInfoLog(programId, infoLogLength, nullptr, &ProgramErrorMessage[0]);
        std::cout << &ProgramErrorMessage.at(0);
    }

    // detach and delete shaders, they are not needed
    glDetachShader(programId, VertexShaderId);
    glDetachShader(programId, FragmentShaderId);

    glDeleteShader(VertexShaderId);
    glDeleteShader(FragmentShaderId);

    this->ID = programId;
    return this->ID;
}


void Shader::setBool( const std::string &name, bool value ) const {
    glUniform1i( glGetUniformLocation( ID, name.c_str() ), ( int ) value );
}
void Shader::setInt( const std::string &name, int value ) const {
    glUniform1i( glGetUniformLocation( ID, name.c_str() ), value );
}
void Shader::setFloat( const std::string &name, float value ) const {
    glUniform1f( glGetUniformLocation( ID, name.c_str() ), value );
}
void Shader::setMat4( const std::string &name, glm::mat4 value ) const {
    glUniformMatrix4fv( glGetUniformLocation( ID, name.c_str() ), 1, GL_FALSE, glm::value_ptr( value ) );
}
void Shader::setVec3( const std::string &name, glm::vec3 value ) const {
    glUniform3f( glGetUniformLocation( ID, name.c_str() ), value.x, value.y, value.z );
}