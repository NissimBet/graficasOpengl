#include <iostream>
#include <GL/glew.h>
#ifdef __linux__
#include <SDL2/SDL.h>
#endif
#ifdef _WIN32
#include <SDL.h>
#endif

#include "Shader.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <Camera.h>
#include <Cube.h>

// Screen size
const int WINDOW_WIDTH = 840;
const int WINDOW_HEIGHT = 480;

/**
 * Function that initializes SDL and its subsystems if any
 * @return true if SDL was initialized
 */
bool initializeSDL() {
    // initialize SDL and subsystems (IMG / Audio / etc)
    return SDL_Init(SDL_INIT_EVERYTHING) == 0;
}

/**
 * function that initializes an SDL window
 * @param windowName title of the window
 * @return a pointer to the window
 */
SDL_Window *initializeWindow(const std::string& windowName) {
    // create a centered window
    SDL_Window *window = SDL_CreateWindow(
            windowName.c_str(),
            SDL_WINDOWPOS_CENTERED,    // x position
            SDL_WINDOWPOS_CENTERED,    // y position
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_OPENGL       // window's flags, use opengl
            );

    // capture mouse movement
    SDL_SetRelativeMouseMode(SDL_TRUE);

    return window;
}

/**
 * function that initializes the opengl context
 * @param window window on which to initialize the context
 * @return the context of opengl
 */
SDL_GLContext initializeGL(SDL_Window* window) {
    // opengl attributes
    // version 3.3
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
    // core version
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    // forward compatibility
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG );

    // create context
    SDL_GLContext glContext  = nullptr;
    glContext = SDL_GL_CreateContext(window);

    // initialize GLEW
    GLenum  err = glewInit();
    if (GLEW_OK != err) {
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
        exit(1);
    }

    // enable vsync
    SDL_GL_SetSwapInterval(1);

    return glContext;
}

/**
 * function that quits SDL and its subsystems
 */
void quitSDL() {
    SDL_Quit();
}

// Esta funcion esta aca nomas para no llenar de los vertices el main
// TODO Extraer a otro lado esta funcion
std::vector<GLfloat> getCubeColors() {
    return std::vector<GLfloat>  {
            0.583f,  0.771f,  0.014f,
            0.609f,  0.115f,  0.436f,
            0.327f,  0.483f,  0.844f,
            0.822f,  0.569f,  0.201f,
            0.435f,  0.602f,  0.223f,
            0.310f,  0.747f,  0.185f,
            0.597f,  0.770f,  0.761f,
            0.559f,  0.436f,  0.730f,
            0.359f,  0.583f,  0.152f,
            0.483f,  0.596f,  0.789f,
            0.559f,  0.861f,  0.639f,
            0.195f,  0.548f,  0.859f,
            0.014f,  0.184f,  0.576f,
            0.771f,  0.328f,  0.970f,
            0.406f,  0.615f,  0.116f,
            0.676f,  0.977f,  0.133f,
            0.971f,  0.572f,  0.833f,
            0.140f,  0.616f,  0.489f,
            0.997f,  0.513f,  0.064f,
            0.945f,  0.719f,  0.592f,
            0.543f,  0.021f,  0.978f,
            0.279f,  0.317f,  0.505f,
            0.167f,  0.620f,  0.077f,
            0.347f,  0.857f,  0.137f,
            0.055f,  0.953f,  0.042f,
            0.714f,  0.505f,  0.345f,
            0.783f,  0.290f,  0.734f,
            0.722f,  0.645f,  0.174f,
            0.302f,  0.455f,  0.848f,
            0.225f,  0.587f,  0.040f,
            0.517f,  0.713f,  0.338f,
            0.053f,  0.959f,  0.120f,
            0.393f,  0.621f,  0.362f,
            0.673f,  0.211f,  0.457f,
            0.820f,  0.883f,  0.371f,
            0.982f,  0.099f,  0.879f
    };
}

