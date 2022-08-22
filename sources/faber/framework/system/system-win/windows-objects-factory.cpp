#include <iostream>
#include <framework/system/system-win/windows-objects-factory.h>
#include <framework/logger/logger.h>

fbr::windows::WindowsSystemObjectsFactory::WindowsSystemObjectsFactory(HINSTANCE executableInstance)
	:m_systemRendererContextFactory(executableInstance)
{
	m_executableInstance = executableInstance;
}

fbr::windows::WindowsSystemObjectsFactory::~WindowsSystemObjectsFactory()
{
	DestroyConsole();
}

std::unique_ptr<fbr::Window> fbr::windows::WindowsSystemObjectsFactory::MakeWindow(const fbr::Resolution& resolution)const
{
	return std::make_unique<fbr::windows::WindowWin>(resolution);
}

std::unique_ptr<fbr::IRenderer> fbr::windows::WindowsSystemObjectsFactory::MakeRenderer(fbr::Window* window) const
{
	fbr::windows::WindowWin* windowWin = dynamic_cast<fbr::windows::WindowWin*>(window);

	if (windowWin == nullptr)
	{
		LOG_ERR("Cannot cast to windows win");
		return nullptr;
	}

	//TODO!!!!!!!!!!!!!!!!!!!!!
	// i tu kurwa trzeba wybraæ JAKI renderer

	//sk¹d wzi¹æ ten typ ??? fbr::opengl::OpenGLRenderer

	//return CreateRenderer<fbr::opengl::OpenGLRenderer>(m_executableInstance, windowWin);

	return nullptr;
}

fbr::windows::WindowsSystemRendererContextFactory& fbr::windows::WindowsSystemObjectsFactory::GetRendererContextCreator()
{
	return m_systemRendererContextFactory;
}

bool fbr::windows::WindowsSystemObjectsFactory::CreateConsole() const
{
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen_s((FILE**)stdout, "CON", "w", stdout);
	freopen_s((FILE**)stderr, "CON", "w", stderr);
	freopen_s((FILE**)stdin, "CON", "r", stdin);
	std::ios::sync_with_stdio();
	std::cout.clear();
	std::clog.clear();
	std::cerr.clear();
	std::cin.clear();

	const HANDLE	console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	const HWND		console_window = GetConsoleWindow();

	RECT primary_client;
	GetClientRect(GetDesktopWindow(), &primary_client);

	const int screen_width = (int)(primary_client.right - primary_client.left);
	const int screen_height = (int)(primary_client.bottom - primary_client.top);

	SetConsoleTitle("Console Window");
	SetWindowLong(console_window, GWL_STYLE, WS_CAPTION | WS_BORDER);

	RECT console_rect;
	GetWindowRect(console_window, &console_rect);

	const int center_pos_x = screen_width / 2 - (int)(console_rect.right - console_rect.left) / 2;
	const int center_pos_y = screen_height / 2 - (int)(console_rect.bottom - console_rect.top) / 2;

	SetWindowPos(console_window, 0, center_pos_x, center_pos_y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

	ShowWindow(console_window, SW_SHOW);
	UpdateWindow(console_window);

	return console_handle != 0 && console_window != 0;
}

void fbr::windows::WindowsSystemObjectsFactory::DestroyConsole() const
{
	FreeConsole();
}