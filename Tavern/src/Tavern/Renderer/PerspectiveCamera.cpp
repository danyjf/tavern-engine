#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Tavern/Renderer/PerspectiveCamera.h"
#include "Tavern/Core/Log.h"

namespace Tavern
{
	PerspectiveCamera::PerspectiveCamera()
	{
		ComputeViewMatrix();
		ComputeProjectionMatrix();
	}

	PerspectiveCamera::~PerspectiveCamera()
	{
	}

	const glm::mat4& PerspectiveCamera::GetViewMatrix() const
	{
		return m_ViewMatrix;
	}

	const glm::mat4& PerspectiveCamera::GetProjectionMatrix() const
	{
		return m_ProjectionMatrix;
	}

	const glm::mat4 PerspectiveCamera::GetViewProjectionMatrix() const
	{
		return m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::CalculateDirectionVectors()
	{
		m_Front.x = cos(glm::radians(m_Rotation.y)) * cos(glm::radians(m_Rotation.x));
		m_Front.y = sin(glm::radians(m_Rotation.x));
		m_Front.z = sin(glm::radians(m_Rotation.y)) * cos(glm::radians(m_Rotation.x));
		m_Front = glm::normalize(m_Front);
		m_Right = glm::normalize(glm::cross(m_Front, glm::vec3(0.0f, 1.0f, 0.0f)));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}

	void PerspectiveCamera::ComputeViewMatrix()
	{
		CalculateDirectionVectors();
		TAVERN_ENGINE_INFO("Position({}, {}, {})", m_Position.x, m_Position.y, m_Position.z);
		TAVERN_ENGINE_INFO("Front({}, {}, {})", m_Front.x, m_Front.y, m_Front.z);
		TAVERN_ENGINE_INFO("Up({}, {}, {})", m_Up.x, m_Up.y, m_Up.z);
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	void PerspectiveCamera::ComputeProjectionMatrix()
	{
		m_ProjectionMatrix = glm::perspective(
			glm::radians(m_FOV),
			m_ViewportWidth / m_ViewportWidth,
			m_NearClipPlane,
			m_FarClipPlane
		);
	}

	void PerspectiveCamera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
	}

	void PerspectiveCamera::SetRotation(const glm::vec3& rotation)
	{
		m_Rotation = rotation;
	}

	void PerspectiveCamera::SetScale(const glm::vec3& scale)
	{
		m_Scale = scale;
	}
}
