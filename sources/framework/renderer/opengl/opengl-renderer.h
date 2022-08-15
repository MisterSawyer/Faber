#pragma once

#include "../../renderer/renderer.h"

#include "opengl-renderer-context/opengl-renderer-context.h"
#include "opengl-surface-bitfields.h"
#include "opengl-shader/opengl-shader.h"
#include "opengl-frame/opengl-frame.h"

namespace fbr::opengl
{
	/*
	* Renderer is a combination of Context and Frame(data to draw) (and additional object like for e.x Shader)
	* it has knowledge of how to use data from Frame to draw it on screen
	*/
	struct OpenGLRenderer : public IRenderer
	{
	public:
		OpenGLRenderer(std::unique_ptr<ContextOpenGL> context);

		bool Init() override;
		void Render() override;
		IRenderFrame* GetFrame() override;

	private:
		//Context may wary - depending on the OS
		std::unique_ptr<ContextOpenGL> m_context;
		std::unique_ptr<OpenGLFrame> m_frame;
	};
}