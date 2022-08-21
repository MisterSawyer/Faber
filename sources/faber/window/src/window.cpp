#include "window.h"
#include <framework-window-listener/framework-window-listener.h>

namespace fbr
{
	Window::Window(const Resolution& resolution)
	{
		m_resolution = resolution;
	}

	void Window::SetListener(std::unique_ptr<FrameworkWindowListener> listener)
	{
		m_listener = std::move(listener);
	}
	FrameworkWindowListener* Window::GetListener()
	{
		return m_listener.get();
	}
}