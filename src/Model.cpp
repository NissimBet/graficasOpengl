//
// Created by jcfflores on 5/12/20.
//

#include "Model.h"
#include "Mesh.h"
#include "Vertex.h"
#include "Shader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <sstream>
#include <utility>

#ifdef DEBUG
#include <iostream>
#endif

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

ModelException::ModelException(const std::string &modelName, const char *errorInfo) {
    std::ostringstream os;
    os << "Failed to load model at " << modelName << " ";
    os << "Error info: " << errorInfo;
    this->errorMessage = os.str();
}

const char *ModelException::what() const noexcept {
    return errorMessage.c_str();
}

Model::Model(std::string path, const glm::vec3 &scaling, const glm::vec3 &color, std::unordered_map<std::string, glm::vec3> colorMap) : WorldObject(glm::vec3(0.0f)),
                                                                                   color(color), path(std::move(path)), colorMap(std::move(colorMap)) {
    loadModel();
    this->scale(scaling);
}

Model::Model(std::string path, const glm::vec3 &position, const glm::vec3 &scaling, const glm::vec3 &color, std::unordered_map<std::string, glm::vec3> colorMap)
        : WorldObject(position), path(std::move(path)), color(color), colorMap(std::move(colorMap)) {
    loadModel();
    this->scale(scaling);
}

void Model::translate(glm::vec3 translationMatrix) {
    WorldObject::translate(translationMatrix);
#ifdef DEBUG
    std::cout << "Position of " << path << " at: ";
    std::cout << "(" << position.x << "," << position.y << "," << position.z << ")" << std::endl;
#endif
}

float scalingFactor = 1.5f;

void Model::handleEvent(const SDL_Event &event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
            this->rotate(15.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        } else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
            this->rotate(15.0f, glm::vec3(0.0f, -1.0f, 0.0f));
        } else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
            this->rotate(15.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        } else if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
            this->rotate(15.0f, glm::vec3(-1.0f, 0.0f, 0.0f));
        } else if (event.key.keysym.scancode == SDL_SCANCODE_X) {
            this->scale(glm::vec3(scalingFactor, scalingFactor, scalingFactor));
        } else if (event.key.keysym.scancode == SDL_SCANCODE_Z) {
            this->scale(glm::vec3(1 / scalingFactor, 1 / scalingFactor, 1 / scalingFactor));
        } else if (event.key.keysym.scancode == SDL_SCANCODE_L) {
            this->translate(glm::vec3(1.0f, 0.0f, 0.0f));
        } else if (event.key.keysym.scancode == SDL_SCANCODE_J) {
            this->translate(glm::vec3(-1.0f, 0.0f, 0.0f));
        } else if (event.key.keysym.scancode == SDL_SCANCODE_K) {
            this->translate(glm::vec3(0.0f, 0.0f, 1.0f));
        } else if (event.key.keysym.scancode == SDL_SCANCODE_I) {
            this->translate(glm::vec3(0.0f, 0.0f, -1.0f));
        }
    }
}

void Model::draw(const Shader &program, bool selected) {
    program.use();
    program.setMat4("model", this->modelMatrix);
    program.setFloat("selected", selected ? 1.0f : 0.55f);
    program.setVec3("highlight", glm::vec3(0.75f, 0.75f, 0.75f));
    for (auto &mesh : meshes) {
        mesh.draw();
    }
}

void Model::loadModel() {
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        throw ModelException(path, import.GetErrorString());
    }

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    // process meshes
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh));
    }
    // process child nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

void Model::addMeshColor(const std::string &meshName, glm::vec3 meshColor) {
    colorMap.insert(std::make_pair(meshName, meshColor));
}

Mesh Model::processMesh(aiMesh *mesh) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::string meshName(mesh->mName.C_Str());
    trim(meshName);

#ifdef DEBUG
    if (path.find("tree") == std::string::npos) {
        std::cout << "Mesh name: " << meshName << std::endl;
    }
#endif

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        glm::vec3 vColor;
        auto mColor = colorMap.find(meshName);
        if(mColor == colorMap.end()) {
            vColor = this->color;
        } else {
            vColor = mColor->second;
        }
        Vertex vertex = {vector, vColor};
        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    return Mesh(vertices, indices);
}