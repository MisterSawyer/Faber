#pragma once
#include "render-frame.h"
#include "../window/window.h"
#include <memory>

namespace fbr
{
	class IRenderer
	{
	public:
		virtual ~IRenderer() = default;

		virtual bool Init(Window * window) = 0;
		virtual void Render() = 0;
		
		inline void Clear() { m_frame->Reset(); }
		inline IRenderFrame* GetFrame() { return m_frame.get(); }
	protected:
		std::unique_ptr<IRenderFrame> m_frame;
	};
}