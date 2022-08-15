#include "opengl-renderer.h"


fbr::opengl::OpenGLRenderer::OpenGLRenderer(std::unique_ptr<ContextOpenGL> context)
{
	m_context = std::move(context);
}


bool fbr::opengl::OpenGLRenderer::Init()
{
	m_frame = std::make_unique<OpenGLFrame>();
	if (m_frame == nullptr)return false;

	return true;
}

fbr::IRenderFrame* fbr::opengl::OpenGLRenderer::GetFrame()
{
	return m_frame.get();
}

void fbr::opengl::OpenGLRenderer::Render()
{
	//TODO
}
