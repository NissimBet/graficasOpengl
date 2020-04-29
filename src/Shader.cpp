//
// Created by nissi on 4/28/2020.
//

#include "Shader.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

GLuint Shader::LoadShaders(const char *vertexFilePath, const char *fragmentFilePath) {
    GLuint VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vertexShaderCode;
    std::ifstream vertexShaderFileStream(vertexFilePath, std::ios::in);
    if (vertexShaderFileStream.is_open()) {
        std::stringstream sstr;
        sstr << vertexShaderFileStream.rdbuf();
        vertexShaderCode = sstr.str();
        vertexShaderFileStream.close();
    }
    else {
        std::cout << "Error, could not open vertex shader at "  <<  vertexFilePath << std::endl;
        return 0;
    }

    std::string fragmentShaderCode;
    std::ifstream fragmentShaderFileStream(fragmentFilePath, std::ios::in);
    if(fragmentShaderFileStream.is_open()) {
        std::stringstream sstr;
        sstr << fragmentShaderFileStream.rdbuf();
        fragmentShaderCode = sstr.str();
        fragmentShaderFileStream.close();
    }
    else {
        std::cout << "Error, could not open vertex shader at "  <<  fragmentFilePath << std::endl;
        return 0;
    }

    GLint result = GL_FALSE;
    int infoLogLength;

    std::cout << "Compiling shader "  <<  vertexFilePath << std::endl;
    char const * vertexSourcePointer = vertexShaderCode.c_str();
    glShaderSource(VertexShaderId, 1, &vertexSourcePointer, nullptr);
    glCompileShader(VertexShaderId);

    glGetShaderiv(VertexShaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(VertexShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if(infoLogLength > 0) {
        std::vector<char> vertexShaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(VertexShaderId, infoLogLength, nullptr, &vertexShaderErrorMessage.at(0));
        std::cout << &vertexShaderErrorMessage.at(0) << std::endl;
    }

    std::cout << "Compiling shader "  <<  fragmentFilePath << std::endl;
    char const * fragmentSourcePointer = fragmentShaderCode.c_str();
    glShaderSource(FragmentShaderId, 1, &fragmentSourcePointer, nullptr);
    glCompileShader(FragmentShaderId);

    glGetShaderiv(FragmentShaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(FragmentShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if(infoLogLength > 0) {
        std::vector<char> fragmentShaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(FragmentShaderId, infoLogLength, nullptr, &fragmentShaderErrorMessage.at(0));
        std::cout << &fragmentShaderErrorMessage.at(0) << std::endl;
    }

    std::cout << "Linking Program " << std::endl;

    GLuint programId = glCreateProgram();
    glAttachShader(programId, VertexShaderId);
    glAttachShader(programId, FragmentShaderId);
    glLinkProgram(programId);

    glGetProgramiv(programId, GL_LINK_STATUS, &result);
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength < 0) {
        std::vector<char> ProgramErrorMessage(infoLogLength+1);
        glGetProgramInfoLog(programId, infoLogLength, nullptr, &ProgramErrorMessage[0]);
        std::cout << &ProgramErrorMessage.at(0);
    }

    glDetachShader(programId, VertexShaderId);
    glDetachShader(programId, FragmentShaderId);

    glDeleteShader(VertexShaderId);
    glDeleteShader(FragmentShaderId);

    return programId;
}
