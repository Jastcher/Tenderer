#pragma once

#include "Buffer.h"
#include "Terminal.h"
#include <memory>
#include <sstream>

#define INDEX2D(x, y) y * terminal->props.width + x

namespace Tenderer {

class Renderer {

public:
  Renderer(std::shared_ptr<Terminal> _terminal);
  ~Renderer();

  void RenderScreen();

  void Fill(const Color &color);

  void Point(unsigned int x, unsigned int y, const Color &color);

  void Text(uint x, uint y, const char *text, const Color &color);

private:
  std::shared_ptr<Terminal> terminal;

  std::stringstream textBuffer;

  Buffer buffer;
  Buffer compBuffer;
};

} // namespace Tenderer
