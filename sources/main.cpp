#include "framework/framework.h"
#include "app/app.h"
#include "framework/system/windows/windows-objects-factory.h"
#include <unordered_set>
#include <math.h>
#include <glm/gtc/constants.hpp>


//TODO
#include "framework/framework-listener/framework-listener.h"


// ---------------------------
#include "../examples/SFML_RENDERER_EXAMPLE/sfml-renderer.h"
//------------------------------


fbr::RendererSystemCreator* rendererCreatorOGL_ptr;
fbr::RendererSystemCreator* rendererCreatorDX_ptr;


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
		angle += timeDelta * glm::pi<float>() * 0.25f;

		if (angle > 2.0f * glm::pi<float>())angle -= 2.0f * glm::pi<float>();

		R = 0.5f * std::sin(angle) + 0.5f;
		B = 0.5f * std::cos(angle) + 0.5f;
	}

	void OnInput(const fbr::InputEvent inputEvent) override
	{
		if (inputEvent.type == fbr::InputEvent::Type::KEY && inputEvent.data.keyCode == VK_ESCAPE)RequestExit();
		if (inputEvent.type == fbr::InputEvent::Type::KEY && inputEvent.data.keyCode == 'D')
			GetListener()->SwitchR(rendererCreatorDX_ptr);
		if (inputEvent.type == fbr::InputEvent::Type::KEY && inputEvent.data.keyCode == 'A')GetListener()->SwitchR(rendererCreatorOGL_ptr);

	}

	//optional override (won't be invoked if renderer is not connected)
	void OnRender(fbr::IRenderFrame* frame) override
	{

		//frame->SetColor();

		//to jest taki hack bo jeszcze nie wymysli³em interface IRenderFrame
		auto ogl_f = dynamic_cast<fbr::opengl::OpenGLFrame* >(frame);
		if (ogl_f != nullptr) {
			ogl_f->SetColor(fbr::Color<float>(R, 0.6f, B, 1.0f));
			return;
		}


		auto dx_f = dynamic_cast<fbr::dx::DXFrame*>(frame);
		if (dx_f != nullptr) {
			dx_f->SetColor(fbr::Color<float>(1.0f-R, 0.6f, B, 1.0f));
		}
	}

	void OnClose() override
	{
	}
private:
	float R, B;
	float angle = 0;
	sf::CircleShape shape;
};


//-------------------------- 
// Taki profesjonalny renderer jest w examples/SFML_RENDERER_EXAMPLE
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
	{
		fbr::windows::WindowsSystemObjectsFactory systemFactory(instance);
		//systemFactory.CreateConsole();

		// Used when choosing predefined renderers with dynamic system detection
		// with custom context depending on the operating sytstem
		// 
		fbr::RendererSystemCreator rendererCreatorOGL(systemFactory.GetRendererContextCreator(), fbr::opengl::OpenGLRendererFactory());
		fbr::RendererSystemCreator rendererCreatorDX(systemFactory.GetRendererContextCreator(), fbr::dx::DX11RendererFactory());

		rendererCreatorOGL_ptr = &rendererCreatorOGL;
		rendererCreatorDX_ptr = &rendererCreatorDX;

		fbr::Framework framework(&systemFactory);

		framework.ChooseRenderer(&rendererCreatorOGL);

		//framework.RegisterRenderer(std::make_unique<SFMLRendererFAST>());

		framework.RegisterApp(std::make_unique<AppMock>());

		if (!framework.Init())
			return -1;

		framework.Loop();

		systemFactory.DestroyConsole();
	}

	while (true)
	{

	}

	return 0;
}