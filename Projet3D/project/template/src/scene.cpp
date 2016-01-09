#include "scene.hpp"

using namespace std;
using namespace glimac;

Scene::Scene(string path_Txt){this->loadScene(path_Txt);}

void Scene::displayModels(float screenWidth, float screenHeight, SDLWindowManager* windowManager, float rotation){
  glm::vec3 lightPos(0.0f, 12.0f, -38.0f);
    // First rendering with shadow
  glm::mat4 lightProjection, lightView;
  glm::mat4 lightSpaceMatrix;
  GLfloat near_plane = 1.0f, far_plane = 7.5f;

  // Second rendering with ambient light
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  this->shaders["AmbientLighting"].Use();

  glm::mat4 view = this->camera.getViewMatrix();
  glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);

  glUniformMatrix4fv(glGetUniformLocation(this->shaders["AmbientLighting"].Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
  glUniformMatrix4fv(glGetUniformLocation(this->shaders["AmbientLighting"].Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
  // Set light uniforms
  glUniform3fv(glGetUniformLocation(this->shaders["AmbientLighting"].Program, "lightPos"), 1, &lightPos[0]);
  glUniform3fv(glGetUniformLocation(this->shaders["AmbientLighting"].Program, "viewPos"), 1, &lightPos[0]);
  glUniformMatrix4fv(glGetUniformLocation(this->shaders["AmbientLighting"].Program, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
  RenderScene(this->shaders["AmbientLighting"], windowManager, rotation,"assets/data/render1.txt");

  lightProjection = glm::perspective(45.0f, (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane); // Note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene.
  lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(1.0));
  lightSpaceMatrix = lightProjection * lightView;
  this->shaders["Shadow"].Use();

  glUniformMatrix4fv(glGetUniformLocation(this->shaders["Shadow"].Program, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

  glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
  glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
  glClear(GL_DEPTH_BUFFER_BIT);
  RenderScene(this->shaders["Shadow"], windowManager, rotation,"assets/data/render1.txt");

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Scene::RenderScene(Shader &shader,  SDLWindowManager* windowManager, float rotation,string path_Txt){
  string line,word,NameModel,ModelT1,ModelT2,ModelT3,ModelS1,ModelS2,ModelS3,ModelR1,ModelR2,ModelR3,Radian;
  ifstream file(path_Txt, ios::in);
  int i,nbModel,nbIt;
  float ModelX1,ModelX2,ModelX3,RotationCage;
  if(file){

    //Initialisation
    getline(file, line);
    stringstream iss(line);
    while(iss >> word >> nbModel)
    {
      //cout << " Number of Models : " << nbModel << endl;
    }
     for(int i=0;i<nbModel;++i)
    {
      getline(file, line);
      stringstream iss(line);
      while(iss >> NameModel >> nbIt >> ModelT1 >> ModelT2 >> ModelT3 >> ModelS1 >> ModelS2 >> ModelS3 >> Radian >> ModelR1 >> ModelR2 >> ModelR3 )
      {
        for(int j=0;j<nbIt;j++){
                    //verification pour les totems et leur positions
            if(NameModel=="totem"||NameModel=="cage"){
              ModelX1=totemPosition[j].x+atof(ModelT1.c_str());
              ModelX2=totemPosition[j].y+atof(ModelT2.c_str());
              ModelX3=totemPosition[j].z+atof(ModelT3.c_str());
            }else
            {
              ModelX1=atof(ModelT1.c_str());
              ModelX2=atof(ModelT2.c_str());
              ModelX3=atof(ModelT3.c_str());
            }
            if(NameModel!="cage")
            {
              RotationCage=0 ;
            }
            else
            {
              RotationCage=rotation + atof(Radian.c_str());
            }
         // Draw the loaded model
            glm::mat4 matModel;

            // Translate model to the center of the scene
            matModel = glm::translate(matModel, glm::vec3(ModelX1,ModelX2,ModelX3));
            matModel = glm::scale(matModel, glm::vec3(atof(ModelS1.c_str()), atof(ModelS2.c_str()), atof(ModelS3.c_str())));
            matModel = glm::rotate(matModel, glm::radians(RotationCage), glm::vec3(atof(ModelR1.c_str()), atof(ModelR2.c_str()), atof(ModelR3.c_str())));
            glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(matModel));
            this->models[(char*)NameModel.c_str()].Draw(shader);

            matModel = glm::mat4(1.0f);
        }
      }
    }

    file.close();
  }
  else{
    cerr << "Impossible d'ouvrir le fichier texte verifiez le chemin ou la nomenclature" << endl;

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
}

void Scene::loadScene(string path_Txt){


  shadows = true;

  // Configure depth map FBO
  glGenFramebuffers(1, &depthMapFBO);

  glGenTextures(1, &depthMap);
  glBindTexture(GL_TEXTURE_2D, depthMap);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

  glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
  glDrawBuffer(GL_NONE);
  glReadBuffer(GL_NONE);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);


int i,nbModel,nbShader;
  string line,word,shaderName, pathShaderVs, pathShaderFs,modelName, pathModel, modelShader;
  string p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15;
  //glm::vec3 totemPosition[5]; //initialisation du tableau des totems
  ifstream file(path_Txt, ios::in);
  if(file){

    //Initialisation
    getline(file, line);
    stringstream iss(line);
    while(iss >> word >> nbModel  >> word >> nbShader )
    {
      cout << " Number of Models : " << nbModel << " And Number of Shaders : " << nbShader << endl;
    }

    //Boucle pour les Modeles
    for(i=0;i<nbModel;++i)
    {
      getline(file, line);
      stringstream iss(line);
      while(iss >> modelName >> pathModel)
      {
        this->models[modelName] = Model((char*)pathModel.c_str());
      }
    }
    //Boucles pour les shaders
    for(i=0;i<nbShader;++i)
    {
      getline(file, line);
      stringstream iss(line);
      while(iss >> shaderName >> pathShaderVs >> pathShaderFs)
      {
        //cout << pathShaderFs << pathShaderVs << endl;
        this->shaders[shaderName] = Shader((char*)pathShaderVs.c_str(), (char*)pathShaderFs.c_str());
      }
    }
      for(i=0;i<1;i++)
      {
      getline(file, line);
      stringstream iss(line);
      while(iss >> p1 >> p2 >> p3 >> p4 >> p5 >> p6 >> p7 >> p8 >> p9 >> p10 >> p11 >> p12 >> p13 >> p14 >> p15); // position totem
      {
       // cout << p1 << " " << p2 << endl;
      }
    }
    file.close();
  }
  else{
    cerr << "Impossible d'ouvrir le fichier texte verifiez le chemin ou la nomenclature" << endl;

  }

   glm::vec3 totemPosition[] = {
    glm::vec3(atof(p1.c_str()), atof(p2.c_str()), atof(p3.c_str())),
    glm::vec3(atof(p4.c_str()), atof(p5.c_str()), atof(p6.c_str())),
    glm::vec3(atof(p7.c_str()), atof(p8.c_str()), atof(p9.c_str())),
    glm::vec3(atof(p10.c_str()), atof(p11.c_str()), atof(p12.c_str())),
    glm::vec3(atof(p13.c_str()), atof(p14.c_str()), atof(p15.c_str())),
  };

  // Initialisation de la scène
  for(int i=0; i<5; i++){
    this->totemPosition[i] = totemPosition[i];
  }

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
