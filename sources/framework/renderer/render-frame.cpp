#include "render-frame.h"

const fbr::Color<float>& fbr::IRenderFrame::GetColor() const
{
	return m_background;
}

void fbr::IRenderFrame::SetColor(const Color<float>& color)
{
	m_background = color;
}

void fbr::IRenderFrame::SetColor(Color<float>&& color)
{
	m_background = std::move(color);
}
