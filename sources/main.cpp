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

	std::unique_ptr<fbr::Framework> framework = std::make_unique<fbr::Framework>(systemFactory.get());

	framework->RegisterApp(std::make_unique<AppMock>());

	// optional
	//framework->RegisterRenderer(std::make_unique<RendererMock>());

	if (!framework->Init())
		return -1;

	framework->Loop();

  return 0;
}

#include "../sources/framework/renderer/opengl/opengl-renderer.h"
#include <iostream>

struct var {
	template <typename _Ty> var& operator = (_Ty src) {
		_inner = std::make_unique<inner<_Ty>>(std::forward<_Ty>(src));
		return *this;
	}
	struct inner_base {
		using ptr = std::unique_ptr<inner_base>;
	};
	template <typename _Ty> struct inner : inner_base {
		inner(_Ty newval) : _value(newval) {}
	private:
		_Ty _value;
	};
private:
	typename inner_base::ptr _inner;
};

//------------
struct IContext
{
	virtual ~IContext() = default;
};

//--------
struct OGLContext : public IContext
{};

struct OGLContextWin : public OGLContext
{
 // windows specyfic
	OGLContextWin(int) {}
};

struct OGLContextLin : public OGLContext
{
	// linux specyfic
	OGLContextLin(std::string) {}
};
// ---- dx

struct DXContext : public IContext
{
};

struct DXContextWin : public DXContext
{
	// windows specyfic
	DXContextWin(char) {}
};

struct DXContextLin : public DXContext
{
	// linux specyfic
	DXContextLin(float) {}
};


//----
struct IR
{};

struct IOGL : public IR
{
	IOGL(OGLContext * con) {}
};

struct IDX : public IR
{
	IDX(DXContext * con) {}
};

//----------

#include <type_traits>



struct AbstractSystemFactory
{
public:
	template < typename T, typename U>
	AbstractSystemFactory( T && obj, U && cr) : object(std::make_shared<SystemFactory<T, U>>(std::forward<T>(obj), std::forward<U>(cr))) {}

	struct RendererCreator {
		virtual ~RendererCreator() {}
		virtual IR * create(IContext* c) const = 0;
		template<class T>
		IContext* ccon() const
		{

		}
	};

	template<typename T, typename U>
	struct SystemFactory : RendererCreator {
		using crt_ = U;
		
		SystemFactory(const T& t, const U & cr) : object(t), creator(cr) {}

		IR * create(IContext* c) const override
		{
			IContext* context = object.ccon<std::remove_reference<crt_>::type>();
			

			return creator.create(context);
		}

	private:
		T object;
		U creator;
	};

	std::shared_ptr<const RendererCreator> object;
};

struct OGL {
	IR* create(IContext* c) const
	{
		return new IOGL(dynamic_cast<OGLContext*>(c));
	}
};


struct DX{
	IR * create(IContext* c) const
	{
		return new IDX(dynamic_cast<DXContext*>(c));
	}
};


struct Win
{
	template<class T>
	IContext * ccon() const
	{
		return nullptr;
	}

	template<>
	IContext* ccon<OGL>() const
	{
		return new OGLContextWin(7);
	}

	template<>
	IContext* ccon<DX>() const
	{
		return new DXContextWin('a');
	}
};


struct Lin
{
	template<class T>
	IContext* ccon()
	{
		return nullptr;
	}

	template<>
	IContext* ccon<OGL>()
	{
		return new OGLContextLin("bela");
	}

	template<>
	IContext* ccon<DX>()
	{
		return new DXContextLin(19.56f);
	}
};


class MockR : public fbr::IRenderer
{

};

#include "framework/renderer/renderer-creator.h"

int __stdcall WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE previnstance, _In_ LPSTR cmdline, _In_ int cmdshow)
{


	
	//auto ren2 = www.CreateContext<IR>();


	std::unique_ptr<fbr::windows::WindowsSystemObjectsFactory> systemFactory = std::make_unique<fbr::windows::WindowsSystemObjectsFactory>(instance);


	auto wnd = systemFactory->MakeWindow(fbr::Resolution(100, 100));

	systemFactory->GetRendererContextCreator().SetWindow(dynamic_cast<fbr::windows::WindowWin *>(wnd.get()));

	fbr::RendererSystemCreator cr(systemFactory->GetRendererContextCreator(), fbr::opengl::OpenGLRendererFactory());
	auto rrr = cr.m_object->CreateRenderer();

	systemFactory->CreateConsole();

	std::unique_ptr<fbr::Framework> framework = std::make_unique<fbr::Framework>(systemFactory.get());

	framework->RegisterApp(std::make_unique<AppMock>());


	//framework->RegisterRenderer(std::make_unique<RendererMock>());

	if (!framework->Init())
		return -1;

	framework->Loop();

	return 0;
}