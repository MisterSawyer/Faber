#include "framework-listener.h"
#include "../input/input.h"
#include "../framework.h"

namespace fbr
{
	void FrameworkWindowListener::OnClose()
	{
		m_framework->RequestExit();
	}

	void FrameworkWindowListener::OnKeyPress(const int keyCode)
	{
		InputEvent newEvent;
		newEvent.type = InputEvent::Type::KEY;
		newEvent.data.keyCode = keyCode;
		m_framework->BufferInput(newEvent);
	}

	void FrameworkWindowListener::OnMouseWheel(int delta)
	{
		InputEvent newEvent;
		newEvent.type = InputEvent::Type::MOUSE_WHEEL;
		newEvent.data.delta = delta;
		m_framework->BufferInput(newEvent);
	}

	void FrameworkWindowListener::OnMouseMoved(const int x, const int y)
	{
		InputEvent newEvent;
		newEvent.type = InputEvent::Type::MOUSE_POSITION;
		newEvent.data.position[0] = x;
		newEvent.data.position[1] = y;
		m_framework->BufferInput(newEvent);
	}

	void FrameworkWindowListener::OnMouseButtonClicked(const int buttonCode)
	{
		InputEvent newEvent;
		newEvent.type = InputEvent::Type::MOUSE_CLICK;
		newEvent.data.keyCode = buttonCode;
		m_framework->BufferInput(newEvent);
	}

	// ---------------

	void FrameworkAppListener::RequestClose()
	{
		m_framework->CloseCurrentApp();
	}
}