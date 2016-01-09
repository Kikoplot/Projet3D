#pragma once

#include "glimac/glm.hpp"
#include <glimac/SDLWindowManager.hpp>
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

class Skybox {
  public:
    Skybox();
    Shader skyboxShader;
    GLuint SkyboxTexture;
    GLuint skyboxVAO, skyboxVBO;

  private:
    GLuint loadCubemap(vector<const GLchar*> faces);
};
