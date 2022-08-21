#include <faber/framework.h>
#include <faber/app/app.h>

#include <faber/logger/logger.h>
#include <faber/timer/timer.h>

#include <faber/window/framework-window-listener/framework-window-listener.h>
#include <faber/app/framework-app-listener/framework-app-listener.h>

namespace fbr
{
	Framework::Framework(ISystemObjectsFactory * systemFactory)
		: m_done(false),
		m_currentApp(),
		m_lastAppTickTime(0),
		m_lastAppRenderTime(0),
		m_systemFactory(systemFactory)
	{
		LOG_INF("Framework created");
	}

	Framework::~Framework()
	{
		LOG_INF("Framework destroyed");
	}

	Framework::AppId_t Framework::RegisterApp(std::unique_ptr<IApp> app)
	{
		AppId_t hash = std::hash<std::unique_ptr<IApp>>()(app);
		auto insertion = m_apps.insert(std::make_pair(hash, std::move(app)));

		m_currentApp = hash;
		LOG_INF("App registered");

		return m_currentApp;
	}

	void Framework::ConnectWindowListener()
	{
		std::unique_ptr<FrameworkWindowListener> ptr = std::make_unique<FrameworkWindowListener>(this);
		m_window->SetListener(std::move(ptr));
	}

	void Framework::ConnectAppListener(const AppId_t & appID)
	{
		
		m_apps[appID]->SetListener(std::make_unique<FrameworkAppListener>(this, appID));
	}

	bool Framework::Init()
	{
		if (m_systemFactory == nullptr)
		{
			LOG_ERR("System factory not specyfied");
			return false;
		}

		// no apps
		if (m_apps.empty()) {
			LOG_ERR("No apps connected");
			return false;
		}

		//TODO it should not be defined here
		Resolution resolution;
		resolution.WIDTH = 1280;
		resolution.HEIGHT = 720;

		// create app window
		//TODO platform specyfic (abstract factory)
		m_window = m_systemFactory->MakeWindow(resolution);

		// install hook for the viewport
		ConnectWindowListener();

		//Create renderer
		CreateRenderer();

		//Init renderer
		if (m_renderer) {
			m_renderer->Init(m_window.get());
		}
		else
		{
			LOG_WAR("No renderer connected");
		}

		AppInitContext appInitContext;
		appInitContext.m_resolution = resolution;
		// initialize user applications
		bool success = InitializeApps(appInitContext);

		if (success) {
			LOG_INF("Framework initialized with status success");
		}
		else {
			LOG_ERR("Framework initialized with status failure");
		}

		// framework initialized
		return success;
	}

	void Framework::RegisterRenderer(std::unique_ptr<IRenderer> renderer)
	{
		m_customRenderer = true;
		m_renderer = std::move(renderer);
	}

	void Framework::CreateRenderer()
	{
		if (m_renderer)m_renderer->Destroy();

		if (m_customRenderer)
		{
			LOG_WAR("Using custom renderer - won't create new one");
			return;
		}

		if (m_rendererSystemFactory)
			m_renderer = std::move(m_rendererSystemFactory->m_object->CreateRenderer(m_window.get()));
		else
			LOG_WAR("There is no renderer factory connected to this framework");
	}

	bool Framework::InitializeApps(const AppInitContext & appInitContext)
	{
		for (auto & app : m_apps)
		{
			if (!app.second->OnInit(appInitContext)) {
				LOG_ERR("App init failed");
				return false;
			}
			else
			{
				ConnectAppListener(app.first);
			}
		}
		return true;
	}

	void Framework::Loop()
	{
		auto prev = Timer::GetInstance().GetNow();

		while (!m_done)
		{
			auto cur = Timer::GetInstance().GetNow();
			auto delta = Timer::GetInstance().ToSecondsIntv(cur - prev);
			prev = cur;

			// pump windows messages
			PumpMessages();

			// process buffered input
			ProcessInput();

			//if app is not valid then request close framework
			if (CheckCurrentAppValidity()) {

				// tick app
				{
					auto timeDelta = (float)delta;
					if (timeDelta > 0.01f)
						timeDelta = 0.01f;

					Tick(timeDelta);
				}

				// render app
				if(m_renderer)Render();
				else
				{
					CreateRenderer();
					if(m_renderer)m_renderer->Init(m_window.get());
				}
			}
		}

		if (m_renderer)m_renderer->Destroy();
	}

	void Framework::RequestExit()
	{
		if (m_done == true)return;

		for (auto & app : m_apps)
		{
			app.second->OnClose();
		}

		m_done = true;
		LOG_INF("Framework requested exit");
	}

	void Framework::Tick(const float timeDelta)
	{
		ScopedTimer timer; // for timing user implementation

		m_apps[m_currentApp]->OnTick(timeDelta);

		m_lastAppTickTime = timer.GetElaspedTime();
	}

	bool Framework::CheckCurrentAppValidity()
	{
		if (m_apps.find(m_currentApp) ==  m_apps.end())
		{
			RequestExit();
			return false;
		}

		return true;
	}

	void Framework::Render()
	{
		//Clear frame
		m_renderer->Clear();

		{
			ScopedTimer timer; // for timing user implementation
			m_apps[m_currentApp]->OnRender(m_renderer->GetFrame());

			m_lastAppRenderTime = timer.GetElaspedTime();
		}

		// present
		m_renderer->Render();
	}

	void Framework::CloseCurrentApp()
	{
		m_apps[m_currentApp]->OnClose();
		m_apps.erase(m_currentApp);
	}

	void Framework::ChooseRenderer(fbr::RendererSystemCreator* creator)
	{
		if (m_systemFactory == nullptr)
		{
			LOG_WAR("Undefined system ");
		}

		if (m_window == nullptr)
		{
			LOG_WAR("Window is not created ");
		}

		m_renderer.reset();

		m_customRenderer = false;
		m_rendererSystemFactory = creator;
	}

	void Framework::ProcessInputEvent(const InputEvent inputEvent)
	{
		m_apps[m_currentApp]->OnInput(inputEvent);
	}

	void Framework::ProcessInput()
	{
		std::vector< InputEvent > grabbedInput;

		{
			std::lock_guard< std::mutex > lock(m_inputBufferLock);
			grabbedInput = std::move(m_inputBuffer);
		}

		for (const InputEvent inputEvent : grabbedInput)
			ProcessInputEvent(inputEvent);
	}

	void Framework::BufferInput(const InputEvent inputEvent)
	{
		std::lock_guard< std::mutex > lock(m_inputBufferLock);
		m_inputBuffer.push_back(inputEvent);
	}

	//TODO PLATFORM SPECIFIC MESSAGES DISPATCHER
#define NOMINMAX
#include <Windows.h>

	void Framework::PumpMessages()
	{
		MSG msg;
		while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&msg, NULL, 0, 0))
			{
				RequestExit();
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}