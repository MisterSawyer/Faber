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
	concept IsRendererFactory = std::is_base_of<fbr::RendererFactory, T>::value;

	template<class T>
	concept IsOpenGLRendererFactory = IsRendererFactory<T> && std::is_base_of<fbr::opengl::OpenGLRendererFactory, T>::value;

	//template<class T>
	//concept IsDXRenderer = std::is_base_of<dx::DXRenderer, T>::value;


	struct WindowsSystemRendererContextFactory
	{

		WindowsSystemRendererContextFactory(const HINSTANCE instance)
			: m_instance(instance) {}

		WindowsSystemRendererContextFactory(const HINSTANCE instance, fbr::windows::WindowWin* window)
			: m_instance(instance), m_window(window) {}


		void SetWindow(fbr::windows::WindowWin* window)
		{
			m_window = window;
		}

		// custom default renderer - custom context
		template<class T>
		requires IsRendererFactory<T>
			std::unique_ptr<fbr::IRendererContext> CreateContext() const
		{
			return nullptr;
		}

		//opengl
		template<class T>
		requires IsOpenGLRendererFactory<T>
			std::unique_ptr<fbr::IRendererContext> CreateContext() const
		{
			return std::make_unique<opengl::windows::ContextOpenGLWindows>(m_instance, m_window->GetHandle());
		}

		//TODO DX

	private:
		HINSTANCE m_instance;
		fbr::windows::WindowWin* m_window;
	};


	
	class WindowsSystemObjectsFactory : public fbr::ISystemObjectsFactory
	{
	public:

		WindowsSystemObjectsFactory(HINSTANCE executableInstance);
		virtual ~WindowsSystemObjectsFactory();

		std::unique_ptr<Window> MakeWindow(const Resolution& resolution)const override;

		std::unique_ptr<IRenderer> MakeRenderer(fbr::Window* window)const override;

		fbr::windows::WindowsSystemRendererContextFactory& GetRendererContextCreator();

		bool CreateConsole()const override;
		void DestroyConsole()const override;
	private:
		fbr::windows::WindowsSystemRendererContextFactory m_systemRendererContextFactory;

		HINSTANCE m_executableInstance;
	};



}