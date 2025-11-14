#pragma once

#include "Mesh.h"
#include "glm/glm.hpp"

namespace Tenderer {

struct Transform {
  glm::vec3 position, scale, rotation;
};

class Object {

public:
  Object();
  Object(const Mesh &mesh);
  ~Object();

  glm::mat4 GetModel() const;

  Transform transform;

  Mesh mesh;

private:
};
} // namespace Tenderer
