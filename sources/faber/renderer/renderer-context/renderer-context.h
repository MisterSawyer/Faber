#pragma once

#include <faber/renderer/color/color.h>
#include <faber/window/window.h>

namespace fbr
{
	/*
	* Context is the state of the rendering engine. It has no information about the objects to be drawn.
	* Renderer is a combination of Context and Frame(data to draw)
	*/
	class IRendererContext
	{
	public:
		virtual ~IRendererContext() = default;

		virtual void SetBackgroundColor(const Color<float> & color) = 0;
		virtual bool Good() const = 0;

		virtual void SwitchDepthTest(bool enable) = 0;
		virtual void SwitchStencilTest(bool enable) = 0;

		virtual void SetDepthClearValue(double depth) = 0;
		virtual void SetStencilClearValue(int stencil) = 0;

		virtual void Clear() = 0;

	protected:
		virtual bool Create() = 0;
		virtual void Destroy() = 0;

		virtual void SetAsRenderTarget() = 0;
		virtual void SwapBuffer() = 0;
		virtual bool MakeCurrent() const = 0;

	};
}