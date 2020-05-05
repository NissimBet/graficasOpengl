//
// Created by nissi on 4/30/2020.
//

#include "Camera.h"

void Camera::handleEvent( Camera_Movement direction, bool wasEventKeyPressed ) {
    switch (direction) {
        case Camera::FORWARD:
            keys[KEY_UP] = wasEventKeyPressed;
            break;
        case Camera::BACKWARD:
            keys[KEY_DOWN] = wasEventKeyPressed;
            break;
        case Camera::LEFT:
            keys[KEY_LEFT] = wasEventKeyPressed;
            break;
        case Camera::RIGHT:
            keys[KEY_RIGHT] = wasEventKeyPressed;
            break;
        default:
            break;
    }
}

void Camera::handleEvent(const SDL_Event &event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_D:
                this->handleEvent( Camera::Camera_Movement::RIGHT, true );
                break;
            case SDL_SCANCODE_A:
                this->handleEvent( Camera::Camera_Movement::LEFT, true );
                break;
            case SDL_SCANCODE_W:
                this->handleEvent( Camera::Camera_Movement::FORWARD, true );
                break;
            case SDL_SCANCODE_S:
                this->handleEvent( Camera::Camera_Movement::BACKWARD, true );
                break;
            default:
                break;
        }
    }
    else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_D:
                this->handleEvent( Camera::Camera_Movement::RIGHT, false );
                break;
            case SDL_SCANCODE_A:
                this->handleEvent( Camera::Camera_Movement::LEFT, false );
                break;
            case SDL_SCANCODE_W:
                this->handleEvent( Camera::Camera_Movement::FORWARD, false );
                break;
            case SDL_SCANCODE_S:
                this->handleEvent( Camera::Camera_Movement::BACKWARD, false );
                break;
            default:
                break;
        }
    }
    else if (event.type == SDL_MOUSEMOTION) {
        Sint32 mouseDeltaX = event.motion.xrel;
        Sint32 mouseDeltaY = event.motion.yrel;
        this->handleEvent( mouseDeltaX, mouseDeltaY );
    }
}

void Camera::handleEvent( Sint32 deltaX, Sint32 deltaY ) {
    // rotation in y axis, resets every 360 degrees
    this->yaw = glm::mod( this->yaw + deltaX * this->mouseSensitivity, 360.0f );
    // rotation in x axis
    this->pitch += deltaY * this->mouseSensitivity;

    // keep pitch at most 90 degrees up or down
    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    else if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    //SDL_WarpMouseGlobal(0,0);
    updateCameraVectors();
}

void Camera::moveCamera( float deltaTime ) {
    // units to move this frame
    float velocity = movementSpeed * deltaTime;

    // check if key is being pressed and move accordingly
    if (keys[KEY_UP]) {
        cameraPosition += cameraFront * velocity;
    }
    if (keys[KEY_DOWN]) {
        cameraPosition -= cameraFront * velocity;
    }
    if (keys[KEY_RIGHT]) {
        cameraPosition += cameraRight * velocity;
    }
    if (keys[KEY_LEFT]) {
        cameraPosition -= cameraRight * velocity;
    }

    // stay on the floor
    //cameraPosition.y = 0.0f;
}

void Camera::updateCameraVectors() {
    // new front direction of camera
    glm::vec3 front;

    // rotate front according to mouse movement
    // use euler angles to calculate rotation
    front.x = glm::cos( glm::radians( pitch ) ) * glm::cos( glm::radians( yaw ) );
    // pitch is reversed for inverted y-axis rotation
    front.y = glm::sin( glm::radians( -pitch ) );
    front.z = glm::cos( glm::radians( pitch ) ) * glm::sin( glm::radians( yaw ) );

    // normalize vector to make sure it does not scale
    cameraFront = glm::normalize( front );

    // camera right is perpendicular to camera front and world up
    cameraRight = glm::normalize( glm::cross( cameraFront, worldUp ) );
    // camera up is perpendicular of camera right and up
    cameraUp = glm::normalize( glm::cross( cameraRight, cameraFront ) );
}

void Camera::resetConstantKeys() {
    for (bool & key : keys) {
        key = false;
    }
}