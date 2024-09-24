#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Tavern/Components/Transform.h"

namespace Tavern
{
	Transform::Transform()
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		ComputeModelMatrix();
	}

	void Transform::SetRotation(const glm::vec3& rotation)
	{
		m_Rotation = rotation;
		ComputeModelMatrix();
	}

	void Transform::SetScale(const glm::vec3& scale)
	{
		m_Scale = scale;
		ComputeModelMatrix();
	}

	void Transform::ComputeModelMatrix()
	{
		m_ModelMatrix = glm::mat4(1.0f);

		// Apply translation
		m_ModelMatrix = glm::translate(m_ModelMatrix, m_Position);

		// Apply rotation ZXY
		m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		// Apply scale
		m_ModelMatrix = glm::scale(m_ModelMatrix, m_Scale);
	}
}
