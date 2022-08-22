#pragma once
#include <memory>
#include <concepts>

#include <framework/renderer/renderer.h>

namespace fbr
{
	/*
	* Creates renderer per operating system
	* Uses type erasure
	* 
	* Usage ex:
	* fbr::RendererSystemCreator creator(fbr::windows::WindowsSystemRendererContextFactory(...), fbr::opengl::OpenGLRendererFactory());
	* 
	* fbr::RendererSystemCreator creator(fbr::linux::LinuxSystemRendererContextFactory(...), fbr::opengl::OpenGLRendererFactory());
	* 
	* fbr::RendererSystemCreator creator(fbr::windows::WindowsSystemRendererContextFactory(...), fbr::opengl::CustomRendererFactory());
	* 
	* Function CreateRenderer() first uses System type to create aprioprieate context for type Renderer
	* then Renderer uses this context to create 
	*/
	struct RendererSystemCreator
	{
	public:
		template < typename SystemType, IsRendererFactory RendererType>
		RendererSystemCreator(SystemType&& system, RendererType&& creator) :
			m_object(std::make_unique<RendererCreatorFactory<SystemType, RendererType>>(std::forward<SystemType>(system), std::forward<RendererType>(creator))) {}

		struct RendererCreatorInterface {
			virtual ~RendererCreatorInterface() {}

			virtual std::unique_ptr<IRenderer> CreateRenderer(fbr::Window* window) = 0;
		private:
			virtual std::unique_ptr<IRenderer> CreateImpl(std::unique_ptr<fbr::IRendererContext> context) = 0;

			template<class SystemType>
			std::unique_ptr<fbr::IRendererContext> CreateContext()
			{
				static_assert(false);
			}
		};

		template<typename SystemType, IsRendererFactory RendererType>
		struct RendererCreatorFactory : RendererCreatorInterface {

			RendererCreatorFactory(const SystemType& system, const RendererType& creator) : m_object(system), m_creator(creator) {}

			std::unique_ptr<IRenderer> CreateRenderer(fbr::Window* window) override
			{
				m_object.SetWindow(window);
				return CreateImpl(nullptr);
			}

		private:
			std::unique_ptr<IRenderer> CreateImpl(std::unique_ptr<fbr::IRendererContext> context) override
			{
				std::unique_ptr<fbr::IRendererContext> newContext = m_object.CreateContext<std::remove_reference<RendererType>::type>();

				return m_creator.Create(std::move(newContext));
			}

			SystemType m_object;
			RendererType m_creator;
		};

		std::unique_ptr<RendererCreatorInterface> m_object;
	};
}