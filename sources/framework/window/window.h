#pragma once
#include <memory>

#include "resolution.h"

namespace fbr
{
	class FrameworkWindowListener;

	class Window
	{
	public:
		Window(const Resolution & resolution);
		virtual ~Window() = default;

		void SetListener(std::unique_ptr<FrameworkWindowListener> listener);
	protected:
		virtual void Create(const Resolution& resolution) = 0;
		virtual void Destroy() = 0;

		FrameworkWindowListener* GetListener();

	private:
		std::unique_ptr<FrameworkWindowListener>		m_listener;
		Resolution m_resolution;
	};
}