#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Tavern/Components/Camera.h"
#include "Tavern/Entity.h"

namespace Tavern
{
	Camera::Camera(Entity* owner, float FOV, float viewportWidth, float viewportHeight, float nearClipPlane, float farClipPlane)
		: Component(owner),
		  m_FOV(FOV),
		  m_ViewportWidth(viewportWidth),
		  m_ViewportHeight(viewportHeight),
		  m_NearClipPlane(nearClipPlane),
		  m_FarClipPlane(farClipPlane)
	{
		m_OwnerTransform = GetOwner()->GetTransform();
		ComputeViewMatrix();
		ComputeProjectionMatrix();
	}

	Camera::~Camera()
	{
	}

	const glm::mat4& Camera::GetViewMatrix() const
	{
		return m_ViewMatrix;
	}

	const glm::mat4& Camera::GetProjectionMatrix() const
	{
		return m_ProjectionMatrix;
	}

	const glm::mat4 Camera::GetViewProjectionMatrix() const
	{
		return m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::CalculateDirectionVectors()
	{
		const glm::vec3& rotation = m_OwnerTransform->GetRotation();
		m_Front.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
		m_Front.y = sin(glm::radians(rotation.x));
		m_Front.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
		m_Front = glm::normalize(m_Front);
		m_Right = glm::normalize(glm::cross(m_Front, glm::vec3(0.0f, 1.0f, 0.0f)));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}

	void Camera::ComputeViewMatrix()
	{
		CalculateDirectionVectors();
		m_ViewMatrix = glm::lookAt(m_OwnerTransform->GetPosition(), m_OwnerTransform->GetPosition() + m_Front, m_Up);
	}

	void Camera::ComputeProjectionMatrix()
	{
		m_ProjectionMatrix = glm::perspective(
			glm::radians(m_FOV),
			m_ViewportWidth / m_ViewportWidth,
			m_NearClipPlane,
			m_FarClipPlane
		);
	}
}
