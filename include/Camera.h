//
// Created by nissi on 4/30/2020.
//

#ifndef GRAFICASOPENGL_CAMERA_H
#define GRAFICASOPENGL_CAMERA_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL_events.h>

// initial camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 3.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
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
    Camera( glm::vec3 cameraPosition = glm::vec3( 0.0f, 0.0f, 0.0f ),
            glm::vec3 cameraUp = glm::vec3( 0.0f, 1.0f, 0.0f ),
            float yaw = YAW, float pitch = PITCH );
    // scalar constructor
    Camera( float, float, float, float, float, float,
            float yaw = YAW, float pitch = YAW );

    glm::mat4 getViewMatrix() { return glm::lookAt( cameraPosition, cameraPosition + cameraFront, cameraUp ); }

    /* Event Interface functions */
    void handleEvent( Camera_Movement, bool wasEventKeyDown );
    void handleEvent( Sint32 deltaX, Sint32 deltaY );

    // move camera with deltatime
    void moveCamera( float );
private:
    // update front, up and right vectors
    void updateCameraVectors();

    // reset keys
    void resetConstantKeys();
    // keys that need to be checked for constant input
    bool keys[TOTAL_KEYS];
};



#endif //GRAFICASOPENGL_CAMERA_H
