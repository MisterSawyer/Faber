#include "app/app.h"

//TODO it must be resolved differently
struct RendererFrameMock : public fbr::IRenderFrame
{
	virtual void Reset() override
	{

	}
};

struct RendererMock : public fbr::IRenderer
{
	bool Init(fbr::Window* window)override
	{
		//TODO I Don't like it
		m_frame = std::make_unique<RendererFrameMock>();
		return true;
	}

	void Render()override
	{

	}
};

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

int main() {

	std::unique_ptr<fbr::Framework> framework = std::make_unique<fbr::Framework>();

	framework->RegisterApp(std::make_unique<AppMock>());

	// optional
	framework->RegisterRenderer(std::make_unique<RendererMock>());

	if (!framework->Init())
		return -1;

	framework->Loop();

  return 0;
}