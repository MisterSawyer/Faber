#pragma once
#include <cstddef>
#include "../framework.h"

namespace fbr
{
	class IFrameworkListener
	{
	public:
		IFrameworkListener(fbr::Framework* framework) : m_framework(framework) {}

		virtual ~IFrameworkListener() = default;
		void ForwardInput(InputEvent inputEvent) const;
	protected:
		fbr::Framework* m_framework;
	};

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

	class FrameworkAppListener : public IFrameworkListener
	{
	public:
		FrameworkAppListener(fbr::Framework* framework, const fbr::Framework::AppId_t & appID)
			: IFrameworkListener(framework),
			m_appID(appID)
		{}

		void RequestClose();
	private:
		fbr::Framework::AppId_t m_appID;
	};
}