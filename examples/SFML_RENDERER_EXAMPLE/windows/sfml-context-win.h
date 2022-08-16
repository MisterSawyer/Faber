#pragma once

#define NOMINMAX
#include <Windows.h>

#include "../sfml-context.h"

struct ContextSFMLWin : ContextSFML
{
	//windows specyfic
	ContextSFMLWin(HWND instance)
	{
		m_window = std::make_unique<sf::RenderWindow>(instance);
	}
};