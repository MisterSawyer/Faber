#pragma once
#include <memory>
#include "renderer.h"

namespace fbr
{
	class RendererFactory
	{

		std::unique_ptr<IRenderer> MakeRenderer();

	};
}