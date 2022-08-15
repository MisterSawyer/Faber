#pragma once
#include <memory>

#include "renderer.h"

namespace fbr
{
	/*
	* Creates renderer per operating system
	* Uses type erasure
	*/
	struct RendererSystemCreator
	{
	public:
		template < typename System, typename Renderer>
		RendererSystemCreator(System && system, Renderer && creator) :
			m_object(std::make_shared<RendererCreatorFactory<System, Renderer>>(std::forward<System>(system), std::forward<Renderer>(creator))) {}

		struct RendererCreatorInterface {
			virtual ~RendererCreatorInterface() {}

			virtual std::unique_ptr<IRenderer> CreateRenderer() = 0;
		private:
			virtual std::unique_ptr<IRenderer> CreateImpl(std::unique_ptr<fbr::IRendererContext> context) = 0;

			template<class System>
			std::unique_ptr<fbr::IRendererContext> CreateContext()
			{
				static_assert(false);
			}
		};

		template<typename System, typename Renderer>
		struct RendererCreatorFactory : RendererCreatorInterface {

			RendererCreatorFactory(const System & system, const Renderer & creator) : m_object(system), m_creator(creator) {}

			std::unique_ptr<IRenderer> CreateRenderer() override
			{
				return CreateImpl(nullptr);
			}

		private:
			std::unique_ptr<IRenderer> CreateImpl(std::unique_ptr<fbr::IRendererContext> context) override
			{
				std::unique_ptr<fbr::IRendererContext> newContext = m_object.CreateContext<std::remove_reference<Renderer>::type>();

				return m_creator.Create(std::move(newContext));
			}


			System m_object;
			Renderer m_creator;
		};

		std::shared_ptr<RendererCreatorInterface> m_object;
	};
}