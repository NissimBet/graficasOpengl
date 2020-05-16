//
// Created by jcfflores on 5/12/20.
//

#include "Model.h"
#include "Mesh.h"
#include "Vertex.h"
#include "Texture.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <sstream>
#include <utility>

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

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
    std::cout << "(" << position.x << "," << position.y << "," << position.z << ")";
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
        } else if (event.key.keysym.scancode == SDL_SCANCODE_I) {
            this->translate(glm::vec3(1.0f, 0.0f, 0.0f));
        } else if (event.key.keysym.scancode == SDL_SCANCODE_K) {
            this->translate(glm::vec3(-1.0f, 0.0f, 0.0f));
        } else if (event.key.keysym.scancode == SDL_SCANCODE_L) {
            this->translate(glm::vec3(0.0f, 0.0f, 1.0f));
        } else if (event.key.keysym.scancode == SDL_SCANCODE_J) {
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
        mesh.draw(program.ID);
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
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;
        if (mesh->mTextureCoords[0]) {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TextCoords = vec;
        } else {
            vertex.TextCoords = glm::vec2(0.0f, 0.0f);
        }
        vertex.Color = this->color;
        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    if (mesh->mMaterialIndex >= 0) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<Texture> specularmaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularmaps.begin(), specularmaps.end());
    }

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string &typeName) {
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for (auto &texture : textures_loaded) {
            if (std::strcmp(texture.path.data(), str.C_Str()) == 0) {
                textures.push_back(texture);
                skip = true;
                break;
            }
        }
        Texture texture;
        texture.id = TextureFromFile(str.C_Str(), directory);
        texture.type = typeName;
        texture.path = str.C_Str();
        textures.push_back(texture);
    }
    return textures;
}

unsigned int TextureFromFile(const std::string &path, const std::string &directory, bool gamma) {
    std::string filename = directory + '/' + path;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format;
        if (nrComponents == 1) {
            format = GL_RED;
        } else if (nrComponents == 3) {
            format = GL_RGB;
        } else {
            format = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else {
        std::cerr << "Failed to load texture at: " << path << std::endl;
    }
    stbi_image_free(data);
    return textureID;
}