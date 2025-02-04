#include <nlohmann/json.hpp>
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
		  m_LocalPosition(0.0f),
		  m_LocalEulerRotation(0.0f),
		  m_LocalScale(1.0f)
	{
		ComputeLocalModelMatrix();
		ComputeModelMatrix();
	}
	
	nlohmann::json TransformComponent::ToJson()
	{
		nlohmann::json json;
		json["transform"]["position"] = { m_Position.x, m_Position.y, m_Position.z };
		json["transform"]["eulerRotation"] = {m_EulerRotation.x, m_EulerRotation.y, m_EulerRotation.z};
		json["transform"]["scale"] = {m_Scale.x, m_Scale.y, m_Scale.z};
		return json;
	}

	void TransformComponent::FromJson(const nlohmann::json& data)
	{
		SetPosition(glm::vec3(
			data["position"][0],
			data["position"][1],
			data["position"][2]
		));
		SetEulerRotation(glm::vec3(
			data["eulerRotation"][0],
			data["eulerRotation"][1],
			data["eulerRotation"][2]
		));
		SetScale(glm::vec3(
			data["scale"][0],
			data["scale"][1],
			data["scale"][2]
		));
	}

	const glm::vec3& TransformComponent::GetLocalPosition() const
	{
		return m_LocalPosition;
	}

	void TransformComponent::SetLocalPosition(const glm::vec3& localPosition)
	{
		m_LocalPosition = localPosition;

		ComputeLocalModelMatrix();
		ComputeModelMatrix();
	}

	const glm::vec3& TransformComponent::GetLocalEulerRotation() const
	{
		return m_LocalEulerRotation;
	}

	void TransformComponent::SetLocalEulerRotation(const glm::vec3& localEulerRotation)
	{
		m_LocalEulerRotation = localEulerRotation;

		ComputeLocalModelMatrix();
		ComputeModelMatrix();
	}

	const glm::vec3& TransformComponent::GetLocalScale() const
	{
		return m_LocalScale;
	}

	void TransformComponent::SetLocalScale(const glm::vec3& localScale)
	{
		m_LocalScale = localScale;

		ComputeLocalModelMatrix();
		ComputeModelMatrix();
	}

	const glm::vec3& TransformComponent::GetPosition()
	{
		return m_Position;
	}

	void TransformComponent::SetPosition(const glm::vec3& position)
	{
		if (GetOwner()->GetParent())
		{
			TransformComponent* parentTransform = GetOwner()->GetParent()->GetTransform();
			m_LocalPosition = position - parentTransform->GetPosition();
		}
		else
		{
			m_LocalPosition = position;
		}

		ComputeLocalModelMatrix();
		ComputeModelMatrix();
	}

	const glm::vec3& TransformComponent::GetEulerRotation()
	{
		return m_EulerRotation;
	}

	void TransformComponent::SetEulerRotation(const glm::vec3& eulerRotation)
	{
		if (GetOwner()->GetParent())
		{
			TransformComponent* parentTransform = GetOwner()->GetParent()->GetTransform();
			m_LocalEulerRotation = eulerRotation - parentTransform->GetEulerRotation();
		}
		else
		{
			m_LocalEulerRotation = eulerRotation;
		}

		ComputeLocalModelMatrix();
		ComputeModelMatrix();
	}

	const glm::vec3& TransformComponent::GetScale()
	{
		return m_Scale;
	}

	void TransformComponent::SetScale(const glm::vec3& scale)
	{
		if (GetOwner()->GetParent())
		{
			TransformComponent* parentTransform = GetOwner()->GetParent()->GetTransform();
			m_LocalScale = scale / parentTransform->GetScale();
		}
		else
		{
			m_LocalScale = scale;
		}

		ComputeLocalModelMatrix();
		ComputeModelMatrix();
	}

	const glm::vec3& TransformComponent::GetLocalFrontDirection() const
	{
		return m_LocalFront;
	}

	const glm::vec3& TransformComponent::GetLocalRightDirection() const
	{
		return m_LocalRight;
	}

	const glm::vec3& TransformComponent::GetLocalUpDirection() const
	{
		return m_LocalUp;
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
		m_LocalModelMatrix = glm::translate(m_LocalModelMatrix, m_LocalPosition);

		// Apply rotation ZXY
		m_LocalModelMatrix = glm::rotate(m_LocalModelMatrix, glm::radians(m_LocalEulerRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		m_LocalModelMatrix = glm::rotate(m_LocalModelMatrix, glm::radians(m_LocalEulerRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		m_LocalModelMatrix = glm::rotate(m_LocalModelMatrix, glm::radians(m_LocalEulerRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		// Apply scale
		m_LocalModelMatrix = glm::scale(m_LocalModelMatrix, m_LocalScale);

		ComputeLocalDirectionVectors();
	}

	void TransformComponent::ComputeModelMatrix()
	{
		if (GetOwner()->GetParent())
		{
			TransformComponent* parentTransform = GetOwner()->GetParent()->GetTransform();
			m_ModelMatrix = parentTransform->GetModelMatrix() * m_LocalModelMatrix;

			m_Position = m_LocalPosition + parentTransform->GetPosition();
			m_EulerRotation = m_LocalEulerRotation + parentTransform->GetEulerRotation();
			m_Scale = m_LocalScale * parentTransform->GetScale();

			ComputeDirectionVectors();
		}
		else
		{
			m_ModelMatrix = m_LocalModelMatrix;

			m_Position = m_LocalPosition;
			m_EulerRotation = m_LocalEulerRotation;
			m_Scale = m_LocalScale;

			m_Front = m_LocalFront;
			m_Right = m_LocalRight;
			m_Up = m_LocalUp;
		}

		for (Entity* child : GetOwner()->GetChildren())
		{
			TransformComponent* childTransform = child->GetTransform();
			childTransform->ComputeModelMatrix();
		}
	}

	void TransformComponent::ComputeLocalDirectionVectors()
	{
		const glm::vec3& eulerRotation = GetLocalEulerRotation();
		m_LocalFront.x = cos(glm::radians(eulerRotation.y)) * cos(glm::radians(eulerRotation.x));
		m_LocalFront.y = sin(glm::radians(eulerRotation.x));
		m_LocalFront.z = sin(glm::radians(eulerRotation.y)) * cos(glm::radians(eulerRotation.x));
		m_LocalFront = glm::normalize(m_LocalFront);
		m_LocalRight = glm::normalize(glm::cross(m_LocalFront, glm::vec3(0.0f, 1.0f, 0.0f)));
		m_LocalUp = glm::normalize(glm::cross(m_LocalRight, m_LocalFront));
	}

	void TransformComponent::ComputeDirectionVectors()
	{
		const glm::vec3& eulerRotation = GetEulerRotation();
		m_Front.x = cos(glm::radians(eulerRotation.y)) * cos(glm::radians(eulerRotation.x));
		m_Front.y = sin(glm::radians(eulerRotation.x));
		m_Front.z = sin(glm::radians(eulerRotation.y)) * cos(glm::radians(eulerRotation.x));
		m_Front = glm::normalize(m_Front);
		m_Right = glm::normalize(glm::cross(m_Front, glm::vec3(0.0f, 1.0f, 0.0f)));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}
}
