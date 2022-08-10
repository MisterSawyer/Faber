#pragma once
#include <cstddef>

namespace fbr
{
	class Framework;

	class IFrameworkListener
	{
	public:
		virtual ~IFrameworkListener() {};
	};

	class FrameworkWindowListener : public IFrameworkListener
	{
	public:
		FrameworkWindowListener(Framework* framework)
			: m_framework(framework)
		{}

		void OnClose();
		void OnKeyPress(const int keyCode);
		void OnMouseWheel(int delta);
		void OnMouseMoved(const int x, const int y);
		void OnMouseButtonClicked(const int buttonCode);

	private:
		Framework* m_framework;
	};

	class FrameworkAppListener : public IFrameworkListener
	{
	public:
		FrameworkAppListener(Framework* framework, const std::size_t & appID)
			: m_framework(framework),
			m_appID(appID)
		{}

		void RequestClose();
	private:
		std::size_t m_appID;
		Framework* m_framework;
	};
}