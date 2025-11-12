#include "Mesh.h"

namespace Tenderer {

Mesh::Mesh() {}
Mesh::~Mesh() {}

Mesh Mesh::CreateCube() {
  Mesh mesh;

  return mesh;
}

Mesh Mesh::CreatePlane() {
  Mesh mesh;

  mesh.renderType = RenderType::TRIANGLES;

  mesh.vertices = {glm::vec3(-0.5, -0.5, 0.0), glm::vec3(0.5, -0.5, 0.0),
                   glm::vec3(0.5, 0.5, 0.0), glm::vec3(-0.5, 0.5, 0.0)};

  mesh.colors = {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 0}};

  mesh.indices = {

      0, 1, 2, 2,
      3, 0

  };

  return mesh;
}
} // namespace Tenderer
