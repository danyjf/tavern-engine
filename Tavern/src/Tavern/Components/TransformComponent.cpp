#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Tavern/Components/TransformComponent.h"

namespace Tavern
{
	TransformComponent::TransformComponent(Entity* owner)
		: Component(owner), m_ModelMatrix(1.0f), m_Position(0.0f), m_Rotation(0.0f), m_Scale(1.0f)
	{
	}

	TransformComponent::~TransformComponent()
	{
	}

	const glm::vec3& TransformComponent::GetPosition() const
	{
		return m_Position;
	}

	void TransformComponent::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		ComputeModelMatrix();
	}

	const glm::vec3& TransformComponent::GetRotation() const
	{
		return m_Rotation;
	}

	void TransformComponent::SetRotation(const glm::vec3& rotation)
	{
		m_Rotation = rotation;
		ComputeModelMatrix();
	}

	const glm::vec3& TransformComponent::GetScale() const
	{
		return m_Scale;
	}

	void TransformComponent::SetScale(const glm::vec3& scale)
	{
		m_Scale = scale;
		ComputeModelMatrix();
	}

	const glm::mat4& TransformComponent::GetModelMatrix() const
	{
		return m_ModelMatrix;
	}

	void TransformComponent::ComputeModelMatrix()
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
