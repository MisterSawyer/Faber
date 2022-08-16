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
	class OpenGLRenderer : public IRenderer
	{
	public:
		OpenGLRenderer(std::unique_ptr<ContextOpenGL> context);

		bool Init(fbr::Window* window) override;
		void Render() override;
		IRenderFrame* GetFrame() override;

	private:
		//Context may wary - depending on the OS
		std::unique_ptr<ContextOpenGL> m_context;
		std::unique_ptr<OpenGLFrame> m_frame;
	};


	/*
	* Used by system factories when performing type erasue construction
	*/
	struct OpenGLRendererFactory : public RendererFactory
	{
		std::unique_ptr<fbr::IRenderer> Create(std::unique_ptr<fbr::IRendererContext> context)
		{
			if (dynamic_cast<ContextOpenGL*>(context.get()) == nullptr)
			{
				//wrong context type O.o
				//static_assert(false);

				return nullptr;
			}

			// jakos nie jestem w 100% do tego przekonany ale sprawdzilismy wczesniej czy upcasting konwersja jest mozliwa
			std::unique_ptr<ContextOpenGL> upcastContext = std::unique_ptr<ContextOpenGL>(dynamic_cast<ContextOpenGL*>(context.release()));

			return std::make_unique<OpenGLRenderer>(std::move(upcastContext));
		}
	};


	// Concept for checking if its a opengl renderer
	template<class T>
	concept IsOpenGLRendererFactory = IsRendererFactory<T> && std::is_base_of<fbr::opengl::OpenGLRendererFactory, T>::value;
}