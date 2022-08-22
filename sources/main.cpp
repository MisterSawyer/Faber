#include <unordered_set>
#include <math.h>
#include <glm/glm/gtc/constants.hpp>

#include <faber/faber.h>

// Aplikacja
struct MainApp : public fbr::IApp
{
	virtual ~MainApp() = default;

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
	}

	//optional override (won't be invoked if renderer is not connected)
	void OnRender(fbr::IRenderFrame* frame) override
	{
		frame->SetColor(fbr::Color<float>(R, 0.6f, B, 1.0f));
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
	fbr::windows::WindowsSystemObjectsFactory systemFactory(instance, cmdline, cmdshow);

	fbr::RendererSystemCreator rendererOGL(systemFactory.GetRendererContextCreator(), fbr::opengl::OpenGLRendererFactory());
	fbr::RendererSystemCreator rendererDX(systemFactory.GetRendererContextCreator(), fbr::dx::DX11RendererFactory());

	return fbr::StartApplication<MainApp>(&systemFactory, &rendererOGL);
}