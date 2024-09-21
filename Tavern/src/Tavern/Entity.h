#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Tavern/Core/Core.h"
#include "Tavern/Renderer/Shader.h"
#include "Tavern/Renderer/Texture.h"

namespace Tavern
{
	class TAVERN_API Entity
	{
	public:
		Entity();
		virtual ~Entity();

		virtual void Update();

		void AddTexture(const Texture& texture);
		void SetPosition(const glm::vec3& position);
		void SetRotation(const glm::vec3& rotation);
		void SetScale(const glm::vec3& scale);

	private:
		Shader* m_Shader;
		std::vector<Texture> m_Textures;
		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;
		glm::mat4 m_ModelMatrix = glm::mat4(1.0f);
		glm::vec3 m_Position = glm::vec3(0.0f);
		glm::vec3 m_Rotation = glm::vec3(0.0f);
		glm::vec3 m_Scale = glm::vec3(1.0f);

		void ComputeModelMatrix();
	};
}
