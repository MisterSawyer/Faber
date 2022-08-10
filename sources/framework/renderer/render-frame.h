#pragma once

namespace fbr
{
	class IRenderFrame
	{
	public:
		virtual ~IRenderFrame() {};
		virtual void Reset() = 0;
	};
}