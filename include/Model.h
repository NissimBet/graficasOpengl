//
// Created by jcfflores on 5/12/20.
//

#ifndef GRAFICASOPENGL_MODEL_H
#define GRAFICASOPENGL_MODEL_H

#include <vector>
#include <string>
#include <unordered_map>
#include <glm/vec3.hpp>
#include <assimp/material.h>
#include "Mesh.h"
#include "WorldObject.h"

struct aiNode;
struct aiScene;
struct aiMesh;

class Shader;

class ModelException : public std::exception {
public:
    ModelException(const std::string &, const char *);

    const char *what() const noexcept override;

private:
    std::string errorMessage;
};

class Model : public WorldObject {
public:
    explicit Model(std::string path, const glm::vec3 &position, const glm::vec3 &scaling, const glm::vec3 &color, std::unordered_map<std::string, glm::vec3> colorMap = {});

    Model(std::string path, const glm::vec3 &scaling, const glm::vec3 &color, std::unordered_map<std::string, glm::vec3> colorMap = {});

    void draw(const Shader &, bool);

    void handleEvent(const SDL_Event &event) override;

    void addMeshColor(const std::string &, glm::vec3);

    void translate(glm::vec3 translationMatrix) override;

private:
    std::vector<Mesh> meshes;
    std::unordered_map<std::string, glm::vec3> colorMap;
    std::string path;
    glm::vec3 color;

    inline void loadModel();

    void processNode(aiNode *node, const aiScene *scene);

    Mesh processMesh(aiMesh *mesh);
};

#endif //GRAFICASOPENGL_MODEL_H
