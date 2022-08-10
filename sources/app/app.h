#pragma once
#include "app-init-context.h"
#include "../framework/framework.h"
#include "../framework/framework-listener/framework-listener.h"

namespace fbr
{
	class IRenderFrame;

	class IApp
	{
	public:
		virtual ~IApp() = default;
		
		/// called when application is initialized
		virtual bool OnInit(AppInitContext appInitContext) = 0;

		// called every frame, the timeDelta contains the time from previous call of OnTick
		virtual void OnTick(const float timeDelta) = 0;

		// called whenever user pressed a key
		virtual void OnInput(const InputEvent inputEvent) = 0;

		// rendering hook that allows to render the scene
		virtual void OnRender(IRenderFrame* frame) {};

		//Called when app is closed
		virtual void OnClose() = 0;

		inline void SetListener(std::unique_ptr<FrameworkAppListener> listener) { m_listener = std::move(listener); }
	protected:
		std::unique_ptr<FrameworkAppListener>	m_listener;
	};
}