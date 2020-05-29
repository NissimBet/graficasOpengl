//
// Created by nissi on 5/20/2020.
//

#ifndef GRAFICASOPENGL_TEXTURE_H
#define GRAFICASOPENGL_TEXTURE_H

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#include <string>
#include <GL/glew.h>

struct Texture {
    unsigned int id;
};

unsigned int loadTextureFromFile(const char *path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, components;
    unsigned char *data = stbi_load(path, &width, &height, &components, 0);
    if (data) {
        GLenum format;
        if (components == 1) {
            format = GL_RED;
        } else if (components == 3) {
            format = GL_RGB;
        } else if (components == 4) {
            format = GL_RGBA;
        }
//        std::cout << "Bind Texture " << path << ' ' << textureID << '\t' << glGetError() << std::endl;
        glBindTexture(GL_TEXTURE_2D, textureID);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//        std::cout << "Set Texture Data " << path << ' ' << textureID << '\t' << glGetError() << std::endl;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//        std::cout << "Create MipMap" << '\t' << glGetError() << std::endl;
        glGenerateMipmap(GL_TEXTURE_2D);

        // texture wrapping
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // texture filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else {
        std::cerr << "Failed to load texture image at " << path << std::endl;
        std::cerr << stbi_failure_reason() << std::endl;
    }
    stbi_image_free(data);

    return textureID;
}

#endif //GRAFICASOPENGL_TEXTURE_H
