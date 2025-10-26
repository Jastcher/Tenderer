
#pragma once

#include <memory>

#include "Buffer.h"
#include "Renderer.h"
#include "Terminal.h"

namespace Tenderer {

class Application {
public:
  Application();
  ~Application();

  unsigned int Width() const;
  unsigned int Height() const;

  void RenderScreen();
  void Fill(const Color &color);
  void Point(uint x, uint y, const Color &color);

  void SetTitle(const std::string &title);

private:
  std::shared_ptr<Terminal> p_Terminal;
  std::shared_ptr<Renderer> p_Renderer;

  Buffer buffer;
  Buffer compBuffer;
};

} // namespace Tenderer
