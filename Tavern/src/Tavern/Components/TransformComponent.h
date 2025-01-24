#pragma once

#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

#include "Tavern/Core/Core.h"
#include "Tavern/Components/Component.h"

namespace Tavern
{
	class Engine;

	class TAVERN_API TransformComponent : public Component
	{
	public:
		TransformComponent(Engine& engine, Entity* owner);
		virtual ~TransformComponent() = default;

		nlohmann::json ToJson() override;
		void FromJson(const nlohmann::json& data) override;

		const glm::vec3& GetLocalPosition() const;
		void SetLocalPosition(const glm::vec3& localPosition);

		const glm::vec3& GetLocalEulerRotation() const;
		void SetLocalEulerRotation(const glm::vec3& localEulerRotation);

		const glm::vec3& GetLocalScale() const;
		void SetLocalScale(const glm::vec3& localScale);

		const glm::vec3& GetPosition();
		void SetPosition(const glm::vec3& position);

		const glm::vec3& GetEulerRotation();
		void SetEulerRotation(const glm::vec3& eulerRotation);

		const glm::vec3& GetScale();
		void SetScale(const glm::vec3& scale);

		const glm::vec3& GetLocalFrontDirection() const;
		const glm::vec3& GetLocalRightDirection() const;
		const glm::vec3& GetLocalUpDirection() const;

		const glm::vec3& GetFrontDirection() const;
		const glm::vec3& GetRightDirection() const;
		const glm::vec3& GetUpDirection() const;

		const glm::mat4& GetLocalModelMatrix() const;
		const glm::mat4& GetModelMatrix() const;

	private:
		glm::mat4 m_LocalModelMatrix = glm::mat4(1.0f);
		glm::mat4 m_ModelMatrix = glm::mat4(1.0f);

		glm::vec3 m_LocalPosition = glm::vec3(0.0f);
		glm::vec3 m_LocalEulerRotation = glm::vec3(0.0f);
		glm::vec3 m_LocalScale = glm::vec3(1.0f);

		glm::vec3 m_Position = glm::vec3(0.0f);
		glm::vec3 m_EulerRotation = glm::vec3(0.0f);
		glm::vec3 m_Scale = glm::vec3(1.0f);

		glm::vec3 m_LocalFront = glm::vec3(0.0f);
		glm::vec3 m_LocalRight = glm::vec3(0.0f);
		glm::vec3 m_LocalUp = glm::vec3(0.0f);

		glm::vec3 m_Front = glm::vec3(0.0f);
		glm::vec3 m_Right = glm::vec3(0.0f);
		glm::vec3 m_Up = glm::vec3(0.0f);

		void ComputeLocalModelMatrix();
		void ComputeModelMatrix();
		void ComputeLocalDirectionVectors();
		void ComputeDirectionVectors();
	};
}
