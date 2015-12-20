#include <glimac/SDLWindowManager.hpp>

#include <GL/glew.h>
#include <iostream>

#include <include/assimp/Importer.hpp>
#include <include/assimp/scene.h>

#include "include/shader.hpp"
#include "include/model.hpp"
#include "include/camera.hpp"

using namespace glimac;
using namespace std;

// Light attributes
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

GLuint loadCubemap(vector<const GLchar*> faces)
{
  GLuint textureID;
  glGenTextures(1, &textureID);
  glActiveTexture(GL_TEXTURE0);

  int width,height;
  std::unique_ptr<Image> image;

  glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
  for(GLuint i = 0; i < faces.size(); i++)
  {
      //image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
      image = loadImage(faces[i]);
      //width = image->getWidth();
      //height = image->getHeight();
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,0,GL_RGBA,image->getWidth(),image->getHeight(),0,GL_RGBA,GL_FLOAT,image->getPixels());
      //glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  }
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

  return textureID;
}

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

    cout << "OpenGL Version : " << glGetString(GL_VERSION) << endl;
    cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << endl;


    // Setup and compile our shaders
    Shader MyShader("template/shaders/model_loading.vs.glsl", "template/shaders/model_loading.fs.glsl");
    Shader AmbientLighting("template/shaders/ambiant_lighting.vs.glsl", "template/shaders/ambiant_lighting.fs.glsl");
    Shader PointLighting("template/shaders/point_lighting.vs.glsl", "template/shaders/point_lighting.fs.glsl");
    Shader skyboxShader("template/shaders/skybox.vs.glsl", "template/shaders/skybox.fs.glsl");

    // Load models
    Model crysis("assets/models/nanosuit/nanosuit.obj");
    Model house("assets/models/house/fw43_lowpoly_n1.3ds");
    Model landscape("assets/models/castle/eastern ancient casttle/eastern ancient casttle.obj");

    GLfloat skyboxVertices[] = {
            // Positions
            -50.0f,  50.0f, -50.0f,
            -50.0f, -50.0f, -50.0f,
             50.0f, -50.0f, -50.0f,
             50.0f, -50.0f, -50.0f,
             50.0f,  50.0f, -50.0f,
            -50.0f,  50.0f, -50.0f,

            -50.0f, -50.0f,  50.0f,
            -50.0f, -50.0f, -50.0f,
            -50.0f,  50.0f, -50.0f,
            -50.0f,  50.0f, -50.0f,
            -50.0f,  50.0f,  50.0f,
            -50.0f, -50.0f,  50.0f,

             50.0f, -50.0f, -50.0f,
             50.0f, -50.0f,  50.0f,
             50.0f,  50.0f,  50.0f,
             50.0f,  50.0f,  50.0f,
             50.0f,  50.0f, -50.0f,
             50.0f, -50.0f, -50.0f,

            -50.0f, -50.0f,  50.0f,
            -50.0f,  50.0f,  50.0f,
             50.0f,  50.0f,  50.0f,
             50.0f,  50.0f,  50.0f,
             50.0f, -50.0f,  50.0f,
            -50.0f, -50.0f,  50.0f,

            -50.0f,  50.0f, -50.0f,
             50.0f,  50.0f, -50.0f,
             50.0f,  50.0f,  50.0f,
             50.0f,  50.0f,  50.0f,
            -50.0f,  50.0f,  50.0f,
            -50.0f,  50.0f, -50.0f,

            -50.0f, -50.0f, -50.0f,
            -50.0f, -50.0f,  50.0f,
             50.0f, -50.0f, -50.0f,
             50.0f, -50.0f, -50.0f,
            -50.0f, -50.0f,  50.0f,
             50.0f, -50.0f,  50.0f
        };

        // Setup skybox VAO
        GLuint skyboxVAO, skyboxVBO;
        glGenVertexArrays(1, &skyboxVAO);
        glGenBuffers(1, &skyboxVBO);
        glBindVertexArray(skyboxVAO);
        glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glBindVertexArray(0);

        // Cubemap (Skybox)
        vector<const GLchar*> faces;
        faces.push_back("assets/textures/right.jpg");
        faces.push_back("assets/textures/left.jpg");
        faces.push_back("assets/textures/top.jpg");
        faces.push_back("assets/textures/bottom.jpg");
        faces.push_back("assets/textures/back.jpg");
        faces.push_back("assets/textures/front.jpg");
        GLuint cubemapTexture = loadCubemap(faces);



    //Point light position
    glm::vec3 pointLightPositions[] {
      glm::vec3(2.3f, -1.6f, -3.0f),
      glm::vec3(-1.7f, 0.9f, 1.0f)
    };

    glm::vec3 ambiantLightPos(0.0f, 0.0f, 0.0f);

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    // Set texture units
    AmbientLighting.Use();
    glUniform1i(glGetUniformLocation(AmbientLighting.Program, "material.diffuse"),  0);
    glUniform1i(glGetUniformLocation(AmbientLighting.Program, "material.specular"), 1);

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
            if(windowManager.isKeyPressed(SDLK_ESCAPE)) done = true;
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

        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);

        // Draw skybox first
        glDepthMask(GL_FALSE);// Remember to turn depth writing off
        skyboxShader.Use();

        glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(glGetUniformLocation(skyboxShader.Program, "skybox"), 0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthMask(GL_TRUE);

        /* POINTLIGHT */
        /*
        PointLighting.Use();
        // Point light 1
        glUniform3f(glGetUniformLocation(PointLighting.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
        glUniform3f(glGetUniformLocation(PointLighting.Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(PointLighting.Program, "pointLights[0].diffuse"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(PointLighting.Program, "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(PointLighting.Program, "pointLights[0].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(PointLighting.Program, "pointLights[0].linear"), 0.009);
        glUniform1f(glGetUniformLocation(PointLighting.Program, "pointLights[0].quadratic"), 0.0032);
        // Point light 2
        glUniform3f(glGetUniformLocation(PointLighting.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
        glUniform3f(glGetUniformLocation(PointLighting.Program, "pointLights[1].ambient"), 0.55f, 0.55f, 0.55f);
        glUniform3f(glGetUniformLocation(PointLighting.Program, "pointLights[1].diffuse"), 0.10f, 0.10f, 0.10f);
        glUniform3f(glGetUniformLocation(PointLighting.Program, "pointLights[1].specular"), 0.50f, 0.50f, 0.50f);
        glUniform1f(glGetUniformLocation(PointLighting.Program, "pointLights[1].constant"), 0.40f);
        glUniform1f(glGetUniformLocation(PointLighting.Program, "pointLights[1].linear"), 0.09);
        glUniform1f(glGetUniformLocation(PointLighting.Program, "pointLights[1].quadratic"), 0.032);
        */

        // Use cooresponding shader when setting uniforms/drawing objects
        AmbientLighting.Use();
        GLint lightPosLoc = glGetUniformLocation(AmbientLighting.Program, "light.position");
        GLint viewPosLoc = glGetUniformLocation(AmbientLighting.Program, "viewPos");
        glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
        glUniform3f(viewPosLoc, lightPos.x, lightPos.y, lightPos.z);
        // Set lights properties
        glUniform3f(glGetUniformLocation(AmbientLighting.Program, "light.ambient"),  0.2f, 0.2f, 0.2f);
        glUniform3f(glGetUniformLocation(AmbientLighting.Program, "light.diffuse"),  0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(AmbientLighting.Program, "light.specular"), 1.0f, 1.0f, 1.0f);
        // Set material properties
        glUniform1f(glGetUniformLocation(AmbientLighting.Program, "material.shininess"), 32.0f);

/*
        // Transformation matrices
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);
        glm::mat4 view = camera.getViewMatrix();
*/

        /* MYSHADER
        MyShader.Use();
        glUniformMatrix4fv(glGetUniformLocation(MyShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(MyShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        */

        // Get the uniform locations
        GLint modelLoc = glGetUniformLocation(AmbientLighting.Program, "model");
        GLint viewLoc  = glGetUniformLocation(AmbientLighting.Program,  "view");
        GLint projLoc  = glGetUniformLocation(AmbientLighting.Program,  "projection");
        // Pass the matrices to the shader
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Draw the loaded model
        glm::mat4 matModel;
        // Translate model to the center of the scene
        matModel = glm::translate(matModel, glm::vec3(0.0f, -1.75f, -5.0f));
        matModel = glm::scale(matModel, glm::vec3(0.2f, 0.2f, 0.2f));
        glUniformMatrix4fv(glGetUniformLocation(AmbientLighting.Program, "model"), 1, GL_FALSE, glm::value_ptr(matModel));
        crysis.Draw(AmbientLighting);

        // Translate model to the center of the scene
        matModel = glm::rotate(matModel, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        matModel = glm::translate(matModel, glm::vec3(0.0f, 2.0f, 0.0f));
        matModel = glm::scale(matModel, glm::vec3(5.0f, 5.0f, 5.0f));
        glUniformMatrix4fv(glGetUniformLocation(AmbientLighting.Program, "model"), 1, GL_FALSE, glm::value_ptr(matModel));
        house.Draw(AmbientLighting);

        // Translate model to the center of the scene
        matModel = glm::rotate(matModel, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        matModel = glm::translate(matModel, glm::vec3(5.0f, -19.0f, 55.0f));
        matModel = glm::scale(matModel, glm::vec3(0.2f, 0.2f, 0.2f));
        glUniformMatrix4fv(glGetUniformLocation(AmbientLighting.Program, "model"), 1, GL_FALSE, glm::value_ptr(matModel));
        landscape.Draw(AmbientLighting);


        // Update the display
        windowManager.swapBuffers();
    }

    //glDeleteBuffers(1, &vbo);
    //glDeleteVertexArrays(1, &vao);


    return EXIT_SUCCESS;
}
