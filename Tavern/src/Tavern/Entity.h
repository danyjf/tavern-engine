#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "Tavern/Core/Core.h"

namespace Tavern
{
	class Shader;
	class Texture;
	class Transform;

	class TAVERN_API Entity
	{
	public:
		Entity();
		virtual ~Entity();

		std::unique_ptr<Transform> m_Transform;

		virtual void Update();

		void AddTexture(const Texture& texture);

	private:
		Shader* m_Shader;
		std::vector<Texture> m_Textures;
		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;
	};
}
