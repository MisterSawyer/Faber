#include "opengl-renderer-context.h"
#include "../../../logger/logger.h"
#include <GL/wglew.h>

bool fbr::opengl::ContextOpenGL::LoadOpenGLExtensions()
{
	if (glewInit() != GLEW_OK)
	{
		LOG_ERR("Loading OpenGL extensions failed.");
		return false;
	}
	LOG_INF("OpenGL extensions loaded.");
	return true;
}


void fbr::opengl::ContextOpenGL::SetOpenGLSettings()
{
	SetBackgroundColor(fbr::Color<float>(255,255,255));
	SetDepthClearValue(1.0);
	SetStencilClearValue(0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_MULTISAMPLE);
}

void fbr::opengl::ContextOpenGL::SetAsRenderTarget()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void fbr::opengl::ContextOpenGL::Clear()
{
	glClear(static_cast<GLbitfield>(SurfaceMask::COLOR_BUFFER) | 
		static_cast<GLbitfield>(SurfaceMask::DEPTH_BUFFER) | 
		static_cast<GLbitfield>(SurfaceMask::STENCIL_BUFFER));
}

void fbr::opengl::ContextOpenGL::ClearBuffers(fbr::opengl::SurfaceMask masks)
{
	glClear(static_cast<GLbitfield>(masks));
}

void fbr::opengl::ContextOpenGL::SetBackgroundColor(const Color<float>& color)
{
	glClearColor(color.R(), color.G(), color.B(), color.Alpha());
}

void fbr::opengl::ContextOpenGL::SetDepthClearValue(double depth)
{
	glClearDepth(depth);
}

void fbr::opengl::ContextOpenGL::SetStencilClearValue(int stencil)
{
	glClearStencil(stencil);
}

void fbr::opengl::ContextOpenGL::SwitchDepthTest(bool enable)
{
	if (enable) glEnable(GL_DEPTH_TEST);
	else glDisable(GL_DEPTH_TEST);
}

void fbr::opengl::ContextOpenGL::SwitchStencilTest(bool enable)
{
	if (enable) glEnable(GL_STENCIL_TEST);
	else glDisable(GL_STENCIL_TEST);
}