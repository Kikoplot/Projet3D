#include "skybox.hpp"
#include <iostream>

using namespace glimac;
using namespace std;

Skybox::Skybox(){}

Skybox::Skybox(int level, int pause){

  Shader skyboxShader("template/shaders/skybox.vs.glsl", "template/shaders/skybox.fs.glsl");
  this->skyboxShader = skyboxShader;

  GLfloat skyboxVertices[] = {
          // Positions
          -40.0f,  40.0f, -40.0f,
          -40.0f, -40.0f, -40.0f,
           40.0f, -40.0f, -40.0f,
           40.0f, -40.0f, -40.0f,
           40.0f,  40.0f, -40.0f,
          -40.0f,  40.0f, -40.0f,

          -40.0f, -40.0f,  40.0f,
          -40.0f, -40.0f, -40.0f,
          -40.0f,  40.0f, -40.0f,
          -40.0f,  40.0f, -40.0f,
          -40.0f,  40.0f,  40.0f,
          -40.0f, -40.0f,  40.0f,

           40.0f, -40.0f, -40.0f,
           40.0f, -40.0f,  40.0f,
           40.0f,  40.0f,  40.0f,
           40.0f,  40.0f,  40.0f,
           40.0f,  40.0f, -40.0f,
           40.0f, -40.0f, -40.0f,

          -40.0f, -40.0f,  40.0f,
          -40.0f,  40.0f,  40.0f,
           40.0f,  40.0f,  40.0f,
           40.0f,  40.0f,  40.0f,
           40.0f, -40.0f,  40.0f,
          -40.0f, -40.0f,  40.0f,

          -40.0f,  40.0f, -40.0f,
           40.0f,  40.0f, -40.0f,
           40.0f,  40.0f,  40.0f,
           40.0f,  40.0f,  40.0f,
          -40.0f,  40.0f,  40.0f,
          -40.0f,  40.0f, -40.0f,

          -40.0f, -40.0f, -40.0f,
          -40.0f, -40.0f,  40.0f,
           40.0f, -40.0f, -40.0f,
           40.0f, -40.0f, -40.0f,
          -40.0f, -40.0f,  40.0f,
           40.0f, -40.0f,  40.0f
      };

      if(level == 1){
        ifstream file("assets/data/sky1.txt", ios::in);
        string Path,Path2,Path3,Path4,Path5,Path6,line;
        file >> Path >> Path2 >> Path3 >> Path4 >> Path5 >> Path6;
        vector<const GLchar*> faces;
        faces.push_back((char*)Path.c_str());
        faces.push_back((char*)Path2.c_str());
        faces.push_back((char*)Path3.c_str());
        faces.push_back((char*)Path4.c_str());
        faces.push_back((char*)Path5.c_str());
        faces.push_back((char*)Path6.c_str());
        GLuint cubemapTexture = loadCubemap(faces);
        this->SkyboxTexture = loadCubemap(faces);
        file.close();
      }

      if(level == 2){
        ifstream file("assets/data/sky2.txt", ios::in);
        string Path,Path2,Path3,Path4,Path5,Path6,line;
        file >> Path >> Path2 >> Path3 >> Path4 >> Path5 >> Path6;
        vector<const GLchar*> faces;
        faces.push_back((char*)Path.c_str());
        faces.push_back((char*)Path2.c_str());
        faces.push_back((char*)Path3.c_str());
        faces.push_back((char*)Path4.c_str());
        faces.push_back((char*)Path5.c_str());
        faces.push_back((char*)Path6.c_str());
        GLuint cubemapTexture = loadCubemap(faces);
        this->SkyboxTexture = loadCubemap(faces);
        file.close();
      }

      if(level == 3){
        ifstream file("assets/data/sky3.txt", ios::in);
        string Path,Path2,Path3,Path4,Path5,Path6,line;
        file >> Path >> Path2 >> Path3 >> Path4 >> Path5 >> Path6;
        vector<const GLchar*> faces;
        faces.push_back((char*)Path.c_str());
        faces.push_back((char*)Path2.c_str());
        faces.push_back((char*)Path3.c_str());
        faces.push_back((char*)Path4.c_str());
        faces.push_back((char*)Path5.c_str());
        faces.push_back((char*)Path6.c_str());
        GLuint cubemapTexture = loadCubemap(faces);
        this->SkyboxTexture = loadCubemap(faces);
        file.close();
      }

      // Setup skybox VAO
      glGenVertexArrays(1, &this->skyboxVAO);
      glGenBuffers(1, &this->skyboxVBO);
      glBindVertexArray(this->skyboxVAO);
      glBindBuffer(GL_ARRAY_BUFFER, this->skyboxVBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
      glBindVertexArray(0);
}

GLuint Skybox::loadCubemap(vector<const GLchar*> faces){
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
