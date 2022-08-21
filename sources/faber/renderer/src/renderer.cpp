#include <faber/renderer/renderer.h>

void fbr::IRenderer::Clear()
{
	auto frame = GetFrame();
	if (frame == nullptr)return;

	frame->Reset();
}
