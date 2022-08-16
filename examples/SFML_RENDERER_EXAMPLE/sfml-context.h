#pragma once
#include "../../sources/framework/renderer/renderer-context/renderer-context.h"

#include <SFML/Graphics/RenderWindow.hpp>

// ========================================================================================================================================
//jako ¿e SFML nie potrzebuje kontekstu który bedzie sie zmienia³ w zaleznosci czy Windows / Linux to nie musimy pisac tego wszystkiego
// ale mogê pokazaæ jakby by³o jakby trzeba by³o
// --- zobacz: ---
// renderer-context.h
// opengl-renderer-context.h
// opengl-renderer-context-windows.h
// 
// potem musimy jeszcze zarjestrowaæ te konteksty w odpowiednich fabrykach
// zobacz: 
// WindowsSystemRendererContextFactory w windows-objects-factory.h
//---
// w tym przypadku mozemy potraktowac kontekst jako sf::RenderWindow

struct ContextSFML : public fbr::IRendererContext
{
	//te wszystkie funkcje trzeba nadpisaæ
	// nie musz¹ byæ koniecznie tutaj nadpisane - mog¹ byæ np w ContextSFMLWin czy ContextSFMLLin
	void SetBackgroundColor(const fbr::Color<float>& color) {};
	bool Good() const { return true; };

	void SwitchDepthTest(bool enable) {};
	void SwitchStencilTest(bool enable) {};

	void SetDepthClearValue(double depth) {};
	void SetStencilClearValue(int stencil) {};

	void Clear() {};

	//--------
	std::unique_ptr<sf::RenderWindow> m_window;
protected:
	bool Create() { return true; };
	void Destroy() {};

	void SetAsRenderTarget() {};
	void SwapBuffer() {};
	bool MakeCurrent() const { return true; };
};
