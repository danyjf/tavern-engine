#pragma once

#include <glm/glm.hpp>

#include "Tavern/Core/Core.h"
#include "Tavern/Components/Component.h"

namespace Tavern
{
	class TAVERN_API Transform : public Component
	{
	public:
		Transform(Entity* owner);
		~Transform();

		const glm::vec3& GetPosition() const;
		void SetPosition(const glm::vec3& position);

		const glm::vec3& GetRotation() const;
		void SetRotation(const glm::vec3& rotation);

		const glm::vec3& GetScale() const;
		void SetScale(const glm::vec3& scale);

		const glm::mat4& GetModelMatrix() const;

	private:
		glm::mat4 m_ModelMatrix;
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale;

		void ComputeModelMatrix();
	};
}
