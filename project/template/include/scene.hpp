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
#include <algorithm>

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
    void update(SDLWindowManager* windowManager, float screenWidth, float screenHeight, float rotation);
    void loadScene();

  private:
    glm::vec3 totemPosition[5];
    map<string, Shader> shaders;
    map<string, Model> models;
    Skybox skybox;
    Camera camera;
    int position;
    void displayModels(float screenWidth, float screenHeight, SDLWindowManager* windowManager, float rotation);
    void displaySkybox(float screenWidth, float screenHeight);
    void initLight(float screenWidth, float screenHeight);
    void moveCam(SDLWindowManager* windowManager);
};
