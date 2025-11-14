#include "WRenderer.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Scene.h"
#include "glm/ext/matrix_transform.hpp"
#include <limits>
#include <memory>

namespace Tenderer {

WRenderer::WRenderer(std::shared_ptr<Renderer> renderer)
    : m_Renderer(renderer), zbuffer(m_Renderer->terminal->props.width *
                                        m_Renderer->terminal->props.height,
                                    std::numeric_limits<float>::infinity()) {};
WRenderer::~WRenderer() {};

void WRenderer::ClearDepthBuffer() {
  std::fill(zbuffer.begin(), zbuffer.end(),
            std::numeric_limits<float>::infinity());
}

void WRenderer::Point(const glm::mat4 &transform, const glm::vec3 &p1,
                      const Color &color1) {

  glm::vec4 t1 = transform * glm::vec4(p1, 1.0f);

  t1 /= t1.w;

  float z1 = t1.z;

  ToScreenSpace(t1);

  int width = m_Renderer->Width();
  int idx = t1.x + t1.y * width;
  if (z1 < zbuffer[idx]) {
    zbuffer[idx] = z1;
    m_Renderer->Point(t1.x, t1.y, color1);
  }
}
void WRenderer::Line(const glm::mat4 &transform, const glm::vec3 &p1,
                     const glm::vec3 &p2, const Color &color1,
                     const Color &color2) {

  glm::vec4 t1 = transform * glm::vec4(p1, 1.0f);
  glm::vec4 t2 = transform * glm::vec4(p2, 1.0f);

  t1 /= t1.w;
  t2 /= t2.w;

  float z1 = t1.z;
  float z2 = t2.z;

  ToScreenSpace(t1);
  ToScreenSpace(t2);

  int x1 = (int)t1.x;
  int y1 = (int)t1.y;
  int x2 = (int)t2.x;
  int y2 = (int)t2.y;

  // Bresenham's line algorithm
  int dx = std::abs(x2 - x1);
  int dy = -std::abs(y2 - y1);
  int sx = x1 < x2 ? 1 : -1;
  int sy = y1 < y2 ? 1 : -1;
  int err = dx + dy;

  int width = m_Renderer->Width();
  int height = m_Renderer->Height();

  while (true) {
    if (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height) {

      // interpolate depth
      float t = (dx > std::abs(y2 - y1)) ? ((x1 - t1.x) / (t2.x - t1.x))
                                         : ((y1 - t1.y) / (t2.y - t1.y));

      float z = z1 + t * (z2 - z1);

      // depth-test
      int idx = y1 * width + x1;
      if (z < zbuffer[idx]) {
        zbuffer[idx] = z;

        // interpolate color
        Color c;
        c.r = (uint8_t)(color1.r + t * (color2.r - color1.r));
        c.g = (uint8_t)(color1.g + t * (color2.g - color1.g));
        c.b = (uint8_t)(color1.b + t * (color2.b - color1.b));

        m_Renderer->Point(x1, y1, c);
      }
    }

    if (x1 == x2 && y1 == y2)
      break;
    int e2 = 2 * err;
    if (e2 >= dy) {
      err += dy;
      x1 += sx;
    }
    if (e2 <= dx) {
      err += dx;
      y1 += sy;
    }
  }
}

void WRenderer::TriangleFilled(const glm::mat4 &transform, const glm::vec3 &p1,
                               const glm::vec3 &p2, const glm::vec3 &p3,
                               const Color &color1, const Color &color2,
                               const Color &color3) {
  // Transform vertices to clip space
  glm::vec4 t1 = transform * glm::vec4(p1, 1.0f);
  glm::vec4 t2 = transform * glm::vec4(p2, 1.0f);
  glm::vec4 t3 = transform * glm::vec4(p3, 1.0f);

  // Perspective divide (clip -> NDC)
  if (t1.w != 0)
    t1 /= t1.w;
  if (t2.w != 0)
    t2 /= t2.w;
  if (t3.w != 0)
    t3 /= t3.w;

  int width = m_Renderer->Width();
  int height = m_Renderer->Height();
  ToScreenSpace(t1);
  ToScreenSpace(t2);
  ToScreenSpace(t3);

  // Bounding box
  int minX = (int)std::floor(std::min(std::min(t1.x, t2.x), t3.x));
  int maxX = (int)std::ceil(std::max(std::max(t1.x, t2.x), t3.x));
  int minY = (int)std::floor(std::min(std::min(t1.y, t2.y), t3.y));
  int maxY = (int)std::ceil(std::max(std::max(t1.y, t2.y), t3.y));

  // Triangle signed area
  float area = (t2.x - t1.x) * (t3.y - t1.y) - (t2.y - t1.y) * (t3.x - t1.x);
  if (area == 0.0f)
    return; // degenerate

  // Rasterization
  for (int y = minY; y <= maxY; ++y) {
    for (int x = minX; x <= maxX; ++x) {
      // Barycentric coordinates
      float w0 = (t2.x - t1.x) * (y - t1.y) - (t2.y - t1.y) * (x - t1.x);
      float w1 = (t3.x - t2.x) * (y - t2.y) - (t3.y - t2.y) * (x - t2.x);
      float w2 = (t1.x - t3.x) * (y - t3.y) - (t1.y - t3.y) * (x - t3.x);

      // Inside triangle test (supports both CW/CCW)
      if ((w0 >= 0 && w1 >= 0 && w2 >= 0) || (w0 <= 0 && w1 <= 0 && w2 <= 0)) {
        // Normalize barycentric coordinates
        float alpha =
            ((t2.x - x) * (t3.y - y) - (t2.y - y) * (t3.x - x)) / area;
        float beta = ((t3.x - x) * (t1.y - y) - (t3.y - y) * (t1.x - x)) / area;
        float gamma = 1.0f - alpha - beta;

        float z = alpha * t1.z + beta * t2.z + gamma * t3.z;

        // Interpolate color
        Color c;
        c.r = (uint8_t)(color1.r * alpha + color2.r * beta + color3.r * gamma);
        c.g = (uint8_t)(color1.g * alpha + color2.g * beta + color3.g * gamma);
        c.b = (uint8_t)(color1.b * alpha + color2.b * beta + color3.b * gamma);

        // depth check
        int idx = y * width + x;
        if (z < zbuffer[idx]) {
          zbuffer[idx] = z; // update depth
          m_Renderer->Point(x, y, c);
        }

        // Draw pixel (assume putPixel handles screen buffer)
      }
    }
  }
}

void WRenderer::RenderObject(const std::shared_ptr<Object> &object) {
  const Mesh &mesh = object->mesh;

  switch (mesh.renderType) {
  case RenderType::TRIANGLES: {
    for (size_t i = 0; i < mesh.indices.size(); i += 3) {
      TriangleFilled(
          object->GetModel(), mesh.vertices[mesh.indices[i]],
          mesh.vertices[mesh.indices[i + 1]],
          mesh.vertices[mesh.indices[i + 2]], mesh.colors[mesh.indices[i]],
          mesh.colors[mesh.indices[i + 1]], mesh.colors[mesh.indices[i + 2]]);
    }
    break;
  }

  case RenderType::LINES: {
    for (size_t i = 0; i < mesh.indices.size(); i += 3) {
      int i0 = mesh.indices[i];
      int i1 = mesh.indices[i + 1];
      int i2 = mesh.indices[i + 2];

      Line(object->GetModel(), mesh.vertices[i0], mesh.vertices[i1],
           mesh.colors[i0], mesh.colors[i1]);

      Line(object->GetModel(), mesh.vertices[i1], mesh.vertices[i2],
           mesh.colors[i1], mesh.colors[i2]);

      Line(object->GetModel(), mesh.vertices[i2], mesh.vertices[i0],
           mesh.colors[i2], mesh.colors[i0]);
    }
    break;
  }

  case RenderType::POINTS: {
    for (size_t i = 0; i < mesh.vertices.size(); i++) {
      Point(object->GetModel(), mesh.vertices[i], mesh.colors[i]);
    }
    break;
  }
  }
}

void WRenderer::RenderScene(const Scene &scene) {

  for (const auto &object : scene.objects) {
    RenderObject(object);
  }
}

void WRenderer::ToScreenSpace(glm::vec4 &p) {
  // map [-1,1] -> [0,1]
  float nx = p.x * 0.5f + 0.5f;
  float ny = p.y * 0.5f + 0.5f;
  // flip Y because screen Y grows downward
  ny = 1.0f - ny;

  p.x = std::floor(nx * (float)m_Renderer->terminal->props.width);
  p.y = std::floor(ny * (float)m_Renderer->terminal->props.height);
}
} // namespace Tenderer
