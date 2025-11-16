#include "Terminal.h"
#include <fcntl.h> // for fcntl()
#include <sstream>
#include <termios.h>
#include <unistd.h>

namespace Tenderer {
struct termios orig_termios;

Terminal::Terminal() {
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  props.width = size.ws_col / 2 + 1;
  props.height = size.ws_row - 1;

  // disable cursor
  std::cout << "\033[?25l";
}

Terminal::~Terminal() {}

void Terminal::GetPos(std::stringstream &ss, unsigned int x, unsigned int y) {
  ss << "\033[" << y + 1 << ";" << x * 2 + 1 << "H";
}

void Terminal::GetColor(std::stringstream &ss, const Color &color) {
  ss << "\e[48;2;" << (int)color.r << ";" << (int)color.g << ";" << (int)color.b
     << "m";
  //<< "\033[0m";
}

void Terminal::SetTitle(const std::string &s) {
  std::cout << "\033]0;" << s << "\007";
}

void Terminal::DisableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void Terminal::EnableRawMode() {
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(Terminal::DisableRawMode);

  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
  raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
  raw.c_cflag |= CS8;
  raw.c_oflag &= ~(OPOST);

  // non-blocking read returns -1 if no input
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 0;

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

} // namespace Tenderer
