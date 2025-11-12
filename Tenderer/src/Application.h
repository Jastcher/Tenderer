
#pragma once

#include <chrono>
#include <memory>
#include <sstream>

#include "Buffer.h"
#include "Terminal.h"
#include "render/Renderer.h"
#include "render/WRenderer.h"

namespace Tenderer {

class Application {
public:
  Application();
  ~Application();

  unsigned int Width() const;
  unsigned int Height() const;

  void RenderScene(const Scene &scene);
  void RenderScreen();
  char PollKey();

  double dt, fps;

  bool limitFps = false;
  int maxFps = 30;

  std::shared_ptr<Terminal> terminal;
  std::shared_ptr<Renderer> renderer;
  std::shared_ptr<WRenderer> wRenderer;

private:
  double crntTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::system_clock::now().time_since_epoch())
                        .count();
  std::chrono::high_resolution_clock::time_point prevTime;
};

} // namespace Tenderer
