#include <framework/framework.h>
#include <framework/framework-listener/framework-listener.h>

namespace fbr
{
	void IFrameworkListener::ForwardInput(InputEvent inputEvent) const
	{
		m_framework->BufferInput(std::move(inputEvent));
	}
}