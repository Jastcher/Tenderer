#include "WRenderer.h"
#include "Renderer.h"
#include <memory>

namespace Tenderer {

static void ToScreenSpace(glm::vec4 &p, uint width, uint height) {
  // map [-1,1] -> [0,1]
  float nx = p.x * 0.5f + 0.5f;
  float ny = p.y * 0.5f + 0.5f;
  // flip Y because screen Y grows downward
  ny = 1.0f - ny;

  p.x = std::floor(nx * (float)width);
  p.y = std::floor(ny * (float)height);
}

WRenderer::WRenderer(std::shared_ptr<Renderer> renderer)
    : m_Renderer(renderer) {};
WRenderer::~WRenderer() {};

void WRenderer::Line(glm::mat4 transform, glm::vec3 p1, glm::vec3 p2,
                     const Color &color1, const Color &color2) {

  glm::vec4 t1 = transform * glm::vec4(p1, 1.0f);
  glm::vec4 t2 = transform * glm::vec4(p2, 1.0f);

  t1 /= t1.w;
  t2 /= t2.w;

  ToScreenSpace(t1, m_Renderer->Width(), m_Renderer->Height());
  ToScreenSpace(t2, m_Renderer->Width(), m_Renderer->Height());

  m_Renderer->Line(t1.x, t1.y, t2.x, t2.y, color1, color2);
}

void WRenderer::Triangle(glm::mat4 transform, glm::vec3 p1, glm::vec3 p2,
                         glm::vec3 p3, const Color &color1, const Color &color2,
                         const Color &color3) {
  glm::vec4 t1 = transform * glm::vec4(p1, 1.0f);
  glm::vec4 t2 = transform * glm::vec4(p2, 1.0f);
  glm::vec4 t3 = transform * glm::vec4(p3, 1.0f);

  t1 /= t1.w;
  t2 /= t2.w;
  t3 /= t3.w;

  ToScreenSpace(t1, m_Renderer->Width(), m_Renderer->Height());
  ToScreenSpace(t2, m_Renderer->Width(), m_Renderer->Height());
  ToScreenSpace(t3, m_Renderer->Width(), m_Renderer->Height());

  m_Renderer->Triangle(t1.x, t1.y, t2.x, t2.y, t3.x, t3.y, color1, color2,
                       color3);
}
void WRenderer::Square(glm::mat4 transform, glm::vec3 p1, glm::vec3 p2,
                       glm::vec3 p3, glm::vec3 p4, const Color &color1,
                       const Color &color2, const Color &color3,
                       const Color &color4) {
  glm::vec4 t1 = transform * glm::vec4(p1, 1.0f);
  glm::vec4 t2 = transform * glm::vec4(p2, 1.0f);
  glm::vec4 t3 = transform * glm::vec4(p3, 1.0f);
  glm::vec4 t4 = transform * glm::vec4(p4, 1.0f);

  t1 /= t1.w;
  t2 /= t2.w;
  t3 /= t3.w;
  t4 /= t4.w;

  ToScreenSpace(t1, m_Renderer->Width(), m_Renderer->Height());
  ToScreenSpace(t2, m_Renderer->Width(), m_Renderer->Height());
  ToScreenSpace(t3, m_Renderer->Width(), m_Renderer->Height());
  ToScreenSpace(t4, m_Renderer->Width(), m_Renderer->Height());

  m_Renderer->Triangle(t1.x, t1.y, t2.x, t2.y, t3.x, t3.y, color1, color2,
                       color3);
  m_Renderer->Triangle(t3.x, t3.y, t4.x, t4.y, t1.x, t1.y, color3, color4,
                       color1);
}
} // namespace Tenderer
