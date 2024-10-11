#pragma once

#include <glm/glm.hpp>

#include "Tavern/Components/BaseComponent.h"
#include "Tavern/Components/TransformComponent.h"
#include "Tavern/Core/Core.h"

namespace Tavern
{
	class Entity;
	class Engine;

	class TAVERN_API CameraComponent : public BaseComponent
	{
	public:
		CameraComponent(Engine* engine, Entity* owner);

		void SetFOV(float FOV);

		const glm::mat4& GetViewMatrix() const;
		const glm::mat4& GetProjectionMatrix() const;
		const glm::mat4 GetViewProjectionMatrix() const;

		void ComputeViewMatrix();
		void ComputeProjectionMatrix();

	private:
		TransformComponent* m_OwnerTransform = nullptr;

		float m_FOV = 45.0f;
		float m_ViewportWidth = 800.0f;
		float m_ViewportHeight = 600.0f;
		float m_NearClipPlane = 0.1f;
		float m_FarClipPlane = 100.0f;

		glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
	};
}
