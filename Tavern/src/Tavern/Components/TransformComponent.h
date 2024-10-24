#pragma once

#include <glm/glm.hpp>

#include "Tavern/Core/Core.h"
#include "Tavern/Components/Component.h"

namespace Tavern
{
	class Engine;

	// TODO: Add function for setting the local and global position, rotation, scale
	// Currently there's only local
	class TAVERN_API TransformComponent : public Component
	{
	public:
		TransformComponent(Engine& engine, Entity* owner);
		virtual ~TransformComponent() = default;

		const glm::vec3& GetPosition() const;
		void SetPosition(const glm::vec3& position);

		const glm::vec3& GetRotation() const;
		void SetRotation(const glm::vec3& rotation);

		const glm::vec3& GetScale() const;
		void SetScale(const glm::vec3& scale);

		const glm::vec3& GetFrontDirection() const;
		const glm::vec3& GetRightDirection() const;
		const glm::vec3& GetUpDirection() const;

		const glm::mat4& GetLocalModelMatrix() const;
		const glm::mat4& GetModelMatrix() const;

	private:
		glm::mat4 m_LocalModelMatrix = glm::mat4(1.0f);
		glm::mat4 m_ModelMatrix = glm::mat4(1.0f);

		glm::vec3 m_Position = glm::vec3(0.0f);
		glm::vec3 m_Rotation = glm::vec3(0.0f);
		glm::vec3 m_Scale = glm::vec3(1.0f);

		glm::vec3 m_Front = glm::vec3(0.0f);
		glm::vec3 m_Right = glm::vec3(0.0f);
		glm::vec3 m_Up = glm::vec3(0.0f);

		void ComputeLocalModelMatrix();
		void ComputeModelMatrix();
		void CalculateDirectionVectors();
	};
}
