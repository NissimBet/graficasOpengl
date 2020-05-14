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
#include "WorldObject.h"

struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;

class Model : public WorldObject {
public:
    explicit Model(const std::string &path, glm::vec3 position = glm::vec3(0.0f)) : worldPosition(position), WorldObject() {
        loadModel(path);
    }
    void draw(Shader);

    glm::vec3 worldPosition;
    void handleEvent(const SDL_Event &event) override;
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
