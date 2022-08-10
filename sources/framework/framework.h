#pragma once

#define NOMINMAX

#include <atomic>
#include <vector>
#include <mutex>
#include "renderer/renderer.h"
#include "input/input.h"
#include "../app/app-init-context.h"

namespace fbr
{
	class IApp;

	class Window;

	class Framework
	{
	public:
		Framework();
		~Framework();

		void RegisterApp(std::unique_ptr<IApp> app);
		void RegisterRenderer(std::unique_ptr<IRenderer> renderer);

		bool Init();
		void Loop();

		void RequestExit();

		void BufferInput(const InputEvent inputEvent);

		void CloseCurrentApp();
	private:
		bool InitializeApps(const AppInitContext& appInitContext);
		bool CheckCurrentAppValidity();
		void ConnectWindowListener();
		void ConnectAppListener(const std::size_t & appID);
		void Tick(const float timeDelta);
		void Render();
		void ProcessInput();
		void ProcessInputEvent(const InputEvent inputEvent);

		void PumpMessages();

		std::atomic<bool>		m_done;

		int						m_currentApp;
		std::vector< std::unique_ptr<IApp> > m_apps;

		double			m_lastAppTickTime;
		double			m_lastAppRenderTime;

		std::unique_ptr<Window> m_window;

		std::unique_ptr<IRenderer> m_renderer;

		std::mutex			m_inputBufferLock;
		std::vector< InputEvent >	m_inputBuffer;
	};
}