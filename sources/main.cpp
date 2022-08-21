#include "faber/faber.h"
#include <faber/app/app.h>
#include <system/system-win/windows-objects-factory.h>
#include <unordered_set>
#include <math.h>
#include <glm/glm/gtc/constants.hpp>


//TODO



fbr::RendererSystemCreator* rendererCreatorOGL_ptr;
fbr::RendererSystemCreator* rendererCreatorDX_ptr;


// Aplikacja
struct AppMock : public fbr::IApp
{
	virtual ~AppMock() = default;

	bool OnInit(fbr::AppInitContext appInitContext) override
	{
		R = 0;
		B = 0;
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
		//if (inputEvent.type == fbr::InputEvent::Type::KEY && inputEvent.data.keyCode == 'D')
		//	GetListener()->SwitchR(rendererCreatorDX_ptr);
		//if (inputEvent.type == fbr::InputEvent::Type::KEY && inputEvent.data.keyCode == 'A')GetListener()->SwitchR(rendererCreatorOGL_ptr);

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
};


int __stdcall WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE previnstance, _In_ LPSTR cmdline, _In_ int cmdshow)
{
	
	auto systemFactory = std::make_unique<fbr::windows::WindowsSystemObjectsFactory>(instance);

	if(systemFactory != nullptr)
		systemFactory->CreateConsole();

	// Used when choosing predefined renderers with dynamic system detection
	// with custom context depending on the operating sytstem
	// 
	fbr::RendererSystemCreator rendererCreatorOGL(systemFactory->GetRendererContextCreator(), fbr::opengl::OpenGLRendererFactory());
	fbr::RendererSystemCreator rendererCreatorDX(systemFactory->GetRendererContextCreator(), fbr::dx::DX11RendererFactory());

	//rendererCreatorOGL_ptr = &rendererCreatorOGL;
	//rendererCreatorDX_ptr = &rendererCreatorDX;

	fbr::Framework framework(systemFactory.get());

	framework.ChooseRenderer(&rendererCreatorOGL);

	framework.RegisterApp(std::make_unique<AppMock>());

	if (!framework.Init())
		return -1;

	framework.Loop();

	systemFactory->DestroyConsole();

	return 0;
}