#pragma once

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/base_object.hpp>

namespace fbr
{
	class IEngineObject
	{
	public:
		
		virtual std::string GetInfo() = 0;
		virtual ~IEngineObject() = default;
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{}
	};
}