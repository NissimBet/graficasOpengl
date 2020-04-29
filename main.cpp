#include <iostream>
#include <GL/glew.h>
#ifdef __linux__
#include <SDL2/SDL.h>
#endif
#ifdef _WIN32
#include <SDL.h>
#endif

#include "Shader.h"

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

    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    static const GLfloat g_vertex_buffer_data[] = {
            -1.0f, -1.0f, 0.0f,
             1.0f, -1.0f, 0.0f,
             0.0f,  1.0f, 0.0f,
    };

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    bool isRunning = true;
    SDL_Event event;

    while(isRunning) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning= false;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    isRunning = false;
                }
            }
        }
        glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
//        glClear( GL_COLOR_BUFFER_BIT );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glUseProgram(shader);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);
        glVertexAttribPointer(
                0, 3, GL_FLOAT, GL_FALSE, 0, nullptr
        );

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        SDL_GL_SwapWindow(window);
    }



    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    quitSDL();



    return 0;
}