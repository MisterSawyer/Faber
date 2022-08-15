#pragma once

#include <concepts>
#include <Windows.h>

#include "../system-factory.h"
#include "../../renderer/opengl/opengl-renderer.h"
#include "../../window/windows/window-win.h"

//windows specyfic
#include "../../renderer/opengl/opengl-renderer-context/windows/opengl-renderer-context-windows.h"


namespace fbr::windows
{

	template<class T>
	concept IsRenderer = std::is_base_of<fbr::IRenderer, T>::value;

	template<class T>
	concept IsOpenGLRenderer = IsRenderer<T> && std::is_base_of<fbr::opengl::OpenGLRenderer, T>::value;

	//template<class T>
	//concept IsDXRenderer = std::is_base_of<dx::DXRenderer, T>::value;

	
	class WindowsSystemObjectsFactory : public fbr::ISystemObjectsFactory
	{
	public:

		WindowsSystemObjectsFactory(HINSTANCE executableInstance);
		virtual ~WindowsSystemObjectsFactory();

		std::unique_ptr<Window> MakeWindow(const Resolution& resolution)const override;

		std::unique_ptr<IRenderer> MakeRenderer(fbr::Window* window)const override;

		bool CreateConsole()const override;
		void DestroyConsole()const override;
	private:

		HINSTANCE m_executableInstance;
	};


	//custom renderer
	template<IsRenderer T>
	std::unique_ptr<IRenderer> CreateRenderer(const HINSTANCE instance, fbr::windows::WindowWin * window)
	{
		return std::make_unique<T>(instance, window->GetHandle());
	}

	//opengl renderer
	template<IsOpenGLRenderer T>
	std::unique_ptr<IRenderer> CreateRenderer(const HINSTANCE instance, fbr::windows::WindowWin * window)
	{
		auto context = std::make_unique<opengl::windows::ContextOpenGLWindows>(instance, window->GetHandle());
		return std::make_unique<opengl::OpenGLRenderer>(context);
	}
}