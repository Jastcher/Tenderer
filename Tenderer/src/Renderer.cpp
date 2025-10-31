#include "Renderer.h"
#include <cmath>
#include <cstring>
#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>

namespace Tenderer {

Renderer::Renderer(std::shared_ptr<Terminal> _terminal) : terminal(_terminal) {}

Renderer::~Renderer() {}

void Renderer::Fill(const Buffer &buffer, const Color &color) {
  for (size_t i = 0; i < buffer.Size(); i++) {
    buffer[i] = color;
  }
}

void Renderer::RenderScreen(Buffer &buffer, Buffer &compBuffer) {
  // index = y * width + x
  // x = index/(y * width)
  // y = index / width - x

  std::stringstream ss;
  for (unsigned int i = 0; i < buffer.Size(); i++) {
    if (buffer[i] == compBuffer[i])
      continue;

    terminal->GetPos(ss, i % terminal->props.width,
                     std::floor(i / terminal->props.width));
    terminal->GetColor(ss, buffer[i]);
  }

  write(STDOUT_FILENO, ss.str().c_str(), ss.str().size());
  // std::cout << ss.str().c_str();
  compBuffer = buffer;
}
void Renderer::Point(Buffer &buffer, unsigned int x, unsigned int y,
                     const Color &color) {
  buffer.Get(x, y) = color;
}

} // namespace Tenderer
