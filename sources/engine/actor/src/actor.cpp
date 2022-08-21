#include <engine/actor/actor.h>
#include <framework/logger/logger.h>

namespace fbr
{
	IActor::IActor()
	{
		m_parent = nullptr;
		m_initialized = false;
		m_destroyed = false;
	}

	void IActor::SetParent(IActor* parent)
	{
		m_parent = parent;
		m_parent->m_childreen.insert(this);
	}

	void IActor::RequestDestroy()
	{
		if (m_destroyed)
		{
			LOG_WAR("Actor already requested to destroy");
			return;
		}

		for (auto & child : m_childreen)
		{
			RequestDestroy();
		}

		OnDestroy();
		m_destroyed = true;
	}

	const bool IActor::Destroyed() const
	{
		return m_destroyed;
	}

	const bool IActor::Initialized() const
	{
		return m_initialized;
	}

	Transformable IActor::GetRelativeTransform()
	{
		if (m_parent == nullptr)return static_cast<Transformable>(*this);

		return static_cast<Transformable>(*this) + m_parent->GetRelativeTransform();
	}

	std::string IActor::GetInfo()
	{
		std::stringstream ss;
		ss << typeid(*this).name()<<"\n";
		ss << GETINFO(m_initialized, m_destroyed, m_parent);
		for (const auto& child : m_childreen)
		{
			ss << GETINFO(child->GetInfo());
		}
		return ss.str();
	}

}