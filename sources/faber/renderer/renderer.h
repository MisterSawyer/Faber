#pragma once
#include <memory>

#include <faber/window/window.h>

#include <faber/renderer/renderer-context/renderer-context.h>
#include <faber/renderer/render-frame/render-frame.h>
#include <faber/renderer/color/color.h>

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

		virtual void Destroy() = 0;

	private:
	};

	struct RendererFactory
	{
		virtual std::unique_ptr<fbr::IRenderer> Create(std::unique_ptr<fbr::IRendererContext> context) = 0;
	};


	template <class T>
	concept IsRendererFactory = std::derived_from<T, RendererFactory>;
}