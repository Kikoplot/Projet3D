#pragma once

#include <glimac/glm.hpp>

class Camera {
  private:
    glm::vec3 m_Position; //Position de la camera
    float m_fPhi; //Coordonnées sphériques du vecteur F latteral
    float m_fTheta; //Coordonnées sphériques du vecteur F vertical

    glm::vec3 m_FrontVector; //Vecteur F
    glm::vec3 m_LeftVector; //Vecteur L
    glm::vec3 m_UpVector; //Vecteur U

  public:
    Camera(); //Constructeur

    void computeDirectionVectors(); //Calcul les vecteurs F, L et U

    void moveFront(float theta); //permettant d'avancer / reculer la caméra. Lorsque delta est positif la caméra doit avancer, sinon elle doit reculer.
    void moveLatteral(float theta); //permettant de se déplacer lattéralement comme dans un fps
    void rotateLeft(float deg); //permettant de tourner latéralement autour du centre de vision.
    void rotateUp(float deg); //permettant de tourner verticalement autour du centre de vision.

    glm::mat4 getViewMatrix() const;
};
