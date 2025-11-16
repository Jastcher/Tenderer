#pragma once
#include "glm/glm.hpp"
#include <map>

namespace Tenderer {

enum class Projection { ORTOGRAPHIC, PERSPECTIVE };

class Camera {
public:
  Camera();
  ~Camera();

  glm::mat4 GetProjection() const;
  glm::mat4 GetView() const;
  glm::mat4 GetCameraMatrix() const;

  void Input(const std::map<char, bool> &keyMap);

  // camera transform
  glm::vec3 position;
  glm::vec3 forward;
  glm::vec3 worldUp;
  glm::vec3 up;
  glm::vec3 right;

  float yaw = 0.0f;
  float pitch = 0.0f;
  // projection parameters
  float fov = 10.0f;
  float aspect = 1.0f;
  float orthoZoom = 1.0f;
  float nearPlane = 0.1f;
  float farPlane = 10.0f;

  Projection projectionType = Projection::ORTOGRAPHIC;

private:
  void UpdateCameraVectors();
  glm::mat4 projection;
  glm::mat4 view;
};

} // namespace Tenderer
