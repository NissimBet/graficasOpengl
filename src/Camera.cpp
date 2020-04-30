//
// Created by nissi on 4/30/2020.
//

#include "Camera.h"

#include <iostream>

Camera::Camera( glm::vec3 cameraPosition, glm::vec3 cameraUp, float yaw, float pitch ) {
    // default values

    // Front of camera is the -z direction
    this->cameraFront = glm::vec3( 0.0f, 0.0f, -1.0f );
    // movement speed of the camera
    this->movementSpeed = SPEED;
    // camera rotation sensitivity
    this->mouseSensitivity = SENSITIVITY;
    // camera fov
    this->zoom = ZOOM;

    // position of camera in world
    this->cameraPosition = cameraPosition;
    // up direction of camera
    this->cameraUp = cameraUp;

    this->yaw = yaw;
    this->pitch = pitch;

    // up direction of the world
    this->worldUp = this->cameraUp;

    // initialize the keys for movement
    resetConstantKeys();
    // set the camera vectors (Front, Up, Right)
    updateCameraVectors();
}

Camera::Camera( float posX, float posY, float posZ,
                float upX, float upY, float upZ,
                float yaw, float pitch ) {
    // fron of camera is the -z direction
    this->cameraFront = glm::vec3( 0.0f, 0.0f, -1.0f );
    // camera movement speed
    this->movementSpeed = SPEED;
    // camera rotation speed
    this->mouseSensitivity = SENSITIVITY;
    // camera fov
    this->zoom = ZOOM;

    // camera position in world
    this->cameraPosition = glm::vec3( posX, posY, posZ );
    // camera up direction
    this->worldUp = glm::vec3( upX, upY, upZ );

    this->yaw = yaw;
    this->pitch = pitch;

    // initialize movement keys
    resetConstantKeys();
    // set the camera vectors (Front, Up, Right)
    updateCameraVectors();
}


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
void Camera::handleEvent( Sint32 deltaX, Sint32 deltaY ) {
    this->yaw = glm::mod( this->yaw + deltaX * this->mouseSensitivity, 360.0f );
    this->pitch += deltaY * this->mouseSensitivity;

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
    // new fron of camera
    glm::vec3 front;

    // rotate front according to mouse movement
    // uses euler angles to calculate rotation
    front.x = glm::cos( glm::radians( pitch ) ) * glm::cos( glm::radians( yaw ) );
    // pitch is reversed for inverted y-axis rotation
    front.y = glm::sin( glm::radians( -pitch ) );
    front.z = glm::cos( glm::radians( pitch ) ) * glm::sin( glm::radians( yaw ) );

    // std::printf( "yaw: %.6f\tpitch: %.6f\t%.6f, %.6f, %.6f\n", yaw, pitch, front.x, front.y, front.z );

    // normalize vector to make sure it does not scale
    cameraFront = glm::normalize( front );
    // std::printf( "%.6f\t%.6f\t%.6f\n", cameraFront.x, cameraFront.y, cameraFront.z );

    // camera right is perpendicular to camera front and world up
    cameraRight = glm::normalize( glm::cross( cameraFront, worldUp ) );
    // camera up is perpendicular of camera right and up
    cameraUp = glm::normalize( glm::cross( cameraRight, cameraFront ) );
}

void Camera::resetConstantKeys() {
    for (int i = 0; i < TOTAL_KEYS; i++) {
        keys[i] = false;
    }
}