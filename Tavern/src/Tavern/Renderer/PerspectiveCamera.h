#pragma once

#include <glm/glm.hpp>

namespace Tavern
{
	class PerspectiveCamera
	{
	public:
		PerspectiveCamera();
		~PerspectiveCamera();

		const glm::mat4& GetViewMatrix() const;
		const glm::mat4& GetProjectionMatrix() const;
		const glm::mat4 GetViewProjectionMatrix() const;

		void SetPosition(const glm::vec3& position);
		void SetRotation(const glm::vec3& rotation);
		void SetScale(const glm::vec3& scale);

	private:
		float m_FOV = 45.0f;
		float m_ViewportWidth = 800.0f;
		float m_ViewportHeight = 600.0f;
		float m_NearClipPlane = 0.1f;
		float m_FarClipPlane = 100.0f;

		glm::vec3 m_Position = { 0.0f, 0.0f, 3.0f };
		glm::vec3 m_Rotation = { 0.0f, -90.0f, 0.0f };
		glm::vec3 m_Scale = { 1.0f, 1.0f, 1.0f };

		glm::vec3 m_Front;
		glm::vec3 m_Right;
		glm::vec3 m_Up;

		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;

		void CalculateDirectionVectors();
		void ComputeViewMatrix();
		void ComputeProjectionMatrix();
	};
}
