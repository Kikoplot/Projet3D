#include <glimac/SDLWindowManager.hpp>

#include <GL/glew.h>
#include <iostream>

#include <include/assimp/Importer.hpp>
#include <include/assimp/scene.h>

#include "include/shader.hpp"
#include "include/model.hpp"
#include "include/camera.hpp"

using namespace glimac;

int main(int argc, char** argv) {
    GLuint screenWidth = 800, screenHeight = 600;
    // Initialize SDL and open a window
    SDLWindowManager windowManager(screenWidth, screenHeight, "ProjectCharlie");

    // Initialize glew for OpenGL3+ support
    glewExperimental = GL_TRUE;
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    //Define the viewport dimensions
    glViewport(0, 0, screenWidth, screenHeight);

    // Setup some OpenGL options
    glEnable(GL_DEPTH_TEST);

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;


    // Setup and compile our shaders
    Shader MyShader("template/shaders/model_loading.vs.glsl", "template/shaders/model_loading.fs.glsl");

    // Load models
    Model crysis("assets/models/nanosuit/nanosuit.obj");
    Model house("assets/models/house/fw43_lowpoly_n1.3ds");
    Model landscape("assets/models/castle/eastern ancient casttle/eastern ancient casttle.obj");

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

     Camera camera; //Initialisation camera

    // Application loop:
    bool done = false;
    while(!done) {

        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
            if(windowManager.isKeyPressed(SDLK_z)) camera.moveFront(0.05);
            if(windowManager.isKeyPressed(SDLK_s)) camera.moveFront(-0.05);
            if(windowManager.isKeyPressed(SDLK_q)) camera.moveLatteral(0.05);
            if(windowManager.isKeyPressed(SDLK_d)) camera.moveLatteral(-0.05);

            glm::ivec2 MousePosition = glm::ivec2(0.0, 0.0);
            MousePosition = windowManager.getMousePosition();
            float MousePositionX = MousePosition.x/600.0f-0.5;
            float MousePositionY = MousePosition.y/600.0f-0.5;
            camera.rotateLeft(-2*MousePositionX);
            camera.rotateUp(-2*MousePositionY);

        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        MyShader.Use();

        // Transformation matrices
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);

        glm::mat4 view = camera.getViewMatrix();

        glUniformMatrix4fv(glGetUniformLocation(MyShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(MyShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Draw the loaded model
        glm::mat4 matModel;

        // Translate model to the center of the scene
        matModel = glm::translate(matModel, glm::vec3(0.0f, -1.75f, -5.0f));
        matModel = glm::scale(matModel, glm::vec3(0.2f, 0.2f, 0.2f));
        glUniformMatrix4fv(glGetUniformLocation(MyShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(matModel));

        crysis.Draw(MyShader);

        // Translate model to the center of the scene
        matModel = glm::rotate(matModel, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        matModel = glm::translate(matModel, glm::vec3(0.0f, 2.0f, 0.0f));
        matModel = glm::scale(matModel, glm::vec3(5.0f, 5.0f, 5.0f));
        glUniformMatrix4fv(glGetUniformLocation(MyShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(matModel));

        house.Draw(MyShader);

        // Translate model to the center of the scene
        matModel = glm::rotate(matModel, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        matModel = glm::translate(matModel, glm::vec3(5.0f, -19.0f, 55.0f));
        matModel = glm::scale(matModel, glm::vec3(0.2f, 0.2f, 0.2f));
        glUniformMatrix4fv(glGetUniformLocation(MyShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(matModel));

        landscape.Draw(MyShader);

        // Update the display
        windowManager.swapBuffers();
    }

    //glDeleteBuffers(1, &vbo);
    //glDeleteVertexArrays(1, &vao);


    return EXIT_SUCCESS;
}
