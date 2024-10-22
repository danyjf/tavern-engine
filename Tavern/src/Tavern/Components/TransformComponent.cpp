#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Tavern/Components/TransformComponent.h"
#include "Tavern/Core/Engine.h"
#include "Tavern/Scene/Entity.h"

namespace Tavern
{
	TransformComponent::TransformComponent(Engine& engine, Entity* owner)
		: Component(engine, owner),
		  m_LocalModelMatrix(1.0f),
		  m_ModelMatrix(1.0f),
		  m_Position(0.0f),
		  m_Rotation(0.0f),
		  m_Scale(1.0f)
	{
		ComputeLocalModelMatrix();
		ComputeModelMatrix();
		CalculateDirectionVectors();
	}

	const glm::vec3& TransformComponent::GetPosition() const
	{
		return m_Position;
	}

	void TransformComponent::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		ComputeLocalModelMatrix();
		ComputeModelMatrix();
	}

	const glm::vec3& TransformComponent::GetRotation() const
	{
		return m_Rotation;
	}

	void TransformComponent::SetRotation(const glm::vec3& rotation)
	{
		m_Rotation = rotation;
		CalculateDirectionVectors();
		ComputeLocalModelMatrix();
		ComputeModelMatrix();
	}

	const glm::vec3& TransformComponent::GetScale() const
	{
		return m_Scale;
	}

	void TransformComponent::SetScale(const glm::vec3& scale)
	{
		m_Scale = scale;
		ComputeLocalModelMatrix();
		ComputeModelMatrix();
	}

	const glm::vec3& TransformComponent::GetFrontDirection() const
	{
		return m_Front;
	}

	const glm::vec3& TransformComponent::GetRightDirection() const
	{
		return m_Right;
	}

	const glm::vec3& TransformComponent::GetUpDirection() const
	{
		return m_Up;
	}

	const glm::mat4& TransformComponent::GetLocalModelMatrix() const
	{
		return m_LocalModelMatrix;
	}

	const glm::mat4& TransformComponent::GetModelMatrix() const
	{
		return m_ModelMatrix;
	}

	void TransformComponent::ComputeLocalModelMatrix()
	{
		m_LocalModelMatrix = glm::mat4(1.0f);

		// Apply translation
		m_LocalModelMatrix = glm::translate(m_LocalModelMatrix, m_Position);

		// Apply rotation ZXY
		m_LocalModelMatrix = glm::rotate(m_LocalModelMatrix, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		m_LocalModelMatrix = glm::rotate(m_LocalModelMatrix, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		m_LocalModelMatrix = glm::rotate(m_LocalModelMatrix, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		// Apply scale
		m_LocalModelMatrix = glm::scale(m_LocalModelMatrix, m_Scale);
	}

	void TransformComponent::ComputeModelMatrix()
	{
		if (GetOwner()->GetParent())
		{
			m_ModelMatrix = GetOwner()->GetParent()->GetTransform()->GetModelMatrix() * m_LocalModelMatrix;
		}
		else
		{
			m_ModelMatrix = m_LocalModelMatrix;
		}

		for (auto& pair : GetOwner()->GetChildren())
		{
			pair.second->GetTransform()->ComputeModelMatrix();
		}
	}

	void TransformComponent::CalculateDirectionVectors()
	{
		const glm::vec3& rotation = GetRotation();
		m_Front.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
		m_Front.y = sin(glm::radians(rotation.x));
		m_Front.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
		m_Front = glm::normalize(m_Front);
		m_Right = glm::normalize(glm::cross(m_Front, glm::vec3(0.0f, 1.0f, 0.0f)));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}
}
