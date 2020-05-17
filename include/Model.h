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
    /**
     * Contructor of the model
     * @param path path of the obj containing the data of the blender object
     * @param position initial position of the model
     * @param scaling initial size of the model
     * @param color initial color of the model
     * @param colorMap mapping of a mesh (name) and its corresponding color
     */
    explicit Model(std::string path, const glm::vec3 &position, const glm::vec3 &scaling, const glm::vec3 &color, std::unordered_map<std::string, glm::vec3> colorMap = {});

    /**
     * Constructor of the model without specifying the position
     * @param path path of the obj containing the data of the blender object
     * @param scaling initial size of the model
     * @param color initial color of the model
     * @param colorMap mapping of a mesh (name) and its corresponding color
     */
    Model(std::string path, const glm::vec3 &scaling, const glm::vec3 &color, std::unordered_map<std::string, glm::vec3> colorMap = {});

    /**
     * draw the model using the passed shader
     * @param shader shader program initialized by opengl
     * @param selected whether the model is currently selected
     */
    void draw(const Shader &shader, bool selected);

    /**
     * handle the keyboard events
     * @param event SDL event object
     */
    void handleEvent(const SDL_Event &event) override;

    /**
     * Add a color to a mesh (name)
     * @param meshName name of the mesh to add a color to
     * @param color value of the color (r,g,b) to set the mesh to
     */
    void addMeshColor(const std::string &meshName, glm::vec3 color);

    /**
     * translate the vector a distance directed by the vector
     * @param translationVector vector containing the values of the movement
     */
    void translate(glm::vec3 translationVector) override;

private:
    // vector of the meshes
    std::vector<Mesh> meshes;
    // map of the name of the mesh and its color
    std::unordered_map<std::string, glm::vec3> colorMap;
    // path of the obj
    std::string path;
    // color of all the meshes
    glm::vec3 color;

    /**
     * load the model from the obj path
     */
    inline void loadModel();

    /**
     * process a node from the aiScene from assimp
     * @param node aiNode to process
     * @param scene aiScene currently loaded by assimp
     */
    void processNode(aiNode *node, const aiScene *scene);

    /**
     * process a mesh loaded from assimp, that that corresponds to aiNode
     * @param mesh mesh data
     * @return returns a mesh object with its buffers and vertices
     */
    Mesh processMesh(aiMesh *mesh);
};

#endif //GRAFICASOPENGL_MODEL_H
