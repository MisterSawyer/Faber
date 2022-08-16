#include "framework-listener.h"
#include "../framework.h"

namespace fbr
{
	void IFrameworkListener::ForwardInput(InputEvent inputEvent) const
	{
		m_framework->BufferInput(std::move(inputEvent));
	}

	void FrameworkWindowListener::OnClose()
	{
		m_framework->RequestExit();
	}

	void FrameworkWindowListener::OnKeyPress(const int keyCode)
	{
		InputEvent newEvent;
		newEvent.type = InputEvent::Type::KEY;
		newEvent.data.keyCode = keyCode;
		ForwardInput(std::move(newEvent));
	}

	void FrameworkWindowListener::OnMouseWheel(int delta)
	{
		InputEvent newEvent;
		newEvent.type = InputEvent::Type::MOUSE_WHEEL;
		newEvent.data.delta = delta;
		ForwardInput(std::move(newEvent));
	}

	void FrameworkWindowListener::OnMouseMoved(const int x, const int y)
	{
		InputEvent newEvent;
		newEvent.type = InputEvent::Type::MOUSE_POSITION;
		newEvent.data.position[0] = x;
		newEvent.data.position[1] = y;
		ForwardInput(std::move(newEvent));
	}

	void FrameworkWindowListener::OnMouseButtonClicked(const int buttonCode)
	{
		InputEvent newEvent;
		newEvent.type = InputEvent::Type::MOUSE_CLICK;
		newEvent.data.keyCode = buttonCode;
		ForwardInput(std::move(newEvent));
	}

	// ---------------

	void FrameworkAppListener::RequestClose()
	{
		m_framework->CloseCurrentApp();
	}

	void FrameworkAppListener::SwitchR(fbr::RendererSystemCreator * ptr)
	{
		m_framework->ChooseRenderer(ptr);
	}
}