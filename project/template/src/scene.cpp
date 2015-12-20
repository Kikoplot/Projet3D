#include "scene.hpp"

using namespace std;
using namespace glimac;

Scene::Scene(){

}

void Scene::displayModels(){
  // Load models
  Shader AmbientLighting("template/shaders/ambiant_lighting.vs.glsl", "template/shaders/ambiant_lighting.fs.glsl");

  Model crysis("assets/models/nanosuit/nanosuit.obj");
  Model house("assets/models/house/fw43_lowpoly_n1.3ds");
  Model landscape("assets/models/castle/eastern ancient casttle/eastern ancient casttle.obj");

  // Draw the loaded model
  glm::mat4 matModel;
  // Translate model to the center of the scene
  matModel = glm::translate(matModel, glm::vec3(0.0f, -1.75f, -5.0f));
  matModel = glm::scale(matModel, glm::vec3(0.05f, 0.05f, 0.05f));
  glUniformMatrix4fv(glGetUniformLocation(AmbientLighting.Program, "model"), 1, GL_FALSE, glm::value_ptr(matModel));
  crysis.Draw(AmbientLighting);

  // Translate model to the center of the scene
  matModel = glm::rotate(matModel, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  matModel = glm::translate(matModel, glm::vec3(0.0f, 2.0f, 0.0f));
  matModel = glm::scale(matModel, glm::vec3(5.5f, 5.5f, 5.5f));
  glUniformMatrix4fv(glGetUniformLocation(AmbientLighting.Program, "model"), 1, GL_FALSE, glm::value_ptr(matModel));
  house.Draw(AmbientLighting);


  // Translate model to the center of the scene
  matModel = glm::rotate(matModel, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  matModel = glm::translate(matModel, glm::vec3(5.0f, -14.8f, 45.0f));
  matModel = glm::scale(matModel, glm::vec3(0.15f, 0.15f, 0.15f));
  glUniformMatrix4fv(glGetUniformLocation(AmbientLighting.Program, "model"), 1, GL_FALSE, glm::value_ptr(matModel));
  landscape.Draw(AmbientLighting);
}


void Scene::loadScene(){
  Camera camera;
  this->camera = camera;

  Skybox skybox;
  this->skybox = skybox;
}

void Scene::displaySkybox(float screenWidth, float screenHeight){

  glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);
  // Draw skybox first
  glDepthMask(GL_FALSE);// Remember to turn depth writing off
  glm::mat4 view = this->camera.getViewMatrix();
  skybox.skyboxShader.Use();
  glUniformMatrix4fv(glGetUniformLocation(this->skybox.skyboxShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(glGetUniformLocation(this->skybox.skyboxShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
  // skybox cube
  glBindVertexArray(this->skybox.skyboxVAO);
  glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.SkyboxTexture);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);
  glDepthMask(GL_TRUE);

}

void Scene::initLight(float screenWidth, float screenHeight){

  Shader AmbientLighting("template/shaders/ambiant_lighting.vs.glsl", "template/shaders/ambiant_lighting.fs.glsl");
  // Use cooresponding shader when setting uniforms/drawing objects
  AmbientLighting.Use();

  glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);
  glm::mat4 view = this->camera.getViewMatrix();

  // Get the uniform locations
  GLint modelLoc = glGetUniformLocation(AmbientLighting.Program, "model");
  GLint viewLoc  = glGetUniformLocation(AmbientLighting.Program,  "view");
  GLint projLoc  = glGetUniformLocation(AmbientLighting.Program,  "projection");
  // Pass the matrices to the shader
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


  GLint lightPosLoc = glGetUniformLocation(AmbientLighting.Program, "light.position");
  GLint viewPosLoc = glGetUniformLocation(AmbientLighting.Program, "viewPos");

  glUniform3f(lightPosLoc, 1.2f, 1.0f, 2.0f);
  glUniform3f(viewPosLoc, 1.2f, 1.0f, 2.0f);

  // Set lights properties
  glUniform3f(glGetUniformLocation(AmbientLighting.Program, "light.ambient"),  0.2f, 0.2f, 0.2f);
  glUniform3f(glGetUniformLocation(AmbientLighting.Program, "light.diffuse"),  0.5f, 0.5f, 0.5f);
  glUniform3f(glGetUniformLocation(AmbientLighting.Program, "light.specular"), 1.0f, 1.0f, 1.0f);
  // Set material properties
  glUniform1f(glGetUniformLocation(AmbientLighting.Program, "material.shininess"), 32.0f);
}

void Scene::update(SDLWindowManager* windowManager, float screenWidth, float screenHeight){
  moveCam(windowManager);
  initLight(screenWidth, screenHeight);
  displayModels();
  displaySkybox(screenWidth, screenHeight);
}

void Scene::moveCam(SDLWindowManager* windowManager){
  if(windowManager->isKeyPressed(SDLK_z)) this->camera.moveFront(0.05);
  if(windowManager->isKeyPressed(SDLK_s)) this->camera.moveFront(-0.05);
  if(windowManager->isKeyPressed(SDLK_q)) this->camera.moveLatteral(0.05);
  if(windowManager->isKeyPressed(SDLK_d)) this->camera.moveLatteral(-0.05);

  glm::ivec2 MousePosition = glm::ivec2(0.0, 0.0);
  MousePosition = windowManager->getMousePosition();
  float MousePositionX = MousePosition.x/600.0f-0.5;
  float MousePositionY = MousePosition.y/600.0f-0.5;
  this->camera.rotateLeft(-2*MousePositionX);
  this->camera.rotateUp(-2*MousePositionY);

}
