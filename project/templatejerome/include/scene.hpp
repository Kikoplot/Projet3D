#pragma once

#include <glimac/SDLWindowManager.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <GL/glew.h>

#include <include/assimp/Importer.hpp>
#include <include/assimp/scene.h>
#include "model.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "skybox.hpp"

using namespace std;
using namespace glimac;

class Scene {
  public:
    Scene();
    void update(SDLWindowManager* windowManager, float screenWidth, float screenHeight);
    void loadScene(string PathTxt);

  private:
    map<string, Shader> shaders;
    map<string, Model> models;
    Skybox skybox;
    Camera camera;
    void displayModels(float screenWidth, float screenHeight);
    void displaySkybox(float screenWidth, float screenHeight);
    void initLight(float screenWidth, float screenHeight);
    void moveCam(SDLWindowManager* windowManager);
};
