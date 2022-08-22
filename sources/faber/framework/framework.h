#pragma once

#include <atomic>
#include <vector>
#include <map>
#include <mutex>
#include <memory>

#include <framework/app/app-init-context.h>

#include <framework/framework-listener/framework-listener.h>
#include <framework/window/window.h>

// --- os ---
#include <framework/system/system-factory.h>

// --- renderer --- 
#include <framework/renderer/renderer.h>
#include <framework/renderer/creator/renderer-creator.h>

namespace fbr
{
	class IFrameworkListener;
	class IApp;

	class Framework
	{
	public:
		using AppId_t = std::size_t;

		friend IFrameworkListener;

		Framework(ISystemObjectsFactory * systemFactory);
		~Framework();

		AppId_t RegisterApp(std::unique_ptr<IApp> app);

		bool Init();
		void Loop();

		void RequestExit();
		void CloseCurrentApp();
		void ChooseRenderer(fbr::RendererSystemCreator* creator);

		void SwitchApp(const AppId_t & appID);

		void RegisterRenderer(std::unique_ptr<IRenderer> renderer);

	private:
		void CreateRenderer();
		bool InitializeApps(const AppInitContext& appInitContext);
		bool CheckCurrentAppValidity();
		void ConnectWindowListener();
		void ConnectAppListener(const AppId_t & appID);
		void Tick(const float timeDelta);
		void Render();
		void ProcessInput();
		void ProcessInputEvent(const InputEvent inputEvent);
		void BufferInput(const InputEvent inputEvent);

		void PumpMessages();

		ISystemObjectsFactory * m_systemFactory;
		RendererSystemCreator * m_rendererSystemFactory;
		bool m_customRenderer;

		std::atomic<bool>		m_done;

		AppId_t						m_currentApp;

		std::map<AppId_t, std::unique_ptr<IApp>> m_apps;

		double			m_lastAppTickTime;
		double			m_lastAppRenderTime;

		std::unique_ptr<Window> m_window;

		std::unique_ptr<IRenderer> m_renderer;

		std::mutex			m_inputBufferLock;
		std::vector< InputEvent >	m_inputBuffer;
	};


	template<std::derived_from<IApp> T>
	int StartApplication(fbr::ISystemObjectsFactory* systemFactory, fbr::RendererSystemCreator* renderer)
	{

		if (systemFactory != nullptr)
			systemFactory->CreateConsole();

		fbr::Framework framework(systemFactory);

		framework.ChooseRenderer(renderer);

		framework.RegisterApp(std::make_unique<T>());

		if (!framework.Init())
			return -1;

		framework.Loop();

		if (systemFactory != nullptr)
			systemFactory->DestroyConsole();

		return 0;
	}
}