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

const int WINDOW_WIDTH = 840;
const int WINDOW_HEIGHT = 480;

bool initializeSDL() {
    // initialize SDL and subsystems (IMG / Audio / etc)
    return SDL_Init(SDL_INIT_EVERYTHING) == 0;
}

SDL_Window *initializeWindow(const std::string& windowName) {
    SDL_Window *window = SDL_CreateWindow(
            windowName.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_OPENGL
            );

    SDL_SetRelativeMouseMode(SDL_TRUE);

    return window;
}

SDL_GLContext initializeGL(SDL_Window* window) {
    // opengl attributes
    // version 3.3
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG );

    SDL_GLContext glContext  = nullptr;

    glContext = SDL_GL_CreateContext(window);

    GLenum  err = glewInit();
    if (GLEW_OK != err) {
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
        exit(1);
    }

    SDL_GL_SetSwapInterval(1);

    return glContext;
}

void quitSDL() {
    SDL_Quit();
}



int main(int argc, char *argv[])
{
    if (!initializeSDL()) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }
    SDL_Window *window = nullptr;
    SDL_GLContext context;

    window = initializeWindow("Test");
    context = initializeGL(window);

    GLuint shader = Shader::LoadShaders("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

    Camera mainCamera = Camera(glm::vec3(0.5f, 1.0f, 5.0f));

    static const GLfloat g_vertex_buffer_data[] = {
            -1.0f,-1.0f,-1.0f, // triangle 1 : begin
            -1.0f,-1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, // triangle 1 : end
            1.0f, 1.0f,-1.0f, // triangle 2 : begin
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f, // triangle 2 : end
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f
    };

    static const GLfloat g_color_buffer_data[] = {
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

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), (float) WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);

    // Camera matrix
    glm::mat4 viewMatrix = glm::lookAt(
            glm::vec3(3,3,-5), // Camera is at (4,3,3), in World Space
            glm::vec3(0,0,0), // and looks at the origin
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 modelMatrix = glm::mat4(1.0f);

    glUseProgram(shader);

    GLint projectionID = glGetUniformLocation(shader, "projection");
    GLint viewID = glGetUniformLocation(shader, "view");
    GLint modelID = glGetUniformLocation(shader, "model");

    glUniformMatrix4fv(projectionID, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(mainCamera.getViewMatrix()));
    glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    bool isRunning = true;
    SDL_Event event;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    float lastFrameTime = SDL_GetTicks() / 1000.0f;
    float deltaTime = 0;

    while(isRunning) {
        float currentFrameTime = SDL_GetTicks() / 1000.0f;
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning= false;
            }
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
                }

            }
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
        glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
//        glClear( GL_COLOR_BUFFER_BIT );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glUseProgram(shader);

        mainCamera.moveCamera(deltaTime);
        glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(mainCamera.getViewMatrix()));

        // 1st attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(
                0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                nullptr             // array buffer offset
        );

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glVertexAttribPointer(
                1,                  // attribute 1. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                nullptr             // array buffer offset
        );
// Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 12*3); // Starting from vertex 0; 3 vertices total -> 1 triangle

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        SDL_GL_SwapWindow(window);
    }



    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    quitSDL();



    return 0;
}