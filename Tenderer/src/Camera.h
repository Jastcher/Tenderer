#pragma once
#include "glm/glm.hpp"

namespace Tenderer {

enum class Projection { ORTOGRAPHIC, PERSPECTIVE };

class Camera {
public:
  Camera();
  ~Camera();

  glm::mat4 GetProjection() const;
  glm::mat4 GetView() const;
  glm::mat4 GetCameraMatrix() const;

  void Input(char c);

  glm::vec3 position = {0, 0, -3};
  glm::vec3 orientation = {0, 0, 1};
  float fov = 90.0f;
  float aspect;

  float orthoZoom = 1.0f;
  float nearPlane = 0.1f;
  float farPlane = 10.0f;

  Projection projectionType = Projection::ORTOGRAPHIC;

private:
  glm::mat4 projection;
  glm::mat4 view;
};

} // namespace Tenderer
