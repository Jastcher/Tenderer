#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include <algorithm>

namespace Tenderer {

Camera::Camera()
    : position(0.0f, 0.0f, -3.0f), yaw(0.0f), pitch(0.0f), fov(90.0f),
      orthoZoom(1.0f), nearPlane(0.1f), farPlane(100.0f),
      projectionType(Projection::PERSPECTIVE) {
  worldUp = {0.0f, 1.0f, 0.0f};
  UpdateCameraVectors();
}

Camera::~Camera() {}

void Camera::UpdateCameraVectors() {
  // Calculate forward from yaw/pitch
  forward.x = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
  forward.y = sin(glm::radians(pitch));
  forward.z = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
  forward = glm::normalize(forward);

  right = glm::normalize(glm::cross(forward, worldUp));
  up = glm::normalize(glm::cross(right, forward));
}

glm::mat4 Camera::GetView() const {
  return glm::lookAt(position, position + forward, up);
}

glm::mat4 Camera::GetProjection() const {
  if (projectionType == Projection::ORTOGRAPHIC) {
    float scale = orthoZoom;
    return glm::ortho(-aspect * scale, aspect * scale, -1.0f * scale,
                      1.0f * scale, nearPlane, farPlane);
  } else {
    return glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
  }
}

glm::mat4 Camera::GetCameraMatrix() const {
  return GetProjection() * GetView();
}

bool isPressed(const std::map<char, bool> &keyMap, char c) {
  auto it = keyMap.find(c);
  return it != keyMap.end() && it->second;
}

void Camera::Input(const std::map<char, bool> &keyMap) {
  float speed = 0.1f;
  float rotSpeed = 2.0f; // degrees per frame

  // Movement
  if (isPressed(keyMap, 'w'))
    position += forward * speed;
  if (isPressed(keyMap, 's'))
    position -= forward * speed;
  if (isPressed(keyMap, 'a'))
    position -= right * speed;
  if (isPressed(keyMap, 'd'))
    position += right * speed;
  if (isPressed(keyMap, 'e'))
    position += worldUp * speed;
  if (isPressed(keyMap, 'r'))
    position -= worldUp * speed;

  // Rotation
  if (isPressed(keyMap, 'j'))
    yaw += rotSpeed;
  if (isPressed(keyMap, 'l'))
    yaw -= rotSpeed;
  if (isPressed(keyMap, 'i'))
    pitch += rotSpeed;
  if (isPressed(keyMap, 'k'))
    pitch -= rotSpeed;

  // Clamp pitch to avoid gimbal lock
  pitch = std::clamp(pitch, -89.0f, 89.0f);

  UpdateCameraVectors();
}

} // namespace Tenderer
