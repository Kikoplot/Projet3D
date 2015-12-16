#include "camera.hpp"
#include <iostream>
#include <cmath>

Camera::Camera(){
  m_Position = glm::vec3(0.0, 0.0, 0.0); //On initialise à 0
  m_fPhi = M_PI;
  m_fTheta = 0.0;
  computeDirectionVectors();
}

void Camera::computeDirectionVectors(){
	m_FrontVector = glm::vec3(cos(m_fTheta)*sin(m_fPhi), sin(m_fTheta), cos(m_fTheta)*cos(m_fPhi));
	m_LeftVector = glm::vec3(sin(m_fPhi+(M_PI/2.0)), 0, cos(m_fPhi+(M_PI/2.0)));
	m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
}

void Camera::moveFront(float theta){
  m_Position += theta * m_FrontVector;
  computeDirectionVectors();
}

void Camera::moveLatteral(float theta){
    m_Position += theta * m_LeftVector;
    computeDirectionVectors();
}

void Camera::rotateLeft(float deg){
  m_fPhi += glm::radians(deg);
  computeDirectionVectors();
}

void Camera::rotateUp(float deg){
  m_fTheta += glm::radians(deg);
  computeDirectionVectors();
}

glm::mat4 Camera::getViewMatrix() const{
  glm::mat4 GVM = glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
  return GVM;
}
