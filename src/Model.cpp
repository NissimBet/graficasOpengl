//
// Created by jcfflores on 5/12/20.
//

#include "Model.h"
#include "Mesh.h"
#include "Vertex.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <sstream>
#include <utility>

ModelException::ModelException(const std::string &modelName, const char *errorInfo) {
    std::ostringstream os;
    os << "Failed to load model at " << modelName << " ";
    os << "Error info: " << errorInfo;
    this->errorMessage = os.str();
}

const char *ModelException::what() const noexcept {
    return errorMessage.c_str();
}

Model::Model(std::string path, const glm::vec3 &scaling, const glm::vec3 &color) : WorldObject(glm::vec3(0.0f)),
                                                                                   color(color), path(std::move(path)) {
    loadModel();
    this->scale(scaling);
}

Model::Model(std::string path, const glm::vec3 &position, const glm::vec3 &scaling, const glm::vec3 &color)
        : WorldObject(position), path(std::move(path)), color(color) {
    loadModel();
    this->scale(scaling);
}

void Model::translate(glm::vec3 translationMatrix) {
    WorldObject::translate(translationMatrix);
    std::cout << "Position of " << path << " at: ";
    std::cout << "(" << position.x << "," << position.y << "," << position.z << ")" << std::endl;
}

unsigned int TextureFromFile(const std::string &path, const std::string &directory, bool gamma = false);

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
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    // process meshes
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // process child nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        vertex.Color = this->color;
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