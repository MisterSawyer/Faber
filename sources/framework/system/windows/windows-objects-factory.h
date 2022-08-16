#pragma once

#include <concepts>
#include <Windows.h>

#include "../system-factory.h"
#include "../../renderer/opengl/opengl-renderer.h"
#include "../../window/windows/window-win.h"
#include "../../renderer/renderer-creator.h"

//windows specyfic
#include "../../renderer/opengl/opengl-renderer-context/windows/opengl-renderer-context-windows.h"


namespace fbr::windows
{
	//template<class T>
	//concept IsDXRenderer = std::is_base_of<dx::DXRenderer, T>::value;

	/*
	* Creates renderer dependent context for Windows operating system
	* function CreateContext<T>()
	* When T is derivative of OpenGLRendererFactory creates ContextOpenGLWindows
	* When T is derivative of DXRendererFactory creates ContextDXWindows
	* When using custom renderer of type T CreateContext return nullptr
	*/
	struct WindowsSystemRendererContextFactory : public SystemRendererContextCreator
	{

		WindowsSystemRendererContextFactory(const HINSTANCE instance)
			: m_instance(instance), m_window(nullptr) {}

		WindowsSystemRendererContextFactory(const HINSTANCE instance, fbr::windows::WindowWin* window)
			: m_instance(instance), m_window(window) {}


		void SetWindow(fbr::Window * window) override
		{
			WindowWin* windowWin = dynamic_cast<WindowWin *>(window);
			if (windowWin == nullptr)
			{
				LOG_ERR("Cannot cast to windows type window");
			}

			m_window = windowWin;
		}

		//Custom renderer - does not create context - returns nullptr
		template<class T>
		requires IsRendererFactory<T>
			std::unique_ptr<fbr::IRendererContext> CreateContext() const
		{
			return nullptr;
		}

		//Creates ContextOpenGLWindows
		template<class T>
		requires opengl::IsOpenGLRendererFactory<T>
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

		WindowsSystemRendererContextFactory & GetRendererContextCreator();

		bool CreateConsole()const override;
		void DestroyConsole()const override;
	private:
		/*
		* Used for creating windows specyfic renderer - custom, opengl, dx, etc.
		*/
		fbr::windows::WindowsSystemRendererContextFactory m_systemRendererContextFactory;

		HINSTANCE m_executableInstance;
	};



}