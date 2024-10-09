#pragma once

#include <glm/glm.hpp>

#include "Tavern/Components/Component.h"
#include "Tavern/Components/TransformComponent.h"
#include "Tavern/Core/Core.h"

namespace Tavern
{
	class Entity;
	class Engine;

	class TAVERN_API CameraComponent : public Component
	{
	public:
		CameraComponent() = default;
		CameraComponent(
			Engine* engine,
			Entity* owner,
			float FOV = 45.0f,
			float viewportWidth = 800.0f,
			float viewportHeight = 600.0f,
			float nearClipPlane = 0.1f,
			float farClipPlane = 100.0f
		);

		void SetFOV(float FOV);

		const glm::mat4& GetViewMatrix() const;
		const glm::mat4& GetProjectionMatrix() const;
		const glm::mat4 GetViewProjectionMatrix() const;

		void ComputeViewMatrix();
		void ComputeProjectionMatrix();

	private:
		TransformComponent* m_OwnerTransform;

		float m_FOV;
		float m_ViewportWidth;
		float m_ViewportHeight;
		float m_NearClipPlane;
		float m_FarClipPlane;

		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
	};
}
