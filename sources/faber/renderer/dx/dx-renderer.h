#pragma once

#include <faber/renderer/renderer.h>
#include <faber/renderer/dx/dx-renderer-context/dx-renderer-context.h>

namespace fbr::dx 
{
	struct DXFrame : fbr::IRenderFrame
	{
		void Reset() override
		{
		}
	};

	class DXRenderer : public fbr::IRenderer
	{
	public:

		DXRenderer(std::unique_ptr<ContextDirectX11> context)
		{
			m_context = std::move(context);
		}

		bool Init(fbr::Window* window) override
		{
			m_frame = std::make_unique<DXFrame>();

			return true;
		}

		void Destroy() override
		{
			m_context->Destroy();
		}

		void Render()
		{
			m_context->Clear();
			
			m_context->SetBackgroundColor(m_frame->GetColor());

			m_context->SwapBuffer();
		}

		IRenderFrame* GetFrame() override
		{
			return  m_frame.get();
		}
	private:
		std::unique_ptr<DXFrame> m_frame;

		std::unique_ptr<ContextDirectX11> m_context;

	};



	/*
	* Used by system factories when performing type erasue construction
	*/
	struct DX11RendererFactory : public RendererFactory
	{
		std::unique_ptr<fbr::IRenderer> Create(std::unique_ptr<fbr::IRendererContext> context)
		{
			if (dynamic_cast<ContextDirectX11*>(context.get()) == nullptr)
			{
				//wrong context type O.o
				//static_assert(false);

				return nullptr;
			}

			// jakos nie jestem w 100% do tego przekonany ale sprawdzilismy wczesniej czy upcasting konwersja jest mozliwa
			std::unique_ptr<ContextDirectX11> upcastContext = std::unique_ptr<ContextDirectX11>(dynamic_cast<ContextDirectX11*>(context.release()));

			return std::make_unique<DXRenderer>(std::move(upcastContext));
		}
	};


	// Concept for checking if its a dx renderer
	template<class T>
	concept IsDX11RendererFactory = IsRendererFactory<T> && std::is_base_of<DX11RendererFactory, T>::value;

}