#include "Renderer.h"
#include <cstring>
#include <sstream>
#include <vector>
#include <iostream>

namespace Tenderer
{

Renderer::Renderer(std::shared_ptr<Terminal> _terminal) : terminal(_terminal)
{
}

Renderer::~Renderer()
{
}

template<typename T> void Renderer::Fill(const Buffer<T>& buffer, const T& color)
{
	for(size_t i = 0; i < buffer.size(); i++) { buffer[i] = color; }
}

void Renderer::RenderScreen()
{
	// index = y * width + x
	// x = index/(y * width)
	// y = index / width - x

	std::stringstream ss;
	for(auto i : pixelChanges)
	{
		// std::cout << i << std::endl;
		// std::cout << "changed color to " << buffer[i].r << " " << buffer[i].g << " " << buffer[i].b << std::endl;
		// std::cout << "Changing pos to: " << i % terminal->props.width << " "
		//<< std::floor(i / terminal->props.width)
		//<< std::endl;

		terminal->GetPos(ss, i % terminal->props.width, std::floor(i / terminal->props.width));
		terminal->GetColor(ss, buffer[i]);
	}

	std::cout << ss.str() << std::flush;

	pixelChanges.clear();
}
void Renderer::Point(unsigned int x, unsigned int y, const Pixel& color)
{
	buffer[INDEX2D(x, y)] = color;
	pixelChanges.push_back(INDEX2D(x, y));
}

} // namespace Tenderer
