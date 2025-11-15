#include "Mesh.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

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

  mesh.indices = {

      0, 1, 2, 2,
      3, 0

  };

  mesh.colors = {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 0}};

  return mesh;
}

Mesh Mesh::LoadObj(const char *path) {
  Mesh mesh;

  std::ifstream file(path);
  if (!file.is_open()) {
    std::cerr << "Failed to open OBJ file: " << path << "\n";
    return mesh;
  }

  std::vector<glm::vec3> tempVertices;
  std::string line;
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string prefix;
    ss >> prefix;

    if (prefix == "v") {
      // vertex position
      float x, y, z;
      ss >> x >> y >> z;
      tempVertices.push_back(glm::vec3(x, -y, z));

      // default white color
      Color c;
      c.r = (x + 1.0f) * 0.5f * 255;
      c.g = (y + 1.0f) * 0.5f * 255;
      c.b = (z + 1.0f) * 0.5f * 255;
      mesh.colors.push_back(c);
    } else if (prefix == "f") {
      // face (assume triangles)
      int v0, v1, v2;
      char slash; // ignore texture/normal slashes
      std::string s0, s1, s2;
      ss >> s0 >> s1 >> s2;

      auto parseIndex = [](const std::string &s) -> int {
        std::stringstream ss(s);
        int idx;
        ss >> idx;
        return idx - 1; // OBJ indices start at 1
      };

      v0 = parseIndex(s0);
      v1 = parseIndex(s1);
      v2 = parseIndex(s2);

      mesh.indices.push_back(v0);
      mesh.indices.push_back(v1);
      mesh.indices.push_back(v2);
    }
  }

  mesh.vertices = tempVertices;
  mesh.renderType = RenderType::TRIANGLES;

  return mesh;
}

} // namespace Tenderer
