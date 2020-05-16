//
// Created by nissi on 5/3/2020.
//

#ifndef GRAFICASOPENGL_WORLDOBJECT_H
#define GRAFICASOPENGL_WORLDOBJECT_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <SDL2/SDL_events.h>

class WorldObject {
protected:
    glm::mat4 modelMatrix;
    glm::vec3 position;

public:
    explicit WorldObject(const glm::vec3 &position = glm::vec3(0.0f)) : position(position) {
        this->modelMatrix = glm::translate(glm::mat4(1), position);
    };

    void rotate(float degrees, glm::vec3 rotationAxis) {
        this->modelMatrix = glm::rotate(this->modelMatrix, degrees * glm::pi<float>() / 180.0f, rotationAxis);
    };

    virtual void translate(glm::vec3 translationMagnitude) {
        this->position += translationMagnitude;
        this->modelMatrix = glm::translate(this->modelMatrix, translationMagnitude);
    };

    void setPosition(glm::vec3 newPosition) {
        //this->modelMatrix = glm::translate(this->modelMatrix, -1 * this->position);
        this->position = newPosition;
        this->modelMatrix = glm::translate(this->modelMatrix, this->position);
    };

    void scale(glm::vec3 scalingMagnitudes) {
        this->modelMatrix = glm::scale(this->modelMatrix, scalingMagnitudes);
    };

    glm::mat4 getModelMatrix() {
        return this->modelMatrix;
    }

    glm::vec3 getPositionVector() {
        return this->position;
    }

    virtual void handleEvent(const SDL_Event &event) = 0;
};


#endif //GRAFICASOPENGL_WORLDOBJECT_H
