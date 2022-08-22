#pragma once
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <glm/glm.hpp>
#include <functional>

namespace fbr
{
	class Transformable 
	{
	public:
		Transformable();
		explicit Transformable(glm::vec3 position);
		explicit Transformable(float pos_x, float pos_y, float pos_z);

		Transformable(const Transformable&);
		Transformable(Transformable&&)noexcept;
		Transformable& operator=(const Transformable&);
		Transformable& operator=(Transformable&&)noexcept;

		Transformable operator + (const Transformable&);

		virtual ~Transformable() = default;

		void SetPosition(glm::vec3 position);
		void SetPosition(float x, float y, float z);
		void SetPositionX(float x);
		void SetPositionY(float y);
		void SetPositionZ(float z);

		void SetRotation(glm::vec3 rotation);
		void SetRotation(float x, float y, float z);
		void SetRotationX(float x);
		void SetRotationY(float y);
		void SetRotationZ(float z);

		void SetScale(glm::vec3 scale);
		void SetScale(float x, float y, float z);
		void SetScaleX(float x);
		void SetScaleY(float y);
		void SetScaleZ(float z);

		glm::vec3 GetPosition() const;
		glm::vec3 GetRotation() const;
		glm::vec3 GetScale() const;

		float GetPositionX() const;
		float GetPositionY() const;
		float GetPositionZ() const;

		float GetRotationX() const;
		float GetRotationY() const;
		float GetRotationZ() const;

		float GetScaleX() const;
		float GetScaleY() const;
		float GetScaleZ() const;

		glm::mat4 GetMatrix();


		bool RecentlyUpdated()const;
		bool IsScheduledToUpdate() const;
		void SetUpdateCallback(std::function<void()> callback);

	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			m_toUpdate = true;
			m_recentlyUpdated = false;

			ar& m_position;
			ar& m_rotation;
			ar& m_scale;
			ar& m_toUpdate;
			ar& m_recentlyUpdated;
			//TODO
			//ar& m_updateCallback;
		}

		void Update();

		glm::mat4 m_matrix;
		glm::vec3 m_position, m_rotation, m_scale;
		bool m_toUpdate;

		bool m_recentlyUpdated;
		std::function<void()> m_updateCallback;
	};
}

namespace boost {
	namespace serialization {

		template<class Archive>
		void serialize(Archive& ar, glm::vec2 & vec, const unsigned int version)
		{
			ar& vec.g;
			ar& vec.r;
			ar& vec.s;
			ar& vec.t;
			ar& vec.x;
			ar& vec.y;
		}

		template<class Archive>
		void serialize(Archive& ar, glm::vec3 & vec, const unsigned int version)
		{
			ar& vec.b;
			ar& vec.g;
			ar& vec.p;
			ar& vec.r;
			ar& vec.s;
			ar& vec.t;
			ar& vec.x;
			ar& vec.y;
			ar& vec.z;
		}

	} // namespace serialization
} // namespace boost