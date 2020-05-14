//
// Created by jcfflores on 5/12/20.
//

#ifndef GRAFICASOPENGL_MODEL_H
#define GRAFICASOPENGL_MODEL_H

#include <vector>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <assimp/material.h>
#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"

struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;

class Model {
public:
    Model(const std::string &path) {
        loadModel(path);
        this->modelMatrix = glm::mat4(1.0f);
        this->worldPosition = glm::vec3(1.0f);
    }
    void draw(Shader);

    glm::mat4 modelMatrix;
    glm::vec3 worldPosition;
private:
    std::vector<Texture> textures_loaded;
    std::vector<Mesh> meshes;
    std::string directory;

    void loadModel(const std::string &);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string &typeName);

};

#endif //GRAFICASOPENGL_MODEL_H
