#include <framework-app-listener.h>

void fbr::FrameworkAppListener::RequestClose()
{
	m_framework->CloseCurrentApp();
}