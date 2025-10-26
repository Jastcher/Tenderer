#pragma once

#include "Buffer.h"
#include <iostream>
#include <sstream>
#include <sys/ioctl.h>
#include <unistd.h>

namespace Tenderer {
struct Props {
  unsigned int width = 0;
  unsigned int height = 0;
};

class Terminal {
public:
  Terminal();
  ~Terminal();

  void GetPos(std::stringstream &ss, unsigned int x, unsigned int y);
  void GetColor(std::stringstream &ss, const Color &pixel);

  void SetTitle(const std::string &title);

public:
  Props props;
};

} // namespace Tenderer
