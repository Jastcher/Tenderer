#pragma once

#include "Buffer.h"
#include <glm/glm.hpp>
#include <vector>
namespace Tenderer {

enum class RenderType { TRIANGLES, LINES, POINTS };

class Mesh {

public:
  Mesh();
  ~Mesh();

  static Mesh CreatePlane(); //??
  static Mesh CreateCube();  //??

  std::vector<glm::vec3> vertices;
  std::vector<Color> colors;
  std::vector<int> indices;

  RenderType renderType = RenderType::TRIANGLES;

private:
};
} // namespace Tenderer
