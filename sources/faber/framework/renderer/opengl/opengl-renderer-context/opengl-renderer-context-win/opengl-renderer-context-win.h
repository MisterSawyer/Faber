#pragma once

#include <framework/renderer/opengl/opengl-renderer-context/opengl-renderer-context.h>

#define NOMINMAX
#include <Windows.h>

#include <string>

namespace fbr::opengl::windows
{
	/*
	* Windows specyfic opengl context
	*/
	class ContextOpenGLWindows : public ContextOpenGL
	{
	public:
		ContextOpenGLWindows(HINSTANCE executableInstance, HWND owner);
		virtual ~ContextOpenGLWindows();

		bool Good() const override;

	protected:
		bool Create() override;
		void Destroy() override;

	private:
		bool MakeCurrent() const override;
		void SwapBuffer() override;

		bool GetAccessToOpenGLExtensions() override;
		PIXELFORMATDESCRIPTOR GeneratePixelFormatDescriptor() const;
		std::string RegisterTemporaryClass();
		HWND CreateTemporaryWindow(const std::string & className);
		void DeleteTemporaryObjects(std::string classname, HWND handleTMP = 0, HDC devTMP = 0, HGLRC ctxTMP = 0);


		HINSTANCE m_executableInstance;
		HWND	m_handle;
		HDC		m_dev;
		HGLRC	m_ctx;
	};
}