#include "window-win.h"
#include <windowsx.h>
#include "../../logger/logger.h"

namespace fbr::windows
{
	bool WindowWin::st_classRegistered = false;
	const wchar_t* WindowWin::st_className = L"FaberFrameworkWindowClass";

	LRESULT CALLBACK WindowWin::StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (uMsg == WM_CREATE)
		{
			LPCREATESTRUCT data = (LPCREATESTRUCT)lParam;
			::SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)data->lpCreateParams);
			auto* window = (WindowWin*)data->lpCreateParams;
			window->m_hwnd = hWnd;
		}

		// Process messages by window message function
		auto window = (WindowWin*) ::GetWindowLongPtr(hWnd, GWLP_USERDATA);
		if (window)
		{
			return window->WndProc(uMsg, wParam, lParam);
		}
		else
		{
			return static_cast<LRESULT>(DefWindowProc(hWnd, uMsg, wParam, lParam));
		}
	}

	WindowWin::WindowWin(const Resolution& resolution) : Window::Window(resolution), m_hwnd(NULL)
	{
		RegisterWindowClass();
		Create(resolution);
		LOG_INF("Window created");
	}

	WindowWin::~WindowWin()
	{
		Destroy();
		LOG_INF("Window destroyed");
	}

	void WindowWin::RegisterWindowClass()
	{
		if (!st_classRegistered)
		{
			WNDCLASSEXW wcex;

			ZeroMemory(&wcex, sizeof(wcex));
			wcex.cbSize = sizeof(WNDCLASSEX);
			wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
			wcex.lpfnWndProc = &StaticWndProc;
			wcex.cbClsExtra = 0;
			wcex.cbWndExtra = 0;
			wcex.hInstance = GetModuleHandle(NULL);
			wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
			wcex.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
			wcex.lpszMenuName = NULL;
			wcex.lpszClassName = st_className;

			RegisterClassExW(&wcex);

			st_classRegistered = true;
		}
	}

	LRESULT CALLBACK WindowWin::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		auto listener = GetListener();

		switch (uMsg)
		{
			// Window is closing
		case WM_CLOSE:
		{
			if (listener)
				listener->OnClose();

			PostQuitMessage(0);
			break;
		}

		// Key pressed
		case WM_KEYDOWN:
		{
			if (listener)
				listener->OnKeyPress((int)wParam);

			return 0;
		}
		// Mouse wheel moved
		case WM_MOUSEWHEEL:
		{
			if (listener)
				listener->OnMouseWheel((int)GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA);

			return 0;
		}
		// Mouse moved
		case WM_MOUSEMOVE:
		{
			if (listener)
				listener->OnMouseMoved((int)GET_X_LPARAM(lParam), (int)GET_Y_LPARAM(lParam));

			return 0;
		}
		//L Mouse click
		case WM_LBUTTONDOWN:
		{
			if (listener)
				listener->OnMouseButtonClicked(1);
			return 0;
		}

		//M Mouse click
		case WM_MBUTTONDOWN:
		{
			if (listener)
				listener->OnMouseButtonClicked(2);
			return 0;
		}
		//R Mouse click
		case WM_RBUTTONDOWN:
		{
			if (listener)
				listener->OnMouseButtonClicked(3);
			return 0;
		}
		}

		return static_cast<LRESULT>(DefWindowProc(m_hwnd, uMsg, wParam, lParam));
	}

	void WindowWin::Create(const Resolution& resolution)
	{
		DWORD dwStyle =  WS_VISIBLE | WS_CAPTION | WS_SYSMENU;
		DWORD dxExStyle = 0;

		m_windowRect;
		m_windowRect.left = 50;
		m_windowRect.top = 50;
		m_windowRect.right = m_windowRect.left + (int)resolution.WIDTH;
		m_windowRect.bottom = m_windowRect.top + (int)resolution.HEIGHT;

		AdjustWindowRect(&m_windowRect, dwStyle, FALSE);

		CreateWindowW(
			st_className,
			L"FaberFramework",
			dwStyle,
			m_windowRect.left, m_windowRect.top,
			m_windowRect.right - m_windowRect.left,
			m_windowRect.bottom - m_windowRect.top,
			NULL, NULL, GetModuleHandle(NULL), this);

		ASSERT(m_hwnd != NULL);
	}

	HWND WindowWin::CreateViewBuffer()
	{
		DWORD Style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS;
		return CreateWindowW(L"STATIC", NULL, Style,
			m_windowRect.left, m_windowRect.top,
			m_windowRect.right - m_windowRect.left,
			m_windowRect.bottom - m_windowRect.top,
			m_hwnd, NULL, GetModuleHandle(NULL), this);
	}

	void WindowWin::Destroy()
	{
		if (m_hwnd != NULL)
		{
			DestroyWindow(m_hwnd);
			m_hwnd = nullptr;
		}
	}

}