#include "Mesh.h"

namespace Tenderer {

Mesh::Mesh() {}
Mesh::~Mesh() {}

Mesh Mesh::CreateCube() {
  Mesh mesh;
  mesh.vertices = {
      glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0.5, -0.5, -0.5),
      glm::vec3(0.5, 0.5, -0.5),   glm::vec3(-0.5, 0.5, -0.5),
      glm::vec3(-0.5, -0.5, 0.5),  glm::vec3(0.5, -0.5, 0.5),
      glm::vec3(0.5, 0.5, 0.5),    glm::vec3(-0.5, 0.5, 0.5),
  };

  mesh.indices = {// Front face
                  0, 1, 2, 2, 3, 0,

                  // Back face
                  4, 5, 6, 6, 7, 4,

                  // Left face
                  4, 0, 3, 3, 7, 4,

                  // Right face
                  1, 5, 6, 6, 2, 1,

                  // Top face
                  3, 2, 6, 6, 7, 3,

                  // Bottom face
                  4, 5, 1, 1, 0, 4};

  mesh.colors = {
      {255, 0, 0},   // 0 - červená
      {0, 255, 0},   // 1 - zelená
      {0, 0, 255},   // 2 - modrá
      {255, 255, 0}, // 3 - žltá
      {255, 0, 255}, // 4 - magenta
      {0, 255, 255}, // 5 - tyrkysová
      {255, 128, 0}, // 6 - oranžová
      {128, 0, 255}  // 7 - fialová
  };
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
