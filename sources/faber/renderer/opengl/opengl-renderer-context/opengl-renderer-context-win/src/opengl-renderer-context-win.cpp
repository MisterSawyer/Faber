#include <opengl-renderer-context-win/opengl-renderer-context-win.h>
#include <faber/logger/logger.h>
#include <glew-2.1.0/include/GL/wglew.h>


fbr::opengl::windows::ContextOpenGLWindows::~ContextOpenGLWindows()
{
}

fbr::opengl::windows::ContextOpenGLWindows::ContextOpenGLWindows(HINSTANCE executableInstance, HWND owner)
{
	m_executableInstance = executableInstance;
	m_handle = owner;
	m_dev = GetDC(m_handle);
	m_ctx = 0;

	ASSERT_MSG(owner != 0, "ContextOpenGLWindows owner cannot be null.");

	if (!Create()) Destroy();
	else SetOpenGLSettings();
}

PIXELFORMATDESCRIPTOR fbr::opengl::windows::ContextOpenGLWindows::GeneratePixelFormatDescriptor() const
{
	PIXELFORMATDESCRIPTOR pfd = { 0 };
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.cColorBits = 24;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.iLayerType = PFD_MAIN_PLANE;
	LOG_INF("Pixel format descriptor generated.");
	return pfd;
}

std::string fbr::opengl::windows::ContextOpenGLWindows::RegisterTemporaryClass()
{
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_executableInstance;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	wc.lpfnWndProc = DefWindowProc;
	wc.lpszClassName = "opengl_temp_window_class";
	wc.lpszMenuName = nullptr;
	wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClass(&wc))
	{
		LOG_ERR("Registering temporary window class failed.");
		return std::string("");
	}

	LOG_INF("Temporary window class registered.");

	return "opengl_temp_window_class";
}

HWND fbr::opengl::windows::ContextOpenGLWindows::CreateTemporaryWindow(const std::string & classname)
{
	HWND handleTMP = CreateWindow(classname.c_str(), "", WS_POPUP, 0, 0, 300, 300, 0, 0, m_executableInstance, nullptr);

	if (handleTMP == 0)
	{
		LOG_ERR("Creating temporary window failed.");
		return 0;
	}

	LOG_INF("Temporary window created.");
	return handleTMP;
}

void fbr::opengl::windows::ContextOpenGLWindows::DeleteTemporaryObjects(std::string classname, HWND handleTMP, HDC devTMP, HGLRC ctxTMP)
{
	if (ctxTMP != 0)
	{
		wglMakeCurrent(0, 0);
		wglDeleteContext(ctxTMP);		
	} else LOG_WAR("Problem when destroying context");

	if (devTMP != 0)
	{
		ReleaseDC(handleTMP, devTMP);	
	}else LOG_WAR("Problem when destroying HDC");

	if (handleTMP != 0)
	{
		DestroyWindow(handleTMP);
		
	}else LOG_WAR("Problem when destroying temp window");

	if (!classname.empty())
	{
		UnregisterClass(classname.c_str(), m_executableInstance);
	}else LOG_WAR("Problem when uregisting temp window class");

	LOG_INF("Temporary objects deleted.");
}

bool fbr::opengl::windows::ContextOpenGLWindows::GetAccessToOpenGLExtensions()
{
	std::string classname = RegisterTemporaryClass();
	if (classname.empty())
	{
		DeleteTemporaryObjects(classname);
		return false;
	}

	HWND handleTMP = CreateTemporaryWindow(classname);
	if (handleTMP == 0)
	{
		DeleteTemporaryObjects(classname, handleTMP);
		return false;
	}

	PIXELFORMATDESCRIPTOR pfd = GeneratePixelFormatDescriptor();
	HDC devTMP = GetDC(handleTMP);

	int pf = ChoosePixelFormat(devTMP, &pfd);
	if (!SetPixelFormat(devTMP, pf, &pfd))
	{
		LOG_ERR("Setting temporary pixel format failed.");
		DeleteTemporaryObjects(classname, handleTMP, devTMP);
		return false;
	}
	LOG_INF("Temporary pixel format set.");

	HGLRC ctxTMP = wglCreateContext(devTMP);
	if (ctxTMP == 0)
	{
		LOG_ERR("Creating temporary OpenGL context failed.");
		DeleteTemporaryObjects(classname, handleTMP, devTMP, ctxTMP);
		return false;
	}

	LOG_INF("Temporary OpenGL context created.");

	if (!wglMakeCurrent(devTMP, ctxTMP))
	{
		LOG_ERR("Making temporary OpenGL context current failed.");
		DeleteTemporaryObjects(classname, handleTMP, devTMP, ctxTMP);
		return false;
	}

	LOG_INF("Temporary OpenGL context current.");

	if (!LoadOpenGLExtensions())
	{
		DeleteTemporaryObjects(classname, handleTMP, devTMP, ctxTMP);
		return false;
	}

	DeleteTemporaryObjects(classname, handleTMP, devTMP, ctxTMP);

	return true;
}


bool fbr::opengl::windows::ContextOpenGLWindows::Create()
{
	if (!GetAccessToOpenGLExtensions())
	{
		return false;
	}

	PIXELFORMATDESCRIPTOR	pfd = GeneratePixelFormatDescriptor();
	int						pf = 0;
	unsigned int			pfc = 0;

	const int dev_attributes[] =
	{
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_SWAP_METHOD_ARB, WGL_SWAP_EXCHANGE_ARB,
		WGL_COLOR_BITS_ARB, 24,
		WGL_ALPHA_BITS_ARB, 8,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
		WGL_SAMPLES_ARB, 8,
		0
	};

	const int ctx_attributes[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 3,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	if (!wglChoosePixelFormatARB(m_dev, dev_attributes, nullptr, 1, &pf, &pfc))
	{
		LOG_ERR("Choosing pixel format failed.");
		return false;
	}

	if (!SetPixelFormat(m_dev, pf, &pfd))
	{
		LOG_ERR("Setting pixel format failed.");
		return false;
	}
	LOG_INF("Pixel format set.");

	m_ctx = wglCreateContextAttribsARB(m_dev, 0, ctx_attributes);
	if (m_ctx == 0)
	{
		LOG_ERR("OpenGL 3.3 is not supported by graphics card.");
		return false;
	}
	LOG_INF("OpenGL 3.3 context created.");

	if (!wglMakeCurrent(m_dev, m_ctx))
	{
		LOG_ERR("Making OpenGL context current failed.");
		return false;
	}
	LOG_INF("OpenGL context current.");

	return true;
}


void fbr::opengl::windows::ContextOpenGLWindows::Destroy()
{
	if (m_ctx != 0)
	{
		wglMakeCurrent(0, 0);
		wglDeleteContext(m_ctx);
		m_ctx = 0;
	}
	if (m_dev != 0)
	{
		ReleaseDC(m_handle, m_dev);
		m_dev = 0;
	}

	LOG_INF("OpenGL 3.3 context deleted.");
}

bool fbr::opengl::windows::ContextOpenGLWindows::Good() const
{
	return (m_handle != 0) && (m_dev != 0) && (m_ctx != 0);
}

bool fbr::opengl::windows::ContextOpenGLWindows::MakeCurrent() const
{
	return wglMakeCurrent(m_dev, m_ctx);
}

void fbr::opengl::windows::ContextOpenGLWindows::SwapBuffer()
{
	if (SwapBuffers(m_dev) != TRUE)
	{
		LOG_ERR("Error swaping buffers" << GetLastError());
	}
}