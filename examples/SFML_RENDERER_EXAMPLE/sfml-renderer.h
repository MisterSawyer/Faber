#pragma once
#include <unordered_set>
#include "../../sources/framework/renderer/frame/render-frame.h"
#include "../../sources/framework/renderer/renderer.h"
#include "sfml-context.h"

#include <SFML-2.5.1/include/SFML/Graphics.hpp>

// klatka renderera
struct SFMLFrame : fbr::IRenderFrame
{
	~SFMLFrame() = default;

	void Reset() override
	{
		m_objects.clear();
	}

	std::unordered_set<sf::Drawable*> m_objects;
};

// renderer
struct RendererSFML : fbr::IRenderer
{
	RendererSFML(std::unique_ptr<ContextSFML> context)
	{
		m_context = std::move(context);
	}

	bool Init(fbr::Window* window) override
	{
		// tutaj mozemy np robic dynamiczne klatki itp itd

		return true;
	}

	void Destroy()
	{
		m_context->Destroy();
	}

	void Render()override
	{
		m_context->m_window->clear();

		for (const auto& obj : m_frame.m_objects)
		{
			m_context->m_window->draw(*obj);
		}

		m_context->m_window->display();
	}

	fbr::IRenderFrame* GetFrame() override { return &m_frame; };
private:
	std::unique_ptr<ContextSFML> m_context;
	SFMLFrame m_frame;
};

//Ta fabryka te¿ jest kompletnie niepotrzebna z racji tego ¿e nie SFML w ogóle  nie u¿ywa kontekstu
struct SFMLRendererFactory : public fbr::RendererFactory
{
	using ContextType = ContextSFML;

	std::unique_ptr<fbr::IRenderer> Create(std::unique_ptr<fbr::IRendererContext> context)
	{
		if (dynamic_cast<ContextSFML*>(context.get()) == nullptr)
		{
			return nullptr;
		}

		std::unique_ptr<ContextSFML> upcastContext = std::unique_ptr<ContextSFML>(dynamic_cast<ContextSFML*>(context.release()));

		return std::make_unique<RendererSFML>(std::move(upcastContext));
	}
};


// Concept for checking if its a SFML renderer
template<class T>
concept IsSFMLRendererFactory = fbr::IsRendererFactory<T> && std::is_base_of<SFMLRendererFactory, T>::value;