#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Shader.h"
#include <Camera.h>
#include <Cube.h>
#include "Model.h"

// Screen size
const int WINDOW_WIDTH = 840;
const int WINDOW_HEIGHT = 480;

// Full Scene file
//const std::string objFile = "Snow_Cabin.obj";
const std::string objCabin = "cabin.obj";
const std::string objCableway = "cableway.obj";
const std::string objSled = "sled.obj";
const std::string objTree = "tree.obj";

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



    Shader shader = Shader();
    shader.LoadShaders("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

    Camera mainCamera = Camera(glm::vec3(0.5f, 1.0f, 5.0f));

    // import model from blender
//    Model model(objFile);
    Cube floor = Cube();


    Model objects[] = {
            Model(objCabin, glm::vec3(-5.0f, 0.0f, 5.0f), glm::vec3(0.8f)),
            Model(objCableway, glm::vec3(3.0f, 15.0f, 3.0f), glm::vec3(0.25f)),
            Model(objSled, glm::vec3(2.0f, -0.0f, -3.5f), glm::vec3(0.45f)),
            Model(objTree, glm::vec3(-5.0f, 0.0f, 4.5f), glm::vec3(0.5f, 0.75f, 0.5f)),
            Model(objTree, glm::vec3(-5.0f, 0.0f, 10.0f), glm::vec3(0.75f, 1.0f, 0.75f)),
            Model(objTree, glm::vec3(5.0f, 0.0f, 3.0f), glm::vec3(0.5f, 0.75f, 0.5f)),
            Model(objTree, glm::vec3(-2.5f, 0.0f, 7.5f), glm::vec3(0.5f, 0.75f, 0.5f)),
    };

    int currentSelected = 0;

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 projectionMatrix = glm::perspective(
            glm::radians(45.0f),                        // 45 degree fov
            (float) WINDOW_WIDTH / (float)WINDOW_HEIGHT,       // screen aspect ratio
            0.1f,                                               // 0.1 minimum drawing range
            100.0f);                                             // 100 maximum drawing range

    shader.use();
    shader.setMat4("projection", projectionMatrix);
    shader.setMat4("view", mainCamera.getViewMatrix());

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
//            model.handleEvent(event);
            objects[currentSelected].handleEvent(event);
            if (event.type == SDL_QUIT) {
                isRunning= false;
            }
            // on key press
            else if (event.type == SDL_KEYDOWN) {
                switch(event.key.keysym.scancode) {
                    case SDL_SCANCODE_ESCAPE:
                        isRunning = false;
                        break;
//                    case SDL_SCANCODE_TAB:
//                        currentSelected = (currentSelected + 1) % (sizeof(objects) / sizeof(Model)) ;
//                        std::cout << currentSelected << std::endl;
//                        break;
                    default:
                        break;
                }
                const Uint8 * state = SDL_GetKeyboardState(nullptr);
                if (state[SDL_SCANCODE_LSHIFT] && state[SDL_SCANCODE_TAB]) {
                    currentSelected--;
                    if(currentSelected < 0) {
                        currentSelected = sizeof(objects) / sizeof(Model) - 1;
                    }
                }
                else if (state[SDL_SCANCODE_TAB]) {
                    currentSelected = (currentSelected + 1) % (sizeof(objects) / sizeof(Model)) ;
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
        shader.use();
        // set view matrix (camera)
        shader.setMat4("view", mainCamera.getViewMatrix());

        for(int i = 0; i < sizeof(objects) / sizeof(Model); i++) {
            objects[i].draw(shader, i == currentSelected);
        }
//        glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(mainCamera.getViewMatrix()));
        // set model matrix (if it changed)


//        model.translate(glm::vec3(5.0f * ( float ) glm::sin( SDL_GetTicks() / 1000.0f ), model.worldPosition.y,  -5.5f + 5.0f  * ( float ) glm::cos( SDL_GetTicks() / 1000.0f )));
//        model.draw(shader);



        // switch window buffer
        // if double buffering is supported
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    quitSDL();

    return 0;
}