#include <iostream>
#include <GL/glew.h>
#include <SDL.h>

const int WINDOW_WIDTH = 840;
const int WINDOW_HEIGHT = 480;

bool initializeSDL() {
    // initialize SDL and subsystems (IMG / Audio / etc)
    return SDL_Init(SDL_INIT_EVERYTHING) < 0;
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
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
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
        std::cout << "Failed to initialize SDL. 9" << SDL_GetError() << std::endl;
    }
    SDL_Window *window = nullptr;
    SDL_GLContext context;

    window = initializeWindow("Test");
    context = initializeGL(window);

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
//        glad_glClearColor( 0.125f, 0.125f, 0.25f, 1.0f );
//        glClear( GL_COLOR_BUFFER_BIT );
        // glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
        glColor3f(1.0f, 0.0f, 0.0f); // Red
        glVertex2f(-0.5f, -0.5f);    // x, y
        glVertex2f( 0.5f, -0.5f);
        glVertex2f( 0.5f,  0.5f);
        glVertex2f(-0.5f,  0.5f);
        glEnd();
    }



    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    quitSDL();



    return 0;
}