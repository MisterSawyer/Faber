#pragma once

namespace fbr
{
	class IRenderFrame
	{
	public:
		virtual ~IRenderFrame() = default;
		virtual void Reset() = 0;
	};
}