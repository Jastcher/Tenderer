#pragma once

#include <memory>
#include "Terminal.h"
#include "Buffer.h"

#define INDEX2D(x, y) y * terminal->props.width + x

namespace Tenderer
{

class Renderer
{

  public:
	Renderer(std::shared_ptr<Terminal> _terminal);
	~Renderer();

	template<typename T = Pixel> void RenderScreen(const Buffer<T>& buffer);

	template<typename T = Pixel> void Fill(const Buffer<T>& buffer, const T& color);
	template<typename T = Pixel>
	void Point(const Buffer<T>& buffer, unsigned int x, unsigned int y, const Pixel& color);

  private:
	std::shared_ptr<Terminal> terminal;
};

} // namespace Tenderer
