#include <faber/app/app.h>


// defining it in .h cause compiler to generate destructor to incloplete type std::unique_ptr<FrameworkAppListener>
fbr::IApp::IApp() = default;
fbr::IApp::~IApp() = default;

void fbr::IApp::RequestExit()
{
	if (m_listener)m_listener->RequestClose();
}

void fbr::IApp::SetListener(std::unique_ptr<FrameworkAppListener> listener)
{
	m_listener = std::move(listener);
}

fbr::FrameworkAppListener* fbr::IApp::GetListener()
{
	return m_listener.get();
}
