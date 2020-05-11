#include <iostream>
#include <GL/glew.h>
#ifdef __linux__
#include <SDL2/SDL.h>
#endif
#ifdef _MSC_VER
#include <SDL.h>
#endif

#include "Shader.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <Camera.h>
#include <Cube.h>
#include <TreeTrunk.h>

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
    SDL_GLContext glContext;
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

int main(int argc, char *argv[])
{
    ///// Initialization
    if (!initializeSDL()) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }
    SDL_Window *window;
    SDL_GLContext context;

    window = initializeWindow("Test");
    context = initializeGL(window);
    /////

    GLuint shader = Shader::LoadShaders("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

    Camera mainCamera = Camera(glm::vec3(0.5f, 1.0f, 5.0f));

    TreeTrunk trunk = TreeTrunk();

    // initialize VAO for opengl drawing
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // bind trunk to vao
    trunk.bind(VAO);

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
            mainCamera.handleEvent(event);
            trunk.handleEvent(event);
            if (event.type == SDL_QUIT) {
                isRunning= false;
            }
            // on key press
            else if (event.type == SDL_KEYDOWN) {
                switch(event.key.keysym.scancode) {
                    case SDL_SCANCODE_ESCAPE:
                        isRunning = false;
                        break;
                    default:
                        break;
                }
            }
        }

        // default color of screen
        glClearColor( 0.0f, 0.0f, 0.4f, 1.0f );

        // clear color and depth buffers
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        // move camera
        mainCamera.moveCamera(deltaTime);

        // set shader to be used
        glUseProgram(shader);
        // set view matrix (camera)
        glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(mainCamera.getViewMatrix()));
        // set model matrix (if it changed)
        glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(trunk.getModelMatrix()));


        trunk.draw(VAO);

        // switch window buffer
        // if double buffering is supported
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    quitSDL();

    return 0;
}