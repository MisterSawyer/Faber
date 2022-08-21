#pragma once
#include <cstddef>
#include <faber/input/input.h>

namespace fbr
{
	class Framework;

	class IFrameworkListener
	{
	public:
		IFrameworkListener(fbr::Framework* framework) : m_framework(framework) {}

		virtual ~IFrameworkListener() = default;
		void ForwardInput(InputEvent inputEvent) const;
	protected:
		fbr::Framework* m_framework;
	};

}