#include "Application.h"
#include "Renderer.h"
#include "Terminal.h"
#include <memory>
#include <pthread.h>

namespace Tenderer
{

Application::Application()
    : p_Terminal(std::make_unique<Terminal>()),
      p_Renderer(std::make_unique<Renderer>(p_Terminal)),
      buffer(p_Terminal->props.width, p_Terminal->props.height),
      compBuffer(p_Terminal->props.width, p_Terminal->props.height)
{
}

Application::~Application()
{
}

unsigned int Application::Width() const
{
	return p_Terminal->props.width;
}
unsigned int Application::Height() const
{
	return p_Terminal->props.height;
}

void Application::RenderScreen()
{
	p_Renderer->RenderScreen(buffer, compBuffer);
}
void Application::Fill(const Pixel& color)
{
	p_Renderer->Fill(buffer, color);
}
void Application::Point(uint x, uint y, const Pixel& color)
{
	p_Renderer->Point(buffer, x, y, color);
}

void Application::SetTitle(const std::string& title)
{
	p_Terminal->SetTitle(title);
}

} // namespace Tenderer