int main(int argc, char *argv[])
{
    ///// Initialization
    if (!initializeSDL()) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }
    SDL_Window *window = nullptr;
    SDL_GLContext context;

    window = initializeWindow("Test");
    context = initializeGL(window);
    /////

    GLuint shader = Shader::LoadShaders("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

    Camera mainCamera = Camera(glm::vec3(0.5f, 1.0f, 5.0f));

    Cube myCube = Cube();
    myCube.setColors( getCubeColors() );

    // initialize VAO for opengl drawing
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // bind cube to vao
    myCube.bind(VAO);

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 projectionMatrix = glm::perspective(
            glm::radians(45.0f),                        // 45 degree fov
            (float) WINDOW_WIDTH / (float)WINDOW_HEIGHT,       // screen aspect ratio
            0.1f,                                               // 0.1 minimum drawing range
            100.0f);                                             // 100 maximum drawing range

    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 modelMatrix = glm::mat4(1.0f);

    glUseProgram(shader);

    // get uniforms for rendering
    GLint projectionID = glGetUniformLocation(shader, "projection");
    GLint viewID = glGetUniformLocation(shader, "view");
    GLint modelID = glGetUniformLocation(shader, "model");

    // set values for each shader uniform
    glUniformMatrix4fv(projectionID, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(mainCamera.getViewMatrix()));
    glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // main loop control variables
    bool isRunning = true;
    SDL_Event event;

    // enable perspective
    glEnable(GL_DEPTH_TEST);
    // order by less value in the w
    glDepthFunc(GL_LESS);

    // program time
    float lastFrameTime = SDL_GetTicks() / 1000.0f;
    float deltaTime = 0;

    while(isRunning) {
        // get time difference between loops
        // used for movement to make it smoother
        float currentFrameTime = SDL_GetTicks() / 1000.0f;
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        // handle keyboard, mouse and window events
        while(SDL_PollEvent(&event)) {
            // window x press
            if (event.type == SDL_QUIT) {
                isRunning= false;
            }
            // on key press
            else if (event.type == SDL_KEYDOWN) {
                switch(event.key.keysym.scancode) {
                    case SDL_SCANCODE_ESCAPE:
                        isRunning = false;
                        break;
                    case SDL_SCANCODE_D:
                        mainCamera.handleEvent( Camera::Camera_Movement::RIGHT, true );
                        break;
                    case SDL_SCANCODE_A:
                        mainCamera.handleEvent( Camera::Camera_Movement::LEFT, true );
                        break;
                    case SDL_SCANCODE_W:
                        mainCamera.handleEvent( Camera::Camera_Movement::FORWARD, true );
                        break;
                    case SDL_SCANCODE_S:
                        mainCamera.handleEvent( Camera::Camera_Movement::BACKWARD, true );
                        break;
                    case SDL_SCANCODE_R:
                        modelMatrix = glm::scale(modelMatrix, glm::vec3(1.05));
                        break;
                    case SDL_SCANCODE_F:
                        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.95));
                        break;
                }
            }
            // on key release
            else if (event.type == SDL_KEYUP) {
                switch(event.key.keysym.scancode) {
                    case SDL_SCANCODE_ESCAPE:
                        isRunning = false;
                        break;
                    case SDL_SCANCODE_D:
                        mainCamera.handleEvent( Camera::Camera_Movement::RIGHT, false );
                        break;
                    case SDL_SCANCODE_A:
                        mainCamera.handleEvent( Camera::Camera_Movement::LEFT, false );
                        break;
                    case SDL_SCANCODE_W:
                        mainCamera.handleEvent( Camera::Camera_Movement::FORWARD, false );
                        break;
                    case SDL_SCANCODE_S:
                        mainCamera.handleEvent( Camera::Camera_Movement::BACKWARD, false );
                        break;
                }
            }
            else if (event.type == SDL_MOUSEMOTION) {
                Sint32 mouseDeltaX = event.motion.xrel;
                Sint32 mouseDeltaY = event.motion.yrel;
                mainCamera.handleEvent( mouseDeltaX, mouseDeltaY );
            }
        }

        // default color of screen
        glClearColor( 0.0f, 0.0f, 0.4f, 1.0f );

        // clear color and depth buffers
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        // set shader to be used
        glUseProgram(shader);

        // move camera
        mainCamera.moveCamera(deltaTime);

        // set view matrix (camera)
        glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(mainCamera.getViewMatrix()));
        // set model matrix (if it changed)
        glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(modelMatrix));

        // draw cube
        myCube.draw(VAO);

        // switch window buffer
        // if double buffering is supported
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    quitSDL();

    return 0;
}