#include "Renderer.h"
#include "Buffer.h"
#include <cmath>
#include <cstring>
#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>

namespace Tenderer {

Renderer::Renderer(std::shared_ptr<Terminal> _terminal)
    : terminal(_terminal),
      buffer(terminal->props.width, terminal->props.height),
      compBuffer(terminal->props.width, terminal->props.height) {}

Renderer::~Renderer() {}

void Renderer::Fill(const Color &color) {
  for (size_t i = 0; i < buffer.Size(); i++) {
    buffer[i] = color;
  }
}

void Renderer::RenderScreen() {
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
    ss << "  ";
  }

  ss << textBuffer.str();

  write(STDOUT_FILENO, ss.str().c_str(), ss.str().size());
  // std::cout << ss.str().c_str();
  compBuffer = buffer;

  textBuffer.clear();
}
void Renderer::Point(unsigned int x, unsigned int y, const Color &color) {
  buffer.Get(x, y) = color;
}

void Renderer::Text(uint x, uint y, const char *text, const Color &color) {

  terminal->GetPos(textBuffer, x, y);
  terminal->GetColor(textBuffer, color);
  textBuffer << text;
}

} // namespace Tenderer
