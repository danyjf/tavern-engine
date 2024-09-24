#pragma once

#include <glm/glm.hpp>

#include "Tavern/Core/Core.h"

namespace Tavern
{
	class TAVERN_API Transform
	{
	public:
		Transform();
		~Transform();

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position);

		const glm::vec3& GetRotation() const { return m_Rotation; }
		void SetRotation(const glm::vec3& rotation);

		const glm::vec3& GetScale() const { return m_Scale; }
		void SetScale(const glm::vec3& scale);

		const glm::mat4& GetModelMatrix() const { return m_ModelMatrix; }

	private:
		glm::mat4 m_ModelMatrix = glm::mat4(1.0f);
		glm::vec3 m_Position = glm::vec3(0.0f);
		glm::vec3 m_Rotation = glm::vec3(0.0f);
		glm::vec3 m_Scale = glm::vec3(1.0f);

		void ComputeModelMatrix();
	};
}
