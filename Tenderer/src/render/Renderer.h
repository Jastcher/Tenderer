#pragma once

#include "Buffer.h"
#include "Terminal.h"
#include <memory>
#include <sstream>
#include <vector>

#define INDEX2D(x, y) y * terminal->props.width + x

namespace Tenderer {

class Renderer {

public:
  Renderer(std::shared_ptr<Terminal> _terminal);
  ~Renderer();

  unsigned int Width() const;
  unsigned int Height() const;

  void RenderScreen();

  void Fill(const Color &color);

  void Point(unsigned int x, unsigned int y, const Color &color);

  void Text(uint x, uint y, const char *text, const Color &color);

  void Line(int x, int y, int x1, int y1, const Color &color1,
            const Color &color2);
  void Triangle(int x1, int y1, int x2, int y2, int x3, int y3,
                const Color &color1, const Color &color2, const Color &color3);

private:
  std::shared_ptr<Terminal> terminal;

  std::stringstream textBuffer;

  Buffer buffer;
  std::vector<bool> compBuffer;
};
} // namespace Tenderer
