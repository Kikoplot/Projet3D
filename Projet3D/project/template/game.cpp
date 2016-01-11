#include <glimac/SDLWindowManager.hpp>

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <include/assimp/Importer.hpp>
#include <include/assimp/scene.h>
#include <glimac/FilePath.hpp>
#include "include/shader.hpp"
#include "include/model.hpp"
#include "include/camera.hpp"
#include "include/skybox.hpp"
#include "include/scene.hpp"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

using namespace glimac;
using namespace std;

int main(int argc, char** argv) {
    GLuint screenWidth = 1440, screenHeight = 900;
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

    Shader shadermenu("template/shaders/phong.vs.glsl", "template/shaders/phong.fs.glsl");

    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] = {
         // Positions          // Colors           // Texture Coords
          1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
          1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
         -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
         -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
     };
     GLuint indices[] = {  // Note that we start from 0!
         0, 1, 3, // First Triangle
         1, 2, 3  // Second Triangle
     };
     GLuint VBO, VAO, EBO;
     glGenVertexArrays(1, &VAO);
     glGenBuffers(1, &VBO);
     glGenBuffers(1, &EBO);

     glBindVertexArray(VAO);

     glBindBuffer(GL_ARRAY_BUFFER, VBO);
     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

     // Position attribute
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
     glEnableVertexAttribArray(0);
     // Color attribute
     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
     glEnableVertexAttribArray(1);
     // TexCoord attribute
     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
     glEnableVertexAttribArray(2);

     glBindVertexArray(0); // Unbind VAO

     std::unique_ptr<Image> image;
     std::unique_ptr<Image> image2;
     std::unique_ptr<Image> image3;

     //Texture 1 Load
     GLuint texture;
     GLuint texture2;
     GLuint texture3;
     glGenTextures(1, &texture);
     glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
     // Set the texture wrapping parameters
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
     // Set texture filtering parameters
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     // Load image, create texture and generate mipmaps
     image = loadImage("assets/textures/title/title1.png");
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_FLOAT, image->getPixels());
     glGenerateMipmap(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

     //Texture 2 Load
     glGenTextures(1, &texture2);
     glBindTexture(GL_TEXTURE_2D, texture2);
     // Set our texture parameters
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
     // Set texture filtering
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     // Load, create texture and generate mipmaps
     image2 = loadImage("assets/textures/title/title2.png");
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image2->getWidth(), image2->getHeight(), 0, GL_RGBA, GL_FLOAT, image2->getPixels());
     glGenerateMipmap(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

     //Texture 3 Load
     glGenTextures(1, &texture3);
     glBindTexture(GL_TEXTURE_2D, texture3);
     // Set our texture parameters
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
     // Set texture filtering
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     // Load, create texture and generate mipmaps
     image3 = loadImage("assets/textures/title/title3.png");
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image3->getWidth(), image3->getHeight(), 0, GL_RGBA, GL_FLOAT, image3->getPixels());
     glGenerateMipmap(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.



    cout << "OpenGL Version : " << glGetString(GL_VERSION) << endl;
    cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << endl;

    int level = 1;
    int pause = 1;

    float ambient, diffuse, specular, shininess;

    vector<Scene> scenes;
    Scene scene1("assets/data/settings1.txt", level, pause);
    scenes.push_back(scene1);
    // if( SDL_Init(SDL_INIT_AUDIO) < 0 ) exit(1);
    //  //Test audio
    //  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    //             printf("SDL_Mixer Error: %s\n", Mix_GetError());
    //         }
    //  Mix_Volume(-1,MIX_MAX_VOLUME);

    //  Mix_Music*music;
    //  music = Mix_LoadMUS("assets/sounds/desert1.wav");
    //  if (music == NULL) {
    //             printf("Couldn't load beat.wav: %s\n", Mix_GetError());
    //         }
    //  Mix_PlayMusic(music, -1);
     //Fin test

    // Application loop:
    bool done = false;
    while(!done) {

        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
          if(e.type == SDL_QUIT || (windowManager.isKeyPressed(SDLK_ESCAPE))) {
              done = true; // Leave the loop after this iteration
          }
          if(windowManager.isKeyPressed(SDLK_p)){
            pause = 1;
            Scene menu("assets/data/menu.txt", 1, pause);
          }
          if(pause == 1){
            if(windowManager.isKeyPressed(SDLK_DOWN)){
              level++;
              if(level>3){
                level = 1;
              }
            }
            if(windowManager.isKeyPressed(SDLK_UP)){
              level--;
              if(level<1){
                level = 3;
              }
            }
            if(windowManager.isKeyPressed(SDLK_RETURN)){
              if(level == 1){
                scenes.pop_back();
                Scene scene1("assets/data/settings1.txt", 1, pause);
                scenes.push_back(scene1);
              }
              if(level == 2){
                scenes.pop_back();
                Scene scene2("assets/data/settings2.txt", 2, pause);
                scenes.push_back(scene2);
              }
              if(level == 3){
                scenes.pop_back();
                Scene scene3("assets/data/settings3.txt", 3, pause);
                scenes.push_back(scene3);
              }
              pause = 0;
            }
          }
      }

      if(level==1){
        ambient = 0.3f;
        diffuse = 0.7f;
        specular = 2.0f;
        shininess = 32.0f;
      }

      if(level==2){
        ambient = 0.01f;
        diffuse = 0.1f;
        specular = 0.1f;
        shininess = 0.5f;
      }

      if(level==3){
        ambient = 0.2f;
        diffuse = 0.3f;
        specular = 0.3f;
        shininess = 0.3f;
      }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(pause == 1){
            shadermenu.Use();
            // Bind Textures using texture units
            glActiveTexture(GL_TEXTURE0);
            if(level == 1){
              glBindTexture(GL_TEXTURE_2D, texture);
            }
            if(level == 2){
              glBindTexture(GL_TEXTURE_2D, texture2);
            }
            if(level == 3){
              glBindTexture(GL_TEXTURE_2D, texture3);
            }
            glUniform1i(glGetUniformLocation(shadermenu.Program, "ourTexture1"), 0);
            glActiveTexture(GL_TEXTURE1);

            // Draw container
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

        else{
          float rotation = rotation + 0.1f;
          scenes[0].update(&windowManager, screenWidth, screenHeight, rotation, ambient, diffuse, specular, shininess, level);
        }
        // Update the display
        windowManager.swapBuffers();
    }


    // Mix_FreeMusic(music); //Fermeture de l'API
    SDL_Quit();

    return EXIT_SUCCESS;
}
