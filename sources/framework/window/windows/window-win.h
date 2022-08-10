#pragma once

#include <Windows.h>
#include "../window.h"


namespace fbr::windows
{
	class WindowWin : public Window
	{
	public:
		WindowWin(const Resolution& resolution);
		virtual ~WindowWin();

		inline HWND GetHandle() const { return m_hwnd; }
		HWND CreateViewBuffer();
	private:
		void RegisterWindowClass();
		void Create(const Resolution& resolution) override;
		void Destroy() override;


		static LRESULT CALLBACK StaticWndProc(HWND, UINT, WPARAM, LPARAM);
		LRESULT CALLBACK WndProc(UINT, WPARAM, LPARAM);

		static bool			st_classRegistered;
		static const wchar_t* st_className;

		HWND	m_hwnd;
		RECT m_windowRect;
	};
}