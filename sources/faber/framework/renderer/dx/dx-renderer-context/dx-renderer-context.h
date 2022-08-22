#pragma once

#include <framework/renderer/renderer-context/renderer-context.h>

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
		virtual void Destroy() = 0;

	private:
		
	};
}