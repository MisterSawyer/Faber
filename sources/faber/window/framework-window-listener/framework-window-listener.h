#pragma once

#include <faber/faber.h>
#include <faber/framework-listener/framework-listener.h>

namespace fbr {
	class FrameworkWindowListener : public IFrameworkListener
	{
	public:
		FrameworkWindowListener(fbr::Framework* framework) : IFrameworkListener(framework)
		{}

		void OnClose();
		void OnKeyPress(const int keyCode);
		void OnMouseWheel(int delta);
		void OnMouseMoved(const int x, const int y);
		void OnMouseButtonClicked(const int buttonCode);

	private:
	};
}