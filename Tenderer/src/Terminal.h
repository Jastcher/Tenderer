#pragma once

#include <sstream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>

namespace Tenderer
{
struct Pixel
{
	unsigned char r = 0;
	unsigned char g = 0;
	unsigned char b = 0;
};

struct Props
{
	unsigned int width = 0;
	unsigned int height = 0;
};

class Terminal
{
  public:
	Terminal();
	~Terminal();

	void GetPos(std::stringstream& ss, unsigned int x, unsigned int y);
	void GetColor(std::stringstream& ss, const Pixel& pixel);

	void SetTitle(const std::string& title);

  public:
	Props props;
};

} // namespace Tenderer
