#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Tavern/Components/CameraComponent.h"
#include "Tavern/Core/Engine.h"
#include "Tavern/Scene/Entity.h"

namespace Tavern
{
	CameraComponent::CameraComponent(Engine& engine, Entity* owner)
		: Component(engine, owner),
		  m_OwnerTransform(GetOwner()->GetTransform())
	{
		ComputeViewMatrix();
		ComputeProjectionMatrix();
	}

	void CameraComponent::Serialize()
	{

	}

	void CameraComponent::SetFOV(float FOV)
	{
		m_FOV = FOV;
		ComputeProjectionMatrix();
	}
	
	void CameraComponent::SetViewportSize(float width, float height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;
		ComputeProjectionMatrix();
	}

	const glm::vec2 CameraComponent::GetViewportSize() const
	{
		return glm::vec2(m_ViewportWidth, m_ViewportHeight);
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
		m_ViewMatrix = glm::lookAt(m_OwnerTransform->GetLocalPosition(), m_OwnerTransform->GetLocalPosition() + m_OwnerTransform->GetFrontDirection(), m_OwnerTransform->GetUpDirection());
	}

	void CameraComponent::ComputeProjectionMatrix()
	{
		m_ProjectionMatrix = glm::perspective(
			glm::radians(m_FOV),
			m_ViewportWidth / m_ViewportHeight,
			m_NearClipPlane,
			m_FarClipPlane
		);
	}
}
