#include "Terminal.h"
#include <sstream>

namespace Tenderer {

Terminal::Terminal() {
  struct winsize size;
  ioctl(STDERR_FILENO, TIOCGWINSZ, &size);
  props.width = size.ws_col;
  props.height = size.ws_row - 1;

  // disable cursor
  std::cout << "\033[?25l";
}

Terminal::~Terminal() {}

void Terminal::GetPos(std::stringstream &ss, unsigned int x, unsigned int y) {
  ss << "\033[" << y + 1 << ";" << x + 1 << "H\033[K";
}

void Terminal::GetColor(std::stringstream &ss, const Color &color) {
  ss << "\e[48;2;" << (int)color.r << ";" << (int)color.g << ";" << (int)color.b
     << "m  ";
  //<< "\033[0m";
}

void Terminal::SetTitle(const std::string &s) {
  std::cout << "\033]0;" << s << "\007";
}

} // namespace Tenderer
