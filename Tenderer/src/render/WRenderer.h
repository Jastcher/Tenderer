#pragma once

#include "Mesh.h"
#include "Renderer.h"
#include "Scene.h"
#include "glm/glm.hpp"

#include <memory>
namespace Tenderer {

class WRenderer {

public:
  WRenderer(std::shared_ptr<Renderer> renderer);
  ~WRenderer();

  void ClearDepthBuffer();

  void Point(const glm::mat4 &transform, const glm::vec3 &p1,
             const Color &color1);

  void Line(const glm::mat4 &transform, const glm::vec3 &p1,
            const glm::vec3 &p2, const Color &color1, const Color &color2);

  void Triangle(const glm::mat4 &transform, const glm::vec3 &p1,
                const glm::vec3 &p2, const glm::vec3 &p3, const Color &color1,
                const Color &color2, const Color &color3);

  void TriangleFilled(const glm::mat4 &transform, const glm::vec3 &p1,
                      const glm::vec3 &p2, const glm::vec3 &p3,
                      const Color &color1, const Color &color2,
                      const Color &color3);

  void Square(const glm::mat4 &transform, const glm::vec3 &p1,
              const glm::vec3 &p2, const glm::vec3 &p3, const glm::vec3 &p4,
              const Color &color1, const Color &color2, const Color &color3,
              const Color &color4);

  void RenderObject(const std::shared_ptr<Object> &object);
  void RenderScene(const Scene &scene);

  void ToScreenSpace(glm::vec4 &p);

  bool wireframeMode = false;

private:
  std::shared_ptr<Renderer> m_Renderer;
  std::vector<float> zbuffer;
};

} // namespace Tenderer
