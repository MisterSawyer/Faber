#include "opengl-renderer.h"


fbr::opengl::OpenGLRenderer::OpenGLRenderer(std::unique_ptr<ContextOpenGL> context)
{
	m_context = std::move(context);
}

fbr::IRenderFrame* fbr::opengl::OpenGLRenderer::GetFrame()
{
	return m_frame.get();
}

bool fbr::opengl::OpenGLRenderer::Init(fbr::Window* window)
{
	if (m_context != nullptr && !m_context->Good())return false;

	m_frame = std::make_unique<OpenGLFrame>();
	if (m_frame == nullptr)return false;

	return true;
}

void fbr::opengl::OpenGLRenderer::Render()
{
	//TODO
}
