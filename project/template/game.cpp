#include <glimac/SDLWindowManager.hpp>

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <include/assimp/Importer.hpp>
#include <include/assimp/scene.h>
#include <glimac/FilePath.hpp>
#include "include/shader.hpp"
#include "include/model.hpp"
#include "include/camera.hpp"
#include "include/skybox.hpp"
#include "include/scene.hpp"

using namespace glimac;
using namespace std;

int main(int argc, char** argv) {
    GLuint screenWidth = 800, screenHeight = 600;
    // Initialize SDL and open a window
    SDLWindowManager windowManager(screenWidth, screenHeight, "ProjectCharlie");

    // Initialize glew for OpenGL3+ support
    glewExperimental = GL_TRUE;
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        cerr << glewGetErrorString(glewInitError) << endl;
        return EXIT_FAILURE;
    }

    //Define the viewport dimensions
    glViewport(0, 0, screenWidth, screenHeight);

    // Setup some OpenGL options
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_FOG);

    cout << "OpenGL Version : " << glGetString(GL_VERSION) << endl;
    cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << endl;

     Scene scene("assets/data/settings.txt");
     //scene.loadScene("template/data/settings.txt");

    // Application loop:
    bool done = false;
    while(!done) {

        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT || (windowManager.isKeyPressed(SDLK_ESCAPE))) {
                done = true; // Leave the loop after this iteration
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float rotation = rotation + 0.1f;

        scene.update(&windowManager, screenWidth, screenHeight, rotation);

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
