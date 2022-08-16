#pragma once
#include "color/color.h"

namespace fbr
{
	class IRenderFrame
	{
	public:
		virtual ~IRenderFrame() = default;
		virtual void Reset() = 0;

		const Color<float> & GetColor() const;

		void SetColor(const Color<float>& color);
		void SetColor(Color<float> && color);

	private:
		Color<float> m_background;
	};
}