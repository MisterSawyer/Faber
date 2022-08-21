#include <faber/framework.h>
#include <framework-listener/framework-listener.h>

namespace fbr
{
	void IFrameworkListener::ForwardInput(InputEvent inputEvent) const
	{
		m_framework->BufferInput(std::move(inputEvent));
	}
}