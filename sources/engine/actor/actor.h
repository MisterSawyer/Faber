#pragma once
#include "../transformable/transformable.h"
#include "../engine-object/engine-object.h"

#include <set>

namespace fbr
{
	/**
	* Represents interface for objects that can be placed into a level
	*/
	class IActor : public virtual IEngineObject,  public virtual Transformable
	{
	public:
		IActor();

		virtual ~IActor() = default;
		virtual bool OnInit() = 0;
		virtual void OnTick(const float timeDelta) = 0;
		virtual void OnDestroy() = 0;

		void RequestDestroy();
		void SetParent(IActor* parent);
		const bool Destroyed() const;
		const bool Initialized() const;

		Transformable GetRelativeTransform();

		std::string GetInfo() override;
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar& boost::serialization::base_object<IEngineObject>(*this);
			ar& boost::serialization::base_object<Transformable>(*this);

			ar& m_initialized;
			ar& m_destroyed;
			ar& m_parent;
			ar& m_childreen;
		}

		bool m_initialized;
		bool m_destroyed;

		IActor * m_parent;
		std::set<IActor*> m_childreen;
	};
}