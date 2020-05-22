/**
 * This program uses Opengl and GLEW for rendering a scene.
 * It uses SDL2 for the creation of the window and handling of events.
 * For the loading of the blender objects and models Assimp is used.
 * For matrix-related calculations, glm is used
 *
 * This program tries to recreate a scene from an image, previously rendered by blender.
 * This program was created by:
 *      Edgar López Villarreal
 *      Francisco Javier Castro Zúñiga
 *      José Cruz Flores Flores
 *      Nissim Ariel Betesh Hassine
 */

#include <iostream>
#include <array>
#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Shader.h"
#include <Camera.h>
#include <Cube.h>
#include "Model.h"
#include "ModelColors.h"
#include "ModelTextures.h"

// Screen size
#ifdef NDEBUG
constexpr int WINDOW_WIDTH = 1920;
constexpr int WINDOW_HEIGHT = 1080;
#else
constexpr int WINDOW_WIDTH = 720;
constexpr int WINDOW_HEIGHT = 480;
#endif

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
SDL_Window *initializeWindow(const std::string &windowName) {
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
SDL_GLContext initializeGL(SDL_Window *window) {
    // opengl attributes
    // version 3.3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    // core version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    // forward compatibility
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

    // create context
    SDL_GLContext glContext;
    glContext = SDL_GL_CreateContext(window);

    // initialize GLEW
    GLenum err = glewInit();
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

int main(int argc, char *argv[]) {
    // Initialization
    if (!initializeSDL()) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }
    SDL_Window *window;
    SDL_GLContext context;

    window = initializeWindow("Test");
    context = initializeGL(window);
    //

    // obj files
    const std::string objCabin = "cabin.obj";
    const std::string objCableway = "cableway.obj";
    const std::string objSled = "sled.obj";
    const std::string objTree = "tree.obj";

    // create shader
    Shader shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

    // initialize camera
    Camera mainCamera = Camera(glm::vec3(0.5f, 1.0f, 5.0f));

    // create a cube to represent the floor
    Cube floor = Cube(1.0f, 1.0f, 1.0f);

    // set the values for the floor
    glm::vec3 floorScale = glm::vec3(10.0f, 0.2f, 10.0f);
    glm::vec3 floorPosition = glm::vec3(-5.0f, -0.25f, -5.0f);
    glm::mat4 floorModel = glm::translate(glm::mat4(1), floorPosition);
    floorModel = glm::scale(floorModel, floorScale);

    // create a VAO to draw the floor and bind to it
    GLuint floorVAO;
    glCreateVertexArrays(1, &floorVAO);
    floor.bind(floorVAO);

    loadTextures();
#ifndef NDEBUG
    std::cout << "Textures Loaded" << std::endl;
#endif
    glm::vec3 leafGreen = glm::vec3(0.322, 0.42, 0.176);

    // Import models
    std::array<Model, 7> objects = {
            Model(objCabin, glm::vec3(0.8f), glm::vec3(0.76f, 0.6f, 0.42f), wallTexture, cabinTextures),
            Model(objCableway, glm::vec3(0.25f), glm::vec3(0.75f, 0.75f, 0.75f), metalTexture, cablewayTextures),
            Model(objSled, glm::vec3(0.45f), glm::vec3(0.76f, 0.6f, 0.42f), metalTexture, sledTextures),
            Model(objTree, glm::vec3(0.5f, 0.75f, 0.5f), leafGreen, leafTexture),
            Model(objTree, glm::vec3(0.75f, 1.0f, 0.75f), leafGreen, leafTexture),
            Model(objTree, glm::vec3(0.5f, 0.75f, 0.5f), leafGreen, leafTexture),
            Model(objTree, glm::vec3(0.5f, 0.75f, 0.5f), leafGreen, leafTexture),
    };

    objects[0].translate(glm::vec3(0.0f, -0.05f, -8.0f));
    objects[0].rotate(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    objects[1].translate(glm::vec3(0.0f, 25.0f, 0.0f));
    objects[3].translate(glm::vec3(-7.0f, 0.0f, -14.0f));
    objects[4].translate(glm::vec3(-6.0f, 0.0f, -5.0f));
    objects[5].translate(glm::vec3(7.0f, 0.0f, -14.0f));
    objects[6].translate(glm::vec3(7.0f, 0.0f, -6.0f));

    int currentSelected = 0;

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 projectionMatrix = glm::perspective(
            glm::radians(45.0f),                        // 45 degree fov
            (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT,       // screen aspect ratio
            0.1f,                                               // 0.1 minimum drawing range
            100.0f);                                             // 100 maximum drawing range
    // set the initial projection and view matrics of the scene
    shader.use();
    shader.setMat4("projection", projectionMatrix);
    shader.setMat4("view", mainCamera.getViewMatrix());

    // main loop control variables
    bool isRunning = true;
    SDL_Event event;

    // enable perspective
    glEnable(GL_DEPTH_TEST);
    // order of drawing by the lower value in w
    glDepthFunc(GL_LESS);

    // program time
    float lastFrameTime = SDL_GetTicks() / 1000.0f;

    while (isRunning) {
        // get time difference between loops
        // used for movement to make it smoother
        float currentFrameTime = SDL_GetTicks() / 1000.0f;
        float deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        // handle keyboard, mouse and window events
        while (SDL_PollEvent(&event)) {
            // window x press
            mainCamera.handleEvent(event);
            objects[currentSelected].handleEvent(event);
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
                // on key press
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_ESCAPE:
                        isRunning = false;
                        break;
                    default:
                        break;
                }
                const Uint8 *state = SDL_GetKeyboardState(nullptr);
                if (state[SDL_SCANCODE_LSHIFT] && state[SDL_SCANCODE_TAB]) {
                    currentSelected--;
                    if (currentSelected < 0) {
                        currentSelected = objects.size() - 1;
                    }
                } else if (state[SDL_SCANCODE_TAB]) {
                    currentSelected++;
                    currentSelected = currentSelected % objects.size();
                }
            }
        }

        // default color of screen
        glClearColor(0.909f, 0.917f, 0.925f, 1.0f);

        // clear color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // move camera
        mainCamera.moveCamera(deltaTime);

        // set shader to be used
        shader.use();
        // set view matrix (camera)
        shader.setMat4("view", mainCamera.getViewMatrix());

        for (int i = 0; i < objects.size(); i++) {
            objects[i].draw(shader, i == currentSelected);
        }

//        glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(mainCamera.getViewMatrix()));
        // set model matrix (if it changed)

        shader.setFloat("selected", 1.0f);
        shader.setMat4("model", floorModel);


        glActiveTexture(GL_TEXTURE0);
        shader.setInt("meshTexture", 0);
        glBindTexture(GL_TEXTURE_2D, snowTexture);
        floor.draw(floorVAO);



        // switch window buffer
        // if double buffering is supported
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    quitSDL();

    return 0;
}