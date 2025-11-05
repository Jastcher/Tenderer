#pragma once

#include "Renderer.h"
#include "glm/glm.hpp"

#include <memory>
namespace Tenderer {

class WRenderer {

public:
  WRenderer(std::shared_ptr<Renderer> renderer);
  ~WRenderer();

  void Line(glm::mat4 transform, glm::vec3 p1, glm::vec3 p2,
            const Color &color1, const Color &color2);

  void Triangle(glm::mat4 transform, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3,
                const Color &color1, const Color &color2, const Color &color3);

  void Square(glm::mat4 transform, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3,
              glm::vec3 p4, const Color &color1, const Color &color2,
              const Color &color3, const Color &color4);

private:
  std::shared_ptr<Renderer> m_Renderer;
};

} // namespace Tenderer
