#pragma once

#include <GL/glew.h>

namespace fbr::opengl
{
	enum class SurfaceMask : unsigned int
	{
		COLOR_BUFFER = GL_COLOR_BUFFER_BIT,
		DEPTH_BUFFER = GL_DEPTH_BUFFER_BIT,
		STENCIL_BUFFER = GL_STENCIL_BUFFER_BIT
	};
}

//TODO IFDEF PLATFORM WINDOWS
#define NOMINMAX
#include <Windows.h>

#include <winnt.h>
DEFINE_ENUM_FLAG_OPERATORS(fbr::opengl::SurfaceMask);