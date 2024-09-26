#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Tavern/Components/CameraComponent.h"
#include "Tavern/Entity.h"

namespace Tavern
{
	CameraComponent::CameraComponent(Entity* owner, float FOV, float viewportWidth, float viewportHeight, float nearClipPlane, float farClipPlane)
		: Component(owner),
		  m_FOV(FOV),
		  m_ViewportWidth(viewportWidth),
		  m_ViewportHeight(viewportHeight),
		  m_NearClipPlane(nearClipPlane),
		  m_FarClipPlane(farClipPlane)
	{
		m_OwnerTransform = GetOwner()->GetTransformComponent();
		ComputeViewMatrix();
		ComputeProjectionMatrix();
	}

	const glm::mat4& CameraComponent::GetViewMatrix() const
	{
		return m_ViewMatrix;
	}

	const glm::mat4& CameraComponent::GetProjectionMatrix() const
	{
		return m_ProjectionMatrix;
	}

	const glm::mat4 CameraComponent::GetViewProjectionMatrix() const
	{
		return m_ProjectionMatrix * m_ViewMatrix;
	}

	void CameraComponent::CalculateDirectionVectors()
	{
		const glm::vec3& rotation = m_OwnerTransform->GetRotation();
		m_Front.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
		m_Front.y = sin(glm::radians(rotation.x));
		m_Front.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
		m_Front = glm::normalize(m_Front);
		m_Right = glm::normalize(glm::cross(m_Front, glm::vec3(0.0f, 1.0f, 0.0f)));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}

	void CameraComponent::ComputeViewMatrix()
	{
		CalculateDirectionVectors();
		m_ViewMatrix = glm::lookAt(m_OwnerTransform->GetPosition(), m_OwnerTransform->GetPosition() + m_Front, m_Up);
	}

	void CameraComponent::ComputeProjectionMatrix()
	{
		m_ProjectionMatrix = glm::perspective(
			glm::radians(m_FOV),
			m_ViewportWidth / m_ViewportWidth,
			m_NearClipPlane,
			m_FarClipPlane
		);
	}
}
