#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Tenderer {

Camera::Camera() { aspect = 1.0f; }
Camera::~Camera() {}

glm::mat4 Camera::GetProjection() const {
  if (projectionType == Projection::ORTOGRAPHIC) {
    float size = orthoZoom;
    return glm::ortho(-size * aspect, size * aspect, -size, size, nearPlane,
                      farPlane);
  } else {
    return glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
  }
}

glm::mat4 Camera::GetView() const {
  glm::vec3 forward = glm::normalize(orientation);
  glm::vec3 up = glm::vec3(0, 1, 0);
  return glm::lookAt(position, position + forward, up);
}

glm::mat4 Camera::GetCameraMatrix() const {
  return GetProjection() * GetView();
}

void Camera::Input(char c) {
  float speed = 0.1f;

  glm::vec3 forward = glm::normalize(orientation);
  glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0, 1, 0)));
  glm::vec3 up = glm::vec3(0, 1, 0);

  switch (c) {
  case 'w':
    position += forward * speed;
    break;
  case 's':
    position -= forward * speed;
    break;
  case 'a':
    position -= right * speed;
    break;
  case 'd':
    position += right * speed;
    break;
  case 'r':
    position -= up * speed;
    break;
  case 'e':
    position += up * speed;
    break;

  case 'j':
    orientation = glm::normalize(glm::rotate(glm::mat4(1.0f), +0.05f, up) *
                                 glm::vec4(orientation, 0.0f));
    break;
  case 'l':
    orientation = glm::normalize(glm::rotate(glm::mat4(1.0f), -0.05f, up) *
                                 glm::vec4(orientation, 0.0f));
    break;

  case 'i':
    orientation = glm::normalize(glm::rotate(glm::mat4(1.0f), +0.05f, right) *
                                 glm::vec4(orientation, 0.0f));
    break;

  case 'k':
    orientation = glm::normalize(glm::rotate(glm::mat4(1.0f), -0.05f, right) *
                                 glm::vec4(orientation, 0.0f));
    break;
  }
}

} // namespace Tenderer
