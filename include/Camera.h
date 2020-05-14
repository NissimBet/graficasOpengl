//
// Created by nissi on 4/30/2020.
//

#ifndef GRAFICASOPENGL_CAMERA_H
#define GRAFICASOPENGL_CAMERA_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL_events.h>

// initial camera values
const float YAW = -90.0f;
// initial
const float PITCH = 0.0f;
// movement speed of the camera
const float SPEED = 5.0f;
// mouse sensitivity
const float SENSITIVITY = 0.1f;
// fov
const float ZOOM = 45.0f;

class Camera
{
public:
    // check for multiple keys pressed at once
    enum ContinuedCheckKeys
    {
        KEY_UP = 0,		// Forward
        KEY_DOWN = 1,	// Backward
        KEY_LEFT = 2,	// Left
        KEY_RIGHT = 3,	// Right
        TOTAL_KEYS = 4
    };

    // Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
    enum Camera_Movement
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    // camera base position in world
    glm::vec3 cameraPosition;
    // camera base directions
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::vec3 cameraRight;
    // world up direction
    glm::vec3 worldUp;

    // rotation on y-axis
    float yaw;
    // rotation on x-axis
    float pitch;
    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    // vector constructor
    explicit Camera(
            glm::vec3 cameraPosition = glm::vec3( 0.0f, 0.0f, 0.0f ),
            glm::vec3 cameraUp = glm::vec3( 0.0f, 1.0f, 0.0f ),
            glm::vec3 cameraFront = glm::vec3( 0.0f, 0.0f, -1.0f ),
            float yaw = YAW, float pitch = PITCH, float zoom = ZOOM,
            float moveSpeed = SPEED, float sensitivity = SENSITIVITY)
            :   cameraPosition(cameraPosition), cameraUp(cameraUp),
                cameraFront(cameraFront), yaw(yaw),
                pitch(pitch), zoom(zoom), movementSpeed(moveSpeed),
                mouseSensitivity(sensitivity), worldUp(cameraUp)
    {
        resetConstantKeys();
        updateCameraVectors();
    };

    /**
     * function that gets the view matrix of the camera
     * @return
     */
    glm::mat4 getViewMatrix() const {
        return glm::lookAt( cameraPosition, cameraPosition + cameraFront, cameraUp );
    }

    /**
     * main event handler, calls the corresponding specific event handler
     * @param event objetct with event data
     */
    void handleEvent(const SDL_Event &event);

    /**
     * function that handles keypress for camera movement in any of 4 directions
     * @param movementDirection direction of the movement (front, back, left, right)
     * @param wasEventKeyDown whether the key is being pressed or released
     */
    void handleEvent( Camera_Movement movementDirection, bool wasEventKeyDown );
    /**
     * function that handles mouse movement to rotate camera
     * @param deltaX mouse change in x direction
     * @param deltaY mouse change in y direction
     */
    void handleEvent( Sint32 deltaX, Sint32 deltaY );

    // move camera after event handling
    void moveCamera( float deltaTime );
private:
    // update front, up and right vectors
    void updateCameraVectors();

    // reset keys
    void resetConstantKeys();

    // keys that need to be checked for constant input
    bool keys[TOTAL_KEYS];
};

#endif //GRAFICASOPENGL_CAMERA_H
