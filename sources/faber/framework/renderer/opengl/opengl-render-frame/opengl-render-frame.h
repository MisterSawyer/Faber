#pragma once
#include <framework/renderer/render-frame/render-frame.h>
namespace fbr::opengl
{
	/*
	* Frame contains information about objects to be drawn
	* Its basically container for data
	*/
	class OpenGLFrame : public fbr::IRenderFrame
	{
	public:
		void Reset() override
		{
		}
	};
}
