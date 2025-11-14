#include "Renderer.h"
#include "Buffer.h"
#include <cmath>
#include <cstring>
#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>

namespace Tenderer {
Color Lerp(Color a, Color b, float t) {
  Color result;
  result.r = (int)(a.r + (b.r - a.r) * t);
  result.g = (int)(a.g + (b.g - a.g) * t);
  result.b = (int)(a.b + (b.b - a.b) * t);
  return result;
}

Renderer::Renderer(std::shared_ptr<Terminal> _terminal)
    : terminal(_terminal),
      buffer(terminal->props.width, terminal->props.height),
      compBuffer(terminal->props.width * terminal->props.height) {

  std::fill(compBuffer.begin(), compBuffer.end(), true);
}

Renderer::~Renderer() {}

unsigned int Renderer::Width() const { return terminal->props.width; }
unsigned int Renderer::Height() const { return terminal->props.height; }

void Renderer::Fill(const Color &color) {
  for (size_t i = 0; i < buffer.Size(); i++) {
    if (buffer[i] != color) {
      compBuffer[i] = 1;
      buffer[i] = color;
    }
  }
}

void Renderer::RenderScreen() {
  // index = y * width + x
  // x = index/(y * width)
  // y = index / width - x

  std::stringstream ss;
  for (unsigned int i = 0; i < buffer.Size(); i++) {
    if (!compBuffer[i])
      continue;

    terminal->GetPos(ss, i % terminal->props.width,
                     std::floor(i / terminal->props.width));
    terminal->GetColor(ss, buffer[i]);
    ss << "  ";
  }

  ss << textBuffer.str();

  write(STDOUT_FILENO, ss.str().c_str(), ss.str().size());
  // std::cout << ss.str().c_str();

  std::fill(compBuffer.begin(), compBuffer.end(), false);

  textBuffer.clear();
}
void Renderer::Point(unsigned int x, unsigned int y, const Color &color) {
  if (x < 0 || y < 0 || x >= (int)Width() || y >= (int)Height())
    return;
  if (buffer.Get(x, y) != color) {
    compBuffer[INDEX2D(x, y)] = 1;
    buffer.Get(x, y) = color;
  }
}

void Renderer::Text(uint x, uint y, const char *text, const Color &color) {

  // std::fill(compBuffer.begin() + INDEX2D(x, y),
  // compBuffer.begin() + INDEX2D(x, y) + strlen(text) * 10, true);
  terminal->GetPos(textBuffer, x, y);
  terminal->GetColor(textBuffer, color);
  textBuffer << text;
}

void Renderer::Line(int x1, int y1, int x2, int y2, const Color &color1,
                    const Color &color2) {
  // Bresenham's line algorithm with color interpolation
  int dx = std::abs(x2 - x1);
  int dy = std::abs(y2 - y1);
  int sx = (x1 < x2) ? 1 : -1;
  int sy = (y1 < y2) ? 1 : -1;
  int err = dx - dy;

  int steps = std::max(dx, dy);
  if (steps == 0) {
    if (x1 >= 0 && y1 >= 0 && x1 < (int)Width() && y1 < (int)Height())
      Point(x1, y1, color1);
    return;
  }

  for (int i = 0; i <= steps; ++i) {
    float t = (float)i / (float)steps;
    if (x1 >= 0 && y1 >= 0 && x1 < (int)Width() && y1 < (int)Height())
      Point(x1, y1, Lerp(color1, color2, t));

    int e2 = 2 * err;
    if (e2 > -dy) {
      err -= dy;
      x1 += sx;
    }
    if (e2 < dx) {
      err += dx;
      y1 += sy;
    }
  }
}
void Renderer::Triangle(int x1, int y1, int x2, int y2, int x3, int y3,
                        const Color &color1, const Color &color2,
                        const Color &color3) {

  Line(x1, y1, x2, y2, color1, color2);
  Line(x2, y2, x3, y3, color2, color3);
  Line(x3, y3, x1, y1, color3, color1);
}

} // namespace Tenderer
