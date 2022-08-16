#include "framework/framework.h"
#include "app/app.h"
#include "framework/system/windows/windows-objects-factory.h"
#include <unordered_set>

// ---------------------------
#include "../examples/SFML_RENDERER_EXAMPLE/sfml-renderer.h"
//------------------------------

// Aplikacja
struct AppMock : public fbr::IApp
{
	virtual ~AppMock() = default;

	bool OnInit(fbr::AppInitContext appInitContext) override
	{
		shape.setRadius(10);
		return true;
	}

	void OnTick(const float timeDelta)override
	{
	}

	void OnInput(const fbr::InputEvent inputEvent) override
	{
		//;'if (inputEvent.type == fbr::InputEvent::Type::KEY && inputEvent.data.keyCode == VK_ESCAPE)RequestExit();
	}

	//optional override (won't be invoked if renderer is not connected)
	void OnRender(fbr::IRenderFrame* frame) override
	{
		//to jest taki hack bo jeszcze nie wymysli³em interface IRenderFrame
		auto f = dynamic_cast<SFMLFrame* >(frame);
		if (f == nullptr) return;

		//frame traktujemy jako klatkê animacji
		f->m_objects.insert(&shape);
	}

	void OnClose() override
	{
	}
private:
	sf::CircleShape shape;
};


//-------------------------- Taki profesjonalny renderer jest w examples/SFML_RENDERER_EXAMPLE
// Mozna jednak zrobic taki renderer na "szybko" bez dynamicznego wykrywania systemu

class SFMLRendererFAST : public fbr::IRenderer
{
public:
	bool Init(fbr::Window* window)
	{
		// to jest "na szybko" wiec zak³adamy ¿e system to windows np:
		auto windowWin = dynamic_cast<fbr::windows::WindowWin*>(window);

		
		//https://www.sfml-dev.org/tutorials/1.6/graphics-win32.php
		m_window = std::make_unique<sf::RenderWindow>(windowWin->CreateViewBuffer());

		return m_window != nullptr;
	}

	void Render()
	{
		m_window->clear();

		for (const auto& obj : m_frame.m_objects)
		{
			m_window->draw(*obj);
		}

		m_window->display();
	}

	fbr::IRenderFrame* GetFrame() 
	{
		return &m_frame;
	}
private:
	SFMLFrame m_frame;
	std::unique_ptr<sf::RenderWindow> m_window;
};


int __stdcall WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE previnstance, _In_ LPSTR cmdline, _In_ int cmdshow)
{
	fbr::windows::WindowsSystemObjectsFactory systemFactory(instance);
	systemFactory.CreateConsole();

	// Used when choosing predefined renderers with dynamic system detection
	// with custom context depending on the operating sytstem
	// 
	fbr::RendererSystemCreator rendererCreator(systemFactory.GetRendererContextCreator(), SFMLRendererFactory());

	fbr::Framework framework(&systemFactory);
	fbr::Framework::AppId_t appid0 = framework.RegisterApp(std::make_unique<AppMock>());

	const bool RENDERER_FAST = false;

	if(RENDERER_FAST)framework.RegisterRenderer(std::make_unique<SFMLRendererFAST>());
	else 
	{

		framework.ChooseRenderer(&rendererCreator);
	}

	if (!framework.Init())
		return -1;

	framework.Loop();

	return 0;
}