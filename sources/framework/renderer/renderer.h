#pragma once
#include <memory>

#include "renderer-context/renderer-context.h"
#include "render-frame.h"
#include "color/color.h"

namespace fbr
{
	class IRenderer
	{
	public:
		IRenderer() = default;

		virtual ~IRenderer() = default;

		virtual bool Init(fbr::Window * window) = 0;
		virtual void Render() = 0;
		virtual IRenderFrame * GetFrame() = 0;

		void Clear();
	private:
	};

	struct RendererFactory
	{
		virtual std::unique_ptr<fbr::IRenderer> Create(std::unique_ptr<fbr::IRendererContext> context) = 0;
	};


	template <class T>
	concept IsRendererFactory = std::derived_from<T, RendererFactory>;
}