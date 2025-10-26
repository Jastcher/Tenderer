#pragma once

#include "Buffer.h"
#include "Terminal.h"
#include <memory>

#define INDEX2D(x, y) y * terminal->props.width + x

namespace Tenderer {

class Renderer {

public:
  Renderer(std::shared_ptr<Terminal> _terminal);
  ~Renderer();

  void RenderScreen(Buffer &buffer, Buffer &compBuffer);

  void Fill(const Buffer &buffer, const Color &color);

  void Point(Buffer &buffer, unsigned int x, unsigned int y,
             const Color &color);

private:
  std::shared_ptr<Terminal> terminal;
};

} // namespace Tenderer
