#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Tavern/Components/CameraComponent.h"
#include "Tavern/Core/Engine.h"
#include "Tavern/Entity.h"

namespace Tavern
{
	CameraComponent::CameraComponent(Engine* engine, Entity* owner)
		: Component(engine, owner),
		  m_OwnerTransform(GetOwner()->GetTransform())
	{
		ComputeViewMatrix();
		ComputeProjectionMatrix();
	}

	void CameraComponent::SetFOV(float FOV)
	{
		m_FOV = FOV;
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

	void CameraComponent::ComputeViewMatrix()
	{
		m_ViewMatrix = glm::lookAt(m_OwnerTransform->GetPosition(), m_OwnerTransform->GetPosition() + m_OwnerTransform->GetFrontDirection(), m_OwnerTransform->GetUpDirection());
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
