//
// Created by jcfflores on 5/12/20.
//

#ifndef GRAFICASOPENGL_MODEL_H
#define GRAFICASOPENGL_MODEL_H

#include <vector>
#include <string>
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <assimp/material.h>
#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"
#include "WorldObject.h"

struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;

class ModelException : public std::exception {
public:
    ModelException(const std::string &, const char *);

    const char *what() const noexcept override;

private:
    std::string errorMessage;
};

class Model : public WorldObject {
public:
    explicit Model(std::string path, const glm::vec3 &position, const glm::vec3 &scaling, const glm::vec3 &color);

    Model(std::string path, const glm::vec3 &scaling, const glm::vec3 &color);

    void draw(const Shader &, bool);

    void handleEvent(const SDL_Event &event) override;

    void translate(glm::vec3 translationMatrix) override;

private:
    std::vector<Texture> textures_loaded;
    std::vector<Mesh> meshes;
    std::string directory;
    std::string path;
    glm::vec3 color;

    void loadModel();

    void processNode(aiNode *node, const aiScene *scene);

    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string &typeName);


};

#endif //GRAFICASOPENGL_MODEL_H
