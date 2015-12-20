#pragma once

#include <glimac/SDLWindowManager.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>

#include <GL/glew.h>
#include <iostream>
#include <vector>

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
    void loadScene();

  private:
    Skybox skybox;
    Camera camera;
    void displayModels();
    void displaySkybox(float screenWidth, float screenHeight);
    void initLight(float screenWidth, float screenHeight);
    void moveCam(SDLWindowManager* windowManager);
};
