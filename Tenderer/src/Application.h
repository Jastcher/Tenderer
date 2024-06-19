
#pragma once

#include <memory>

#include "Terminal.h"
#include "Renderer.h"
#include "Buffer.h"

namespace Tenderer
{

class Application
{
  public:
	Application();
	~Application();

	unsigned int Width() const;
	unsigned int Height() const;

	void RenderScreen();
	void Fill(const Pixel& color);
	void Point(uint x, uint y, const Pixel& color);

	void SetTitle(const std::string& title);

  private:
	std::shared_ptr<Terminal> p_Terminal;
	std::shared_ptr<Renderer> p_Renderer;
	Buffer<Pixel> buffer;

	std::vector<unsigned int> changes;
};

} // namespace Tenderer
