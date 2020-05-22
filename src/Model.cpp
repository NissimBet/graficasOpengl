#include "Model.h"
#include "Mesh.h"
#include "Vertex.h"
#include "Shader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <sstream>
#include <utility>

#ifndef NDEBUG
#include <iostream>
#endif

ModelException::ModelException(const std::string &modelName, const char *errorInfo) {
    std::ostringstream os;
    os << "Failed to load model at " << modelName << " ";
    os << "Error info: " << errorInfo;
    this->errorMessage = os.str();
}

const char *ModelException::what() const noexcept {
    return errorMessage.c_str();
}

Model::Model(std::string path, const glm::vec3 &scaling, const glm::vec3 &color, std::unordered_map<std::string, glm::vec3> colorMap, std::unordered_map<std::string, unsigned int> textureMap)
        : WorldObject(glm::vec3(0.0f)), color(color), path(std::move(path)), colorMap(std::move(colorMap)), textureMap(std::move(textureMap)), textureID(0) {
    loadModel();
    this->scale(scaling);
}

Model::Model(std::string path, const glm::vec3 &position, const glm::vec3 &scaling, const glm::vec3 &color, std::unordered_map<std::string, glm::vec3> colorMap, std::unordered_map<std::string, unsigned int> textureMap)
        : WorldObject(position), path(std::move(path)), color(color), colorMap(std::move(colorMap)), textureMap(std::move(textureMap)), textureID(0) {
    loadModel();
    this->scale(scaling);
}

Model::Model(std::string path, const glm::vec3 &scaling, const glm::vec3 &color, unsigned int textureID, std::unordered_map<std::string, unsigned int> textureMap)
        : WorldObject(glm::vec3(0.0f)), path(std::move(path)), color(color), textureID(textureID), textureMap(std::move(textureMap)) {
    loadModel();
    this->scale(scaling);
}


void Model::translate(glm::vec3 translationVector) {
    // translate the object
    WorldObject::translate(translationVector);
#ifndef NDEBUG
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
    // bind the shader
    program.use();
    // set the model matrix of the object
    program.setMat4("model", this->modelMatrix);
    // set if the object is currently selected
    program.setFloat("selected", selected ? 1.0f : 0.55f);
    // set highlighting color
    program.setVec3("highlight", glm::vec3(0.75, 0.75, 0.75));
    // draw the meshes corresponding to the model
    for (auto &mesh : meshes) {
        mesh.draw(program);
    }
}

void Model::loadModel() {
    // initialize and import obj of the model
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    // if the scene could not be loaded, throw error
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        throw ModelException(path, import.GetErrorString());
    }

    // process the main node of the scene
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
    unsigned int meshTexID;

#ifndef NDEBUG
    if (path.find("tree") == std::string::npos) {
        std::cout << "Mesh name: " << meshName << std::endl;
    }
#endif

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        // set the mesh vertices
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        // set the mesh colors
        glm::vec3 vColor;
        // if a color could be bound to the mesh, use it, if not, use the model default color
        auto mColor = colorMap.find(meshName);
        if(mColor == colorMap.end()) {
            vColor = this->color;
        } else {
            vColor = mColor->second;
        }
        // set the coordinates for the textures
        glm::vec2 vTextures = {0.0, 0.0};
        if (mesh->mTextureCoords[0]) {
            vTextures.x = mesh->mTextureCoords[0][i].x;
            vTextures.y = mesh->mTextureCoords[0][i].y;
        }
        Vertex vertex = {vector, vColor, vTextures};
        vertices.push_back(vertex);
    }

    // set the indices of the vertices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    auto texID = textureMap.find(meshName);
    if (texID == textureMap.end()) {
//        std::cout << "Texture bound to mesh " << meshName << '\t' << this->textureID << std::endl;
        meshTexID = this->textureID;
    }
    else {
        meshTexID = texID->second;
    }
#ifndef NDEBUG
    std::cout << "Texture bound to mesh " << meshName << '\t' << meshTexID << std::endl;
#endif

    return Mesh(vertices, indices, meshTexID);
}