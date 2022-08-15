#include "app/app.h"

//ON WINDOWS
#include "framework/system/windows/windows-objects-factory.h"

//TODO it must be resolved differently



struct AppMock : public fbr::IApp
{
	bool OnInit(fbr::AppInitContext appInitContext) override
	{
		return true;
	}

	void OnTick(const float timeDelta)override
	{

	}

	void OnInput(const fbr::InputEvent inputEvent) override
	{

	}

	//optional override (won't be invoked if renderer is not connected)
	void OnRender(fbr::IRenderFrame* frame) override
	{

	}

	void OnClose() override
	{

	}
};

struct RendererFrameMock : public fbr::IRenderFrame
{
	virtual void Reset() override
	{

	}
};

class RendererMock : public fbr::IRenderer
{
public:
	void Render()
	{

	}
};

int main() {

	std::unique_ptr<fbr::ISystemObjectsFactory> systemFactory = std::make_unique<fbr::windows::WindowsSystemObjectsFactory>(nullptr);

	std::unique_ptr<fbr::Framework> framework = std::make_unique<fbr::Framework>(systemFactory);

	framework->RegisterApp(std::make_unique<AppMock>());

	// optional
	//framework->RegisterRenderer(std::make_unique<RendererMock>());

	if (!framework->Init())
		return -1;

	framework->Loop();

  return 0;
}

#include "../sources/framework/renderer/opengl/opengl-renderer.h"

int __stdcall WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE previnstance, _In_ LPSTR cmdline, _In_ int cmdshow)
{
	std::unique_ptr<fbr::ISystemObjectsFactory> systemFactory = std::make_unique<fbr::windows::WindowsSystemObjectsFactory>(instance);


	systemFactory->CreateConsole();

	std::unique_ptr<fbr::Framework> framework = std::make_unique<fbr::Framework>(systemFactory);

	framework->RegisterApp(std::make_unique<AppMock>());

	

	//framework->RegisterRenderer(std::make_unique<RendererMock>());

	if (!framework->Init())
		return -1;

	framework->Loop();

	return 0;
}