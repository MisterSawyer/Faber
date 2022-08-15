#pragma once
#include <memory>

#include "render-frame.h"
#include "color/color.h"

namespace fbr
{
	class IRenderer
	{
	public:
		IRenderer() = default;

		virtual ~IRenderer() = default;

		virtual bool Init() = 0;
		virtual void Render() = 0;
		virtual IRenderFrame * GetFrame() = 0;

		void Clear();
	private:
	};
}