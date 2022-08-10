#include "transformable.h"
#include "../../framework/logger/logger.h"
#include <glm/gtc/matrix_transform.hpp>

namespace fbr
{
	Transformable::Transformable()
	{
		m_position = glm::vec3(0.0f, 0.0f, 0.0f);
		m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
		m_toUpdate = true;
		Update();
	}

	Transformable::Transformable(glm::vec3 position)
	{
		m_position = position;
		m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
		m_matrix = glm::mat4();
		m_toUpdate = true;
		Update();
	}

	Transformable::Transformable(float pos_x, float pos_y, float pos_z)
	{
		m_position = glm::vec3(pos_x, pos_y, pos_z);
		m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
		m_matrix = glm::mat4();
		m_toUpdate = true;
		Update();
	}

	Transformable::Transformable(const Transformable& other)
	{
		m_position = other.m_position;
		m_rotation = other.m_rotation;
		m_scale = other.m_scale;
		m_matrix = glm::mat4();
		m_toUpdate = true;
		Update();
	}

	Transformable::Transformable(Transformable&& other)noexcept
	{
		m_position = std::move(other.m_position);
		m_rotation = std::move(other.m_rotation);
		m_scale = std::move(other.m_scale);
		m_matrix = glm::mat4();
		m_toUpdate = true;
		Update();
	}

	Transformable& Transformable::operator=(const Transformable& other)
	{
		if (this == &other)
		{
			LOG_WAR("Self assigment");
			return *this;
		}

		m_position = other.m_position;
		m_rotation = other.m_rotation;
		m_scale = other.m_scale;
		m_toUpdate = true;
		Update();

		return *this;
	}

	Transformable& Transformable::operator=(Transformable&& other)noexcept
	{
		if (this == &other)
		{
			LOG_WAR("Self move assigment");
			return *this;
		}
		m_position = std::move(other.m_position);
		m_rotation = std::move(other.m_rotation);
		m_scale = std::move(other.m_scale);
		m_toUpdate = true;
		Update();

		return *this;
	}

	void Transformable::SetPosition(glm::vec3 position)
	{
		this->m_position = position;
		m_toUpdate = true;
	}

	void Transformable::SetPosition(float x, float y, float z)
	{
		this->m_position.x = x;
		this->m_position.y = y;
		this->m_position.z = z;
		m_toUpdate = true;
	}

	void Transformable::SetPositionX(float x)
	{
		this->m_position.x = x;
		m_toUpdate = true;
	}

	void Transformable::SetPositionY(float y)
	{
		this->m_position.y = y;
		m_toUpdate = true;
	}

	void Transformable::SetPositionZ(float z)
	{
		this->m_position.z = z;
		m_toUpdate = true;
	}

	void Transformable::SetRotation(glm::vec3 rotation)
	{
		this->m_rotation = rotation;
		m_toUpdate = true;
	}

	void Transformable::SetRotation(float x, float y, float z)
	{
		this->m_rotation.x = x;
		this->m_rotation.y = y;
		this->m_rotation.z = z;
		m_toUpdate = true;
	}

	void Transformable::SetRotationX(float x)
	{
		this->m_rotation.x = x;
		m_toUpdate = true;
	}

	void Transformable::SetRotationY(float y)
	{
		this->m_rotation.y = y;
		m_toUpdate = true;
	}

	void Transformable::SetRotationZ(float z)
	{
		this->m_rotation.z = z;
		m_toUpdate = true;
	}

	void Transformable::SetScale(glm::vec3 scale)
	{
		this->m_scale = scale;
		m_toUpdate = true;
	}

	void Transformable::SetScale(float x, float y, float z)
	{
		this->m_scale.x = x;
		this->m_scale.y = y;
		this->m_scale.z = z;
		m_toUpdate = true;
	}

	void Transformable::SetScaleX(float x)
	{
		this->m_scale.x = x;
		m_toUpdate = true;
	}

	void Transformable::SetScaleY(float y)
	{
		this->m_scale.y = y;
		m_toUpdate = true;
	}

	void Transformable::SetScaleZ(float z)
	{
		this->m_scale.z = z;
		m_toUpdate = true;
	}

	glm::vec3 Transformable::GetPosition() const
	{
		return this->m_position;
	}

	glm::vec3 Transformable::GetRotation() const
	{
		return this->m_rotation;
	}

	glm::vec3 Transformable::GetScale() const
	{
		return this->m_scale;
	}

	float Transformable::GetPositionX() const
	{
		return this->m_position.x;
	}

	float Transformable::GetPositionY() const
	{
		return this->m_position.y;
	}

	float Transformable::GetPositionZ() const
	{
		return this->m_position.z;
	}

	float Transformable::GetRotationX() const
	{
		return this->m_rotation.x;
	}

	float Transformable::GetRotationY() const
	{
		return this->m_rotation.y;
	}

	float Transformable::GetRotationZ() const
	{
		return this->m_rotation.z;
	}

	float Transformable::GetScaleX() const
	{
		return this->m_scale.x;
	}

	float Transformable::GetScaleY() const
	{
		return this->m_scale.y;
	}

	float Transformable::GetScaleZ() const
	{
		return this->m_scale.z;
	}

	glm::mat4 Transformable::GetMatrix()
	{
		Update();
		return m_matrix;
	}

	void Transformable::Update()
	{
		m_recentlyUpdated = false;
		if (!m_toUpdate)return;
		m_matrix = glm::translate(glm::mat4(), m_position);

		m_matrix = glm::rotate(m_matrix, glm::radians(m_rotation.x), glm::vec3(1.0, 0.0, 0.0));
		m_matrix = glm::rotate(m_matrix, glm::radians(m_rotation.y), glm::vec3(0.0, 1.0, 0.0));
		m_matrix = glm::rotate(m_matrix, glm::radians(m_rotation.z), glm::vec3(0.0, 0.0, 1.0));

		m_matrix = glm::scale(m_matrix, m_scale);
		m_toUpdate = false;
		m_recentlyUpdated = true;

		if (m_updateCallback)m_updateCallback();
	}

	bool Transformable::IsScheduledToUpdate() const
	{
		return m_toUpdate;
	}

	Transformable Transformable::operator + (const Transformable & rhs)
	{
		Transformable sum = *this;

		sum.m_position += rhs.m_position;
		sum.m_rotation += rhs.m_rotation;
		sum.m_scale += rhs.m_scale;

		sum.m_toUpdate = true;
		sum.Update();

		return sum;
	}

	bool Transformable::RecentlyUpdated()const
	{
		return m_recentlyUpdated;
	}

	void Transformable::SetUpdateCallback(std::function<void()> callback)
	{
		m_updateCallback = std::move(callback);
	}

}