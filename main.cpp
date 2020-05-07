#include <iostream>

#include <Gl/glew.h>
#include <GL/glut.h>

#include "Shader.h"
//#include <vector>
//#include <glm/glm.hpp>
//#include <glm/ext.hpp>
//#include <Camera.h>
//#include <Cube.h>
//#include <TreeTrunk.h>

// Screen size
const int WINDOW_WIDTH = 840;
const int WINDOW_HEIGHT = 480;
const int SCREEN_FPS = 60;

bool initGL() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    GLenum error = glGetError();
    if(error != GL_NO_ERROR) {
        std::cout << "Error Initializing Opengl. " << gluErrorString(error) << std::endl;
        return false;
    }
    return true;
}

void render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

    glutSolidCube(1);

    glFlush();  // Rende

    glutSwapBuffers();
}

void update() {

}

void runMainLoop(int val) {
    update();
    render();

    glutTimerFunc(1000 / SCREEN_FPS, runMainLoop, val);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);                 // Initialize GLUT
    glewInit();
    glutInitDisplayMode(GLUT_DOUBLE);
    glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);   // Set the window's initial width & height
    if(!initGL()) {
        std::cout << "Unable to initialize graphics library" << std::endl;
    }
    glutDisplayFunc(render); // Register display callback handler for window re-paint
    glutTimerFunc(1000 / SCREEN_FPS, runMainLoop, 0);

    GLuint shader = Shader::LoadShaders("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

    glutMainLoop();           // Enter the infinitely event-processing loop
    return 0;

//
//
//    GLuint shader = Shader::LoadShaders("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
//
////    Camera mainCamera = Camera(glm::vec3(0.5f, 1.0f, 5.0f));
//
//    // initialize VAO for opengl drawing
//    GLuint VAO;
//    glGenVertexArrays(1, &VAO);
//    glBindVertexArray(VAO);
//
//    // bind trunk to vao
////    trunk.bind(VAO);
//
//    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
//    glm::mat4 projectionMatrix = glm::perspective(
//            glm::radians(45.0f),                        // 45 degree fov
//            (float) WINDOW_WIDTH / (float)WINDOW_HEIGHT,       // screen aspect ratio
//            0.1f,                                               // 0.1 minimum drawing range
//            100.0f);                                             // 100 maximum drawing range
//
//    // Model matrix : an identity matrix (model will be at the origin)
//    glm::mat4 modelMatrix = glm::mat4(1.0f);

//    glUseProgram(shader);

    // get uniforms for rendering
//    GLint projectionID = glGetUniformLocation(shader, "projection");
//    GLint viewID = glGetUniformLocation(shader, "view");
//    GLint modelID = glGetUniformLocation(shader, "model");
//
//    // set values for each shader uniform
//    glUniformMatrix4fv(projectionID, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
//    glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(mainCamera.getViewMatrix()));
//    glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // main loop control variables
//    bool isRunning = true;


//    // enable perspective
//    glEnable(GL_DEPTH_TEST);
//    // order by less value in the w
//    glDepthFunc(GL_LESS);

    // program time
//    float lastFrameTime = SDL_GetTicks() / 1000.0f;
//    float deltaTime = 0;

//    while(isRunning) {
        // get time difference between loops
        // used for movement to make it smoother
//        float currentFrameTime = SDL_GetTicks() / 1000.0f;
//        deltaTime = currentFrameTime - lastFrameTime;
//        lastFrameTime = currentFrameTime;

        // handle keyboard, mouse and window events
//        while(SDL_PollEvent(&event)) {
//            // window x press
//            mainCamera.handleEvent(event);
//            trunk.handleEvent(event);
//            if (event.type == SDL_QUIT) {
//                isRunning= false;
//            }
//            // on key press
//            else if (event.type == SDL_KEYDOWN) {
//                switch(event.key.keysym.scancode) {
//                    case SDL_SCANCODE_ESCAPE:
//                        isRunning = false;
//                        break;
//                    default:
//                        break;
//                }
//            }
//        }

//        // default color of screen
//        glClearColor( 0.0f, 0.0f, 0.4f, 1.0f );
//
//        // clear color and depth buffers
//        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//
//        // move camera
////        mainCamera.moveCamera(deltaTime);
//
//        // set shader to be used
//        glUseProgram(shader);
//        // set view matrix (camera)
//        glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(mainCamera.getViewMatrix()));
//        // set model matrix (if it changed)
//        glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(trunk.getModelMatrix()));


//        trunk.draw(VAO);

//    }



    return 0;
}