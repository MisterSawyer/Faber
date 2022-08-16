#pragma once
#include "../../renderer-context/renderer-context.h"

namespace fbr::dx
{
	template<class T>
	void safeRelease(T** object)
	{
		if (*object != nullptr)
		{
			(*object)->Release();
			*object = nullptr;
		}
	}

	class ContextDirectX11 : public IRendererContext
	{
	public:
		virtual void SwapBuffer() = 0;
	private:
		
	};
}