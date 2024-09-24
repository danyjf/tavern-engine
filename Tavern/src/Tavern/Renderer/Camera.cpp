#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Tavern/Renderer/Camera.h"

namespace Tavern
{
	Camera::Camera(float FOV, float viewportWidth, float viewportHeight, float nearClipPlane, float farClipPlane)
		: m_FOV(FOV),
		  m_ViewportWidth(viewportWidth),
		  m_ViewportHeight(viewportHeight),
		  m_NearClipPlane(nearClipPlane),
		  m_FarClipPlane(farClipPlane)
	{
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
		m_Front.x = cos(glm::radians(m_Rotation.y)) * cos(glm::radians(m_Rotation.x));
		m_Front.y = sin(glm::radians(m_Rotation.x));
		m_Front.z = sin(glm::radians(m_Rotation.y)) * cos(glm::radians(m_Rotation.x));
		m_Front = glm::normalize(m_Front);
		m_Right = glm::normalize(glm::cross(m_Front, glm::vec3(0.0f, 1.0f, 0.0f)));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}

	void Camera::ComputeViewMatrix()
	{
		CalculateDirectionVectors();
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
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

	void Camera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
	}

	void Camera::SetRotation(const glm::vec3& rotation)
	{
		m_Rotation = rotation;
	}

	void Camera::SetScale(const glm::vec3& scale)
	{
		m_Scale = scale;
	}
}
