#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <include/assimp/scene.h>
#include <glm/glm.hpp>

#include "shader.hpp"

using namespace std;

struct Vertex {
    // Position
    glm::vec3 Position;
    // Normal
    glm::vec3 Normal;
    // TexCoords
    glm::vec2 TexCoords;
};

struct Texture {
    GLuint id;
    string type;
    aiString path;
};

class Mesh {
  public:
    /*  Mesh Data  */
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;
    // Constructor
    Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
    // Render the mesh
    void Draw(Shader shader);

  private:
    GLuint VAO, VBO, EBO;
    // Initializes all the buffer objects/arrays
    void setupMesh();
};
