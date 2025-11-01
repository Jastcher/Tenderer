#include "Application.h"
#include "Renderer.h"
#include "Terminal.h"
#include <memory>
#include <pthread.h>

namespace Tenderer {

static bool KeyAvailable() {
  fd_set fds;
  FD_ZERO(&fds);
  FD_SET(STDIN_FILENO, &fds);

  struct timeval timeout = {0, 0}; // no wait
  return select(STDIN_FILENO + 1, &fds, NULL, NULL, &timeout) > 0;
}

Application::Application()
    : p_Terminal(std::make_unique<Terminal>()),
      p_Renderer(std::make_unique<Renderer>(p_Terminal)) {

  p_Terminal->EnableRawMode();
}

Application::~Application() {}

unsigned int Application::Width() const { return p_Terminal->props.width; }
unsigned int Application::Height() const { return p_Terminal->props.height; }

void Application::RenderScreen() { p_Renderer->RenderScreen(); }
void Application::Fill(const Color &color) { p_Renderer->Fill(color); }
void Application::Point(uint x, uint y, const Color &color) {
  p_Renderer->Point(x, y, color);
}

void Application::Text(uint x, uint y, const char *text, const Color &color) {
  p_Renderer->Text(x, y, text, color);
}

void Application::SetTitle(const std::string &title) {
  p_Terminal->SetTitle(title);
}

char Application::PollKey() {
  char c;
  if (KeyAvailable() && read(STDIN_FILENO, &c, 1) == 1)
    return c;
  return 0; // no key pressed
}

} // namespace Tenderer
