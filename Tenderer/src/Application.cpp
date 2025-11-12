#include "Application.h"
#include "Terminal.h"
#include "render/Renderer.h"
#include <iterator>
#include <memory>
#include <pthread.h>
#include <thread>

namespace Tenderer {

static bool KeyAvailable() {
  fd_set fds;
  FD_ZERO(&fds);
  FD_SET(STDIN_FILENO, &fds);

  struct timeval timeout = {0, 0}; // no wait
  return select(STDIN_FILENO + 1, &fds, NULL, NULL, &timeout) > 0;
}

Application::Application()
    : terminal(std::make_unique<Terminal>()),
      renderer(std::make_unique<Renderer>(terminal)),
      wRenderer(std::make_unique<WRenderer>(renderer)) {

  terminal->EnableRawMode();
}

Application::~Application() {}

unsigned int Application::Width() const { return terminal->props.width; }
unsigned int Application::Height() const { return terminal->props.height; }

void Application::RenderScene(const Scene &scene) {
  wRenderer->RenderScene(scene);
  RenderScreen();
}

void Application::RenderScreen() {
  using namespace std::chrono;

  auto frameStart = high_resolution_clock::now();

  renderer->RenderScreen();

  auto frameEnd = high_resolution_clock::now();
  dt = duration_cast<duration<double>>(frameEnd - prevTime).count();
  fps = 1.0 / dt;
  prevTime = frameEnd;

  if (limitFps) {
    double frameDuration =
        duration_cast<duration<double>>(frameEnd - frameStart).count();
    double targetDuration = 1.0 / maxFps;

    if (frameDuration < targetDuration) {
      std::this_thread::sleep_for(
          duration<double>(targetDuration - frameDuration));
    }
  }
}
char Application::PollKey() {
  char c;
  if (KeyAvailable() && read(STDIN_FILENO, &c, 1) == 1)
    return c;
  return 0; // no key pressed
}

} // namespace Tenderer
