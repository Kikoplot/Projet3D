#include "scene.hpp"

using namespace std;
using namespace glimac;

Scene::Scene(){

}

void Scene::displayModels(float screenWidth, float screenHeight, SDLWindowManager* windowManager, float rotation){

  glm::mat4 view = this->camera.getViewMatrix();
  glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);

  // Draw the loaded model
  glm::mat4 matModel;

  // Translate model to the center of the scene
  matModel = glm::translate(matModel, glm::vec3(0.0f, -15.0f, 0.0f));
  matModel = glm::scale(matModel, glm::vec3(0.12f, 0.12f, 0.12f));
  glUniformMatrix4fv(glGetUniformLocation(this->shaders["AmbientLighting"].Program, "model"), 1, GL_FALSE, glm::value_ptr(matModel));
  this->models["landscape"].Draw(this->shaders["AmbientLighting"]);

  matModel = glm::mat4(1.0f);

  for(int i=0; i<5; i++){
    matModel = glm::translate(matModel, glm::vec3(totemPosition[i]));
    matModel = glm::scale(matModel, glm::vec3(0.01f, 0.01f, 0.01f));
    glUniformMatrix4fv(glGetUniformLocation(this->shaders["AmbientLighting"].Program, "model"), 1, GL_FALSE, glm::value_ptr(matModel));
    this->models["totem"].Draw(this->shaders["AmbientLighting"]);
    matModel = glm::mat4(1.0f);
  }

  if(windowManager->isKeyPressed(SDLK_w)){
    position = 0;
    this->camera.move(this->totemPosition, position);
  }

  if(windowManager->isKeyPressed(SDLK_x)){
    position = 1;
    this->camera.move(this->totemPosition, position);
  }

  if(windowManager->isKeyPressed(SDLK_c)){
    position = 2;
    this->camera.move(this->totemPosition, position);
  }

  if(windowManager->isKeyPressed(SDLK_v)){
    position = 3;
    this->camera.move(this->totemPosition, position);
  }

  if(windowManager->isKeyPressed(SDLK_b)){
    position = 4;
    this->camera.move(this->totemPosition, position);
  }

  for(int i=0; i<5; i++){
    matModel = glm::translate(matModel, glm::vec3(totemPosition[i].x, totemPosition[i].y + 4.0f, totemPosition[i].z));
    matModel = glm::scale(matModel, glm::vec3(0.6f, 0.6f, 0.6f));
    matModel = glm::rotate(matModel, glm::radians(34.5f+rotation), glm::vec3(1.0f, 1.0f, 1.0f));
    glUniformMatrix4fv(glGetUniformLocation(this->shaders["AmbientLighting"].Program, "model"), 1, GL_FALSE, glm::value_ptr(matModel));
    this->models["cage"].Draw(this->shaders["AmbientLighting"]);
    matModel = glm::mat4(1.0f);
  }
}


void Scene::loadScene(){
  this->shaders["AmbientLighting"] = Shader("template/shaders/ambiant_lighting.vs.glsl", "template/shaders/ambiant_lighting.fs.glsl");
  this->shaders["PointLight"] = Shader("template/shaders/point_lighting.vs.glsl", "template/shaders/point_lighting.fs.glsl");

  this->models["landscape"] = Model("assets/models/tropical/Small Tropical Island.obj");
  this->models["totem"] = Model("assets/models/column/column.obj");
  this->models["cage"] = Model("assets/models/cage/Portal Refraction Cube.3ds");

  glm::vec3 totemPosition[] = {
    glm::vec3(-24.0f, -12.5f, 18.0f),
    glm::vec3(-27.0f, -14.0f, -10.0f),
    glm::vec3(14.0f, -4.5f, -21.0f),
    glm::vec3(16.0f, 0.8f, 0.0f),
    glm::vec3(14.0f, -8.7f, 23.5f),
  };

  // Initialisation de la scène
  for(int i=0; i<5; i++){
    this->totemPosition[i] = totemPosition[i];
  }

  position = 0;

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
  // Use cooresponding shader when setting uniforms/drawing objects
  this->shaders["AmbientLighting"].Use();

  glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);
  glm::mat4 view = this->camera.getViewMatrix();

  // Get the uniform locations
  GLint modelLoc = glGetUniformLocation(this->shaders["AmbientLighting"].Program, "model");
  GLint viewLoc  = glGetUniformLocation(this->shaders["AmbientLighting"].Program,  "view");
  GLint projLoc  = glGetUniformLocation(this->shaders["AmbientLighting"].Program,  "projection");
  // Pass the matrices to the shader
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


  GLint lightPosLoc = glGetUniformLocation(this->shaders["AmbientLighting"].Program, "light.position");
  GLint viewPosLoc = glGetUniformLocation(this->shaders["AmbientLighting"].Program, "viewPos");

  glUniform3f(lightPosLoc, 0.0f, 12.0f, -38.0f);
  glUniform3f(viewPosLoc, 0.0f, 12.0f, -38.0f);

  // Set lights properties
  glUniform3f(glGetUniformLocation(this->shaders["AmbientLighting"].Program, "light.ambient"),  0.3f, 0.3f, 0.3f);
  glUniform3f(glGetUniformLocation(this->shaders["AmbientLighting"].Program, "light.diffuse"),  0.7f, 0.7f, 0.7f);
  glUniform3f(glGetUniformLocation(this->shaders["AmbientLighting"].Program, "light.specular"), 2.0f, 2.0f, 2.0f);
  // Set material properties
  glUniform1f(glGetUniformLocation(this->shaders["AmbientLighting"].Program, "material.shininess"), 32.0f);
}

void Scene::update(SDLWindowManager* windowManager, float screenWidth, float screenHeight, float rotation){
  moveCam(windowManager);
  initLight(screenWidth, screenHeight);
  displayModels(screenWidth, screenHeight, windowManager, rotation);
  displaySkybox(screenWidth, screenHeight);
}

void Scene::moveCam(SDLWindowManager* windowManager){
  if(windowManager->isKeyPressed(SDLK_z)) this->camera.moveFront(0.02);
  if(windowManager->isKeyPressed(SDLK_s)) this->camera.moveFront(-0.02);
  if(windowManager->isKeyPressed(SDLK_q)) this->camera.moveLatteral(0.02);
  if(windowManager->isKeyPressed(SDLK_d)) this->camera.moveLatteral(-0.02);

  glm::ivec2 MousePosition = glm::ivec2(0.0, 0.0);
  MousePosition = windowManager->getMousePosition();
  float MousePositionX = MousePosition.x/800.0f-0.5;
  float MousePositionY = MousePosition.y/600.0f-0.5;

  this->camera.rotateLeft(-1*MousePositionX);
  this->camera.rotateUp(-1*MousePositionY);

  // Draw the loaded model
  glm::mat4 matModel;
}
